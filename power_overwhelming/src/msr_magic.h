// <copyright file="msr_magic.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <ios>


namespace visus {
namespace power_overwhelming {
namespace detail {

    // Offsets into the device files for various sensor readings and the unit
    // divisors that allow for converting the raw numbers for Watts, Joules
    // and seconds, respecitvely.
namespace msr_offsets {
namespace amd {
    // AMD offsets from https://github.com/amd/amd_energy/blob/master/amd_energy.c
    // and https://github.com/deater/uarch-configure/blob/master/rapl-read/rapl-read.c
    constexpr std::streamoff package_energy_status = 0xC001029B;
    constexpr std::streamoff pp0_energy_status = 0xC001029A;
    constexpr std::streamoff unit_divisors = 0xC0010299;
} /* namespace amd */

namespace intel {
    // Offsets from https://lkml.org/lkml/2011/5/26/93
    constexpr std::streamoff dram_energy_status = 0x619;
    constexpr std::streamoff dram_performance_status = 0x61B;
    constexpr std::streamoff dram_power_info = 0x61C;
    constexpr std::streamoff dram_power_limit = 0x618;
    constexpr std::streamoff package_energy_status = 0x611;
    constexpr std::streamoff package_performance_status = 0x613;
    constexpr std::streamoff package_power_info = 0x614;
    constexpr std::streamoff package_power_limit = 0x610;
    constexpr std::streamoff platform_energy_status = 0x64D;
    constexpr std::streamoff pp0_energy_status = 0x639;
    constexpr std::streamoff pp0_performance_status = 0x63B;
    constexpr std::streamoff pp0_power_limit = 0x638;
    constexpr std::streamoff pp0_policy = 0x63A;
    constexpr std::streamoff pp1_energy_status = 0x641;
    constexpr std::streamoff pp1_policy = 0x642;
    constexpr std::streamoff pp1_power_limit = 0x640;
    constexpr std::streamoff unit_divisors = 0x606;
} /* namespace intel */
} /* namespace msr_offsets */

    // The bitmasks and bitshift offsets for isolating different divisors in the
    // 64-bit value we read for all units at once.
namespace msr_units {
namespace amd {
    // Values from  https://github.com/amd/amd_energy/blob/master/amd_energy.c
    constexpr std::uint32_t energy_offset = 0x08;
    constexpr std::uint64_t energy_mask = 0x1F00;
} /* namespace amd */

namespace intel {
    // Values from https://lkml.org/lkml/2011/5/26/93
    constexpr std::uint64_t energy_mask = 0x1F00;
    constexpr std::uint32_t energy_offset = 0x08;
    constexpr std::uint64_t power_mask = 0x000F;
    constexpr std::uint32_t power_offset = 0x00;
    constexpr std::uint64_t time_mask = 0xF000;
    constexpr std::uint32_t time_offset = 0x10;
} /* namespace intel */
} /* namespace msr_units */

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
