// <copyright file="daqmx_channel.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/daqmx_channel.h"

#include <stdexcept>

#include "visus/pwrowg/convert_string.h"
#include "visus/pwrowg/string_functions.h"


/*
 * PWROWG_NAMESPACE::daqmx_channel::name
 */
_Ret_z_ const char *PWROWG_NAMESPACE::daqmx_channel::name(void) const noexcept {
    auto retval = this->_name.as<char>();
    return (retval != nullptr) ? retval : "";
}


/*
 * PWROWG_NAMESPACE::daqmx_channel::daqmx_channel
 */
PWROWG_NAMESPACE::daqmx_channel::daqmx_channel(
        _In_z_ const wchar_t *channel)
        : _max_value(0.0), _min_value(0.0) {
    if (channel == nullptr) {
        throw std::invalid_argument("A valid physical channel must be "
            "specified.");
    }

    auto c = convert_string<char>(channel);
    detail::safe_assign(this->_channel, c);

#if defined(POWER_OVERWHELMING_WITH_DAQMX)
    this->_terminal_configuration = daqmx_terminal_configuration::standard;
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
}


/*
 * PWROWG_NAMESPACE::daqmx_channel::daqmx_channel
 */
PWROWG_NAMESPACE::daqmx_channel::daqmx_channel(
        _In_z_ const char *channel)
        : _max_value(0.0), _min_value(0.0) {
    if (channel == nullptr) {
        throw std::invalid_argument("A valid physical channel must be "
            "specified.");
    }

    detail::safe_assign(this->_channel, channel);

#if defined(POWER_OVERWHELMING_WITH_DAQMX)
    this->_terminal_configuration = daqmx_terminal_configuration::standard;
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
}


/*
 * PWROWG_NAMESPACE::daqmx_channel::name
 */
void PWROWG_NAMESPACE::daqmx_channel::name(_In_z_ const wchar_t *value) {
    if (value == nullptr) {
        throw std::invalid_argument("A valid name must be specified.");
    }

    auto c = convert_string<char>(value);
    detail::safe_assign(this->_name, c);
}


/*
 * PWROWG_NAMESPACE::daqmx_channel::name
 */
void PWROWG_NAMESPACE::daqmx_channel::name(_In_z_ const char *value) {
    if (value == nullptr) {
        throw std::invalid_argument("A valid name must be specified.");
    }

    detail::safe_assign(this->_name, value);
}
