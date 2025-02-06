// <copyright file="tinkerforge_sensor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "tinkerforge_sensor.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

///// <summary>
///// The callback to be invoked for incoming asynchronous current
///// readings.
///// </summary>
///// <param name="current"></param>
///// <param name="data"></param>
//void CALLBACK current_callback(const std::int32_t current, void *data) {
//    assert(data != nullptr);
//    auto that = static_cast<tinkerforge_sensor_impl *>(data);
//    std::lock_guard<decltype(that->async_lock)> l(that->async_lock);
//    const auto ts = timestamp::now();
//    that->async_data[0] = static_cast<measurement::value_type>(current)
//        / static_cast<measurement::value_type>(1000);
//    that->invoke_callback(ts);   // TODO: Do we really want to invoke directly? How do we detect a consistent state?
//}
//
///// <summary>
///// The callback to be invoked for incoming asynchronous power
///// readings.
///// </summary>
///// <param name="power"></param>
///// <param name="data"></param>
//void CALLBACK power_callback(const std::int32_t power, void *data) {
//    assert(data != nullptr);
//    auto that = static_cast<tinkerforge_sensor_impl *>(data);
//    std::lock_guard<decltype(that->async_lock)> l(that->async_lock);
//    const auto ts = timestamp::now();
//    that->async_data[1] = static_cast<measurement::value_type>(power)
//        / static_cast<measurement::value_type>(1000);
//    that->invoke_callback(ts);   // TODO: Do we really want to invoke directly? How do we detect a consistent state?
//}
//
///// <summary>
///// The callback to be invoked for incoming asynchronous power
///// readings from our modified firmware.
///// </summary>
///// <param name="power"></param>
///// <param name="time"></param>
///// <param name="data"></param>
//void CALLBACK power_time_callback(const std::int32_t power,
//        const std::uint32_t time, void *data) {
//#if defined(CUSTOM_TINKERFORGE_FIRMWARE)
//    assert(data != nullptr);
//    auto that = static_cast<tinkerforge_sensor_impl *>(data);
//    std::lock_guard<decltype(that->async_lock)> l(that->async_lock);
//    const auto ts = that->time_xlate(time, that->bricklet);
//    //auto wall_time = create_timestamp(that->async_sampling.resolution());
//    //::OutputDebugStringW((that->sensor_name + L" " + std::to_wstring(wall_time)
//    //    + L" " + std::to_wstring(time)
//    //    + L" " + std::to_wstring(wall_time - ts)
//    //    + L"\r\n").c_str());
//    that->async_data[1] = static_cast<measurement::value_type>(power)
//        / static_cast<measurement::value_type>(1000);
//    that->invoke_callback(ts);
//#else /* defined(CUSTOM_TINKERFORGE_FIRMWARE) */
//    power_callback(power, data);
//#endif /* defined(CUSTOM_TINKERFORGE_FIRMWARE) */
//}

PWROWG_DETAIL_NAMESPACE_END


/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::specialise
 */
PWROWG_DETAIL_NAMESPACE::sensor_description_builder&
PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::specialise(
        _In_ sensor_description_builder& builder,
        _In_ const tinkerforge_configuration::end_point& end_point,
        _In_ const tinkerforge_bricklet& bricklet,
        _In_ const tinkerforge_sensor_source source,
        _In_ const sensor_type type,
        _In_ const reading_unit unit) {
    return builder.with_id(bricklet.uid())
        .with_type(type | sensor_type::hardware)
        .with_path("%s:%hu/%s/%ls",
            end_point.name(),
            end_point.port(),
            bricklet.uid().c_str(),
            to_string(source))
        .with_name("Tinkerforge/%s:%hu/%s/%ls",
            end_point.name(),
            end_point.port(),
            bricklet.uid().c_str(),
            to_string(source))
        .measured_in(reading_unit::ampere)
        .with_new_private_data<private_data>(end_point, source);
}


/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::tinkerforge_sensor
 */
PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::tinkerforge_sensor(
        _In_ tinkerforge_scope scope,
        _In_z_ const char *uid,
        _In_ const tinkerforge_sensor_source source)
        : _scope(scope), _source(source) {
    if (uid == nullptr) {
        throw std::invalid_argument("The UID of the voltage/current bricklet "
            "must not be null.");
    }

    this->_uid = uid;
    ::voltage_current_v2_create(&this->_bricklet, this->_uid.c_str(),
        this->_scope);

    //// Initialise the asynchronous measurement buffer with in valid data.
    //std::fill(this->async_data.begin(), this->async_data.end(),
    //    measurement::invalid_value);

    // TODO: this is too slow, only set timing in reset.
#if defined(CUSTOM_TINKERFORGE_FIRMWARE)
    this->_time_xlate.reset(this->_bricklet);
#endif /* defined(CUSTOM_TINKERFORGE_FIRMWARE) */
}


/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::configuration
 */
void PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::configuration(
        _Out_ tinkerforge_sample_averaging& averaging,
        _Out_ tinkerforge_conversion_time& voltage_conversion_time,
        _Out_ tinkerforge_conversion_time& current_conversion_time) {
    typedef std::underlying_type<tinkerforge_conversion_time>::type adc_type;
    typedef std::underlying_type<tinkerforge_sample_averaging>::type avg_type;

    auto status = ::voltage_current_v2_get_configuration(
        &this->_bricklet,
        reinterpret_cast<avg_type *>(&averaging),
        reinterpret_cast<adc_type *>(&voltage_conversion_time),
        reinterpret_cast<adc_type *>(&current_conversion_time));
    if (status < 0) {
        throw tinkerforge_exception(status);
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::configuration
 */
void PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::configuration(
        _In_ const tinkerforge_sample_averaging averaging,
        _In_ const tinkerforge_conversion_time voltage_conversion_time,
        _In_ const tinkerforge_conversion_time current_conversion_time) {
    typedef std::underlying_type<tinkerforge_conversion_time>::type adc_type;
    typedef std::underlying_type<tinkerforge_sample_averaging>::type avg_type;

    auto status = ::voltage_current_v2_set_configuration(
        &this->_bricklet,
        static_cast<avg_type>(averaging),
        static_cast<adc_type>(voltage_conversion_time),
        static_cast<adc_type>(current_conversion_time));
    if (status < 0) {
        throw tinkerforge_exception(status);
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::error_count
 */
PWROWG_NAMESPACE::tinkerforge_error_count
PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::error_count(void) const {
    tinkerforge_error_count retval;

    auto status = ::voltage_current_v2_get_spitfp_error_count(&this->_bricklet,
        &retval.ack_checksum,
        &retval.message_checksum,
        &retval.frame,
        &retval.overflow);
    if (status < 0) {
        throw tinkerforge_exception(status);
    }

    return retval;
}


/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::identify
 */
void PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::identify(
        _Out_writes_(8) char uid[8],
        _Out_writes_(8) char connected_to_uid[8],
        _Out_ char& position,
        _Out_writes_(3) std::uint8_t hardware_version[3],
        _Out_writes_(3) std::uint8_t firmware_version[3],
        _Out_ std::uint16_t& device_id) const {
    auto status = ::voltage_current_v2_get_identity(&this->_bricklet,
        uid,
        connected_to_uid,
        &position,
        hardware_version,
        firmware_version,
        &device_id);
    if (status < 0) {
        throw tinkerforge_exception(status);
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::identify
 */
void PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::identify(
        _Out_writes_(8) char uid[8]) const {
    char dummy0[8];
    char dummy1;
    std::uint8_t dummy2[3];
    std::uint8_t dummy3[3];
    std::uint16_t dummy4;
    this->identify(uid, dummy0, dummy1, dummy2, dummy3, dummy4);
}


/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::reset
 */
void PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::reset(void) {
    {
        auto status = ::voltage_current_v2_reset(&this->_bricklet);
        if (status < 0) {
            throw tinkerforge_exception(status);
        }
    }

    // As per
    // https://www.tinkerforge.com/en/doc/Software/Bricklets/VoltageCurrentV2_Bricklet_C.html,
    // we need to recreate the device object after a reset.
    ::voltage_current_v2_destroy(&this->_bricklet);
    ::voltage_current_v2_create(&this->_bricklet, this->_uid.c_str(),
        this->_scope);

#if defined(CUSTOM_TINKERFORGE_FIRMWARE)
    this->_time_xlate.reset(this->_bricklet);
#endif /* defined(CUSTOM_TINKERFORGE_FIRMWARE) */
}


/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::resync_internal_clock
 */
void PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::resync_internal_clock(
    void) {
#if defined(CUSTOM_TINKERFORGE_FIRMWARE)
    this->_time_xlate.update(this->_bricklet);
#endif /* defined(CUSTOM_TINKERFORGE_FIRMWARE) */
}


/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::resync_internal_clock_after
 */
void PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::resync_internal_clock_after(
    _In_ const std::size_t cnt) {
#if defined(CUSTOM_TINKERFORGE_FIRMWARE)
    this->_time_xlate.update_every(cnt);
#endif /* defined(CUSTOM_TINKERFORGE_FIRMWARE) */
}


#if false
#include <cassert>
#include <chrono>
#include <thread>
#include <vector>

#include <bricklet_voltage_current_v2.h>

#include "tinkerforge_exception.h"
#include "tinkerforge_sensor_impl.h"
#include "zero_memory.h"


/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::for_all
 */
std::size_t PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::for_all(
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
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::for_all
 */
std::size_t PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::for_all(
        _Out_writes_opt_(cnt_sensors) tinkerforge_sensor *out_sensors,
        _In_ const std::size_t cnt_sensors,
        _In_opt_z_ const wchar_t *host,
        _In_ const std::uint16_t port,
        _In_ const std::size_t timeout) {
    auto h = convert_string<char>(host);
    return for_all(out_sensors, cnt_sensors, timeout, h.c_str(), port);
}


/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::get_definitions
 */
std::size_t PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::get_definitions(
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
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::tinkerforge_sensor
 */
PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::tinkerforge_sensor(
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
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::tinkerforge_sensor
 */
PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::tinkerforge_sensor(
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
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::~tinkerforge_sensor
 */
PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::~tinkerforge_sensor(
        void) {
    delete this->_impl;
}



/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::description
 */
_Ret_maybenull_z_ const wchar_t *
PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::description(
        void) const noexcept {
    if (this->_impl != nullptr) {
        return this->_impl->description.c_str();
    } else {
        return nullptr;
    }
}




/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::name
 */
_Ret_maybenull_z_ const wchar_t *
PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::name(void) const noexcept {
    if (this->_impl != nullptr) {
        return this->_impl->sensor_name.c_str();
    } else {
        return nullptr;
    }
}




/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::sample
 */
void PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::sample(
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
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::operator =
 */
PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor&
PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::operator =(
        _In_ tinkerforge_sensor&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        delete this->_impl;
        this->_impl = rhs._impl;
        rhs._impl = nullptr;
    }

    return *this;
}


/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::operator bool
 */
PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::operator bool(
        void) const noexcept {
    return (this->_impl != nullptr);
}


/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::sample_async
 */
void PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::sample_async(
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
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::sample_sync
 */
PWROWG_DETAIL_NAMESPACE::measurement_data
PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::sample_sync(void) const {
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
#endif
