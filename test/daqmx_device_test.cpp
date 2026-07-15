// <copyright file="daqmx_device_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"

#if defined(POWER_OVERWHELMING_WITH_DAQMX)
#include <visus/pwrowg/daqmx_device.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define TEST_DEVICE_NAME "NIUSB-6423"


PWROWG_TEST_NAMESPACE_BEGIN

TEST_CLASS(daqmx_device_test) {

public:

    TEST_METHOD(all) {
        std::vector<daqmx_device> devices(daqmx_device::all(nullptr, 0));
        daqmx_device::all(devices.data(), devices.size());
    }

    TEST_METHOD(ctor) {
        daqmx_device d(TEST_DEVICE_NAME);
        Assert::AreEqual(TEST_DEVICE_NAME, d.name(), L"name", LINE_INFO());
        Assert::IsNotNull(d.analog_inputs(), L"analog_inputs", LINE_INFO());
        Assert::IsNotNull(d.analog_outputs(), L"analog_outputs", LINE_INFO());
        Assert::IsTrue(d.simulated(), L"simulated", LINE_INFO());
        Assert::IsNotNull(d.type(), L"type", LINE_INFO());
    }

};

PWROWG_TEST_NAMESPACE_END

#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
