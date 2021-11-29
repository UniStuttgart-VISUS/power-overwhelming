// <copyright file="tinkerforge_sensor_impl.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <bricklet_voltage_current_v2.h>

#include "tinkerforge_scope.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// Holds the implementation details of the Tinkerforge sensor.
    /// </summary>
    struct tinkerforge_sensor_impl final {

        //cb_enumerate(const char *uid, const char *connected_uid,
        //    char position, uint8_t hardware_version[3],
        //    uint8_t firmware_version[3], uint16_t device_identifier,
        //    uint8_t enumeration_type, void *user_data)

        /// <summary>
        /// The handle for a voltage/current bricklet.
        /// </summary>
        VoltageCurrentV2 bricklet;

        /// <summary>
        /// A user-defined description of what the sensor is actually measuring.
        /// </summary>
        std::wstring description;

        /// <summary>
        /// The name of the sensor, which has been created from the host,
        /// port and unique ID of the bricklet.
        /// </summary>
        std::wstring sensor_name;

        /// <summary>
        /// The scope keeping the connection alive while the sensor is still in
        /// use.
        /// </summary>
        tinkerforge_scope scope;

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="host"></param>
        /// <param name="port"></param>
        /// <param name="uid"></param>
        tinkerforge_sensor_impl(const std::string& host,
            const std::uint16_t port, const char *uid);

        /// <summary>
        /// Finalises the instance.
        /// </summary>
        ~tinkerforge_sensor_impl(void);
    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
