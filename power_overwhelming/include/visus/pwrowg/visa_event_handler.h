// <copyright file="visa_event_handler.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_VISA_EVENT_HANDLER_H)
#define _PWROWG_VISA_EVENT_HANDLER_H
#pragma once
#if defined(POWER_OVERWHELMING_WITH_VISA)

#include <cassert>
#include <cinttypes>
#include <cstdlib>
#include <memory>
#include <type_traits>

#include <visa.h>

#include "visus/pwrowg/handler_functions.h"
#include "visus/pwrowg/visa_object.h"


// Forward declarations.
PWROWG_NAMESPACE_BEGIN
class visa_instrument;
PWROWG_NAMESPACE_END;


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// This class functions as an adapter that allows for all kinds of C++
/// callables, most notably lambdas, to be used as VISA event handlers.
/// </summary>
/// <remarks>
/// <para>Users of this library should not make any assumptions about this type,
/// but treat the pointers they receive from the <see cref="visa_instrument" />
/// as opaque handles.</para>
/// <para>This type works by allocating instances on the heap with additional
/// space behind to hold the C++ callable to be invoked. This is achieved by
/// providing a specialised <see cref="operator new" /> that allocates more
/// space than requested and in-place constructs the callable behind the
/// requested memory block. The destructor of the handler will call a
/// type-erased destructor callback for the context. Therefore, it is important
/// that the context is always located directly behind the object and that the
/// contructor of the handler never fails. Otherwise, the already initialised
/// context might leave orphaned resources.</para>
/// <para>It is paramount that any object of this type is located on the heap
/// as it must live as long as it is registered as event handler. Do not
/// attempt any shenanigans with this type! Only use what the
/// <see cref="create" /> factory returns and free it using
/// <see langword="delete" /> <i>after</i> the handler has been unregistered
/// from VISA.</para>
/// </remarks>
class POWER_OVERWHELMING_API visa_event_handler final {

public:

    /// <summary>
    /// Creates a new event handler <paramref name="callback" /> for the given
    /// <paramref name="event_type" /> on the VISA session of the given
    /// <param name="instrument" />, which can be installed using the
    /// <ses cref="viInstallHandler" /> function for said session.
    /// </summary>
    /// <typeparam name="TCallback">A callable receiving a reference to the
    /// <see cref="visa_instrument" />, the <see cref="ViEventType" /> and a
    /// <see cref="visa_object" /> representing the event itself.</typeparam>
    /// <param name="instrument">The VISA instrument for which the event handler
    /// is intended. The caller is responsible for making sure that the handler
    /// is installed to the session of this instrument.</param>
    /// <param name="event_type">The type of the event to subscribe.</param>
    /// <param name="callback">The callback to be invoked.</param>
    /// <returns>An instance of the wrapper, which must be
    /// <see langword="delete" />d after the handler has been unregistered.
    /// Typically, this pointer is only used as a handle in the public API and
    /// should not be deleted by the users of the library.</returns>
    template<class TCallback> static _Ret_valid_ visa_event_handler *create(
        _In_ visa_instrument& instrument,
        _In_ const ViEventType event_type,
        _In_ TCallback&& callback);

    /// <summary>
    /// Allocates the memory for a new instance of the handler along with a
    /// <see cref="TContext" />, which will be initialised by passing
    /// <paramref name="context" />.
    /// </summary>
    /// <typeparam name="TContext">The type of the context to be allocated along
    /// with the instance.</typeparam>
    /// <param name="size">The size of the instance to be allocated.</param>
    /// <param name="context">The context to be passed around with the instance.
    /// </param>
    /// <returns>The allocated memory for the instance and the context, but only
    /// if the context object was successfully initialised. The allocation will
    /// fail if the context could not be initialised, in which case any
    /// exception from its constructor will be propagated to the caller.
    /// </returns>
    /// <exception cref="std::bad_alloc">If the allocation failed.</exception>
    template<class TContext> static void *operator new(
            _In_ const std::size_t size,
            _In_ TContext&& context) {
        return allocate_with_context(size, std::forward<TContext>(context));
    }

    /// <summary>
    /// Frees the memory allocated for an instance of the handler.
    /// </summary>
    /// <param name="ptr">The memory to be freed.</param>
    static inline void operator delete(_In_ void *ptr) noexcept {
        free_with_context(ptr);
    }

    visa_event_handler(const visa_event_handler&) = delete;

    visa_event_handler(visa_event_handler&&) = delete;

    /// <summary>
    /// Finalises the instance.
    /// </summary>
    inline ~visa_event_handler(void) noexcept {
        this->_dtor(this);
    }

    visa_event_handler& operator =(const visa_event_handler&) = delete;

    visa_event_handler& operator =(visa_event_handler&&) = delete;

    /// <summary>
    /// Answer the native event handler to be installed.
    /// </summary>
    /// <returns>The native event handler.</returns>
    inline _Ret_valid_ operator ViHndlr(void) const noexcept {
        return this->_handler;
    }

    /// <summary>
    /// Answer the type the handler is for.
    /// </summary>
    /// <returns>The type of events being handled by this instance.</returns>
    inline operator ViEventType(void) const noexcept {
        return this->_type;
    }

private:

    /// <summary>
    /// The type of a destructor callback that is deleting the callback context.
    /// </summary>
    typedef void (*destructor_type)(visa_event_handler *);

    /// <summary>
    /// Calls the destructor of <typeparamref name="TContext" /> on the context
    /// of the instance.
    /// </summary>
    template<class TContext>
    static void dtor(_In_ visa_event_handler *ptr) noexcept {
        assert(ptr != nullptr);
        auto ctx = reinterpret_cast<TContext *>(ptr + 1);
        ctx->~TContext();
    }

    /// <summary>
    /// The native callback function that is used to invoke functors from VISA.
    /// The task of this callback is (i) unpacking the C++ callable the user
    /// wants to be invoked, (ii) wrapping the <paramref name="event" /> in a
    /// RAII object that will automatically be released on exit and (iii)
    /// invoking the C++ callable with the <see cref="visa_instrument" /> and
    /// the wrapped event.
    /// </summary>
    template<class TCallback> static ViStatus _VI_FUNCH invoke(
        _In_ const ViSession session,
        _In_ const ViEventType event_type,
        _In_ ViEvent event,
        _In_ ViAddr context);

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <remarks>
    /// No constructor of this class must throw an exception as this might
    /// orphan resources in the context placed behind it in memory during
    /// allocation. Only the destructor of a successfully initialised instance
    /// will free these resources.
    /// </remarks>
    /// <param name="instrument">The instrument object holding the VISA session
    /// to register to.</param>
    /// <param name="type">The type of the event to subscribe to.</param>
    /// <param name="handler">The native handler, which must be an instance of
    /// <see cref="invoke" />.</param>
    /// <param name="dtor">The destructor callback to be used for the context of
    /// the instance.</param>
    visa_event_handler(_In_ visa_instrument& instrument,
        _In_ const ViEventType type,
        _In_ const ViHndlr handler,
        _In_ const destructor_type dtor) noexcept;

    destructor_type _dtor;
    ViHndlr _handler;
    visa_instrument& _instrument;
    ViEventType _type;
};

PWROWG_DETAIL_NAMESPACE_END

#include "visus/pwrowg/visa_event_handler.inl"

#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */
#endif /* !defined(_PWROWG_VISA_EVENT_HANDLER_H) */
