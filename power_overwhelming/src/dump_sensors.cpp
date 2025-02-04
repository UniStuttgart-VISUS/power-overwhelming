// <copyright file="dump_sensors.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/dump_sensors.h"

#include "sensor_utilities.h"


/*
 * PWROWG_NAMESPACE::dump_sensors
 */
std::size_t PWROWG_NAMESPACE::dump_sensors(_In_z_ const char *path) {
    throw "TODO";
    //const auto descs = detail::get_all_sensor_descs();
    //detail::write_json(path, descs);
    //return descs.size();
}


/*
 * PWROWG_NAMESPACE::dump_sensors
 */
std::size_t PWROWG_NAMESPACE::dump_sensors(
        _In_z_ const wchar_t *path) {
    throw "TODO";
    //const auto descs = detail::get_all_sensor_descs();
    //detail::write_json(path, descs);
    //return descs.size();
}
