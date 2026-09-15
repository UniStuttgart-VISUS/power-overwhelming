// <copyright file="daqmx_sensor_definition.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/daqmx_sensor_definition.h"

#include <memory>
#include <type_traits>

#include "visus/pwrowg/convert_string.h"
#include "visus/pwrowg/daqmx_current_channel.h"
#include "visus/pwrowg/daqmx_power_channel.h"
#include "visus/pwrowg/daqmx_voltage_channel.h"
#include "visus/pwrowg/string_functions.h"


/*
 * PWROWG_NAMESPACE::daqmx_sensor_definition::daqmx_sensor_definition
 */
PWROWG_NAMESPACE::daqmx_sensor_definition::daqmx_sensor_definition(
        _In_ const daqmx_voltage_channel& voltage_channel,
        _In_ const daqmx_current_channel& current_channel,
        _In_opt_z_ const wchar_t *description)
    : _current_channel(new daqmx_current_channel(current_channel)),
        _power_channel(nullptr),
        _voltage_channel(new daqmx_voltage_channel(voltage_channel)),
        _voltage_for_current_channel(nullptr),
        _volt_per_ampere(0.0f) {
    detail::safe_assign(this->_description, description);
}


/*
 * PWROWG_NAMESPACE::daqmx_sensor_definition::daqmx_sensor_definition
 */
PWROWG_NAMESPACE::daqmx_sensor_definition::daqmx_sensor_definition(
        _In_ const daqmx_power_channel& power_channel,
        _In_opt_z_ const wchar_t *description)
    : _current_channel(nullptr),
        _power_channel(new daqmx_power_channel(power_channel)),
        _voltage_channel(nullptr),
        _voltage_for_current_channel(nullptr),
        _volt_per_ampere(0.0f) {
    detail::safe_assign(this->_description, description);
}


/*
 * PWROWG_NAMESPACE::daqmx_sensor_definition::daqmx_sensor_definition
 */
PWROWG_NAMESPACE::daqmx_sensor_definition::daqmx_sensor_definition(
        _In_ const daqmx_voltage_channel& voltage_channel,
        _In_ const daqmx_voltage_channel& current_channel,
        _In_ const double volt_per_ampere,
        _In_opt_z_ const wchar_t *description) 
    : _current_channel(nullptr),
        _power_channel(nullptr),
        _voltage_channel(new daqmx_voltage_channel(voltage_channel)),
        _voltage_for_current_channel(
            new daqmx_voltage_channel(current_channel)),
        _volt_per_ampere(volt_per_ampere) {
    detail::safe_assign(this->_description, description);
}


/*
 * PWROWG_NAMESPACE::daqmx_sensor_definition::daqmx_sensor_definition
 */
PWROWG_NAMESPACE::daqmx_sensor_definition::daqmx_sensor_definition(
        _In_ const daqmx_voltage_channel& channel,
        _In_opt_z_ const wchar_t *description) 
    : _current_channel(nullptr),
        _power_channel(nullptr),
        _voltage_channel(new daqmx_voltage_channel(channel)),
        _voltage_for_current_channel(nullptr),
        _volt_per_ampere(0.0f) {
    detail::safe_assign(this->_description, description);
}


/*
 * PWROWG_NAMESPACE::daqmx_sensor_definition::~daqmx_sensor_definition
 */
PWROWG_NAMESPACE::daqmx_sensor_definition::~daqmx_sensor_definition(
        void) noexcept {
    delete this->_current_channel;
    delete this->_power_channel;
    delete this->_voltage_channel;
    delete this->_voltage_for_current_channel;
}


/*
 * PWROWG_NAMESPACE::daqmx_sensor_definition::description
 */
PWROWG_NAMESPACE::daqmx_sensor_definition&
PWROWG_NAMESPACE::daqmx_sensor_definition::description(
        _In_opt_z_ const wchar_t *description) {
    detail::safe_assign(this->_description, description);
    return *this;
}


/*
 * PWROWG_NAMESPACE::daqmx_sensor_definition::operator =
 */
PWROWG_NAMESPACE::daqmx_sensor_definition&
PWROWG_NAMESPACE::daqmx_sensor_definition::operator =(
        _In_ const daqmx_sensor_definition& rhs) {
    static const auto cp = [](auto& d, const auto s) {
        typedef std::remove_pointer_t<std::decay_t<decltype(d)>> type;
        delete d;
        d = (s != nullptr) ? new type(*s) : nullptr;
    };

    if (this != std::addressof(rhs)) {
        cp(this->_current_channel, rhs._current_channel);
        this->_description = rhs._description;
        cp(this->_power_channel, rhs._power_channel);
        cp(this->_voltage_channel, rhs._voltage_channel);
        cp(this->_voltage_for_current_channel,
            rhs._voltage_for_current_channel);
        this->_volt_per_ampere = rhs._volt_per_ampere;
    }
    return *this;
}


/*
 * PWROWG_NAMESPACE::daqmx_sensor_definition::operator bool
 */
PWROWG_NAMESPACE::daqmx_sensor_definition::operator bool(
        void) const noexcept {
    const auto vc = ((this->_current_channel != nullptr)
        && (this->_voltage_channel != nullptr));
    const auto p = (this->_power_channel != nullptr);
    const auto vv = ((this->_voltage_channel != nullptr)
        && (this->_voltage_for_current_channel != nullptr));
    return (vc || p || vv);
}
