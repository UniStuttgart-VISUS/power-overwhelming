// <copyright file="rtx_config.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "zero_adjust.h"

#include <algorithm>
#include <cassert>
#include <cerrno>
#include <charconv>
#include <cstdio>
#include <ctime>
#include <limits>
#include <list>
#include <memory>
#include <iomanip>
#include <iostream>
#include <map>
#include <optional>
#include <thread>
#include <tuple>
#include <vector>

#if defined(_WIN32)
#include <conio.h>
#endif /* defined(_WIN32) */

#include "visus/pwrowg/convert_string.h"
#include "visus/pwrowg/rtx_configuration.h"
#include "visus/pwrowg/string_functions.h"


/// <summary>
/// The valid (100%) range of the ZADJ parameter.s
/// </summary>
static constexpr auto zadj_range = 3.0f;

static constexpr auto title_adjustment = "Adjustment";
static constexpr auto title_channel = "Channel";
static constexpr auto title_instrument = "Instrument";
static constexpr auto title_latest = "Latest";
static constexpr auto title_measurement = "Measurement";
static constexpr auto title_offset = "Offset";
static constexpr auto title_type = "Type";
static constexpr auto title_value = "Value";
static constexpr auto title_waveforms = "Waveforms";

static constexpr auto precision = 6;
static constexpr auto width_adjustment = precision + 3;
static const auto width_channel = ::strlen(title_channel);
static constexpr auto width_latest = precision + 3;
static const auto width_measurement = ::strlen(title_measurement);
static constexpr auto width_offset = precision + 3;
static const auto width_type = ::strlen(title_type);
static constexpr auto width_value = precision + 3;
static const auto width_waveforms = ::strlen(title_waveforms);

/// <summary>
/// Groups the result of a measurement.
/// </summary>
struct measurement final {
    std::size_t count;
    float value;
    float mean;

    inline measurement(_In_ const float value = 0.0f,
            _In_ const float mean = 0.0f,
            _In_ const std::size_t count = 0) noexcept
        : count(count), value(value), mean(mean) { }
};


/// <summary>
/// Holds per-sensor data.
/// </summary>
struct sensor final {
    visus::pwrowg::rtx_channel channel;
    visus::pwrowg::rtx_instrument& instrument;
    std::string instrument_name;
    std::string measurement;
    float value;
    bool zero_adjust;

    inline sensor(_In_ visus::pwrowg::rtx_instrument& instrument,
            _In_ const visus::pwrowg::rtx_channel& channel,
            _In_ const std::size_t measurement)
        : channel(channel),
            instrument(instrument),
            instrument_name(instrument.path()),
            measurement(std::string("MEAS") + std::to_string(measurement)),
            value(0.0f),
            zero_adjust(false) {
        auto name = this->instrument.name<char>();
        if (!name.empty()) {
            this->instrument_name += " (" + name + ")";
        }
    }

    inline float percent(void) noexcept {
        return - value / zadj_range * 100.0f;
    }
};


/// <summary>
/// Makes sure that the response in <paramref name="blob" /> is null-terminated.
/// </summary>
/// <param name="blob"></param>
/// <returns></returns>
static _Ret_maybenull_z_ const char* terminate_response(
        _In_ visus::pwrowg::blob& blob) noexcept {
    auto retval = blob.as<char>();
    if (retval == nullptr) {
        return retval;
    }

    visus::pwrowg::detail::trim_eol(retval);
    return retval;
}


/// <summary>
/// Gets the measurement for the given <paramref name="sensor" />, which might
/// block.
/// </summary>
static std::optional<measurement> get_measurement(
        _In_ const sensor& sensor) noexcept {
    // R&S reports something like FLT_MAX, but a bit less, if the measurement is
    // not available. This seems to be a reasonable threshold for us to detect
    // this case.s
    constexpr auto invalid_value = 1.e37f;

    try {
        measurement retval;

        {
            const auto query = sensor.measurement + ":RES?\n";
            auto response = sensor.instrument.query(query.c_str());
            const auto value = ::terminate_response(response);

            retval.value = std::stof(value);
            if (retval.value >= invalid_value) {
                return std::optional<measurement>();
            }
        }

        {
            const auto query = sensor.measurement + ":RES:AVG?\n";
            auto response = sensor.instrument.query(query.c_str());
            const auto value = ::terminate_response(response);

            retval.mean = std::stof(value);
            if (retval.mean >= invalid_value) {
                return std::optional<measurement>();
            }
        }

        {
            const auto query = sensor.measurement + ":RES:WFMC?\n";
            auto response = sensor.instrument.query(query.c_str());
            const auto value = ::terminate_response(response);

            retval.count = std::stoul(value);
        }

        return retval;
    } catch (...) {
        return std::optional<measurement>();
    }
};


/*
 * ::zero_adjust
 */
void zero_adjust(_In_z_ const TCHAR* path,
        _In_ const std::chrono::duration<float> horizontal,
        _In_ const visus::pwrowg::rtx_quantity& vertical,
        _In_ const std::chrono::duration<float> degauss,
        _In_ const std::size_t waveforms,
        _In_opt_z_ const TCHAR* type,
        _In_ const bool no_wait,
        _In_ const bool apply) {
    using namespace visus::pwrowg;
    assert(path != nullptr);

    if (!no_wait) {
        std::wcout << L"Adjusting zero-level of current channels. Remove the "
            L"conductors from all current clamps, perform hardware zero "
            L"adjustment on the probe where applicable and ";
#if defined(_WIN32)
        std::wcout << L"press any key to start the processs." << std::endl;
        ::getch();
#else /* !defined(_WIN32) */
        std::wcout << L"press Enter to start the processs." << std::endl;
        std::cin.get();
#endif /* !defined(_WIN32) */
        std::cout << std::endl;
    }

    const auto config = rtx_configuration::load(path);
    const auto cnt_sensors = config.count_sensors();
    const auto delay = std::chrono::milliseconds(config.reset_delay());

    // Build a LUT by path for all instruments. At the same time, reset all
    // instruments and apply the base configuration.
    std::map<std::string, std::tuple<rtx_instrument, std::size_t>> instruments;

    {
        std::vector<rtx_instrument> i(rtx_instrument::all(nullptr, 0));
        const auto cnt = rtx_instrument::all(i.data(), i.size());

        for (std::size_t j = 0; j < cnt; ++j) {
            auto& instrument = i[j];

            instrument.reset(config.reset_flags());

            instrument.reset(config.reset_flags());
            std::this_thread::sleep_for(delay);
            config.base_configuration().apply(instrument);

            // Set a trigger that we expect not to fire because we will do that
            // manually later on.
            instrument.automatic_roll(false);
            instrument.trigger(rtx_trigger(
                static_cast<rtx_trigger::input_type>(5),
                rtx_trigger_type::edge));

            // Override the time range to the user-defined value for averaging
            // the probe readings.
            instrument.time_range(horizontal);

            std::string path(instrument.path());
            instruments[path] = std::make_tuple(
                std::move(instrument),
                static_cast<std::size_t>(0));
            assert(!instrument);

            std::this_thread::sleep_for(delay);
            std::get<0>(instruments[path]).operation_complete();
            std::get<0>(instruments[path]).throw_on_system_error();

            std::cout << "Instrument " << path << " is ready." << std::endl;
        }
    }

    // Setup measuring the current value of the current channels with zero
    // offset. Remember the measurement channel for each sensor and the path
    // to the instrument it is located on.
    std::list<sensor> sensors;
    //sensors.reserve(cnt_sensors);
    for (std::size_t i = 0; i < cnt_sensors; ++i) {
        const auto& sensor = config.sensor(i);

        auto it = instruments.find(sensor.path());
        if (it == instruments.end()) {
            std::cerr << "Instrument " << sensor.path() << " for sensor ";
            std::wcerr << sensor.description() << L" was not found and will be "
                L"ignored." << std::endl;
            continue;
        }

        auto& instrument = std::get<0>(it->second);
        const auto measure_idx = ++std::get<1>(it->second);
        sensors.emplace_back(instrument, sensor.current_channel(), measure_idx);
        const auto instrument_path = convert_string<wchar_t>(sensor.path());

        // Configure the channel to use an offset of zero regardless of what we
        // got fromthe JSON file.
        auto& channel = sensors.back().channel;
        std::vector<wchar_t> channel_name(channel.name(nullptr, 0));
        channel.name(channel_name.data(), channel_name.size());
        channel.offset(rtx_quantity(0.0f, "A"));
        channel.range(vertical);
        if (channel.zero_adjust()) {
            channel.zero_adjust(0.0f);
        } else {
            channel.zero_offset(0.0f);
        }
        instrument.channel(channel);

        // Sync point for isolation issues caused by the channel configuration.
        instrument.operation_complete();
        instrument.throw_on_system_error();
        std::wcout << L"Sensor " << sensor.description()
            << L" using " << channel_name.data()
            << L" on instrument " << instrument_path
            << L" has been configured for zero adjustment." << std::endl;

        // Try to degauss the probe if possible.
        try {
            const auto cmd = std::string("PROB")
                + std::to_string(channel.channel())
                + ":SET:DEG\n";
            instrument.write(cmd.c_str());

            //  Always demagnetize the probe before measurement. The
            // demagnetizing process takes about one second.
            std::this_thread::sleep_for(degauss);

            // Wait for the configuration to be applied and check whether it
            // was successful.
            instrument.operation_complete();
            instrument.throw_on_system_error();
            std::cout << "PROB" << channel.channel() << " on instrument ";
            std::wcout << instrument_path << " was degaussed." << std::endl;

            sensors.back().zero_adjust = true;
        } catch (...) {
            std::cout << "PROB" << channel.channel() << " on instrument ";
            std::wcout << instrument_path << " cannot be degaussed "
                "programmatically." << std::endl;
            instrument.clear_status();
            sensors.back().zero_adjust = false;
        }

        // Setup the measurement which gives us the current level of the probe.
        {
            const auto cmd = sensors.back().measurement + ":ENAB OFF\n";
            instrument.write(cmd.c_str());
        }

        {
            auto cmd = sensors.back().measurement + ":MAIN ";
            if (type == nullptr) {
                cmd += "MEAN\n";
            } else {
                cmd += convert_string<char>(type) + "\n";
            }

            instrument.write(cmd.c_str());
        }

        {
            const auto cmd = sensors.back().measurement + ":SOUR CH"
                + std::to_string(sensors.back().channel.channel()) + "\n";
            instrument.write(cmd.c_str());
        }

        {
            const auto cmd = sensors.back().measurement + ":TIM:AUTO ON\n";
            instrument.write(cmd.c_str());
        }

        {
            const auto cmd = sensors.back().measurement + ":STAT ON\n";
            instrument.write(cmd.c_str());
        }

        std::cout << sensors.back().measurement << " has been set up on "
            "instrument " << instrument.path() << "." << std::endl;
    }

    // Put all instruments in free run mode.
    for (auto& i : instruments) {
        auto& instrument = std::get<0>(i.second);

        instrument.operation_complete();
        instrument.throw_on_system_error();
    } /* for (std::size_t i = 0; i < cnt_sensors; ++i) */

    // Sort the sensors such that the ones on the same instrument are
    // contiguous.
    sensors.sort([](const auto& l, const auto& r) {
        const auto d = ::strcmp(l.instrument.path(), r.instrument.path());
        return (d < 0) || ((d == 0) && (l.channel.channel()
            < r.channel.channel()));
    });

    // If we have all current sensors, we can determine the width of the
    // column.
    const auto width_instrument = std::max_element(sensors.begin(),
        sensors.end(), [](const auto& l, const auto& r) {
            return l.instrument_name.size() < r.instrument_name.size();
        })->instrument_name.size();

    // Start a rolling acquisition on all instruments.B
    for (auto& i : instruments) {
        auto& instrument = std::get<0>(i.second);
        instrument.automatic_roll(true);
        instrument.automatic_roll_time(horizontal / 12);
        instrument.acquisition(rtx_acquisition()
            .enable_automatic_points()
            .segmented(false)
            .state(rtx_acquisition_state::run));
    }

    // Signal the user that we are ready to start measuring. This is for the
    // crazy people who use --no-wait and dagauss the hardware during setup...
    std::wcout << L"All probes and instruments are ready." << std::endl
        << std::endl;
    for (auto& i : instruments) {
        std::get<0>(i.second).beep(3);
    }

    // Next, wait until we have the requested number of measurements.
    std::cout << std::setw(width_instrument) << title_instrument << " "
        << std::setw(width_channel) << title_channel << " "
        << std::setw(width_measurement) << title_measurement << " "
        << std::setw(width_latest) << title_latest << " "
        << std::setw(width_latest) << title_waveforms << " "
        << std::setw(width_offset) << title_offset << " "
        << std::setw(width_adjustment) << title_adjustment << std::endl;

    auto missing_waveforms = true;
    while (missing_waveforms) {
        missing_waveforms = false;

        for (auto& i : instruments) {
            std::get<0>(i.second).trigger_manually();
        }

        std::this_thread::sleep_for(horizontal);

        for (auto& s : sensors) {
            const auto value = ::get_measurement(s);
            if (value) {
                s.value = value->mean;

                std::cout << std::setw(width_instrument)
                    << s.instrument_name
                    << " ";
                std::cout << std::setw(width_channel)
                    << s.channel.channel()
                    << " ";
                std::cout << std::setw(width_measurement)
                    << s.measurement
                    << " ";
                std::cout << std::setw(width_latest)
                    << value->value
                    << " ";
                std::cout << std::setw(width_waveforms)
                    << value->count
                    << " ";

                std::cout << std::setw(width_offset)
                    << s.value
                    << " ";

                if (s.zero_adjust) {
                    std::cout << std::setw(width_adjustment)
                        << std::fixed
                        << std::setprecision(precision)
                        << s.percent()
                        << std::endl;

                } else {
                    std::cout << std::setw(width_adjustment)
                        << "-"
                        << std::endl;
                }

                if (value->count < waveforms) {
                    missing_waveforms = true;
                }
            } else {
                missing_waveforms = true;
            } /* if (value) */
        }/* for (auto& s : sensors) */
    } /* while (missing_waveforms) */

    // Apply the results to the instrument.
    for (auto& s : sensors) {
        if (s.zero_adjust) {
            s.channel.zero_adjust(s.percent());
        } else {
            s.channel.zero_offset(s.value);
        }

        s.instrument.channel(s.channel);
        s.instrument.operation_complete();
        s.instrument.beep();
        
    } /* for (auto& s : sensors) */

    // Apply or print the results.
    std::cout << std::endl;
    if (apply) {
        constexpr auto time_length = 8 + 6;
        auto backup = convert_string<char>(path) + ".";

        time_t time;
        std::time(&time);
        auto tm = ::localtime(&time);

        const auto offset = backup.size();
        backup.resize(backup.size() + time_length);
        if (::strftime(&backup[0] + offset, time_length + 1, "%Y%m%d%H%M%S",
                tm) <= 0) {
            throw std::runtime_error("Failed to format timestamp for backup "
                "file.");
        }
        backup += ".json";

        std::cout << "Creating backup " << backup << " of configuration "
            "file ..." << std::endl;
        if (::rename(path, backup.c_str()) < 0) {
#if defined(_WIN32)
            throw std::system_error(_doserrno, std::system_category());
#else /* !defined(_WIN32) */
            throw std::system_error(errno, std::system_category());
#endif /* !defined(_WIN32) */
        }

        std::vector<rtx_sensor_definition> patched_sensors(
            config.count_sensors());
        std::copy(config.sensors(), config.sensors() + config.count_sensors(),
            patched_sensors.begin());

        for (auto& p : patched_sensors) {
            rtx_channel channel(p.current_channel());

            // Patch the copy of the channel.
            for (auto& s : sensors) {
                if (!visus::pwrowg::detail::equals(s.instrument.path(),
                        p.path())) {
                    continue;
                }
                if (s.channel.channel() != channel.channel()) {
                    continue;
                }

                if (s.zero_adjust) {
                    channel.zero_adjust(s.percent());
                } else {
                    channel.zero_offset(s.value);
                }
            }

            // Replace the sensor definition with a patched one.
            p = rtx_sensor_definition(p.path(),
                p.voltage_channel(),
                channel,
                p.description(),
                p.waveform_points());
        }

        std::wcout << "Saving patched configuration to "
            << visus::pwrowg::convert_string<wchar_t>(path) << " ..."
            << std::endl;
        auto patched_config = config;
        patched_config.sensors(patched_sensors.data(), patched_sensors.size());
        patched_config.save(path);

    } else {
        std::cout << std::setw(width_instrument) << title_instrument << " "
            << std::setw(width_channel) << title_channel << " "
            << std::setw(width_type) << title_type << " "
            << std::setw(width_value) << title_value << std::endl;

        for (auto& s : sensors) {
            std::cout << std::setw(width_instrument)
                << s.instrument_name
                << " ";
            std::cout << std::setw(width_channel)
                << s.channel.channel()
                << " ";
            std::cout << std::setw(width_type)
                << (s.zero_adjust ? "ZADJ" : "ZOFF")
                << " ";
            std::cout << std::setw(width_value)
                << std::fixed
                << std::setprecision(precision)
                << (s.zero_adjust ? s.percent() : s.value)
                << std::endl;
        }
    }
}
