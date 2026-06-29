// <copyright file="daqmx_library_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"

#include <daqmx_library.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


PWROWG_TEST_NAMESPACE_BEGIN

TEST_CLASS(daqmx_library_test) {

public:

#if defined(POWER_OVERWHELMING_WITH_DAQMX)
    TEST_METHOD(instance) {
        auto& instance = detail::daqmx_library::instance();
        Assert::IsNotNull(instance._DAQmxGetErrorString, L"DAQmxGetErrorString", LINE_INFO());
    }
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */

};

PWROWG_TEST_NAMESPACE_END
