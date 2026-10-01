// <copyright file="sensor_array_state.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_SENSOR_ARRAY_STATE_H)
#define _PWROWG_SENSOR_ARRAY_STATE_H
#pragma once

#include "visus/pwrowg/api.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Possible state changes that the sensor array can report to its sensors.
/// </summary>
enum class sensor_array_state {

    /// <summary>
    /// The sensor array is not running.
    /// </summary>
    stopped,

    /// <summary>
    /// The sensor array is in the process of starting all sensors. They might
    /// be sampled soon.
    /// </summary>
    starting,

    /// <summary>
    /// The sensor array has started all sensors.
    /// </summary>
    started,

    /// <summary>
    /// The sensor array is periodically sampling the sensors.
    /// </summary>
    running,

    /// <summary>
    /// The sensor array is preparing to shut down all sensors. They might still
    /// be sampled until the <see cref="stopped" /> state is reached.
    /// </summary>
    stopping,
};

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_SENSOR_ARRAY_STATE_H) */
