// <copyright file="rapl_domain.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/rapl_domain.h"


/*
 * visus::power_overwhelming::to_string
 */
_Ret_z_ const wchar_t *visus::power_overwhelming::to_string(
        const rapl_domain domain) {
#define _GCC_IS_SHIT(v) L##v
#define _TO_STRING_CASE(v) case rapl_domain::v: return _GCC_IS_SHIT(#v)

    switch (domain) {
        _TO_STRING_CASE(amd_package_energy_status);
        _TO_STRING_CASE(amd_pp0_energy_status);
        _TO_STRING_CASE(dram_energy_status);
        _TO_STRING_CASE(dram_performance_status);
        _TO_STRING_CASE(dram_power_info);
        _TO_STRING_CASE(dram_power_limit);
        _TO_STRING_CASE(intel_package_energy_status);
        _TO_STRING_CASE(intel_pp0_energy_status);
        _TO_STRING_CASE(package_performance_status);
        _TO_STRING_CASE(package_power_info);
        _TO_STRING_CASE(package_power_limit);
        _TO_STRING_CASE(platform_energy_status);
        _TO_STRING_CASE(pp0_performance_status);
        _TO_STRING_CASE(pp0_power_limit);
        _TO_STRING_CASE(pp0_policy);
        _TO_STRING_CASE(pp1_energy_status);
        _TO_STRING_CASE(pp1_policy);
        _TO_STRING_CASE(pp1_power_limit);

        default:
            throw std::invalid_argument("The specified RAPL domain is "
                "unknown. Make sure to add all new sources in to_string.");
    }

#undef _GCC_IS_SHIT
#undef _TO_STRING_CASE
}
