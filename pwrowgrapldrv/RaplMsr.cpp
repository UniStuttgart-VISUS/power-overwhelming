// <copyright file="RaplMsr.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "RaplMsr.h"

#include <ntddk.h>


// https://github.com/amd/amd_energy/blob/master/amd_energy.c
// https://github.com/deater/uarch-configure/blob/master/rapl-read/rapl-read.c
constexpr const unsigned __int32 AMD_PACKAGE_ENERGY_STATUS = 0xC001029B;
constexpr const unsigned __int32 AMD_PP0_ENERGY_STATUS = 0xC001029A;
constexpr const unsigned __int32 AMD_UNIT_DIVISORS = 0xC0010299;

// https://lkml.org/lkml/2011/5/26/93
constexpr const unsigned __int32 INTEL_DRAM_ENERGY_STATUS = 0x619;
constexpr const unsigned __int32 INTEL_DRAM_PERFORMANCE_STATUS = 0x61B;
constexpr const unsigned __int32 INTEL_DRAM_POWER_INFO = 0x61C;
constexpr const unsigned __int32 INTEL_DRAM_POWER_LIMIT = 0x618;
constexpr const unsigned __int32 INTEL_PACKAGE_ENERGY_STATUS = 0x611;
constexpr const unsigned __int32 INTEL_PACKAGE_PERFORMANCE_STATUS = 0x613;
constexpr const unsigned __int32 INTEL_PACKAGE_POWER_INFO = 0x614;
constexpr const unsigned __int32 INTEL_PACKAGE_POWER_LIMIT = 0x610;
constexpr const unsigned __int32 INTEL_PLATFORM_ENERGY_STATUS = 0x64D;
constexpr const unsigned __int32 INTEL_PP0_ENERGY_STATUS = 0x639;
constexpr const unsigned __int32 INTEL_PP0_PERFORMANCE_STATUS = 0x63B;
constexpr const unsigned __int32 INTEL_PP0_POWER_LIMIT = 0x638;
constexpr const unsigned __int32 INTEL_PP0_POLICY = 0x63A;
constexpr const unsigned __int32 INTEL_PP1_ENERGY_STATUS = 0x641;
constexpr const unsigned __int32 INTEL_PP1_POLICY = 0x642;
constexpr const unsigned __int32 INTEL_PP1_POWER_LIMIT = 0x640;
constexpr const unsigned __int32 INTEL_UNIT_DIVISORS = 0x606;


/// <summary>
/// Gets the RAPL MSRs that are supported for the given AMD CPU.
/// </summary>
static SIZE_T GetSupportedAmdRegisters(_In_ const RaplCpuInfo& cpuInfo,
        _Out_writes_opt_(cnt) unsigned __int32 *dst,
        _In_ const SIZE_T cnt) {
    ASSERT(cpuInfo.Vendor == RaplCpuVendor::Amd);
    // TODO
    return 0;
}


/// <summary>
/// Gets the RAPL MSRs that are supported for the given Intel CPU.
/// </summary>
static SIZE_T GetSupportedIntelRegisters(_In_ const RaplCpuInfo& cpuInfo,
            _Out_writes_opt_(cnt) unsigned __int32 *dst,
    _In_ const SIZE_T cnt) {
    ASSERT(cpuInfo.Vendor == RaplCpuVendor::Intel);
    // TODO
    return 0;
}


/*
 * ::RaplGetSupportedRegisters
 */
SIZE_T RaplGetSupportedRegisters(_In_ const RaplCpuInfo& cpuInfo,
        _Out_writes_opt_(cnt) unsigned __int32 *dst,
        _In_ const SIZE_T cnt) {
    SIZE_T retval = 0;

    switch (cpuInfo.Vendor) {
        case RaplCpuVendor::Amd:
            retval = ::GetSupportedAmdRegisters(cpuInfo, dst, cnt);
            break;

        case RaplCpuVendor::Intel:
            retval = ::GetSupportedIntelRegisters(cpuInfo, dst, cnt);
            break;

        default:
            return 0;
    }

    if (dst != nullptr) {
        // TODO: Could sort the list here. 
    }

    return retval;
}
