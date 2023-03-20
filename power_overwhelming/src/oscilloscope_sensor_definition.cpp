// <copyright file="oscilloscope_sensor_definition.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/oscilloscope_sensor_definition.h"

#include <cassert>
#include <memory>
#include <stdexcept>


/*
 * ...::oscilloscope_sensor_definition
 */
visus::power_overwhelming::oscilloscope_sensor_definition::oscilloscope_sensor_definition(
        _In_z_ const wchar_t *description,
        _In_ const std::uint32_t channel_voltage,
        _In_ const std::uint32_t channel_current)
    : _attenuation_current(0.0f),
        _attenuation_voltage(0.0f),
        _channel_current(channel_current),
        _channel_voltage(channel_voltage),
        _description(nullptr) {
    if (description == nullptr) {
        throw std::invalid_argument("The description of an oscilloscope-based "
            "sensor must not be null.");
    }
    if (this->_channel_current == this->_channel_voltage) {
        throw std::invalid_argument("The channel measuring voltage cannot be "
            "the same as the one measuring current.");
    }

    this->_description = ::wcsdup(description);
    if (this->_description == nullptr) {
        throw std::bad_alloc();
    }
}


/*
 * ...::oscilloscope_sensor_definition
 */
visus::power_overwhelming::oscilloscope_sensor_definition::oscilloscope_sensor_definition(
        _In_z_ const wchar_t *description,
        _In_ const std::uint32_t channel_voltage,
        _In_ const float attenuation_voltage,
        _In_ const std::uint32_t channel_current,
        _In_ const float attenuation_current)
    : _attenuation_current(attenuation_current),
        _attenuation_voltage(attenuation_voltage),
        _channel_current(channel_current),
        _channel_voltage(channel_voltage),
        _description(nullptr) {
    if (description == nullptr) {
        throw std::invalid_argument("The description of an oscilloscope-based "
            "sensor must not be null.");
    }
    if (this->_channel_current == this->_channel_voltage) {
        throw std::invalid_argument("The channel measuring voltage cannot be "
            "the same as the one measuring current.");
    }

    this->_description = ::wcsdup(description);
    if (this->_description == nullptr) {
        throw std::bad_alloc();
    }
}


/*
 * ...::oscilloscope_sensor_definition
 */
visus::power_overwhelming::oscilloscope_sensor_definition::oscilloscope_sensor_definition(
        _In_ const oscilloscope_sensor_definition& rhs) : _description(nullptr) {
    *this = rhs;
}


/*
 * ...::~oscilloscope_sensor_definition
 */
visus::power_overwhelming::oscilloscope_sensor_definition::~oscilloscope_sensor_definition(
        void) {
    assert(this->_description != nullptr);
    ::free(this->_description);
}


/*
 * visus::power_overwhelming::oscilloscope_sensor_definition::operator =
 */
visus::power_overwhelming::oscilloscope_sensor_definition&
visus::power_overwhelming::oscilloscope_sensor_definition::operator =(
        _In_ const oscilloscope_sensor_definition& rhs) {
    if (this != std::addressof(rhs)) {
        this->_attenuation_current = rhs._attenuation_current;
        this->_attenuation_voltage = rhs._attenuation_voltage;
        this->_channel_current = rhs._channel_current;
        this->_channel_voltage = rhs._channel_voltage;

        this->_description = ::wcsdup(rhs._description);
        if (this->_description == nullptr) {
            throw std::bad_alloc();
        }
    }

    return *this;
}
