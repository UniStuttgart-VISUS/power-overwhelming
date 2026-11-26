// <copyright file="RaplMsr.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "RaplMsr.h"

#include <intrin.h>
#include <ntddk.h>

// https://github.com/amd/amd_energy/blob/master/amd_energy.c
// https://github.com/deater/uarch-configure/blob/master/rapl-read/rapl-read.c
constexpr unsigned __int32 AMD_PACKAGE_ENERGY_STATUS = 0xC001029B;
constexpr unsigned __int32 AMD_PP0_ENERGY_STATUS = 0xC001029A;
constexpr unsigned __int32 AMD_UNIT_DIVISORS = 0xC0010299;

// https://lkml.org/lkml/2011/5/26/93
constexpr unsigned __int32 INTEL_DRAM_ENERGY_STATUS = 0x619;
constexpr unsigned __int32 INTEL_DRAM_PERFORMANCE_STATUS = 0x61B;
constexpr unsigned __int32 INTEL_DRAM_POWER_INFO = 0x61C;
constexpr unsigned __int32 INTEL_DRAM_POWER_LIMIT = 0x618;
constexpr unsigned __int32 INTEL_PACKAGE_ENERGY_STATUS = 0x611;
constexpr unsigned __int32 INTEL_PACKAGE_PERFORMANCE_STATUS = 0x613;
constexpr unsigned __int32 INTEL_PACKAGE_POWER_INFO = 0x614;
constexpr unsigned __int32 INTEL_PACKAGE_POWER_LIMIT = 0x610;
constexpr unsigned __int32 INTEL_PLATFORM_ENERGY_STATUS = 0x64D;
constexpr unsigned __int32 INTEL_PP0_ENERGY_STATUS = 0x639;
constexpr unsigned __int32 INTEL_PP0_PERFORMANCE_STATUS = 0x63B;
constexpr unsigned __int32 INTEL_PP0_POWER_LIMIT = 0x638;
constexpr unsigned __int32 INTEL_PP0_POLICY = 0x63A;
constexpr unsigned __int32 INTEL_PP1_ENERGY_STATUS = 0x641;
constexpr unsigned __int32 INTEL_PP1_POLICY = 0x642;
constexpr unsigned __int32 INTEL_PP1_POWER_LIMIT = 0x640;
constexpr unsigned __int32 INTEL_UNIT_DIVISORS = 0x606;


/// <summary>
/// Helper that performs the CheckMsr call, appends <paramref name="reg" /> to
/// <paramref name="dst" /> if <paramref name="offset" /> is a valid offset.
/// As a side effect, <paramref name="offset" /> is incremented if the register
/// is supported. If <paramref name="dst" /> is <see langword="nullptr" />, the
/// function only counts the number of potential registers without checking
/// them.
/// </summary>
static inline void GetSupportedMsr(
        _Out_writes_opt_(cnt) unsigned __int32 *dst,
        _In_ const SIZE_T cnt,
        _In_ const unsigned __int32 reg,
        _Inout_ SIZE_T& offset) noexcept {
    if (dst == nullptr) {
        ++offset;

    } else {
        __try {
            volatile auto data = __readmsr(reg);

            if (offset < cnt) {
                dst[offset] = reg;
            }
            ++offset;

        } __except (EXCEPTION_EXECUTE_HANDLER) {
            KdPrint(("[PWROWG] Reading MSR 0x%x failed\r\n", reg));
        }
    }
}


/// <summary>
/// Gets the RAPL MSRs that are supported for the given AMD CPU.
/// </summary>
static SIZE_T GetSupportedAmdRegisters(_In_ const RaplCpuInfo& cpuInfo,
        _Out_writes_opt_(cnt) unsigned __int32 *dst,
        _In_ const SIZE_T cnt) noexcept {
    ASSERT(cpuInfo.Vendor == RaplCpuVendor::Amd);
    SIZE_T retval = 0;

    ::GetSupportedMsr(dst, cnt, AMD_PACKAGE_ENERGY_STATUS, retval);
    ::GetSupportedMsr(dst, cnt, AMD_PP0_ENERGY_STATUS, retval);
    ::GetSupportedMsr(dst, cnt, AMD_UNIT_DIVISORS, retval);

    return retval;
}


/// <summary>
/// Gets the RAPL MSRs that are supported for the given Intel CPU.
/// </summary>
static SIZE_T GetSupportedIntelRegisters(_In_ const RaplCpuInfo& cpuInfo,
        _Out_writes_opt_(cnt) unsigned __int32 *dst,
        _In_ const SIZE_T cnt) noexcept {
    ASSERT(cpuInfo.Vendor == RaplCpuVendor::Intel);
    SIZE_T retval = 0;

    ::GetSupportedMsr(dst, cnt, INTEL_DRAM_ENERGY_STATUS, retval);
    ::GetSupportedMsr(dst, cnt, INTEL_DRAM_PERFORMANCE_STATUS, retval);
    ::GetSupportedMsr(dst, cnt, INTEL_DRAM_POWER_INFO, retval);
    ::GetSupportedMsr(dst, cnt, INTEL_DRAM_POWER_LIMIT, retval);
    ::GetSupportedMsr(dst, cnt, INTEL_PACKAGE_ENERGY_STATUS, retval);
    ::GetSupportedMsr(dst, cnt, INTEL_PACKAGE_PERFORMANCE_STATUS, retval);
    ::GetSupportedMsr(dst, cnt, INTEL_PACKAGE_POWER_INFO, retval);
    ::GetSupportedMsr(dst, cnt, INTEL_PACKAGE_POWER_LIMIT, retval);
    ::GetSupportedMsr(dst, cnt, INTEL_PLATFORM_ENERGY_STATUS, retval);
    ::GetSupportedMsr(dst, cnt, INTEL_PP0_ENERGY_STATUS, retval);
    ::GetSupportedMsr(dst, cnt, INTEL_PP0_PERFORMANCE_STATUS, retval);
    ::GetSupportedMsr(dst, cnt, INTEL_PP0_POWER_LIMIT, retval);
    ::GetSupportedMsr(dst, cnt, INTEL_PP0_POLICY, retval);
    ::GetSupportedMsr(dst, cnt, INTEL_PP1_ENERGY_STATUS, retval);
    ::GetSupportedMsr(dst, cnt, INTEL_PP1_POLICY, retval);
    ::GetSupportedMsr(dst, cnt, INTEL_PP1_POWER_LIMIT, retval);
    ::GetSupportedMsr(dst, cnt, INTEL_UNIT_DIVISORS, retval);

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
