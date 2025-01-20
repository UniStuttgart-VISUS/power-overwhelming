// <copyright file="tinerforge_configuration.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/tinkerforge_configuration.h"

#include "visus/pwrowg/convert_string.h"

#include "string_functions.h"


/*
 * PWROWG_NAMESPACE::tinkerforge_configuration::tinkerforge_configuration
 */
PWROWG_NAMESPACE::tinkerforge_configuration::tinkerforge_configuration(void)
        : _port(default_port), _source(default_source) {
    this->host(default_host);
}


/*
 * PWROWG_NAMESPACE::tinkerforge_configuration::host
 */
PWROWG_NAMESPACE::tinkerforge_configuration&
PWROWG_NAMESPACE::tinkerforge_configuration::host(_In_z_ const char *host) {
    PWROWG_DETAIL_NAMESPACE::safe_assign(this->_host, host);
    return *this;
}


/*
 * PWROWG_NAMESPACE::tinkerforge_configuration::host
 */
PWROWG_NAMESPACE::tinkerforge_configuration&
PWROWG_NAMESPACE::tinkerforge_configuration::host(_In_z_ const wchar_t *host) {
    PWROWG_DETAIL_NAMESPACE::safe_assign(this->_host,
        convert_string<wchar_t>(host));
    return *this;
}


/*
 * PWROWG_NAMESPACE::tinkerforge_configuration::port
 */
PWROWG_NAMESPACE::tinkerforge_configuration&
PWROWG_NAMESPACE::tinkerforge_configuration::port(
        _In_ const std::uint16_t port) noexcept {
    this->_port = port;
    return *this;
}


/*
 * PWROWG_NAMESPACE::tinkerforge_configuration::source
 */
PWROWG_NAMESPACE::tinkerforge_configuration&
PWROWG_NAMESPACE::tinkerforge_configuration::source(
        _In_ const source_type source) noexcept {
    this->_source = source;
    return *this;
}
