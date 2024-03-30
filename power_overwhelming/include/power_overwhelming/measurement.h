// <copyright file="measurement.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licenced under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <iostream>
#include <utility>

#include "power_overwhelming/convert_string.h"
#include "power_overwhelming/csv_iomanip.h"
#include "power_overwhelming/measurement_data.h"
#include "power_overwhelming/quote.h"


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Represents a single measurement sample for current, voltage and power.
    /// </summary>
    class POWER_OVERWHELMING_API measurement final {

    public:

        /// <summary>
        /// The type of string characters.
        /// </summary>
        typedef wchar_t char_type;

        /// <summary>
        /// The type of a timestamp associated with a measurement.
        /// </summary>
        typedef measurement_data::timestamp_type timestamp_type;

        /// <summary>
        /// The type of current and voltage measurements.
        /// </summary>
        typedef measurement_data::value_type value_type;

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
        /// Initialises a new instance.
        /// </summary>
        /// <param name="sensor">The name of the sensor from which the
        /// measurement originates.</param>
        /// <param name="data">The actual measurement data of the sample.
        /// </param>
        measurement(_In_z_ const char_type *sensor,
            _In_ const measurement_data& data);

        /// <summary>
        /// Clone <paramref name="rhs" />.
        /// </summary>
        /// <param name="rhs">The object to be cloned.</param>
        inline measurement(_In_ const measurement& rhs)
                : _data(rhs._data),  _sensor(nullptr) {
            this->set_sensor(rhs._sensor);
        }

        /// <summary>
        /// Move <paramref name="rhs" /> to a new object.
        /// </summary>
        /// <param name="rhs"></param>
        /// <returns></returns>
        inline measurement(measurement&& rhs) noexcept
                : _data(std::move(rhs._data)), _sensor(rhs._sensor) {
            rhs._sensor = nullptr;
        }

        /// <summary>
        /// Finalises the instance.
        /// </summary>
        ~measurement(void);

        /// <summary>
        /// Gets the electric current (in Amperes) measured at the given point
        /// in time.
        /// </summary>
        /// <returns>The electric current if it was measured, or
        /// <see cref="invalid_value" /> if the sample only contains the
        /// power.</returns>
        inline value_type current(void) const noexcept {
            return this->_data.current();
        }

        /// <summary>
        /// Gets the pure <see cref="measurement_data" /> of the sample.
        /// </summary>
        /// <returns>The data of the sample.</returns>
        inline const measurement_data& data(void) const noexcept {
            return this->_data;
        }

        /// <summary>
        /// Gets the electric power (in Watts) measured at the given point in
        /// time.
        /// </summary>
        /// <remarks>
        /// If the specified power is negative, it is considered as not given
        /// and computed from current and voltage on the fly.
        /// </remarks>
        /// <returns>The electric power.</returns>
        inline value_type power(void) const noexcept {
            return this->_data.power();
        }

        /// <summary>
        /// Gets the name of the sensor the measurement comes from.
        /// </summary>
        /// <returns>The name of the sensor, which may be <c>nullptr</c> if the
        /// sample has been moved.</returns>
        inline _Ret_maybenull_z_ const char_type *sensor(void) const noexcept {
            return this->_sensor;
        }

        /// <summary>
        /// Gets the timestamp of the measurement.
        /// </summary>
        /// <returns>The timestamp in the unit requested from the sensor.
        /// </returns>
        inline timestamp_type timestamp(void) const noexcept {
            return this->_data.timestamp();
        }

        /// <summary>
        /// Gets the electric potential (in Volts) measured at the given point
        /// in time.
        /// </summary>
        /// <returns>The electric potential if it was measured, or
        /// <see cref="invalid_value" /> if the sample only contains the
        /// power.</returns>
        inline value_type voltage(void) const noexcept {
            return this->_data.voltage();
        }

        /// <summary>
        /// Assignment.
        /// </summary>
        /// <param name="rhs">The right-hand side operand.</param>
        /// <returns><c>*this</c></returns>
        measurement& operator =(const measurement& rhs);

        /// <summary>
        /// Move assignment.
        /// </summary>
        /// <param name="rhs">The right-hand side operand.</param>
        /// <returns><c>*this</c></returns>
        measurement& operator =(measurement&& rhs) noexcept;

        /// <summary>
        /// Test whether the measurement is valid.
        /// </summary>
        /// <returns><c>true</c> if the measurement is valid, <c>false</c>
        /// if it has been invalidated by moving it.</returns>
        operator bool(void) const noexcept;

    private:

        void set_sensor(_In_z_ const char_type *sensor);

        measurement_data _data;
        char_type *_sensor;
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
