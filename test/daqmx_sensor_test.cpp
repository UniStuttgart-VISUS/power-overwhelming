// <copyright file="daqmx_sensor_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"

#include <visus/pwrowg/daqmx_configuration.h>
#include <visus/pwrowg/daqmx_current_channel.h>
#include <visus/pwrowg/daqmx_power_channel.h>
#include <visus/pwrowg/daqmx_sensor_definition.h>
#include <visus/pwrowg/daqmx_voltage_channel.h>

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

        daqmx_sensor_definition e(d);
        Assert::IsFalse(static_cast<bool>(e), L"Cloned invalid", LINE_INFO());
        Assert::IsNull(d.current_channel(), L"Cloned current_channel", LINE_INFO());
        Assert::IsNull(d.description(), L"Cloned description", LINE_INFO());
        Assert::IsNull(d.power_channel(), L"Cloned power_channel", LINE_INFO());
        Assert::IsNull(d.voltage_channel(), L"Cloned voltage_channel", LINE_INFO());
    }

    TEST_METHOD(daqmx_sensor_definition_2chan_ctor) {
        daqmx_sensor_definition d(daqmx_voltage_channel("ai1"), daqmx_current_channel("ai2"), L"Erich");
        Assert::IsTrue(static_cast<bool>(d), L"Constructed valid", LINE_INFO());
        Assert::IsNotNull(d.current_channel(), L"current_channel", LINE_INFO());
        Assert::AreEqual(L"Erich", d.description(), L"description", LINE_INFO());
        Assert::IsNull(d.power_channel(), L"power_channel", LINE_INFO());
        Assert::IsNotNull(d.voltage_channel(), L"voltage_channel", LINE_INFO());

        daqmx_sensor_definition e(d);
        Assert::IsTrue(static_cast<bool>(d), L"Cloned valid", LINE_INFO());
        Assert::IsNotNull(e.current_channel(), L"Cloned current_channel", LINE_INFO());
        Assert::AreEqual(d.description(), e.description(), L"Cloned description", LINE_INFO());
        Assert::IsNull(e.power_channel(), L"Cloned power_channel", LINE_INFO());
        Assert::IsNotNull(e.voltage_channel(), L"Cloned voltage_channel", LINE_INFO());
    }

    TEST_METHOD(daqmx_sensor_definition_chan_ctor) {
        daqmx_sensor_definition d(daqmx_power_channel("ai1", "ai2"), L"Egon");
        Assert::IsTrue(static_cast<bool>(d), L"Constructed valid", LINE_INFO());
        Assert::IsNull(d.current_channel(), L"current_channel", LINE_INFO());
        Assert::AreEqual(L"Egon", d.description(), L"description", LINE_INFO());
        Assert::IsNotNull(d.power_channel(), L"power_channel", LINE_INFO());
        Assert::IsNull(d.voltage_channel(), L"voltage_channel", LINE_INFO());

        daqmx_sensor_definition e(d);
        Assert::IsTrue(static_cast<bool>(d), L"Cloned valid", LINE_INFO());
        Assert::IsNull(e.current_channel(), L"Cloned current_channel", LINE_INFO());
        Assert::AreEqual(d.description(), e.description(), L"Cloned description", LINE_INFO());
        Assert::IsNotNull(e.power_channel(), L"Cloned power_channel", LINE_INFO());
        Assert::IsNull(e.voltage_channel(), L"Cloned voltage_channel", LINE_INFO());
    }

};

PWROWG_TEST_NAMESPACE_END
