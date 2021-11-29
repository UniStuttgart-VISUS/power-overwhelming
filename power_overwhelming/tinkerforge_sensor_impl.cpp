// <copyright file="tinkerforge_sensor_impl.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "tinkerforge_sensor_impl.h"

#include <cassert>

#include "convert_string.h"


/*
 * ...::detail::tinkerforge_sensor_impl::tinkerforge_sensor_impl
 */
visus::power_overwhelming::detail::tinkerforge_sensor_impl::tinkerforge_sensor_impl(
        const std::string& host, const std::uint16_t port,
        const char *uid)
        : scope(host, port) {
    // Note that there is a delicate balance in what is done where and when in
    // this constructor: If we enter the body, the scope will have a valid
    // connection to a master brick. Otherwise, its constructor would have
    // thrown. As the scope has been constructed in the initialiser, it will
    // also be destructed if the constructor body throws. Therefore, it is
    // safe to throw if the 'uid' is invalid. However, if one would throw
    // after the bricklet has been created, there would be a memory leak,
    // because the destructor will not be called as the object has never been
    // constructed. This is the reason why the 'sensor_name' is create before
    // the bricklet: creating the string might throw std::bad_alloc and
    // std::system_error.
    if (uid == nullptr) {
        throw std::invalid_argument("The UID of the voltage/current bricklet "
            "must not be null.");
    }

    this->sensor_name = L"Tinkerforge/" + convert_string(host) + L":"
        + std::to_wstring(port) + L"/" + convert_string(uid);

    ::voltage_current_v2_create(&this->bricklet, uid, this->scope);
}


/*
 * ...::detail::tinkerforge_sensor_impl::~tinkerforge_sensor_impl
 */
visus::power_overwhelming::detail::tinkerforge_sensor_impl::~tinkerforge_sensor_impl(
        void) {
    ::voltage_current_v2_destroy(&this->bricklet);
}
