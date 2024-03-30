// <copyright file="measurement_data.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/measurement_data.h"

#include <limits>
#include <stdexcept>


/*
 * visus::power_overwhelming::measurement_data::invalid_value
 */
const visus::power_overwhelming::measurement_data::value_type
visus::power_overwhelming::measurement_data::invalid_value
    = std::numeric_limits<value_type>::lowest();


/*
 * visus::power_overwhelming::measurement_data::measurement_data
 */
visus::power_overwhelming::measurement_data::measurement_data(
        _In_ const timestamp_type timestamp,
        _In_ const value_type voltage,
        _In_ const value_type current,
        _In_ const value_type power)
    :_current(current), _power(power), _timestamp(timestamp),
        _voltage(voltage) { }


/*
 * visus::power_overwhelming::measurement_data::measurement_data
 */
visus::power_overwhelming::measurement_data::measurement_data(
        _In_ const timestamp_type timestamp,
        _In_ const value_type voltage,
        _In_ const value_type current)
    :_current(current), _power(invalid_value), _timestamp(timestamp),
        _voltage(voltage) {
    if (voltage == invalid_value) {
        throw std::invalid_argument("A valid voltage measurement_data must be "
            "specified.");
    }
    if (current == invalid_value) {
        throw std::invalid_argument("A valid current measurement_data must be "
            "specified.");
    }
}


/*
 * visus::power_overwhelming::measurement_data::measurement_data
 */
visus::power_overwhelming::measurement_data::measurement_data(
        _In_ const timestamp_type timestamp,
        _In_ const value_type power)
    : _current(invalid_value), _power(power), _timestamp(timestamp),
        _voltage(invalid_value) {
    if (power == invalid_value) {
        throw std::invalid_argument("A valid power measurement_data must be "
            "specified.");
    }
}


/*
 * visus::power_overwhelming::measurement_data::operator =
 */
visus::power_overwhelming::measurement_data&
visus::power_overwhelming::measurement_data::operator =(
        measurement_data&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        this->_current = rhs._current;
        rhs._current = invalid_value;
        this->_power = rhs._power;
        rhs._power = invalid_value;
        this->_timestamp = rhs._timestamp;
        rhs._timestamp = power_overwhelming::timestamp(0);
        this->_voltage = rhs._voltage;
        rhs._voltage = invalid_value;
    }

    return *this;
}


/*
 * visus::power_overwhelming::measurement_data::operator bool
 */
visus::power_overwhelming::measurement_data::operator bool(void) const noexcept {
    auto isPowerValid = (this->_power != invalid_value);
    auto isSeparateValid = (this->_current != invalid_value)
        && (this->_voltage != invalid_value);
    return (isPowerValid || isSeparateValid);
}
