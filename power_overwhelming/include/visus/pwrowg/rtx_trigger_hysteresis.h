// <copyright file="rtx_trigger_hysteresis.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>

#if !defined(_PWROWG_RTX_TRIGGER_HYSTERESIS_H)
#define _PWROWG_RTX_TRIGGER_HYSTERESIS_H
#pragma once

#include "visus/pwrowg/api.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Defines possible hysteresis ranges around trigger levels on oscilloscopes.
/// </summary>
enum class rtx_trigger_hysteresis {

    /// <summary>
    /// Let the instrument decide, which is the default on reset.
    /// </summary>
    automatic,

    /// <summary>
    /// Small range.
    /// </summary>
    low,

    /// <summary>
    /// Medium range.
    /// </summary>
    medium,

    /// <summary>
    /// Large range.
    /// </summary>
    high
};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_RTX_TRIGGER_HYSTERESIS_H) */
