// <copyright file="rtx_sensor_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"
#include "CppUnitTest.h"

#include <visus/pwrowg/rtx_configuration.h>
#include <visus/pwrowg/rtx_instrument.h>
#include <visus/pwrowg/rtx_instrument_configuration.h>
#include <visus/pwrowg/rtx_sensor_trigger_builder.h>

#include <rtx_sensor.h>
#include <sensor_array_impl.h>


PWROWG_TEST_NAMESPACE_BEGIN

TEST_CLASS(rtx_sensor_test) {

public:

    TEST_METHOD(test_descriptions) {
        typedef detail::rtx_sensor type;
        const auto device = test_instrument();

        if (!device.empty()) {
            type::configuration_type config;
            config.add_sensor(device.c_str(),
                rtx_channel(1).attenuation(0.1f, "V").range(1.0f),
                rtx_channel(2).attenuation(0.1f, "A").range(2.0f));
            config.add_sensor(device.c_str(), 
                rtx_channel(3).attenuation(0.1f, "V").range(3.0f),
                rtx_channel());
            config.add_sensor(device.c_str(),
                rtx_channel(),
                rtx_channel(4).attenuation(1.0f, "A").range(4.0f));
            std::vector<sensor_description> descs;
            descs.resize(type::descriptions(nullptr, 0, config));
            Assert::AreEqual(std::size_t(3 + 1 + 1), descs.size(), L"Description for power sensor.", LINE_INFO());
            type::descriptions(descs.data(), descs.size(), config);
        }
    }

    TEST_METHOD(test_sensor_config) {
        rtx_configuration config;
        Assert::AreEqual(std::size_t(0), config.count_sensors(), L"No sensors in list", LINE_INFO());
        Assert::IsNull(config.sensors(), L"No sensors allocated", LINE_INFO());

        config.trigger(rtx_sensor_trigger_builder::for_path("hugo").when_channel("CH0").rises_above(2.5f).build());
        Assert::AreEqual("hugo", config.trigger().path(), L"Trigger path is set", LINE_INFO());
        Assert::IsNotNull(config.trigger().trigger(), L"Trigger is set", LINE_INFO());
        Assert::AreEqual("CH0", config.trigger().trigger()->source(), L"Trigger source is set", LINE_INFO());

        config.add_sensor(L"hugo",
            rtx_channel(1).attenuation(10.f, "V").range(1.0f),
            rtx_channel(2).attenuation(1.f, "A").range(2.0f));
        Assert::AreEqual(std::size_t(1), config.count_sensors(), L"One sensor in list", LINE_INFO());
        Assert::IsNotNull(config.sensors(), L"Sensors allocated", LINE_INFO());
        Assert::AreEqual("hugo", config.sensors()[0].path(), L"Sensor path is set", LINE_INFO());
        Assert::AreEqual(std::uint32_t(1), config.sensors()[0].voltage_channel().channel(), L"Voltage channel is set", LINE_INFO());
        Assert::AreEqual(10.f, config.sensors()[0].voltage_channel().attenuation().value(), L"Voltage attenuation is set", LINE_INFO());
        Assert::AreEqual(std::uint32_t(2), config.sensors()[0].current_channel().channel(), L"Current channel is set", LINE_INFO());
        Assert::AreEqual(1.f, config.sensors()[0].current_channel().attenuation().value(), L"Current attenuation is set", LINE_INFO());

        config.save(L"rtx_sensor_test.json");
        auto config2 = rtx_configuration::load(L"rtx_sensor_test.json");
        Assert::AreEqual(config.count_sensors(), config2.count_sensors(), L"One sensor restored", LINE_INFO());
        Assert::IsNotNull(config2.sensors(), L"Sensors allocated", LINE_INFO());
        Assert::AreEqual(config.sensors()[0].path(), config2.sensors()[0].path(), L"Sensor path is restored", LINE_INFO());
        Assert::AreEqual(config.sensors()[0].voltage_channel().channel(), config2.sensors()[0].voltage_channel().channel(), L"Voltage channel is restored", LINE_INFO());
        Assert::AreEqual(config.sensors()[0].voltage_channel().attenuation().value(), config2.sensors()[0].voltage_channel().attenuation().value(), L"Voltage attenuation is restored", LINE_INFO());
        Assert::AreEqual(config.sensors()[0].current_channel().channel(), config2.sensors()[0].current_channel().channel(), L"Current channel is restored", LINE_INFO());
        Assert::AreEqual(config.sensors()[0].current_channel().attenuation().value(), config2.sensors()[0].current_channel().attenuation().value(), L"Current attenuation is restored", LINE_INFO());
    }

    TEST_METHOD(test_sensor_creation) {
        typedef detail::rtx_sensor type;
        const auto device = test_instrument();

        if (!device.empty()) {
            detail::sensor_array_impl owner;
            owner.configuration = std::make_unique<detail::sensor_array_configuration_impl>();
            owner.configuration->sensor_configs[type::configuration_type::id] = std::make_unique<type::configuration_type>();

            auto sensor_config0 = owner.configuration->find_sensor_config(type::configuration_type::id);
            Assert::IsNotNull(sensor_config0, L"Configuration is set", LINE_INFO());

            auto sensor_config = dynamic_cast<type::configuration_type *>(sensor_config0);
            Assert::IsNotNull(sensor_config, L"Configuration is of correct type", LINE_INFO());
            sensor_config->base_configuration(rtx_instrument_configuration(std::chrono::seconds(3), 5000, 4000).beep_on_trigger(true))
                .download_retries(1)
                .download_timeout(10000);
            auto trigger = rtx_sensor_trigger_builder::for_path(device.c_str()).when_software_triggered().build();
            //trigger = rtx_sensor_trigger_builder::for_all().when_parallel_port("LPT1").measured_via_external().build();
            //trigger = rtx_sensor_trigger_builder::for_all().when_channel("CH1").rises_above(0.1f).build();
            sensor_config->trigger(trigger);

            sensor_config->add_sensor(device.c_str(),
                rtx_channel(1).range(2.0f, "V").attenuation(0.1f, "V"),
                rtx_channel(2).range(2.0f, "A").attenuation(0.1f, "A"));
            sensor_config->add_sensor(device.c_str(),
                rtx_channel(3).range(4.0f, "V").attenuation(1.0f, "V"),
                rtx_channel(4).range(4.0f, "A").attenuation(1.0f, "A"));

            std::vector<sensor_description> descs;
            descs.resize(type::descriptions(nullptr, 0, *sensor_config));
//            Assert::AreEqual(std::size_t(2 * 3), descs.size(), L"Descriptions for all sensors and the power sensor.", LINE_INFO());
            type::descriptions(descs.data(), descs.size(), *sensor_config);

            type::list_type sensors;
            const auto unused = type::from_descriptions(sensors, 0, descs.begin(), descs.end(), &owner, *sensor_config);
            Assert::IsTrue(unused == descs.end(), L"All consumed", LINE_INFO());

            sensors.front().sample(true);
            std::this_thread::sleep_for(std::chrono::seconds(1));
            Assert::IsTrue(trigger.acquire(
                [](void) { Assert::IsTrue(true, L"Triggered", LINE_INFO()); },
                [](std::exception_ptr) { Assert::IsTrue(false, L"Acquisition failure", LINE_INFO()); return true; }
            ), L"Acquire scheduled", LINE_INFO());
            std::this_thread::sleep_for(std::chrono::seconds(5));
        }
    }

    TEST_METHOD(test_sensor_trigger) {
        {
            rtx_sensor_trigger trigger;
            Assert::IsNotNull(trigger.path(), L"Default path is not null", LINE_INFO());
            Assert::AreEqual("", trigger.path(), L"Default path is empty", LINE_INFO());
            Assert::IsNull(trigger.trigger(), L"No trigger set", LINE_INFO());
        }
        {
            auto trigger = rtx_sensor_trigger_builder::for_path("hugo").when_channel(std::uint8_t(1)).rises_above(2.5f).build();
            Assert::AreEqual("hugo", trigger.path(), L"Path is set", LINE_INFO());
            Assert::IsNotNull(trigger.trigger(), L"Trigger is set", LINE_INFO());
        }
        {
            auto trigger = rtx_sensor_trigger_builder::for_path("hugo").when_software_triggered().with_daisy_chain().build();
            Assert::AreEqual("hugo", trigger.path(), L"Path is set", LINE_INFO());
            Assert::IsNull(trigger.trigger(), L"Trigger is not set", LINE_INFO());
        }
#if false
        {
            // This test will only work if the port extension card is installed on the test machine.
            auto trigger = rtx_sensor_trigger_builder::for_first().when_channel("CH1").rises_above(2.5f).build();
            Assert::IsNotNull(trigger.path(), L"Path is set", LINE_INFO());
        }
#endif
#if false
        {
            // This test will only work if the port extension card is installed on the test machine.
            auto trigger = rtx_sensor_trigger_builder::for_name("rta01").when_channel("CH1").rises_above(2.5f).build();
            Assert::IsNotNull(trigger.path(), L"Path is set", LINE_INFO());
        }
#endif
#if false
        {
            // This test will only work if the port extension card is installed on the test machine.
            auto trigger = rtx_sensor_trigger_builder::for_path("hugo")
                .when_parallel_port("LTP1")
                .raise_pins(parallel_port_pin::all)
                .for_duration(100)
                .measured_via_channel("CH1")
                .at_level(2.9f)
                .build();
            Assert::AreEqual("hugo", trigger.path(), L"Path is set", LINE_INFO());
            Assert::IsNotNull(trigger.trigger(), L"Trigger is set", LINE_INFO());
        }
#endif
#if false
        {
            // This test will only work if the port extension card is installed on the test machine.
            auto trigger = rtx_sensor_trigger_builder::for_path("hugo").when_parallel_port("COM1").measured_via_channel("CH1").build();
            Assert::AreEqual("hugo", trigger.path(), L"Path is set", LINE_INFO());
            Assert::IsNotNull(trigger.trigger(), L"Trigger is set", LINE_INFO());
        }
#endif
#if false
        {
            // This test will only work if the port extension card is installed on the test machine.
            auto trigger = rtx_sensor_trigger_builder::for_serial(L"103698").when_channel("CH1").rises_above(2.5f).build();
            Assert::IsNotNull(trigger.path(), L"Path is set", LINE_INFO());
        }
#endif
    }

    TEST_METHOD(test_voltage_only_sensor_creation) {
        typedef detail::rtx_sensor type;
        const auto device = test_instrument();

        if (!device.empty()) {
            detail::sensor_array_impl owner;
            owner.configuration = std::make_unique<detail::sensor_array_configuration_impl>();
            owner.configuration->sensor_configs[type::configuration_type::id] = std::make_unique<type::configuration_type>();

            auto sensor_config0 = owner.configuration->find_sensor_config(type::configuration_type::id);
            Assert::IsNotNull(sensor_config0, L"Configuration is set", LINE_INFO());

            auto sensor_config = dynamic_cast<type::configuration_type *>(sensor_config0);
            Assert::IsNotNull(sensor_config, L"Configuration is of correct type", LINE_INFO());

            sensor_config->base_configuration(rtx_instrument_configuration(std::chrono::seconds(3), 5000, 4000).beep_on_trigger(true))
                .download_retries(1)
                .download_timeout(10000);
            auto trigger = rtx_sensor_trigger_builder::for_path(device.c_str()).when_software_triggered().build();
            sensor_config->trigger(trigger);

            sensor_config->add_sensor(device.c_str(),
                rtx_channel(1).range(2.0f, "V").attenuation(0.1f, "V"),
                rtx_channel(2).range(2.0f, "A").attenuation(0.1f, "A"));
            sensor_config->add_sensor(device.c_str(),
                rtx_channel(3).range(4.0f, "V").attenuation(1.0f, "V"),
                rtx_channel());

            std::vector<sensor_description> descs;
            descs.resize(type::descriptions(nullptr, 0, *sensor_config));
            Assert::AreEqual(std::size_t(4), descs.size(), L"Descriptions for all sensors and the power sensor.", LINE_INFO());
            type::descriptions(descs.data(), descs.size(), *sensor_config);

            type::list_type sensors;
            const auto unused = type::from_descriptions(sensors, 0, descs.begin(), descs.end(), &owner, *sensor_config);
            Assert::IsTrue(unused == descs.end(), L"All consumed", LINE_INFO());

            sensors.front().sample(true);
            std::this_thread::sleep_for(std::chrono::seconds(1));
            Assert::IsTrue(trigger.acquire(
                [](void) { Assert::IsTrue(true, L"Triggered", LINE_INFO()); },
                [](std::exception_ptr) { Assert::IsTrue(false, L"Acquisition failure", LINE_INFO()); return true; }
            ), L"Acquire scheduled", LINE_INFO());
            std::this_thread::sleep_for(std::chrono::seconds(5));
        }
    }

#if false
    TEST_METHOD(test_multi_sensor_creation) {
        typedef detail::rtx_sensor type;

        if (rtx_instrument::all(nullptr, 0) > 1) {
            detail::sensor_array_impl owner;
            owner.configuration = std::make_unique<detail::sensor_array_configuration_impl>();
            owner.configuration->sensor_configs[type::configuration_type::id] = std::make_unique<type::configuration_type>();

            auto sensor_config0 = owner.configuration->find_sensor_config(type::configuration_type::id);
            Assert::IsNotNull(sensor_config0, L"Configuration is set", LINE_INFO());

            auto sensor_config = dynamic_cast<type::configuration_type *>(sensor_config0);
            Assert::IsNotNull(sensor_config, L"Configuration is of correct type", LINE_INFO());

            sensor_config->base_configuration(rtx_instrument_configuration(std::chrono::seconds(3), 5000, 4000).beep_on_trigger(true).beep_on_apply(true))
                .download_retries(1)
                .download_timeout(10000);
            auto trigger = rtx_sensor_trigger_builder::for_all().when_parallel_port("LPT3").measured_via_external().build();
            trigger = rtx_sensor_trigger_builder::for_all().when_software_triggered().build();
            sensor_config->trigger(trigger);

            std::vector<rtx_instrument> instruments(rtx_instrument::all(nullptr, 0));
            rtx_instrument::all(instruments.data(), instruments.size());
            Assert::IsFalse(instruments.empty(), L"Have at least one instrument", LINE_INFO());

            rtx_instrument::foreach_instance([](visa_instrument& i, void *c) {
                auto config = static_cast<type::configuration_type *>(c);
                config->add_sensor(i.path(),
                    rtx_channel(1).range(2.0f, "V").attenuation(0.1f, "V"),
                    rtx_channel(2).range(2.0f, "A").attenuation(0.1f, "A"));
                config->add_sensor(i.path(),
                    rtx_channel(1).range(2.0f, "V").attenuation(0.1f, "V"),
                    rtx_channel(2).range(2.0f, "A").attenuation(0.1f, "A"));
                return true;
            }, sensor_config);

            std::vector<sensor_description> descs(type::descriptions(nullptr, 0, *sensor_config));
            type::descriptions(descs.data(), descs.size(), *sensor_config);

            type::list_type sensors;
            const auto unused = type::from_descriptions(sensors, 0, descs.begin(), descs.end(), &owner, *sensor_config);
            Assert::IsTrue(unused == descs.end(), L"All consumed", LINE_INFO());
            Assert::IsFalse(sensors.empty(), L"Have at least one sensor.", LINE_INFO());

            sensors.front().sample(true);
            auto evt = create_event();
            std::this_thread::sleep_for(std::chrono::seconds(1));
            Assert::IsTrue(trigger.acquire(
                [evt](void) { 
                    Assert::IsTrue(true, L"Triggered", LINE_INFO()); 
                    set_event(evt);
                },
                [evt](std::exception_ptr) {
                    set_event(evt);
                    Assert::IsTrue(false, L"Acquisition failure", LINE_INFO());
                    return true;
                }
            ), L"Acquire scheduled", LINE_INFO());
            wait_event(evt);
        }
    }
#endif

private:

    static std::string test_instrument(void) {
#if defined(POWER_OVERWHELMING_WITH_VISA)
        try {
            auto result = rtx_instrument::find_resources(rtx_instrument::rohde_und_schwarz, rtx_instrument::product_id);
            auto msz = result.as<char>();
            return (msz != nullptr) ? msz : "";
        } catch (...) { }
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */
        return "";
    }
};

PWROWG_TEST_NAMESPACE_END
