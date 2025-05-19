// <copyright file="dump_sensors.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025  Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/dump_sensors.h"

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
/// Entry point of the dump_sensors application, which dumps the definitions of
/// all sensors into the user-provided file.
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
int _tmain(const int argc, const TCHAR **argv) {
    using namespace visus::pwrowg;

    std::wcout << L"dump_sensors" << std::endl;
    std::wcout << L"© 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart."
        << std::endl << L"All rights reserved."
        << std::endl << std::endl;

    const std::vector<std::basic_string<TCHAR>> cmd_line(argv, argv + argc);
    auto show_help = (argc < 2);

    if (show_help) {
        // Input is wrong, so show the help.
        std::wcout << L"Dumps the definition of all sensors that are currently "
            << L"available on this machine " << std::endl
            << L"into a JSON file." << std::endl << std::endl;
        std::wcout << "Usage: dump_sensors <output path>"
            << std::endl;
        return -2;
    }

    std::wcout << L"Enumerating all available sensors. This might take some "
        L"time ..." << std::endl;

    // Can go on with the real thing, which is just calling into the library to
    // save the sensor definitions.
    try {
        const auto path = cmd_line[1];
        auto sensors = sensor_array::for_all(sensor_array_configuration());
        const auto cnt = dump_sensors(sensors, path);
        std::wcout << cnt << ((cnt == 1) ? L" sensor" : L" sensors")
            << L" dumped to \"" << path.c_str() << L"\"." << std::endl;
        return 0;
    } catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
        return -1;
    }
}
