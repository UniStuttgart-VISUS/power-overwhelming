// <copyright file="throttling_state.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2024 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cinttypes>

#include "visus/pwrowg/api.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Represents possible throttling states the GPU can report.
/// </summary>
enum class throttling_state : std::uint32_t {

    /// <summary>
    /// The GPU is currently not throttled.
    /// </summary>
    none = 0x00000000,

    /// <summary>
    /// The GPU performance is limited by the total power limit.
    /// </summary>
    power = 0x00000001,

    /// <summary>
    /// The GPU performance is limited by the temperature limit.
    /// </summary>
    thermal = 0x00000002,

    /// <summary>
    /// The GPU performance is limited by the total current limit.
    /// </summary>
    current = 0x00000004,

    /// <summary>
    /// The GPU performance is limited by reliability voltage.
    /// </summary>
    reliability = 0x00000008,

    /// <summary>
    /// The GPU performance is limited by the maximum operating voltage.
    /// </summary>
    voltage = 0x000000010,

    /// <summary>
    /// The GPU performance is limited by GPU utilisation.
    /// </summary>
    utilisation = 0x00000020,

    /// <summary>
    /// The GPU is throttled due to some unknown other reason.
    /// </summary>
    other = 0x80000000
};

/// <summary>
/// Combine two <see cref="throttling_state" />s.
/// </summary>
/// <param name="lhs">The left-hand side operand.</param>
/// <param name="rhs">The right-hand side operand.</param>
/// <returns>The bitwise &quot;or&quot; of the two operands.</returns>
extern  POWER_OVERWHELMING_API throttling_state operator |(
    _In_ const throttling_state lhs, _In_ const throttling_state rhs);

/// <summary>
/// Test two <see cref="throttling_state" />s.
/// </summary>
/// <param name="lhs">The left-hand side operand.</param>
/// <param name="rhs">The right-hand side operand.</param>
/// <returns>The bitwise &quot;and&quot; of the two operands.</returns>
extern POWER_OVERWHELMING_API throttling_state operator &(
    _In_ const throttling_state lhs, _In_ const throttling_state rhs);

PWROWG_NAMESPACE_END
