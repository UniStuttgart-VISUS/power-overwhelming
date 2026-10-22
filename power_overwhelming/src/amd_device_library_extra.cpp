// <copyright file="amd_device_library_extra.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if defined(POWER_OVERWHELMING_WITH_ADLX)
#include "amd_device_library_extra.h"


#define __POWER_OVERWHELMING_ADLX_FUNC(f, r) \
    do { \
        if constexpr (r) { \
            this->_##f = this->get_function<decltype(this->_##f)>(#f); \
        } else  {\
            this->_##f = this->try_get_function<decltype(this->_##f)>(#f); \
        } \
    } while (false)


/*
 * PWROWG_DETAIL_NAMESPACE::amd_device_library_extra::instance
 */
const PWROWG_DETAIL_NAMESPACE::amd_device_library_extra&
PWROWG_DETAIL_NAMESPACE::amd_device_library_extra::instance(void) {
    static const amd_device_library_extra instance;
    return instance;
}


/*
 * PWROWG_DETAIL_NAMESPACE::amd_device_library_extra::amd_device_library_extra
 */
PWROWG_DETAIL_NAMESPACE::amd_device_library_extra::amd_device_library_extra(
        void) : library_base(ADLX_DLL_NAME) {
    __POWER_OVERWHELMING_ADLX_FUNC(ADLXQueryFullVersion, true);
    __POWER_OVERWHELMING_ADLX_FUNC(ADLXQueryVersion, true);
    __POWER_OVERWHELMING_ADLX_FUNC(ADLXInitializeWithCallerAdl, true);
    __POWER_OVERWHELMING_ADLX_FUNC(ADLXInitialize, false);
    __POWER_OVERWHELMING_ADLX_FUNC(ADLXInitializeWithIncompatibleDriver, false);
    __POWER_OVERWHELMING_ADLX_FUNC(ADLXInitialize2, false);
    __POWER_OVERWHELMING_ADLX_FUNC(ADLXInitializeWithIncompatibleDriver2, false);
    __POWER_OVERWHELMING_ADLX_FUNC(ADLXTerminate, true);
}

#undef __POWER_OVERWHELMING_ADLX_FUNC
#endif /* defined(POWER_OVERWHELMING_WITH_ADLX) */
