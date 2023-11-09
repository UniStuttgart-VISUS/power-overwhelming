// <copyright file="tinkerforge.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"
#include "tinkerforge.h"



/*
 * ::sample_all_tinkerforge_sensors
  */
void sample_all_tinkerforge_sensors(void) {
    using namespace visus::power_overwhelming;

    try {
        std::vector<tinkerforge_sensor> sensors;
        sensors.resize(tinkerforge_sensor::for_all(nullptr, 0));
        auto cnt = tinkerforge_sensor::for_all(sensors.data(),
            sensors.size());

        if (cnt < sensors.size()) {
            sensors.resize(cnt);
        }

        for (auto& s : sensors) {
            s.reset();
            std::wcout << s.name() << L":" << std::endl;
            auto m = s.sample();
            std::wcout << m.timestamp() << L": "
                << m.voltage() << " V * "
                << m.current() << " A = "
                << m.power() << L" W"
                << std::endl;
        }

    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
}


/*
 * ::sample_tinkerforge_sensor
 */
void sample_tinkerforge_sensor(void) {
    using namespace visus::power_overwhelming;

    try {
        std::vector<tinkerforge_sensor_definition> descs;
        descs.resize(tinkerforge_sensor::get_definitions(nullptr, 0));
        auto cnt = tinkerforge_sensor::get_definitions(descs.data(),
            descs.size());

        if (cnt < descs.size()) {
            descs.resize(cnt);
        }

        for (auto& d : descs) {
            tinkerforge_sensor s(d);
            s.reset();

            std::wcout << s.name() << L":" << std::endl;
            auto m = s.sample();
            std::wcout << m.timestamp() << L": "
                << m.voltage() << " V * "
                << m.current() << " A = "
                << m.power() << L" W"
                << std::endl;
        }

    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
}


/*
 * ::sample_tinkerforge_sensor_data
 */
void sample_tinkerforge_sensor_data(void) {
    using namespace visus::power_overwhelming;

    try {
        std::vector<tinkerforge_sensor_definition> descs;
        descs.resize(tinkerforge_sensor::get_definitions(nullptr, 0));
        auto cnt = tinkerforge_sensor::get_definitions(descs.data(),
            descs.size());

        if (cnt < descs.size()) {
            descs.resize(cnt);
        }

        for (auto& d : descs) {
            tinkerforge_sensor s(d);
            s.reset();

            std::wcout << s.name() << L":" << std::endl;
            auto m = s.sample_data();
            std::wcout << m.timestamp() << L": "
                << m.voltage() << " V * "
                << m.current() << " A = "
                << m.power() << L" W"
                << std::endl;
        }

    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
}


/*
 * ::sample_tinkerforge_sensor_async
 */
void sample_tinkerforge_sensor_async(const unsigned int dt) {
    using namespace visus::power_overwhelming;

    try {
        std::vector<tinkerforge_sensor_definition> descs;
        std::vector<tinkerforge_sensor> sensors;
        descs.resize(tinkerforge_sensor::get_definitions(nullptr, 0));
        auto cnt = tinkerforge_sensor::get_definitions(descs.data(),
            descs.size());

        if (cnt < descs.size()) {
            descs.resize(cnt);
        }

        for (auto& d : descs) {
            sensors.emplace_back(d);
            sensors.back().reset();
            sensors.back().sample([](const measurement& m, void *) {
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

    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
}


/*
 * ::sample_tinkerforge_power_async
 */
void sample_tinkerforge_power_async(const unsigned int dt) {
    using namespace visus::power_overwhelming;

    try {
        std::vector<tinkerforge_sensor_definition> descs;
        std::vector<tinkerforge_sensor> sensors;
        descs.resize(tinkerforge_sensor::get_definitions(nullptr, 0));
        auto cnt = tinkerforge_sensor::get_definitions(descs.data(),
            descs.size());

        if (cnt < descs.size()) {
            descs.resize(cnt);
        }

        for (auto& d : descs) {
            sensors.emplace_back(d);
            sensors.back().reset();
            sensors.back().configure(
                sample_averaging::average_of_4,
                conversion_time::microseconds_588,
                conversion_time::microseconds_588);
            sensors.back().resync_internal_clock_after(20);
            sensors.back().sample(async_sampling()
                .samples_every(20000)
                .using_resolution(timestamp_resolution::milliseconds)
                .delivers_measurements_to([](const measurement& m, void *) {
                    std::wcout << m.sensor() << L":" << m.timestamp() << L": "
                        << m.power() << L" W"
                        << std::endl;
                })
                .from_source(tinkerforge_sensor_source::power)
                .as_rvalue());
        }

        std::this_thread::sleep_for(std::chrono::seconds(5));

        for (auto& s : sensors) {
            s.sample(nullptr);
        }

    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
}


/*
 * ::print_tinkerforge_display
 */
void print_tinkerforge_display(const char *text) {
    using namespace visus::power_overwhelming;

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
            d.print(text);
        }

    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
}
