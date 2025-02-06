// <copyright file="tinerforge_configuration.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/tinkerforge_configuration.h"

#include <algorithm>
#include <stdexcept>

#include "visus/pwrowg/convert_string.h"

#include "string_functions.h"


/// <summary>
/// The default host on which brickd is assumed to run.
/// </summary>
static constexpr const char *default_host = "localhost";


/// <summary>
/// The default port on which brickd is assumed to listen on.
/// </summary>
static constexpr const std::uint16_t default_port = 4223;


/*
 * PWROWG_NAMESPACE::tinkerforge_configuration::end_point::end_point
 */
PWROWG_NAMESPACE::tinkerforge_configuration::end_point::end_point(void)
        : _port(default_port) {
    PWROWG_DETAIL_NAMESPACE::safe_assign(this->_name, default_host);
}


/*
 * PWROWG_NAMESPACE::tinkerforge_configuration::end_point::end_point
 */
PWROWG_NAMESPACE::tinkerforge_configuration::end_point::end_point(
        _In_z_ const char *host)
        : _port(default_port) {
    PWROWG_DETAIL_NAMESPACE::safe_assign(this->_name, host);
}


/*
 * PWROWG_NAMESPACE::tinkerforge_configuration::end_point::end_point
 */
PWROWG_NAMESPACE::tinkerforge_configuration::end_point::end_point(
        _In_z_ const char *host,
        _In_ const std::uint16_t port)
        : _port(port) {
    PWROWG_DETAIL_NAMESPACE::safe_assign(this->_name, host);
}


/*
 * PWROWG_NAMESPACE::tinkerforge_configuration::id
 */
const PWROWG_NAMESPACE::guid PWROWG_NAMESPACE::tinkerforge_configuration::id(
    0x2A24F596, 0xC0C0, 0x4395, 0x81CD, 0x92, 0x42, 0xFD, 0xA9, 0xAC, 0xF1);


/*
 * PWROWG_NAMESPACE::tinkerforge_configuration::tinkerforge_configuration
 */
PWROWG_NAMESPACE::tinkerforge_configuration::tinkerforge_configuration(void) {
    this->add_end_point(end_point());
}


/*
 * PWROWG_NAMESPACE::tinkerforge_configuration::~tinkerforge_configuration
 */
PWROWG_NAMESPACE::tinkerforge_configuration::~tinkerforge_configuration(void) {
    this->destroy_end_points();
}


/*
 * PWROWG_NAMESPACE::tinkerforge_configuration::add_end_point
 */
PWROWG_NAMESPACE::tinkerforge_configuration&
PWROWG_NAMESPACE::tinkerforge_configuration::add_end_point(
        _In_ const end_point&address) {
    const auto offset = this->_end_points.size();

    this->_end_points.grow(this->_end_points.size() + sizeof(end_point));
    new (this->_end_points.as<end_point>(offset)) end_point(address);

    return *this;
}


/*
 * PWROWG_NAMESPACE::tinkerforge_configuration::count_end_points
 */
std::size_t PWROWG_NAMESPACE::tinkerforge_configuration::count_end_points(
        void) const noexcept {
    return this->_end_points.size() / sizeof(end_point);
}


/*
 * PWROWG_NAMESPACE::tinkerforge_configuration::end_points
 */
PWROWG_NAMESPACE::tinkerforge_configuration&
PWROWG_NAMESPACE::tinkerforge_configuration::end_points(
        _In_reads_(cnt) end_point *addresses,
        _In_ const std::size_t cnt) {
    if (addresses == nullptr) {
        throw std::invalid_argument("A valid array of Brickd addresses must be "
            "provided.");
    }
    if (cnt < 1) {
        throw std::invalid_argument("At least one Brickd address must be "
            "provided.");
    }

    this->destroy_end_points();

    this->_end_points.resize(cnt * sizeof(end_point));

    for (std::size_t i = 0; i < cnt; ++i) {
        const auto offset = i * sizeof(end_point);
        new (this->_end_points.as<end_point>(offset)) end_point(addresses[i]);
    }

    return *this;
}


/*
 * PWROWG_NAMESPACE::tinkerforge_configuration::destroy_end_points
 */
void PWROWG_NAMESPACE::tinkerforge_configuration::destroy_end_points(void) {
    for (std::size_t i = 0; i < this->count_end_points(); ++i) {
        const auto offset = i * sizeof(end_point);
        this->_end_points.as<end_point>(offset)->~end_point();
    }
}
