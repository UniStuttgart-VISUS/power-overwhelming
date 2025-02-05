// <copyright file="sensor_registry.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_SENSOR_REGISTRY_H)
#define _PWROWG_SENSOR_REGISTRY_H
#pragma once

#include <cassert>
#include <memory>
#include <stdexcept>
#include <vector>

#include "visus/pwrowg/sensor_array_configuration.h"
#include "visus/pwrowg/sensor_description.h"

#include "adl_sensor.h"
#include "emi_sensor.h"
#include "msr_sensor.h"
#include "nvml_sensor.h"
#include "sensor_array_configuration_impl.h"
#include "string_functions.h"
#include "tinkerforge_sensor.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// The type of a sensor registry, which is the central location where all
/// sensors need to be registered in order to be available for use in a
/// sensor array.
/// </summary>
/// <remarks>
/// Implementors should add all their sensors in the <c>typedef</c>
/// <see cref="sensor_registry" /> below, which is used by the
/// <see cref="sensor_array" /> to enumerate all sensors.
/// </remarks>
/// <typeparam name="TSensors">The types of the sensors to be registered.
/// </typeparam>
template<class... TSensors> class basic_sensor_registry final {

public:

    /// <summary>
    /// Adds the default configurations for all of
    /// <typeparamref name="TSensors" /> to the given <paramref name="config" />.
    /// </summary>
    /// <param name="config">An array configuration that should receive the
    /// sensor configuration instances. Not configurations must have been added
    /// to the array configuration before as it is a fatal error if a
    /// configuration ID is used multiple times.</param>
    /// <exception cref="std::logic_error">If a duplicate configuration ID was
    /// found. This can either be caused by passing a <paramref name="config" />
    /// that has already been configured, or by having sensor descriptions with
    /// conflicting ID values. Furthermore, it could be caused by adding the
    /// same sensor multiple times in the instantiation of the
    /// <see cref="basic_sensor_registry" />.</exception>
    static void configure(sensor_array_configuration_impl& config);

    basic_sensor_registry(void) = delete;

private:

    template<class T, class... Ts>
    static void configure0(_In_ sensor_array_configuration_impl& config);

    inline static void configure0(_In_ sensor_array_configuration_impl&) { }

};


/// <summary>
/// The one and only sensor registry where all known sensors are registered.
/// </summary>
typedef basic_sensor_registry<adl_sensor, nvml_sensor> sensor_registry;

PWROWG_DETAIL_NAMESPACE_END

#include "sensor_registry.inl"

#endif /* !defined(_PWROWG_SENSOR_REGISTRY_H) */
