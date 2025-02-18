// <copyright file="hmc8015_sensor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "hmc8015_sensor.h"

#include <array>
#include <cassert>
#include <sstream>
#include <stdexcept>

#include <rapidcsv.h>

#include "sensor_array_impl.h"


/*
 * PWROWG_DETAIL_NAMESPACE_BEGIN::hmc8015_sensor::descriptions
 */
std::size_t PWROWG_DETAIL_NAMESPACE::hmc8015_sensor::descriptions(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) sensor_description *dst,
        _In_ std::size_t cnt,
        _In_ const configuration_type& config) {
    std::size_t retval = 0;

#if defined(POWER_OVERWHELMING_WITH_VISA)
    // These are the functions we enable by default if the user did not request
    // anything special via the 'config' object.
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


#if defined(POWER_OVERWHELMING_WITH_VISA)
/*
 * PWROWG_DETAIL_NAMESPACE::hmc8015_sensor::hmc8015_sensor
 */
PWROWG_DETAIL_NAMESPACE::hmc8015_sensor::hmc8015_sensor(
        _Inout_ hmc8015_instrument&& instrument,
        _In_ const sensor_array_impl *owner,
        _In_ const std::size_t index,
        _Inout_ std::vector<hmc8015_function>&& functions)
    : _functions(std::move(functions)),
        _instrument(std::move(instrument)),
        _index(index),
        _owner(owner) {
    if (!this->_instrument) {
        throw std::invalid_argument("A valid HMC 8015 instrument must be used "
            "for a sensor..");
    }
    if (this->_owner == nullptr) {
        throw std::invalid_argument("The owning sensor array of a HMC 8015 "
            "sensor must not be null.");
    }
}
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */


/*
 * PWROWG_DETAIL_NAMESPACE::hmc8015_sensor::sample
 */
void PWROWG_DETAIL_NAMESPACE::hmc8015_sensor::sample(_In_ const bool enable) {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    using std::chrono::duration;
    using std::chrono::duration_cast;

    if (enable) {
        this->_state.begin_start();

        // Clamp the sampling interval according to the SCPI Programmer's
        // Manual p. 43.
        auto interval = duration_cast<duration<float>>(
            this->_owner->configuration->interval).count();
        if (interval < 0.1f) {
            interval = std::numeric_limits<float>::lowest();
        } else if (interval > 600.0f) {
            interval = (std::numeric_limits<float>::max)();
        }

        // Set the user-defined log file or create one.
        if (this->configuration().log_file() != nullptr) {
            this->_instrument.log_file(
                this->configuration().log_file(),
                true,
                this->configuration().log_to_usb());

        } else {
            // Unfortunately, the HMC8015 only supports 8.3 file names, so we
            // try to build a unique one ...
            std::stringstream file_name_builder;

            // TODO: find s.th. better here, e.g. base64
            auto timestamp = std::chrono::high_resolution_clock::now()
                .time_since_epoch().count();
            timestamp = timestamp & UINT_MAX ^ (timestamp >> 32);
            file_name_builder << std::hex
                << static_cast<std::uint32_t>(timestamp)
                << ".csv";

            auto file_name = file_name_builder.str();
            this->_instrument.log_file(
                file_name.c_str(),
                true,
                this->configuration().log_to_usb());
        }

        this->_instrument.integrator_behaviour(hmc8015_integrator_mode::manual);
        this->_instrument.log_behaviour(interval, hmc8015_log_mode::unlimited);
        this->_instrument.reset_integrator();
        this->_instrument.operation_complete();
        this->_instrument.start_integrator();
        this->_instrument.log(true);

        this->_state.end_start();

    } else {
        this->_state.begin_stop();

        // Stop integration and logging.
        this->_instrument.log(false);
        this->_instrument.stop_integrator();

        // Find out where the instrument wrote the data to.
        std::vector<char> log;
        log.resize(this->_instrument.log_file(nullptr, 0));
        this->_instrument.log_file(log.data(), log.size());

        {
            std::vector<char> logs;
            logs.resize(this->_instrument.list_files_on_instrument(nullptr, 0));
            this->_instrument.list_files_on_instrument(logs.data(), logs.size());
            logs.push_back('\r');
            logs.push_back('\n');
            ::OutputDebugStringA(logs.data());
        }

        // Patch the file name, because what is reported by the device is wrong.
        std::match_results<std::vector<char>::iterator> match;
        if (std::regex_match(log.begin(), log.end(), match, rx_log_patch)) {
            log.insert(match[1].first, { '.', 'C', 'S', 'V' });
        }

        this->_instrument.operation_complete();

        // Download the CSV file into memory.
        auto log_data = this->_instrument.copy_file_from_instrument_or_usb(
            log.data());
            //"\"63FE0D59.CSV\", INT");

        // Parse the samples and emit everything at once.
        std::stringstream log_stream(log_data);
        rapidcsv::Document csv(log_stream,
            rapidcsv::LabelParams(),
            rapidcsv::SeparatorParams(';', true),
            rapidcsv::ConverterParams(),
            rapidcsv::LineReaderParams(true, '#', true));

        // TODO
        //csv.GetRowNames();
        //URMS[V]; IRMS[A]; P[W]; FU[Hz]; EMPTY; EMPTY; S[VA]; Q[var]; LAMBDA[]; UTHD[%]; Timestamp
        //231.27E+00;45.0E-03;6.63E+00;50.0E+00;nan;nan;10.38E+00; 7.98E+00; 639E-03; 2E+00; 04:49:33:000

        // If using internal memory, delete the log file. If the user selected the
        // USB thumb drive, we assume the original data should be kept for
        // reference.
        if (!this->configuration().log_to_usb()) {
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

    builder.with_private_data(function);

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


/*
 * PWROWG_DETAIL_NAMESPACE::hmc8015_sensor::rx_log_patch
 */
const std::regex PWROWG_DETAIL_NAMESPACE::hmc8015_sensor::rx_log_patch(
    "^\".+(\").+$", std::regex::icase | std::regex::ECMAScript);


/*
 * PWROWG_DETAIL_NAMESPACE::hmc8015_sensor::configuration
 */
const PWROWG_DETAIL_NAMESPACE::hmc8015_sensor::configuration_type&
PWROWG_DETAIL_NAMESPACE::hmc8015_sensor::configuration(void) const noexcept {
    assert(this->_owner != nullptr);
    assert(this->_owner->configuration != nullptr);
    auto it = this->_owner->configuration->sensor_configs.find(
        configuration_type::id);
    assert(it != this->_owner->configuration->sensor_configs.end());
    return dynamic_cast<const configuration_type &>(*it->second);
}
