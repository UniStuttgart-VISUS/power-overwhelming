// <copyright file="sensor_array_sate.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_SENSOR_ARRAY_STATE_H)
#define _PWROWG_SENSOR_ARRAY_STATE_H
#pragma once

#include "visus/pwrowg/api.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Possible states the <see cref="sensor_array" /> can be in.
/// </summary>
enum class sensor_array_state {

    /// <summary>
    /// The sensors are stopped and can be started.
    /// </summary>
    stopped,

    /// <summary>
    /// The array is in the process of starting the sensors.
    /// </summary>
    starting,

    /// <summary>
    /// The sensors are running and delivering data to the callbacks.
    /// </summary>
    running,

    /// <summary>
    /// The sensors are being stopped, but some are still running.
    /// </summary>
    stopping
};

PWROWG_DETAIL_NAMESPACE_END

#endif  /* !defined(_PWROWG_SENSOR_ARRAY_STATE_H) */
