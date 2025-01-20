// <copyright file="log_mode.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_HMC8015_LOG_MODE_H)
#define _PWROWG_HMC8015_LOG_MODE_H
#pragma once

#include "visus/pwrowg/api.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Defines possible logging modes of the HMC8015 power analyser.
/// </summary>
enum class hmc8015_log_mode {

    /// <summary>
    /// Capture data until explicitly stopped or the memory is full.
    /// </summary>
    unlimited,

    /// <summary>
    /// Capture the specified number of samples.
    /// </summary>
    count,

    /// <summary>
    /// Capture for the specified duration after start.
    /// </summary>
    duration,

    /// <summary>
    /// Capture for the specified duration after the given start time.
    /// </summary>
    time_span
};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_HMC8015_LOG_MODE_H) */
