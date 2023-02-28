// <copyright file="tinkerforge_scope.cpp" company="Visualisierungsinstitut der Universit�t Stuttgart">
// Copyright � 2021 Visualisierungsinstitut der Universit�t Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph M�ller</author>

#include "tinkerforge_bricklet.h"

#include <algorithm>


/*
 * visus::power_overwhelming::detail::tinkerforge_bricklet::tinkerforge_bricklet
 */
visus::power_overwhelming::detail::tinkerforge_bricklet::tinkerforge_bricklet(void)
        : _device_type(0), _position('\0') {
    std::fill(this->_firmware_version.begin(), this->_firmware_version.end(),
        static_cast<std::uint8_t>(0));
    std::fill(this->_hardware_version.begin(), this->_hardware_version.end(),
        static_cast<std::uint8_t>(0));
}


/*
 * visus::power_overwhelming::detail::tinkerforge_bricklet::tinkerforge_bricklet
 */
visus::power_overwhelming::detail::tinkerforge_bricklet::tinkerforge_bricklet(
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
