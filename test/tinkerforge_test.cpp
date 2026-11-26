// <copyright file="tinkerforge_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"

#include <visus/pwrowg/tinkerforge_conversion_time_traits.h>
#include <visus/pwrowg/tinkerforge_sample_averaging_traits.h>

#include <sensor_array_impl.h>
#include <tinkerforge_sensor.h>


PWROWG_TEST_NAMESPACE_BEGIN

TEST_CLASS(tinkerforge_test) {

public:

    TEST_METHOD(conversion_time_traits) {
        using std::chrono::duration_cast;
        using std::chrono::microseconds;

        Assert::AreEqual(140ll, tinkerforge_conversion_time_traits<tinkerforge_conversion_time::microseconds_140>::value.count(), L"140 µs", LINE_INFO());
        Assert::AreEqual(204ll, tinkerforge_conversion_time_traits<tinkerforge_conversion_time::microseconds_204>::value.count(), L"204 µs", LINE_INFO());
        Assert::AreEqual(332ll, tinkerforge_conversion_time_traits<tinkerforge_conversion_time::microseconds_332>::value.count(), L"332 µs", LINE_INFO());
        Assert::AreEqual(588ll, tinkerforge_conversion_time_traits<tinkerforge_conversion_time::microseconds_588>::value.count(), L"588 µs", LINE_INFO());
        Assert::AreEqual(duration_cast<microseconds>(std::chrono::duration<double, std::milli>(1.1)).count(), tinkerforge_conversion_time_traits<tinkerforge_conversion_time::milliseconds_1_1>::value.count(), L"1.1 ms", LINE_INFO());
        Assert::AreEqual(duration_cast<microseconds>(std::chrono::duration<double, std::milli>(2.116)).count(), tinkerforge_conversion_time_traits<tinkerforge_conversion_time::milliseconds_2_116>::value.count(), L"2.116 ms", LINE_INFO());
        Assert::AreEqual(duration_cast<microseconds>(std::chrono::duration<double, std::milli>(4.156)).count(), tinkerforge_conversion_time_traits<tinkerforge_conversion_time::milliseconds_4_156>::value.count(), L"4.156 ms", LINE_INFO());
        Assert::AreEqual(duration_cast<microseconds>(std::chrono::duration<double, std::milli>(8.244)).count(), tinkerforge_conversion_time_traits<tinkerforge_conversion_time::milliseconds_8_244>::value.count(), L"8.244 ms", LINE_INFO());
    }

    TEST_METHOD(sample_avg_traits) {
        Assert::AreEqual(std::size_t(1), tinkerforge_sample_averaging_traits<tinkerforge_sample_averaging::average_of_1>::value, L"1 sample", LINE_INFO());
        Assert::AreEqual(std::size_t(4), tinkerforge_sample_averaging_traits<tinkerforge_sample_averaging::average_of_4>::value, L"4 samples", LINE_INFO());
        Assert::AreEqual(std::size_t(16), tinkerforge_sample_averaging_traits<tinkerforge_sample_averaging::average_of_16>::value, L"16 samples", LINE_INFO());
        Assert::AreEqual(std::size_t(64), tinkerforge_sample_averaging_traits<tinkerforge_sample_averaging::average_of_64>::value, L"64 samples", LINE_INFO());
        Assert::AreEqual(std::size_t(128), tinkerforge_sample_averaging_traits<tinkerforge_sample_averaging::average_of_128>::value, L"128 samples", LINE_INFO());
        Assert::AreEqual(std::size_t(256), tinkerforge_sample_averaging_traits<tinkerforge_sample_averaging::average_of_256>::value, L"256 samples", LINE_INFO());
        Assert::AreEqual(std::size_t(512), tinkerforge_sample_averaging_traits<tinkerforge_sample_averaging::average_of_512>::value, L"512 samples", LINE_INFO());
        Assert::AreEqual(std::size_t(1024), tinkerforge_sample_averaging_traits<tinkerforge_sample_averaging::average_of_1024>::value, L"1024 samples", LINE_INFO());
    }

    TEST_METHOD(test_descriptions) {
        typedef detail::tinkerforge_sensor type;

        type::configuration_type config;
        std::vector<sensor_description> descs;
        descs.resize(type::descriptions(nullptr, 0, config));
        type::descriptions(descs.data(), descs.size(), config);

        for (auto& d : descs) {
            Assert::AreEqual(int(reading_type::floating_point), int(d.reading_type()), L"produces floats", LINE_INFO());
            Assert::AreEqual(L"Tinkerforge", d.vendor(), L"Vendor name", LINE_INFO());
            Assert::AreNotEqual(std::size_t(0), ::wcslen(d.id()), L"ID not empty", LINE_INFO());
            Assert::AreNotEqual(std::size_t(0), ::wcslen(d.name()), L"Name not empty", LINE_INFO());
            Assert::AreNotEqual(std::size_t(0), ::wcslen(d.path()), L"Path not empty", LINE_INFO());
        }
    }

    TEST_METHOD(test_parse_end_point) {
        {
            const auto ep = tinkerforge_configuration::end_point::parse((char *) nullptr);
            Assert::AreEqual("localhost", ep.name(), L"name", LINE_INFO());
            Assert::AreEqual(4223, int(ep.port()), L"port", LINE_INFO());
        }
        {
            const auto ep = tinkerforge_configuration::end_point::parse((wchar_t *) nullptr);
            Assert::AreEqual("localhost", ep.name(), L"name", LINE_INFO());
            Assert::AreEqual(4223, int(ep.port()), L"port", LINE_INFO());
        }
        {
            const auto ep = tinkerforge_configuration::end_point::parse("horst");
            Assert::AreEqual("horst", ep.name(), L"name", LINE_INFO());
            Assert::AreEqual(4223, int(ep.port()), L"port", LINE_INFO());
        }
        {
            const auto ep = tinkerforge_configuration::end_point::parse(L"horst:42");
            Assert::AreEqual("horst", ep.name(), L"name", LINE_INFO());
            Assert::AreEqual(42, int(ep.port()), L"port", LINE_INFO());
        }
        {
            const auto ep = tinkerforge_configuration::end_point::parse("127.0.0.1:1234");
            Assert::AreEqual("127.0.0.1", ep.name(), L"name", LINE_INFO());
            Assert::AreEqual(1234, int(ep.port()), L"port", LINE_INFO());
        }
        {
            const auto ep = tinkerforge_configuration::end_point::parse(L"[::1]:1234");
            Assert::AreEqual("[::1]", ep.name(), L"name", LINE_INFO());
            Assert::AreEqual(1234, int(ep.port()), L"port", LINE_INFO());
        }
    }

    TEST_METHOD(test_power_sensor_creation) {
        //::_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_CHECK_ALWAYS_DF | _CRTDBG_LEAK_CHECK_DF);
        //::_CrtSetDbgFlag(_CRTDBG_CHECK_ALWAYS_DF);
        //::_CrtSetBreakAlloc(778);
        typedef detail::tinkerforge_sensor type;

        type::configuration_type config;
        std::vector<sensor_description> descs;
        descs.resize(type::descriptions(nullptr, 0, config));
        type::descriptions(descs.data(), descs.size(), config);

        detail::sensor_array_impl dummy;

        {
            auto end = std::remove_if(descs.begin(), descs.end(), [](const sensor_description &d) {
                return !d.is_sensor_type(sensor_type::power);
            });
            descs.erase(end, descs.end());
        }

        type::list_type sensors;
        const auto unused = type::from_descriptions(sensors, 0, descs.begin(), descs.end(), &dummy, config);
        Assert::IsTrue(unused == descs.end(), L"All consumed", LINE_INFO());
        sensors.clear();
    }

    TEST_METHOD(test_sensor_array) {
        sensor_array_configuration config;
        auto sensors = sensor_array::for_matches(std::move(config), is_tinkerforge_sensor);

        if (sensors.size() > 0) {
            auto controller = sensors.controller<tinkerforge_configuration>();
            Assert::IsNotNull(controller, L"Have Tinkerforge controller", LINE_INFO());
            // Note: the following should never crash in any configuration.
            controller->resync_clock();
        }
    }

    TEST_METHOD(test_sensor_run) {
        typedef detail::tinkerforge_sensor type;

        auto evt = create_event();
        sensor_array_configuration config;
            config.deliver_to([](const sample *s, const std::size_t cnt, const sensor_description *, const std::size_t, void *e) {
                auto evt = static_cast<event_type *>(e);
                set_event(*evt);
            })
            .deliver_context(&evt);

        auto sensors = sensor_array::for_matches(std::move(config), is_tinkerforge_sensor);
        if (!sensors.empty()) {
            sensors.start();
            Assert::IsTrue(wait_event(evt, 1000), L"Sensor fired within 1 sec.", LINE_INFO());
            sensors.stop();
        }
    }

    TEST_METHOD(test_voltage_current_sensor_creation) {
        typedef detail::tinkerforge_sensor type;

        type::configuration_type config;
        std::vector<sensor_description> descs;
        descs.resize(type::descriptions(nullptr, 0, config));
        type::descriptions(descs.data(), descs.size(), config);

        detail::sensor_array_impl dummy;

        {
            auto end = std::remove_if(descs.begin(), descs.end(), [](const sensor_description &d) {
                return d.is_sensor_type(sensor_type::power);
                });
            descs.erase(end, descs.end());
        }

        type::list_type sensors;
        const auto unused = type::from_descriptions(sensors, 0, descs.begin(), descs.end(), &dummy, config);
        Assert::IsTrue(unused == descs.end(), L"All consumed", LINE_INFO());
    }

    TEST_METHOD(test_voltage_sensor_creation) {
        typedef detail::tinkerforge_sensor type;

        type::configuration_type config;
        std::vector<sensor_description> descs;
        descs.resize(type::descriptions(nullptr, 0, config));
        type::descriptions(descs.data(), descs.size(), config);

        detail::sensor_array_impl dummy;

        {
            auto end = std::remove_if(descs.begin(), descs.end(), [](const sensor_description &d) {
                return !d.is_sensor_type(sensor_type::voltage);
            });
            descs.erase(end, descs.end());
        }

        type::list_type sensors;
        const auto unused = type::from_descriptions(sensors, 0, descs.begin(), descs.end(), &dummy, config);
        Assert::IsTrue(unused == descs.end(), L"All consumed", LINE_INFO());
    }

};

PWROWG_TEST_NAMESPACE_END
