// <copyright file="msr_magic_config.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "msr_magic.h"

#include "power_overwhelming/cpu_affinity.h"
#include "power_overwhelming/cpu_info.h"


/*
 * visus::power_overwhelming::detail::is_rapl_energy_supported
 */
bool visus::power_overwhelming::detail::is_rapl_energy_supported(
        _In_ const msr_sensor::core_type core,
        _In_ const rapl_domain domain) {
    thread_affinity_scope affinity(core);

    power_overwhelming::cpu_info cpu_info[2];
    if (get_cpu_info(cpu_info, 2) < 2) {
        return false;
    }

    const auto model = extract_cpu_model(cpu_info);

    switch (extract_cpu_vendor(cpu_info[0])) {
        case cpu_vendor::amd: {
            // AMD family is sum of base and extended according to
            // https://en.wikichip.org/wiki/amd/cpuid.
            // From https://github.com/deater/uarch-configure/blob/bc635a5e55e01f5248857ac4af48f91a2519cb31/rapl-read/rapl-read.c#L284
            // and https://github.com/amd/amd_energy/blob/c4263c9dc1aa13b89f20078ddaa30a96302a4c88/amd_energy.c#L275-L277
            // we conclude that all Zen (17h) CPUs and above should support RAPL
            // MSRs for the package and PP0.
            const auto family = model.base_family + model.extended_family;
            if (family >= 0x17) {
                switch (domain) {
                    case rapl_domain::package:
                    case rapl_domain::pp0:
                        return true;
                }
            }
            } break;

        case cpu_vendor::intel:
            break;
    }

    return false;
}


/*
 * visus::power_overwhelming::detail::make_amd_energy_magic_config
 */
visus::power_overwhelming::detail::msr_magic_config
visus::power_overwhelming::detail::make_amd_energy_magic_config(
        _In_ const std::streamoff data_location,
        _In_ std::function<bool(const msr_sensor::core_type)> is_supported) {
    msr_magic_config retval;
    retval.data_location = data_location;
    retval.is_supported = is_supported ? is_supported : nullptr;
    retval.unit_location = msr_offsets::amd::unit_divisors;
    retval.unit_mask = msr_units::amd::energy_mask;
    retval.unit_offset = msr_units::amd::energy_offset;
    return retval;
}


/*
 * visus::power_overwhelming::detail::make_intel_energy_magic_config
 */
visus::power_overwhelming::detail::msr_magic_config
visus::power_overwhelming::detail::make_intel_energy_magic_config(
        _In_ const std::streamoff data_location,
        _In_ std::function<bool(const msr_sensor::core_type)> is_supported) {
    msr_magic_config retval;
    retval.data_location = data_location;
    retval.is_supported = is_supported ? is_supported : nullptr;
    retval.unit_location = msr_offsets::intel::unit_divisors;
    retval.unit_mask = msr_units::intel::energy_mask;
    retval.unit_offset = msr_units::intel::energy_offset;
    return retval;
}
