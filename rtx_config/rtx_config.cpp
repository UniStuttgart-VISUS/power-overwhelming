// <copyright file="rtx_config.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include <algorithm>
#include <iostream>
#include <map>
#include <thread>
#include <vector>

#include "visus/pwrowg/convert_string.h"
#include "visus/pwrowg/rtx_instrument_configuration.h"
#include "visus/pwrowg/rtx_configuration.h"

#include "visual_config.h"
#include "zero_adjust.h"


#if !defined(_tmain)
#define _tmain main
#define TCHAR char
#define _T(x) (x)
#endif /* !defined(_tmain) */


/// <summary>
/// Finds the command line switch <paramref name="name"/> in the given command
/// line.
/// </summary>
template<class TIterator> TIterator find_switch(_In_ const TIterator begin,
    _In_ const TIterator end, _In_z_ const char* name) {
    return std::find_if(begin, end, [name](_In_ const char* arg) {
        return visus::pwrowg::detail::equals(arg, name, true);
        });
}

/// <summary>
/// Finds the value of the command line argument <paramref name="name"/> in the
/// given command line.
/// </summary>
template<class TIterator> TIterator find_argument(_In_ const TIterator begin,
    _In_ const TIterator end, _In_z_ const char* name) {
    auto retval = find_switch(begin, end, name);
    if (retval != end) {
        ++retval;
    }
    return retval;
}


/// <summary>
/// Entry point of the rtx_config application, which saves and restores the
/// configuration of Rohde &amp; Schwarz RTA and RTB series oscilloscopes.
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
int _tmain(const int argc, const TCHAR **argv) {
    using namespace visus::pwrowg;
    const auto end = argv + argc;

    std::wcout << L"rtx_config" << std::endl;
    std::wcout << L"© 2023 - 2026 Visualisierungsinstitut der Universität Stuttgart."
        << std::endl << std::endl;

    const std::vector<std::basic_string<TCHAR>> cmd_line(argv, argv + argc);
    auto path = static_cast<const TCHAR*>(nullptr);

    auto save = false;
    {
        auto it = ::find_argument(argv, end, "--save");
        if ((save = (it != end))) {
            path = *it;
        }
    }

    auto restore = false;
    {
        auto it = ::find_argument(argv, end, "--restore");
        if ((restore = (it != end))) {
            path = *it;
        }
    }

    auto zero_adjust = false;
    {
        auto it = ::find_argument(argv, end, "--zero-adjust");
        if ((zero_adjust = (it != end))) {
            path = *it;
        }
    }
    const auto show_help = (!save && !restore && !zero_adjust);

    if (show_help) {
        // Input is wrong, so show the help (or the UI on Windows).
#if defined(_WIN32)
        return visual_config();
#else /* defined(_WIN32) */
        std::cout << "Usage: rtx_config --save <output path>" << std::endl;
        std::cout << "Usage: rtx_config --restore <input path>" << std::endl;
        std::cout << "Usage: rtx_config --zero_adjust <sensor configuration>"
            << std::endl;
        return -2;
#endif /* defined(_WIN32) */
    }

    try {
        std::vector<rtx_instrument> instrums(rtx_instrument::all(nullptr, 0));
        rtx_instrument::all(instrums.data(), instrums.size());

        if (save) {
            auto p = convert_string<wchar_t>(path);
            rtx_instrument_configuration::save(instrums.data(),
                instrums.size(), p.c_str());

        } else if (restore) {
            auto p = convert_string<wchar_t>(path);
            for (auto& i : instrums) {
                i.reset(rtx_instrument_reset::all);
            }

            rtx_instrument_configuration::apply(instrums.data(),
                instrums.size(), p.c_str());

        } else if (zero_adjust) {
            const bool apply = (::find_switch(argv, end, "--apply") != end);

            std::chrono::duration<float> degauss(1.5f);
            {
                auto it = ::find_argument(argv, end, "--degauss-time");
                if ((it != end)) {
                    degauss = std::chrono::duration<float>(std::stof(*it));
                }
            }

            const bool no_wait = (::find_switch(argv, end, "--no-wait") != end);

            std::chrono::duration<float> range(5.0f);
            {
                auto it = ::find_argument(argv, end, "--range");
                if ((it != end)) {
                    range = std::chrono::duration<float>(std::stof(*it));
                }
            }

            std::size_t retries = 0;
            {
                auto it = ::find_argument(argv, end, "--retries");
                if ((it != end)) {
                    retries = std::stoul(*it);
                }
            }

            ::zero_adjust(path, range, degauss, retries, no_wait, apply);
        }

        return 0;
    } catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
        return -1;
    }
}
