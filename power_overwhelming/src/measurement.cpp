// <copyright file="measurement.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2023 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/measurement.h"

#include <stdexcept>

#include "string_functions.h"


/*
 * visus::power_overwhelming::measurement::invalid_value
 */
const visus::power_overwhelming::measurement::value_type
visus::power_overwhelming::measurement::invalid_value
    = visus::power_overwhelming::measurement_data::invalid_value;


/*
 * visus::power_overwhelming::measurement::measurement
 */
visus::power_overwhelming::measurement::measurement(
        _In_z_ const char_type *sensor,
        _In_ const timestamp_type timestamp,
        _In_ const value_type voltage,
        _In_ const value_type current,
        _In_ const value_type power)
        : _data(timestamp, voltage, current, power), _sensor(nullptr) {
    this->set_sensor(sensor);
}


/*
 * visus::power_overwhelming::measurement::measurement
 */
visus::power_overwhelming::measurement::measurement(
        _In_z_ const char_type *sensor,
        _In_ const timestamp_type timestamp,
        _In_ const value_type voltage,
        _In_ const value_type current)
        : _data(timestamp, voltage, current), _sensor(nullptr) {
    this->set_sensor(sensor);
}


/*
 * visus::power_overwhelming::measurement::measurement
 */
visus::power_overwhelming::measurement::measurement(
        _In_z_ const char_type *sensor,
        _In_ const timestamp_type timestamp,
        _In_ const value_type power)
        : _data(timestamp, power), _sensor(nullptr) {
    this->set_sensor(sensor);
}


/*
 * visus::power_overwhelming::measurement::measurement
 */
visus::power_overwhelming::measurement::measurement(
        _In_z_ const char_type *sensor,
        _In_ const measurement_data& data)
        : _data(data), _sensor(nullptr) {
    this->set_sensor(sensor);
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
        this->_data = rhs._data;
        detail::safe_assign(this->_sensor, rhs._sensor);
    }

    return *this;
}


/*
 * visus::power_overwhelming::measurement::operator =
 */
visus::power_overwhelming::measurement&
visus::power_overwhelming::measurement::operator =(measurement&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        this->_data = std::move(rhs._data);
        detail::safe_assign(this->_sensor, std::move(rhs._sensor));
    }

    return *this;
}


/*
 * visus::power_overwhelming::measurement::operator bool
 */
visus::power_overwhelming::measurement::operator bool(void) const noexcept {
    return (this->_sensor != nullptr) && static_cast<bool>(this->_data);
}


/*
 * visus::power_overwhelming::measurement::set_sensor
 */
void visus::power_overwhelming::measurement::set_sensor(
        _In_z_ const char_type *sensor) {
    if (sensor == nullptr) {
        throw std::invalid_argument("A valid sensor name must be specified.");
    }

    detail::safe_assign(this->_sensor, sensor);
}
