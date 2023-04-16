// <copyright file="msr_sensor_impl.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <vector>

#include "power_overwhelming/cpu_affinity.h"
#include "power_overwhelming/cpu_info.h"
#include "power_overwhelming/msr_sensor.h"
#include "power_overwhelming/rapl_domain.h"
#include "power_overwhelming/measurement.h"

#include "msr_device_factory.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// Private data container for the <see cref="msr_sensor" />.
    /// </summary>
    struct msr_sensor_impl final {

        /// <summary>
        /// Determines which RAPL domains are in principle supported for the
        /// given CPU vendor.
        /// </summary>
        /// <remarks>
        /// The specific CPU model at hand might still not support all of the
        /// domains returned by this method.
        /// </remarks>
        /// <param name="vendor">The CPU vendor to determine the available RAPL
        /// domains for.</param>
        /// <returns>A list of domains that might be supported on a CPU by the
        /// given vendor.</returns>
        std::vector<rapl_domain> supported_domains(
            _In_ const cpu_vendor vendor);

        /// <summary>
        /// The MSR device the sensor is reading the data from.
        /// </summary>
        msr_device_factory::device_type device;


        /// <summary>
        /// The offset of the data the sensor samples in the MSR device file.
        /// </summary>
        std::streamoff offset;

        /// <summary>
        /// A sampler for MSR sensors.
        /// </summary>
        //static detail::sampler<emi_sampler_context> sampler;

        /// <summary>
        /// The sensor name.
        /// </summary>
        std::wstring sensor_name;

        /// <summary>
        /// The divisor that allows conversion of samples to Joules.
        /// </summary>
        /// <remarks>
        /// As we are solely sampling the accumulated energy consumption in our
        /// sensor, it is sufficient to have this single divisor.
        /// </remarks>
        std::uint32_t unit_divisor;

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        inline msr_sensor_impl(void) : offset(0), unit_divisor(1) { }

        void set(_In_ const msr_device::core_type core,
            _In_ const rapl_domain domain);

    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
