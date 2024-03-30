// <copyright file="adl_sensor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

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

        for (auto& s : sensors) {
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
 * ::sample_adl_sensor_data
 */
void sample_adl_sensor_data(void) {
    using namespace visus::power_overwhelming;

    try {
        std::vector<adl_sensor> sensors;
        sensors.resize(adl_sensor::for_all(nullptr, 0));
        adl_sensor::for_all(sensors.data(), sensors.size());

        for (auto &s : sensors) {
            std::wcout << s.name() << L":" << std::endl;
            auto m = s.sample_data();
            std::wcout << m.timestamp() << L": "
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
            async_sampling config;
            config.delivers_measurements_to([](const measurement& m, void *) {
                std::wcout << m.timestamp() << L" ("
                    << m.sensor() << L"): "
                    << m.voltage() << L" V, "
                    << m.current() << L" A, "
                    << m.power() << L" W" << std::endl;
            });
            s.sample(std::move(config));
        }

        // Wait for the requested number of seconds.
        std::this_thread::sleep_for(std::chrono::seconds(dt));

        // Disable asynchronous sampling.
        for (auto& s : sensors) {
            s.sample(async_sampling());
        }

    } catch (std::exception& ex) {
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
