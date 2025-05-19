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
#include "tinkerforge_bricklet.h"
#include "tinkerforge_exception.h"
#include "tinkerforge_scope.h"


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
PWROWG_NAMESPACE::tinkerforge_configuration::tinkerforge_configuration(void)
        : _averaging(tinkerforge_sample_averaging::average_of_4),
        _cnt_end_points(0),
        _current_conversion_time(tinkerforge_conversion_time::microseconds_588),
        _end_points(nullptr),
        _timeout(5000),
        _voltage_conversion_time(tinkerforge_conversion_time::microseconds_588) {
    this->add_end_point(end_point());
}


/*
 * PWROWG_NAMESPACE::tinkerforge_configuration::tinkerforge_configuration
 */
PWROWG_NAMESPACE::tinkerforge_configuration::tinkerforge_configuration(
        _In_ const tinkerforge_configuration& rhs)
    : _averaging(rhs._averaging),
        _cnt_end_points(0),
        _current_conversion_time(rhs._current_conversion_time),
        _end_points(nullptr),
        _timeout(rhs._timeout),
        _voltage_conversion_time(rhs._voltage_conversion_time) {
    this->end_points(rhs._end_points, rhs._cnt_end_points);
}


/*
 * PWROWG_NAMESPACE::tinkerforge_configuration::~tinkerforge_configuration
 */
PWROWG_NAMESPACE::tinkerforge_configuration::~tinkerforge_configuration(void) {
    delete[] this->_end_points;
}


/*
 * PWROWG_NAMESPACE::tinkerforge_configuration::add_end_point
 */
PWROWG_NAMESPACE::tinkerforge_configuration&
PWROWG_NAMESPACE::tinkerforge_configuration::add_end_point(
        _In_ const end_point& address) {
    assert((this->_cnt_end_points == 0) || (this->_end_points != nullptr));
    const auto begin = this->_end_points;
    const auto end = this->_end_points + this->_cnt_end_points;

    // Reallocate and copy existing end points.
    this->_end_points = new end_point[++this->_cnt_end_points];
    std::copy(begin, end, this->_end_points);
    delete[] begin;

    // Add the new end point.
    this->_end_points[this->_cnt_end_points - 1] = address;

    return *this;
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

    if (this->_cnt_end_points != cnt) {
        delete[] this->_end_points;
        this->_cnt_end_points = cnt;
        this->_end_points = new end_point[this->_cnt_end_points];
    }

    std::copy(addresses, addresses + cnt, this->_end_points);

    return *this;
}


/*
 * PWROWG_NAMESPACE::tinkerforge_configuration::operator =
 */
PWROWG_NAMESPACE::tinkerforge_configuration&
PWROWG_NAMESPACE::tinkerforge_configuration::operator =(
        _In_ const tinkerforge_configuration& rhs) {
    if (this != std::addressof(rhs)) {
        this->_averaging = rhs._averaging;
        this->_current_conversion_time = rhs._current_conversion_time;
        this->end_points(rhs._end_points, rhs._cnt_end_points);
        this->_timeout = rhs._timeout;
        this->_voltage_conversion_time = rhs._voltage_conversion_time;
    }

    return *this;
}
