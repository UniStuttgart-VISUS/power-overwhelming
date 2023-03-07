// <copyright file="dump_sensors.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/dump_sensors.h"

#include "sensor_utilities.h"


/*
 * visus::power_overwhelming::dump_sensors
 */
std::size_t visus::power_overwhelming::dump_sensors(const char *path) {
    const auto descs = detail::get_all_sensor_descs();
    detail::write_json(path, descs);
    return descs.size();
}


/*
 * visus::power_overwhelming::dump_sensors
 */
std::size_t visus::power_overwhelming::dump_sensors(const wchar_t *path) {
    const auto descs = detail::get_all_sensor_descs();
    detail::write_json(path, descs);
    return descs.size();
}
