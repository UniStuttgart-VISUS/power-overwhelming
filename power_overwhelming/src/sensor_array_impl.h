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
#include <vector>

#include "visus/pwrowg/sensor_array_callback.h"
#include "visus/pwrowg/sensor_description.h"

#include "detector.h"
#include "sensor_state.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Holds the implementation details of a sensor array.
/// </summary>
struct sensor_array_impl final {

    /// <summary>
    /// The detector type for the asynchronous sample method.
    /// </summary>
    /// <typeparam name="TType"></typeparam>
    template<class TType>
    using async_sample = decltype(std::declval<TType &>().sample(
        std::declval<sensor_array_callback>(),
        std::declval<std::chrono::milliseconds>(),
        std::declval<void *>()));

    /// <summary>
    /// The detector type for the synchronous sample method.
    /// </summary>
    /// <typeparam name="TType"></typeparam>
    template<class TType>
    using sync_sample = decltype(std::declval<TType&>().sample(
        std::declval<sensor_array_callback>(),
        std::declval<void *>()));

    /// <summary>
    /// Detects whether <typeparamref name="TType" /> uses asynchronous
    /// sampling.
    /// </summary>
    /// <typeparam name="TType"></typeparam>
    template<class TType>
    using has_async_sample = typename detector<async_sample, void, TType>::type;

    /// <summary>
    /// Detects whether <typeparamref name="TType" /> uses synchronous sampling.
    /// </summary>
    /// <typeparam name="TType"></typeparam>
    template<class TType>
    using has_sync_sample = typename detector<sync_sample, void, TType>::type;

    /// <summary>
    /// Holds the descriptions of all sensors in the array.
    /// </summary>
    std::vector<sensor_description> descriptions;

    /// <summary>
    /// Tracks the state of the array.
    /// </summary>
    sensor_state state;

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    inline sensor_array_impl(void) = default;
};

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_SENSOR_ARRAY_IMPL_H) */
