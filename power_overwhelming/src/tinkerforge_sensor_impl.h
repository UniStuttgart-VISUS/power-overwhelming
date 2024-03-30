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
#include "power_overwhelming/timestamp.h"

#include "tinkerforge_scope.h"
#include "tinkerforge_time_translator.h"


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
        /// Utility for transforming bricklet times to timestamps
        /// </summary>
        tinkerforge_time_translator time_xlate;
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
        /// Answer whether the code has access to the internal timer of the
        /// bricklet.
        /// </summary>
        /// <returns></returns>
#if defined(CUSTOM_TINKERFORGE_FIRMWARE)
        inline bool has_internal_time(void) const noexcept {
            return this->time_xlate;
        }
#else /* defined(CUSTOM_TINKERFORGE_FIRMWARE) */
        inline constexpr bool has_internal_time(void) const noexcept {
            return false;
        }
#endif /* defined(CUSTOM_TINKERFORGE_FIRMWARE) */

        /// <summary>
        /// If <see cref="on_measurement" /> is set, invoke the callback with
        /// the data stored in <see cref="async_data" />.
        /// </summary>
        /// <remarks>The caller must hold <see cref="async_lock" />.</remarks>
        /// <param name="timestamp"></param>
        void invoke_callback(const power_overwhelming::timestamp timestamp);

    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
