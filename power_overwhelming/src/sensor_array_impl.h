// <copyright file="sensor_array_impl.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_SENSOR_ARRAY_IMPL_H)
#define _PWROWG_SENSOR_ARRAY_IMPL_H
#pragma once

#include <algorithm>
#include <cassert>
#include <atomic>
#include <chrono>
#include <functional>
#include <memory>
#include <thread>
#include <vector>

#include "visus/pwrowg/sensor_array_callback.h"
#include "visus/pwrowg/sensor_description.h"

#include "detector.h"
#include "sensor_array_configuration_impl.h"
#include "sensor_registry.h"
#include "sensor_state.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Holds the implementation details of a sensor array.
/// </summary>
struct sensor_array_impl final {

    /// <summary>
    /// The signature of a sampler function.
    /// </summary>
    typedef std::function<void(const sensor_array_callback callback,
        void *context)> sampler_func;

    /// <summary>
    /// Holds the configuration of the array, including the sample callback
    /// and the user-defined context passed to it.
    /// </summary>
    std::unique_ptr<sensor_array_configuration_impl> configuration;

    /// <summary>
    /// Holds the descriptions of all sensors in the array.
    /// </summary>
    std::vector<sensor_description> descriptions;

    /// <summary>
    /// The synchronous samplers invoked by the <see cref="sampler_threads" />.
    /// </summary>
    std::vector<sampler_func> samplers;

    /// <summary>
    /// The collection of sampler threads used to actively sample inherently
    /// synchronous sensors like NVML.
    /// </summary>
    std::vector<std::thread> sampler_threads;

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
    /// Tracks the state of the array.
    /// </summary>
    sensor_state state;

    /// <summary>
    /// Finalises the instance.
    /// </summary>
    inline ~sensor_array_impl(void) noexcept {
        assert(this->state == sensor_state::value_type::stopped);
#if (defined(DEBUG) || defined(_DEBUG))
        assert(std::none_of(this->sampler_threads.begin(),
            this->sampler_threads.end(),
            [](std::thread& t) { return t.joinable(); }));
#endif /* (defined(DEBUG) || defined(_DEBUG)) */
    }
};

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_SENSOR_ARRAY_IMPL_H) */
