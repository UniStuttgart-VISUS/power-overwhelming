// <copyright file="sensor_filters.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_SENSOR_FILTERS_H)
#define _PWROWG_SENSOR_FILTERS_H
#pragma once

#include <algorithm>
#include <array>

#include "visus/pwrowg/sensor_description.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Answer whether the given <see cref="sensor_description" /> describes an
/// ADL-based sensor.
/// </summary>
/// <param name="desc">The sensor to check.</param>
/// <returns><c>true</c> if the sensor is ADL-based, <c>false</c> otherwise.
/// </returns>
extern POWER_OVERWHELMING_API bool is_adl_sensor(
    _In_ const sensor_description& desc) noexcept;

/// <summary>
/// Answer whether the given <see cref="sensor_description" /> fulfills all of
/// the given <paramref name="predicates" />.
/// </summary>
/// <typeparam name="TPredicates">The types of the predicates.</typeparam>
/// <param name="desc">The sensor to check.</param>
/// <param name="predicates">The list of predicates to check.</param>
/// <returns><c>true</c> if the given sensor fulfills all of the given
/// predicates, <c>false</c> otherwise.</returns>
template<class... TPredicates>
inline bool is_all_of(_In_ const sensor_description& desc,
        _In_ TPredicates... predicates) {
    static_assert(sizeof...(TPredicates) > 0, "At least one predicate must be "
        "provided.");
    std::array<bool, sizeof...(TPredicates)> results { predicates(desc)... };
    return (std::find(results.begin(), results.end(), false) == results.end());
}

/// <summary>
/// Answer whether the given <see cref="sensor_description" /> fulfills any of
/// the given <paramref name="predicates" />.
/// </summary>
/// <typeparam name="TPredicates">The types of the predicates.</typeparam>
/// <param name="desc">The sensor to check.</param>
/// <param name="predicates">The list of predicates to check.</param>
/// <returns><c>true</c> if the given sensor fulfills any of the given
/// predicates, <c>false</c> otherwise.</returns>
template<class... TPredicates>
inline bool is_any_of(_In_ const sensor_description& desc,
        _In_ TPredicates... predicates) {
    static_assert(sizeof...(TPredicates) > 0, "At least one predicate must be "
        "provided.");
    std::array<bool, sizeof...(TPredicates)> results { predicates(desc)... };
    return (std::find(results.begin(), results.end(), true) != results.end());
}

/// <summary>
/// Answer whether the given <see cref="sensor_description" /> describes a
/// sensor targetting the CPU.
/// </summary>
/// <param name="desc">The sensor to check.</param>
/// <returns><c>true</c> if the sensor is a CPU sensor, <c>false</c> otherwise.
/// </returns>
extern POWER_OVERWHELMING_API bool is_cpu_sensor(
    _In_ const sensor_description& desc) noexcept;

/// <summary>
/// Answer whether the given <see cref="sensor_description" /> describes a
/// sensor measuring current.
/// </summary>
/// <param name="desc">The sensor to check.</param>
/// <returns><c>true</c> if the sensor is a current sensor, <c>false</c>
/// otherwise.</returns>
extern POWER_OVERWHELMING_API bool is_current_sensor(
    _In_ const sensor_description& desc) noexcept;

/// <summary>
/// Answer whether the given <see cref="sensor_description" /> describes a
/// sensor measuring energy.
/// </summary>
/// <param name="desc">The sensor to check.</param>
/// <returns><c>true</c> if the sensor is a energy sensor, <c>false</c>
/// otherwise.</returns>
extern POWER_OVERWHELMING_API bool is_energy_sensor(
    _In_ const sensor_description& desc) noexcept;

/// <summary>
/// Answer whether the given <see cref="sensor_description" /> describes a
/// sensor targetting the GPU.
/// </summary>
/// <param name="desc">The sensor to check.</param>
/// <returns><c>true</c> if the sensor is a GPU sensor, <c>false</c> otherwise.
/// </returns>
extern POWER_OVERWHELMING_API bool is_gpu_sensor(
    _In_ const sensor_description& desc) noexcept;

/// <summary>
/// Answer whether the given <see cref="sensor_description" /> describes a
/// Rohde &amp; Schwarz HMC 8015 power analyser.
/// </summary>
/// <param name="desc">The sensor to check.</param>
/// <returns><c>true</c> if the sensor is a HMC 8015 sensor, <c>false</c>
/// otherwise.</returns>
extern POWER_OVERWHELMING_API bool is_hmc8015_sensor(
    _In_ const sensor_description &desc) noexcept;

/// <summary>
/// Answer whether the given <see cref="sensor_description" /> describes an
/// NVML-based sensor.
/// </summary>
/// <param name="desc">The sensor to check.</param>
/// <returns><c>true</c> if the sensor is NVML-based, <c>false</c> otherwise.
/// </returns>
extern POWER_OVERWHELMING_API bool is_nvml_sensor(
    _In_ const sensor_description& desc) noexcept;

/// <summary>
/// Answer whether the given <see cref="sensor_description" /> describes a
/// sensor measuring power.
/// </summary>
/// <param name="desc">The sensor to check.</param>
/// <returns><c>true</c> if the sensor is a power sensor, <c>false</c>
/// otherwise.</returns>
extern POWER_OVERWHELMING_API bool is_power_sensor(
    _In_ const sensor_description& desc) noexcept;

/// <summary>
/// Answer whether the given <see cref="sensor_description" /> describes a
/// Tinkerforge-based sensor.
/// </summary>
/// <param name="desc">The sensor to check.</param>
/// <returns><c>true</c> if the sensor is Tinkerforge-based, <c>false</c>
/// otherwise.
/// </returns>
extern POWER_OVERWHELMING_API bool is_tinkerforge_sensor(
    _In_ const sensor_description& desc) noexcept;

/// <summary>
/// Answer whether the given <see cref="sensor_description" /> describes a
/// sensor for USB power delivery measurement.
/// </summary>
/// <param name="desc">The sensor to check.</param>
/// <returns><c>true</c> if the sensor is USB PD sensor, <c>false</c>
/// otherwise.</returns>
extern POWER_OVERWHELMING_API bool is_usb_pd_sensor(
    _In_ const sensor_description& desc) noexcept;

/// <summary>
/// Answer whether the given <see cref="sensor_description" /> describes a
/// sensor measuring voltage.
/// </summary>
/// <param name="desc">The sensor to check.</param>
/// <returns><c>true</c> if the sensor is a voltage sensor, <c>false</c>
/// otherwise.</returns>
extern POWER_OVERWHELMING_API bool is_voltage_sensor(
    _In_ const sensor_description& desc) noexcept;

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_SENSOR_FILTERS_H) */
