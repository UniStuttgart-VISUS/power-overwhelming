// <copyright file="cpu_info.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/cpu_info.h"

#include <array>
#include <cstring>
#include <stdexcept>
#include <system_error>

#if defined(_WIN32)
#include <intrin.h>
#include <Windows.h>
#else /* defined(_WIN32) */
#include <cpuid.h>
#endif /* defined(_WIN32) */


/*
 * visus::power_overwhelming::get_cpu_info
 */
std::uint32_t visus::power_overwhelming::get_cpu_info(
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
            throw std::system_error(EFAIL, std::system_category());
        }
#endif /* defined(_WIN32) */
    }

    return retval;
}


/*
 * visus::power_overwhelming::get_cpu_vendor
 */
visus::power_overwhelming::cpu_vendor visus::power_overwhelming::get_cpu_vendor(
        void) noexcept {
#define _RET_MATCH(v, r) if (::strncmp(vendor, (v), sizeof(vendor)) == 0) \
    return cpu_vendor::r

    cpu_info info;
    char vendor[0x20] = { 0 };

    if (get_cpu_info(&info, 1) > 0) {
        // Kansas city shuffle ...
        *reinterpret_cast<int *>(vendor) = info.values[1];
        *reinterpret_cast<int *>(vendor + 4) = info.values[3];
        *reinterpret_cast<int *>(vendor + 8) = info.values[2];
    }

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
