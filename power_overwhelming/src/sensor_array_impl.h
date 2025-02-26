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
        sensor_description *, void *context)> sampler_func;

    /// <summary>
    /// Answer the sample callback stored in the given array.
    /// </summary>
    /// <param name="impl">The array to check retrieve the callback from.
    /// </param>
    /// <returns>The callback stored in the given array.</returns>
    static inline sensor_array_callback callback(
            _In_ const sensor_array_impl *impl) {
        assert(impl != nullptr);
        assert(impl->configuration != nullptr);
        return impl->configuration->callback;
    }

    /// <summary>
    /// Invokes the sample callback stored in the given array.
    /// </summary>
    /// <param name="impl">The sensor array to invoke the callback of.</param>
    /// <param name="samples">The samples to be delivered.</param>
    /// <param name="cnt">The number of samples to be delivered.</param>
    static inline void callback(_In_ const sensor_array_impl *impl,
            _In_reads_(cnt) const sample *samples,
            _In_ const std::size_t cnt) {
        callback(impl)(samples, cnt, raw_descriptions(impl), context(impl));
    }

    /// <summary>
    /// Answer the user-defined context pointer stored in the given array.
    /// </summary>
    /// <param name="impl">The array to check retrieve the context from.
    /// </param>
    /// <returns>The context stored in the given array.</returns>
    static inline _Ret_maybenull_ void *context(
            _In_ const sensor_array_impl *impl) {
        assert(impl != nullptr);
        assert(impl->configuration != nullptr);
        return impl->configuration->context;
    }

    /// <summary>
    /// Answer the sensor list of the array as a raw pointer.
    /// </summary>
    /// <param name="impl">The array to check retrieve the context from.
    /// </param>
    /// <returns>The context stored in the given array.</returns>
    static inline _Ret_maybenull_ const sensor_description *raw_descriptions(
            _In_ const sensor_array_impl *impl) {
        assert(impl != nullptr);
        return impl->descriptions.data();
    }

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
