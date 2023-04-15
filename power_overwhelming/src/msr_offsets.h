// <copyright file="msr_offsets.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <ios>


// Values from https://lkml.org/lkml/2011/5/26/93.


namespace visus {
namespace power_overwhelming {
namespace detail {
namespace msr_offsets {

    constexpr std::streamoff amd_package_energy_status = 0xC001029B;
    constexpr std::streamoff amd_pp0_energy_status = 0xC001029A;
    constexpr std::streamoff dram_energy_status = 0x619;
    constexpr std::streamoff dram_performance_status = 0x61B;
    constexpr std::streamoff dram_power_info = 0x61C;
    constexpr std::streamoff dram_power_limit = 0x618;
    constexpr std::streamoff intel_package_energy_status = 0x611;
    constexpr std::streamoff intel_pp0_energy_status = 0x639;
    constexpr std::streamoff package_performance_status = 0x613;
    constexpr std::streamoff package_power_info = 0x614;
    constexpr std::streamoff package_power_limit = 0x610;
    constexpr std::streamoff platform_energy_status = 0x64D;
    constexpr std::streamoff pp0_performance_status = 0x63B;
    constexpr std::streamoff pp0_power_limit = 0x638;
    constexpr std::streamoff pp0_policy = 0x63A;
    constexpr std::streamoff pp1_energy_status = 0x641;
    constexpr std::streamoff pp1_policy = 0x642;
    constexpr std::streamoff pp1_power_limit = 0x640;
    constexpr std::streamoff unit_divisors = 0x606;

} /* namespace msr_offsets */
} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
