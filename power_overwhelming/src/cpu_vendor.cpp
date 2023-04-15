// <copyright file="cpu_vendor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/cpu_vendor.h"

#include <array>
#include <cstring>
#include <stdexcept>

#if defined(_WIN32)
#include <intrin.h>
#include <Windows.h>
#else /* defined(_WIN32) */
#include <cpuid.h>
#endif /* defined(_WIN32) */


/*
 * visus::power_overwhelming::get_cpu_vendor
 */
visus::power_overwhelming::cpu_vendor visus::power_overwhelming::get_cpu_vendor(
        void) noexcept {
#define _RET_MATCH(v, r) if (::strncmp(vendor, (v), sizeof(vendor)) == 0) \
    return cpu_vendor::r

    std::array<int, 4> data;
    char vendor[0x20] = { 0 };

#if defined(_WIN32)
    // Determine the number of functions available as described on
    // https://learn.microsoft.com/de-de/cpp/intrinsics/cpuid-cpuidex?view=msvc-170
    ::__cpuid(data.data(), 0);
#else /* defined(_WIN32) */
    // Determine the number of functions available as described on
    // https://stackoverflow.com/questions/14266772/how-do-i-call-cpuid-in-linux
    data[0] = ::__get_cpuid_max(0, nullptr);
#endif /* defined(_WIN32) */

    if (data[0] > 0) {
        // If available, get the first function, which holds the name.
#if defined(_WIN32)
        ::__cpuidex(data.data(), 0, 0);
#else /* defined(_WIN32) */
        if (!::__get_cpuid(0, &data[0], &data[1], &data[2], &data[3])) {
            return cpu_vendor::unknown;
        }
#endif /* defined(_WIN32) */

        // Kansas city shuffle ...
        *reinterpret_cast<int *>(vendor) = data[1];
        *reinterpret_cast<int *>(vendor + 4) = data[3];
        *reinterpret_cast<int *>(vendor + 8) = data[2];
    }

    // Check for common vendors from https://www.sandpile.org/x86/cpuid.htm ...
    _RET_MATCH("AuthenticAMD", amd);
    _RET_MATCH("GenuineIntel", intel);

    // ... and the weird stuff.
    _RET_MATCH("CentaurHauls", centaur);
    _RET_MATCH("CyrixInstead", cyrix);
    _RET_MATCH("HygonGenuine", hygon);
    _RET_MATCH("Geode by NSC", national_semiconductor);
    _RET_MATCH("NexGenDriven", nexgen);
    _RET_MATCH("RiseRiseRise", rise);
    _RET_MATCH("SiS SiS SiS ", sis);
    _RET_MATCH("GenuineTMx86", transmeta);
    _RET_MATCH("UMC UMC UMC ", umc);

    return cpu_vendor::unknown;
#undef _RET_MATCH
}
