// <copyright file="rtx_config.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/convert_string.h"
#include "power_overwhelming/rtx_instrument_configuration.h"

#include <algorithm>
#include <iostream>
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
/// Entry point of the rtx_config application, which saves and restores the
/// configuration of Rohde &amp; Schwarz RTA and RTB series oscilloscopes.
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
int _tmain(const int argc, const TCHAR **argv) {
    using namespace visus::power_overwhelming;

    std::wcout << L"rtx_config" << std::endl;
    std::wcout << L"© 2023 Visualisierungsinstitut der Universität Stuttgart."
        << std::endl << L"All rights reserved."
        << std::endl << std::endl;

    const std::vector<std::basic_string<TCHAR>> cmd_line(argv, argv + argc);
    auto show_help = (argc != 3);
    const auto save = (cmd_line[1] == _T("--save"));
    const auto restore = (cmd_line[1] == _T("--restore"));
    show_help = show_help || (!save && !restore);

    if (show_help) {
        // Input is wrong, so show the help.
        std::wcout << L"TODO " << std::endl << std::endl;
        std::wcout << "Usage: rtx_config --save <output path>" << std::endl;
        std::wcout << "Usage: rtx_config --restore <input path>" << std::endl;
        return -2;
    }

    try {
        auto path = convert_string<wchar_t>(cmd_line[2]);
        std::vector<rtx_instrument> instrums(rtx_instrument::all(nullptr, 0));
        rtx_instrument::all(instrums.data(), instrums.size());

        if (save) {
            rtx_instrument_configuration::save(instrums.data(),
                instrums.size(), path.c_str());

        } else if (restore) {
            for (auto& i : instrums) {
                i.reset(rtx_instrument_reset::all);
            }

            rtx_instrument_configuration::apply(instrums.data(),
                instrums.size(), path.c_str());
        }

        return 0;
    } catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
        return -1;
    }
}
