// <copyright file="thermal_sample.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cinttypes>
#include <limits>

#include "power_overwhelming/timestamp.h"


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Container for samples from a <see cref="thermal_sensor" />.
    /// </summary>
    class POWER_OVERWHELMING_API thermal_sample final {

    public:

        /// <summary>
        /// The type of a timestamp associated with the sample.
        /// </summary>
        typedef power_overwhelming::timestamp timestamp_type;

        /// <summary>
        /// The type used to express temperature values.
        /// </summary>
        typedef float value_type;

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="timestamp">The timestamp when the sample was obtained.
        /// </param>
        /// <param name="temperature">The temperature in degrees Celsius. If
        /// the value is below the absolute zero, the sample is considered
        /// invalid.</param>
        inline thermal_sample(
                _In_ const timestamp_type timestamp = timestamp_type::zero,
                _In_ const value_type temperature
                = std::numeric_limits<value_type>::lowest())
            : _temperature(temperature), _timestamp(timestamp) { }

        /// <summary>
        /// Gets the measured temperature.
        /// </summary>
        /// <returns>The temerature retrieved by the sensor.</returns>
        inline value_type temperature(void) const noexcept {
            return this->_temperature;
        }

        /// <summary>
        /// Gets the timestamp of the sample.
        /// </summary>
        /// <returns>The timestamp in the unit requested from the sensor.
        /// </returns>
        inline timestamp_type timestamp(void) const noexcept {
            return this->_timestamp;
        }

        /// <summary>
        /// Answer whether the temperature measurement in the sample is valid.
        /// </summary>
        /// <returns><c>false</c> if the temperature is below the absolute zero of
        /// 0 Kelvin, <c>true</c> otherwise.</returns>
        inline operator bool(void) const noexcept {
            return (this->_temperature >= -273.15f);
        }

    private:

        value_type _temperature;
        timestamp_type _timestamp;
    };

} /* namespace power_overwhelming */
} /* namespace visus */
