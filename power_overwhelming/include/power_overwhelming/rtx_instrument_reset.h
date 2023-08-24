// <copyright file="rtx_instrument_reset.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cinttypes>
#include <limits>
#include <type_traits>


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Defines the scope of <see cref="rtx_instrument::reset" />.
    /// </summary>
    enum class rtx_instrument_reset : std::uint64_t {

        /// <summary>
        /// Performs a simple reset (<c>*RST</c>).
        /// </summary>
        /// <remarks>
        /// The default instrument reset is always performed. You can add
        /// additional things to reset by adding the other flags.
        /// </remarks>
        reset,

        /// <summary>
        /// Flushes all I/O buffers.
        /// </summary>
        /// <remarks>
        /// The buffer reset includes reading as much as possible from
        /// the device followed by a <c>viClear</c>.
        /// </remarks>
        buffers = 0x0001,

        /// <summary>
        /// Clears the status bits (<c>*CLS</c>).
        /// </summary>
        status = 0x0002,

        /// <summary>
        /// Stops the acquisition after the reset, which will put the device in
        /// the run state.
        /// </summary>
        stop = 0x0004,

        /// <summary>
        /// All possible things that we can reset right now and possibly in
        /// the future ...
        /// </summary>
        all = (std::numeric_limits<std::uint64_t>::max)()
    };


    /// <summary>
    /// Performs a bitwise combination of the given
    /// <see cref="rtx_instrument_reset" />s.
    /// </summary>
    /// <param name="lhs">The left-hand side operand.</param>
    /// <param name="rhs">The right-hand side operand.</param>
    /// <returns>The combined pins.</returns>
    inline rtx_instrument_reset operator |(
            _In_ const rtx_instrument_reset lhs,
            _In_ const rtx_instrument_reset rhs) {
        typedef std::decay<decltype(lhs)>::type enum_type;
        auto l = static_cast<std::underlying_type<enum_type>::type>(lhs);
        auto r = static_cast<std::underlying_type<enum_type>::type>(rhs);
        return static_cast<enum_type>(l | r);
    }

    /// <summary>
    /// Performs a bitwise intersection of the given
    /// <see cref="rtx_instrument_reset" />s.
    /// </summary>
    /// <param name="lhs">The left-hand side operand.</param>
    /// <param name="rhs">The right-hand side operand.</param>
    /// <returns>The intersected pins.</returns>
    inline rtx_instrument_reset operator &(
            _In_ const rtx_instrument_reset lhs,
            _In_ const rtx_instrument_reset rhs) {
        typedef std::decay<decltype(lhs)>::type enum_type;
        auto l = static_cast<std::underlying_type<enum_type>::type>(lhs);
        auto r = static_cast<std::underlying_type<enum_type>::type>(rhs);
        return static_cast<enum_type>(l & r);
    }

} /* namespace power_overwhelming */
} /* namespace visus */
