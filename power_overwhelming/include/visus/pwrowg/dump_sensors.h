﻿// <copyright file="dump_sensors.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_DUMP_SENSORS_H)
#define _PWROWG_DUMP_SENSORS_H
#pragma once

#include <cstddef>
#include <string>

#include "visus/pwrowg/sensor_array.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Saves a JSON array of all sensors currently found on the the system.
/// </summary>
/// <param name="sensors">The sensor array to dump.</param>
/// <param name="path">The path of the file to write the sensor data to.
/// </param>
/// <returns>The number of sensors actually dumped.</returns>
/// <exception cref="std::ios_base::failure">If saving the sensor data
/// failed.</exception>
std::size_t POWER_OVERWHELMING_API dump_sensors(
    _In_ const sensor_array& sensors,
    _In_z_ const char *path);

/// <summary>
/// Saves a JSON array of all sensors currently found on the the system.
/// </summary>
/// <param name="sensors">The sensor array to dump.</param>
/// <param name="path">The path of the file to write the sensor data to.
/// </param>
/// <returns>The number of sensors actually dumped.</returns>
/// <exception cref="std::ios_base::failure">If saving the sensor data
/// failed.</exception>
std::size_t POWER_OVERWHELMING_API dump_sensors(
    _In_ const sensor_array& sensors,
    _In_z_ const wchar_t *path);

/// <summary>
/// Saves a JSON array of all sensors currently found on the the system.
/// </summary>
/// <param name="sensors">The sensor array to dump.</param>
/// <param name="path">The path of the file to write the sensor data to.
/// </param>
/// <returns>The number of sensors actually dumped.</returns>
/// <exception cref="std::ios_base::failure">If saving the sensor data
/// failed.</exception>
template<class TChar>
inline std::size_t dump_sensors(
        _In_ const sensor_array& sensors,
        _In_ const std::basic_string<TChar>& path) {
    return dump_sensors(sensors, path.c_str());
}

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_DUMP_SENSORS_H) */
