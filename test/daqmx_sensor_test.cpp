// <copyright file="daqmx_sensor_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"

#include <visus/pwrowg/daqmx_configuration.h>
#include <visus/pwrowg/daqmx_current_channel.h>
#include <visus/pwrowg/daqmx_device.h>
#include <visus/pwrowg/daqmx_power_channel.h>
#include <visus/pwrowg/daqmx_sensor_definition.h>
#include <visus/pwrowg/daqmx_sensor_trigger_builder.h>
#include <visus/pwrowg/daqmx_voltage_channel.h>
#include <visus/pwrowg/multi_sz.h>

#include <daqmx_serialisation.h>
#include <sensor_array_impl.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


PWROWG_TEST_NAMESPACE_BEGIN

TEST_CLASS(daqmx_sensor_test) {

public:

    TEST_METHOD(daqmx_sensor_definition_dft_ctor) {
        daqmx_sensor_definition d;
        Assert::IsFalse(static_cast<bool>(d), L"Constructed invalid", LINE_INFO());
        Assert::IsNull(d.current_channel(), L"current_channel", LINE_INFO());
        Assert::IsNull(d.description(), L"description", LINE_INFO());
        Assert::IsNull(d.power_channel(), L"power_channel", LINE_INFO());
        Assert::IsNull(d.voltage_channel(), L"voltage_channel", LINE_INFO());
        Assert::IsNull(d.voltage_for_current_channel(), L"voltage_for_current_channel", LINE_INFO());

        daqmx_sensor_definition e(d);
        Assert::IsFalse(static_cast<bool>(e), L"Cloned invalid", LINE_INFO());
        Assert::IsNull(e.current_channel(), L"Cloned current_channel", LINE_INFO());
        Assert::IsNull(e.description(), L"Cloned description", LINE_INFO());
        Assert::IsNull(e.power_channel(), L"Cloned power_channel", LINE_INFO());
        Assert::IsNull(e.voltage_channel(), L"Cloned voltage_channel", LINE_INFO());
        Assert::IsNull(e.voltage_for_current_channel(), L"voltage_for_current_channel", LINE_INFO());
    }


    TEST_METHOD(daqmx_sensor_definition_1chan_ctor) {
        daqmx_sensor_definition d(daqmx_power_channel("ai1", "ai2"), L"Egon");
        Assert::IsTrue(static_cast<bool>(d), L"Constructed valid", LINE_INFO());
        Assert::IsNull(d.current_channel(), L"current_channel", LINE_INFO());
        Assert::AreEqual(L"Egon", d.description(), L"description", LINE_INFO());
        Assert::IsNotNull(d.power_channel(), L"power_channel", LINE_INFO());
        Assert::IsNull(d.voltage_channel(), L"voltage_channel", LINE_INFO());
        Assert::IsNull(d.voltage_for_current_channel(), L"voltage_for_current_channel", LINE_INFO());

        daqmx_sensor_definition e(d);
        Assert::IsTrue(static_cast<bool>(d), L"Cloned valid", LINE_INFO());
        Assert::IsNull(e.current_channel(), L"Cloned current_channel", LINE_INFO());
        Assert::AreEqual(d.description(), e.description(), L"Cloned description", LINE_INFO());
        Assert::IsNotNull(e.power_channel(), L"Cloned power_channel", LINE_INFO());
        Assert::IsNull(e.voltage_channel(), L"Cloned voltage_channel", LINE_INFO());
        Assert::IsNull(e.voltage_for_current_channel(), L"Cloned voltage_for_current_channel", LINE_INFO());

        Assert::AreEqual("ai1", e.power_channel()->voltage_channel(), L"power_channel voltage", LINE_INFO());
        Assert::AreEqual("ai2", e.power_channel()->current_channel(), L"power_channel current", LINE_INFO());
    }

    TEST_METHOD(daqmx_sensor_definition_1chan_serialisation) {
        daqmx_sensor_definition d(daqmx_power_channel("ai1", "ai2"), L"Egon");
        Assert::IsTrue(static_cast<bool>(d), L"Constructed valid", LINE_INFO());
        Assert::IsNull(d.current_channel(), L"current_channel", LINE_INFO());
        Assert::AreEqual(L"Egon", d.description(), L"description", LINE_INFO());
        Assert::IsNotNull(d.power_channel(), L"power_channel", LINE_INFO());
        Assert::IsNull(d.voltage_channel(), L"voltage_channel", LINE_INFO());
        Assert::IsNull(d.voltage_for_current_channel(), L"voltage_for_current_channel", LINE_INFO());

        const auto json = detail::json_serialise(d);

        const auto e = detail::json_deserialise<daqmx_sensor_definition>(json);
        Assert::IsTrue(static_cast<bool>(d), L"Cloned valid", LINE_INFO());
        Assert::IsNull(e.current_channel(), L"Cloned current_channel", LINE_INFO());
        Assert::AreEqual(d.description(), e.description(), L"Cloned description", LINE_INFO());
        Assert::IsNotNull(e.power_channel(), L"Cloned power_channel", LINE_INFO());
        Assert::IsNull(e.voltage_channel(), L"Cloned voltage_channel", LINE_INFO());
        Assert::IsNull(e.voltage_for_current_channel(), L"Cloned voltage_for_current_channel", LINE_INFO());

        Assert::AreEqual("ai1", e.power_channel()->voltage_channel(), L"power_channel voltage", LINE_INFO());
        Assert::AreEqual("ai2", e.power_channel()->current_channel(), L"power_channel current", LINE_INFO());
    }

    TEST_METHOD(daqmx_sensor_definition_2chan_ctor) {
        daqmx_sensor_definition d(daqmx_voltage_channel("ai1"), daqmx_current_channel("ai2"), L"Erich");
        Assert::IsTrue(static_cast<bool>(d), L"Constructed valid", LINE_INFO());
        Assert::IsNotNull(d.current_channel(), L"current_channel", LINE_INFO());
        Assert::AreEqual(L"Erich", d.description(), L"description", LINE_INFO());
        Assert::IsNull(d.power_channel(), L"power_channel", LINE_INFO());
        Assert::IsNotNull(d.voltage_channel(), L"voltage_channel", LINE_INFO());
        Assert::IsNull(d.voltage_for_current_channel(), L"voltage_for_current_channel", LINE_INFO());

        daqmx_sensor_definition e(d);
        Assert::IsTrue(static_cast<bool>(d), L"Cloned valid", LINE_INFO());
        Assert::IsNotNull(e.current_channel(), L"Cloned current_channel", LINE_INFO());
        Assert::AreEqual(d.description(), e.description(), L"Cloned description", LINE_INFO());
        Assert::IsNull(e.power_channel(), L"Cloned power_channel", LINE_INFO());
        Assert::IsNotNull(e.voltage_channel(), L"Cloned voltage_channel", LINE_INFO());
        Assert::IsNull(e.voltage_for_current_channel(), L"Cloned voltage_for_current_channel", LINE_INFO());

        Assert::AreEqual("ai1", e.voltage_channel()->channel(), L"voltage_channel path", LINE_INFO());
        Assert::AreEqual("ai2", e.current_channel()->channel(), L"current_channel path", LINE_INFO());
    }

    TEST_METHOD(daqmx_sensor_definition_2chan_serialise) {
        daqmx_sensor_definition d(daqmx_voltage_channel("ai1"), daqmx_current_channel("ai2"), L"Erich");
        Assert::IsTrue(static_cast<bool>(d), L"Constructed valid", LINE_INFO());
        Assert::IsNotNull(d.current_channel(), L"current_channel", LINE_INFO());
        Assert::AreEqual(L"Erich", d.description(), L"description", LINE_INFO());
        Assert::IsNull(d.power_channel(), L"power_channel", LINE_INFO());
        Assert::IsNotNull(d.voltage_channel(), L"voltage_channel", LINE_INFO());
        Assert::IsNull(d.voltage_for_current_channel(), L"voltage_for_current_channel", LINE_INFO());

        const auto json = detail::json_serialise(d);

        const auto e = detail::json_deserialise<daqmx_sensor_definition>(json);
        Assert::IsTrue(static_cast<bool>(d), L"Cloned valid", LINE_INFO());
        Assert::IsNotNull(e.current_channel(), L"Cloned current_channel", LINE_INFO());
        Assert::AreEqual(d.description(), e.description(), L"Cloned description", LINE_INFO());
        Assert::IsNull(e.power_channel(), L"Cloned power_channel", LINE_INFO());
        Assert::IsNotNull(e.voltage_channel(), L"Cloned voltage_channel", LINE_INFO());
        Assert::IsNull(e.voltage_for_current_channel(), L"Cloned voltage_for_current_channel", LINE_INFO());

        Assert::AreEqual("ai1", e.voltage_channel()->channel(), L"voltage_channel path", LINE_INFO());
        Assert::AreEqual("ai2", e.current_channel()->channel(), L"current_channel path", LINE_INFO());
    }

    TEST_METHOD(daqmx_sensor_definition_2vchan_ctor) {
        daqmx_sensor_definition d(daqmx_voltage_channel("ai1"), daqmx_voltage_channel("ai2"), 42, L"Erich");
        Assert::IsTrue(static_cast<bool>(d), L"Constructed valid", LINE_INFO());
        Assert::IsNull(d.current_channel(), L"current_channel", LINE_INFO());
        Assert::AreEqual(L"Erich", d.description(), L"description", LINE_INFO());
        Assert::IsNull(d.power_channel(), L"power_channel", LINE_INFO());
        Assert::IsNotNull(d.voltage_channel(), L"voltage_channel", LINE_INFO());
        Assert::IsNotNull(d.voltage_for_current_channel(), L"voltage_for_current_channel", LINE_INFO());

        daqmx_sensor_definition e(d);
        Assert::IsTrue(static_cast<bool>(d), L"Cloned valid", LINE_INFO());
        Assert::IsNull(e.current_channel(), L"Cloned current_channel", LINE_INFO());
        Assert::AreEqual(d.description(), e.description(), L"Cloned description", LINE_INFO());
        Assert::IsNull(e.power_channel(), L"Cloned power_channel", LINE_INFO());
        Assert::IsNotNull(e.voltage_channel(), L"Cloned voltage_channel", LINE_INFO());
        Assert::IsNotNull(e.voltage_for_current_channel(), L"Cloned voltage_for_current_channel", LINE_INFO());

        Assert::AreEqual("ai1", e.voltage_channel()->channel(), L"voltage_channel path", LINE_INFO());
        Assert::AreEqual("ai2", e.voltage_for_current_channel()->channel(), L"voltage_for_current_channel path", LINE_INFO());
    }

    TEST_METHOD(daqmx_sensor_definition_2vchan_serialise) {
        daqmx_sensor_definition d(daqmx_voltage_channel("ai1"), daqmx_voltage_channel("ai2"), 42, L"Erich");
        Assert::IsTrue(static_cast<bool>(d), L"Constructed valid", LINE_INFO());
        Assert::IsNull(d.current_channel(), L"current_channel", LINE_INFO());
        Assert::AreEqual(L"Erich", d.description(), L"description", LINE_INFO());
        Assert::IsNull(d.power_channel(), L"power_channel", LINE_INFO());
        Assert::IsNotNull(d.voltage_channel(), L"voltage_channel", LINE_INFO());
        Assert::IsNotNull(d.voltage_for_current_channel(), L"voltage_for_current_channel", LINE_INFO());

        const auto json = detail::json_serialise(d);

        const auto e = detail::json_deserialise<daqmx_sensor_definition>(json);
        Assert::IsTrue(static_cast<bool>(d), L"Cloned valid", LINE_INFO());
        Assert::IsNull(e.current_channel(), L"Cloned current_channel", LINE_INFO());
        Assert::AreEqual(d.description(), e.description(), L"Cloned description", LINE_INFO());
        Assert::IsNull(e.power_channel(), L"Cloned power_channel", LINE_INFO());
        Assert::IsNotNull(e.voltage_channel(), L"Cloned voltage_channel", LINE_INFO());
        Assert::IsNotNull(e.voltage_for_current_channel(), L"Cloned voltage_for_current_channel", LINE_INFO());

        Assert::AreEqual("ai1", e.voltage_channel()->channel(), L"voltage_channel path", LINE_INFO());
        Assert::AreEqual("ai2", e.voltage_for_current_channel()->channel(), L"voltage_for_current_channel path", LINE_INFO());
    }

    TEST_METHOD(test_sensor_creation) {
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
        typedef detail::daqmx_sensor type;
        const auto device = test_instrument();

        if (device) {
            detail::sensor_array_impl owner;
            owner.configuration = std::make_unique<detail::sensor_array_configuration_impl>();
            owner.configuration->sensor_configs[type::configuration_type::id] = std::make_unique<type::configuration_type>();

            auto sensor_config0 = owner.configuration->find_sensor_config(type::configuration_type::id);
            Assert::IsNotNull(sensor_config0, L"Configuration is set", LINE_INFO());

            auto sensor_config = dynamic_cast<type::configuration_type *>(sensor_config0);
            Assert::IsNotNull(sensor_config, L"Configuration is of correct type", LINE_INFO());

            sensor_config->timing(daqmx_sample_clock_timing(1000.0, daqmx_edge::rising, daqmx_sample_mode::continuous, 10 * 1024));
            auto trigger = daqmx_sensor_trigger_builder().when_starting().build();
            //trigger = daqmx_sensor_trigger_builder()
            //    .when_parallel_port("LPT1")
            //    .measured_via_channel("hugo/ai0")
            //    .build();
            sensor_config->trigger(trigger);

            sensor_config->add_sensor(
                daqmx_sensor_definition(
                    daqmx_voltage_channel(multi_sz<char>::at(device.analog_inputs(), 0)).max_value(10),
                    daqmx_voltage_channel(multi_sz<char>::at(device.analog_inputs(), 1)).max_value(10),
                    10));
            //sensor_config->add_sensor(
            //    daqmx_sensor_definition(
            //        daqmx_voltage_channel(multi_sz<char>::at(device.analog_inputs(), 2)).max_value(10),
            //        daqmx_current_channel(multi_sz<char>::at(device.analog_inputs(), 3)).max_value(10).shunt_resistor_location(daqmx_shunt_resistor_location::external).shunt_resistor_value(500)));

            std::vector<sensor_description> descs;
            descs.resize(type::descriptions(nullptr, 0, *sensor_config));
            type::descriptions(descs.data(), descs.size(), *sensor_config);

            type::list_type sensors;
            const auto unused = type::from_descriptions(sensors, 0, descs.begin(), descs.end(), &owner, *sensor_config);
            Assert::IsTrue(unused == descs.end(), L"All consumed", LINE_INFO());

            sensors.front().sample(true);
            std::this_thread::sleep_for(std::chrono::seconds(1));
            //Assert::IsTrue(trigger.acquire(
            //    [](void) { Assert::IsTrue(true, L"Triggered", LINE_INFO()); },
            //    [](std::exception_ptr) { Assert::IsTrue(false, L"Acquisition failure", LINE_INFO()); return true; }
            //), L"Acquire scheduled", LINE_INFO());
            std::this_thread::sleep_for(std::chrono::seconds(20));
        }
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
    }

    private:

        static daqmx_device test_instrument(void) {
            std::vector<daqmx_device> devices(daqmx_device::all(nullptr, 0));
            if (devices.empty()) {
                return daqmx_device();
            }

            daqmx_device::all(devices.data(), devices.size());
            return devices.front();
        }
};

PWROWG_TEST_NAMESPACE_END
