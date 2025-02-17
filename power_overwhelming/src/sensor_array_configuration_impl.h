// <copyright file="sensor_array_configuration_impl.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_SENSOR_ARRAY_CONFIGURATION_IMPL_H)
#define _PWROWG_SENSOR_ARRAY_CONFIGURATION_IMPL_H
#pragma once

#include <typeindex>
#include <memory>
#include <unordered_map>

#include "visus/pwrowg/sensor_array_callback.h"
#include "visus/pwrowg/sensor_configuration.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Holds the implementation details of a configuration object for a sensor
/// array.
/// </summary>
struct sensor_array_configuration_impl final {

    /// <summary>
    /// The type used to store a sensor configuration object.
    /// </summary>
    typedef std::unique_ptr<sensor_configuration> sensor_config;

    /// <summary>
    /// An ampty sampler callback, which is user as the default, that does
    /// nothing.
    /// </summary>
    /// <param name=""></param>
    /// <param name=""></param>
    /// <param name=""></param>
    /// <param name=""></param>
    static void sample_nothing(_In_opt_ const sample *samples,
        _In_ const std::size_t cnt,
        _In_opt_ const sensor_description *sensors,
        _In_opt_ void *context) { }

    /// <summary>
    /// The callback that the <see cref="sampler_threads" /> must invoke.
    /// </summary>
    sensor_array_callback callback;

    /// <summary>
    /// The user-defined context pointer to be passed to the sample
    /// <see cref="callback" />.
    /// </summary>
    void *context;

    /// <summary>
    /// The sampling interval for the <see cref="sampler_threads" />.
    /// </summary>
    std::chrono::milliseconds interval;

    /// <summary>
    /// Holds the configuration objects of all known sensors.
    /// </summary>
    std::unordered_map<guid, sensor_config> sensor_configs;

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    inline sensor_array_configuration_impl(void)
        : callback(sample_nothing),
        context(nullptr),
        interval(5000) { }

    /// <summary>
    /// Gets the sensor configuration registered with the specified ID.
    /// </summary>
    inline sensor_configuration *find_sensor_config(_In_ const guid id) {
        auto it = this->sensor_configs.find(id);
        return (it != this->sensor_configs.end()) ? it->second.get() : nullptr;
    }

    /// <summary>
    /// Gets the sensor configuration registered with the specified ID.
    /// </summary>
    inline const sensor_configuration *find_sensor_config(
            _In_ const guid id) const {
        auto it = this->sensor_configs.find(id);
        return (it != this->sensor_configs.end()) ? it->second.get() : nullptr;
    }

};

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_SENSOR_ARRAY_CONFIGURATION_IMPL_H) */
