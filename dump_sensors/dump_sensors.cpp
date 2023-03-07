// <copyright file="dump_sensors.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/collector.h"
#include "power_overwhelming/dump_sensors.h"

#include <iostream>

#if defined(_WIN32)
#include <Windows.h>
#include <tchar.h>
#endif /* defined(_WIN32) */

#if !defined(_tmain)
#define _tmain main
#define TCHAR char
#endif /* !defined(_tmain) */


/// <summary>
/// Entry point of the dump_sensors application, which dumps the definitions of
/// all sensors into the user-provided file.
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
int _tmain(const int argc, const TCHAR **argv) {
    std::wcout << L"dump_sensors" << std::endl;
    std::wcout << L"© 2023 Visualisierungsinstitut der Universität Stuttgart."
        << std::endl << std::endl;

    auto show_help = (argc < 2);

    if (show_help) {
        // Input is wrong, so show the help.
        std::wcout << L"Dumps the definition of all sensors that are currently "
            << L"available on this machine " << std::endl
            << L"into a JSON file." << std::endl << std::endl;
        std::wcout << "Usage: dump_sensors <output path>" << std::endl;
        return -2;

    } else {
        // Can go on with the real thing, which is just calling into the
        // library to save the sensor definitions.
        try {
            auto cnt = visus::power_overwhelming::dump_sensors(argv[1]);
            std::wcout << cnt << " sensor(s) dumped." << std::endl;
            return 0;
        } catch (std::exception& ex) {
            std::cout << ex.what() << std::endl;
            return -1;
        }
    }

}
