// <copyright file="dump_readings.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/sensor_array.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

#if defined(_WIN32)
#include <Windows.h>
#include <conio.h>
#include <tchar.h>
#endif /* defined(_WIN32) */

#if !defined(_tmain)
#define _tmain main
#define TCHAR char
#define _T(x) (x)
#endif /* !defined(_tmain) */


/// <summary>
/// Entry point of the dump_sensors application, which dumps sensor readings
/// until a key is pressed.
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
int _tmain(const int argc, const TCHAR **argv) {
    using namespace visus::pwrowg;

    std::wcout << L"dump_readings" << std::endl;
    std::wcout
        << L"© 2023 - 2026 Visualisierungsinstitut der Universität Stuttgart."
        << std::endl << L"All rights reserved."
        << std::endl << std::endl;

    try {
        auto sensors = sensor_array::for_all(std::move(
            sensor_array_configuration()
            .sample_every(std::chrono::milliseconds(10))
            .deliver_to([](const sample *samples, std::size_t cnt,
                    const sensor_description *sensors, void *ctx) {
                for (std::size_t i = 0; i < cnt; ++i) {
                    std::wcout << sensors[samples[i].source].id()
                        << L"@" << samples[i].timestamp << L": ";
                    switch (sensors[samples[i].source].reading_type()) {
                        case reading_type::floating_point:
                            std::wcout << samples[i].reading.floating_point;
                            break;

                        case reading_type::signed_integer:
                            std::wcout << samples[i].reading.signed_integer;
                            break;

                        case reading_type::unsigned_integer:
                            std::wcout << samples[i].reading.unsigned_integer;
                            break;
                    }
                    std::wcout << std::endl;
                }
            })));

        sensors.start();
#if defined(_WIN32)
        std::wcout << L"Press any key to end measurement." << std::endl;
        getch();
#else /* defined(_WIN32) */
        std::this_thread::sleep_for(std::chrono::seconds(10));
#endif /* defined(_WIN32) */
        sensors.stop();

        return 0;
    } catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
        return -1;
    }
}
