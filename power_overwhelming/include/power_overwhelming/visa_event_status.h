// <copyright file="visa_event_status.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart.
// Licenced under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cinttypes>
#include <type_traits>

#include "power_overwhelming/power_overwhelming_api.h"


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Defines the semantics of the bits in the event status register (ESR)
    /// of a VISA instrument.
    /// </summary>
    enum class visa_event_status : std::uint8_t {

        /// <summary>
        /// Indicates that no event is active or that all events should be
        /// masked.
        /// </summary>
        none = 0x00,

        /// <summary>
        /// This bit is set after the instrument encounters an <c>*OPC</c>
        /// request and all previous commands have been processed.
        /// </summary>
        operation_complete = 0x01,

        /// <summary>
        /// This bit is set if the computer wants to read data from the
        /// instrument without issuing a query before the read operation.
        /// </summary>
        query_error = 0x04,

        /// <summary>
        /// This bit is set if a device-dependent error occurred.
        /// </summary>
        device_dependent_error = 0x08,

        /// <summary>
        /// This bit is set if a command was syntactically correct, but cannot
        /// be processed for other reasons.
        /// </summary>
        execution_error = 0x10,

        /// <summary>
        /// This bit is set if a command was syntactically incorrect or
        /// undefined.
        /// </summary>
        command_error = 0x20,

        /// <summary>
        /// This bit is set when the instrument is switched to manual control.
        /// </summary>
        user_request = 0x40,

        /// <summary>
        /// This bit is set if the device is turned on.
        /// </summary>
        power_on = 0x80
    };

    /// <summary>
    /// Performs a bitwise combination of the given
    /// <see cref="visa_event_status" />s.
    /// </summary>
    /// <param name="lhs">The left-hand side operand.</param>
    /// <param name="rhs">The right-hand side operand.</param>
    /// <returns>The combined event status bits.</returns>
    inline visa_event_status operator |(
            _In_ const visa_event_status lhs,
            _In_ const visa_event_status rhs) {
        typedef std::decay<decltype(lhs)>::type enum_type;
        auto l = static_cast<std::underlying_type<enum_type>::type>(lhs);
        auto r = static_cast<std::underlying_type<enum_type>::type>(rhs);
        return static_cast<enum_type>(l | r);
    }

    /// <summary>
    /// Performs a bitwise intersection of the given
    /// <see cref="visa_event_status" />s.
    /// </summary>
    /// <param name="lhs">The left-hand side operand.</param>
    /// <param name="rhs">The right-hand side operand.</param>
    /// <returns>The intersected event status bits.</returns>
    inline visa_event_status operator &(
            _In_ const visa_event_status lhs,
            _In_ const visa_event_status rhs) {
        typedef std::decay<decltype(lhs)>::type enum_type;
        auto l = static_cast<std::underlying_type<enum_type>::type>(lhs);
        auto r = static_cast<std::underlying_type<enum_type>::type>(rhs);
        return static_cast<enum_type>(l & r);
    }

    /// <summary>
    /// Invers the given <see cref="visa_event_status" /> flags.
    /// </summary>
    /// <param name="status">The flags to invert.</param>
    /// <returns>The inverse of <paramref name="status" />.</returns>
    inline visa_event_status operator ~(_In_ const visa_event_status status) {
        typedef std::decay<decltype(status)>::type enum_type;
        auto s = static_cast<std::underlying_type<enum_type>::type>(status);
        return static_cast<enum_type>(~s);
    }

    /// <summary>
    /// Answer whether the intersection between <paramref name="lhs" /> and
    /// <paramref name="rhs" /> is not empty.
    /// </summary>
    /// <param name="lhs">The left-hand side operand.</param>
    /// <param name="rhs">The right-hand side operand.</param>
    /// <returns><c>true</c> if both operands have at least one bit in common,
    /// <c>false</c> otherwise.</returns>
    inline bool operator &&(_In_ const visa_event_status lhs,
        _In_ const visa_event_status rhs) {
        typedef std::decay<decltype(lhs)>::type enum_type;
        auto l = static_cast<std::underlying_type<enum_type>::type>(lhs);
        auto r = static_cast<std::underlying_type<enum_type>::type>(rhs);
        return ((l & r) != 0);
    }

} /* namespace power_overwhelming */
} /* namespace visus */
