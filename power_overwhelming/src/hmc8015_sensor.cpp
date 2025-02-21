// <copyright file="hmc8015_sensor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "hmc8015_sensor.h"

#include <array>
#include <cassert>
#include <stdexcept>

#include <rapidcsv.h>

#include "visus/pwrowg/blob_streambuf.h"
#include "visus/pwrowg/on_exit.h"

#include "sensor_array_impl.h"
#include "tokenise.h"


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

    // Determine which functions are actually enabled: the configured ones or
    // the default if the user did not provide anything special.
    auto funcs = config.functions();
    auto cnt_funcs = config.count_functions();

    if (funcs == nullptr) {
        funcs = default_functions.data();
        cnt_funcs = default_functions.size();
    }

    // Force output counter to be empty if no buffer was provided.
    if (dst == nullptr) {
        cnt = 0;
    }

    auto builder = sensor_description_builder::create()
        .with_vendor(L"Rohde & Schwarz")
        .with_type(sensor_type::hardware | sensor_type::external)
        .produces(reading_type::floating_point);

    try {
        if (cnt == 0) {
            // If we are only measuring, we do not open the device, because this
            // is expensive, but we only enumerate the device paths and multiply
            // them by the number of active functions.
            auto multiplier = 0;
            for (std::size_t f = 0; f < cnt_funcs; ++f) {
                if (specialise(builder, funcs[f])) {
                    ++multiplier;
                }
            }

            auto instruments = visa_instrument::find_resources(
                hmc8015_instrument::rohde_und_schwarz,
                hmc8015_instrument::product_id);

            retval = multi_sz<char>::count(instruments.as<char>()) * multiplier;

        } else {
            // If we have a request for actually retrieving the descriptors, we
            // need to connect to the devices in order to obtain the name.
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
                // Move the instrument to the heap, such that it can be shared
                // between the descriptors using the same hardware. The rationale
                // for this is that reconnecting multiple times to the same HMC
                // makes the whole process even more fragile than it already is,
                // so we want to avoid this. When the sensors are created, all
                // functions on the same instrument share the same sensor anyway.
                auto instrument = std::make_shared<hmc8015_instrument>(
                    std::move(i));

                instrument->reset(true, true);
                instrument->current_range(config.current_range(),
                    config.current_range_value());
                instrument->voltage_range(config.voltage_range(),
                    config.voltage_range_value());
                instrument->operation_complete();

                // Determine the unique path of the instrument, which we need to
                // connect the sensor to and which we need to build the ID.
                const auto path = instrument->path();
                if (path == nullptr) {
                    continue;
                }
                builder.with_path(path);

                //try {
                //    instrument->clear();
                //    instrument->operation_complete();
                //} catch (...) { /* If this fails, there was no I/O pending. */ }

                // Create the friendly name.
                {
                    std::vector<wchar_t> name;
                    name.resize(instrument->identify(name.data(), name.size()));
                    instrument->identify(name.data(), name.size());
                    builder.with_name(name.data());
                }

                // Create a descriptor for each function being recorded.
                for (std::size_t f = 0; f < cnt_funcs; ++f) {
                    if (specialise(builder, funcs[f])) {
                        if (cnt > 0) {
                            dst[retval] = builder
                                .with_id("%s/%ls", path, to_string(funcs[f]))
                                .with_new_private_data<private_data>(instrument, funcs[f])
                                .build();
                            --cnt;
                        }

                        ++retval;
                    }
                }

            } /* for (auto& i : instruments) */
        } /* if (cnt == 0) */

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
        _In_ const PWROWG_NAMESPACE::sample::source_type index,
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

        // Enable the requested functions.
        this->_instrument.custom_functions(this->_functions.data(),
            this->_functions.size());

        // Set the user-defined log file or create one.
        {
            const auto log = this->configuration().log_file();
            if (log != nullptr) {
                this->_instrument.log_file(
                    log,
                    true,
                    this->configuration().log_to_usb());

            } else {
                auto log = create_file_name();
                this->_instrument.log_file(
                    log.c_str(),
                    true,
                    this->configuration().log_to_usb());
            }
        }

        // Now, find out what the actual log file ist, because the device might
        // change that and once we started the logging, we cannot get the correct
        // name anymore, because the device then tells us what the next file
        // name would be if we restarted logging with the same name rather than
        // what the current log name actually is ...
        {
            this->_log.resize(this->_instrument.log_file(nullptr, 0));
            this->_instrument.log_file(this->_log.data(), this->_log.size());

            // We have the log name now, but we cannot use this to download the
            // data, because this requires the file name extension which is not
            // returned from the device. Therefore, patch the file name and
            // remember it for the download later on.
            //std::match_results<std::vector<char>::iterator> match;
            std::cmatch match;
            if (std::regex_match(this->_log.data(), match, rx_log_patch)) {
                auto d = match[1].first - this->_log.data();
                auto e = match[1].second - this->_log.data();
                auto l = std::string(match[2].first, match[2].second);

                {
                    auto it = this->_log.begin();
                    std::advance(it, e);
                    auto end = hmc8015_instrument::log_extension
                        + ::strlen(hmc8015_instrument::log_extension);
                    this->_log.insert(it,
                        hmc8015_instrument::log_extension,
                        end);
                }

                // There is a special case if we are on the USB thumb drive: the
                // instrument will log into the folder "DATA/" as it does
                // internally, but in contrast to internal memory, we need to
                // specify the full path for the external drive, so we patch
                // again and insert it. Note that as we compute the offsets from
                // the start, the patches to the file name need to be applied
                // back to front.
                if (equals(l, "EXT", true)) {
                    auto it = this->_log.begin();
                    std::advance(it, d);
                    auto end = hmc8015_instrument::ext_log_directory
                        + ::strlen(hmc8015_instrument::ext_log_directory);
                    this->_log.insert(it,
                        hmc8015_instrument::ext_log_directory,
                        end);
                }
            }
        }

        this->_instrument.integrator_behaviour(hmc8015_integrator_mode::manual);
        this->_instrument.log_behaviour(interval, hmc8015_log_mode::unlimited);
        this->_instrument.reset_integrator();
        this->_instrument.operation_complete();
        this->_instrument.start_integrator();
        this->_instrument.log(true);
        this->_instrument.display("hmc8015_sensor is active.");

        // Make sure that we explode if there was any error before. This usually
        // happens if logging fails, which is absolutely critical.
        this->_instrument.operation_complete();
        this->_instrument.throw_on_system_error();

        this->_state.end_start();

    } else {
        this->_state.begin_stop();

        auto grd_msg = on_exit([this](void) {
            this->_instrument.display(static_cast<char *>(nullptr));
        });

        // Stop integration and logging.
        this->_instrument.log(false);
        this->_instrument.stop_integrator();
        this->_instrument.operation_complete();
        this->_instrument.display("hmc8015_sensor is processing results.");

        //{
        //    std::vector<char> logs;
        //    logs.resize(this->_instrument.list_files_on_instrument(nullptr, 0));
        //    this->_instrument.list_files_on_instrument(logs.data(), logs.size());
        //    logs.push_back('\r');
        //    logs.push_back('\n');
        //    ::OutputDebugStringA(logs.data());
        //}

        // Download the CSV file into memory.
        //auto log_data = this->_instrument.copy_file_from_instrument_or_usb(
        //    this->_log.data());
        blob log_data;
        try {
           log_data = this->_instrument.copy_file_from_instrument_or_usb(
                this->_log.data());
        } catch (visa_exception) {
            // Second chance ...
            std::this_thread::sleep_for(this->configuration()
                .timeout_as<std::chrono::milliseconds>());
            this->_instrument.clear_status();
            log_data = this->_instrument.copy_file_from_instrument_or_usb(
                this->_log.data());
        }

        // Parse the samples and emit everything at once.
        blob_streambuf<char> log_buf(log_data);
        std::istream log_stream(&log_buf);
        rapidcsv::Document csv(log_stream,
            rapidcsv::LabelParams(),
            rapidcsv::SeparatorParams(';', true),
            rapidcsv::ConverterParams(),
            rapidcsv::LineReaderParams(true, '#', true));

        const auto columns = csv.GetColumnNames();
        std::vector<PWROWG_NAMESPACE::sample> samples;
        auto sensor = this->_index;
        const auto today = timestamp::today();

        // Get all the timestamps, which are time-only, so we need to offset it
        // by the date.
        // TODO: this is unsafe (especially at VISUS ;)). Refactor using date from header and detect date wraps.
        std::vector<timestamp> timestamps;

        {
            auto ts = csv.GetColumn<std::string>(
                this->configuration().timestamp_column());
            timestamps.reserve(ts.size());
            std::transform(ts.begin(),
                ts.end(),
                std::back_inserter(timestamps),
                [&today](const std::string& s) {
                    return today + parse_time(s);
                });
        }

        for (auto f : this->_functions) {
            auto func = PWROWG_NAMESPACE::convert_string<char>(to_string(f));
            auto it = std::find_if(columns.begin(),
                columns.end(),
                [&func](const std::string& c) {
                    return starts_with(c, func, true);
                });

            if (it != columns.end()) {
                auto col = csv.GetColumn<float>(*it);
                samples.clear();
                samples.reserve(col.size());

                for (auto r : col) {
                    samples.emplace_back(sensor, r);
                }

                this->_owner->configuration->callback(
                    samples.data(),
                    samples.size(),
                    this->_owner->descriptions.data(),
                    this->_owner->configuration->context);
            }

            ++sensor;
        }

        if (!this->configuration().log_to_usb()) {
            this->_instrument.delete_file_from_instrument_or_usb(
                this->_log.data());
        }

        this->_state.end_stop();
    }
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */
}


/*
 * PWROWG_DETAIL_NAMESPACE::hmc8015_sensor::create_file_name
 */
std::string PWROWG_DETAIL_NAMESPACE::hmc8015_sensor::create_file_name(void) {
    // Unfortunately, the HMC8015 only supports 8.3 file names, so we try to
    // build a unique one within that range without simply using an RFC time
    // stamp.
    std::stringstream builder;

    // TODO: find s.th. better here, e.g. base64
    auto timestamp = std::chrono::high_resolution_clock::now()
        .time_since_epoch().count();
    timestamp = timestamp & UINT_MAX ^ (timestamp >> 32);

    builder << std::hex
        << std::uppercase
        << static_cast<std::uint32_t>(timestamp);

    return builder.str();
}


/*
 * PWROWG_DETAIL_NAMESPACE::hmc8015_sensor::parse_time
 */
std::chrono::milliseconds PWROWG_DETAIL_NAMESPACE::hmc8015_sensor::parse_time(
        _In_ const std::string& time) {
    // TODO: performance (avoid copies).
    std::chrono::milliseconds retval(0);

    const auto tokens = tokenise_if(time,
        [](const char c) {
            return ((c == ':') || (c == '.'));
        },
        true);
    if ((tokens.size() < 2) || (tokens.size() > 4)) {
        throw std::invalid_argument("The specified input does not represent a "
            "valid time of day.");
    }

    retval += std::chrono::hours(std::stoi(tokens[0]));
    retval += std::chrono::minutes(std::stoi(tokens[1]));

    if (tokens.size() > 2) {
        retval += std::chrono::seconds(std::stoi(tokens[2]));
    }

    if (tokens.size() > 3) {
        retval += std::chrono::milliseconds(std::stoi(tokens[3]));
    }

    return retval;
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


/*
 * PWROWG_DETAIL_NAMESPACE::hmc8015_sensor::rx_log_patch
 */
const std::regex PWROWG_DETAIL_NAMESPACE::hmc8015_sensor::rx_log_patch(
    "^\"([^\"]+)\"\\s*,\\s*([A-Z]+)$", std::regex::icase);
//    "^\"(.+)\"\\s*,\\s*([A-Z]+)$", std::regex::icase);


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
