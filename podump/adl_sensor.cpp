// <copyright file="adl_sensor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
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


/*
 * ::sample_adl_thermal
 */
void sample_adl_thermal(const unsigned int dt) {
    using namespace visus::power_overwhelming;

    try {
        std::vector<adl_thermal_sensor> sensors;
        sensors.resize(adl_thermal_sensor::for_all(nullptr, 0));
        adl_thermal_sensor::for_all(sensors.data(), sensors.size());

        // Enable asynchronous sampling.
        for (auto& s : sensors) {
            async_sampling config;
            config.delivers_thermal_samples_to([](const wchar_t *n, const thermal_sample *s, const std::size_t c, void *) {
                for (std::size_t i = 0; i < c; ++i) {
                    std::wcout << s[i].timestamp() << L" ("
                        << n << L"): "
                        << s[i].temperature() << L"°C"
                        << std::endl;
                }
            });
            s.sample(std::move(config));
        }

        // Wait for the requested number of seconds.
        std::this_thread::sleep_for(std::chrono::seconds(dt));

        // Disable asynchronous sampling.
        for (auto &s : sensors) {
            s.sample(async_sampling());
        }

    } catch (std::exception &ex) {
        std::cerr << ex.what() << std::endl;
    }
}


/*
 * ::sample_adl_throttling
 */
void sample_adl_throttling(const unsigned int dt) {
    using namespace visus::power_overwhelming;

    try {
        std::vector<adl_throttling_sensor> sensors;
        sensors.resize(adl_throttling_sensor::for_all(nullptr, 0));
        adl_throttling_sensor::for_all(sensors.data(), sensors.size());

        // Enable asynchronous sampling.
        for (auto& s : sensors) {
            async_sampling config;
            config.delivers_throttling_samples_to([](const wchar_t *n, const throttling_sample *s, const std::size_t c, void *) {
                for (std::size_t i = 0; i < c; ++i) {
                    std::wcout << s[i].timestamp() << L" ("
                        << n << L"): "
                        << static_cast<int>(s[i].state()) << L", "
                        << (s[i].throttled() ? L"" : L"not ")
                        << L"throttled." << std::endl;

                }
            });
            s.sample(std::move(config));
        }

        // Wait for the requested number of seconds.
        std::this_thread::sleep_for(std::chrono::seconds(dt));

        // Disable asynchronous sampling.
        for (auto &s : sensors) {
            s.sample(async_sampling());
        }

    } catch (std::exception &ex) {
        std::cerr << ex.what() << std::endl;
    }
}


/*
 * ::sample_adl_sensor_and_throttling
 */
void sample_adl_sensor_and_throttling(const unsigned int ds,
        const unsigned int dt) {
    using namespace visus::power_overwhelming;

    try {
        std::vector<adl_sensor> power_sensors;
        power_sensors.resize(adl_sensor::for_all(nullptr, 0));
        adl_sensor::for_all(power_sensors.data(), power_sensors.size());

        std::vector<adl_throttling_sensor> throttling_sensors;
        throttling_sensors.resize(adl_throttling_sensor::for_all(nullptr, 0));
        adl_throttling_sensor::for_all(throttling_sensors.data(), throttling_sensors.size());

        // Enable asynchronous sampling.
        for (auto& s : power_sensors) {
            async_sampling config;
            config.delivers_measurements_to([](const measurement& m, void*) {
                std::wcout << m.timestamp() << L" ("
                << m.sensor() << L"): "
                << m.voltage() << L" V, "
                << m.current() << L" A, "
                << m.power() << L" W" << std::endl;
            });
            s.sample(std::move(config));
        }

        for (auto& s : throttling_sensors) {
            async_sampling config;
            config.delivers_throttling_samples_to([](const wchar_t* n, const throttling_sample* s, const std::size_t c, void*) {
                for (std::size_t i = 0; i < c; ++i) {
                    std::wcout << s[i].timestamp() << L" ("
                        << n << L"): "
                        << static_cast<int>(s[i].state()) << L", "
                        << (s[i].throttled() ? L"" : L"not ")
                        << L"throttled." << std::endl;

                }
            });
            s.sample(std::move(config));
        }


        // Wait for the requested number of seconds.
        const auto first_sleep = std::chrono::seconds((std::min)(ds, dt));
        const auto second_sleep = std::chrono::seconds((std::max)(ds, dt)) - first_sleep;
        const auto power_first = (ds < dt);

        std::this_thread::sleep_for(first_sleep);

        // Disable asynchronous sampling.
        if (power_first) {
            for (auto& s : power_sensors) {
                s.sample(async_sampling());
            }
        } else {
            for (auto& s : throttling_sensors) {
                s.sample(async_sampling());
            }
        }

        // Wait again
        std::this_thread::sleep_for(second_sleep);

        // Disable asynchronous sampling.
        if (power_first) {
            for (auto& s : throttling_sensors) {
                s.sample(async_sampling());
            }
        } else {
            for (auto& s : power_sensors) {
                s.sample(async_sampling());
            }
        }

    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
}


/*
 * ::sample_adl_thermal_and_throttling
 */
void sample_adl_thermal_and_throttling(const unsigned int dt) {
    using namespace visus::power_overwhelming;

    try {
        std::vector<adl_thermal_sensor> thermal_sensors;
        thermal_sensors.resize(adl_thermal_sensor::for_all(nullptr, 0));
        adl_thermal_sensor::for_all(thermal_sensors.data(), thermal_sensors.size());

        std::vector<adl_throttling_sensor> throttling_sensors;
        throttling_sensors.resize(adl_throttling_sensor::for_all(nullptr, 0));
        adl_throttling_sensor::for_all(throttling_sensors.data(), throttling_sensors.size());

        // Enable asynchronous sampling.
        for (auto& s : thermal_sensors) {
            async_sampling config;
            config.delivers_thermal_samples_to([](const wchar_t* n, const thermal_sample* s, const std::size_t c, void*) {
                for (std::size_t i = 0; i < c; ++i) {
                    std::wcout << s[i].timestamp() << L" ("
                        << n << L"): "
                        << s[i].temperature() << L"°C"
                        << std::endl;
                }
                });
            s.sample(std::move(config));
        }

        for (auto& s : throttling_sensors) {
            async_sampling config;
            config.delivers_throttling_samples_to([](const wchar_t* n, const throttling_sample* s, const std::size_t c, void*) {
                for (std::size_t i = 0; i < c; ++i) {
                    std::wcout << s[i].timestamp() << L" ("
                        << n << L"): "
                        << static_cast<int>(s[i].state()) << L", "
                        << (s[i].throttled() ? L"" : L"not ")
                        << L"throttled." << std::endl;

                }
            });
            s.sample(std::move(config));
        }

        // Wait for the requested number of seconds.
        std::this_thread::sleep_for(std::chrono::seconds(dt));

        // Disable asynchronous sampling.
        for (auto& s : thermal_sensors) {
            s.sample(async_sampling());
        }
        for (auto& s : throttling_sensors) {
            s.sample(async_sampling());
        }

    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }

}
