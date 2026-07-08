// <copyright file="daqmx_task_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"

#if defined(POWER_OVERWHELMING_WITH_DAQMX)
#include <visus/pwrowg/event.h>
#include <visus/pwrowg/daqmx_task.h>
#include <visus/pwrowg/on_exit.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define TEST_DEVICE_NAME "NIUSB-6423"


PWROWG_TEST_NAMESPACE_BEGIN

TEST_CLASS(daqmx_task_test) {

public:

    TEST_METHOD(ctor) {
        const daqmx_task task("test");
        Assert::IsTrue(static_cast<bool>(task), L"Task valid", LINE_INFO());
    }

    TEST_METHOD(add_channels) {
        daqmx_task task("test");
        Assert::IsTrue(static_cast<bool>(task), L"Task valid", LINE_INFO());
        try {
            task += daqmx_voltage_channel(TEST_DEVICE_NAME "/ai0").min_value(-10.0).max_value(10.0);
            task += daqmx_current_channel(TEST_DEVICE_NAME "/ai1").min_value(-10.0).max_value(10.0)
                .shunt_resistor_location(daqmx_shunt_resistor_location::external)
                .shunt_resistor_value(400);
            //task += daqmx_power_channel(TEST_DEVICE_NAME "/ai2", TEST_DEVICE_NAME "/ai3")
            //    .voltage_min_value(-5.0).voltage_max_value(5.0)
            //    .current_min_value(-2.0).current_max_value(2.0)
            //    .shunt_resistor_location(daqmx_shunt_resistor_location::external)
            //    .shunt_resistor_value(249.0);
        } catch (...) { /* Will fail if no device is present */ }
    }

    TEST_METHOD(clock_timing) {
        daqmx_task task("test");
        Assert::IsTrue(static_cast<bool>(task), L"Task valid", LINE_INFO());
        try {
            task += daqmx_voltage_channel(TEST_DEVICE_NAME "/ai0").min_value(-10.0).max_value(10.0);
            task.timing(daqmx_sample_clock_timing(1000.0, daqmx_edge::rising, daqmx_sample_mode::finite, 1000));
        } catch (...) { /* Will fail if no device is present */ }
    }

    TEST_METHOD(on_done) {
        daqmx_task task("test");
        Assert::IsTrue(static_cast<bool>(task), L"Task valid", LINE_INFO());
        task += daqmx_voltage_channel(TEST_DEVICE_NAME "/ai0").min_value(-10.0).max_value(10.0);
        task.on_done([](const daqmx_task& task, const int32) {
            Assert::IsTrue(static_cast<bool>(task), L"Task valid", LINE_INFO());
            return 0;
        });
    }

    TEST_METHOD(on_sample) {
        daqmx_task task("test");
        Assert::IsTrue(static_cast<bool>(task), L"Task valid", LINE_INFO());
        try {
            task += daqmx_voltage_channel(TEST_DEVICE_NAME "/ai0").min_value(-10.0).max_value(10.0);
            task.on_sample(1024, [](const daqmx_task& task, const daqmx_sample_event_type, uInt32) {
                Assert::IsTrue(static_cast<bool>(task), L"Task valid", LINE_INFO());
                return 0;
                });
        } catch (...) { /* Will fail if no device is present */ }
    }

    TEST_METHOD(read) {
        daqmx_task task("test");
        Assert::IsTrue(static_cast<bool>(task), L"Task valid", LINE_INFO());

        try {
            task += daqmx_voltage_channel(TEST_DEVICE_NAME "/ai0").terminal_configuration(daqmx_terminal_configuration::differential).min_value(-10.0).max_value(10.0);
            task += daqmx_voltage_channel(TEST_DEVICE_NAME "/ai1").terminal_configuration(daqmx_terminal_configuration::differential).min_value(-10.0).max_value(10.0);
            task.timing(daqmx_sample_clock_timing(100.0, daqmx_edge::rising, daqmx_sample_mode::continuous, 10));
            auto evt = create_event();
            pwrowg_on_exit([&evt]() { destroy_event(evt); });
            task.on_sample(10, [evt](daqmx_task& t, const daqmx_sample_event_type, const uInt32 cnt) {
                Assert::AreEqual(uInt32(10), cnt, L"Sample count ready", LINE_INFO());
                std::array<double, 20> buffer;
                Assert::AreEqual(std::size_t(10), t.read(buffer.data(), buffer.size()), L"Read all", LINE_INFO());
                set_event(evt);
                return 0;
                });
            task.start();
            wait_event(evt);
        } catch (...) { /* Will fail if no device is present */ }
    }

};

PWROWG_TEST_NAMESPACE_END

#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
