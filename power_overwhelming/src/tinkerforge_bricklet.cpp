// <copyright file="tinkerforge_bricklet.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "tinkerforge_bricklet.h"

#include <algorithm>


/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_bricklet::tinkerforge_bricklet
 */
PWROWG_DETAIL_NAMESPACE::tinkerforge_bricklet::tinkerforge_bricklet(void)
        : _device_type(0), _position('\0') {
    std::fill(this->_firmware_version.begin(), this->_firmware_version.end(),
        static_cast<std::uint8_t>(0));
    std::fill(this->_hardware_version.begin(), this->_hardware_version.end(),
        static_cast<std::uint8_t>(0));
}


/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_bricklet::tinkerforge_bricklet
 */
PWROWG_DETAIL_NAMESPACE::tinkerforge_bricklet::tinkerforge_bricklet(
        const std::string& uid, const std::string&connected_uid,
        const char position, const std::uint8_t hardware_version[3],
        const std::uint8_t firmware_version[3],
        const std::uint16_t device_identifier)
    : _device_type(device_identifier), _position(position), _uid(uid),
        _via(connected_uid) {
    std::copy(firmware_version, firmware_version + 3,
        this->_firmware_version.begin());
    std::copy(hardware_version, hardware_version + 3,
        this->_hardware_version.begin());
}
