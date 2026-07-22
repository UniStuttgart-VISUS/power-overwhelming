// <copyright file="tinkerforge_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"

#include <sensor_array_impl.h>
#include <tinkerforge_sensor.h>


PWROWG_TEST_NAMESPACE_BEGIN

TEST_CLASS(tinkerforge_test) {

public:

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
            config.deliver_to([](const sample *s, const std::size_t cnt, const sensor_description *, void *e) {
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
