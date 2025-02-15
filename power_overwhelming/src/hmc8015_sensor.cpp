// <copyright file="hmc8015_sensor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "hmc8015_sensor.h"

#include <array>
#include <cassert>
#include <stdexcept>


/*
 * PWROWG_DETAIL_NAMESPACE_BEGIN::hmc8015_sensor::descriptions
 */
std::size_t PWROWG_DETAIL_NAMESPACE::hmc8015_sensor::descriptions(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) sensor_description *dst,
        _In_ std::size_t cnt,
        _In_ const configuration_type& config) {
    std::size_t retval = 0;

#if defined(POWER_OVERWHELMING_WITH_VISA)
    const std::array<hmc8015_function, 6> default_functions {
        hmc8015_function::rms_voltage,
        hmc8015_function::rms_current,
        hmc8015_function::active_power,
        hmc8015_function::apparent_power,
        hmc8015_function::watt_hour,
        hmc8015_function::integration_time
    };

    // Force output counter to be empty if no buffer was provided.
    if (dst == nullptr) {
        cnt = 0;
    }

    auto builder = sensor_description_builder::create()
        .with_vendor(L"Rohde & Schwarz")
        .with_type(sensor_type::hardware | sensor_type::external)
        .produces(reading_type::floating_point);

    try {
        std::vector<hmc8015_instrument> instruments;
        instruments.resize(hmc8015_instrument::for_all(
            nullptr,
            0,
            config.timeout()));
        hmc8015_instrument::for_all(
            instruments.data(),
            instruments.size(),
            config.timeout());

        for (auto& i : instruments) {
            // Determine the unique path of the instrument, which we need to
            // connect the sensor to and which we need to build the ID.
            const auto path = i.path();
            if (path == nullptr) {
                continue;
            }
            builder.with_path(path);

            // Create the friendly name.
            {
                std::vector<wchar_t> name;
                name.resize(i.identify(name.data(), name.size()));
                i.identify(name.data(), name.size());
                builder.with_name(name.data());
            }

            // Determine which functions to enable: the configured ones or the
            // default if the user did not provide anything special.
            auto funcs = config.functions();
            auto cnt_funcs = config.count_functions();

            if (funcs == nullptr) {
                funcs = default_functions.data();
                cnt_funcs = default_functions.size();
            }

            i.custom_functions(funcs, cnt_funcs);

            // Create a descriptor for each function being recorded.
            for (std::size_t f = 0; f < cnt_funcs; ++f) {
                if (specialise(builder, funcs[f])) {
                    if (cnt > 0) {
                        dst[retval] = builder
                            .with_id("%s/%ls", path, to_string(funcs[f]))
                            .build();
                        --cnt;
                    }

                    ++retval;

                    break;  // TODO, TODO, TODO, HACK
                }
            }
        }

        return retval;

    } catch (...) {
        // Not supported if we are here.
        return 0;
    }
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */

    return retval;
}


/*
 * PWROWG_DETAIL_NAMESPACE::hmc8015_sensor::hmc8015_sensor
 */
PWROWG_DETAIL_NAMESPACE::hmc8015_sensor::hmc8015_sensor(
        _In_z_ const wchar_t *path,
        _In_ const std::size_t index,
        _In_ const configuration_type& config)
    : _config(config),
        _index(index) {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    this->_instrument = hmc8015_instrument(path, config.timeout());
    this->_instrument.timeout(config.timeout());
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */
}


/*
 * PWROWG_DETAIL_NAMESPACE::hmc8015_sensor::sample
 */
void PWROWG_DETAIL_NAMESPACE::hmc8015_sensor::sample(
        _In_opt_ const sensor_array_callback callback,
        _In_ const std::chrono::milliseconds interval,
        _In_opt_ void *context) {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    using std::chrono::duration;
    using std::chrono::duration_cast;

    if (callback != nullptr) {
        this->_state.begin_start();

        const auto i = duration_cast<duration<float>>(interval);
        this->_instrument.integrator_behaviour(hmc8015_integrator_mode::manual)
            .log_behaviour(i.count(), hmc8015_log_mode::unlimited)
            .log_file("hackno.csv", false, false)
            .start_integrator()
            .log(true);

        this->_state.end_start();

    } else {
        this->_state.begin_stop();

        // Stop integration and logging.
        this->_instrument.stop_integrator()
            .log(false);

        // Find out where the instrument wrote the data to.
        std::vector<char> log;
        log.resize(this->_instrument.log_file(nullptr, 0));
        this->_instrument.log_file(log.data(), log.size());

        // Download the CSV file into memory.
        auto csv = this->_instrument.copy_file_from_instrument_or_usb(
            log.data());

        // Parse the samples and emit everything at once.
        // TODO

        // If using internal memory, delete the log file. If the user selected the
        // USB thumb drive, we assume the original data should be kept for
        // reference.
        if (!this->_config.log_to_usb()) {
            this->_instrument.delete_file_from_instrument_or_usb(log.data());
        }

        this->_state.end_stop();
    }
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */
}


/*
 * PWROWG_DETAIL_NAMESPACE::hmc8015_sensor::specialise
 */
bool PWROWG_DETAIL_NAMESPACE::hmc8015_sensor::specialise(
        _In_ sensor_description_builder& builder,
        _In_ const hmc8015_function function) {
    const auto base_type = sensor_type::external | sensor_type::system;

    if (is_current(function)) {
        builder.produces(reading_type::floating_point)
            .measured_in(reading_unit::ampere)
            .with_type(base_type | sensor_type::current);
        return true;

    } else if (is_energy(function)) {
        builder.produces(reading_type::floating_point)
            .measured_in(reading_unit::watt_hour)
            .with_type(base_type | sensor_type::energy);
        return true;

    } else if (is_power(function)) {
        builder.produces(reading_type::floating_point)
            .measured_in(reading_unit::watt)
            .with_type(base_type | sensor_type::power);
        return true;

    } else if (is_voltage(function)) {
        builder.produces(reading_type::floating_point)
            .measured_in(reading_unit::volt)
            .with_type(base_type | sensor_type::voltage);
        return true;

    } else {
        // This is nothing we support in the sensor.
        return false;
    }
}
