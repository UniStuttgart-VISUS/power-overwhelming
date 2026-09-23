// <copyright file="rtx_config.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "zero_adjust.h"

#include <algorithm>
#include <cassert>
#include <charconv>
#include <limits>
#include <iomanip>
#include <iostream>
#include <map>
#include <optional>
#include <thread>
#include <vector>

#if defined(_WIN32)
#include <conio.h>
#endif /* defined(_WIN32) */

#include "visus/pwrowg/convert_string.h"


/// <summary>
/// Holds per-sensor data.
/// </summary>
struct sensor final {
    visus::pwrowg::rtx_channel channel;
    visus::pwrowg::rtx_instrument& instrument;
    const std::string measurement;
    float value;
    bool zero_adjust;

    inline sensor(_In_ visus::pwrowg::rtx_instrument& instrument,
            _In_ const visus::pwrowg::rtx_channel& channel,
            _In_ const std::size_t measurement)
        : channel(channel),
            instrument(instrument),
            measurement(std::string("MEAS") + std::to_string(measurement)),
            value(0.0f),
            zero_adjust(false) { }
};


/*
 * ::zero_adjust
 */
void zero_adjust(_In_z_ const TCHAR* path,
        _In_ const std::chrono::duration<float> range,
        _In_ const std::chrono::duration<float> degauss,
        _In_ const std::size_t retries,
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

            // Set a single acquisition such that the instrument does not start
            // automatically.
            instrument.acquisition(rtx_acquisition()
                .state(rtx_acquisition_state::single));

            // Disable automatic roll during the setup.
            instrument.automatic_roll(false);

            //// Set a trigger that we expect not to fire.
            //instrument.trigger(rtx_trigger(
            //    static_cast<rtx_trigger::input_type>(5),
            //    rtx_trigger_type::edge));

            // Override the time range to the user-defined value for averaging
            // the probe readings.
            instrument.time_range(range);

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
    std::vector<sensor> sensors;
    sensors.reserve(cnt_sensors);
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
            std::wcout << instrument_path << " can be degaussed." << std::endl;

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
            const auto cmd = sensors.back().measurement + ":MAIN RMS\n";
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
        instrument.acquisition(rtx_acquisition()
            .enable_automatic_points()
            .segmented(true)
            .state(rtx_acquisition_state::run));
        instrument.automatic_roll(true);
        instrument.operation_complete();
        instrument.throw_on_system_error();
    }

    std::wcout << L"All probes and instruments are ready." << std::endl
        << std::endl;

    const auto get_measurement = []( const sensor& sensor) noexcept {
        // Block until the measurement becomes available.
        auto query = sensor.measurement + ":RES?\n";
        auto response = sensor.instrument.query(query.c_str());

        // Read the average from the statistics.
        query = sensor.measurement + ":RES:AVG?\n";
        response = sensor.instrument.query(query.c_str());


        auto value = response.as<char>();
        assert(value != nullptr);
        for (std::size_t i = 0; i < response.size(); ++i) {
            if ((value[i] == '\n') || (value[i] == '\r')) {
                value[i] = 0;
            }
            // [sic]
            if (value[i] == 0) {
                break;
            }
        }

        try {
            const auto number = std::stof(value);
            if (number > 1.e37f) {
                // R&S reports something like FLT_MAX, but less, if the
                // measurement is not available.
                return std::optional<float>();
            }

            return std::optional<float>(number);
        } catch (std::exception& ex) {
            std::cout << "Parsing measurement \"" << value << "\" failed: "
                << ex.what();
            return std::optional<float>();
        }
    };


    // Next, wait until we have a measurement.
    constexpr auto title_adjustment = "Adjustment";
    constexpr auto title_channel = "Channel";
    constexpr auto title_instrument = "Instrument";
    constexpr auto title_mean = "Mean";
    constexpr auto title_measurement = "Measurement";
    constexpr auto title_offset = "Offset";
    constexpr auto precision = 6;
    constexpr auto width_adjustment = precision + 3;
    const auto width_channel = ::strlen(title_channel);
    const auto width_instrument = ::strlen(sensors.front().instrument.path());
    constexpr auto width_mean = precision + 3;
    const auto width_measurement = ::strlen(title_measurement);
    constexpr auto width_offset = precision + 3;
    auto success = false;

    for (std::size_t i = 0; !success && (i < retries + 1); ++i) {
        success = true;

        std::cout << std::setw(width_instrument) << title_instrument << " "
            << std::setw(width_channel) << title_channel << " "
            << std::setw(width_measurement) << title_measurement << " "
            << std::setw(width_mean) << title_mean << " "
            << std::setw(width_offset) << title_offset << " "
            << std::setw(width_adjustment) << title_adjustment << std::endl;

        // Get the measurement.
        for (auto& s : sensors) {
            try {
                const auto value = get_measurement(s);
                if (value) {
                    s.value = *value;
                } else {
                    success = false;
                }
            } catch (std::exception& ex) {
                success = false;
                std::cerr << ex.what() << std::endl;
            }
        } /* for (auto& s : sensors) */

        if (!success) {
            continue;
        }

        // Apply the results to the instrument.
        for (auto& s : sensors) {
                        std::cout << std::setw(width_instrument)
                << s.instrument.path()
                << " ";
            std::cout << std::setw(width_channel)
                << s.channel.channel()
                << " ";
            std::cout << std::setw(width_measurement)
                << s.measurement
                << " ";

            try {
                std::cout << std::setw(width_mean)
                    << std::fixed
                    << std::setprecision(precision)
                    << s.value << " ";

                const auto offset = -s.value;
                std::cout << std::setw(width_offset)
                    << std::fixed
                    << std::setprecision(precision)
                    << offset << " ";

                if (s.zero_adjust) {
                    const auto adjustment = offset / -3.0f * 100.0f;
                    std::cout << std::setw(width_adjustment)
                        << std::fixed
                        << std::setprecision(precision)
                        << adjustment
                        << std::endl;
                    s.channel.zero_adjust(adjustment);

                } else {
                    std::cout << std::setw(width_adjustment)
                        << "-"
                        << std::endl;
                    s.channel.zero_offset(offset);
                }

                s.instrument.channel(s.channel);
                s.instrument.operation_complete();
            } catch (std::exception& ex) {
                success = false;
                std::cerr << ex.what() << std::endl;
            }
        } /* for (auto& s : sensors) */
    } /* for (std::size_t i = 0; !success && (i < retries + 1); ++i) */
}
