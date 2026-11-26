// <copyright file="RaplCpuInfo.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <ntddk.h>


/// <summary>
/// Possible CPU vendors.
/// </summary>
/// <remarks>
/// At this point, we are only interested whether the CPU is AMD, Intel or any
/// other, because others do not support RAPL MSRs.
/// </remarks>
enum class RaplCpuVendor {
    Amd,
    Intel,
    Other
};


/// <summary>
/// A structure holding all necessary information about the CPU we are running
/// on.
/// </summary>
struct RaplCpuInfo {
    __int8 BaseFamily;
    __int8 ExtendedFamily;
    __int8 BaseModel;
    __int8 ExtendedModel;
    __int8 Stepping;
    RaplCpuVendor Vendor;
};


/// <summary>
/// Structure holding the DisplayFamily and DisplayModel of the CPU,
/// which is used to identify the CPU model in a human-readable way.
/// </summary>
struct RaplDisplayFamilyModel {
    unsigned __int32 DisplayFamily;
    unsigned __int32 DisplayModel;
    RaplDisplayFamilyModel(void) : DisplayFamily(0), DisplayModel(0) {}
    RaplDisplayFamilyModel(_In_ const RaplCpuInfo& cpuInfo) {
        if (cpuInfo.BaseFamily != 0xF) {
            this->DisplayFamily = cpuInfo.BaseFamily;
        } else {
            this->DisplayFamily = cpuInfo.ExtendedFamily + cpuInfo.BaseFamily;
        }
        if ((cpuInfo.BaseFamily == 0x6) || (cpuInfo.BaseFamily == 0xF)) {
            this->DisplayModel = (cpuInfo.ExtendedModel << 4) + cpuInfo.BaseModel;
        } else {
            this->DisplayModel = cpuInfo.BaseModel;
        }
    }
};
