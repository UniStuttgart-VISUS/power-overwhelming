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

#include "visus/pwrowg/sample.h"

#include "sensor_state.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Defines the interface for a generic sensor.
/// </summary>
/// <remarks>
/// <para>Sensors derived from this class must have the following interface in
/// order to be registered with the <see cref="sensor_registry" />:</para>
/// <para>A public typedef named <c>configuration_type</c> designates the public
/// configuration type for the sensor class. This configuration type must be
/// default constructible.</para>
/// <para>TODO</para>
/// </remarks>
class sensor {

protected:

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    sensor(void) = default;

};

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_SENSOR_H) */
