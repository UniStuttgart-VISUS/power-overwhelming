// <copyright file="sensor_filters.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_SENSOR_FILTERS_H)
#define _PWROWG_SENSOR_FILTERS_H
#pragma once

#include "visus/pwrowg/sensor_description.h"


PWROWG_NAMESPACE_BEGIN

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
