// <copyright file="daqmx_task_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"

#if defined(POWER_OVERWHELMING_WITH_DAQMX)
#include <visus/pwrowg/event.h>
#include <visus/pwrowg/daqmx_device.h>
#include <visus/pwrowg/daqmx_task.h>
#include <visus/pwrowg/multi_sz.h>
#include <visus/pwrowg/on_exit.h>

#include <daqmx_error_category.h>
#include <daqmx_library.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


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

        auto device = test_instrument();
        if (device) {
            task += daqmx_voltage_channel(multi_sz<char>::at(device.analog_inputs(), 0)).min_value(-10.0).max_value(10.0);
            task += daqmx_current_channel(multi_sz<char>::at(device.analog_inputs(), 1)).min_value(-10.0).max_value(10.0)
                .shunt_resistor_location(daqmx_shunt_resistor_location::external)
                .shunt_resistor_value(400);
            //task += daqmx_power_channel(multi_sz<char>::at(device.analog_inputs(), 2), multi_sz<char>::at(device.analog_inputs(), 3))
            //    .voltage_min_value(-5.0).voltage_max_value(5.0)
            //    .current_min_value(-2.0).current_max_value(2.0)
            //    .shunt_resistor_location(daqmx_shunt_resistor_location::external)
            //    .shunt_resistor_value(249.0);
        }
    }

    TEST_METHOD(clock_timing) {
        daqmx_task task("test");
        Assert::IsTrue(static_cast<bool>(task), L"Task valid", LINE_INFO());

        auto device = test_instrument();
        if (device) {
            task += daqmx_voltage_channel(multi_sz<char>::at(device.analog_inputs(), 0)).min_value(-10.0).max_value(10.0);
            task.timing(daqmx_sample_clock_timing(1000.0, daqmx_edge::rising, daqmx_sample_mode::finite, 1000));
        }
    }

    TEST_METHOD(on_done) {
        daqmx_task task("test");

        auto device = test_instrument();
        if (device) {
            Assert::IsTrue(static_cast<bool>(task), L"Task valid", LINE_INFO());
            task += daqmx_voltage_channel(multi_sz<char>::at(device.analog_inputs(), 0)).min_value(-10.0).max_value(10.0);
            task.on_done([](const daqmx_task& task, const int32) {
                Assert::IsTrue(static_cast<bool>(task), L"Task valid", LINE_INFO());
                return 0;
                });
        }
    }

    TEST_METHOD(on_sample) {
        daqmx_task task("test");
        Assert::IsTrue(static_cast<bool>(task), L"Task valid", LINE_INFO());

        auto device = test_instrument();
        if (device) {
            task += daqmx_voltage_channel(multi_sz<char>::at(device.analog_inputs(), 0)).min_value(-10.0).max_value(10.0);
            task.on_sample(1024, [](const daqmx_task& task, const daqmx_sample_event_type, uInt32) {
                Assert::IsTrue(static_cast<bool>(task), L"Task valid", LINE_INFO());
                return 0;
                });
        }
    }

    TEST_METHOD(read) {
        daqmx_task task("test");
        Assert::IsTrue(static_cast<bool>(task), L"Task valid", LINE_INFO());

        auto device = test_instrument();
        if (device) {
            task += daqmx_voltage_channel(multi_sz<char>::at(device.analog_inputs(), 0)).terminal_configuration(daqmx_terminal_configuration::differential).min_value(-10.0).max_value(10.0);
            task += daqmx_voltage_channel(multi_sz<char>::at(device.analog_inputs(), 1)).terminal_configuration(daqmx_terminal_configuration::differential).min_value(-10.0).max_value(10.0);
            task.timing(daqmx_sample_clock_timing(100.0, daqmx_edge::rising, daqmx_sample_mode::continuous, 10));
            detail::throw_if_daqmx_failed(detail::daqmx_library::instance()._DAQmxDisableStartTrig(task));
            auto evt = create_event();
            pwrowg_on_exit([&evt]() { destroy_event(evt); });
            task.on_sample(10, [evt](daqmx_task& t, const daqmx_sample_event_type, const uInt32 cnt) {
                Assert::AreEqual(uInt32(10), cnt, L"Sample count ready", LINE_INFO());
                std::array<double, 20> buffer;
                std::size_t read = 0;
                const auto status = t.read(read, buffer.data(), buffer.size());
                if (status >= 0) {
                    Assert::AreEqual(std::size_t(10), read, L"Read all", LINE_INFO());
                }
                set_event(evt);
                return 0;
            });
            task.start();
            wait_event(evt);
            task.stop();
            task.wait();
        }
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

#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
