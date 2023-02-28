// <copyright file="sensor_utilities.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <memory>
#include <vector>

#include "power_overwhelming/sensor.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

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

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
