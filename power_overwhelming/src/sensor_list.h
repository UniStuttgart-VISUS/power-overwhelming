// <copyright file="sensor_list.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_SENSOR_LIST_H)
#define _PWROWG_SENSOR_LIST_H
#pragma once

#include <cassert>
#include <chrono>
#include <list>
#include <memory>
#include <vector>

#include "visus/pwrowg/sensor_array_callback.h"

#include "detect_sample.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// A container for all sensors of type <typeparamref name="TSensor" />.
/// </summary>
template<class TSensor> struct sensor_list {

    /// <summary>
    /// The type of a sensor in this list.
    /// </summary>
    typedef TSensor value_type;

    /// <summary>
    /// The type of the synchronous sampler function.
    /// </summary>
    typedef void (TSensor:: *sampler_type)(
        _In_ const sensor_array_callback callback,
        _In_opt_ void *context);

    /// <summary>
    /// Holds function pointer to the synchronous sample function of the
    /// <see cref="sensors" />.
    /// </summary>
    sampler_type sampler;

    /// <summary>
    /// Holds the actual sensors.
    /// </summary>
    /// <remarks>
    /// A list is used here, because sensors do not have to be copyable or
    /// movable for this container to work.
    /// </remarks>
    std::list<value_type> sensors;

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    inline sensor_list(void) : sampler(nullptr) { }

    /// <summary>
    /// Samples <paramref name="cnt" /> of the <see cref="sensors" /> starting
    /// at offset <paramref name="begin" /> provided the synchronous
    /// <see cref="sampler" /> is set.
    /// </summary>
    /// <param name="begin"></param>
    /// <param name="cnt"></param>
    /// <param name="callback"></param>
    /// <param name="context"></param>
    void sample(_In_ const std::size_t begin,
        _In_ const std::size_t cnt,
        _In_ const sensor_array_callback callback,
        _In_opt_ void *context);

    /// <summary>
    /// Starts or stops (if <paramref name="callback" /> is <c>nullptr</c>) the
    /// asynchronous sampling of <see cref="sensors" /> provided the
    /// <see cref="value_type" /> supports asynchronous sampling.
    /// </summary>
    /// <param name="callback"></param>
    /// <param name="interval"></param>
    /// <param name="context"></param>
    /// <returns><c>true</c> if the sampling was started or stopped, <c>false</c>
    /// if the sensor cannot perform asynchronous sampling.</returns>
    bool sample(_In_opt_ const sensor_array_callback callback,
        _In_ const std::chrono::milliseconds interval,
        _In_opt_ void *context);
};

PWROWG_DETAIL_NAMESPACE_END

#include "sensor_list.inl"

#endif /* !defined(_PWROWG_SENSOR_LIST_H) */
