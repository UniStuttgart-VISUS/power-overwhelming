// <copyright file="tinkerforge_scope.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <array>
#include <cinttypes>
#include <string>

#include <ip_connection.h>


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// Container for information about the connected bricklets.
    /// </summary>
    class tinkerforge_bricklet final {

    public:

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        tinkerforge_bricklet(void);

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="uid"></param>
        /// <param name="connected_uid"></param>
        /// <param name="position"></param>
        /// <param name="hardware_version"></param>
        /// <param name="firmware_version"></param>
        /// <param name="device_identifier"></param>
        tinkerforge_bricklet(const std::string& uid,
            const std::string& connected_uid, const char position,
            const std::uint8_t hardware_version[3],
            const std::uint8_t firmware_version[3],
            const std::uint16_t device_identifier);

        /// <summary>
        /// Gets the type of the device.
        /// </summary>
        inline std::uint16_t device_type(void) const noexcept {
            return this->_device_type;
        }

        /// <summary>
        /// Gets the version of the firmware.
        /// </summary>
        inline const std::array<std::uint8_t, 3>& firmware_version(
                void) const noexcept {
            return this->_firmware_version;
        };

        /// <summary>
        /// Gets the version of the hardware.
        /// </summary>
        inline const std::array<std::uint8_t, 3>& hardware_version(
                void) const noexcept {
            return this->_hardware_version;
        };

        /// <summary>
        /// Gets the slot via which the bricklet is connected to
        /// <see cref="via" />.
        /// </summary>
        inline char position(void) const noexcept {
            return this->_position;
        }

        /// <summary>
        /// Gets the UID of the bricklet.
        /// </summary>
        inline const std::string& uid(void) const noexcept {
            return this->_uid;
        }

        /// <summary>
        /// Gets the UID of the brick which serves as connection point for the
        /// bricklet.
        /// </summary>
        inline const std::string& via(void) const noexcept {
            return this->_via;
        }

    private:

        std::uint16_t _device_type;
        std::array<std::uint8_t, 3> _firmware_version;
        std::array<std::uint8_t, 3> _hardware_version;
        char _position;
        std::string _uid;
        std::string _via;
    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
