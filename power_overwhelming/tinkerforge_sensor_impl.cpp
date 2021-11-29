// <copyright file="tinkerforge_sensor_impl.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "tinkerforge_sensor_impl.h"

#include <cassert>


/*
 * ...::detail::tinkerforge_sensor_impl::tinkerforge_sensor_impl
 */
visus::power_overwhelming::detail::tinkerforge_sensor_impl::tinkerforge_sensor_impl(
        const std::string& host, const std::uint16_t port,
        const char *uid)
        : scope(host, port) {
    assert(uid != nullptr);
    ::voltage_current_v2_create(&this->bricklet, uid, this->scope);
}


/*
 * ...::detail::tinkerforge_sensor_impl::~tinkerforge_sensor_impl
 */
visus::power_overwhelming::detail::tinkerforge_sensor_impl::~tinkerforge_sensor_impl(
        void) {
    ::voltage_current_v2_destroy(&this->bricklet);
}
