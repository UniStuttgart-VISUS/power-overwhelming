// <copyright file="tinkerforge_sensor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "tinkerforge_sensor.h"

#include <stdexcept>


/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::descriptions
 */
std::size_t PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::descriptions(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) sensor_description *dst,
        _In_ std::size_t cnt,
        _In_ const configuration_type& config) {
    typedef tinkerforge_bricklet bricklet_type;

    std::vector<bricklet_type> bricklets;
    auto builder = sensor_description_builder::create()
        .with_vendor(L"Tinkerforge")
        .with_editable_type(sensor_type::cpu
            | sensor_type::external
            | sensor_type::gpu
            | sensor_type::system)
        .produces(reading_type::floating_point);
    std::size_t retval = 0;

    if (dst == nullptr) {
        // Subsequently, we only check 'cnt', so make it reflect an invalid
        // buffer.
        cnt = 0;
    }

    for (std::size_t i = 0; i < config.count_end_points(); ++i) {
        auto& end_point = config.end_points()[i];

        try {
            tinkerforge_scope scope(end_point.name(), end_point.port());

            bricklets.clear();
            scope.copy_bricklets(
                std::back_inserter(bricklets),
                [](const bricklet_type& b) { return (b.device_type()
                    == VOLTAGE_CURRENT_V2_DEVICE_IDENTIFIER); },
                std::chrono::milliseconds(config.timeout()));

            for (auto& b : bricklets) {
                if (cnt > 0) {
                    dst[retval] = specialise(builder,
                        scope,
                        config,
                        end_point,
                        b,
                        sensor_type::current,
                        reading_unit::ampere).build();
                    --cnt;
                }
                ++retval;

                if (cnt > 0) {
                    dst[retval] = specialise(builder,
                        scope,
                        config,
                        end_point,
                        b,
                        sensor_type::voltage,
                        reading_unit::volt).build();
                    --cnt;
                }
                ++retval;

                if (cnt > 0) {
                    dst[retval] = specialise(builder,
                        scope,
                        config,
                        end_point,
                        b,
                        sensor_type::power,
                        reading_unit::watt).build();
                    --cnt;
                }
                ++retval;
            }
        } catch (tinkerforge_exception) {
            // If the connection failed in the scope, we do not have any
            // bricklets from the specific host. This is typically caused
            // by brickd not running on 'end_point'. At this point, the
            // resolution is to just ignore the end point.
        }
    }

    return retval;
}


/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::invalid_index
 */
constexpr std::size_t PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::invalid_index;


/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::current_callback
 */
void PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::current_callback(
        _In_ const std::int32_t value,
        _In_ void *data) {
    typedef decltype(reading::floating_point) value_type;
    assert(data != nullptr);
    auto that = static_cast<tinkerforge_sensor *>(data);
    std::lock_guard<decltype(that->_lock)> l(that->_lock);
    PWROWG_NAMESPACE::sample sample(static_cast<value_type>(value)
        / static_cast<value_type>(1000));
    that->_callback(that->_index_current, &sample, 1, that->_context);
}


/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::power_callback
 */
void PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::power_callback(
        _In_ const std::int32_t value,
        _In_ void *data) {
    typedef decltype(reading::floating_point) value_type;
    assert(data != nullptr);
    auto that = static_cast<tinkerforge_sensor *>(data);
    std::lock_guard<decltype(that->_lock)> l(that->_lock);
    PWROWG_NAMESPACE::sample sample(static_cast<value_type>(value)
        / static_cast<value_type>(1000));
    that->_callback(that->_index_power, &sample, 1, that->_context);
}


/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::power_time_callback
 */
void PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::power_time_callback(
        _In_ const std::int32_t value,
        _In_ const std::uint32_t time,
        _In_ void *data) {
#if defined(CUSTOM_TINKERFORGE_FIRMWARE)
    typedef decltype(reading::floating_point) value_type;
    assert(data != nullptr);
    auto that = static_cast<tinkerforge_sensor *>(data);
    std::lock_guard<decltype(that->_lock)> l(that->_lock);
    PWROWG_NAMESPACE::sample sample(static_cast<value_type>(value)
        / static_cast<value_type>(1000));
    const auto ts = that->_time_xlate(time, that->_bricklet);
    //auto wall_time = create_timestamp(that->async_sampling.resolution());
    //::OutputDebugStringW((that->sensor_name + L" " + std::to_wstring(wall_time)
    //    + L" " + std::to_wstring(time)
    //    + L" " + std::to_wstring(wall_time - ts)
    //    + L"\r\n").c_str());
    PWROWG_NAMESPACE::sample sample(ts, static_cast<value_type>(value)
        / static_cast<value_type>(1000));
    that->_callback(that->_index_power, &sample, 1, that->_context);
#else /* defined(CUSTOM_TINKERFORGE_FIRMWARE) */
    power_callback(value, data);
#endif /* defined(CUSTOM_TINKERFORGE_FIRMWARE) */
}


/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::same_bricklet
 */
bool PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::same_bricklet(
        _In_ const sensor_description& lhs,
        _In_ const sensor_description& rhs) {
    auto pdl = sensor_description_builder::private_data<tinkerforge_scope>(lhs);
    auto pdr = sensor_description_builder::private_data<tinkerforge_scope>(lhs);
    return ((*pdl == *pdr) && equals(lhs.id(), rhs.id()));
}


/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::sensor_mask
 */
PWROWG_NAMESPACE::sensor_type
PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::sensor_mask(
        _In_ const sensor_description& desc) {
    const auto mask = sensor_type::power
        | sensor_type::voltage
        | sensor_type::current;
    return (desc.sensor_type() & mask);
}


/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::specialise
 */
PWROWG_DETAIL_NAMESPACE::sensor_description_builder&
PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::specialise(
        _In_ sensor_description_builder& builder,
        _In_ const tinkerforge_scope& scope,
        _In_ const configuration_type& config,
        _In_ const tinkerforge_configuration::end_point& end_point,
        _In_ const tinkerforge_bricklet& bricklet,
        _In_ const PWROWG_NAMESPACE::sensor_type type,
        _In_ const reading_unit unit) {
    const char *source = "unknown";

    if ((type | sensor_type::current) != sensor_type::unknown) {
        source = "current";
    } else if ((type | sensor_type::power) != sensor_type::unknown) {
        source = "power";
    } else if ((type | sensor_type::voltage) != sensor_type::unknown) {
        source = "voltage";
    }

    return builder.with_id(bricklet.uid())
        .with_type(type | sensor_type::hardware)
        .with_path("%s:%hu/%s/%s",
            end_point.name(),
            end_point.port(),
            bricklet.uid().c_str(),
            source)
        .with_name("Tinkerforge/%s:%hu/%s/%s",
            end_point.name(),
            end_point.port(),
            bricklet.uid().c_str(),
            source)
        .measured_in(reading_unit::ampere)
        .with_new_private_data<private_data>(scope, config);
}


/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::voltage_callback
 */
void PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::voltage_callback(
        _In_ const std::int32_t value,
        _In_ void *data) {
    typedef decltype(reading::floating_point) value_type;
    assert(data != nullptr);
    auto that = static_cast<tinkerforge_sensor *>(data);
    std::lock_guard<decltype(that->_lock)> l(that->_lock);
    PWROWG_NAMESPACE::sample sample(static_cast<value_type>(value)
        / static_cast<value_type>(1000));
    that->_callback(that->_index_voltage, &sample, 1, that->_context);
}


/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::disable_callbacks
 */
void PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::disable_callbacks(void) {
    // First of all, disable the callbacks that run in the communication thread
    // of the Tinkerforge device. Note that we must *not* clear the context,
    // because the whole registration is not thread-safe. We therefore have to
    // assume that the callback might have already been copied to a local
    // variable whereas the context has not. In this case, we would risk
    // invoking a valid callback with an invalid context if we set the context
    // to nullptr, too.
    ::voltage_current_v2_register_callback(&this->_bricklet,
        VOLTAGE_CURRENT_V2_CALLBACK_CURRENT,
        nullptr,
        this);
    ::voltage_current_v2_register_callback(&this->_bricklet,
        VOLTAGE_CURRENT_V2_CALLBACK_POWER,
        nullptr,
        this);
    ::voltage_current_v2_register_callback(&this->_bricklet,
        VOLTAGE_CURRENT_V2_CALLBACK_VOLTAGE,
        nullptr,
        this);

    if (this->has_internal_time()) {
        ::voltage_current_v2_register_callback(&this->_bricklet,
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
            &this->_bricklet, 0, false, 'x', 0, 0);
        if (status < 0) {
            throw tinkerforge_exception(status);
        }
    }

    {
        auto status = ::voltage_current_v2_set_power_callback_configuration(
            &this->_bricklet, 0, false, 'x', 0, 0);
        if (status < 0) {
            throw tinkerforge_exception(status);
        }
    }

    {
        auto status = ::voltage_current_v2_set_voltage_callback_configuration(
            &this->_bricklet, 0, false, 'x', 0, 0);
        if (status < 0) {
            throw tinkerforge_exception(status);
        }
    }

    if (this->has_internal_time()) {
        auto status = ::voltage_current_v2_set_power_time_callback_configuration(
            &this->_bricklet, false);
        if (status < 0) {
            throw tinkerforge_exception(status);
        }
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::tinkerforge_sensor
 */
PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::tinkerforge_sensor(
        _In_ tinkerforge_scope scope,
        _In_z_ const wchar_t *uid,
        _In_ std::shared_ptr<tinkerforge_configuration> config,
        _In_ const std::size_t index_power,
        _In_ const std::size_t index_voltage,
        _In_ const std::size_t index_current)
    : _callback(nullptr),
        _config(config),
        _context(nullptr),
        _index_current(index_current),
        _index_power(index_power),
        _index_voltage(index_voltage),
        _scope(scope) {
    if (config == nullptr) {
        throw std::invalid_argument("The general Tinkerforge sensor "
            "configuration must not be null.");
    }
    if (uid == nullptr) {
        throw std::invalid_argument("The UID of the voltage/current bricklet "
            "must not be null.");
    }

    auto u = PWROWG_NAMESPACE::convert_string<char>(uid);
    ::voltage_current_v2_create(&this->_bricklet, u.c_str(), this->_scope);

    //// Initialise the asynchronous measurement buffer with in valid data.
    //std::fill(this->async_data.begin(), this->async_data.end(),
    //    measurement::invalid_value);

    // TODO: this is too slow, only set timing in reset.
#if defined(CUSTOM_TINKERFORGE_FIRMWARE)
    this->_time_xlate.reset(this->_bricklet);
#endif /* defined(CUSTOM_TINKERFORGE_FIRMWARE) */
}


/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::~tinkerforge_sensor
 */
PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::~tinkerforge_sensor(
        void) noexcept {
    // Make sure to disable the callbacks in case the user forgot to do
    // so before destroying the sensor. Note that we do not hold the lock at
    // this point, which enables all callbacks that are already running to
    // exit asap.
    this->disable_callbacks();

    // Make sure that we do not destroy the sensor while asnychronous data are
    // written. This will block until the writer exited.
    // TODO: This is only semi-safe for cases where only one calback is running. We need to fix that some time, but for now, we usually only
    // run power callbacks, so it is somewhat OK ...
    std::lock_guard<decltype(this->_lock)> l(this->_lock);

    ::voltage_current_v2_destroy(&this->_bricklet);
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
    // Preserve the UID.
    char uid[8];
    this->identify(uid);

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
    ::voltage_current_v2_create(&this->_bricklet, uid, this->_scope);

#if defined(CUSTOM_TINKERFORGE_FIRMWARE)
    this->_time_xlate.reset(this->_bricklet);
#endif /* defined(CUSTOM_TINKERFORGE_FIRMWARE) */

    // As we have reset everything, apply the configuration again.
    this->configuration(this->_config->averaging(),
        this->_config->voltage_conversion_time(),
        this->_config->current_conversion_time());
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


/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::sample
 */
void PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::sample(
        _In_opt_ const sensor_array_callback callback,
        _In_ const std::chrono::milliseconds interval,
        _In_opt_ void *context) {
    if (callback != nullptr) {
        // If a valid callback is provided, enable the sensor.
        this->_state.begin_start();

        this->_callback = callback;
        this->_context = context;

        if (this->_index_current < invalid_index) {
            this->enable_current_callback(interval);
        }

        if (this->_index_power < invalid_index) {
            this->enable_power_callback(interval);
        }

        if (this->_index_voltage < invalid_index) {
            this->enable_voltage_callback(interval);
        }

        this->_state.end_start();

    } else {
        // Disable asynchronous sampling if there is no callback.
        this->_state.begin_stop();
        this->disable_callbacks();
        this->_context = context;
        this->_state.end_stop();
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::enable_current_callback
 */
void PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::enable_current_callback(
        _In_ const std::chrono::milliseconds interval) {
    ::voltage_current_v2_register_callback(&this->_bricklet,
        VOLTAGE_CURRENT_V2_CALLBACK_CURRENT,
        reinterpret_cast<void (*)(void)>(current_callback),
        this);

    auto status = ::voltage_current_v2_set_current_callback_configuration(
        &this->_bricklet,
        static_cast<std::int32_t>(interval.count()),
        false,
        'x',
        0,
        0);
    if (status < 0) {
        throw tinkerforge_exception(status);
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::enable_power_callback
 */
void PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::enable_power_callback(
        _In_ const std::chrono::milliseconds interval) {
    if (this->has_internal_time()) {
        ::voltage_current_v2_register_callback(&this->_bricklet,
            VOLTAGE_CURRENT_V2_CALLBACK_POWER_TIME,
            reinterpret_cast<void (*)(void)>(power_time_callback),
            this);

        auto status = ::voltage_current_v2_set_power_time_callback_configuration(
            &this->_bricklet,
            true);
        if (status < 0) {
            throw tinkerforge_exception(status);
        }

    } else {
        ::voltage_current_v2_register_callback(&this->_bricklet,
            VOLTAGE_CURRENT_V2_CALLBACK_POWER,
            reinterpret_cast<void (*)(void)>(power_callback),
            this);

        auto status = ::voltage_current_v2_set_power_callback_configuration(
            &this->_bricklet,
            static_cast<std::int32_t>(interval.count()),
            false,
            'x',
            0,
            0);
        if (status < 0) {
            throw tinkerforge_exception(status);
        }
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::enable_voltage_callback
 */
void PWROWG_DETAIL_NAMESPACE::tinkerforge_sensor::enable_voltage_callback(
        _In_ const std::chrono::milliseconds interval) {
    ::voltage_current_v2_register_callback(&this->_bricklet,
        VOLTAGE_CURRENT_V2_CALLBACK_VOLTAGE,
        reinterpret_cast<void (*)(void)>(voltage_callback),
        this);

    auto status = ::voltage_current_v2_set_voltage_callback_configuration(
        &this->_bricklet,
        static_cast<std::int32_t>(interval.count()),
        false,
        'x',
        0,
        0);
    if (status < 0) {
        throw tinkerforge_exception(status);
    }
}
