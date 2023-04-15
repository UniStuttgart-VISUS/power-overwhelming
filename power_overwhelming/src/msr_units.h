// <copyright file="msr_units.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cinttypes>


// Values from https://lkml.org/lkml/2011/5/26/93.


namespace visus {
namespace power_overwhelming {
namespace detail {
namespace msr_units {

    /// <summary>
    /// The mask for isolating the conversion factor for energy in the
    /// sample returned from location <see cref="unit_offset" />.
    /// </summary>
    static constexpr std::uint64_t energy_mask = 0x1F00;

    /// <summary>
    /// The number of bits the energy unit conversion constant needs to be
    /// shifted to be isolated.
    /// </summary>
    static constexpr std::uint32_t energy_offset = 0x08;

    /// <summary>
    /// The mask for isolating the conversion factor for power in the
    /// sample returned from location <see cref="unit_offset" />.
    /// </summary>
    static constexpr std::uint64_t power_mask = 0x000F;

    /// <summary>
    /// The number of bits the power unit conversion constant needs to be
    /// shifted to be isolated.
    /// </summary>
    static constexpr std::uint32_t power_offset = 0x00;

    /// <summary>
    /// The mask for isolating the conversion factor for time in the
    /// sample returned from location <see cref="unit_offset" />.
    /// </summary>
    static constexpr std::uint64_t time_mask = 0xF000;

    /// <summary>
    /// The number of bits the time unit conversion constant needs to be
    /// shifted to be isolated.
    /// </summary>
    static constexpr std::uint32_t time_offset = 0x10;

} /* namespace msr_units */
} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
