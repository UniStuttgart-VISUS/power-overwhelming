// <copyright file="sensor_utilities.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "sensor_utilities.h"

#include <cassert>

#include "power_overwhelming/adl_sensor.h"
#include "power_overwhelming/hmc8015_sensor.h"
#include "power_overwhelming/nvml_sensor.h"
#include "power_overwhelming/rtb_sensor.h"
#include "power_overwhelming/tinkerforge_sensor.h"


/*
 * visus::power_overwhelming::detail::get_all_sensors
 */
std::vector<std::unique_ptr<visus::power_overwhelming::sensor>>
visus::power_overwhelming::detail::get_all_sensors(void) {
    std::vector<std::unique_ptr<sensor>> retval;

    // Get all ADL sensors.
    try {
        move_sensors(retval, get_all_sensors_of<adl_sensor>());
    } catch (...) { /* Just ignore the sensor. */ }

    // Get all R&S HMC8015 sensors.
    try {
        move_sensors(retval, get_all_sensors_of<hmc8015_sensor>());
    } catch (...) { /* Just ignore the sensor. */ }

    // Get all NVML sensors.
    try {
        move_sensors(retval, get_all_sensors_of<nvml_sensor>());
    } catch (...) { /* Just ignore the sensor. */ }

    // Get all R&S RTBxxxx sensors.
    try {
        move_sensors(retval, get_all_sensors_of<rtb_sensor>());
    } catch (...) { /* Just ignore the sensor. */ }

    // Get all Tinkerforge sensors.
    try {
        std::vector<tinkerforge_sensor_definiton> descs;
        descs.resize(tinkerforge_sensor::get_definitions(nullptr, 0));
        auto cnt = tinkerforge_sensor::get_definitions(descs.data(),
            descs.size());

        const auto host = tinkerforge_sensor::default_host;
        const auto port = tinkerforge_sensor::default_port;

        retval.reserve(retval.size() + descs.size());

        for (auto &d : descs) {
            assert(d.uid() != nullptr);
            retval.emplace_back(new tinkerforge_sensor(d));
        }
    } catch (...) { /* Just ignore the sensor. */ }

    return retval;
}
