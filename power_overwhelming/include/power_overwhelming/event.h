// <copyright file="event.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2018 - 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#if defined(_WIN32)
#define NOMINMAX
#include <Windows.h>
#else /*defined(_WIN32) */
#define POWER_OVERWHELMING_EVENT_EMULATION
#endif /* defined(_WIN32) */

#include "power_overwhelming/power_overwhelming_api.h"


namespace visus {
namespace power_overwhelming {

    /* Forward declarations. */
#if defined(POWER_OVERWHELMING_EVENT_EMULATION)
    namespace detail { struct event_impl; }
#endif /* defined(POWER_OVERWHELMING_EVENT_EMULATION) */

    /// <summary>
    /// Represents an opaque event handle.
    /// </summary>
    /// <remarks>
    /// Callers should not make any assumptions about the internals of the event
    /// handle.
    /// </remarks>
#if defined(POWER_OVERWHELMING_EVENT_EMULATION)
    typedef detail::event_impl *event_type;
#else /* defined(POWER_OVERWHELMING_EVENT_EMULATION) */
    typedef HANDLE event_type;
#endif /* defined(POWER_OVERWHELMING_EVENT_EMULATION) */

    /// <summary>
    /// Allocates a new event object.
    /// </summary>
    /// <param name="manual_reset"></param>
    /// <param name="initially_signalled"></param>
    /// <returns></returns>
    /// <exception cref="std::bad_alloc"></exception>
    /// <exception cref="std::system_error"></exception>
    extern event_type POWER_OVERWHELMING_API create_event(
        const bool manual_reset = false,
        const bool initially_signalled = false);

    /// <summary>
    /// Destroys the given event.
    /// </summary>
    /// <param name="event">The event to be released.</param>
    extern void POWER_OVERWHELMING_API destroy_event(event_type& event);

    /// <summary>
    /// Resets a manual reset event.
    /// </summary>
    /// <param name="event">The handle of the event to reset.</param>
    /// <exception cref="std::system_error">In case the operation failed.
    /// </exception>
    extern void POWER_OVERWHELMING_API reset_event(event_type event);

    /// <summary>
    /// Signals an event.
    /// </summary>
    /// <param name="event">The handle of the event to set.</param>
    /// <exception cref="std::system_error">In case the operation failed.
    /// </exception>
    extern void POWER_OVERWHELMING_API set_event(event_type event);

    /// <summary>
    /// Waits for an event to become signalled.
    /// </summary>
    /// <param name="event">The handle of the event to wait for.</param>
    /// <exception cref="std::system_error">In case the operation failed.
    /// </exception>
    extern void POWER_OVERWHELMING_API wait_event(event_type event);

    /// <summary>
    /// Waits for an event to become signalled.
    /// </summary>
    /// <param name="event">The handle of the event to wait for.</param>
    /// <param name="timeout">The timeout to wait in milliseconds.</param>
    /// <returns><c>true</c> if the event was signalled in time, <c>false</c> if
    /// the operation timed out without another error.</returns>
    /// <exception cref="std::system_error">In case the operation failed.
    /// </exception>
    extern bool POWER_OVERWHELMING_API wait_event(event_type event,
        const unsigned int timeout);

} /* namespace power_overwhelming */
} /* namespace visus */
