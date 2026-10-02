// <copyright file="msr_magic_config.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_MSR_MAGIC_H)
#define _PWROWG_MSR_MAGIC_H
#pragma once

#include <utility>

#include "visus/pwrowg/cpu_info.h"
#include "visus/pwrowg/api.h"
#include "visus/pwrowg/rapl_domain.h"
#include "visus/pwrowg/rapl_quantity.h"
#include "visus/pwrowg/sensor_type.h"

#include "msr_magic.h"
#include "msr_sensor.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

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


/// <summary>
/// A container for all the magic offsets required to retrieve and interpret
/// data from an MSR device file.
/// </summary>
struct msr_magic_config final {
    /// <summary>
    /// Specifies the offset into the MSR file where the actual data samples
    /// are located.
    /// </summary>
    std::streamoff data_location;

    /// <summary>
    /// The type of sendor we want to report to users of Power Overwhelming.
    /// </summary>
    sensor_type type;

    /// <summary>
    /// Specifies the offset into the MSR file where the unit divisors are
    /// stored.
    /// </summary>
    std::streamoff unit_location;

    /// <summary>
    /// Specifies the bitmask that is applied to the data read from
    /// <see cref="unit_location" /> to isolate the unit.
    /// </summary>
    std::uint64_t unit_mask;

    /// <summary>
    /// Specifies the number of bits that the masked unit bits need to be
    /// shifted to yields a valid number.
    /// </summary>
    std::uint32_t unit_offset;

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    inline msr_magic_config(void) noexcept
        : data_location(0),
        type(sensor_type::unknown),
        unit_location(0),
        unit_mask(0),
        unit_offset(0) { }
};

/// <summary>
/// A pair that can be used to initialise a lookup table in form of an
/// <see cref="std::map" /> or <see cref="std::unordered_map" />.
/// </summary>
typedef std::pair<rapl_domain, msr_magic_config> msr_magic_config_entry;

/// <summary>
/// Creates a <see cref="msr_magic_config" /> for a CPU from the specified
/// vendor and the energy unit and wraps it into a pair for the initialiser
/// of a lookup table.
/// </summary>
inline PWROWG_TEST_API msr_magic_config_entry make_energy_magic_config(
    _In_ const cpu_vendor vendor,
    _In_ const rapl_domain domain,
    _In_ const std::streamoff data_location,
    _In_ const sensor_type type);

/// <summary>
/// Creates a <see cref="msr_magic_config" /> for a CPU from the specified
/// vendor and the power unit and wraps it into a pair for the initialiser
/// of a lookup table.
/// </summary>
inline PWROWG_TEST_API msr_magic_config_entry make_power_magic_config(
    _In_ const cpu_vendor vendor,
    _In_ const rapl_domain domain,
    _In_ const std::streamoff data_location,
    _In_ const sensor_type type);

/// <summary>
/// Creates a <see cref="msr_magic_config" /> for a CPU from the specified
/// vendor and the time unit and wraps it into a pair for the initialiser
/// of a lookup table.
/// </summary>
inline PWROWG_TEST_API msr_magic_config_entry make_time_magic_config(
    _In_ const cpu_vendor vendor,
    _In_ const rapl_domain domain,
    _In_ const std::streamoff data_location,
    _In_ const sensor_type type);


PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_MSR_MAGIC_H) */
