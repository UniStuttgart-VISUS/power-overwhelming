// <copyright file="tinkerforge_sensor.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "measurement.h"
#include "timestamp_resolution.h"
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
        /// <remarks>
        /// <para>Tinkerforge bricklets are discovered asynchronously via
        /// a network protocol. Therefore, it might take some time to find
        /// all of them and it is impossible to know for sure whether the
        /// currently know set of bricklets is the actual ones. However,
        /// the library keeps a list of already discovered bricklets, which
        /// is updated in background and returned if it is non-empty. Otherwise,
        /// ie in case of an empty list, the method waits for at most
        /// <paramref name="timeout" /> milliseconds for the bricklets to
        /// appear.</para>
        /// <para>Due to the asynchronous detection of bricklets and the fact
        /// that bricklets are fully hot-plug capable and therefore can also
        /// be removed at any time, the method might return spurious numbers
        /// of bricklets which need to be handled by the caller. It is
        /// absolutely mandatory to check the return value! If the return
        /// value is larger than <paramref name="cnt_definitions" />, the caller
        /// should increase the buffer size and call the method again. If the
        /// returned number of brickles is smaller than
        /// <paramref name="cnt_definitions" />, the remaining elements in
        /// the output array are invalid and must not be used. Spurious return
        /// values can even occur when using the pattern of calling the method
        /// with <c>nullptr</c> for <paramref name="out_definitions" /> to
        /// count the required space, allocating this space and then calling
        /// it again. This is due to the cached bricklets only being locked
        /// when inside the method, not between calls.</para>
        /// <para>Callers should try to avoid specifying larger numbers
        /// for <paramref name="cnt_definitions" /> than the actually available
        /// number of current/voltage bricklets, because the method assumes
        /// that this is the epected number and waits until the timeout if
        /// less bricklets than this number are actually connected. A reasonable
        /// pattern is determining the number of current/voltage bricklets by
        /// calling the method without an output buffer, the expected number
        /// as <paramre name="cnt_definitions" /> and a fairly large timeout
        /// to give the method time to actually discover all of the expected
        /// bricklets. Callers should then allocate the required output buffer
        /// and call the method again with a small timeout.</para>
        /// </remarks>
        /// <param name="out_definitions">Receives the sensor definitions. If
        /// <c>nullptr</c>, the sensors will only be counted.</param>
        /// <param name="cnt_definitions">Size of
        /// <paramref name="out_definitions" /> in elements. It is safe to pass
        /// any number if <paramref name="out_definitions" /> is <c>nullptr</c>.
        /// In this case, the number is interpreted as the expected number of
        /// bricklets to wait for.</param>
        /// <param name="timeout">The number of milliseconds to wait for the
        /// bricklets to connect if none are cached. This value defaults to
        /// 1000.</param>
        /// <param name="host">The host on which the Brick daemon is running.
        /// This parameter defaults to &quot;localhost&quot;.</param>
        /// <param name="port">The port on which the Brick daemon is listening.
        /// This parameter defaults to 4223.</param>
        /// <returns>The number of current/voltage bricklets available,
        /// regardless of how many have been copied.</returns>
        static std::size_t get_definitions(
            tinkerforge_sensor_definiton *out_definitions,
            const std::size_t cnt_definitions, const std::size_t timeout = 1000,
            const char *host = default_host,
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
        /// Sample the sensor.
        /// </summary>
        /// <param name="resolution">The temporal resolution of the timestamp
        /// to be returned.</param>
        /// <returns>A sensor sample with the information about power
        /// consumption that is available via Tinkerforge bricklets.</returns>
        /// <exception cref="std::invalid_argument">If
        /// <paramref name="resolution" /> does not designate a valid resolution
        /// for timestamps.</exception>
        /// <exception cref="std::runtime_error">If a sensor that has been moved
        /// is sampled.</exception
        /// <exception cref="tinkerforge_exception">If the sensor could not be
        /// sampled. </exception>
        measurement sample(const timestamp_resolution resolution) const;

        /// <summary>
        /// Sample the sensor using a timestamp with millisecond resolution.
        /// </summary>
        /// <returns>A sensor sample with the information about power
        /// consumption that is available via Tinkerforge bricklets.</returns>
        /// <exception cref="std::runtime_error">If a sensor that has been moved
        /// is sampled.</exception>
        /// <exception cref="tinkerforge_exception">If the sensor could not be
        /// sampled. </exception>
        inline measurement sample(void) const {
            return this->sample(timestamp_resolution::milliseconds);
        }

        /// <summary>
        /// Asynchronously sample the sensor every
        /// <paramref name="sampling_period "/> milliseconds.
        /// </summary>
        /// <param name="on_measurement">The callback to be invoked if new data
        /// arrived. If this is <c>nullptr</c>, the asynchronous sampling will
        /// be disabled. Only one callback can be registered, subsequent calls
        /// will fail.</param>
        /// <param name="sampling_period">The desired sampling period in
        /// milliseconds. This parameter defaults to 1.</param>
        /// <exception cref="std::runtime_error">If the sensor has been moved.
        /// </exception>
        /// <exception cref="std::logic_error">If the sensor is already being
        /// sampled asynchronously due to a previous call to the method.
        /// </exception>
        /// <exception cref="tinkerforge_exception">If the sensor could not be
        /// sampled. </exception>
        void sample(const measurement_callback on_measurement,
            const std::int32_t sampling_period = 1);

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
