// <copyright file="visa_event_handler.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "power_overwhelming/power_overwhelming_api.h"


namespace visus {
namespace power_overwhelming {

    /* Forward declarations. */
    class visa_instrument;


namespace detail {

    /// <summary>
    /// A container for storing the callbacks to be invoked on VISA events.
    /// </summary>
    class visa_event_handler final {

    public:

        /// <summary>
        /// The type of callback to be invoked for the event.
        /// </summary>
        typedef void (*callback_type)(visa_instrument&, void *);

        /// <summary>
        /// The type of an optional user-defined deleter for the context, which
        /// is used if the ownership of the context is transferred to the
        /// <see cref="visa_event_handler" />.
        /// </summary>
        typedef void (*context_deleter_type)(void *);

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        visa_event_handler(void);

        visa_event_handler(const visa_event_handler&) = delete;

        /// <summary>
        /// Move construction.
        /// </summary>
        /// <param name="rhs">The object to be moved.</param>
        visa_event_handler(_Inout_ visa_event_handler&& rhs) noexcept;

        /// <summary>
        /// Finalises the instance.
        /// </summary>
        ~visa_event_handler(void);

        /// <summary>
        /// Installs the given callback.
        /// </summary>
        /// <param name="callback">The callback to be invoked on an event.
        /// </param>
        /// <returns><c>*this</c>.</returns>
        visa_event_handler& callback(
            _In_opt_ const callback_type callback) noexcept;

        /// <summary>
        /// Sets a new context and an optional deleter for the case that
        /// ownership of the context is transferred to the object.
        /// </summary>
        /// <param name="context">A context to be passed to the callback.
        /// </param>
        /// <param name="context_deleter">If not <c>nullptr</c>, the ownership
        /// of <pararmref name="context" /> is transferred to the object, which
        /// will use this function to free the context when necessary.</param>
        /// <returns><c>*this</c>.</returns>
        visa_event_handler& context(_In_opt_ void *context,
            _In_opt_ const context_deleter_type context_deleter = nullptr);

        visa_event_handler& operator =(const visa_event_handler&) = delete;

        /// <summary>
        /// Move assignment.
        /// </summary>
        /// <param name="rhs">The right-hand side operand.</param>
        /// <returns><c>*this</c>.</returns>
        visa_event_handler& operator =(_Inout_ visa_event_handler&& rhs) noexcept;

        /// <summary>
        /// Assign a new callback.
        /// </summary>
        /// <param name="rhs">The right-hand side operand.</param>
        /// <returns><c>*this</c>.</returns>
        visa_event_handler& operator =(_In_opt_ const callback_type rhs) noexcept;

        /// <summary>
        /// Answer whether <paramref name="callback" /> is the callback that is
        /// set as the handler of this event.
        /// </summary>
        /// <param name="callback">The callback to be tested.</param>
        /// <returns><c>true</c> if <paramref name="callback" /> is the
        /// currently set callback, <c>false</c> otherwise.</returns>
        bool operator ==(_In_opt_ const callback_type callback) const noexcept;

        /// <summary>
        /// Answer whether <paramref name="callback" /> is not the callback that
        /// is set as the handler of this event.
        /// </summary>
        /// <param name="callback">The callback to be tested.</param>
        /// <returns><c>false</c> if <paramref name="callback" /> is the
        /// currently set callback, <c>true</c> otherwise.</returns>
        bool operator !=(_In_opt_ const callback_type callback) const noexcept;

        /// <summary>
        /// Answer whether a valid callback is set.
        /// </summary>
        /// <returns><c>true</c> if a callback is set, <c>false</c> if the
        /// current callback is <c>nullptr</c>.</returns>
        inline operator bool(void) const noexcept {
            return (this->_callback != nullptr);
        }

        /// <summary>
        /// Invokes the callback, if one is set, and passes the configured
        /// context to it.
        /// </summary>
        /// <param name="instrument">The instrument to be passed to the
        /// callback. This should be the instrument that generated the event.
        /// </param>
        /// <returns><c>true</c> if the callback was invoked, <c>false</c> if
        /// none was set.</returns>
        bool operator ()(_In_ visa_instrument& instrument) const;

    private:

        callback_type _callback;
        mutable void *_context;
        context_deleter_type _context_deleter;
    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
