// <copyright file="tinkerforge_sensor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licenced under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/tinkerforge_sensor.h"

#include <cassert>
#include <chrono>
#include <thread>
#include <vector>

#include <bricklet_voltage_current_v2.h>

#include "sampler.h"
#include "tinkerforge_exception.h"
#include "tinkerforge_sensor_impl.h"
#include "zero_memory.h"


/*
 * visus::power_overwhelming::tinkerforge_sensor::for_all
 */
std::size_t visus::power_overwhelming::tinkerforge_sensor::for_all(
        _Out_writes_opt_(cnt_sensors) tinkerforge_sensor *out_sensors,
        _In_ const std::size_t cnt_sensors,
        _In_ const std::size_t timeout,
        _In_opt_z_ const char *host,
        _In_ const std::uint16_t port) {
    if ((out_sensors == nullptr) || (cnt_sensors == 0)) {
        return tinkerforge_sensor::get_definitions(nullptr, 0, timeout, host,
            port);

    } else {
        std::vector<tinkerforge_sensor_definition> descs(cnt_sensors);
        auto retval = tinkerforge_sensor::get_definitions(descs.data(),
            descs.size(), timeout, host, port);

        // Handle potential attachment of sensors between measurment call and
        // actual instantiation call.
        if (retval < cnt_sensors) {
            retval = cnt_sensors;
        }

        for (std::size_t i = 0; i < retval; ++i) {
            out_sensors[i] = tinkerforge_sensor(descs[i]);
        }

        return retval;
    }
}


/*
 * visus::power_overwhelming::tinkerforge_sensor::for_all
 */
std::size_t visus::power_overwhelming::tinkerforge_sensor::for_all(
        _Out_writes_opt_(cnt_sensors) tinkerforge_sensor *out_sensors,
        _In_ const std::size_t cnt_sensors,
        _In_opt_z_ const wchar_t *host,
        _In_ const std::uint16_t port,
        _In_ const std::size_t timeout) {
    auto h = convert_string<char>(host);
    return for_all(out_sensors, cnt_sensors, timeout, h.c_str(), port);
}


/*
 * visus::power_overwhelming::tinkerforge_sensor::get_definitions
 */
std::size_t visus::power_overwhelming::tinkerforge_sensor::get_definitions(
        _When_(dst != nullptr, _Out_writes_opt_(cnt))
        tinkerforge_sensor_definition *dst,
        _In_ const std::size_t cnt,
        _In_ const std::size_t timeout,
        _In_opt_z_ const char *host,
        _In_ const std::uint16_t port) {
    typedef detail::tinkerforge_bricklet bricklet_type;

    try {
        std::vector<bricklet_type> bricklets;
        const auto h = (host != nullptr) ? host : default_host;
        detail::tinkerforge_scope scope(h, port);

        auto retval = scope.copy_bricklets(
            std::back_inserter(bricklets),
            [](const bricklet_type& b) { return (b.device_type()
                == VOLTAGE_CURRENT_V2_DEVICE_IDENTIFIER); },
            std::chrono::milliseconds(timeout),
            cnt);

        if (dst != nullptr) {
            for (std::size_t i = 0; (i < cnt) && (i < retval); ++i) {
                dst[i] = tinkerforge_sensor_definition(
                    bricklets[i].uid().c_str());
            }
        }

        return retval;
    } catch (tinkerforge_exception) {
        // If the connection failed in the scope, we do not have any bricklets.
        // This is typically caused by brickd not running on 'host'.
        return 0;
    }
}


/*
 * visus::power_overwhelming::tinkerforge_sensor::tinkerforge_sensor
 */
visus::power_overwhelming::tinkerforge_sensor::tinkerforge_sensor(
        _In_z_ const char *uid,
        _In_opt_z_ const char *host,
        _In_ const std::uint16_t port) : _impl(nullptr) {
    // The implementation will (i) obtain and manage the scope with the
    // connection to the master brick, (ii) allocate the voltage/current
    // bricklet and manage its life time.
    this->_impl = new detail::tinkerforge_sensor_impl(
        (host != nullptr) ? host : default_host,
        port,
        uid);
}


/*
 * visus::power_overwhelming::tinkerforge_sensor::tinkerforge_sensor
 */
visus::power_overwhelming::tinkerforge_sensor::tinkerforge_sensor(
        _In_z_ const char *uid,
        _In_opt_z_ const wchar_t *description,
        _In_opt_z_ const char *host,
        _In_ const std::uint16_t port) : _impl(nullptr) {
    this->_impl = new detail::tinkerforge_sensor_impl(
        (host != nullptr) ? host : default_host,
        port,
        uid);

    if (description != nullptr) {
        this->_impl->description = description;
    }
}


/*
 * visus::power_overwhelming::tinkerforge_sensor::tinkerforge_sensor
 */
visus::power_overwhelming::tinkerforge_sensor::tinkerforge_sensor(
        _In_ const tinkerforge_sensor_definition& definition,
        _In_opt_z_ const char *host,
        _In_ const std::uint16_t port) : _impl(nullptr) {
    this->_impl = new detail::tinkerforge_sensor_impl(
        (host != nullptr) ? host : default_host,
        port,
        definition.uid());

    if (definition.description() != nullptr) {
        this->_impl->description = definition.description();
    }
}


/*
 * visus::power_overwhelming::tinkerforge_sensor::~tinkerforge_sensor
 */
visus::power_overwhelming::tinkerforge_sensor::~tinkerforge_sensor(
        void) {
    delete this->_impl;
}


/*
 * visus::power_overwhelming::tinkerforge_sensor::configuration
 */
void visus::power_overwhelming::tinkerforge_sensor::configuration(
        _Out_ sample_averaging& averaging,
        _Out_ conversion_time& voltage_conversion_time,
        _Out_ conversion_time& current_conversion_time) {
    typedef std::underlying_type<conversion_time>::type native_adc_type;
    typedef std::underlying_type<conversion_time>::type native_avg_type;

    if (!*this) {
        throw std::runtime_error("The configuration of a disposed "
            "tinkerforge_sensor cannot be retrieved.");
    }

    auto status = ::voltage_current_v2_get_configuration(
        &this->_impl->bricklet,
        reinterpret_cast<native_avg_type *>(&averaging),
        reinterpret_cast<native_adc_type *>(&voltage_conversion_time),
        reinterpret_cast<native_adc_type *>(&current_conversion_time));
    if (status < 0) {
        throw tinkerforge_exception(status);
    }
}


/*
 * visus::power_overwhelming::tinkerforge_sensor::configure
 */
void visus::power_overwhelming::tinkerforge_sensor::configure(
        _In_ const sample_averaging averaging,
        _In_ const conversion_time voltage_conversion_time,
        _In_ const conversion_time current_conversion_time) {
    typedef std::underlying_type<conversion_time>::type native_adc_type;
    typedef std::underlying_type<conversion_time>::type native_avg_type;

    if (!*this) {
        throw std::runtime_error("A disposed instance of tinkerforge_sensor "
            "cannot be configured.");
    }

    auto status = ::voltage_current_v2_set_configuration(
        &this->_impl->bricklet,
        static_cast<native_avg_type>(averaging),
        static_cast<native_adc_type>(voltage_conversion_time),
        static_cast<native_adc_type>(current_conversion_time));
    if (status < 0) {
        throw tinkerforge_exception(status);
    }
}


/*
 * visus::power_overwhelming::tinkerforge_sensor::description
 */
_Ret_maybenull_z_ const wchar_t *
visus::power_overwhelming::tinkerforge_sensor::description(
        void) const noexcept {
    if (this->_impl != nullptr) {
        return this->_impl->description.c_str();
    } else {
        return nullptr;
    }
}


/*
 * visus::power_overwhelming::tinkerforge_sensor::error_count
 */
visus::power_overwhelming::tinkerforge_error_count
visus::power_overwhelming::tinkerforge_sensor::error_count(void) const {
    this->check_not_disposed();

    tinkerforge_error_count retval;
    auto status = ::voltage_current_v2_get_spitfp_error_count(
        &this->_impl->bricklet, &retval.ack_checksum, &retval.message_checksum,
        &retval.frame, &retval.overflow);
    if (status < 0) {
        throw tinkerforge_exception(status);
    }

    return retval;
}


/*
 * visus::power_overwhelming::tinkerforge_sensor::identify
 */
void visus::power_overwhelming::tinkerforge_sensor::identify(
        _Out_writes_(8) char uid[8],
        _Out_writes_(8) char connected_to_uid[8],
        _Out_ char& position,
        _Out_writes_(3) std::uint8_t hardware_version[3],
        _Out_writes_(3) std::uint8_t firmware_version[3],
        _Out_ std::uint16_t& device_id) const {
    if (!*this) {
        throw std::runtime_error("A disposed instance of tinkerforge_sensor "
            "cannot be identified.");
    }

    auto status = ::voltage_current_v2_get_identity(&this->_impl->bricklet, uid,
        connected_to_uid, &position, hardware_version, firmware_version,
        &device_id);
    if (status < 0) {
        throw tinkerforge_exception(status);
    }
}


/*
 * visus::power_overwhelming::tinkerforge_sensor::identify
 */
void visus::power_overwhelming::tinkerforge_sensor::identify(
        _Out_writes_(8) char uid[8]) const {
    char dummy0[8];
    char dummy1;
    std::uint8_t dummy2[3];
    std::uint8_t dummy3[3];
    std::uint16_t dummy4;
    this->identify(uid, dummy0, dummy1, dummy2, dummy3, dummy4);
}


/*
 * visus::power_overwhelming::tinkerforge_sensor::name
 */
_Ret_maybenull_z_ const wchar_t *
visus::power_overwhelming::tinkerforge_sensor::name(void) const noexcept {
    if (this->_impl != nullptr) {
        return this->_impl->sensor_name.c_str();
    } else {
        return nullptr;
    }
}


/*
 * visus::power_overwhelming::tinkerforge_sensor::reset
 */
void visus::power_overwhelming::tinkerforge_sensor::reset(void) {
    if (!*this) {
        throw std::runtime_error("A disposed instance of tinkerforge_sensor "
            "cannot be reset.");
    }

    auto status = ::voltage_current_v2_reset(&this->_impl->bricklet);
    if (status < 0) {
        throw tinkerforge_exception(status);
    }

#if defined(CUSTOM_TINKERFORGE_FIRMWARE)
    this->_impl->time_xlate.reset(this->_impl->bricklet);
#endif /* defined(CUSTOM_TINKERFORGE_FIRMWARE) */
}


/*
 * visus::power_overwhelming::tinkerforge_sensor::resync_internal_clock_after
 */
void visus::power_overwhelming::tinkerforge_sensor::resync_internal_clock_after(
        _In_ const std::size_t cnt) {
#if defined(CUSTOM_TINKERFORGE_FIRMWARE)
    this->_impl->time_xlate.update_every(cnt);
#endif /* defined(CUSTOM_TINKERFORGE_FIRMWARE) */
}


/*
 * visus::power_overwhelming::tinkerforge_sensor::sample
 */
void visus::power_overwhelming::tinkerforge_sensor::sample(
        _In_opt_ const measurement_callback on_measurement,
        _In_ const tinkerforge_sensor_source source,
        _In_ const microseconds_type period,
        _In_opt_ void *context) {
#if defined(_WIN32)
    ::OutputDebugStringW(L"PWROWG DEPRECATION WARNING: This method is only "
        L"provided for backwards compatibility and might be removed in "
        L"future versions of the library. Use async_sampling to configure "
        L"asynchronous sampling.\r\n");
#endif /* defined(_WIN32) */
    this->check_not_disposed();
    this->sample_async(std::move(async_sampling()
        .samples_every(period)
        .delivers_measurements_to(on_measurement)
        .passes_context(context)));
}


/*
 * visus::power_overwhelming::tinkerforge_sensor::operator =
 */
visus::power_overwhelming::tinkerforge_sensor&
visus::power_overwhelming::tinkerforge_sensor::operator =(
        _In_ tinkerforge_sensor&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        delete this->_impl;
        this->_impl = rhs._impl;
        rhs._impl = nullptr;
    }

    return *this;
}


/*
 * visus::power_overwhelming::tinkerforge_sensor::operator bool
 */
visus::power_overwhelming::tinkerforge_sensor::operator bool(
        void) const noexcept {
    return (this->_impl != nullptr);
}


/*
 * visus::power_overwhelming::tinkerforge_sensor::sample_async
 */
void visus::power_overwhelming::tinkerforge_sensor::sample_async(
        _Inout_ async_sampling&& sampling) {
    static constexpr auto one = static_cast<microseconds_type>(1);
    static constexpr auto thousand = static_cast<microseconds_type>(1000);

    this->check_not_disposed();

    std::lock_guard<decltype(this->_impl->async_lock)> l(
        this->_impl->async_lock);
    const auto enabled = static_cast<bool>(this->_impl->async_sampling);
    if (enabled && sampling) {
        throw std::logic_error("Asynchronous sampling cannot be started while "
            "it is already running.");
    }

    if ((this->_impl->async_sampling = std::move(sampling))) {
        // Callback is non-null, so user wants to enable asynchronous sampling.

        try {
            const auto& config = this->_impl->async_sampling;
            const auto millis = static_cast<std::int32_t>((std::max)(one,
                config.interval() / thousand));
            const auto source = config.tinkerforge_sensor_source();

            if (source == tinkerforge_sensor_source::all) {
                // Enable all sensor readings.
                this->_impl->enable_callbacks(millis);

            } else {
                // Enable individual sensor readings.
                if ((source & tinkerforge_sensor_source::current)
                        == tinkerforge_sensor_source::current) {
                    this->_impl->enable_current_callback(millis);
                }
                if ((source & tinkerforge_sensor_source::power)
                        == tinkerforge_sensor_source::power) {
                    this->_impl->enable_power_callback(millis);
                }
                if ((source & tinkerforge_sensor_source::voltage)
                        == tinkerforge_sensor_source::voltage) {
                    this->_impl->enable_voltage_callback(millis);
                }
            }

        } catch (...) {
            // Clear the guard in case the operation failed.
            this->_impl->async_sampling.is_disabled();
            throw;
        }

    } else {
        // If sampling was enabled, disable it.
        if (enabled) {
            this->_impl->disable_callbacks();
        }
    }
}



/*
 * visus::power_overwhelming::tinkerforge_sensor::sample_sync
 */
visus::power_overwhelming::measurement_data
visus::power_overwhelming::tinkerforge_sensor::sample_sync(void) const {
    this->check_not_disposed();

    static const auto thousand = static_cast<measurement::value_type>(1000);
    std::int32_t current = 0;   // Current in mA.
    std::int32_t power = 0;     // Power in mW.
    std::int32_t voltage = 0;   // Voltage in mV.
    auto timestamp = power_overwhelming::timestamp::now();

    {
        auto status = ::voltage_current_v2_get_voltage(&this->_impl->bricklet,
            &voltage);
        if (status < 0) {
            throw tinkerforge_exception(status);
        }
    }

    {
        auto status = ::voltage_current_v2_get_current(&this->_impl->bricklet,
            &voltage);
        if (status < 0) {
            throw tinkerforge_exception(status);
        }
    }

    if (this->_impl->has_internal_time()) {
        std::uint32_t time;
        auto status = ::voltage_current_v2_get_power_time(
            &this->_impl->bricklet, &power, &time);
        if (status < 0) {
            throw tinkerforge_exception(status);
        }

#if defined(CUSTOM_TINKERFORGE_FIRMWARE)
        timestamp = this->_impl->time_xlate(time, this->_impl->bricklet);
#endif /* defined(CUSTOM_TINKERFORGE_FIRMWARE) */

    } else {
        auto status = ::voltage_current_v2_get_power(&this->_impl->bricklet,
            &power);
        if (status < 0) {
            throw tinkerforge_exception(status);
        }
    }

    return measurement_data(timestamp,
        static_cast<measurement::value_type>(voltage) / thousand,
        static_cast<measurement::value_type>(current) / thousand,
        static_cast<measurement::value_type>(power) / thousand);
}
