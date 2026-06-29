// <copyright file="daqmx_power_channel.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/daqmx_power_channel.h"

#include <stdexcept>

#include "visus/pwrowg/convert_string.h"
#include "visus/pwrowg/string_functions.h"


/*
 * PWROWG_NAMESPACE::daqmx_power_channel::daqmx_power_channel
 */
PWROWG_NAMESPACE::daqmx_power_channel::daqmx_power_channel(
        _In_z_ const wchar_t *voltage_channel,
        _In_z_ const wchar_t *current_channel)
    : daqmx_channel(voltage_channel),
        _current_max_value(0.0),
        _current_min_value(0.0),
        _shunt_resistor_value(0.0) {
    if (current_channel == nullptr) {
        throw std::invalid_argument("A valid physical channel must be "
            "specified.");
    }

    auto c = convert_string<char>(current_channel);
    detail::safe_assign(this->_current_channel, c);

#if defined(POWER_OVERWHELMING_WITH_DAQMX)
    this->_shunt_resistor_location = daqmx_shunt_resistor_location::standard;
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
}


/*
 * PWROWG_NAMESPACE::daqmx_power_channel::daqmx_power_channel
 */
PWROWG_NAMESPACE::daqmx_power_channel::daqmx_power_channel(
        _In_z_ const char *voltage_channel,
        _In_z_ const char *current_channel)
    : daqmx_channel(voltage_channel),
        _current_max_value(0.0),
        _current_min_value(0.0),
        _shunt_resistor_value(0.0) {
    if (current_channel == nullptr) {
        throw std::invalid_argument("A valid physical channel must be "
            "specified.");
    }

    detail::safe_assign(this->_current_channel, current_channel);

#if defined(POWER_OVERWHELMING_WITH_DAQMX)
    this->_shunt_resistor_location = daqmx_shunt_resistor_location::standard;
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
}
