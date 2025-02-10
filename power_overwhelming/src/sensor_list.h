// <copyright file="sensor_list.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_SENSOR_LIST_H)
#define _PWROWG_SENSOR_LIST_H
#pragma once

#include <chrono>
#include <list>
#include <memory>
#include <vector>

#include "visus/pwrowg/sensor_array_callback.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// A container for all sensors of type <typeparamref name="TSensor" />.
/// </summary>
template<class TSensor> struct sensor_list {

    /// <summary>
    /// The type of the control function for asynchronous samplers.
    /// </summary>
    typedef void (TSensor:: *async_sampler_type)(
        _In_opt_ const sensor_array_callback callback,
        _In_ const std::chrono::milliseconds interval,
        _In_opt_ void *context);

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
    /// Holds the actual sensors.
    /// </summary>
    /// <remarks>
    /// A list is used here, because sensors do not have to be copyable or
    /// movable for this container to work.
    /// </remarks>
    std::list<value_type> sensors;

    /// <summary>
    /// Holds function pointer to the synchronous sample function of the
    /// <see cref="sensors" />.
    /// </summary>
    sampler_type sample;

    /// <summary>
    /// Holds function pointer to the control function for the asynchronous
    /// sampling of the <see cref="sensors" />.
    /// </summary>
    async_sampler_type sample_async;

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    inline sensor_list(void) : sample(nullptr), sample_async(nullptr) { }
};

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_SENSOR_LIST_H) */
