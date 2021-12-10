// <copyright file="hmc8015_sensor.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <climits>
#include <cstddef>
#include <cstdint>
#include <cinttypes>

#include "instrument_range.h"
#include "log_mode.h"
#include "measurement.h"
#include "timestamp_resolution.h"


namespace visus {
namespace power_overwhelming {

    /* Forward declarations */
    namespace detail { struct visa_sensor_impl; }

    /// <summary>
    /// Allows for controlling a Rohde & Schwarz HMC8015 power analyser.
    /// </summary>
    class POWER_OVERWHELMING_API hmc8015_sensor final {

    public:

        /// <summary>
        /// Create sensor objects for all Rohde &amp; Schwarz HMC8015
        /// instruments that can be enumerated via VISA.
        /// </summary>
        /// <param name="out_sensors">An array receiving the sensors. If this is
        /// <c>nullptr</c>, nothing is returned.</param>
        /// <param name="cnt_sensors">The number of sensors that can be stored in
        /// <paramref name="out_sensors" />.</param>
        /// <param name="timeout">The timeout in milliseconds for establishing a
        /// connection to each instrument that was found. This parameter defaults
        /// to 3000.</param>
        /// <returns>The number of HMC8015 instruments found, regardless of how
        /// many have been returned to <paramref name="out_sensors" />.</returns>
        static std::size_t for_all(hmc8015_sensor *out_sensors,
            const std::size_t cnt_sensors,
            const std::int32_t timeout = 3000);

        /// <summary>
        /// The product ID of the HMC8015.
        /// </summary>
        /// <remarks>
        /// This is the ID reported by the device we use at VISUS. If this does
        /// not work, use the RsVisaTester tool and discover the device via the
        /// &quot;Find Resource&quot; functionality.
        /// </remarks>
        static constexpr const char *product_id = "0x0135";

        /// <summary>
        /// The vendor ID of Rohde &amp; Schwarz.
        /// </summary>
        static constexpr const char *vendor_id = "0x0AAD";

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        hmc8015_sensor(void);

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="path"></param>
        /// <param name="timeout"></param>
        /// <exception cref="std::invalid_argument">If <paramref name="path" />
        /// is <c>nullptr</c>.</exception>
        /// <exception cref="std::bad_alloc">If the memory for the sensor state
        /// could not be allocated.</exception>
        /// <exception cref="std::system_error">If the VISA library could not be
        /// loaded.</exception>
        /// <exception cref="visa_exception">If the sensor could not be
        /// initialised.</exception>
        hmc8015_sensor(const char *path, const std::int32_t timeout);

        /// <summary>
        /// Move <paramref name="rhs" /> into a new instance.
        /// </summary>
        /// <param name="rhs">The object to be moved.</param>
        inline hmc8015_sensor(hmc8015_sensor&& rhs) noexcept
                : _impl(rhs._impl) {
            rhs._impl = nullptr;
        }

        /// <summary>
        /// Finalise the instance.
        /// </summary>
        ~hmc8015_sensor(void);

        /// <summary>
        /// Sets the current range.
        /// </summary>
        /// <remarks>
        /// <para>The instrument can be instructed to select a reasonable range
        /// by specifying <see cref="instrument_range::automatically" />.
        /// However, this will prevent a correct integration of measurements if
        /// the range changes during the measurement period. Therefore, it is
        /// reasonable to specify a safe range explictly in such an application
        /// case.</para>
        /// </remarks>
        /// <param name="range">Defines how <paramref name="value" /> is
        /// interpreted.</param>
        /// <param name="value">The current range in Amperes. This parameter
        /// is only used if <paramref name="range" /> is set to
        /// <see cref="instrument_range::explicitly" />. Valid values are
        /// 0.005, 0.01, 0.02, 0.05, 0.1, 0.2, 0.5, 1, 2, 5, 10 an 20.</param>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        inline void current_range(const instrument_range range,
                const float value = 0.0f) {
            // Note: HMC8015 supports only one channel, so this is hard coded.
            this->set_range(1, "CURR", range, value);
        }

        /// <summary>
        /// Gets whether logging is enabled or not.
        /// </summary>
        /// <returns><c>true</c> if the instrument is currently logging,
        /// <c>false</c> otherwise.</returns>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        bool is_log(void);

        /// <summary>
        /// Enables or disables logging.
        /// </summary>
        /// <param name="enable">Start logging if <c>true</c>, otherwise, stop
        /// it.</param>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        void log(const bool enable);

        /// <summary>
        /// Configures how logging started by <see cref="log" /> behaves.
        /// </summary>
        /// <param name="interval">The interval between samples in seconds.
        /// Specifying the lowest/maximum value of <c>float</c> is interpreted
        /// as special values &quot;MIN&quot; and &quot;MAX&quot; respectively.
        /// </param>
        /// <param name="mode">The logging mode.</param>
        /// <param name="value">The count (number of samples) or duration (in
        /// seconds), depending on the given <paramref name="mode" />. This
        /// value is ignored for <see cref="log_mode::unlimited" />. Specifying
        /// the lowest/maximum value of <c>int</c> is interpreted as special
        /// values &quot;MIN&quot; and &quot;MAX&quot; respectively.</param>
        /// <param name="year">The year of the start time if
        /// <see cref="log_mode::time_span" /> is selected.</param>
        /// <param name="month">The month of the start time if
        /// <see cref="log_mode::time_span" /> is selected.</param>
        /// <param name="day">The day of the start time if
        /// <see cref="log_mode::time_span" /> is selected.</param>
        /// <param name="hour">The hour of the start time if
        /// <see cref="log_mode::time_span" /> is selected.</param>
        /// <param name="minute">The minute of the start time if
        /// <see cref="log_mode::time_span" /> is selected.</param>
        /// <param name="second">The second of the start time if
        /// <see cref="log_mode::time_span" /> is selected.</param>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        void log_behaviour(const float interval, const log_mode mode,
            const int value = INT_MAX,
            const std::int32_t year = 0, const std::int32_t month = 0,
            const std::int32_t day = 0, const std::int32_t hour = 0,
            const std::int32_t minute = 0, const std::int32_t second = 0);

        /// <summary>
        /// Gets the path to the log file.
        /// </summary>
        /// <param name="path">The buffer receiving the log file. Note that
        /// this is the path and a designator whether the internal or USB
        /// memory is used. If this parameter is <c>nullptr</c>, nothing will
        /// be written. The output string is guaranteed to be null-terminated
        /// if anything has been written.</param>
        /// <param name="cnt">The maximum number of bytes that can be written
        /// to <paramref name="path "/>.</param>
        /// <returns>The actual length of the path, including the terminating
        /// null character.</returns>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        std::size_t log_file(char *path, const std::size_t cnt);

        /// <summary>
        /// Sets the path to the log file.
        /// </summary>
        /// <param name="path">The path to the log file, usually just the
        /// file name.</param>
        /// <param name="overwrite">If <c>true</c>, the file will be cleared
        /// if it already exists. This parameter defaults to <c>false</c>.
        /// </param>
        /// <param name="use_usb">If <c>true</c>, the file will be written to
        /// the attached USB stick instead of internal memory. This parameter
        /// defaults to <c>false</c>.</param>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        void log_file(const char *path, const bool overwrite = false,
            const bool use_usb = false);

        /// <summary>
        /// Gets the name of the sensor.
        /// </summary>
        /// <returns>The implementation-defined, human-readable name of the
        /// sensor.</returns>
        const wchar_t *name(void) const noexcept;

        /// <summary>
        /// Resets the instrument to its default state.
        /// </summary>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        void reset(void);

        /// <summary>
        /// Samples the sensor one time.
        /// </summary>
        /// <param name="resolution">The resolution of the timestamp to be
        /// generated for the measurement.</param>
        /// <returns>The measurement received from the instrument.</returns>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        measurement sample(const timestamp_resolution resolution
            = timestamp_resolution::milliseconds);

        /// <summary>
        /// Synchonises the date and time on the instrument with the system
        /// clock of the computer calling this API.
        /// </summary>
        /// <param name="utc">If <c>true</c>, UTC will be used, the local time
        /// otherwise. This parameter defaults to <c>false</c>.</param>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        void synchronise_clock(const bool utc = false);

        /// <summary>
        /// Sets the voltage range.
        /// </summary>
        /// <remarks>
        /// <para>The instrument can be instructed to select a reasonable range
        /// by specifying <see cref="instrument_range::automatically" />.
        /// However, this will prevent a correct integration of measurements if
        /// the range changes during the measurement period. Therefore, it is
        /// reasonable to specify a safe range explictly in such an application
        /// case.</para>
        /// </remarks>
        /// <param name="range">Defines how <paramref name="value" /> is
        /// interpreted.</param>
        /// <param name="value">The current range in Volts. This parameter
        /// is only used if <paramref name="range" /> is set to
        /// <see cref="instrument_range::explicitly" />. Valid values are
        /// 5, 15, 30, 60, 150, 300 and 600.</param>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        inline void voltage_range(const instrument_range range,
                const std::int32_t value = 0) {
            // Note: HMC8015 supports only one channel, so this is hard coded.
            this->set_range(1, "VOLT", range, static_cast<float>(value));
        }

        /// <summary>
        /// Move assignment.
        /// </summary>
        /// <param name="rhs">The right-hand side operand</param>
        /// <returns><c>*this</c></returns>
        hmc8015_sensor& operator =(hmc8015_sensor&& rhs) noexcept;

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

        void check_not_disposed(void);

        void set_range(const std::int32_t channel, const char *quantity,
            const instrument_range range, const float value);

        detail::visa_sensor_impl *_impl;
    };

} /* namespace power_overwhelming */
} /* namespace visus */
