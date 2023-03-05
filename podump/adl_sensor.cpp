// <copyright file="adl_sensor.cpp" company="Visualisierungsinstitut der Universit�t Stuttgart">
// Copyright � 2023 Visualisierungsinstitut der Universit�t Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph M�ller</author>

#include "pch.h"
#include "adl_sensor.h"


/*
 * ::sample_adl_sensor
 */
void sample_adl_sensor(void) {
    using namespace visus::power_overwhelming;

    try {
        std::vector<adl_sensor> sensors;
        sensors.resize(adl_sensor::for_all(nullptr, 0));
        adl_sensor::for_all(sensors.data(), sensors.size());

        for (auto &s : sensors) {
            std::wcout << s.name() << L":" << std::endl;
            auto m = s.sample();
            std::wcout << m.timestamp() << L" (" << m.sensor() << L"): "
                << m.voltage() << L" V, "
                << m.current() << L" A, "
                << m.power() << L" W" << std::endl;
        }
    } catch (std::exception &ex) {
        std::cerr << ex.what() << std::endl;
    }
}


/*
 * ::sample_adl_sensor_async
 */
void sample_adl_sensor_async(const unsigned int dt) {
    using namespace visus::power_overwhelming;

    try {
        std::vector<adl_sensor> sensors;
        sensors.resize(adl_sensor::for_all(nullptr, 0));
        adl_sensor::for_all(sensors.data(), sensors.size());

        // Enable asynchronous sampling.
        for (auto& s : sensors) {
            s.sample([](const measurement& m, void *) {
                std::wcout << m.timestamp() << L" (" << m.sensor() << L"): "
                    << m.voltage() << L" V, "
                    << m.current() << L" A, "
                    << m.power() << L" W" << std::endl;
                });
        }

        // Wait for the requested number of seconds.
        std::this_thread::sleep_for(std::chrono::seconds(dt));

        // Disable asynchronous sampling.
        for (auto& s : sensors) {
            s.sample(nullptr);
        }

    } catch (std::exception &ex) {
        std::cerr << ex.what() << std::endl;
    }
}


/*
 * ::sample_adl_from_udid
 */
void sample_adl_from_udid(const char *udid) {
    using namespace visus::power_overwhelming;

    try {
        auto s = adl_sensor::from_udid(udid, adl_sensor_source::soc);

        std::wcout << s.name() << L":" << std::endl;
        auto m = s.sample();
        std::wcout << m.timestamp() << L" (" << m.sensor() << L"): "
            << m.voltage() << L" V, "
            << m.current() << L" A, "
            << m.power() << L" W" << std::endl;
    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
}