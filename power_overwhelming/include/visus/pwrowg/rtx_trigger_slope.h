// <copyright file="rtx_trigger_slope.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>

#if !defined(_PWROWG_RTX_TRIGGER_SLOPE_H)
#define _PWROWG_RTX_TRIGGER_SLOPE_H
#pragma once

#include "visus/pwrowg/api.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Defines possible slopes for edge triggers on an oscillosope.
/// </summary>
enum class rtx_trigger_slope {

    /// <summary>
    /// Triggers on rising and falling edges.
    /// </summary>
    both,

    /// <summary>
    /// Triggers on the rising edge only.
    /// </summary>
    rising,

    /// <summary>
    /// Triggers on the falling edge only.
    /// </summary>
    falling
};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_RTX_TRIGGER_SLOPE_H) */
