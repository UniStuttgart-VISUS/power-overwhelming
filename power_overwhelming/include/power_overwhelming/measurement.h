﻿// <copyright file="measurement.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cinttypes>
#include <iostream>
#include <utility>

#include "power_overwhelming/convert_string.h"
#include "power_overwhelming/csv_iomanip.h"
#include "power_overwhelming/quote.h"


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Represents a single measurement sample for current, voltage and power.
    /// </summary>
    class POWER_OVERWHELMING_API measurement {

    public:

        /// <summary>
        /// The type of string characters.
        /// </summary>
        typedef wchar_t char_type;

        /// <summary>
        /// The type of a timestamp associated with a measurement.
        /// </summary>
        typedef std::int64_t timestamp_type;

        /// <summary>
        /// The type of current and voltage measurements.
        /// </summary>
        typedef float value_type;

        /// <summary>
        /// The value used to represent invalid measurements.
        /// </summary>
        static const value_type invalid_value;

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="sensor">The name of the sensor from which the
        /// measurement originates, which must be a non-<c>nullptr</c> string.
        /// </param>
        /// <param name="timestamp">The timestamp of the sensor. The unit is
        /// defined by the configuration of the sensor.</param>
        /// <param name="voltage">The measured voltage in Volts.</param>
        /// <param name="current">The measured current in Amperes.</param>
        /// <param name="power">The measured power in Watts.</param>
        measurement(_In_z_ const char_type *sensor,
            _In_ const timestamp_type timestamp,
            _In_ const value_type voltage,
            _In_ const value_type current,
            _In_ const value_type power);

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="sensor">The name of the sensor from which the
        /// measurement originates.</param>
        /// <param name="timestamp">The timestamp of the sensor. The unit is
        /// defined by the configuration of the sensor.</param>
        /// <param name="voltage">The measured voltage in Volts.</param>
        /// <param name="current">The measured current in Amperes.</param>
        measurement(_In_z_ const char_type *sensor,
            _In_ const timestamp_type timestamp,
            _In_ const value_type voltage,
            _In_ const value_type current);

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="sensor">The name of the sensor from which the
        /// measurement originates.</param>
        /// <param name="timestamp">The timestamp of the sensor. The unit is
        /// defined by the configuration of the sensor.</param>
        /// <param name="power"></param>
        /// <param name="power">The measured power in Watts.</param>
        measurement(_In_z_ const char_type *sensor,
            _In_ const timestamp_type timestamp,
            _In_ const value_type power);

        /// <summary>
        /// Clone <paramref name="rhs" />.
        /// </summary>
        /// <param name="rhs">The object to be cloned.</param>
        inline measurement(const measurement& rhs) : _sensor(nullptr) {
            *this = rhs;
        }

        /// <summary>
        /// Move <paramref name="rhs" /> to a new object.
        /// </summary>
        /// <param name="rhs"></param>
        /// <returns></returns>
        inline measurement(measurement&& rhs) noexcept : _sensor(nullptr) {
            *this = std::move(rhs);
        }

        /// <summary>
        /// Finalises the instance.
        /// </summary>
        ~measurement(void);

        /// <summary>
        /// Gets the electric current (in Amperes) measured at the given point
        /// in time.
        /// </summary>
        /// <returns></returns>
        inline value_type current(void) const noexcept {
            return this->_current;
        }

        /// <summary>
        /// Gets the electric power (in Watts) measured at the given point in
        /// time.
        /// </summary>
        /// <remarks>
        /// If the specified power is negative, it is considered as not given
        /// and computed from current and voltage on the fly.
        /// </remarks>
        /// <returns></returns>
        inline value_type power(void) const noexcept {
            return (this->_power > static_cast<value_type>(0))
                ? this->_power
                : this->_current * this->_voltage;
        }

        /// <summary>
        /// Gets the name of the sensor the measurement comes from.
        /// </summary>
        /// <returns></returns>
        inline _Ret_z_ const char_type *sensor(void) const noexcept {
            return this->_sensor;
        }

        /// <summary>
        /// Gets the timestamp of the measurement.
        /// </summary>
        /// <returns></returns>
        inline timestamp_type timestamp(void) const noexcept {
            return this->_timestamp;
        }

        /// <summary>
        /// Gets the electric potential (in Volts) measured at the given point
        /// in time.
        /// </summary>
        /// <returns></returns>
        inline value_type voltage(void) const noexcept {
            return this->_voltage;
        }

        /// <summary>
        /// Assignment.
        /// </summary>
        /// <param name="rhs"></param>
        /// <returns><c>*this</c></returns>
        measurement& operator =(const measurement& rhs);

        /// <summary>
        /// Move assignment.
        /// </summary>
        /// <param name="rhs"></param>
        /// <returns><c>*this</c></returns>
        measurement& operator =(measurement&& rhs) noexcept;

        /// <summary>
        /// Test whether the measurement is valid.
        /// </summary>
        /// <param name=""></param>
        /// <returns></returns>
        operator bool(void) const noexcept;

    private:

        value_type _current;
        value_type _power;
        char_type *_sensor;
        timestamp_type _timestamp;
        value_type _voltage;
    };


    /// <summary>
    /// A callback for <see cref="measurement" />s that are received
    /// asynchronously.
    /// </summary>
    typedef void (*measurement_callback)(const measurement&, _In_opt_ void *);

} /* namespace power_overwhelming */
} /* namespace visus */


namespace std {

    /// <summary>
    /// Print <paramref name="rhs" /> as CSV to <paramref name="lhs" />.
    /// </summary>
    /// <typeparam name="TChar"></typeparam>
    /// <typeparam name="TTraits"></typeparam>
    /// <param name="lhs"></param>
    /// <param name="rhs"></param>
    /// <returns></returns>
    template<class TChar, class TTraits>
    basic_ostream<TChar, TTraits>& operator <<(
        _In_ basic_ostream<TChar, TTraits>& lhs,
        _In_ const visus::power_overwhelming::measurement &rhs);

}

#include "power_overwhelming/measurement.inl"
