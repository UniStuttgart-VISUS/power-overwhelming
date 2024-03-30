// <copyright file="amd_display_library.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "amd_display_library.h"

#include <atomic>
#include <cassert>
#include <cinttypes>
#include <new>
#include <system_error>

#if defined(_WIN32)
#include <tchar.h>
#else /* defined(_WIN32) */
#define TEXT(t) (t)
#endif /* defined(_WIN32) */

#include "amd_display_library.h"


#define __POWER_OVERWHELMING_GET_ADL_FUNC(n) \
    this->n = this->get_function<decltype(this->n)>(#n)


/*
 * visus::power_overwhelming::detail::amd_display_library::instance
 */
const visus::power_overwhelming::detail::amd_display_library&
visus::power_overwhelming::detail::amd_display_library::instance(void) {
    static const amd_display_library instance;
    return instance;
}


/*
 * visus::power_overwhelming::detail::amd_display_library::amd_display_library
 */
visus::power_overwhelming::detail::amd_display_library::amd_display_library(
        void) : library_base(TEXT("atiadlxx.dll"), TEXT("atiadlxy.dll")) {
    __POWER_OVERWHELMING_GET_ADL_FUNC(ADL2_Adapter_Active_Get);
    __POWER_OVERWHELMING_GET_ADL_FUNC(ADL2_Adapter_AdapterInfo_Get);
    __POWER_OVERWHELMING_GET_ADL_FUNC(ADL2_Adapter_NumberOfAdapters_Get);
    __POWER_OVERWHELMING_GET_ADL_FUNC(ADL2_Adapter_PMLog_Support_Get);
    __POWER_OVERWHELMING_GET_ADL_FUNC(ADL2_Adapter_PMLog_Start);
    __POWER_OVERWHELMING_GET_ADL_FUNC(ADL2_Adapter_PMLog_Stop);
    __POWER_OVERWHELMING_GET_ADL_FUNC(ADL2_Device_PMLog_Device_Create);
    __POWER_OVERWHELMING_GET_ADL_FUNC(ADL2_Device_PMLog_Device_Destroy);
    __POWER_OVERWHELMING_GET_ADL_FUNC(ADL2_Main_Control_Create);
    __POWER_OVERWHELMING_GET_ADL_FUNC(ADL2_Main_Control_Destroy);
}
