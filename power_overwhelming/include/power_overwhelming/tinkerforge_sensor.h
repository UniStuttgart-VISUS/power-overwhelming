// <copyright file="tinkerforge_sensor.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "power_overwhelming/conversion_time.h"
#include "power_overwhelming/sample_averaging.h"
#include "power_overwhelming/sensor.h"
#include "power_overwhelming/tinkerforge_sensor_definiton.h"
#include "power_overwhelming/tinkerforge_sensor_source.h"


namespace visus {
namespace power_overwhelming {

    /* Forward declarations. */
    namespace detail { struct tinkerforge_sensor_impl; }

    /// <summary>
    /// A power sensor based on the Tinkerforge current/voltage bricklet v2.
    /// </summary>
    class POWER_OVERWHELMING_API tinkerforge_sensor final : public sensor {

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
        /// The default source to sample.
        /// </summary>
        static constexpr const tinkerforge_sensor_source default_source
            = tinkerforge_sensor_source::all;

        /// <summary>
        /// Create sensors for all Tinkerforge bricklets attached to the
        /// <see cref="host" /> on <see cref="port" />.
        /// </summary>
        /// <remarks>
        /// <para>This method is a utility method that retrieves all sensor
        /// definition from <see cref="tinkerforge_sensor::get_definitions" />
        /// and creates a sensor for all of them.</para>
        /// <para>The method handles the fact that sensors may be attached and
        /// detached at runtime by truncating the number of sensors actually
        /// created should this happen during the measuring call and the
        /// instantiation call to the method. Therefore, the number of sensors
        /// acually created may be smaller than the buffer provided even if the
        /// buffer has been measured before using the same method.</para>
        /// </remarks>
        /// <param name="out_sensors">Receives the sensors, if not
        /// <c>nullptr</c>.</param>
        /// <param name="cnt_sensors">The available space in
        /// <paramref name="out_sensors" />.</param>
        /// <param name="host">The host on which the Brick daemon is running.
        /// This parameter defaults to &quot;localhost&quot;.</param>
        /// <param name="port">The port on which the Brick daemon is listening.
        /// This parameter defaults to 4223.</param>
        /// <param name="timeout">The number of milliseconds to wait for the
        /// bricklets to connect if none are cached. This value defaults to
        /// 1000.</param>
        /// <returns>The number of sensors available on the system, regardless
        /// of the size of the output array. If this number is larger than
        /// <paramref name="cntSensors" />, not all sensors have been returned.
        /// </returns>
        /// <exception cref="std::bad_alloc">If the required resources could not
        /// be allocated.</exception>
        /// <exception cref="tinkerforge_exception">If the connection to the
        /// master brick could not be established.</exception>
        static std::size_t for_all(tinkerforge_sensor *out_sensors,
            const std::size_t cnt_sensors, const std::size_t timeout = 1000,
            const char *host = default_host,
            const std::uint16_t port = default_port);

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
        inline tinkerforge_sensor(void) : _impl(nullptr) { }

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
        /// is <c>nullptr</c>.</exception>
        /// <exception cref="std::bad_alloc">If the required resources could not
        /// be allocated.</exception>
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
        /// is <c>nullptr</c>.</exception>
        /// <exception cref="std::bad_alloc">If the required resources could not
        /// be allocated.</exception>
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
        /// <paramref name="definition" /> is invalid.</exception>
        /// <exception cref="std::bad_alloc">If the required resources could not
        /// be allocated.</exception>
        /// <exception cref="tinkerforge_exception">If the connection to the
        /// master brick could not be established.</exception>
        tinkerforge_sensor(const tinkerforge_sensor_definiton& definition,
            const char *host = default_host,
            const std::uint16_t port = default_port);

        /// <summary>
        /// Move <paramref name="rhs" /> into a new instance.
        /// </summary>
        /// <param name="rhs">The object to be moved.</param>
        inline tinkerforge_sensor(tinkerforge_sensor&& rhs) noexcept
                : _impl(rhs._impl) {
            rhs._impl = nullptr;
        }

        /// <summary>
        /// Finalises the instance.
        /// </summary>
        virtual ~tinkerforge_sensor(void);

        /// <summary>
        /// Retrieves the current configuration of the bricklet.
        /// </summary>
        /// <param name="averaging">Receives the number of samples to average.
        /// </param>
        /// <param name="voltage_conversion_time">Receives the A/D conversion
        /// time for voltage.</param>
        /// <param name="current_conversion_time">Receives the A/D conversion
        /// time for current.</param>
        /// <exception cref="std::runtime_error">If the sensor has been disposed
        /// by a move before.</exception>
        /// <exception cref="tinkerforge_exception">If the operation failed.
        /// </exception>
        void configuration(sample_averaging& averaging,
            conversion_time& voltage_conversion_time,
            conversion_time& current_conversion_time);

        /// <summary>
        /// Configures the bricklet.
        /// </summary>
        /// <param name="averaging">The number of samples to average.</param>
        /// <param name="voltage_conversion_time">The A/D conversion time for
        /// voltage.</param>
        /// <param name="current_conversion_time">The A/D conversion time for
        /// current.</param>
        /// <exception cref="std::runtime_error">If the sensor has been disposed
        /// by a move before.</exception>
        /// <exception cref="tinkerforge_exception">If the operation failed.
        /// </exception>
        void configure(const sample_averaging averaging,
            const conversion_time voltage_conversion_time,
            const conversion_time current_conversion_time);

        /// <summary>
        /// The user-defined description of what the sensor is measuring.
        /// </summary>
        /// <returns>The description of what the sensor is measuring.</returns>
        const wchar_t *description(void) const noexcept;

        /// <summary>
        /// Identify the bricklet used for the sensor.
        /// </summary>
        /// <param name="uid">Receives the UID of the sensor bricklet.</param>
        /// <param name="connected_to_uid">Receives the UID of the brick the
        /// sensor is connected to.</param>
        /// <param name="position">Receives the position ('a' to 'h') where the
        /// bricklet is connected to the brick.</param>
        /// <param name="hardware_version">Receives the major, minor, revision
        /// version of the hardware.</param>
        /// <param name="firmware_version">Receives the major, minor, revision
        /// version of the firmware.</param>
        /// <param name="device_id">Receives the ID of the hardware type, which
        /// should be 2105 for the Voltage/Current Bricklet 2.0. See
        /// https://www.tinkerforge.com/de/doc/Software/Device_Identifier.html#device-identifier
        /// for a list of identifiers.</param>
        /// <exception cref="std::runtime_error">If the sensor has been disposed
        /// by a move before.</exception>
        /// <exception cref="tinkerforge_exception">If the operation failed.
        /// </exception>
        void identify(char uid[8], char connected_to_uid[8], char& position,
            std::uint8_t hardware_version[3], std::uint8_t firmware_version[3],
            std::uint16_t& device_id) const;

        /// <summary>
        /// Answer the UID of the bricklet used for the sensor.
        /// </summary>
        /// <param name="uid">Receives the UID of the sensor bricklet.</param>
        /// <exception cref="std::runtime_error">If the sensor has been disposed
        /// by a move before.</exception>
        /// <exception cref="tinkerforge_exception">If the operation failed.
        /// </exception>
        void identify(char uid[8]) const;

        /// <summary>
        /// Gets the name of the sensor.
        /// </summary>
        /// <returns>The implementation-defined, human-readable name of the
        /// sensor.</returns>
        virtual const wchar_t *name(void) const noexcept override;

        /// <summary>
        /// Reset the bricklet.
        /// </summary>
        void reset(void);

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
        virtual measurement sample(
            const timestamp_resolution resolution) const override;

        using sensor::sample;

        /// <summary>
        /// Asynchronously sample the sensor every
        /// <paramref name="sampling_period "/> microseconds.
        /// </summary>
        /// <param name="on_measurement">The callback to be invoked if new data
        /// arrived. If this is <c>nullptr</c>, the asynchronous sampling will
        /// be disabled. Only one callback can be registered, subsequent calls
        /// will fail.</param>
        /// <param name="source">Specifies the data to be sampled from the
        /// bricklet. If you are only interested in power, it is reasonable to
        /// not request current and voltage in order to free up bandwidth.
        /// </param>
        /// <param name="sampling_period">The desired sampling period in
        /// microseconds. Note that Tinkerforge only supports millisecond
        /// resolution for this parameter, so this number must be divisble by
        /// 1000. The sampling frequence will be clamped to 1 ms at the bottom.
        /// This parameter defaults to 1000 (1 millisecond).
        /// </param>
        /// <param name="context">A user-defined context pointer that is passed
        /// on to <see cref="on_measurement" />. This parameter defaults to
        /// <c>nullptr</c>.</param>
        /// <exception cref="std::runtime_error">If the sensor has been moved.
        /// </exception>
        /// <exception cref="std::logic_error">If the sensor is already being
        /// sampled asynchronously due to a previous call to the method.
        /// </exception>
        /// <exception cref="tinkerforge_exception">If the sensor could not be
        /// sampled. </exception>
        void sample(const measurement_callback on_measurement,
            const tinkerforge_sensor_source source = default_source,
            const microseconds_type sampling_period = default_sampling_period,
            void *context = nullptr);

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
        virtual operator bool(void) const noexcept override;

    private:

        detail::tinkerforge_sensor_impl *_impl;
    };

} /* namespace power_overwhelming */
} /* namespace visus */
