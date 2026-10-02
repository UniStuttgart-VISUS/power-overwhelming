// <copyright file="msr_magic_config.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "msr_magic.h"

#include "visus/pwrowg/cpu_affinity.h"
#include "visus/pwrowg/cpu_info.h"


/*
 * PWROWG_DETAIL_NAMESPACE::make_energy_magic_config
 */
PWROWG_DETAIL_NAMESPACE::msr_magic_config_entry
PWROWG_DETAIL_NAMESPACE::make_energy_magic_config(
        _In_ const cpu_vendor vendor,
        _In_ const rapl_domain domain,
        _In_ const std::streamoff data_location,
        _In_ const sensor_type type) {
    msr_magic_config config;
    config.data_location = data_location;
    config.type = sensor_type::software | type;

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
            break;

        default:
            throw std::invalid_argument("The specified CPU vendor does not "
                "support RAPL MSRs.");
    }

    return std::make_pair(domain, config);
}


/*
 * PWROWG_DETAIL_NAMESPACE::make_throttling_magic_config
 */
PWROWG_DETAIL_NAMESPACE::msr_magic_config_entry
PWROWG_DETAIL_NAMESPACE::make_throttling_magic_config(
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
        : std::bind(is_rapl_energy_supported, std::placeholders::_1, domain); // TODO: Probably should be a different check for throttling support.

    switch (vendor) {

    case cpu_vendor::intel:
        config.unit_location = msr_offsets::intel::unit_divisors;
        config.unit_mask = msr_units::intel::time_mask;
        config.unit_offset = msr_units::intel::time_offset;
        break;

    default:
        config.is_supported = nope;
        break;
    }

    return std::make_pair(domain, config);
}
