// <copyright file="podump.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include <iostream>
#include <thread>
#include <vector>

#include <adl_sensor.h>
#include <measurement.h>
#include <nvml_sensor.h>
#include <tinkerforge_sensor.h>
#include <tchar.h>


/// <summary>
/// Entry point of the podump application, which dumps all available sensor data
/// once to the console.
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
int _tmain(const int argc, const TCHAR **argv) {
    using namespace visus::power_overwhelming;

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
    } catch (std::exception &ex) {
        std::cerr << ex.what() << std::endl;
    }

    // Print data for all connected Tinkerforge sensors.
    try {
        std::vector<tinkerforge_sensor_definiton> sensors;
        sensors.resize(tinkerforge_sensor::get_sensors(nullptr, 0));
        tinkerforge_sensor::get_sensors(sensors.data(), sensors.size());

        for (auto& s: sensors) {
            tinkerforge_sensor sensor(s);
            // TODO
        }

    } catch (std::exception &ex) {
        std::cerr << ex.what() << std::endl;
    }

    std::this_thread::sleep_for(std::chrono::seconds(10));

     return 0;
}
