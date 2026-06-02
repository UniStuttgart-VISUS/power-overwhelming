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

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_RTX_TRIGGER_TYPE_H) */
