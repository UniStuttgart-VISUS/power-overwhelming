// <copyright file="msr_magic_config.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "msr_magic.h"

#include "visus/pwrowg/cpu_affinity.h"
#include "visus/pwrowg/cpu_info.h"


/*
 * PWROWG_DETAIL_NAMESPACE::is_rapl_energy_supported
 */
bool PWROWG_DETAIL_NAMESPACE::is_rapl_energy_supported(
        _In_ const msr_sensor::core_type core,
        _In_ const rapl_domain domain) {
    // Force the calling thread to the specified core for the stuff to come such
    // that we are sure that we get the CPU info from the right CPU.
    thread_affinity_scope affinity(core);

    PWROWG_NAMESPACE::cpu_info cpu_info[2];
    if (get_cpu_info(cpu_info, 2) < 2) {
        return false;
    }

    const auto model = extract_cpu_model(cpu_info);

    switch (extract_cpu_vendor(cpu_info[0])) {
        case cpu_vendor::amd:
        case cpu_vendor::hygon: {
            // AMD family is sum of base and extended according to
            // https://en.wikichip.org/wiki/amd/cpuid.
            // From https://github.com/deater/uarch-configure/blob/bc635a5e55e01f5248857ac4af48f91a2519cb31/rapl-read/rapl-read.c#L284
            // and https://github.com/amd/amd_energy/blob/c4263c9dc1aa13b89f20078ddaa30a96302a4c88/amd_energy.c#L275-L277
            // we conclude that all Zen (17h) CPUs and above should support RAPL
            // MSRs for the package and PP0.
            // Hygon is treated as AMD in
            // https://github.com/torvalds/linux/blob/6a8f57ae2eb07ab39a6f0ccad60c760743051026/drivers/powercap/intel_rapl_msr.c#L160-L161
            const auto fam = model.base_family + model.extended_family;
            if (fam >= 0x17) {
                switch (domain) {
                    case rapl_domain::package:
                    case rapl_domain::pp0:
                        return true;
                }
            }
            } break;

        case cpu_vendor::intel:
            // Use list of supported CPUs from
            // https://github.com/torvalds/linux/blob/6a8f57ae2eb07ab39a6f0ccad60c760743051026/drivers/powercap/intel_rapl_msr.c#L139-L147
            // See also https://en.wikichip.org/wiki/intel/cpuid and
            // https://github.com/torvalds/linux/blob/master/arch/x86/include/asm/intel-family.h
            // Note: We are only interested in the energy status, which is
            // supported for all domains on Intel, so we do not make any
            // additional checks.
            if (model.base_family == 0x6) {
                const auto mod = model.extended_model << 4 | model.base_model;
                switch (mod) {
                    case 0x8C:  // Tiger Lake L
                    case 0x97:  // Alder Lake
                    case 0x9A:  // Alder Lake L
                    case 0xBE:  // Alder Lake N
                    case 0xB7:  // Raptor Lake
                    case 0xBA:  // Raptor Lake P
                    case 0xAC:  // Meteor Lake
                    case 0xAA:  // Meteor Lake L
                        return true;
                }
            }
            break;
    }
    // If we reached this point, RAPL MSRs are not supported on the core.

    return false;
}


/*
 * PWROWG_DETAIL_NAMESPACE::make_energy_magic_config
 */
PWROWG_DETAIL_NAMESPACE::msr_magic_config_entry
PWROWG_DETAIL_NAMESPACE::make_energy_magic_config(
        _In_ const cpu_vendor vendor,
        _In_ const rapl_domain domain,
        _In_ const std::streamoff data_location,
        _In_ const std::function<bool(const msr_sensor::core_type)>& check) {
    static const decltype(msr_magic_config::is_supported) nope
        = [](const msr_sensor::core_type) { return false; };

    msr_magic_config config;
    config.data_location = data_location;
    config.is_supported = static_cast<bool>(check)
        ? check
        : std::bind(is_rapl_energy_supported, std::placeholders::_1, domain);

    switch (vendor) {
        case cpu_vendor::amd:
            config.unit_location = msr_offsets::amd::unit_divisors;
            config.unit_mask = msr_units::amd::energy_mask;
            config.unit_offset = msr_units::amd::energy_offset;
            break;

        case cpu_vendor::intel:
            config.unit_location = msr_offsets::intel::unit_divisors;
            config.unit_mask = msr_units::intel::energy_mask;
            config.unit_offset = msr_units::intel::energy_offset;

        default:
            config.is_supported = nope;
            break;
    }

    return std::make_pair(domain, config);
}
