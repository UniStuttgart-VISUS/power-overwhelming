// <copyright file="RaplMsr.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
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
    // https://en.wikichip.org/wiki/amd/cpuid
    const auto family = cpuInfo.BaseFamily + cpuInfo.ExtendedFamily;
    const auto model = cpuInfo.ExtendedModel << 4 | cpuInfo.BaseModel;
    SIZE_T retval = 0;

#define _WRT_DST(r) if ((dst != nullptr) && (retval < cnt)) \
    { dst[retval] = (r); } ++retval
    // https://github.com/amd/amd_energy/blob/c4263c9dc1aa13b89f20078ddaa30a96302a4c88/amd_energy.c#L275-L277
    if ((family == 0x17) && (model == 0x31)) {
        // Zen 2 (Rome)
        _WRT_DST(AMD_PACKAGE_ENERGY_STATUS);
        _WRT_DST(AMD_PP0_ENERGY_STATUS);
        _WRT_DST(AMD_UNIT_DIVISORS);

    } else if (family >= 0x19) {
        // Zen 3+ (Milan and successors)
        _WRT_DST(AMD_PACKAGE_ENERGY_STATUS);
        _WRT_DST(AMD_PP0_ENERGY_STATUS);
        _WRT_DST(AMD_UNIT_DIVISORS);

    }
#undef _WRT_DST

    return retval;
}


/// <summary>
/// Gets the RAPL MSRs that are supported for the given Intel CPU.
/// </summary>
static SIZE_T GetSupportedIntelRegisters(_In_ const RaplCpuInfo& cpuInfo,
        _Out_writes_opt_(cnt) unsigned __int32 *dst,
        _In_ const SIZE_T cnt) {
    ASSERT(cpuInfo.Vendor == RaplCpuVendor::Intel);
    const auto model = cpuInfo.ExtendedModel << 4 | cpuInfo.BaseModel;
    SIZE_T retval = 0;

#define _WRT_DST(r) if ((dst != nullptr) && (retval < cnt)) \
    { dst[retval] = (r); } ++retval
    https://github.com/torvalds/linux/blob/6a8f57ae2eb07ab39a6f0ccad60c760743051026/drivers/powercap/intel_rapl_msr.c#L139-L147
    if (cpuInfo.BaseFamily == 0x6) {
        switch (model) {
            case 0x8C:  // Tiger Lake L
            case 0x97:  // Alder Lake
            case 0x9A:  // Alder Lake L
            case 0xBE:  // Alder Lake N
            case 0xB7:  // Raptor Lake
            case 0xBA:  // Raptor Lake P
            case 0xAC:  // Meteor Lake
            case 0xAA:  // Meteor Lake L
                _WRT_DST(INTEL_DRAM_ENERGY_STATUS);
                _WRT_DST(INTEL_DRAM_PERFORMANCE_STATUS);
                _WRT_DST(INTEL_DRAM_POWER_INFO);
                _WRT_DST(INTEL_DRAM_POWER_LIMIT);
                _WRT_DST(INTEL_PACKAGE_ENERGY_STATUS);
                _WRT_DST(INTEL_PACKAGE_PERFORMANCE_STATUS);
                _WRT_DST(INTEL_PACKAGE_POWER_INFO);
                _WRT_DST(INTEL_PACKAGE_POWER_LIMIT);
                _WRT_DST(INTEL_PLATFORM_ENERGY_STATUS);
                _WRT_DST(INTEL_PP0_ENERGY_STATUS);
                _WRT_DST(INTEL_PP0_PERFORMANCE_STATUS);
                _WRT_DST(INTEL_PP0_POWER_LIMIT);
                _WRT_DST(INTEL_PP0_POLICY);
                _WRT_DST(INTEL_PP1_ENERGY_STATUS);
                _WRT_DST(INTEL_PP1_POLICY);
                _WRT_DST(INTEL_PP1_POWER_LIMIT);
                _WRT_DST(INTEL_UNIT_DIVISORS);
                break;
        }
    }
#undef _WRT_DST

    return retval;
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
        // TODO: Could sort the list here and do binary search below.
    }

    return retval;
}


/*
 * RaplIsRegisterSupported
 */
bool RaplIsRegisterSupported(_In_ const unsigned __int32 reg,
        _In_reads_(cnt) const unsigned __int32 *regs,
        _In_ const SIZE_T cnt) {
    if (regs == nullptr) {
        // A nullptr here signals that we should not test.
        return true;
    }

    for (SIZE_T i = 0; i < cnt; ++i) {
        if (reg == regs[i]) {
            return true;
        }
    }

    return false;
}
