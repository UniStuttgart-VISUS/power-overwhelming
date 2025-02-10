// <copyright file="sensor_array_impl.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_SENSOR_ARRAY_IMPL_H)
#define _PWROWG_SENSOR_ARRAY_IMPL_H
#pragma once

#include <atomic>
#include <chrono>
#include <memory>
#include <vector>

#include "visus/pwrowg/sensor_array_callback.h"
#include "visus/pwrowg/sensor_description.h"

#include "detector.h"
#include "sensor_registry.h"
#include "sensor_state.h"


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
    /// Holds references to all sensors in the array.
    /// </summary>
    /// <remarks>
    /// Note that one sensor stored here might appear as multiple sensors towards
    /// the user of the sensor array, i.e. there is not direct match of the
    /// <see cref="descriptions" /> and the <see cref="sensors" />.
    /// </remarks>
    sensor_registry::sensor_list_type sensors;

    /// <summary>
    /// The user-defined context pointer to be passed to the sample callback.
    /// </summary>
    void *context;

    /// <summary>
    /// Tracks the state of the array.
    /// </summary>
    sensor_state state;

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    inline sensor_array_impl(void) : context(nullptr) { }
};

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_SENSOR_ARRAY_IMPL_H) */
