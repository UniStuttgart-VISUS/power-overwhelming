// <copyright file="daqmx_configuration_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"

#include <visus/pwrowg/daqmx_configuration.h>
#include <visus/pwrowg/daqmx_current_channel.h>
#include <visus/pwrowg/daqmx_power_channel.h>
#include <visus/pwrowg/daqmx_voltage_channel.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


PWROWG_TEST_NAMESPACE_BEGIN

TEST_CLASS(daqmx_configuration_test) {

public:

#if defined(POWER_OVERWHELMING_WITH_DAQMX)
    TEST_METHOD(timing_get_set) {
        daqmx_configuration config;
        config.timing(daqmx_sample_clock_timing("ch1", 1000.0, daqmx_edge::falling, daqmx_sample_mode::continuous, 2048));

        {
            const daqmx_sample_clock_timing *t = nullptr;
            Assert::IsTrue(config.try_get(t), L"try_get sample clock timing", LINE_INFO());
            Assert::IsNotNull(t, L"sample clock timing pointer should not be null", LINE_INFO());
            Assert::AreEqual(1000.0, t->rate(), L"sample rate", LINE_INFO());
            Assert::AreEqual(int(daqmx_sample_mode::continuous), int(t->mode()), L"sample mode", LINE_INFO());
            Assert::AreEqual(std::uint64_t(2048), t->samples(), L"samples per channel", LINE_INFO());
            Assert::AreEqual("ch1", t->source(), L"source channel", LINE_INFO());
            Assert::AreEqual(int(daqmx_edge::falling), int(t->edge()), L"source edge", LINE_INFO());
        }

        {
            const daqmx_implicit_timing *t = nullptr;
            Assert::IsFalse(config.try_get(t), L"try_get implicit timing", LINE_INFO());
            Assert::IsNull(t, L"implicit timing pointer should be null", LINE_INFO());
        }
    }
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */

    TEST_METHOD(channels) {
        daqmx_configuration config;
        Assert::AreEqual(std::size_t(0), config.count_sensors(), L"initial sensor count", LINE_INFO());

        config.add_sensor(daqmx_sensor_definition(daqmx_voltage_channel("ai1"), daqmx_voltage_channel("ai2"), 42.0, L"Erich"));
        Assert::AreEqual(std::size_t(1), config.count_sensors(), L"sensor count after adding one sensor", LINE_INFO());
        Assert::IsNotNull(config.sensors(), L"sensors() should not return null", LINE_INFO());
        Assert::AreEqual(config.sensor(0).description(), L"Erich", L"sensor 0 description", LINE_INFO());
        Assert::AreEqual(config.sensor(0).voltage_channel()->channel(), "ai1", L"sensor 0 voltage channel", LINE_INFO());
        Assert::AreEqual(config.sensor(0).voltage_for_current_channel()->channel(), "ai2", L"sensor 0 voltage for current channel", LINE_INFO());
        Assert::AreEqual(42.0, config.sensor(0).volt_per_ampere(), L"sensor 0 V/A", LINE_INFO());

        config.add_sensor(daqmx_sensor_definition(daqmx_power_channel("ai3", "ai4"), L"Walter"));
        Assert::AreEqual(std::size_t(2), config.count_sensors(), L"sensor count after adding second sensor", LINE_INFO());
        Assert::IsNotNull(config.sensors(), L"sensors() should not return null", LINE_INFO());
        Assert::AreEqual(config.sensor(1).description(), L"Walter", L"sensor 1 description", LINE_INFO());
        Assert::AreEqual(config.sensor(1).power_channel()->voltage_channel(), "ai3", L"sensor 1 voltage channel", LINE_INFO());
        Assert::AreEqual(config.sensor(1).power_channel()->current_channel(), "ai4", L"sensor 1 current channel", LINE_INFO());
    }

};

PWROWG_TEST_NAMESPACE_END
