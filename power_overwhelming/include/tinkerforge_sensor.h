// <copyright file="tinkerforge_sensor.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "measurement.h"
#include "tinkerforge_sensor_definiton.h"


namespace visus {
namespace power_overwhelming {

    /* Forward declarations. */
    namespace detail { struct tinkerforge_sensor_impl; }

    /// <summary>
    /// A power sensor based on the Tinkerforge current/voltage bricklet v2.
    /// </summary>
    class POWER_OVERWHELMING_API tinkerforge_sensor final {

    public:

        /// <summary>
        /// The default host on which brickd is assumed to run.
        /// </summary>
        static constexpr const char *default_host = "localhost";

        /// <summary>
        /// The default port on which brickd is assumed to listen on.
        /// </summary>
        static constexpr const std::uint16_t default_port = 4223;

        /// <summary>
        /// Retrieve sensor definitions for all bricklets attacted to the
        /// specified host.
        /// </summary>
        /// <param name="outSensors">Receives the sensor definitions. If
        /// <c>nullptr</c>, the sensors will only be counted.</param>
        /// <param name="cntSensors">Size of <paramref name="outSensors" />
        /// in elements.</param>
        /// <param name="host">The host on which the Brick daemon is running.
        /// This parameter defaults to &quot;localhost&quot;.</param>
        /// <param name="port">The port on which the Brick daemon is listening.
        /// This parameter defaults to 4223.</param>
        /// <returns>The number of current/voltage bricklets available,
        /// regardless of how many have been copied.</returns>
        static std::size_t get_sensors(tinkerforge_sensor_definiton *outSensors,
            const std::size_t cntSensors, const char *host = default_host,
            const std::uint16_t port = default_port);

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="uid">The unique identifier of the voltage/current
        /// bricklet addressed by the sensor.</param>
        /// <param name="host">The host on which the Brick daemon is running.
        /// This parameter defaults to &quot;localhost&quot;.</param>
        /// <param name="port">The port on which the Brick daemon is listening.
        /// This parameter defaults to 4223.</param>
        /// <exception cref="std::invalid_argument">If <paramref name="uid" />
        /// is <c>nullptr</c>.</exceptions>
        /// <exception cref="std::bad_alloc">If the required resources could not
        /// be allocated.</exceptions>
        /// <exception cref="tinkerforge_exception">If the connection to the
        /// master brick could not be established.</exception>
        tinkerforge_sensor(const char *uid, const char *host = default_host,
            const std::uint16_t port = default_port);

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="uid">The unique identifier of the voltage/current
        /// bricklet addressed by the sensor.</param>
        /// <param name="description">A user-defined description that allows you
        /// to track what this sensor is measuring. It is safe to pass
        /// <c>nullptr</c>, in which case no description will be set.</param>
        /// <param name="host">The host on which the Brick daemon is running.
        /// This parameter defaults to &quot;localhost&quot;.</param>
        /// <param name="port">The port on which the Brick daemon is listening.
        /// This parameter defaults to 4223.</param>
        /// <exception cref="std::invalid_argument">If <paramref name="uid" />
        /// is <c>nullptr</c>.</exceptions>
        /// <exception cref="std::bad_alloc">If the required resources could not
        /// be allocated.</exceptions>
        /// <exception cref="tinkerforge_exception">If the connection to the
        /// master brick could not be established.</exception>
        tinkerforge_sensor(const char *uid, const wchar_t *description,
            const char *host = default_host,
            const std::uint16_t port = default_port);

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="definition">The definition of the bricklet to create
        /// the sensor for</param>
        /// <param name="host">The host on which the Brick daemon is running.
        /// This parameter defaults to &quot;localhost&quot;.</param>
        /// <param name="port">The port on which the Brick daemon is listening.
        /// This parameter defaults to 4223.</param>
        /// <exception cref="std::invalid_argument">If the UID in
        /// <paramref name="definition" /> is invalid.</exceptions>
        /// <exception cref="std::bad_alloc">If the required resources could not
        /// be allocated.</exceptions>
        /// <exception cref="tinkerforge_exception">If the connection to the
        /// master brick could not be established.</exception>
        tinkerforge_sensor(const tinkerforge_sensor_definiton& definition,
            const char *host = default_host,
            const std::uint16_t port = default_port);

        /// <summary>
        /// Move <paramref name="rhs" /> into a new instance.
        /// </summary>
        /// <param name="rhs">The object to be moved.</param>
        inline tinkerforge_sensor(tinkerforge_sensor && rhs) noexcept
                : _impl(rhs._impl) {
            rhs._impl = nullptr;
        }

        /// <summary>
        /// Finalises the instance.
        /// </summary>
        ~tinkerforge_sensor(void);

        /// <summary>
        /// The user-defined description of what the sensor is measuring.
        /// </summary>
        /// <returns>The description of what the sensor is measuring.</returns>
        const wchar_t *description(void) const noexcept;

        /// <summary>
        /// Gets the name of the sensor.
        /// </summary>
        /// <returns>The implementation-defined, human-readable name of the
        /// sensor.</returns>
        const wchar_t *name(void) const noexcept;

        /// <summary>
        /// Move assignment.
        /// </summary>
        /// <param name="rhs">The right-hand side operand</param>
        /// <returns><c>*this</c></returns>
        tinkerforge_sensor& operator =(tinkerforge_sensor&& rhs) noexcept;

        /// <summary>
        /// Determines whether the sensor is valid.
        /// </summary>
        /// <remarks>
        /// A sensor is considered valid until it has been disposed by a move
        /// operation.
        /// </remarks>
        /// <returns><c>true</c> if the sensor is valid, <c>false</c>
        /// otherwise.</returns>
        operator bool(void) const noexcept;

    private:

        detail::tinkerforge_sensor_impl *_impl;
    };

} /* namespace power_overwhelming */
} /* namespace visus */
