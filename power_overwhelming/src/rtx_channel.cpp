// <copyright file="rtx_channel.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/rtx_channel.h"

#include <stdexcept>

#include "string_functions.h"


/*
 * PWROWG_NAMESPACE::rtx_channel::rtx_channel
 */
PWROWG_NAMESPACE::rtx_channel::rtx_channel(_In_ const channel_type channel)
    : _attenuation(rtx_quantity(0.0f)),
        _bandwidth(rtx_channel_bandwidth::full),
        _channel(channel),
        _coupling(rtx_channel_coupling::direct_current_limit),
        _decimation_mode(rtx_decimation_mode::sample),
        _polarity(rtx_channel_polarity::normal),
        _state(false),
        _zero_adjust(false),
        _zero_adjust_offset(0.0f) { }


/*
 * PWROWG_NAMESPACE::rtx_channel::rtx_channel
 */
PWROWG_NAMESPACE::rtx_channel::rtx_channel(
        _In_ const channel_type channel,
        _In_ const rtx_channel& channel_template)
    : _attenuation(channel_template._attenuation),
        _bandwidth(channel_template._bandwidth),
        _channel(channel),
        _coupling(channel_template._coupling),
        _decimation_mode(channel_template._decimation_mode),
        _polarity(channel_template._polarity),
        _state(channel_template._state),
        _zero_adjust(channel_template._zero_adjust),
        _zero_adjust_offset(channel_template._zero_adjust_offset) { }


/*
 * PWROWG_NAMESPACE::rtx_channel::attenuation
 */
PWROWG_NAMESPACE::rtx_channel&
PWROWG_NAMESPACE::rtx_channel::attenuation(
        _In_ const rtx_quantity& attenuation) {
    if ((attenuation.value() != 0.0f) && (::strlen(attenuation.unit()) == 0)) {
        throw std::invalid_argument("The unit of the attenuation can only be "
            "empty if the value is zero.");
    }

    this->_attenuation = attenuation;
    return *this;
}


/*
 * PWROWG_NAMESPACE::rtx_channel::zero_adjust_offset
 */
PWROWG_NAMESPACE::rtx_channel&
PWROWG_NAMESPACE::rtx_channel::zero_adjust_offset(
        _In_ const float offset) noexcept {
    if (offset < -100.0f) {
        this->_zero_adjust_offset = -100.0f;
    } else if (offset > 100.0f) {
        this->_zero_adjust_offset = 100.0f;
    } else {
        this->_zero_adjust_offset = offset;
    }

    return *this;
}
