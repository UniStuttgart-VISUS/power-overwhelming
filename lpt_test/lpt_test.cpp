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
#include <fstream>
#include <iostream>
#include <thread>

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
    using std::chrono::duration_cast;
    typedef std::chrono::steady_clock clock_type;
    typedef std::chrono::microseconds output_type;

    const std::vector<std::basic_string<TCHAR>> cmd_line(argv, argv + argc);

    rtx_instrument::channel_type channel = 1;
    std::chrono::seconds download_timeout(10);
    rtx_instrument instrument;
    std::basic_string<TCHAR> instrument_id;
    std::basic_string<TCHAR> output(_T("lpt_test.csv"));
    std::basic_string<TCHAR> port(_T("LPT3"));
    std::chrono::milliseconds pulse(100);
    std::chrono::seconds time(5);
    std::chrono::milliseconds wait_reset(500);
    std::basic_string<TCHAR> waveform(_T("lpt_test_waveform.csv"));

    try {
        {
            auto it = ::find_argument(cmd_line.begin(), cmd_line.end(),
                _T("--channel"));
            if (it != cmd_line.end()) {
                channel = std::stoi(*it);
            }
        }

        {
            auto it = ::find_argument(cmd_line.begin(), cmd_line.end(),
                _T("--download-timeout"));
            if (it != cmd_line.end()) {
                download_timeout = std::chrono::seconds(std::stoi(*it));
            }
        }

        {
            auto it = ::find_argument(cmd_line.begin(), cmd_line.end(),
                _T("--instrument"));
            if (it != cmd_line.end()) {
                instrument_id = *it;
            }
        }

        {
            auto it = ::find_argument(cmd_line.begin(), cmd_line.end(),
                _T("--output"));
            if (it != cmd_line.end()) {
                output = *it;
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

        {
            auto it = ::find_argument(cmd_line.begin(), cmd_line.end(),
                _T("--wait-reset"));
            if (it != cmd_line.end()) {
                wait_reset = std::chrono::milliseconds(std::stoi(*it));
            }
        }

        {
            auto it = ::find_argument(cmd_line.begin(), cmd_line.end(),
                _T("--waveform"));
            if (it != cmd_line.end()) {
                waveform = *it;
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
            .enable_automatic_points());
        config.trigger(rtx_trigger::edge(channel)
            .slope(rtx_trigger_slope::rising)
            .level(rtx_quantity(1.5f, "V"))
            .mode(rtx_trigger_mode::normal));
        config.reference_position(rtx_reference_point::middle);
        {
            const auto range = config.time_range();
            const rtx_quantity offset(range.value() / 2.0f, range.unit());
            config.trigger_position(offset);
        }
        config.channel(rtx_channel(channel)
            .state(true)
            .attenuation(1.0f, "V")
            .bandwidth(rtx_channel_bandwidth::full)
            .coupling(rtx_channel_coupling::direct_current_limit)
            .range(rtx_quantity(8.0f, "V")));

        std::wcout << L"Setting up instrument ..." << std::endl;
        instrument.reset();
        std::this_thread::sleep_for(wait_reset);
        config.apply(instrument);

        std::wcout << L"Setting up trigger ..." << std::endl;
        parallel_port_trigger trigger(port.c_str());
        trigger.write(parallel_port_pin::none);
        instrument.acquisition(rtx_acquisition_state::single);

        std::wcout << L"Measuring ..." << std::endl;
        const auto deadline = clock_type::now() + time;
        std::vector<clock_type::time_point> begin, risen, drain, end;
        begin.reserve(static_cast<std::size_t>(std::ceil(time / pulse)));
        risen.reserve(begin.capacity());
        drain.reserve(begin.capacity());
        end.reserve(begin.capacity());

        while (clock_type::now() < deadline) {
            begin.push_back(clock_type::now());
            trigger.write(parallel_port_pin::all);
            risen.push_back(clock_type::now());

            while (clock_type::now() < begin.back() + pulse);

            drain.push_back(clock_type::now());
            trigger.write(parallel_port_pin::none);
            end.push_back(clock_type::now());

            while (clock_type::now() < end.back() + pulse);
        }

        instrument.operation_complete();

        std::wcout << L"Writing timings ..." << std::endl;
        std::ofstream stream(output.c_str(), std::ios::trunc);
        stream << "rise [us],up [us],drain [us]" << std::endl;

        assert(risen.size() == begin.size());
        assert(drain.size() == begin.size());
        assert(end.size() == begin.size());
        for (std::size_t i = 0; i < begin.size(); ++i) {
            stream << duration_cast<output_type>(risen[i] - begin[i]).count() << ",";
            stream << duration_cast<output_type>(drain[i] - risen[i]).count() << ",";
            stream << duration_cast<output_type>(end[i] - drain[i]).count() << std::endl;
        }

        std::wcout << L"Downloading waveform ..." << std::endl;
        const auto data = instrument.data(channel,
            rtx_waveform_points::maximum,
            duration_cast<std::chrono::milliseconds>(download_timeout).count());
        const auto range = instrument.time_range();

        std::wcout << L"Writing waveform ..." << std::endl;
        stream = std::ofstream(waveform, std::ios::trunc);
        stream << "volts (" << range.value() << range.unit() << ")"
            << std::endl;
        for (auto d : data) {
            stream << d << std::endl;
        }

        std::wcout << L"Done." << std::endl;
        return 0;
    } catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
        return -1;
    }
}
