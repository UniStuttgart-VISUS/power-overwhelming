// <copyright file="visa_instrument_reset.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_VISA_INSTRUMENT_RESET_H)
#define _PWROWG_VISA_INSTRUMENT_RESET_H
#pragma once

#include <cinttypes>
#include <limits>
#include <type_traits>

#include "visus/pwrowg/api.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Defines the scope of <see cref="visa_instrument::reset" />.
/// </summary>
enum class visa_instrument_reset : std::uint32_t {

    /// <summary>
    /// Does nothing.
    /// </summary>
    none = 0x0000,

    /// <summary>
    /// Performs a simple reset (<c>*RST</c>).
    /// </summary>
    reset = 0x0001,

    /// <summary>
    /// Flushes all I/O buffers.
    /// </summary>
    /// <remarks>
    /// The buffer reset includes reading as much as possible from
    /// the device followed by a <c>viClear</c>.
    /// </remarks>
    buffers = 0x0002,

    /// <summary>
    /// Clears the status bits (<c>*CLS</c>).
    /// </summary>
    status = 0x0004,

    /// <summary>
    /// All possible things that we can reset right now and possibly in
    /// the future ...
    /// </summary>
    all = (std::numeric_limits<std::uint32_t>::max)()
};


/// <summary>
/// Performs a bitwise combination of the given
/// <see cref="visa_instrument_reset" />s.
/// </summary>
/// <param name="lhs">The left-hand side operand.</param>
/// <param name="rhs">The right-hand side operand.</param>
/// <returns>The combined pins.</returns>
inline visa_instrument_reset operator |(
        _In_ const visa_instrument_reset lhs,
        _In_ const visa_instrument_reset rhs) {
    typedef std::decay<decltype(lhs)>::type enum_type;
    auto l = static_cast<std::underlying_type<enum_type>::type>(lhs);
    auto r = static_cast<std::underlying_type<enum_type>::type>(rhs);
    return static_cast<enum_type>(l | r);
}

/// <summary>
/// Performs a bitwise intersection of the given
/// <see cref="visa_instrument_reset" />s.
/// </summary>
/// <param name="lhs">The left-hand side operand.</param>
/// <param name="rhs">The right-hand side operand.</param>
/// <returns>The intersected pins.</returns>
inline visa_instrument_reset operator &(
        _In_ const visa_instrument_reset lhs,
        _In_ const visa_instrument_reset rhs) {
    typedef std::decay<decltype(lhs)>::type enum_type;
    auto l = static_cast<std::underlying_type<enum_type>::type>(lhs);
    auto r = static_cast<std::underlying_type<enum_type>::type>(rhs);
    return static_cast<enum_type>(l & r);
}

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_VISA_INSTRUMENT_RESET_H) */
