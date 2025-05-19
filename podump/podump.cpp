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
    using namespace visus::pwrowg;

#if (defined(DEBUG) || defined(_DEBUG))
    ::_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //::_CrtSetBreakAlloc(558);
#endif /* (defined(DEBUG) || defined(_DEBUG)) */

#if false
    stable_power_state_scope spss;
#endif

    // Tinkerforge instruments
#if false
    ::print_tinkerforge_display();
#endif

    // Rohde & Schwarz instruments
#if false
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
        sensor_array_configuration config;
        config
            //.exclude<tinkerforge_configuration>()
            //.exclude<usb_pd_configuration>()
            .configure<hmc8015_configuration>([](hmc8015_configuration& c) {
                //c.function_list(hmc8015_function::rms_current);
                c.timeout(std::chrono::seconds(10));
                c.current_range(hmc8015_instrument_range::maximum);
                c.voltage_range(hmc8015_instrument_range::maximum);
                c.clear_internal_memory(true);
                //c.log_file("pdmp");
                c.log_to_usb(false);
            })
            .sample_every(std::chrono::milliseconds(5))
            .deliver_to([](const sample *s,
                    std::size_t n,
                    const sensor_description *descs,
                    void *) {
                for (std::size_t i = 0; i < n; ++i) {
                    auto desc = descs[s[i].source];
                    std::wcout << s[i].source << L"/"
                        << desc.id() << L" (" << desc.name() << L")"
                        << L" @" << s[i].timestamp << L": "
                        << s->reading.floating_point << std::endl;
                }
            });

        auto sensors = sensor_array::for_all(std::move(config));

        // Print all sensors.
        for (auto s : sensors) {
            std::wcout << s.name() << L": " << std::endl
                << L"\tID: " << s.id() << std::endl
                << L"\tPath: " << s.path() << std::endl;
        }
        std::cout << std::endl;

        // Sample the sensors for some time.
        sensors.start();
        std::this_thread::sleep_for(std::chrono::seconds(5));
        sensors.stop();

        //for (std::size_t i = 0; i < 4; ++i) {
        //    std::this_thread::sleep_for(std::chrono::seconds(5));

        //    sensors.start();
        //    std::this_thread::sleep_for(std::chrono::seconds(5));
        //    sensors.stop();
        //}
    }

    return 0;
}
