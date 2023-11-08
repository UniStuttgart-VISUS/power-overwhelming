// <copyright file="tinkerforge_sensor_impl.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
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
        const auto timestamp = create_timestamp(that->async_sampling.resolution());
        std::lock_guard<decltype(that->async_lock)> l(that->async_lock);
        that->async_data[0] = static_cast<measurement::value_type>(current)
            / static_cast<measurement::value_type>(1000);
        that->invoke_callback(timestamp);   // TODO: Do we really want to invoke directly? How do we detect a consistent state?
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
        const auto timestamp = create_timestamp(that->async_sampling.resolution());
        std::lock_guard<decltype(that->async_lock)> l(that->async_lock);
        that->async_data[1] = static_cast<measurement::value_type>(power)
            / static_cast<measurement::value_type>(1000);
        that->invoke_callback(timestamp);   // TODO: Do we really want to invoke directly? How do we detect a consistent state?
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
        const auto timestamp = convert(timestamp_resolution::milliseconds,
            that->time_offset + time,
            that->async_sampling.resolution());
        //auto tt = create_timestamp(that->async_sampling.resolution());
        std::lock_guard<decltype(that->async_lock)> l(that->async_lock);
        that->async_data[1] = static_cast<measurement::value_type>(power)
            / static_cast<measurement::value_type>(1000);
        that->invoke_callback(timestamp);
#else /* defined(CUSTOM_TINKERFORGE_FIRMWARE) */
        tinkerforge_sensor_impl::power_callback(power, data);
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
        const auto timestamp = create_timestamp(that->async_sampling.resolution());
        std::lock_guard<decltype(that->async_lock)> l(that->async_lock);
        that->async_data[2] = static_cast<measurement::value_type>(voltage)
            / static_cast<measurement::value_type>(1000);
        that->invoke_callback(timestamp);   // TODO: Do we really want to invoke directly? How do we detect a consistent state?
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

    // Compute the 'time_offset' member if available.
    this->init_time_offset();
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

#if defined(CUSTOM_TINKERFORGE_FIRMWARE)
    if (this->has_internal_time()) {
        auto status = ::voltage_current_v2_set_power_time_callback_configuration(
            &this->bricklet, false);
        if (status < 0) {
            throw tinkerforge_exception(status);
        }
    }
#endif /* defined(CUSTOM_TINKERFORGE_FIRMWARE) */
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


/*
 * visus::power_overwhelming::detail::tinkerforge_sensor_impl::init_time_offset
 */
bool
visus::power_overwhelming::detail::tinkerforge_sensor_impl::init_time_offset(
        const std::size_t iterations) {
#if defined(CUSTOM_TINKERFORGE_FIRMWARE)
    char connected_to_uid[8];
    std::uint16_t device_id;
    std::uint8_t firmware_version[3];
    std::uint8_t hardware_version[3];
    char position;
    std::uint32_t time;
    std::vector<timestamp_type> time_offsets(iterations + 1);
    char uid[8];

    this->time_offset = 0;

    // Get the firmware version so that we can find out whether the bricklet
    // supports our customised callback that includes on-device time.
    {
        auto status = ::voltage_current_v2_get_identity(&this->bricklet, uid,
            connected_to_uid, &position, hardware_version, firmware_version,
            &device_id);
        if (status < 0) {
            return false;
        }
    }

    // Check against the configured firmware version. The major version must
    // always be set by the build system, the remainer is only checked if set.
    if (firmware_version[0] != CUSTOM_TINKERFORGE_FIRMWARE_MJ) {
        return false;
    }

#if defined(CUSTOM_TINKERFORGE_FIRMWARE_MN)
    if (firmware_version[1] != CUSTOM_TINKERFORGE_FIRMWARE_MN) {
        return false;
    }
#endif /* CUSTOM_TINKERFORGE_FIRMWARE_MN */

#if defined(CUSTOM_TINKERFORGE_FIRMWARE_RV)
    if (firmware_version[2] != CUSTOM_TINKERFORGE_FIRMWARE_RV) {
        return false;
    }
#endif /* CUSTOM_TINKERFORGE_FIRMWARE_RV */

    // Compute the median offset over the requested number of iterations.
    for (std::size_t i = 1; i < time_offsets.size(); ++i) {
        typedef std::make_unsigned<timestamp_type>::type unsigned_type;
        auto timestamp = create_timestamp(timestamp_resolution::milliseconds);
        auto status = ::voltage_current_v2_get_time(&this->bricklet, &time);
        if (status < 0) {
            return false;
        }

        time_offsets[i] = timestamp - time;
    }

    std::sort(time_offsets.begin(), time_offsets.end());
    this->time_offset = time_offsets[time_offsets.size() >> 1];
    return true;

#else /* defined(CUSTOM_TINKERFORGE_FIRMWARE) */
    return false;
#endif /* defined(CUSTOM_TINKERFORGE_FIRMWARE) */
}
