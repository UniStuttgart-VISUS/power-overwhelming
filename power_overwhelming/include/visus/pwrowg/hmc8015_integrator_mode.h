// <copyright file="hmc8015_integrator_mode.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_HMC8015_INTEGRATOR_MODE_H)
#define _PWROWG_HMC8015_INTEGRATOR_MODE_H
#pragma once

#include "visus/pwrowg/api.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Defines possible modes of integrator of the the HMC8015 power analyser.
/// </summary>
enum class hmc8015_integrator_mode {

    /// <summary>
    /// Manual integration (user triggered). This is the default behaviour.
    /// </summary>
    manual,

    /// <summary>
    /// Integrate for a specified duration.
    /// </summary>
    duration,

    /// <summary>
    /// Integrate for a specified time span (start and end).
    /// </summary>
    time_span,
};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_HMC8015_INTEGRATOR_MODE_H) */
