// <copyright file="daqmx_current_channel.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/daqmx_current_channel.h"


/*
 * PWROWG_NAMESPACE::daqmx_current_channel::daqmx_current_channel
 */
PWROWG_NAMESPACE::daqmx_current_channel::daqmx_current_channel(
        _In_z_ const wchar_t *channel)
        : daqmx_channel(channel), _shunt_resistor_value(0.0) {
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
    this->_shunt_resistor_location = daqmx_shunt_resistor_location::standard;
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
}


/*
 * PWROWG_NAMESPACE::daqmx_current_channel::daqmx_current_channel
 */
PWROWG_NAMESPACE::daqmx_current_channel::daqmx_current_channel(
        _In_z_ const char *channel)
        : daqmx_channel(channel), _shunt_resistor_value(0.0) {
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
    this->_shunt_resistor_location = daqmx_shunt_resistor_location::standard;
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
}
