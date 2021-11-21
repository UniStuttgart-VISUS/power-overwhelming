// <copyright file="adl.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <adl_sdk.h>
#include <windows.h>


namespace visus {
namespace power_overwhelming {

#define __POWER_OVERWHELMING_DECL_ADL_FUNC(r, n, ...) \
    r (*n)(__VA_ARGS__) = nullptr

    /// <summary>
    /// Wrapper for dynamically loading the AMD Display Library.
    /// </summary>
    class adl final {

    public:

        /// <summary>
        /// Gets the only instance of the ADL wrapper.
        /// </summary>
        /// <param name=""></param>
        /// <returns></returns>
        /// <exception cref="std::system_error">If the library could not
        /// be loaded, eg because the machine does not have an AMD GPU.
        /// </exception>
        static const adl& instance(void);

        adl(const adl&) = delete;

        /// <summary>
        /// Finalises the instance.
        /// </summary>
        ~adl(void);

        __POWER_OVERWHELMING_DECL_ADL_FUNC(int, ADL2_Adapter_Active_Get,
            ADL_CONTEXT_HANDLE, int, int *);

        __POWER_OVERWHELMING_DECL_ADL_FUNC(int, ADL_Adapter_AdapterInfo_Get,
            LPAdapterInfo, int);

        __POWER_OVERWHELMING_DECL_ADL_FUNC(int,
            ADL_Adapter_NumberOfAdapters_Get, int *);

        __POWER_OVERWHELMING_DECL_ADL_FUNC(int, ADL2_Adapter_PMLog_Support_Get,
            ADL_CONTEXT_HANDLE, int, ADLPMLogSupportInfo *);

        __POWER_OVERWHELMING_DECL_ADL_FUNC(int, ADL2_Adapter_PMLog_Support_Start,
            ADL_CONTEXT_HANDLE context, int, ADLPMLogStartInput *,
            ADLPMLogStartOutput *, ADL_D3DKMT_HANDLE);

        __POWER_OVERWHELMING_DECL_ADL_FUNC(int, ADL2_Adapter_PMLog_Support_Stop,
            ADL_CONTEXT_HANDLE, int, ADL_D3DKMT_HANDLE);

        __POWER_OVERWHELMING_DECL_ADL_FUNC(int, ADL2_Device_PMLog_Device_Create,
            ADL_CONTEXT_HANDLE, int, ADL_D3DKMT_HANDLE *);

        __POWER_OVERWHELMING_DECL_ADL_FUNC(int, ADL2_Device_PMLog_Device_Destroy,
            ADL_CONTEXT_HANDLE, ADL_D3DKMT_HANDLE);

        __POWER_OVERWHELMING_DECL_ADL_FUNC(int, ADL_Main_Control_Create,
            ADL_MAIN_MALLOC_CALLBACK, int);

        __POWER_OVERWHELMING_DECL_ADL_FUNC(int, ADL_Main_Control_Destroy, void);

        adl& operator =(const adl&) = delete;

    private:

        adl(void);

        HINSTANCE _handle;
    };

} /* namespace power_overwhelming */
} /* namespace visus */

