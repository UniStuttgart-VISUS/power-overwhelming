// <copyright file="msr_sensor_impl.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "power_overwhelming/msr_sensor.h"
#include "power_overwhelming/measurement.h"
#include "power_overwhelming/rapl_domain.h"

#include "msr_device_factory.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// Private data container for the <see cref="msr_sensor" />.
    /// </summary>
    /// <remarks>
    /// The magic numbers here are from https://lkml.org/lkml/2011/5/26/93.
    /// </remarks>
    struct msr_sensor_impl final {

        /// <summary>
        /// The mask for isolating the conversion factor for energy in the
        /// sample returned from location <see cref="unit_offset" />.
        /// </summary>
        static constexpr std::uint32_t energy_unit_mask = 0x1F00;

        /// <summary>
        /// The number of bits the energy unit conversion constant needs to be
        /// shifted to be isolated.
        /// </summary>
        static constexpr std::uint32_t energy_unit_offset = 0x08;

        /// <summary>
        /// The mask for isolating the conversion factor for power in the
        /// sample returned from location <see cref="unit_offset" />.
        /// </summary>
        static constexpr std::uint32_t power_unit_mask = 0x000F;

        /// <summary>
        /// The number of bits the power unit conversion constant needs to be
        /// shifted to be isolated.
        /// </summary>
        static constexpr std::uint32_t power_unit_offset = 0x00;

        /// <summary>
        /// The mask for isolating the conversion factor for time in the
        /// sample returned from location <see cref="unit_offset" />.
        /// </summary>
        static constexpr std::uint32_t time_unit_mask = 0xF000;

        /// <summary>
        /// The number of bits the time unit conversion constant needs to be
        /// shifted to be isolated.
        /// </summary>
        static constexpr std::uint32_t time_unit_offset = 0x10;

        /// <summary>
        /// The offset of the unit divisors in the MSR device file.
        /// </summary>
        static constexpr std::streamoff unit_offset = 0x606;

        /// <summary>
        /// The MSR device the sensor is reading the data from.
        /// </summary>
        msr_device_factory::device_type device;

        /// <summary>
        /// The divisor that allows conversion of samples to Joules.
        /// </summary>
        std::uint32_t energy_unit_divisor;

        /// <summary>
        /// The divisor that allows conversion of samples to Watts.
        /// </summary>
        std::uint32_t power_unit_divisor;

        /// <summary>
        /// A sampler for MSR sensors.
        /// </summary>
        //static detail::sampler<emi_sampler_context> sampler;

        /// <summary>
        /// The sensor name.
        /// </summary>
        std::wstring sensor_name;

        /// <summary>
        /// The divisor that allows conversion of samples to seconds.
        /// </summary>
        std::uint32_t time_unit_divisor;

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        inline msr_sensor_impl(void) : energy_unit_divisor(1),
            power_unit_divisor(1), time_unit_divisor(1) { }

        /// <summary>
        /// Finalises the instance.
        /// </summary>
        ~msr_sensor_impl(void);

        void set(_In_ const msr_device::core_type core,
            _In_ const rapl_domain domain);

    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */

        //amd_package_energy_status = 0xc001029b,
        //amd_pp0_energy_status = 0xc001029a,
        //dram_energy_status = 0x619,
        //dram_performance_status = 0x61b,
        //dram_power_info = 0x61c,
        //dram_power_limit = 0x618,
        //intel_package_energy_status = 0x611,
        //intel_pp0_energy_status = 0x639,
        //package_performance_status = 0x613,
        //package_power_info = 0x614,
        //package_power_limit = 0x610,
        //platform_energy_status = 0x64d,
        //pp0_performance_status = 0x63b,
        //pp0_power_limit = 0x638,
        //pp0_policy = 0x63A,
        //pp1_energy_status = 0x641,
        //pp1_policy = 0x642,
        //pp1_power_limit = 0x640
