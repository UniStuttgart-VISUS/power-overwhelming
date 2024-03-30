// <copyright file="sensor_utilities.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 - 2023 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <memory>
#include <vector>

#include <nlohmann/json.hpp>

#include "power_overwhelming/convert_string.h"
#include "power_overwhelming/sensor.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// Get all serialised sensor descriptions for sensors on the current
    /// machine.
    /// </summary>
    /// <returns>A JSON array holding all the descriptors.</returns>
    nlohmann::json get_all_sensor_descs(void);

    /// <summary>
    /// Gets all sensors available on the current machine.
    /// </summary>
    /// <returns>A list of all sensors we know on this system.</returns>
    extern std::vector<std::unique_ptr<sensor>> get_all_sensors(void);

    /// <summary>
    /// Gets all sensors of the specified type.
    /// </summary>
    /// <typeparam name="TSensor">The type of the sensor to retrieve, which must
    /// have the standard static <c>for_all</c> method for retrieval.</typeparam>
    /// <returns>A list of all sensors of the specified type, which are
    /// available on the system.</returns>
    template<class TSensor> inline std::vector<TSensor> get_all_sensors_of(void) {
        std::vector<TSensor> retval;
        retval.resize(TSensor::for_all(nullptr, 0));
        TSensor::for_all(retval.data(), retval.size());
        return retval;
    }

    /// <summary>
    /// Move the given sensor to the given polymorphic sensor list
    /// <paramref name="dst" />.
    /// </summary>
    /// <typeparam name="TSensor"></typeparam>
    /// <param name="dst"></param>
    /// <param name="sensor"></param>
    /// <returns></returns>
    template<class TSensor>
    inline std::vector<std::unique_ptr<sensor>>& move_sensor(
            std::vector<std::unique_ptr<sensor>>& dst,
            TSensor&& sensor) {
        dst.emplace_back(new TSensor(std::move(sensor)));
        return dst;
    }

    /// <summary>
    /// Adds the given list of sensors to the polymorphic sensor list
    /// <paramref name="dst" />.
    /// </summary>
    /// <typeparam name="TSensor"></typeparam>
    /// <param name="dst"></param>
    /// <param name="sensors"></param>
    /// <returns><paramref name="dst" /></returns>
    template<class TSensor>
    inline std::vector<std::unique_ptr<sensor>>& move_sensors(
            std::vector<std::unique_ptr<sensor>>& dst,
            std::vector<TSensor>&& sensors) {
        dst.reserve(dst.size() + sensors.size());

        for (auto& s : sensors) {
            dst.emplace_back(new TSensor(std::move(s)));
        }

        return dst;
    }

    /// <summary>
    /// Parse sensor instances from a JSON-based configuration.
    /// </summary>
    /// <param name="descs"></param>
    /// <returns></returns>
    std::vector<std::unique_ptr<sensor>> parse_sensors(
        const nlohmann::json &descs);

    /// <summary>
    /// Read a JSON configuration file.
    /// </summary>
    /// <param name="path">The path to the JSON file.</param>
    /// <returns>The contents of the JSON file.</returns>
    nlohmann::json read_json(const char *path);

    /// <summary>
    /// Read a JSON configuration file.
    /// </summary>
    /// <param name="path">The path to the JSON file.</param>
    /// <returns>The contents of the JSON file.</returns>
    nlohmann::json read_json(const wchar_t *path);

    /// <summary>
    /// Write JSON configuration to a file.
    /// </summary>
    /// <param name="path">The path to the JSON file.</param>
    /// <param name="json">The JSON content to write</param>
    void write_json(const char *path, const nlohmann::json& json);

    /// <summary>
    /// Write JSON configuration to a file.
    /// </summary>
    /// <param name="path">The path to the JSON file.</param>
    /// <param name="json">The JSON content to write</param>
    void write_json(const wchar_t *path, const nlohmann::json& json);

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
