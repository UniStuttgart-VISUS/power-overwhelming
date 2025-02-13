// <copyright file="tinkerforge_configuration.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_TINKERFORGE_CONFIGURATION_H)
#define _PWROWG_TINKERFORGE_CONFIGURATION_H
#pragma once

#include <chrono>
#include <cmath>

#include "visus/pwrowg/blob.h"
#include "visus/pwrowg/sensor_configuration.h"
#include "visus/pwrowg/tinkerforge_conversion_time.h"
#include "visus/pwrowg/tinkerforge_error_count.h"
#include "visus/pwrowg/tinkerforge_sample_averaging.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Provides additional configuration options for Tingerforge-based sensors when
/// creating a <see cref="sensor_array" />.
/// </summary>
/// <remarks>
/// <para>Note that the configuration object will keep the connection with the
/// bricks alive. Releasing all sensors is not sufficient to close all
/// connections.</para>
/// </remarks>
class POWER_OVERWHELMING_API tinkerforge_configuration final
        : public sensor_configuration {

public:

    /// <summary>
    /// Represents the location of a Tinkerforge Brickd.
    /// </summary>
    class end_point final {

    public:

        /// <summary>
        /// Initialises a new instance with the default port on localhost.
        /// </summary>
        end_point(void);

        /// <summary>
        /// Initialises a new instance with the default port.
        /// </summary>
        /// <param name="host">The host name or address.</param>
        end_point(_In_z_ const char *host);

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="host">The host name or address.</param>
        /// <param name="port">The port number.</param>
        end_point(_In_z_ const char *host, _In_ const std::uint16_t port);

        /// <summary>
        /// Answer the name or address of the host where Brickd is runnning.
        /// </summary>
        /// <returns>The host name or address.</returns>
        inline _Ret_maybenull_z_ const char *name(void) const noexcept {
            return this->_name.as<char>();
        }

        /// <summary>
        /// Answer the port the Brickd is listening on.
        /// </summary>
        /// <returns>The port of the Brick.</returns>
        inline std::uint16_t port(void) const noexcept {
            return this->_port;
        }

    private:

        blob _name;
        std::uint16_t _port;
    };

    /// <summary>
    /// A unique identifer for the <see cref="tinkerforge_configuration" /> type.
    /// </summary>
    static const guid id;

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    tinkerforge_configuration(void);

    /// <summary>
    /// Initialise a copy of <paramref name="rhs" />.
    /// </summary>
    /// <param name="rhs">The object to be cloned.</param>
    tinkerforge_configuration(_In_ const tinkerforge_configuration& rhs);

    /// <summary>
    /// Finalises the instance.
    /// </summary>
    ~tinkerforge_configuration(void);

    /// <summary>
    /// Adds the given end point to the list of end points.
    /// </summary>
    /// <param name="address">The end point to be added.</param>
    /// <returns><c>*this</c>.</returns>
    tinkerforge_configuration& add_end_point(_In_ const end_point& address);

    /// <summary>
    /// Answer how many samples from the sensor will be averaged for an output
    /// sample.
    /// </summary>
    /// <returns>The sample averaging.</returns>
    inline tinkerforge_sample_averaging averaging(void) const noexcept {
        return this->_averaging;
    }

    /// <summary>
    /// Configure how many samples from the sensor will be averaged for an output
    /// sample.
    /// </summary>
    /// <param name="averaging">The new averaging method.</param>
    /// <returns><c>*this</c>.</returns>
    inline tinkerforge_configuration& averaging(
            _In_ const tinkerforge_sample_averaging averaging) noexcept {
        this->_averaging = averaging;
        return *this;
    }

    /// <summary>
    /// Answer the number of registered end points.
    /// </summary>
    /// <returns>The number of registered end points.</returns>
    inline std::size_t count_end_points(void) const noexcept {
        return this->_cnt_end_points;
    }

    /// <summary>
    /// Answer the conversio time of teh current sensor.
    /// </summary>
    /// <returns>The configured conversion time.</returns>
    inline tinkerforge_conversion_time current_conversion_time(
            void) const noexcept {
        return this->_current_conversion_time;
    }

    /// <summary>
    /// Configure the conversion time of the current sensor.
    /// </summary>
    /// <param name="conversion_time">The new conversion time.</param>
    /// <returns><c>*this</c>.</returns>
    inline tinkerforge_configuration& current_conversion_time(
            _In_ const tinkerforge_conversion_time conversion_time) noexcept {
        this->_current_conversion_time = conversion_time;
        return *this;
    }

    /// <summary>
    /// Answer the array of registered <see cref="end_point" />s.
    /// </summary>
    /// <remarks>
    /// The size of the array can be obtained from
    /// <see cref="count_end_points" />.
    /// </remarks>
    /// <returns>The end points of the Brickds.</returns>
    inline _Ret_valid_ const end_point *end_points(void) const noexcept {
        return this->_end_points;
    }

    /// <summary>
    /// Sets all end points.
    /// </summary>
    /// <param name="addresses">An array of at least <paramref name="cnt" /> end
    /// point addresses.</param>
    /// <param name="cnt">The number of end points provided.</param>
    /// <returns><c>*this</c>.</returns>
    tinkerforge_configuration& end_points(_In_reads_(cnt) end_point *addresses,
        _In_ const std::size_t cnt);

    /// <summary>
    /// Answer the timeout for connecting to the brickd, in milliseconds.
    /// </summary>
    /// <returns>The timeout in milliseconds.</returns>
    inline std::uint32_t timeout(void) const noexcept {
        return this->_timeout;
    }

    /// <summary>
    /// Sets the timeout for connecting to the brickd.
    /// </summary>
    /// <typeparam name="TType"></typeparam>
    /// <typeparam name="TPeriod"></typeparam>
    /// <param name="timeout"></param>
    /// <returns></returns>
    template<class TType, class TPeriod>
    inline tinkerforge_configuration& timeout(
            _In_ const std::chrono::duration<TType, TPeriod> timeout) {
        auto m= std::chrono::duration_cast<std::chrono::milliseconds>(timeout);
        this->_timeout = std::abs(m.count());
        return *this;
    }

    /// <summary>
    /// Answer the conversio time of teh voltage sensor.
    /// </summary>
    /// <returns>The configured conversion time.</returns>
    inline tinkerforge_conversion_time voltage_conversion_time(
            void) const noexcept {
        return this->_voltage_conversion_time;
    }

    /// <summary>
    /// Configure the conversion time of the voltage sensor.
    /// </summary>
    /// <param name="conversion_time">The new conversion time.</param>
    /// <returns><c>*this</c>.</returns>
    inline tinkerforge_configuration& voltage_conversion_time(
            _In_ const tinkerforge_conversion_time conversion_time) noexcept {
        this->_voltage_conversion_time = conversion_time;
        return *this;
    }

    /// <summary>
    /// Assignment.
    /// </summary>
    /// <param name="rhs">The object to be cloned.</param>
    /// <returns><c>*this</c>.</returns>
    tinkerforge_configuration& operator =(
        _In_ const tinkerforge_configuration& rhs);

private:

    tinkerforge_sample_averaging _averaging;
    std::size_t _cnt_end_points;
    tinkerforge_conversion_time _current_conversion_time;
    end_point *_end_points;
    std::uint64_t _timeout;
    tinkerforge_conversion_time _voltage_conversion_time;

};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_TINKERFORGE_CONFIGURATION_H) */
