// <copyright file="tinkerforge_sensor_impl.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "tinkerforge_sensor_impl.h"

#include <cassert>

#include "power_overwhelming/convert_string.h"

#include "tinkerforge_exception.h"


/*
 * ..::tinkerforge_sensor_impl::current_callback
 */
void CALLBACK
visus::power_overwhelming::detail::tinkerforge_sensor_impl::current_callback(
        const std::int32_t current, void *data) {
    assert(data != nullptr);
    auto that = static_cast<tinkerforge_sensor_impl *>(data);
    const auto timestamp = create_timestamp(that->async_sampling.resolution());
    std::lock_guard<decltype(that->async_lock)> l(that->async_lock);
    that->async_data[0] = static_cast<measurement::value_type>(current)
        / static_cast<measurement::value_type>(1000);
    that->invoke_callback(timestamp);   // TODO: Do we really want to invoke directly? How do we detect a consistent state?
}


/*
 * visus::power_overwhelming::detail::tinkerforge_sensor_impl::get_sensor_name
 */
std::string
visus::power_overwhelming::detail::tinkerforge_sensor_impl::get_sensor_name(
        const std::string& host, const std::uint16_t port,
        const std::string& uid) {
    return std::string("Tinkerforge/") + host + ":" + std::to_string(port)
        + "/" + uid;
}


/*
 * ...::tinkerforge_sensor_impl::power_callback
 */
void CALLBACK
visus::power_overwhelming::detail::tinkerforge_sensor_impl::power_callback(
        const std::int32_t power, void *data) {
    assert(data != nullptr);
    auto that = static_cast<tinkerforge_sensor_impl *>(data);
    const auto timestamp = create_timestamp(that->async_sampling.resolution());
    std::lock_guard<decltype(that->async_lock)> l(that->async_lock);
    that->async_data[1] = static_cast<measurement::value_type>(power)
        / static_cast<measurement::value_type>(1000);
    that->invoke_callback(timestamp);   // TODO: Do we really want to invoke directly? How do we detect a consistent state?
}


/*
 * ...::tinkerforge_sensor_impl::voltage_callback
 */
void CALLBACK
visus::power_overwhelming::detail::tinkerforge_sensor_impl::voltage_callback(
        const std::int32_t voltage, void *data) {
    assert(data != nullptr);
    auto that = static_cast<tinkerforge_sensor_impl *>(data);
    const auto timestamp = create_timestamp(that->async_sampling.resolution());
    std::lock_guard<decltype(that->async_lock)> l(that->async_lock);
    that->async_data[2] = static_cast<measurement::value_type>(voltage)
        / static_cast<measurement::value_type>(1000);
    that->invoke_callback(timestamp);   // TODO: Do we really want to invoke directly? How do we detect a consistent state?
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

    this->sensor_name = power_overwhelming::convert_string<wchar_t>(
        tinkerforge_sensor_impl::get_sensor_name(host, port, uid));

    ::voltage_current_v2_create(&this->bricklet, uid, this->scope);

    // Initialise the asynchronous measurement buffer with in valid data.
    std::fill(this->async_data.begin(), this->async_data.end(),
        measurement::invalid_value);
}


/*
 * ...::detail::tinkerforge_sensor_impl::~tinkerforge_sensor_impl
 */
visus::power_overwhelming::detail::tinkerforge_sensor_impl::~tinkerforge_sensor_impl(
        void) {
    // Make sure to disable the callbacks in case the user forgot to do
    // so before destroying the sensor.
    this->disable_callbacks();

    // Make sure that we do not destroy the sensor while asnychronous data are
    // written. This will block until the writer exited.
    std::lock_guard<decltype(this->async_lock)> l(this->async_lock);

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
    this->enable_current_callback(period);
    this->enable_power_callback(period);
    this->enable_voltage_callback(period);
}


/*
 * ...::detail::tinkerforge_sensor_impl::enable_current_callback
 */
void visus::power_overwhelming::detail::tinkerforge_sensor_impl
::enable_current_callback(const std::int32_t period) {
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
}


/*
 * ...::detail::tinkerforge_sensor_impl::enable_power_callback
 */
void visus::power_overwhelming::detail::tinkerforge_sensor_impl
::enable_power_callback(const std::int32_t period) {
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
}


/*
 * ...::detail::tinkerforge_sensor_impl::enable_voltage_callback
 */
void visus::power_overwhelming::detail::tinkerforge_sensor_impl
::enable_voltage_callback(const std::int32_t period) {
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


/*
 * visus::power_overwhelming::detail::tinkerforge_sensor_impl::invoke_callback
 */
void visus::power_overwhelming::detail::tinkerforge_sensor_impl::invoke_callback(
        const timestamp_type timestamp) {
    auto current = this->async_data[0];
    auto power = this->async_data[1];
    auto voltage = this->async_data[2];
    measurement_data measurement(timestamp, voltage, current, power);

    if (measurement) {
        this->async_sampling.deliver(this->sensor_name.c_str(), measurement);
    }
}
