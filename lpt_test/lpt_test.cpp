// <copyright file="lpt_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/parallel_port_trigger.h"
#include "visus/pwrowg/rtx_instrument.h"
#include "visus/pwrowg/rtx_instrument_configuration.h"

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <thread>
#include <vector>

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
/// Derives a file name from the user-specified output path.
/// </summary>
std::basic_string<TCHAR> derive_filename(
        _In_ const std::basic_string<TCHAR>& path,
        _In_z_ const TCHAR *suffix,
        _In_z_ const TCHAR *ext = _T(".csv")) {
    assert(suffix != nullptr);
    assert(ext != nullptr);
    assert(*ext == _T('.'));
    constexpr auto npos = std::basic_string<TCHAR >::npos;
    const auto fb = path.find_last_of(_T("/\\"));
    const auto eb = path.find_last_of(_T("."));

    if ((eb == npos) || (fb > eb)) {
        return path + suffix + ext;
    } else {
        return path.substr(0, eb) + suffix + path.substr(eb);
    }
}


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
/// Computes the bilevel waveform pulse width in number of samples.
/// </summary>
template<class TOut, class TIn>
static typename std::iterator_traits<TIn>::value_type pulse_width(
        _In_ TOut oit, _In_ const TIn begin, _In_ const TIn end,
        _In_ std::size_t bins = 64) {
    typedef std::iterator_traits<TIn> traits_type;
    const auto range = std::minmax_element(begin, end);
    auto retval = static_cast<typename traits_type::value_type>(0);

    // State-level estimation.
    if (bins < 4) {
        bins = 4;
    } else {
        bins &= ~0x1;
    }

    const auto bin = [range, bins](const auto value) {
        const auto v = value - *range.first;
        const auto r = *range.second - *range.first;
        return static_cast<std::size_t>(std::floor(v / r * (bins - 1)));
    };

    std::vector<std::size_t> histogram(bins, 0);
    for (auto it = begin; it != end; ++it) {
        ++histogram[bin(*it)];
    }

    const auto mode = [range, bins, histogram](
            const decltype(histogram.begin()) b,
            const decltype(histogram.end()) e,
            std::size_t offset) {
        const auto r = *range.second - *range.first;
        const auto m = std::max_element(b, e);

        std::size_t c = 0;
        auto s = static_cast<typename traits_type::value_type>(0);
        for (auto it = b; it != e; ++it, ++offset) {
            if (*it == *m) {
                s += *range.first + (offset + 0.5f) * r / bins;
                ++c;
            }
        }

        return s / c;
    };

    const auto split = histogram.begin() + (bins >> 1);
    const auto low = mode(histogram.begin(), split, 0);
    const auto high = mode(split, histogram.end(), bins >> 1);
    const auto threshold = (low + high) / 2;

    std::size_t i = 0;
    std::size_t pulses = 0;
    bool state = (*begin > threshold);
    std::size_t start = 0;
    for (auto it = begin; it != end; ++it, ++i) {
        if (state) {
            state = (*it <= threshold);
            if (!state) {
                const auto w = i - start;
                retval += w;
                *oit++ = w;
                ++pulses;
            }

        } else {
            state = (*it >= threshold);
            if (state) {
                start = i;
            }
        }
    }

    retval /= pulses;
    return retval;
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
    using std::chrono::milliseconds;
    using std::chrono::seconds;
    typedef std::chrono::steady_clock clock_type;
    typedef std::chrono::microseconds output_type;

    const std::vector<std::basic_string<TCHAR>> cmd_line(argv, argv + argc);

    rtx_instrument::channel_type channel = 1;
    seconds download_timeout(10);
    rtx_instrument instrument;
    std::basic_string<TCHAR> instrument_id;
    std::basic_string<TCHAR> output(_T("lpt_test.csv"));
    std::basic_string<TCHAR> port(_T("LPT3"));
    milliseconds pulse(100);
    seconds time(5);
    milliseconds wait_reset(500);

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
        std::vector<clock_type::time_point> brise, erise, bfall, efall;
        brise.reserve(static_cast<std::size_t>(std::ceil(time / pulse)));
        erise.reserve(brise.capacity());
        bfall.reserve(brise.capacity());
        efall.reserve(brise.capacity());

        while (clock_type::now() < deadline) {
            brise.push_back(clock_type::now());
            trigger.write(parallel_port_pin::all);
            erise.push_back(clock_type::now());

            while (clock_type::now() < brise.back() + pulse);

            bfall.push_back(clock_type::now());
            trigger.write(parallel_port_pin::none);
            efall.push_back(clock_type::now());

            while (clock_type::now() < efall.back() + pulse);
        }

        instrument.operation_complete();

        std::wcout << L"Writing timings ..." << std::endl;
        std::ofstream stream(derive_filename(output, _T("-pulses")),
            std::ios::trunc);
        stream << "begin rise [ticks],"
            << "end rise [ticks],"
            << "begin fall [ticks],"
            << "end fall [ticks],"
            << "rise [us],"
            << "high [us],"
            << "fall [us],"
            << "begin rise [us],"
            << "end rise [us],"
            << "begin fall [us],"
            << "end fall [us],"
            << "consolidated high [us]"
            << std::endl;

        assert(erise.size() == brise.size());
        assert(bfall.size() == brise.size());
        assert(efall.size() == brise.size());
        for (std::size_t i = 0; i < brise.size(); ++i) {
            stream << brise[i].time_since_epoch().count() << ",";
            stream << erise[i].time_since_epoch().count() << ",";
            stream << bfall[i].time_since_epoch().count() << ",";
            stream << efall[i].time_since_epoch().count() << ",";

            const auto r = erise[i] - brise[i];
            const auto h = bfall[i] - erise[i];
            const auto f = efall[i] - bfall[i];
            stream << duration_cast<output_type>(r).count() << ",";
            stream << duration_cast<output_type>(h).count() << ",";
            stream << duration_cast<output_type>(f).count() << ", ";

            const auto br = duration_cast<output_type>(brise[i] - brise.front());
            const auto er = duration_cast<output_type>(erise[i] - brise.front());
            const auto bf = duration_cast<output_type>(bfall[i] - brise.front());
            const auto ef = duration_cast<output_type>(efall[i] - brise.front());
            stream << br.count() << ",";
            stream << er.count() << ",";
            stream << bf.count() << ",";
            stream << ef.count() << ",";

            const auto c = h + (r / 2) + (f / 2);
            stream << duration_cast<output_type>(c).count() << std::endl;
        }

        std::wcout << L"Downloading waveform ..." << std::endl;
        const auto data = instrument.data(channel,
            rtx_waveform_points::maximum,
            duration_cast<milliseconds>(download_timeout).count());
        const auto range = instrument.time_range();

        std::wcout << L"Writing waveform ..." << std::endl;
        stream = std::ofstream(derive_filename(output, _T("-waveform")),
            std::ios::trunc);
        stream << "volts (" << range.value() << range.unit() << ")"
            << std::endl;
        for (auto d : data) {
            stream << d << std::endl;
        }

        std::wcout << L"Analysing waveform ..." << std::endl;
        std::vector<float> pulse_widths;
        const auto avg_pulse_width = ::pulse_width(
            std::back_inserter(pulse_widths),
            data.begin(),
            data.end());

        std::wcout << L"Done." << std::endl;
        return 0;
    } catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
        return -1;
    }
}
