// <copyright file="daqmx_done_handler.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_DAQMX_DONE_HANDLER_H)
#define _PWROWG_DAQMX_DONE_HANDLER_H
#pragma once
#if defined(POWER_OVERWHELMING_WITH_DAQMX)

#include <cassert>
#include <cstdlib>
#include <memory>

#if defined(POWER_OVERWHELMING_WITH_DAQMX)
#include <NIDAQmx.h>
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */

#include "visus/pwrowg/handler_functions.h"


// Forward declarations.
PWROWG_NAMESPACE_BEGIN
class daqmx_task;
PWROWG_NAMESPACE_END;


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// This class functions as an adapter that allows for all kinds of C++
/// callables, most notably lambdas, to be used as DAQmx done event handlers.
/// </summary>
/// <remarks>
/// <para>Users of this library should not make any assumptions about this type,
/// but treat the as opaque handles.</para>
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
/// <see cref="install" /> factory returns and free it using
/// <see langword="delete" /> to unregister the handler.</para>
/// </remarks>
class POWER_OVERWHELMING_API daqmx_done_handler final {

public:

    /// <summary>
    /// Installs a new event handler <paramref name="callback" /> for the event
    /// fired when <paramref name="task" /> is completed.
    /// </summary>
    /// <typeparam name="TCallback">A callable receiving a reference to the
    /// <see cref="daqmx_task" /> representing the completed task and an integer
    /// representing the status of the task. The callback should return zero to
    /// indicate success or a NI-DAQmx error code.</typeparam>
    /// <param name="task">The task for which the handler should be installed.
    /// </param>
    /// <param name="callback"></param>
    /// <returns>An instance of the wrapper, which must be
    /// <see langword="delete" />d in order to unregister the handler and to
    /// free the memory associated with it. Typically, this pointer is only used
    /// as a handle in the public API and should not be deleted by the users of
    /// the library.</returns>
    template<class TCallback> static _Ret_valid_ daqmx_done_handler *install(
        _In_ daqmx_task& task, _In_ TCallback&& callback);

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
            _In_ const std::size_t size, _In_ TContext&& context) {
        return allocate_with_context(size, std::forward<TContext>(context));
    }

    /// <summary>
    /// Frees the memory allocated for an instance of the handler.
    /// </summary>
    /// <param name="ptr">The memory to be freed.</param>
    static inline void operator delete(_In_ void *ptr) noexcept {
        free_with_context(ptr);
    }

    daqmx_done_handler(const daqmx_done_handler&) = delete;

    daqmx_done_handler(daqmx_done_handler&&) = delete;

    /// <summary>
    /// Finalises the instance.
    /// </summary>
    ~daqmx_done_handler(void) noexcept;

    daqmx_done_handler& operator =(const daqmx_done_handler&) = delete;

    daqmx_done_handler& operator =(daqmx_done_handler&&) = delete;

private:

    /// <summary>
    /// The type of the native callback function.
    /// </summary>
    typedef DAQmxDoneEventCallbackPtr callback_type;

    /// <summary>
    /// The type of a destructor callback that is deleting the callback context.
    /// </summary>
    typedef void (*destructor_type)(daqmx_done_handler *);

    /// <summary>
    /// Calls the destructor of <typeparamref name="TContext" /> on the context
    /// of the instance.
    /// </summary>
    template<class TContext>
    static void dtor(_In_ daqmx_done_handler *ptr) noexcept {
        assert(ptr != nullptr);
        auto ctx = reinterpret_cast<TContext *>(ptr + 1);
        ctx->~TContext();
    }

    /// <summary>
    /// Unpacks the <typeparamref name="TCallback" /> stored after the
    /// <paramref name="context" /> and invokes it.
    /// </summary>
    template<class TCallback> static int32 CVICALLBACK invoke(
        _In_ const TaskHandle task,
        _In_ const int32 status,
        _In_ void *context);

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <remarks>
    /// No constructor of this class must throw an exception as this might
    /// orphan resources in the context placed behind it in memory during
    /// allocation. Only the destructor of a successfully initialised instance
    /// will free these resources.
    /// </remarks>
    /// <param name="task">The DAQmx task to register to.</param>
    /// <param name="dtor">The destructor callback to be used for the context of
    /// the instance.</param>
    daqmx_done_handler(_In_ daqmx_task& task,
        _In_ const destructor_type dtor) noexcept;

    /// <summary>
    /// Installs the given callback with the <see langword="this" /> pointer as
    /// context.
    /// </summary>
    /// <param name="callback">An instance of <see cref="invoke" /> for the
    /// correct callable type.</param>
    void install(_In_ const callback_type callback);

    destructor_type _dtor;
    daqmx_task& _task;
};

PWROWG_DETAIL_NAMESPACE_END

#include "visus/pwrowg/daqmx_done_handler.inl"

#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
#endif /* !defined(_PWROWG_DAQMX_DONE_HANDLER_H) */
