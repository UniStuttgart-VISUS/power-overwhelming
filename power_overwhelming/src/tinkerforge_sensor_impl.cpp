// <copyright file="tinkerforge_sensor_impl.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "tinkerforge_sensor_impl.h"

#include <algorithm>
#include <cassert>
#include <numeric>

#include "power_overwhelming/convert_string.h"

#include "tinkerforge_exception.h"
#include "timestamp.h"


#if !defined(CALLBACK)
#define CALLBACK
#endif /* !defined(CALLBACK) */


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// The callback to be invoked for incoming asynchronous current
    /// readings.
    /// </summary>
    /// <param name="current"></param>
    /// <param name="data"></param>
    void CALLBACK current_callback(const std::int32_t current, void *data) {
        assert(data != nullptr);
        auto that = static_cast<tinkerforge_sensor_impl *>(data);
        std::lock_guard<decltype(that->async_lock)> l(that->async_lock);
        const auto ts = create_timestamp(that->async_sampling.resolution());
        that->async_data[0] = static_cast<measurement::value_type>(current)
            / static_cast<measurement::value_type>(1000);
        that->invoke_callback(ts);   // TODO: Do we really want to invoke directly? How do we detect a consistent state?
    }

    /// <summary>
    /// The callback to be invoked for incoming asynchronous power
    /// readings.
    /// </summary>
    /// <param name="power"></param>
    /// <param name="data"></param>
    void CALLBACK power_callback(const std::int32_t power, void *data) {
        assert(data != nullptr);
        auto that = static_cast<tinkerforge_sensor_impl *>(data);
        std::lock_guard<decltype(that->async_lock)> l(that->async_lock);
        const auto ts = create_timestamp(that->async_sampling.resolution());
        that->async_data[1] = static_cast<measurement::value_type>(power)
            / static_cast<measurement::value_type>(1000);
        that->invoke_callback(ts);   // TODO: Do we really want to invoke directly? How do we detect a consistent state?
    }

    /// <summary>
    /// The callback to be invoked for incoming asynchronous power
    /// readings from our modified firmware.
    /// </summary>
    /// <param name="power"></param>
    /// <param name="time"></param>
    /// <param name="data"></param>
    void CALLBACK power_time_callback(const std::int32_t power,
            const std::uint32_t time, void *data) {
#if defined(CUSTOM_TINKERFORGE_FIRMWARE)
        assert(data != nullptr);
        auto that = static_cast<tinkerforge_sensor_impl *>(data);
        std::lock_guard<decltype(that->async_lock)> l(that->async_lock);
        const auto ts = that->time_xlate(time,
            that->async_sampling.resolution(),
            that->bricklet);
        //auto wall_time = create_timestamp(that->async_sampling.resolution());
        //::OutputDebugStringW((that->sensor_name + L" " + std::to_wstring(wall_time)
        //    + L" " + std::to_wstring(time)
        //    + L" " + std::to_wstring(wall_time - ts)
        //    + L"\r\n").c_str());
        that->async_data[1] = static_cast<measurement::value_type>(power)
            / static_cast<measurement::value_type>(1000);
        that->invoke_callback(ts);
#else /* defined(CUSTOM_TINKERFORGE_FIRMWARE) */
        power_callback(power, data);
#endif /* defined(CUSTOM_TINKERFORGE_FIRMWARE) */
    }

    /// <summary>
    /// The callback to be invoked for incoming asynchronous voltage
    /// readings.
    /// </summary>
    /// <param name="power"></param>
    /// <param name="data"></param>
    void CALLBACK voltage_callback(const std::int32_t voltage, void *data) {
        assert(data != nullptr);
        auto that = static_cast<tinkerforge_sensor_impl *>(data);
        std::lock_guard<decltype(that->async_lock)> l(that->async_lock);
        const auto ts = create_timestamp(that->async_sampling.resolution());
        that->async_data[2] = static_cast<measurement::value_type>(voltage)
            / static_cast<measurement::value_type>(1000);
        that->invoke_callback(ts);   // TODO: Do we really want to invoke directly? How do we detect a consistent state?
    }

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */


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
 * ...::detail::tinkerforge_sensor_impl::tinkerforge_sensor_impl
 */
visus::power_overwhelming::detail::tinkerforge_sensor_impl::tinkerforge_sensor_impl(
        const std::string& host, const std::uint16_t port,
        const char *uid)
        : scope(host, port), uid(uid) {
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

    // TODO: this is too slow, only set timing in reset.
//#if defined(CUSTOM_TINKERFORGE_FIRMWARE)
//    this->time_xlate.reset(this->bricklet);
//#endif /* defined(CUSTOM_TINKERFORGE_FIRMWARE) */
}


/*
 * ...::detail::tinkerforge_sensor_impl::~tinkerforge_sensor_impl
 */
visus::power_overwhelming::detail::tinkerforge_sensor_impl
::~tinkerforge_sensor_impl(void) {
    // Make sure to disable the callbacks in case the user forgot to do
    // so before destroying the sensor. Note that we do not hold the lock at
    // this point, which enables all callbacks that are already running to
    // exit asap.
    this->disable_callbacks();

    // Make sure that we do not destroy the sensor while asnychronous data are
    // written. This will block until the writer exited.
    // TODO: This is only semi-safe for cases where only one calback is running. We need to fix that some time, but for now, we usually only
    // run power callbacks, so it is somewhat OK ...
    std::lock_guard<decltype(this->async_lock)> l(this->async_lock);

    ::voltage_current_v2_destroy(&this->bricklet);
}


/*
 * visus::power_overwhelming::detail::tinkerforge_sensor_impl::disable_callbacks
 */
void visus::power_overwhelming::detail::tinkerforge_sensor_impl::disable_callbacks(
        void) {
    // First of all, disable the callbacks that run in the communication thread
    // of the Tinkerforge device. Note that we must *not* clear the context,
    // because the whole registration is not thread-safe. We therefore have to
    // assume that the callback might have already been copied to a local
    // variable whereas the context has not. In this case, we would risk
    // invoking a valid callback with an invalid context if we set the context
    // to nullptr, too.
    ::voltage_current_v2_register_callback(&this->bricklet,
        VOLTAGE_CURRENT_V2_CALLBACK_CURRENT,
        nullptr,
        this);
    ::voltage_current_v2_register_callback(&this->bricklet,
        VOLTAGE_CURRENT_V2_CALLBACK_POWER,
        nullptr,
        this);
    ::voltage_current_v2_register_callback(&this->bricklet,
        VOLTAGE_CURRENT_V2_CALLBACK_VOLTAGE,
        nullptr,
        this);

    if (this->has_internal_time()) {
        ::voltage_current_v2_register_callback(&this->bricklet,
            VOLTAGE_CURRENT_V2_CALLBACK_POWER,
            nullptr,
            this);
    }

    // At this point, we can be sure that any callback can run only once (if it
    // was already running). Therefore, we now prevent the hardware from pushing
    // new data to the software. Disabling the following does not suffice to
    // stop valid callbacks from being invoked, because these calls might have
    // already been invoked by queued data that the bricklet has pushed to the
    // host code.
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

    if (this->has_internal_time()) {
        auto status = ::voltage_current_v2_set_power_time_callback_configuration(
            &this->bricklet, false);
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
    if (this->has_internal_time()) {
        ::voltage_current_v2_register_callback(&this->bricklet,
            VOLTAGE_CURRENT_V2_CALLBACK_POWER_TIME,
            reinterpret_cast<void (*)(void)>(power_time_callback),
            this);

        auto status = ::voltage_current_v2_set_power_time_callback_configuration(
            &this->bricklet, true);
        if (status < 0) {
            throw tinkerforge_exception(status);
        }

    } else {
        ::voltage_current_v2_register_callback(&this->bricklet,
            VOLTAGE_CURRENT_V2_CALLBACK_POWER,
            reinterpret_cast<void (*)(void)>(power_callback),
            this);

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
