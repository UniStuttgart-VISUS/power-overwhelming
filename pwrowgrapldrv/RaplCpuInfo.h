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
