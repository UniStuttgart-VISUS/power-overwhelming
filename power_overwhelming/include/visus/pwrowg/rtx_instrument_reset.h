// <copyright file="rtx_instrument_reset.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_RTX_INSTRUMENT_RESET_H)
#define _PWROWG_RTX_INSTRUMENT_RESET_H
#pragma once

#include "visus/pwrowg/visa_instrument_reset.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Defines the scope of <see cref="rtx_instrument::reset" />.
/// </summary>
enum class rtx_instrument_reset : std::uint64_t {

    /// <summary>
    /// Does nothing.
    /// </summary>
    none = static_cast<std::uint64_t>(visa_instrument_reset::none),

    /// <summary>
    /// Performs a simple reset (<c>*RST</c>).
    /// </summary>
    reset = static_cast<std::uint64_t>(visa_instrument_reset::reset),

    /// <summary>
    /// Flushes all I/O buffers.
    /// </summary>
    /// <remarks>
    /// The buffer reset includes reading as much as possible from
    /// the device followed by a <c>viClear</c>.
    /// </remarks>
    buffers = static_cast<std::uint64_t>(visa_instrument_reset::buffers),

    /// <summary>
    /// Clears the status bits (<c>*CLS</c>).
    /// </summary>
    status = static_cast<std::uint64_t>(visa_instrument_reset::status),

    /// <summary>
    /// Reads all system errors until the queue is empty.
    /// </summary>
    errors = static_cast<std::uint64_t>(visa_instrument_reset::errors),

    /// <summary>
    /// Stops the acquisition after the reset, which will put the device in
    /// the run state.
    /// </summary>
    stop = static_cast<std::uint64_t>(visa_instrument_reset::all) + 0x0001,

    /// <summary>
    /// Instructs the software to trigger the device before the reset to release
    /// all threads potentially waiting for a trigger.
    /// </summary>
    trigger = static_cast<std::uint64_t>(visa_instrument_reset::all) + 0x0002,

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

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_RTX_INSTRUMENT_RESET_H) */
