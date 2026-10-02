// <copyright file="msr_magic_config.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "msr_magic.h"

#include "visus/pwrowg/cpu_affinity.h"
#include "visus/pwrowg/cpu_info.h"


/*
 * PWROWG_DETAIL_NAMESPACE::to_string
 */
_Ret_z_ const wchar_t* PWROWG_DETAIL_NAMESPACE::to_string(
    _In_ const msr_interface rapl_if) {
#define _GCC_IS_SHIT(v) L##v
#define _TO_STRING_CASE(v) case msr_interface::v: return _GCC_IS_SHIT(#v)

    switch (rapl_if) {
        _TO_STRING_CASE(power_limit);
        _TO_STRING_CASE(energy_status);
        _TO_STRING_CASE(perf_status);
        _TO_STRING_CASE(power_info);
        _TO_STRING_CASE(policy);

    default:
        throw std::invalid_argument("The specified RAPL domain is "
            "unknown. Make sure to add all new sources in to_string.");
    }

#undef _GCC_IS_SHIT
#undef _TO_STRING_CASE
}


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
 * PWROWG_DETAIL_NAMESPACE::make_power_magic_config
 */
PWROWG_DETAIL_NAMESPACE::msr_magic_config_entry
PWROWG_DETAIL_NAMESPACE::make_power_magic_config(
    _In_ const cpu_vendor vendor,
    _In_ const rapl_domain domain,
    _In_ const std::streamoff data_location,
    _In_ const sensor_type type) {
    msr_magic_config config;
    config.data_location = data_location;
    config.type = sensor_type::software | type;

    switch (vendor) {

    case cpu_vendor::intel:
        config.unit_location = msr_offsets::intel::unit_divisors;
        config.unit_mask = msr_units::intel::power_mask;
        config.unit_offset = msr_units::intel::power_offset;
        break;

    default:
        throw std::invalid_argument("The specified CPU vendor does not "
            "support RAPL MSRs.");
    }

    return std::make_pair(domain, config);
}


/*
 * PWROWG_DETAIL_NAMESPACE::make_time_magic_config
 */
PWROWG_DETAIL_NAMESPACE::msr_magic_config_entry
PWROWG_DETAIL_NAMESPACE::make_time_magic_config(
    _In_ const cpu_vendor vendor,
    _In_ const rapl_domain domain,
    _In_ const std::streamoff data_location,
    _In_ const sensor_type type) {
    msr_magic_config config;
    config.data_location = data_location;
    config.type = sensor_type::software | type;

    switch (vendor) {

    case cpu_vendor::intel:
        config.unit_location = msr_offsets::intel::unit_divisors;
        config.unit_mask = msr_units::intel::time_mask;
        config.unit_offset = msr_units::intel::time_offset;
        break;

    default:
        throw std::invalid_argument("The specified CPU vendor does not "
            "support RAPL MSRs.");
    }

    return std::make_pair(domain, config);
}
