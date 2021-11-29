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

        /// <summary>
        /// The handle for a voltage/current bricklet.
        /// </summary>
        VoltageCurrentV2 bricklet;

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
