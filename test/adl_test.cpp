// <copyright file="adl_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"

#include "amd_device_library_extra.h"
#include "amd_display_library.h"


PWROWG_TEST_NAMESPACE_BEGIN

TEST_CLASS(adl_test) {

public:

#if defined(POWER_OVERWHELMING_WITH_ADL)
    TEST_METHOD(adl_wrapper) {
        try {
            auto& lib = detail::amd_display_library::instance();
            Assert::IsNotNull(lib._ADL2_Adapter_Active_Get, L"ADL2_Adapter_Active_Get", LINE_INFO());
            Assert::IsNotNull(lib._ADL2_Adapter_AdapterInfo_Get, L"ADL2_Adapter_AdapterInfo_Get", LINE_INFO());
        } catch (...) { /* Test cannot run without AMD driver. */ }
    }
#endif /* defined(POWER_OVERWHELMING_WITH_ADL) */

#if defined(POWER_OVERWHELMING_WITH_ADLX)
    TEST_METHOD(adlx_wrapper) {
        try {
            auto& lib = detail::amd_device_library_extra::instance();
            Assert::IsNotNull(lib._ADLXQueryVersion, L"ADLXQueryVersion", LINE_INFO());
            //lib._ADLXInitializeWithIncompatibleDriver
        } catch (...) { /* Test cannot run without AMD driver. */ }
    }
#endif /* defined(POWER_OVERWHELMING_WITH_ADLX) */

};

PWROWG_TEST_NAMESPACE_END
