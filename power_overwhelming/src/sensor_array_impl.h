// <copyright file="sensor_array_impl.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_SENSOR_ARRAY_IMPL_H)
#define _PWROWG_SENSOR_ARRAY_IMPL_H
#pragma once

#include <atomic>
#include <vector>

#include "visus/pwrowg/sensor_description.h"

#include "sensor_array_state.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Holds the implementation details of a sensor array.
/// </summary>
struct sensor_array_impl final {

    /// <summary>
    /// Holds the descriptions of all sensors in the array.
    /// </summary>
    std::vector<sensor_description> descriptions;

    /// <summary>
    /// Tracks the state of the array.
    /// </summary>
    std::atomic<sensor_array_state> state;

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    inline sensor_array_impl(void) : state(sensor_array_state::stopped) { }
};

PWROWG_DETAIL_NAMESPACE_END

#endif  /* !defined(_PWROWG_SENSOR_ARRAY_IMPL_H) */
