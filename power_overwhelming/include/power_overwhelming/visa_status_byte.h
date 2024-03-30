// <copyright file="visa_status_byte.h" company="Visualisierungsinstitut der Universität Stuttgart">
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
    /// Defines the semantics of the bits in the VISA status byte.
    /// </summary>
    enum class visa_status_byte : std::uint16_t {

        /// <summary>
        /// Indicates that no status bit is set.
        /// </summary>
        none = 0x00,

        /// <summary>
        /// This bit is set if at least one entry is in the error queue.
        /// </summary>
        error_queue_not_empty = 0x04,

        /// <summary>
        /// This bit is set if any of the questionable status registers is set,
        /// which indicate that the instrument is not operating under normal
        /// conditions.
        /// </summary>
        questionable_status = 0x08,

        /// <summary>
        /// This bit is set if a message is available in the output buffer.
        /// </summary>
        message_available = 0x10,

        /// <summary>
        /// This bit is set if the instrument has issues a service request.
        /// </summary>
        master_status = 0x20,

        /// <summary>
        /// This bit is set while the instrument is busy performing an action.
        /// </summary>
        operation_status = 0x40
    };

    /// <summary>
    /// Performs a bitwise combination of the given
    /// <see cref="visa_status_byte" />s.
    /// </summary>
    /// <param name="lhs">The left-hand side operand.</param>
    /// <param name="rhs">The right-hand side operand.</param>
    /// <returns>The combined status bits.</returns>
    inline visa_status_byte operator |(_In_ const visa_status_byte lhs,
            _In_ const visa_status_byte rhs) {
        typedef std::decay<decltype(lhs)>::type enum_type;
        auto l = static_cast<std::underlying_type<enum_type>::type>(lhs);
        auto r = static_cast<std::underlying_type<enum_type>::type>(rhs);
        return static_cast<enum_type>(l | r);
    }

    /// <summary>
    /// Performs a bitwise intersection of the given
    /// <see cref="visa_status_byte" />s.
    /// </summary>
    /// <param name="lhs">The left-hand side operand.</param>
    /// <param name="rhs">The right-hand side operand.</param>
    /// <returns>The intersected status bits.</returns>
    inline visa_status_byte operator &(_In_ const visa_status_byte lhs,
            _In_ const visa_status_byte rhs) {
        typedef std::decay<decltype(lhs)>::type enum_type;
        auto l = static_cast<std::underlying_type<enum_type>::type>(lhs);
        auto r = static_cast<std::underlying_type<enum_type>::type>(rhs);
        return static_cast<enum_type>(l & r);
    }

    /// <summary>
    /// Invers the given <see cref="visa_status_byte" /> flags.
    /// </summary>
    /// <param name="status">The flags to invert.</param>
    /// <returns>The inverse of <paramref name="status" />.</returns>
    inline visa_status_byte operator ~(_In_ const visa_status_byte status) {
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
    inline bool operator &&(_In_ const visa_status_byte lhs,
            _In_ const visa_status_byte rhs) {
        typedef std::decay<decltype(lhs)>::type enum_type;
        auto l = static_cast<std::underlying_type<enum_type>::type>(lhs);
        auto r = static_cast<std::underlying_type<enum_type>::type>(rhs);
        return ((l & r) != 0);
    }

} /* namespace power_overwhelming */
} /* namespace visus */
