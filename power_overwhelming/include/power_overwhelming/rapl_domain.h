// <copyright file="rapl_domain.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <ios>

#include "power_overwhelming/power_overwhelming_api.h"


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// 
    /// </summary>
    enum class rapl_domain : std::streamoff {
        amd_package_energy_status = 0xc001029b,
        amd_pp0_energy_status = 0xc001029a,
        dram_energy_status = 0x619,
        dram_performance_status = 0x61b,
        dram_power_info = 0x61c,
        dram_power_limit = 0x618,
        intel_package_energy_status = 0x611,
        intel_pp0_energy_status = 0x639,
        package_performance_status = 0x613,
        package_power_info = 0x614,
        package_power_limit = 0x610,
        platform_energy_status = 0x64d,
        pp0_performance_status = 0x63b,
        pp0_power_limit = 0x638,
        pp0_policy = 0x63A,
        pp1_energy_status = 0x641,
        pp1_policy = 0x642,
        pp1_power_limit = 0x640
    };

    /// <summary>
    /// Convert the given RAPL domain to a human-readable string representation.
    /// </summary>
    /// <param name="domain">The RAPL domain to be converter.</param>
    /// <returns>The name of the domain.</returns>
    extern POWER_OVERWHELMING_API _Ret_z_ const wchar_t *to_string(
        _In_ const rapl_domain domain);

} /* namespace power_overwhelming */
} /* namespace visus */
