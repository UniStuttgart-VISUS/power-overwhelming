// <copyright file="sensor_utilities.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_SENSOR_UTILITIES_H)
#define _PWROWG_SENSOR_UTILITIES_H
#pragma once

#include <algorithm>
#include <chrono>
#include <memory>
#include <vector>

#include <nlohmann/json.hpp>

#include "visus/pwrowg/convert_string.h"
#include "visus/pwrowg/sensor_array.h"
#include "visus/pwrowg/sensor_description.h"

#include "sensor_state.h"
#include "string_functions.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Get all serialised sensor descriptions for sensors on the current
/// machine.
/// </summary>
/// <param name="sensors">The sensor array to get the descriptors from.</param>
/// <returns>A JSON array holding all the descriptors.</returns>
nlohmann::json PWROWG_TEST_API get_all_sensor_descs(
    _In_ const sensor_array& sensors);


/// <summary>
/// Retrieves the sampling interval from the given array configuration.
/// </summary>
/// <param name="config">The configuration to retrieve the sampling interval
/// from.</param>
/// <returns>The sampling interval.</returns>
std::chrono::milliseconds PWROWG_TEST_API get_sampling_interval(
    _In_ const sensor_array_configuration_impl& config) noexcept;

/// <summary>
/// Retrieves the sampling interval from the given sensor array.
/// </summary>
/// <param name="sensors">The sensor array to get the sampling interval from.
/// </param>
/// <returns>The sampling interval.</returns>
/// <exception cref="std::invalid_argument">If the sensor array does not hold a
/// valid configuration.</exception>
std::chrono::milliseconds PWROWG_TEST_API get_sampling_interval(
    _In_ const sensor_array_impl& sensors);

/// <summary>
/// Move the sensors in <see cref="begin" /> to <see cref="end" /> that match
/// <paramref name="predicate" /> to the front of the range.
/// </summary>
/// <remarks>
/// The relative order of the elements matching the predicate is not changed,
/// however the elements not matching the predicate may be reordered by the
/// operation.
/// </remarks>
/// <typeparam name="TIterator"></typeparam>
/// <typeparam name="TPredicate"></typeparam>
/// <param name="begin"></param>
/// <param name="end"></param>
/// <param name="predicate"></param>
/// <returns></returns>
template<class TIterator, class TPredicate>
TIterator move_front_if(_In_ const TIterator begin, _In_ const TIterator end,
    _In_ const TPredicate predicate);

///// <summary>
///// Parse sensor instances from a JSON-based configuration.
///// </summary>
///// <param name="descs"></param>
///// <returns></returns>
//std::vector<std::unique_ptr<sensor>> parse_sensors(
//    _In_ const nlohmann::json& descs);

/// <summary>
/// Mask the power, voltage and current bits of the sensor type in
/// <paramref name="desc" />.
/// </summary>
/// <param name="desc">A sensor description to get the sensor type from.</param>
/// <returns>A mask containing whether the sensor provides power, voltage or
/// current.</returns>
sensor_type PWROWG_TEST_API pwr_volt_cur_mask(
    _In_ const sensor_description& desc);

/// <summary>
/// Read a JSON configuration file.
/// </summary>
/// <param name="path">The path to the JSON file.</param>
/// <returns>The contents of the JSON file.</returns>
nlohmann::json PWROWG_TEST_API read_json(_In_z_ const char *path);

/// <summary>
/// Read a JSON configuration file.
/// </summary>
/// <param name="path">The path to the JSON file.</param>
/// <returns>The contents of the JSON file.</returns>
nlohmann::json PWROWG_TEST_API read_json(_In_z_ const wchar_t *path);

/// <summary>
/// Sort the given range of <see cref="sensor_description" />s according to
/// their path.
/// </summary>
/// <typeparam name="TIterator"></typeparam>
/// <param name="begin"></param>
/// <param name="end"></param>
template<class TIterator>
inline void sort_by_path(_In_ TIterator begin, _In_ TIterator end) {
    std::stable_sort(
        begin,
        end,
        [](const sensor_description& lhs, const sensor_description& rhs) {
            return (compare(lhs.path(), rhs.path()) < 0);
        });
}

PWROWG_DETAIL_NAMESPACE_END

#include "sensor_utilities.inl"

#endif /* !defined(_PWROWG_SENSOR_UTILITIES_H) */
