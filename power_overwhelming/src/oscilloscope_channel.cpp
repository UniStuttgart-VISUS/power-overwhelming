// <copyright file="oscilloscope_channel.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/oscilloscope_channel.h"

#include <stdexcept>

#include "string_functions.h"


/*
 * visus::power_overwhelming::oscilloscope_channel::oscilloscope_channel
 */
visus::power_overwhelming::oscilloscope_channel::oscilloscope_channel(
        _In_ const std::uint32_t channel)
        : _bandwidth(oscilloscope_channel_bandwidth::full),
        _channel(channel),
        _coupling(oscilloscope_channel_coupling::direct_current_limit),
        _decimation_mode(oscilloscope_decimation_mode::sample),
        _gain(oscilloscope_quantity(10.0f, "V")),
        _polarity(oscilloscope_channel_polarity::normal),
        _state(false) { }
