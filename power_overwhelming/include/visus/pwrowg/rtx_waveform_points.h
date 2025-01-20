// <copyright file="rtx_waveform_points.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>

#if !defined(_PWROWG_RTX_WAVEFORM_POINTS_H)
#define _PWROWG_RTX_WAVEFORM_POINTS_H
#pragma once

#include "visus/pwrowg/api.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Specifies possible types of waveform points to be selected for transfer.
/// </summary>
enum class rtx_waveform_points {

    /// <summary>
    /// The default, which are the points visible on screen at the
    /// resolution visible on screen.
    /// </summary>
    visible,

    /// <summary>
    /// All points a maximum resolution as they are available in memory.
    /// </summary>
    maximum,

    /// <summary>
    /// Points at maximum resolution available in memory, but only for the
    /// visible range.
    /// </summary>
    maximum_visible

};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_RTX_WAVEFORM_POINTS_H) */
