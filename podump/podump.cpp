// <copyright file="podump.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"

#include "graphics_devices.h"
#include "rohde_und_schwarz.h"
#include "tinkerforge.h"


/// <summary>
/// Entry point of the podump application, which dumps all available sensor data
/// once to the console.
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
int _tmain(const int argc, const TCHAR **argv) {
#if (defined(DEBUG) || defined(_DEBUG))
    ::_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //::_CrtSetBreakAlloc(558);
#endif /* (defined(DEBUG) || defined(_DEBUG)) */

#if true
    visus::pwrowg::stable_power_state_scope spss;
#endif

    // Tinkerforge instruments
#if true
    ::print_tinkerforge_display();
#endif

    // Rohde & Schwarz instruments
#if true
#if true
    ::query_hmc8015();
#endif

#if true
    ::query_rtx_instrument();
#endif

#if true
    ::configure_rtx_instrument();
#endif
#endif

    // Utility APIs
#if true
    ::enumerate_graphics_devices();
#endif

    // Main sensor array.
    {
        visus::pwrowg::sensor_array_configuration config;
        config
            .sample_every(std::chrono::milliseconds(5))
            .deliver_to([](std::size_t id, const visus::pwrowg::sample *s, std::size_t n, void *c) {
                auto descs = static_cast<visus::pwrowg::sensor_description *>(c);
                for (std::size_t i = 0; i < n; ++i) {
                    std::cout << id << "/"
                        << visus::pwrowg::convert_string<char>(descs[id].name()) << "@"
                        << s[i].timestamp << ": "
                        << s->reading.floating_point << std::endl;
                }
            })
            .deliver_sensors_as_context();

        auto sensors = visus::pwrowg::sensor_array::for_all(std::move(config));
        sensors.start();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        sensors.stop();
    }

    return 0;
}
