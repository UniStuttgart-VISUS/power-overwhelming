// <copyright file="tinkerforge_sensor_impl.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <array>
#include <mutex>
#include <functional>

#include <bricklet_voltage_current_v2.h>

#if defined(_WIN32)
#include <Windows.h>
#endif /* defined(_WIN32) */

#include "power_overwhelming/async_sampling.h"
#include "power_overwhelming/measurement.h"

#include "timestamp.h"
#include "tinkerforge_scope.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// Holds the implementation details of the Tinkerforge sensor.
    /// </summary>
    struct tinkerforge_sensor_impl final {

        /// <summary>
        /// Compose the sensor name from the given connection information.
        /// </summary>
        /// <param name="host"></param>
        /// <param name="port"></param>
        /// <param name="uid"></param>
        /// <returns></returns>
        static std::string get_sensor_name(const std::string& host,
            const std::uint16_t port, const std::string& uid);

        /// <summary>
        /// The handle for a voltage/current bricklet.
        /// </summary>
        VoltageCurrentV2 bricklet;

        /// <summary>
        /// Buffer for incoming asynchronous data (current, power, voltage, in
        /// that order).
        /// </summary>
        std::array<measurement::value_type, 3> async_data;

        /// <summary>
        /// A lock for protecting <see cref="async_data" /> and the callback
        /// configuration.
        /// </summary>
        std::mutex async_lock;

        /// <summary>
        /// The asynchronous sampling configuration for the sensor.
        /// </summary>
        async_sampling async_sampling;

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

#if defined(CUSTOM_TINKERFORGE_FIRMWARE)
        /// <summary>
        /// The offset of the system clock (in milliseconds) from the zero-point
        /// of the time reported by the bricklet with Moritz' custom firmware.
        /// This information is used to compute wall-clock times from hardware
        /// timestamps and needs to be calibrated on startup.
        /// </summary>
        timestamp_type time_offset;
#endif /* defined(CUSTOM_TINKERFORGE_FIRMWARE) */

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

        /// <summary>
        /// Enable the current callback with <see cref="bricklet" />.
        /// </summary>
        /// <param name="period"></param>
        /// <exception cref="tinkerforge_exception"></exception>
        void enable_current_callback(const std::int32_t period = 1);

        /// <summary>
        /// Enable the power callback with <see cref="bricklet" />.
        /// </summary>
        /// <param name="period"></param>
        /// <exception cref="tinkerforge_exception"></exception>
        void enable_power_callback(const std::int32_t period = 1);

        /// <summary>
        /// Enable the voltage callback with <see cref="bricklet" />.
        /// </summary>
        /// <param name="period"></param>
        /// <exception cref="tinkerforge_exception"></exception>
        void enable_voltage_callback(const std::int32_t period = 1);

        /// <summary>
        /// If <see cref="on_measurement" /> is set, invoke the callback with
        /// the data stored in <see cref="async_data" />.
        /// </summary>
        /// <remarks>The caller must hold <see cref="async_lock" />.</remarks>
        /// <param name="timestamp"></param>
        void invoke_callback(const timestamp_type timestamp);

        /// <summary>
        /// Find out whether the bricklet has our customised firmware, and if
        /// so, determine the <see cref="time_offset" /> for it.
        /// </summary>
        /// <remarks>
        /// This method has no effect unless <c>CUSTOM_TINKERFORGE_FIRMWARE</c>
        /// is defined and has a positive, non-zero value.
        /// </remarks>
        /// <param name="iterations"></param>
        /// <returns></returns>
        bool init_time_offset(const std::size_t iterations = 4);
    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
