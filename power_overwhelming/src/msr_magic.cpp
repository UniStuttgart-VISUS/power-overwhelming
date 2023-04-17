// <copyright file="msr_magic_config.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "msr_magic.h"

#include "power_overwhelming/cpu_info.h"


/*
 * visus::power_overwhelming::detail::make_amd_energy_magic_config
 */
visus::power_overwhelming::detail::msr_magic_config
visus::power_overwhelming::detail::make_amd_energy_magic_config(
        _In_ const std::streamoff data_location,
        _In_ std::function<bool(const msr_sensor::core_type)> is_supported) {
    msr_magic_config retval;
    retval.data_location = data_location;
    retval.unit_location = msr_offsets::amd::unit_divisors;
    retval.unit_mask = msr_units::amd::energy_mask;
    retval.unit_offset = msr_units::amd::energy_offset;

    if (is_supported) {
        retval.is_supported = is_supported;
    }

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
    retval.unit_location = msr_offsets::intel::unit_divisors;
    retval.unit_mask = msr_units::intel::energy_mask;
    retval.unit_offset = msr_units::intel::energy_offset;

    if (is_supported) {
        retval.is_supported = is_supported;
    }

    return retval;
}
