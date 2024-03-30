// <copyright file="measurement_data.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cinttypes>
#include <utility>

#include "power_overwhelming/timestamp.h"


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Container for the raw measurement data of a single sample for current,
    /// voltage and power.
    /// </summary>
    /// <remarks>
    /// This class has been newly introduced to reduce the overhead of code that
    /// manually tracks the source of samples instead of relying on the sensor
    /// embedding its name into a <see cref="measurement" /> sample.
    /// </remarks>
    class POWER_OVERWHELMING_API measurement_data final {

    public:

        /// <summary>
        /// The type of a timestamp associated with a measurement.
        /// </summary>
        typedef power_overwhelming::timestamp timestamp_type;

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
        /// <param name="timestamp">The timestamp of the sensor.</param>
        /// <param name="voltage">The measured voltage in Volts.</param>
        /// <param name="current">The measured current in Amperes.</param>
        /// <param name="power">The measured power in Watts.</param>
        measurement_data(_In_ const timestamp_type timestamp,
            _In_ const value_type voltage,
            _In_ const value_type current,
            _In_ const value_type power);

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="timestamp">The timestamp of the sensor.</param>
        /// <param name="voltage">The measured voltage in Volts.</param>
        /// <param name="current">The measured current in Amperes.</param>
        /// <exception cref="std::invalid_argument">If any of
        /// <paramref name="voltage" /> or <paramref name="current" /> is
        /// <see cref="measurement_data::invalid_value" />.</exception>
        measurement_data(_In_ const timestamp_type timestamp,
            _In_ const value_type voltage,
            _In_ const value_type current);

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="timestamp">The timestamp of the sensor.</param>
        /// <param name="power"></param>
        /// <param name="power">The measured power in Watts.</param>
        /// <exception cref="std::invalid_argument">If <paramref name="power" />
        /// is <see cref="measurement_data::invalid_value" />.</exception>
        measurement_data(_In_ const timestamp_type timestamp,
            _In_ const value_type power);

        /// <summary>
        /// Clone <paramref name="rhs" />.
        /// </summary>
        /// <param name="rhs">The object to be cloned.</param>
        measurement_data(const measurement_data& rhs) = default;

        /// <summary>
        /// Move <paramref name="rhs" /> to a new object.
        /// </summary>
        /// <param name="rhs">The object to be moved.</param>
        inline measurement_data(measurement_data&& rhs) noexcept {
            *this = std::move(rhs);
        }

        /// <summary>
        /// Finalises the instance.
        /// </summary>
        ~measurement_data(void) = default;

        /// <summary>
        /// Gets the electric current (in Amperes) measured at the given point
        /// in time.
        /// </summary>
        /// <returns>The electric current if it was measured, or
        /// <see cref="invalid_value" /> if the sample only contains the
        /// power.</returns>
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
        /// <returns>The electric power.</returns>
        inline value_type power(void) const noexcept {
            return (this->_power >= static_cast<value_type>(0))
                ? this->_power
                : this->_current * this->_voltage;
        }

        /// <summary>
        /// Gets the timestamp of the measurement.
        /// </summary>
        /// <returns>The timestamp of the measurement.</returns>
        inline timestamp_type timestamp(void) const noexcept {
            return this->_timestamp;
        }

        /// <summary>
        /// Gets the electric potential (in Volts) measured at the given point
        /// in time.
        /// </summary>
        /// <returns>The electric potential if it was measured, or
        /// <see cref="invalid_value" /> if the sample only contains the
        /// power.</returns>
        inline value_type voltage(void) const noexcept {
            return this->_voltage;
        }

        /// <summary>
        /// Assignment.
        /// </summary>
        /// <param name="rhs">The right-hand side operand.</param>
        /// <returns><c>*this</c></returns>
        measurement_data& operator =(const measurement_data& rhs) = default;

        /// <summary>
        /// Move assignment.
        /// </summary>
        /// <param name="rhs">The right-hand side operand.</param>
        /// <returns><c>*this</c></returns>
        measurement_data& operator =(measurement_data&& rhs) noexcept;

        /// <summary>
        /// Test whether the measurement is valid.
        /// </summary>
        /// <returns><c>true</c> if the object contains valid measurement
        /// data, <c>false</c> otherwise.</returns>
        operator bool(void) const noexcept;

    private:

        inline measurement_data(void) : _current(invalid_value),
            _power(invalid_value), _timestamp(0), _voltage(invalid_value) { }

        value_type _current;
        value_type _power;
        timestamp_type _timestamp;
        value_type _voltage;

        friend class measurement_data_series;
    };

} /* namespace power_overwhelming */
} /* namespace visus */
