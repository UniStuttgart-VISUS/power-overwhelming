// <copyright file="rtx_sensor_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"
#include "CppUnitTest.h"

#include "visus/pwrowg/rtx_configuration.h"
#include "visus/pwrowg/rtx_sensor_trigger_builder.h"

#include "rtx_sensor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


PWROWG_TEST_NAMESPACE_BEGIN

TEST_CLASS(rtx_sensor_test) {

public:

    TEST_METHOD(test_descriptions) {
        typedef detail::rtx_sensor type;
        const auto device = test_instrument();

        if (!device.empty()) {
            type::configuration_type config;
            config.add_sensor(device.c_str(), 1, 10.f, 2, 10.0f);
            config.add_sensor(device.c_str(), 3, 10.f, 0, 0.0f);
            config.add_sensor(device.c_str(), 0, 0.f, 4, 1.0f);

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

        config.add_sensor(L"hugo", 1, 10.f, 2, 1.0f);
        Assert::AreEqual(std::size_t(1), config.count_sensors(), L"One sensor in list", LINE_INFO());
        Assert::IsNotNull(config.sensors(), L"Sensors allocated", LINE_INFO());
        Assert::AreEqual("hugo", config.sensors()[0].path(), L"Sensor path is set", LINE_INFO());
        Assert::AreEqual(std::uint32_t(1), config.sensors()[0].voltage_channel().channel(), L"Voltage channel is set", LINE_INFO());
        Assert::AreEqual(10.f, config.sensors()[0].voltage_channel().attenuation().value(), L"Voltage attenuation is set", LINE_INFO());
        Assert::AreEqual(std::uint32_t(2), config.sensors()[0].current_channel().channel(), L"Current channel is set", LINE_INFO());
        Assert::AreEqual(1.f, config.sensors()[0].current_channel().attenuation().value(), L"Current attenuation is set", LINE_INFO());
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
            sensor_config->add_sensor(device.c_str(), 1, 10.f, 2, 10.0f);
            sensor_config->add_sensor(device.c_str(), 3, 1.f, 4, 1.0f);

            std::vector<sensor_description> descs;
            descs.resize(type::descriptions(nullptr, 0, *sensor_config));
            Assert::AreEqual(std::size_t(2 * 3), descs.size(), L"Descriptions for all sensors and the power sensor.", LINE_INFO());
            type::descriptions(descs.data(), descs.size(), *sensor_config);

            type::list_type sensors;
            const auto unused = type::from_descriptions(sensors, 0, descs.begin(), descs.end(), &owner, *sensor_config);
            Assert::IsTrue(unused == descs.end(), L"All consumed", LINE_INFO());
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
            auto trigger = rtx_sensor_trigger_builder::for_path("hugo").when_software_triggered().build();
            Assert::AreEqual("hugo", trigger.path(), L"Path is set", LINE_INFO());
            Assert::IsNull(trigger.trigger(), L"Trigger is not set", LINE_INFO());
        }
#if 0
        {
            // This test will only work if the port extension card is installed on the test machine.
            auto trigger = rtx_sensor_trigger_builder::for_first().when_channel("CH1").rises_above(2.5f).build();
            Assert::IsNotNull(trigger.path(), L"Path is set", LINE_INFO());
        }
#endif
#if 0
        {
            // This test will only work if the port extension card is installed on the test machine.
            auto trigger = rtx_sensor_trigger_builder::for_name("rta01").when_channel("CH1").rises_above(2.5f).build();
            Assert::IsNotNull(trigger.path(), L"Path is set", LINE_INFO());
        }
#endif
#if 0
        {
            // This test will only work if the port extension card is installed on the test machine.
            auto trigger = rtx_sensor_trigger_builder::for_path("hugo")
                .when_parallel_port("COM1")
                .raise_pins(parallel_port_pin::all)
                .for_duration(100)
                .measured_via_channel("CH1")
                .at_level(2.9f)
                .build();
            Assert::AreEqual("hugo", trigger.path(), L"Path is set", LINE_INFO());
            Assert::IsNotNull(trigger.trigger(), L"Trigger is set", LINE_INFO());
        }
#endif
#if 0
        {
            // This test will only work if the port extension card is installed on the test machine.
            auto trigger = rtx_sensor_trigger_builder::for_path("hugo").when_parallel_port("COM1").measured_via_channel("CH1").build();
            Assert::AreEqual("hugo", trigger.path(), L"Path is set", LINE_INFO());
            Assert::IsNotNull(trigger.trigger(), L"Trigger is set", LINE_INFO());
        }
#endif
#if 0
        {
            // This test will only work if the port extension card is installed on the test machine.
            auto trigger = rtx_sensor_trigger_builder::for_serial(L"103698").when_channel("CH1").rises_above(2.5f).build();
            Assert::IsNotNull(trigger.path(), L"Path is set", LINE_INFO());
        }
#endif
    }

private:

    static std::string test_instrument(void) {
#if defined(POWER_OVERWHELMING_WITH_VISA)
        try {
            auto result = rtx_instrument::find_resources("?*::0x0AAD::?*::?*::INSTR");
            auto msz = result.as<char>();
            return (msz != nullptr) ? msz : "";
        } catch (...) { }
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */
        return "";
    }

};

PWROWG_TEST_NAMESPACE_END
