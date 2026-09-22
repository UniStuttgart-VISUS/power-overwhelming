// <copyright file="rtx_config.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "zero_adjust.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <optional>
#include <thread>
#include <vector>

#if defined(_WIN32)
#include <conio.h>
#endif /* defined(_WIN32) */


/// <summary>
/// Holds per-sensor data.
/// </summary>
struct sensor final {
    visus::pwrowg::rtx_channel channel;
    visus::pwrowg::rtx_instrument& instrument;
    const std::string measurement;
    float offset;

    inline sensor(_In_ visus::pwrowg::rtx_instrument& instrument,
            _In_ const visus::pwrowg::rtx_channel& channel,
            _In_ const std::size_t measurement)
        : channel(channel),
            instrument(instrument),
            measurement(std::string("MEAS") + std::to_string(measurement)),
            offset(0.0f) { }
};


/*
 * ::zero_adjust
 */
void zero_adjust(_In_z_ const TCHAR* path) {
    using namespace visus::pwrowg;
    assert(path != nullptr);

    std::wcout << L"Adjusting zero-level of current channels. Remove the "
        L"conductors from all current clamps and ";
#if defined(_WIN32)
    std::wcout << L"press any key to start the processs." << std::endl;
    ::getch();
#else /* !defined(_WIN32) */
    std::wcout << L"press Enter to start the processs." << std::endl;
    std::cin.get();
#endif /* !defined(_WIN32) */

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
            std::this_thread::sleep_for(delay);

            instrument.enable_system_checks(true);

            std::string path(instrument.path());
            instruments[path] = std::make_tuple(
            std::move(instrument),
            static_cast<std::size_t>(0));

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
            std::cerr << "Instrument " << sensor.path() << " was not found "
                "and will be ignored." << std::endl;
            continue;
        }

        auto& instrument = std::get<0>(it->second);
        const auto measure_idx = ++std::get<1>(it->second);
        sensors.emplace_back(instrument, sensor.current_channel(), measure_idx);

        auto channel = sensor.current_channel();
        channel.zero_offset(0.0f);
        channel.zero_adjust_offset(0.0f);
        instrument.channel(channel);

        // Configure measuring what the channel currently reports.
        {
            const auto cmd = sensors.back().measurement + ":MAIN RMS\n";
            instrument.write(cmd.c_str());
        }

        {
            const auto cmd = sensors.back().measurement + ":SOUR CH"
                + std::to_string(channel.channel()) + "\n";
            instrument.write(cmd.c_str());
        }
    }

    const auto get_measurement = []( const sensor& sensor) noexcept {
        const auto query = sensor.measurement + ":RES?\n";
        auto response = sensor.instrument.query(query.c_str());

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
            return std::optional<float>(std::stof(value));
        } catch (...) {
            return std::optional<float>();
        }
    };

    // Next, wait until we have a measurement.
    for (auto& s : sensors) {
        for (std::size_t i = 0; i < 8;) {
            const auto value = get_measurement(s);
            if (value) {
                s.offset -= *value;
                s.channel.zero_offset(s.offset);
                s.instrument.channel(s.channel);
                ++i;
            }
        }
    }
}
