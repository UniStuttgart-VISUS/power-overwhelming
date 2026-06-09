// <copyright file="rtx_trigger_type.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_RTX_TRIGGER_TYPE_H)
#define _PWROWG_RTX_TRIGGER_TYPE_H
#pragma once

#include "visus/pwrowg/api.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Enumerated possible types of <see cref="rtx_trigger" />s.
/// </summary>
enum class rtx_trigger_type {

    /// <summary>
    /// Indicates that the trigger is disabled.
    /// </summary>
    none = 0x0,

    /// <summary>
    /// An edge trigger on a rising or falling (or both) edge of the signal.
    /// </summary>
    edge,

    /// <summary>
    /// Enables the B trigger as well.
    /// </summary>
    edge_ab,

    /// <summary>
    /// A trigger based on the width of a pulse, same as <see cref="pulse" />.
    /// </summary>
    width,

    /// <summary>
    /// A trigger based on the width of a pulse, same as <see cref="width" />.
    /// </summary>
    pulse = width,

    /// <summary>
    /// A video or TV trigger.
    /// </summary>
    tv,

    /// <summary>
    /// A serial bus trigger.
    /// </summary>
    bus,

    /// <summary>
    /// A trigger based on a logic pattern.
    /// </summary>
    logic,

    /// <summary>
    /// Triggers on power supply line.
    /// </summary>
    line,

    /// <summary>
    /// Triggers on rise and fall time, same as <see cref="transition" />.
    /// </summary>
    rise_time,

    /// <summary>
    /// Triggers on rise and fall time, same as <see cref="rise_time" />.
    /// </summary>
    transition = rise_time,

    /// <summary>
    /// Trigger on runts, on pulses with smaller amplitude.
    /// </summary>
    runt
};


/// <summary>
/// Parses a <see cref="rtx_trigger_type" /> from its string representation.
/// </summary>
/// <param name="str">The string to be parsed.</param>
/// <returns>The trigger type represented by the string, or
/// <see cref="rtx_trigger_type::none "/> if the string could not be parsed.
/// </returns>
PWROWG_TEST_API rtx_trigger_type parse_rtx_trigger_type(
    _In_z_ const wchar_t *str) noexcept;


/// <summary>
/// Parses a <see cref="rtx_trigger_type" /> from its string representation.
/// </summary>
/// <param name="str">The string to be parsed.</param>
/// <returns>The trigger type represented by the string, or
/// <see cref="rtx_trigger_type::none "/> if the string could not be parsed.
/// </returns>
PWROWG_TEST_API rtx_trigger_type parse_rtx_trigger_type(
    _In_z_ const char *str) noexcept;


/// <summary>
/// Answer the string representation of the trigger type as it is used by the
/// instrument. This string can be used for the VISA command configuring the
/// trigger type.
/// </summary>
/// <param name="value">The type to be converted.</param>
/// <returns>A pointer to a static string representing the type.</returns>
PWROWG_TEST_API _Ret_z_ const char *to_string(
    _In_ const rtx_trigger_type value);

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_RTX_TRIGGER_TYPE_H) */
