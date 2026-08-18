// <copyright file="lpt_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/parallel_port_trigger.h"
#include "visus/pwrowg/rtx_instrument.h"
#include "visus/pwrowg/rtx_instrument_configuration.h"

#include <cassert>
#include <chrono>
#include <iostream>

#if defined(_WIN32)
#include <Windows.h>
#include <tchar.h>
#endif /* defined(_WIN32) */

#if !defined(_tmain)
#define _tmain main
#define TCHAR char
#define _T(x) (x)
#endif /* !defined(_tmain) */


/// <summary>
/// Find a switch in the given range of command line arguments.
/// </summary>
template<class TIterator> static TIterator find_switch(
        _In_ const TIterator begin,
        _In_ const TIterator end,
        _In_z_ const TCHAR *name) {
    assert(name != nullptr);
    for (auto it = begin; it != end; ++it) {
        if (*it == name) {
            return it;
        }
    }
    return end;
}


/// <summary>
//// Find an argument in the given range of command line arguments.
/// </summary>
template<class TIterator> static TIterator find_argument(
        _In_ const TIterator begin,
        _In_ const TIterator end,
        _In_z_ const TCHAR *name) {
    assert(name != nullptr);
    auto it = find_switch(begin, end, name);
    if (it != end) {
        ++it;
    }
    return it;
}


/// <summary>
/// Entry point of the lpt_test application, which tests the timing of
/// the parallel port trigger with an oscilloscope.
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
int _tmain(const int argc, const TCHAR **argv) {
    using namespace visus::pwrowg;
    typedef std::chrono::steady_clock clock_type;

    const std::vector<std::basic_string<TCHAR>> cmd_line(argv, argv + argc);

    rtx_instrument::channel_type channel = 1;
    rtx_instrument instrument;
    std::basic_string<TCHAR> instrument_id;
    std::basic_string<TCHAR> port(_T("LPT3"));
    std::chrono::milliseconds pulse(10);
    std::chrono::seconds time(5);

    try {
        {
            auto it = ::find_argument(cmd_line.begin(), cmd_line.end(),
                _T("--instrument"));
            if (it != cmd_line.end()) {
                instrument_id = *it;
            }
        }

        {
            auto it = ::find_argument(cmd_line.begin(), cmd_line.end(),
                _T("--channel"));
            if (it != cmd_line.end()) {
                channel = std::stoi(*it);
            }
        }

        {
            auto it = ::find_argument(cmd_line.begin(), cmd_line.end(),
                _T("--port"));
            if (it != cmd_line.end()) {
                port = *it;
            }
        }

        {
            auto it = ::find_argument(cmd_line.begin(), cmd_line.end(),
                _T("--pulse"));
            if (it != cmd_line.end()) {
                pulse = std::chrono::milliseconds(std::stoi(*it));
            }
        }

        {
            auto it = ::find_argument(cmd_line.begin(), cmd_line.end(),
                _T("--time"));
            if (it != cmd_line.end()) {
                time = std::chrono::seconds(std::stoi(*it));
            }
        }

        if (instrument_id.empty()) {
            std::vector<rtx_instrument> is(rtx_instrument::all(nullptr, 0));
            rtx_instrument::all(is.data(), is.size());
            if (is.empty()) {
                throw std::invalid_argument("No instruments found.");
            }
            instrument = std::move(is.front());

        } else {
            try {
                instrument = rtx_instrument::from_name(instrument_id.c_str());
            } catch (...) {
                instrument = rtx_instrument(instrument_id.c_str());
            }
        }

        rtx_instrument_configuration config(time);
        config.acquisition(rtx_acquisition()
            .state(rtx_acquisition_state::single)
            .enable_automatic_points());
        config.trigger(rtx_trigger::edge(channel)
            .slope(rtx_trigger_slope::rising)
            .level(rtx_quantity(2.5f, "V"))
            .mode(rtx_trigger_mode::normal));
        config.reference_position(rtx_reference_point::middle);
        {
            const auto range = config.time_range();
            const rtx_quantity offset(range.value() / 2.0f, range.unit());
            config.trigger_position(offset);
        }
        config.channel(rtx_channel(channel)
            .attenuation(0.1f, "V")
            .bandwidth(rtx_channel_bandwidth::full)
            .coupling(rtx_channel_coupling::direct_current_limit)
            .range(rtx_quantity(4.0f, "V")));

        instrument.reset();
        config.apply(instrument);

        parallel_port_trigger trigger(port.c_str());

        const auto deadline = clock_type::now() + time;

        while (clock_type::now() < deadline) {
            const auto b = clock_type::now();
            trigger.write(parallel_port_pin::all);
            const auto u = clock_type::now();

            while (clock_type::now() < u + pulse);

            const auto d = clock_type::now();
            trigger.write(parallel_port_pin::none);
            const auto e = clock_type::now();

            while (clock_type::now() < e + pulse);
        }

        return 0;
    } catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
        return -1;
    }
}
