// <copyright file="cpu_info.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/cpu_info.h"

#include <array>
#include <cstring>
#include <stdexcept>
#include <system_error>

#if defined(_WIN32)
#include <intrin.h>
#include <Windows.h>
#else /* defined(_WIN32) */
#include <cpuid.h>
#include <errno.h>
#endif /* defined(_WIN32) */

#include "zero_memory.h"


/*
 * PWROWG_NAMESPACE::extract_cpu_model
 */
PWROWG_NAMESPACE::cpu_model
PWROWG_NAMESPACE::extract_cpu_model(
        _In_reads_(2) const cpu_info info[2]) noexcept {
    // https://www.amd.com/system/files/TechDocs/25481.pdf
    // https://en.wikichip.org/wiki/amd/cpuid
    // https://www.intel.com/content/www/us/en/architecture-and-technology/64-ia-32-architectures-software-developer-vol-2a-manual.html
    cpu_model retval;

    retval.stepping = (info[1].registers.eax & 0x0000000F) >> 0;
    retval.base_model = (info[1].registers.eax & 0x000000F0) >> 4;
    retval.base_family = (info[1].registers.eax & 0x00000F00) >> 8;
    retval.extended_model = (info[1].registers.eax & 0x0000F0000) >> 16;
    retval.extended_family = (info[1].registers.eax & 0x00FF00000) >> 20;

    return retval;
}


/*
 * PWROWG_NAMESPACE::extract_cpu_vendor
 */
void PWROWG_NAMESPACE::extract_cpu_vendor(
        _Out_writes_(0x20) char dst[20],
        _In_ const cpu_info& info) {
    if (dst == nullptr) {
        throw std::invalid_argument("A valid output buffer must be provided.");
    }

    // Kansas city shuffle ...
    ::ZeroMemory(dst, 20);
    *reinterpret_cast<int *>(dst) = info.values[1];
    *reinterpret_cast<int *>(dst + 4) = info.values[3];
    *reinterpret_cast<int *>(dst + 8) = info.values[2];
}


/*
 * PWROWG_NAMESPACE::extract_cpu_vendor
 */
PWROWG_NAMESPACE::cpu_vendor
PWROWG_NAMESPACE::extract_cpu_vendor(_In_ const cpu_info& info) noexcept {
#define _RET_MATCH(v, r) if (::strncmp(vendor, (v), sizeof(vendor)) == 0) \
    return cpu_vendor::r

    // Kansas city shuffle ...
    char vendor[0x20];
    extract_cpu_vendor(vendor, info);

    // Check for common vendors from https://en.wikipedia.org/wiki/CPUID ...
    _RET_MATCH("AuthenticAMD", amd);
    _RET_MATCH("GenuineIntel", intel);

    // ... and the weird stuff.
    _RET_MATCH("AMDisbetter!", amd);
    _RET_MATCH("MiSTer AO486", ao486);
    _RET_MATCH("bhyve bhyve ", bhyve);
    _RET_MATCH("CentaurHauls", centaur);
    _RET_MATCH("CyrixInstead", cyrix);
    _RET_MATCH("Vortex86 SoC", dmp);
    _RET_MATCH("E2K MACHINE", elbrus);
    _RET_MATCH("HygonGenuine", hygon);
    _RET_MATCH("Microsoft Hv", hyperv);
    _RET_MATCH(" KVMKVMKVM  ", kvm);
    _RET_MATCH("MicrosoftXTA", microsoft_xta);
    _RET_MATCH("Geode by NSC", national_semiconductor);
    _RET_MATCH("NexGenDriven", nexgen);
    _RET_MATCH(" lrpepyh  vr", parallels);
    _RET_MATCH("ACRNACRNACRN", project_acrn);
    _RET_MATCH("TCGTCGTCGTCG", qemu);
    _RET_MATCH(" QNXQVMBSQG ", qnx);
    _RET_MATCH("Genuine  RDC", rdc);
    _RET_MATCH("RiseRiseRise", rise);
    _RET_MATCH("VirtualApple", rosetta2);
    _RET_MATCH("SiS SiS SiS ", sis);
    _RET_MATCH("TransmetaCPU", transmeta);
    _RET_MATCH("GenuineTMx86", transmeta);
    _RET_MATCH("UMC UMC UMC ", umc);
    _RET_MATCH("VIA VIA VIA ", via);
    _RET_MATCH("VMwareVMware", vmware);
    _RET_MATCH("XenVMMXenVMM", xen);
    _RET_MATCH("  Shanghai  ", zhaoxin);

    return cpu_vendor::unknown;
#undef _RET_MATCH
}

/*
 * PWROWG_NAMESPACE::get_cpu_info
 */
std::uint32_t PWROWG_NAMESPACE::get_cpu_info(
        _Out_writes_opt_(cnt) cpu_info *infos,
        _In_ std::uint32_t cnt) {
    cpu_info info;

#if defined(_WIN32)
    // Determine the number of functions available as described on
    // https://learn.microsoft.com/de-de/cpp/intrinsics/cpuid-cpuidex?view=msvc-170
    ::__cpuid(info.values, 0);
#else /* defined(_WIN32) */
    // Determine the number of functions available as described on
    // https://stackoverflow.com/questions/14266772/how-do-i-call-cpuid-in-linux
    info.registers.eax = ::__get_cpuid_max(0, nullptr);
#endif /* defined(_WIN32) */

    // EAX now holds the number of queries we can make.
    const auto retval = static_cast<std::uint32_t>(info.registers.eax);

    // Make all queries that are available and for which we have storage.
    for (std::uint32_t i = 0; (i < (std::min)(cnt, retval))
            && (infos != nullptr); ++i) {
#if defined(_WIN32)
        ::__cpuidex(reinterpret_cast<int *>(infos[i].values), i, 0);
#else /* defined(_WIN32) */
        if (!::__get_cpuid(i, &infos[i].registers.eax, &infos[i].registers.ebx,
                &infos[i].registers.ecx, &infos[i].registers.edx)) {
            throw std::system_error(EFAULT, std::system_category());
        }
#endif /* defined(_WIN32) */
    }

    return retval;
}


/*
 * PWROWG_NAMESPACE::get_cpu_vendor
 */
PWROWG_NAMESPACE::cpu_vendor PWROWG_NAMESPACE::get_cpu_vendor(
        void) noexcept {
    cpu_info info;
    if (get_cpu_info(&info, 1) > 0) {
        return extract_cpu_vendor(info);
    } else {
        return cpu_vendor::unknown;
    }
}


/*
 * PWROWG_NAMESPACE::to_string
 */
_Ret_z_ const wchar_t *PWROWG_NAMESPACE::to_string(
        _In_ const cpu_vendor vendor) noexcept {
#define _TO_STRING_CASE(v, s) case cpu_vendor::v: return s

    switch (vendor) {
        // The normal stuff.
        _TO_STRING_CASE(amd, L"AMD");
        _TO_STRING_CASE(intel, L"Intel");

        // The weird stuff.
        _TO_STRING_CASE(ao486, L"MiSTer");
        _TO_STRING_CASE(bhyve, L"bhyve");
        _TO_STRING_CASE(centaur, L"Centaur");
        _TO_STRING_CASE(cyrix, L"Cyrix");
        _TO_STRING_CASE(dmp, L" DM&P ");
        _TO_STRING_CASE(elbrus, L"MCST");
        _TO_STRING_CASE(hygon, L"Hygon");
        _TO_STRING_CASE(hyperv, L"Microsoft");
        _TO_STRING_CASE(kvm, L"KVM");
        _TO_STRING_CASE(microsoft_xta, L"Microsoft");
        _TO_STRING_CASE(national_semiconductor, L"National Semiconductor");
        _TO_STRING_CASE(nexgen, L"NexGen");
        _TO_STRING_CASE(parallels, L"Parallels");
        _TO_STRING_CASE(project_acrn, L"Project ACRN");
        _TO_STRING_CASE(qemu, L"QEMU");
        _TO_STRING_CASE(qnx, L"QNX");
        _TO_STRING_CASE(rdc, L"RDC Semiconductor");
        _TO_STRING_CASE(rise, L"Rise Technology");
        _TO_STRING_CASE(rosetta2, L"Apple");
        _TO_STRING_CASE(sis, L"SiS");
        _TO_STRING_CASE(transmeta, L"Transmeta");
        _TO_STRING_CASE(umc, L"UMC");
        _TO_STRING_CASE(via, L"VIA");
        _TO_STRING_CASE(vmware, L"VMware");
        _TO_STRING_CASE(xen, L"Xen");
        _TO_STRING_CASE(zhaoxin, L"Zhaoxin");

        default: return L"Unknown";
    }
}

