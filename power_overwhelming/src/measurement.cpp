// <copyright file="measurement.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/measurement.h"

#include <limits>
#include <stdexcept>


/*
 * visus::power_overwhelming::measurement::invalid_value
 */
const visus::power_overwhelming::measurement::value_type
visus::power_overwhelming::measurement::invalid_value
    = std::numeric_limits<value_type>::lowest();


/*
 * visus::power_overwhelming::measurement::measurement
 */
visus::power_overwhelming::measurement::measurement(const char_type *sensor,
        const timestamp_type timestamp, const value_type voltage,
        const value_type current, const value_type power) 
    :_current(current), _power(power), _sensor(nullptr),
        _timestamp(timestamp), _voltage(voltage) {
    if (sensor == nullptr) {
        throw std::invalid_argument("A valid sensor name must be specified.");
    }

    this->_sensor = ::_wcsdup(sensor);
    if (this->_sensor == nullptr) {
        throw std::bad_alloc();
    }
}


/*
 * visus::power_overwhelming::measurement::measurement
 */
visus::power_overwhelming::measurement::measurement(const char_type *sensor,
        const timestamp_type timestamp, const value_type voltage,
        const value_type current) 
    :_current(current), _power(invalid_value), _sensor(nullptr),
        _timestamp(timestamp), _voltage(voltage) {
    if (sensor == nullptr) {
        throw std::invalid_argument("A valid sensor name must be specified.");
    }
    if (voltage == invalid_value) {
        throw std::invalid_argument("A valid voltage measurement must be "
            "specified.");
    }
    if (current == invalid_value) {
        throw std::invalid_argument("A valid current measurement must be "
            "specified.");
    }

    this->_sensor = ::_wcsdup(sensor);
    if (this->_sensor == nullptr) {
        throw std::bad_alloc();
    }
}


/*
 * visus::power_overwhelming::measurement::measurement
 */
visus::power_overwhelming::measurement::measurement(const char_type *sensor,
        const timestamp_type timestamp, const value_type power)
    :_current(invalid_value), _power(power), _sensor(nullptr),
        _timestamp(timestamp), _voltage(invalid_value) {
    if (sensor == nullptr) {
        throw std::invalid_argument("A valid sensor name must be specified.");
    }
    if (power == invalid_value) {
        throw std::invalid_argument("A valid power measurement must be "
            "specified.");
    }

    this->_sensor = ::_wcsdup(sensor);
    if (this->_sensor == nullptr) {
        throw std::bad_alloc();
    }
}


/*
 * visus::power_overwhelming::measurement::~measurement
 */
visus::power_overwhelming::measurement::~measurement(void) {
    if (this->_sensor != nullptr) {
        ::free(this->_sensor);
    }
}


/*
 * visus::power_overwhelming::measurement::operator =
 */
visus::power_overwhelming::measurement&
visus::power_overwhelming::measurement::operator =(const measurement& rhs) {
    if (this != std::addressof(rhs)) {
        this->_current = rhs._current;
        this->_power = rhs._power;
        this->_sensor = ::_wcsdup(rhs._sensor);
        if (this->_sensor == nullptr) {
            throw std::bad_alloc();
        }
        this->_timestamp = rhs._timestamp;
        this->_voltage = rhs._voltage;
    }

    return *this;
}


/*
 * visus::power_overwhelming::measurement::operator =
 */
visus::power_overwhelming::measurement&
visus::power_overwhelming::measurement::operator =(measurement&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        this->_current = rhs._current;
        rhs._current = invalid_value;
        this->_power = rhs._power;
        rhs._power = invalid_value;
        this->_sensor = rhs._sensor;
        rhs._sensor = nullptr;
        this->_timestamp = rhs._timestamp;
        rhs._timestamp = 0;
        this->_voltage = rhs._voltage;
        rhs._voltage = invalid_value;
    }

    return *this;
}


/*
 * visus::power_overwhelming::measurement::operator bool
 */
visus::power_overwhelming::measurement::operator bool(void) const noexcept {
    auto isPowerValid = (this->_power != invalid_value);
    auto isSeparateValid = (this->_current != invalid_value)
        && (this->_voltage != invalid_value);

    return (this->_sensor != nullptr) && (isPowerValid || isSeparateValid);
}
