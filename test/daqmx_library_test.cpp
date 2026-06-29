// <copyright file="daqmx_library_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"

#if defined(POWER_OVERWHELMING_WITH_DAQMX)
#include <daqmx_error_category.h>
#include <daqmx_library.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


PWROWG_TEST_NAMESPACE_BEGIN

TEST_CLASS(daqmx_library_test) {

public:

    TEST_METHOD(instance) {
        auto& instance = detail::daqmx_library::instance();
        Assert::IsNotNull(instance._DAQmxGetErrorString, L"DAQmxGetErrorString", LINE_INFO());
    }

    TEST_METHOD(error_category) {
        auto msg = detail::daqmx_category().message(DAQmxErrorTimeoutExceeded);
        Assert::IsFalse(msg.empty(), L"Error message should not be empty", LINE_INFO());
    }

};

PWROWG_TEST_NAMESPACE_END

#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
