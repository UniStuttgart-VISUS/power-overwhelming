// <copyright file="sensor.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_SENSOR_H)
#define _PWROWG_SENSOR_H
#pragma once

#include <cinttypes>
#include <cstdlib>

#include "visus/pwrowg/api.h"

#include "sensor_state.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Defines the interface for a generic sensor.
/// </summary>
class sensor {

protected:

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    sensor(void) = default;

};

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_SENSOR_H) */
