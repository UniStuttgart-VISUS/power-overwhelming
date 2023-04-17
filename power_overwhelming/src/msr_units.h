// <copyright file="msr_units.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cinttypes>


namespace visus {
namespace power_overwhelming {
namespace detail {
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
