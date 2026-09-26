// <copyright file="dump_sensors.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_DUMP_SENSORS_H)
#define _PWROWG_DUMP_SENSORS_H
#pragma once

#include <cstddef>
#include <string>
#include <vector>

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
/// <typeparam name="TChar">The character type used for the path.</typeparam>
/// <typeparam name="TTraits">The character traits.</typeparam>
/// <typeparam name="TAlloc">The string allocator.</typeparam>
/// <param name="sensors">The sensor array to dump.</param>
/// <param name="path">The path of the file to write the sensor data to.
/// </param>
/// <returns>The number of sensors actually dumped.</returns>
/// <exception cref="std::ios_base::failure">If saving the sensor data
/// failed.</exception>
template<class TChar, class TTraits, class TAlloc>
inline std::size_t dump_sensors(_In_ const sensor_array& sensors,
        _In_ const std::basic_string<TChar, TTraits, TAlloc>& path) {
    return dump_sensors(sensors, path.c_str());
}

/// <summary>
/// Restore sensor descriptions from a JSON file. Please note that these
/// descriptions are not usable for constructing a sensor array, but can only
/// be used for comparison of their publicly exposed properties.
/// </summary>
/// <param name="sensors">An array to receive at least <paramref name="cnt" />
/// sensor descriptions.</param>
/// <param name="cnt">The number of sensor descriptions the array
/// <paramref name="sensors" /> can hold.</param>
/// <param name="path">The path of the JSON file to read the sensor descriptions
/// from.</param>
/// <returns>The number of sensor descriptions in he JSON file, regardless of
/// how many have been written.</returns>
std::size_t POWER_OVERWHELMING_API restore_sensor_descriptions(
    _Out_writes_opt_(cnt) sensor_description *sensors,
    _In_ const std::size_t cnt,
    _In_z_ const wchar_t *path);

/// <summary>
/// Restore sensor descriptions from a JSON file. Please note that these
/// descriptions are not usable for constructing a sensor array, but can only
/// be used for comparison of their publicly exposed properties.
/// </summary>
/// <param name="sensors">An array to receive at least <paramref name="cnt" />
/// sensor descriptions.</param>
/// <param name="cnt">The number of sensor descriptions the array
/// <paramref name="sensors" /> can hold.</param>
/// <param name="path">The path of the JSON file to read the sensor descriptions
/// from.</param>
/// <returns>The number of sensor descriptions in he JSON file, regardless of
/// how many have been written.</returns>
std::size_t POWER_OVERWHELMING_API restore_sensor_descriptions(
    _Out_writes_opt_(cnt) sensor_description *sensors,
    _In_ const std::size_t cnt,
    _In_z_ const char *path);

/// <summary>
/// Restore sensor descriptions from a JSON file. Please note that these
/// descriptions are not usable for constructing a sensor array, but can only
/// be used for comparison of their publicly exposed properties.
/// </summary>
/// <typeparam name="TChar">The character type used for the path.</typeparam>
/// <param name="path">The path of the JSON file to read the sensor descriptions
/// from.</param>
/// <returns>The sensor descriptions persisted in the file.</returns>
template<class TChar>
inline std::vector<sensor_description> restore_sensor_descriptions(
        _In_z_ const TChar *path) {
    std::vector<sensor_description> retval(restore_sensor_descriptions(
        nullptr, 0, path));
    restore_sensor_descriptions(retval.data(), retval.size(), path);
    return retval;
}

/// <summary>
/// Restore sensor descriptions from a JSON file. Please note that these
/// descriptions are not usable for constructing a sensor array, but can only
/// be used for comparison of their publicly exposed properties.
/// </summary>
/// <typeparam name="TChar">The character type used for the path.</typeparam>
/// <typeparam name="TTraits">The character traits.</typeparam>
/// <typeparam name="TAlloc">The string allocator.</typeparam>
/// <param name="path">The path of the JSON file to read the sensor descriptions
/// from.</param>
/// <returns>The sensor descriptions persisted in the file.</returns>
template<class TChar, class TTraits, class TAlloc>
inline std::vector<sensor_description> restore_sensor_descriptions(
        _In_ const std::basic_string<TChar, TTraits, TAlloc>& path) {
    return restore_sensor_descriptions(path.c_str());
}


PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_DUMP_SENSORS_H) */
