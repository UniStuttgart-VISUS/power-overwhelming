// <copyright file="amd_display_library.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <memory>
#include <utility>

#include <adl_defines.h>
#include <adl_sdk.h>

#include "library_base.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

#define __POWER_OVERWHELMING_ADL_FUNC(r, n, ...) \
    r (*n)(__VA_ARGS__) = nullptr

    /// <summary>
    /// Wrapper for dynamically loading the AMD Display Library.
    /// </summary>
    class amd_display_library final : public library_base {

    public:

        /// <summary>
        /// Gets the only instance of the class.
        /// </summary>
        /// <param name=""></param>
        /// <returns></returns>
        /// <exception cref="std::system_error">If the library could not
        /// be loaded, eg because the machine does not have an AMD GPU.
        /// </exception>
        static const amd_display_library& instance(void);

        __POWER_OVERWHELMING_ADL_FUNC(int, ADL2_Adapter_Active_Get,
            ADL_CONTEXT_HANDLE, int, int *);
        __POWER_OVERWHELMING_ADL_FUNC(int, ADL2_Adapter_AdapterInfo_Get,
            ADL_CONTEXT_HANDLE, LPAdapterInfo, int);
        __POWER_OVERWHELMING_ADL_FUNC(int,
            ADL2_Adapter_NumberOfAdapters_Get, ADL_CONTEXT_HANDLE, int *);
        __POWER_OVERWHELMING_ADL_FUNC(int, ADL2_Adapter_PMLog_SensorLimits_Get,
            ADL_CONTEXT_HANDLE, int, ADLPMLogSensorLimits *);
        __POWER_OVERWHELMING_ADL_FUNC(int, ADL2_Adapter_PMLog_Support_Get,
            ADL_CONTEXT_HANDLE, int, ADLPMLogSupportInfo *);
        __POWER_OVERWHELMING_ADL_FUNC(int, ADL2_Adapter_PMLog_Start,
            ADL_CONTEXT_HANDLE, int, ADLPMLogStartInput *,
            ADLPMLogStartOutput *, ADL_D3DKMT_HANDLE);
        __POWER_OVERWHELMING_ADL_FUNC(int, ADL2_Adapter_PMLog_Stop,
            ADL_CONTEXT_HANDLE, int, ADL_D3DKMT_HANDLE);
        __POWER_OVERWHELMING_ADL_FUNC(int, ADL2_Device_PMLog_Device_Create,
            ADL_CONTEXT_HANDLE, int, ADL_D3DKMT_HANDLE *);
        __POWER_OVERWHELMING_ADL_FUNC(int, ADL2_Device_PMLog_Device_Destroy,
            ADL_CONTEXT_HANDLE, ADL_D3DKMT_HANDLE);
        __POWER_OVERWHELMING_ADL_FUNC(int, ADL2_Main_Control_Create,
            ADL_MAIN_MALLOC_CALLBACK, int, ADL_CONTEXT_HANDLE *);
        __POWER_OVERWHELMING_ADL_FUNC(int, ADL2_Main_Control_Destroy,
            ADL_CONTEXT_HANDLE);
        __POWER_OVERWHELMING_ADL_FUNC(int, ADL2_New_QueryPMLogData_Get,
            ADL_CONTEXT_HANDLE, int, ADLPMLogDataOutput *);
        __POWER_OVERWHELMING_ADL_FUNC(int,
            ADL2_Overdrive8_PMLogSensorRange_Caps, ADL_CONTEXT_HANDLE, int,
            int *, ADLOD8SingleInitSetting **);
        __POWER_OVERWHELMING_ADL_FUNC(int,
            ADL2_Overdrive8_PMLogSensorType_Support_Get, ADL_CONTEXT_HANDLE,
            int, int *, int **);
        __POWER_OVERWHELMING_ADL_FUNC(int, ADL2_OverdriveN_CapabilitiesX2_Get,
            ADL_CONTEXT_HANDLE, int, ADLODNCapabilitiesX2 *);
        __POWER_OVERWHELMING_ADL_FUNC(int, ADL2_OverdriveN_Capabilities_Get,
            ADL_CONTEXT_HANDLE, int, ADLODNCapabilities *);
        __POWER_OVERWHELMING_ADL_FUNC(int,
            ADL2_OverdriveN_PerformanceStatus_Get, ADL_CONTEXT_HANDLE, int,
            ADLODNPerformanceStatus *);
        __POWER_OVERWHELMING_ADL_FUNC(int, ADL2_OverdriveN_PowerLimit_Get,
            ADL_CONTEXT_HANDLE, int, ADLODNPowerLimitSetting *);
        __POWER_OVERWHELMING_ADL_FUNC(int, ADL2_OverdriveN_Temperature_Get,
            ADL_CONTEXT_HANDLE, int, int, int *);
        __POWER_OVERWHELMING_ADL_FUNC(int,
            ADL2_OverdriveN_ThrottleNotification_Get, ADL_CONTEXT_HANDLE,
            int, int*, int*);
        __POWER_OVERWHELMING_ADL_FUNC(int, ADL2_Overdrive_Caps,
            ADL_CONTEXT_HANDLE, int, int *, int *, int *);

    private:

        /// <summary>
        /// Initialise a new instance.
        /// </summary>
        /// <remarks>
        /// Try the 64-bit library first, which will fail in Wow64 processes.
        /// In this case, try the 32-bit variant next.
        /// </remarks>
        amd_display_library(void);
    };

#undef __POWER_OVERWHELMING_ADL_FUNC

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
