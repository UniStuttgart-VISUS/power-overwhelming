// <copyright file="oscilloscope_channel.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/oscilloscope_channel.h"

#include <stdexcept>

#include "string_functions.h"


/*
 * visus::power_overwhelming::oscilloscope_channel::oscilloscope_channel
 */
visus::power_overwhelming::oscilloscope_channel::oscilloscope_channel(
        _In_ const channel_type channel)
    : _attenuation(oscilloscope_quantity(0.0f)),
        _bandwidth(oscilloscope_channel_bandwidth::full),
        _channel(channel),
        _coupling(oscilloscope_channel_coupling::direct_current_limit),
        _decimation_mode(oscilloscope_decimation_mode::sample),
        _polarity(oscilloscope_channel_polarity::normal),
        _state(false) { }


/*
 * visus::power_overwhelming::oscilloscope_channel::oscilloscope_channel
 */
visus::power_overwhelming::oscilloscope_channel::oscilloscope_channel(
        _In_ const channel_type channel,
        _In_ const oscilloscope_channel& channel_template) 
    : _attenuation(channel_template._attenuation),
        _bandwidth(channel_template._bandwidth),
        _channel(channel),
        _coupling(channel_template._coupling),
        _decimation_mode(channel_template._decimation_mode),
        _polarity(channel_template._polarity),
        _state(channel_template._state) { }


/*
 * visus::power_overwhelming::oscilloscope_channel::attenuation
 */
visus::power_overwhelming::oscilloscope_channel&
visus::power_overwhelming::oscilloscope_channel::attenuation(
        _In_ const oscilloscope_quantity& attenuation) {
    if ((attenuation.value() != 0.0f) && (::strlen(attenuation.unit()) == 0)) {
        throw std::invalid_argument("The unit of the attenuation can only be "
            "empty if the value is zero.");
    }

    this->_attenuation = attenuation;
    return *this;
}
