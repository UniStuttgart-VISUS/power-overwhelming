// <copyright file="daqmx_task_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"

#if defined(POWER_OVERWHELMING_WITH_DAQMX)
#include <visus/pwrowg/daqmx_task.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


PWROWG_TEST_NAMESPACE_BEGIN

TEST_CLASS(daqmx_task_test) {

public:

    TEST_METHOD(ctor) {
        const daqmx_task task("test");
        Assert::IsTrue(static_cast<bool>(task), L"Task valid", LINE_INFO());
    }

#if false
    // Note: This test requires a (simulated) device NIUSB-6423 to be present.
    TEST_METHOD(add_channels) {
        daqmx_task task("test");
        Assert::IsTrue(static_cast<bool>(task), L"Task valid", LINE_INFO());
        task += daqmx_voltage_channel("NIUSB-6423/ai0").min_value(-10.0).max_value(10.0);
        task += daqmx_current_channel("NIUSB-6423/ai1").min_value(-10.0).max_value(10.0)
            .shunt_resistor_location(daqmx_shunt_resistor_location::external)
            .shunt_resistor_value(400);
        //task += daqmx_power_channel("NIUSB-6423/ai2", "NIUSB-6423/ai3")
        //    .voltage_min_value(-5.0).voltage_max_value(5.0)
        //    .current_min_value(-2.0).current_max_value(2.0)
        //    .shunt_resistor_location(daqmx_shunt_resistor_location::external)
        //    .shunt_resistor_value(249.0);
    }
#endif

};

PWROWG_TEST_NAMESPACE_END

#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
