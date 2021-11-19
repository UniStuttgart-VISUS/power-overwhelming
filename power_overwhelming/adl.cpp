// <copyright file="adl.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "adl.h"

#include <system_error>

#include <tchar.h>


#define __POWER_OVERWHELMING_GET_ADL_FUNC(n) this->n \
    = reinterpret_cast<decltype(this->n)>(::GetProcAddress(this->_handle, #n))


/*
 * visus::power_overwhelming::adl::instance
 */
const visus::power_overwhelming::adl&
visus::power_overwhelming::adl::instance(void) {
    static const adl retval;
    return retval;
}


/*
 * visus::power_overwhelming::adl::~adl
 */
visus::power_overwhelming::adl::~adl(void) {
    if (this->_handle != NULL) {
        ::FreeLibrary(this->_handle);
    }
}


/*
 * visus::power_overwhelming::adl::adl
 */
visus::power_overwhelming::adl::adl(void) : _handle(NULL) {
    this->_handle = ::LoadLibrary(_T("atiadlxx.dll"));
    if (this->_handle == NULL) {
        // A 32-bit application on 64 bit will fail to load the DLL, so try
        // loading the 32-bit variant next.
        this->_handle = LoadLibrary(TEXT("atiadlxy.dll"));
    }

    if (this->_handle == NULL) {
        // This is probably a machine without AMD GPU.
        throw std::system_error(ERROR_NOT_FOUND, std::system_category(), "The "
            "AMD Display Library could not be loaded. Make sure to use this "
            "function only on machines with AMD cards and appropriate AMD "
            "drivers installed.");
    }

    // Get all the function pointers we need.
    __POWER_OVERWHELMING_GET_ADL_FUNC(ADL2_Adapter_Active_Get);
    __POWER_OVERWHELMING_GET_ADL_FUNC(ADL_Adapter_AdapterInfo_Get);
    __POWER_OVERWHELMING_GET_ADL_FUNC(ADL_Adapter_NumberOfAdapters_Get);
    __POWER_OVERWHELMING_GET_ADL_FUNC(ADL2_Adapter_PMLog_Support_Get);
    __POWER_OVERWHELMING_GET_ADL_FUNC(ADL2_Adapter_PMLog_Support_Start);
    __POWER_OVERWHELMING_GET_ADL_FUNC(ADL2_Adapter_PMLog_Support_Stop);
    __POWER_OVERWHELMING_GET_ADL_FUNC(ADL2_Device_PMLog_Device_Create);
    __POWER_OVERWHELMING_GET_ADL_FUNC(ADL2_Device_PMLog_Device_Destroy);
    __POWER_OVERWHELMING_GET_ADL_FUNC(ADL_Main_Control_Create);
    __POWER_OVERWHELMING_GET_ADL_FUNC(ADL_Main_Control_Destroy);
}
