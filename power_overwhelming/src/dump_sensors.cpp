// <copyright file="dump_sensors.cpp" company="Visualisierungsinstitut der Universit�t Stuttgart">
// Copyright � 2023 Visualisierungsinstitut der Universit�t Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph M�ller</author>

#include "power_overwhelming/dump_sensors.h"

#include "sensor_utilities.h"


/*
 * visus::power_overwhelming::dump_sensors
 */
void visus::power_overwhelming::dump_sensors(const char *path) {
    detail::write_json(path, detail::get_all_sensor_descs());
}


/*
 * visus::power_overwhelming::dump_sensors
 */
void visus::power_overwhelming::dump_sensors(const wchar_t *path) {
    detail::write_json(path, detail::get_all_sensor_descs());
}
