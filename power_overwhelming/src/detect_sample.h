// <copyright file="detect_sample.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_DETECT_SAMPLE_H)
#define _PWROWG_DETECT_SAMPLE_H
#pragma once

#include <chrono>
#include <utility>

#include "visus/pwrowg/sensor_array_callback.h"

#include "detector.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// The detector type for the asynchronous sample method to be used by
/// <see ref="has_async_sample" />.
/// </summary>
/// <typeparam name="TType">The type to be check for an asynchronous sampling
/// method.</typeparam>
template<class TType>
using _async_sample= decltype(std::declval<TType &>().sample(
    std::declval<sensor_array_callback>(),
    std::declval<std::chrono::milliseconds>(),
    std::declval<void *>()));

/// <summary>
/// The detector type for the synchronous sample method to be used by
/// <see cref="has_sync_sample" />.
/// </summary>
/// <typeparam name="TType">The type to be check for a synchronous sampling
/// method.</typeparam>
template<class TType>
using _sync_sample = decltype(std::declval<TType &>().sample(
    std::declval<sensor_array_callback>(),
    std::declval<void *>()));

/// <summary>
/// Detects whether <typeparamref name="TType" /> uses asynchronous
/// sampling.
/// </summary>
/// <typeparam name="TType">The type to be check for an asynchronous sampling
/// method.</typeparam>
template<class TType>
using has_async_sample = typename detector<_async_sample, void, TType>::type;

/// <summary>
/// Detects whether <typeparamref name="TType" /> uses synchronous sampling.
/// </summary>
/// <typeparam name="TType">The type to be check for a synchronous sampling
/// method.</typeparam>
template<class TType>
using has_sync_sample = typename detector<_sync_sample, void, TType>::type;

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_DETECT_SAMPLE_H) */
