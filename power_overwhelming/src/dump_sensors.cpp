// <copyright file="dump_sensors.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/dump_sensors.h"

#include "sensor_utilities.h"


/*
 * visus::power_overwhelming::dump_sensors
 */
std::size_t visus::power_overwhelming::dump_sensors(_In_z_ const char *path) {
    const auto descs = detail::get_all_sensor_descs();
    detail::write_json(path, descs);
    return descs.size();
}


/*
 * visus::power_overwhelming::dump_sensors
 */
std::size_t visus::power_overwhelming::dump_sensors(
        _In_z_ const wchar_t *path) {
    const auto descs = detail::get_all_sensor_descs();
    detail::write_json(path, descs);
    return descs.size();
}
