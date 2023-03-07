// <copyright file="dump_sensors.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "power_overwhelming/power_overwhelming_api.h"


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Saves a JSON array of all sensors currently found on the the system.
    /// </summary>
    /// <param name="path">The path of the file to write the sensor data to.
    /// </para>
    /// <exception cref="std::ios_base::failure">If saving the sensor data
    /// failed.</exception>
    void POWER_OVERWHELMING_API dump_sensors(const char *path);

    /// <summary>
    /// Saves a JSON array of all sensors currently found on the the system.
    /// </summary>
    /// <param name="path">The path of the file to write the sensor data to.
    /// </para>
    /// <exception cref="std::ios_base::failure">If saving the sensor data
    /// failed.</exception>
    void POWER_OVERWHELMING_API dump_sensors(const wchar_t *path);

} /* namespace power_overwhelming */
} /* namespace visus */
