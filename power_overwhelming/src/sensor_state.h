// <copyright file="sensor_state.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_SENSOR_STATE_H)
#define _PWROWG_SENSOR_STATE_H
#pragma once

#include "visus/pwrowg/api.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Possible states any of the sensors and the the
/// <see cref="sensor_array" /> as a whole can be in.
/// </summary>
enum class sensor_state {

    /// <summary>
    /// The sensors or the array are stopped and can be started.
    /// </summary>
    stopped,

    /// <summary>
    /// The sensor is starting and in a state where it cannot be modified,
    /// or the array is in the process of starting the sensors.
    /// </summary>
    /// <remarks>
    /// The following states can be <see cref="running" /> if the startup has
    /// succeeded, or <see cref="stopped" /> in case of an error.
    /// </remarks>
    starting,

    /// <summary>
    /// The sensor or the array are running and delivering data to the
    /// callbacks.
    /// </summary>
    running,

    /// <summary>
    /// The sensors are being stopped, but some are still running, or a single
    /// sensor is in a transitional state where it cannot be modified.
    /// </summary>
    /// <remarks>
    /// The next state after this must be <see cref="stopped" />.
    /// </remarks>
    stopping
};

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_SENSOR_STATE_H) */
