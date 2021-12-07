// <copyright file="tinkerforge_sensor_impl.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "tinkerforge_sensor_impl.h"

#include <cassert>

#include "convert_string.h"
#include "tinkerforge_exception.h"


/*
 * ..::tinkerforge_sensor_impl::current_callback
 */
void CALLBACK
visus::power_overwhelming::detail::tinkerforge_sensor_impl::current_callback(
    const std::int32_t current, void *data) {
    assert(data != nullptr);
    auto that = static_cast<tinkerforge_sensor_impl *>(data);
    that->current_buffer[get_write_buffer_index(that->current_state)];
    swap_write_buffer(that->current_state);
}


/*
 * ...::tinkerforge_sensor_impl::power_callback
 */
void CALLBACK
visus::power_overwhelming::detail::tinkerforge_sensor_impl::power_callback(
        const std::int32_t power, void *data) {
    assert(data != nullptr);
    auto that = static_cast<tinkerforge_sensor_impl *>(data);

}


/*
 * ...::tinkerforge_sensor_impl::voltage_callback
 */
void CALLBACK
visus::power_overwhelming::detail::tinkerforge_sensor_impl::voltage_callback(
        const std::int32_t voltage, void *data) {
    assert(data != nullptr);
    auto that = static_cast<tinkerforge_sensor_impl *>(data);

}


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

    // Setup the triple buffers.
    initialise_triple_buffer_state(this->current_state);
}


/*
 * ...::detail::tinkerforge_sensor_impl::~tinkerforge_sensor_impl
 */
visus::power_overwhelming::detail::tinkerforge_sensor_impl::~tinkerforge_sensor_impl(
        void) {
    ::voltage_current_v2_destroy(&this->bricklet);
}


/*
 * visus::power_overwhelming::detail::tinkerforge_sensor_impl::disable_callbacks
 */
void visus::power_overwhelming::detail::tinkerforge_sensor_impl::disable_callbacks(
        void) {
    {
        auto status = ::voltage_current_v2_set_current_callback_configuration(
            &this->bricklet, 0, false, 'x', 0, 0);
        if (status < 0) {
            throw tinkerforge_exception(status);
        }
    }

    {
        auto status = ::voltage_current_v2_set_power_callback_configuration(
            &this->bricklet, 0, false, 'x', 0, 0);
        if (status < 0) {
            throw tinkerforge_exception(status);
        }
    }

    {
        auto status = ::voltage_current_v2_set_voltage_callback_configuration(
            &this->bricklet, 0, false, 'x', 0, 0);
        if (status < 0) {
            throw tinkerforge_exception(status);
        }
    }
}


/*
 * ...::tinkerforge_sensor_impl::enable_callbacks
 */
void visus::power_overwhelming::detail::tinkerforge_sensor_impl::enable_callbacks(
        const std::int32_t period) {
    ::voltage_current_v2_register_callback(&this->bricklet,
        VOLTAGE_CURRENT_V2_CALLBACK_CURRENT,
        reinterpret_cast<void (*)(void)>(current_callback),
        this);

    {
        auto status = ::voltage_current_v2_set_current_callback_configuration(
            &this->bricklet, period, false, 'x', 0, 0);
        if (status < 0) {
            throw tinkerforge_exception(status);
        }
    }

    ::voltage_current_v2_register_callback(&this->bricklet,
        VOLTAGE_CURRENT_V2_CALLBACK_POWER,
        reinterpret_cast<void (*)(void)>(power_callback),
        this);

    {
        auto status = ::voltage_current_v2_set_power_callback_configuration(
            &this->bricklet, period, false, 'x', 0, 0);
        if (status < 0) {
            throw tinkerforge_exception(status);
        }
    }

    ::voltage_current_v2_register_callback(&this->bricklet,
        VOLTAGE_CURRENT_V2_CALLBACK_VOLTAGE,
        reinterpret_cast<void (*)(void)>(voltage_callback),
        this);

    {
        auto status = ::voltage_current_v2_set_voltage_callback_configuration(
            &this->bricklet, period, false, 'x', 0, 0);
        if (status < 0) {
            throw tinkerforge_exception(status);
        }
    }
}
