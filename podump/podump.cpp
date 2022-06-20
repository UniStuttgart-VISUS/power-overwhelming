// <copyright file="podump.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include <iostream>
#include <thread>
#include <vector>

#include <tchar.h>
#include <Windows.h>

#include "power_overwhelming/adl_sensor.h"
#include "power_overwhelming/collector.h"
#include "power_overwhelming/graphics_device.h"
#include "power_overwhelming/hmc8015_sensor.h"
#include "power_overwhelming/measurement.h"
#include "power_overwhelming/nvml_sensor.h"
#include "power_overwhelming/rtb_sensor.h"
#include "power_overwhelming/stable_power_state_scope.h"
#include "power_overwhelming/tinkerforge_display.h"
#include "power_overwhelming/tinkerforge_sensor.h"


/// <summary>
/// Entry point of the podump application, which dumps all available sensor data
/// once to the console.
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
int _tmain(const int argc, const TCHAR **argv) {
    using namespace visus::power_overwhelming;

#if (defined(DEBUG) || defined(_DEBUG))
    ::_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //::_CrtSetBreakAlloc(1);
#endif /* (defined(DEBUG) || defined(_DEBUG)) */

    stable_power_state_scope spss;

#if true
    {
        collector::make_configuration_template(L"sensors.json");
        collector collector(L"sensors.json");
    }
#endif

#if false
    // Print data for all supported AMD cards.
    try {
        std::vector<adl_sensor> sensors;
        sensors.resize(adl_sensor::for_all(nullptr, 0));
        adl_sensor::for_all(sensors.data(), sensors.size());

        for (auto& s : sensors) {
            std::wcout << s.name() << L":" << std::endl;
            auto m = s.sample();
            std::wcout << m.timestamp() << L" (" << m.sensor() << L"): "
                << m.power() << L" W" << std::endl;
        }
    } catch (std::exception &ex) {
        std::cerr << ex.what() << std::endl;
    }
#endif

#if false
    // Sample all supported AMD cards for five seconds.
    try {
        std::vector<adl_sensor> sensors;
        sensors.resize(adl_sensor::for_all(nullptr, 0));
        adl_sensor::for_all(sensors.data(), sensors.size());

        for (auto& s : sensors) {
            s.sample([](const measurement &m) {
                std::wcout << m.timestamp() << L": " << m.power() << L" W"
                    << std::endl;
            });
        }

        std::this_thread::sleep_for(std::chrono::seconds(5));

        for (auto& s : sensors) {
            s.sample(nullptr);
        }
    } catch (std::exception &ex) {
        std::cerr << ex.what() << std::endl;
    }
#endif

#if true
    // Print data for all supported NVIDIA cards.
    try {
        std::vector<nvml_sensor> sensors;
        sensors.resize(nvml_sensor::for_all(nullptr, 0));
        nvml_sensor::for_all(sensors.data(), sensors.size());

        for (auto& s : sensors) {
            std::wcout << s.name() << L":" << std::endl;
            auto m = s.sample();
            std::wcout << m.timestamp() << L": " << m.power() << L" W"
                << std::endl;
        }
    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
#endif

#if false
    // Sample all supported NVIDIA cards for five seconds.
    try {
        std::vector<nvml_sensor> sensors;
        sensors.resize(nvml_sensor::for_all(nullptr, 0));
        nvml_sensor::for_all(sensors.data(), sensors.size());

        for (auto& s : sensors) {
            s.sample([](const measurement& m) {
                std::wcout << m.timestamp() << L": " << m.power() << L" W"
                    << std::endl;
                });
        }

        std::this_thread::sleep_for(std::chrono::seconds(5));

        for (auto& s : sensors) {
            s.sample(nullptr);
        }

    } catch (std::exception &ex) {
        std::cerr << ex.what() << std::endl;
    }
#endif

#if true
    // Print all supported graphics devices
    try {
        std::vector<graphics_device> devices;
        devices.resize(graphics_device::all(nullptr, 0));
        graphics_device::all(devices.data(), devices.size());

        for (auto& d : devices) {
            std::wcout << d.name() << L": " << d.id() << std::endl;
        }
    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
#endif

#if false
    // Print some useful messsage to all Tinkerforge LCDs attached.
    try {
        std::vector<tinkerforge_display> displays;
        displays.resize(tinkerforge_display::for_all(nullptr, 0));
        auto cnt = tinkerforge_display::for_all(displays.data(),
            displays.size());

        if (cnt < displays.size()) {
            displays.resize(cnt);
        }

        for (auto& d : displays) {
            d.clear();
            d.print("Power overwhelming!");
        }

    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
#endif

#if false
    // Print data for all connected Tinkerforge sensors.
    try {
        std::vector<tinkerforge_sensor_definiton> descs;
        descs.resize(tinkerforge_sensor::get_definitions(nullptr, 0));
        auto cnt = tinkerforge_sensor::get_definitions(descs.data(),
            descs.size());

        if (cnt < descs.size()) {
            descs.resize(cnt);
        }

        for (auto &d : descs) {
            tinkerforge_sensor s(d);
            std::wcout << s.name() << L":" << std::endl;
            auto m = s.sample();
            std::wcout << m.timestamp() << L": " << m.voltage() << " V * "
                << m.current() << " A = " << m.power() << L" W"
                << std::endl;
        }

    } catch (std::exception &ex) {
        std::cerr << ex.what() << std::endl;
    }
#endif

#if false
    // Asynchronously sample the Tinkerforge sensors for five seconds.
    try {
        std::vector<tinkerforge_sensor_definiton> descs;
        std::vector<tinkerforge_sensor> sensors;
        descs.resize(tinkerforge_sensor::get_definitions(nullptr, 0));
        auto cnt = tinkerforge_sensor::get_definitions(descs.data(),
            descs.size());

        if (cnt < descs.size()) {
            descs.resize(cnt);
        }

        for (auto& d : descs) {
            sensors.emplace_back(d);
            sensors.back().sample([](const measurement& m) {
                std::wcout << m.sensor() << L":" << m.timestamp() << L": "
                    << m.voltage() << " V * " << m.current() << " A = "
                    << m.power() << L" W"
                    << std::endl;
                });
        }

        std::this_thread::sleep_for(std::chrono::seconds(5));

        for (auto& s : sensors) {
            s.sample(nullptr);
        }

    } catch (std::exception &ex) {
        std::cerr << ex.what() << std::endl;
    }
#endif

#if false
    // Query HMC8015
    try {
        std::vector<hmc8015_sensor> sensors;
        sensors.resize(hmc8015_sensor::for_all(nullptr, 0));
        hmc8015_sensor::for_all(sensors.data(), sensors.size());

        for (auto &s : sensors) {
            s.display("Die Kraft ist überwältigend!");
            s.synchronise_clock();
            s.log_file("podump.csv", true, true);
            s.current_range(instrument_range::maximum);
            s.voltage_range(instrument_range::explicitly, 300);

            SYSTEMTIME now;
            ::GetLocalTime(&now);

            std::wcout << now.wHour << ":" << now.wMinute << ":" << now.wSecond << std::endl;

            //s.log_behaviour(std::numeric_limits<float>::lowest(),
            //    log_mode::time_span, 5, now.wYear, now.wMonth,
            //    now.wDay, now.wHour, now.wMinute, now.wSecond + 5);
            s.log_behaviour(std::numeric_limits<float>::lowest(),
                log_mode::duration);
            s.log(true);
            std::wcout << s.is_log() << std::endl;

            std::vector<char> path(1024);
            s.log_file(path.data(), path.size());
            std::this_thread::sleep_for(std::chrono::seconds(6));
            s.log(false);

            std::wcout << s.name() << L":" << std::endl;
            auto m = s.sample(timestamp_resolution::milliseconds);
            std::wcout << m.timestamp() << L": " << m.voltage() << " V * "
                << m.current() << " A = " << m.power() << L" W"
                << std::endl;
        }

    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
#endif

#if false
    // Query RTB2004
    try {
        std::vector<oscilloscope_sensor_definition> definitions;
        std::vector<rtb_sensor> sensors;
        sensors.resize(rtb_sensor::for_all(nullptr, 0));
        rtb_sensor::for_all(sensors.data(), sensors.size());

        definitions.push_back(oscilloscope_sensor_definition(L"Test1",
            1, 10.0f, 2, 10.0f));

        for (auto& s : sensors) {
            s.synchronise_clock();
            s.configure(definitions.data(), definitions.size());
            //s.expression(1, "CH1*CH2", "W");
            std::wcout << s.name() << L":" << std::endl;
        }

    } catch (std::exception &ex) {
        std::cerr << ex.what() << std::endl;
    }
#endif

    return 0;
}
