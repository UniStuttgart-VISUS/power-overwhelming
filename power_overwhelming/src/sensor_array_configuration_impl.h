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

#include "visus/pwrowg/sensor_configuration_base.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Holds the implementation details of a configuration object for a sensor
/// array.
/// </summary>
struct sensor_array_configuration_impl final {

    /// <summary>
    /// The type used to store a sensor configuration object.
    /// </summary>
    typedef std::unique_ptr<sensor_configuration_base> sensor_config;

    /// <summary>
    /// Holds the configuration objects of all known sensors.
    /// </summary>
    std::unordered_map<guid, sensor_config> sensor_configs;

    /// <summary>
    /// Gets the sensor configuration registered with the specified ID.
    /// </summary>
    inline sensor_configuration_base *find_sensor_config(_In_ const guid id) {
        auto it = this->sensor_configs.find(id);
        return (it != this->sensor_configs.end()) ? it->second.get() : nullptr;
    }

    /// <summary>
    /// Gets the sensor configuration registered with the specified ID.
    /// </summary>
    inline const sensor_configuration_base *find_sensor_config(
            _In_ const guid id) const {
        auto it = this->sensor_configs.find(id);
        return (it != this->sensor_configs.end()) ? it->second.get() : nullptr;
    }

};

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_SENSOR_ARRAY_CONFIGURATION_IMPL_H) */
