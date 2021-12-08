// <copyright file="tinkerforge_sensor_impl.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <array>
#include <atomic>
#include <functional>

#include <bricklet_voltage_current_v2.h>
#include <Windows.h>

#include "measurement.h"
#include "tinkerforge_scope.h"
#include "triple_buffering.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// Holds the implementation details of the Tinkerforge sensor.
    /// </summary>
    struct tinkerforge_sensor_impl final {

        /// <summary>
        /// The callback to be invoked for incoming asynchronous current
        /// readings.
        /// </summary>
        /// <param name="current"></param>
        /// <param name="data"></param>
        static void CALLBACK current_callback(const std::int32_t current,
            void *data);

        /// <summary>
        /// The callback to be invoked for incoming asynchronous power
        /// readings.
        /// </summary>
        /// <param name="power"></param>
        /// <param name="data"></param>
        static void CALLBACK power_callback(const std::int32_t power,
            void *data);

        /// <summary>
        /// The callback to be invoked for incoming asynchronous voltage
        /// readings.
        /// </summary>
        /// <param name="power"></param>
        /// <param name="data"></param>
        static void CALLBACK voltage_callback(const std::int32_t voltage,
            void *data);

        /// <summary>
        /// The handle for a voltage/current bricklet.
        /// </summary>
        VoltageCurrentV2 bricklet;

        /// <summary>
        /// Triple buffer for asynchronously arriving current readings.
        /// </summary>
        std::array<std::int32_t, 3> current_buffer;

        /// <summary>
        /// Tracks the state of the triple buffer <see cref="current_buffer" />.
        /// </summary>
        triple_buffer_state current_state;

        /// <summary>
        /// A user-defined description of what the sensor is actually measuring.
        /// </summary>
        std::wstring description;

        /// <summary>
        /// A callback to be invoked if a <see cref="measurement" /> is received
        /// asynchronously.
        /// </summary>
        std::atomic<measurement_callback> on_measurement;

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

        /// <summary>
        /// Disable all three callbacks of <see cref="bricklet" />.
        /// </summary>
        /// <exception cref="tinkerforge_exception"></exception>
        void disable_callbacks(void);

        /// <summary>
        /// Enable all three callbacks with <see cref="bricklet" />.
        /// </summary>
        /// <remarks>
        /// This method will set the callbacks defined in this class on the
        /// bricklet and start sampling it with the specified period (in
        /// milliseconds).
        /// </remarks>
        /// <param name="period"></param>
        /// <exception cref="tinkerforge_exception"></exception>
        void enable_callbacks(const std::int32_t period = 1);
    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
