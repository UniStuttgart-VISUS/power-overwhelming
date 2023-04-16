// <copyright file="msr_sensor_impl.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <chrono>
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
        /// The core the sensor is sampling.
        /// </summary>
        msr_device::core_type core;

        /// <summary>
        /// The MSR device the sensor is reading the data from.
        /// </summary>
        msr_device_factory::device_type device;

        /// <summary>
        /// The RAPL domain the sensor is sampling.
        /// </summary>
        rapl_domain domain;

        /// <summary>
        /// The point in time when the sensor was last sampled.
        /// </summary>
        mutable std::chrono::system_clock::time_point last_time;

        /// <summary>
        /// The value of the last sample.
        /// </summary>
        mutable msr_device::sample_type last_sample;

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
        measurement::value_type unit_divisor;

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        inline msr_sensor_impl(void) : core(0), domain(rapl_domain::package),
            last_sample(0), offset(0), unit_divisor(1) { }

        /// <summary>
        /// Read a new sample into <see cref="last_value" />.
        /// </summary>
        void sample(void);

        /// <summary>
        /// Obtain a new sample and create a measurement from its difference to
        /// <see cref="last_value" />.
        /// </summary>
        /// <param name="resolution">The resolution of the timestamp being
        /// created.</param>
        /// <returns>The result of the measurement.</returns>
        measurement sample(_In_ const timestamp_resolution resolution) const;

        /// <summary>
        /// Sets the initial parameters.
        /// </summary>
        /// <param name="core">The core for which to open the MSR device
        /// file.</param>
        /// <param name="domain">The RAPL domain to sample, which is used to
        /// determine the file offset if <paramref name="offset" /> is
        /// negative.</param>
        /// <param name="offset">A &quot;because-I-know&quot; override for the
        /// file offset. If negative, the method will determine the offset
        /// of the RAPL domain manually.</param>
        /// <exception cref="runtime_error">If the CPU vendor could not be
        /// determined to find the RAPL offset.</exception>
        /// <exception cref="std::invalid_argument">If the RAPL domain is not
        /// supported for the specified CPU core.</exception>
        /// <exception cref="std::system_error">If the MSR device file could
        /// not be opened.</exception>
        void set(_In_ const msr_device::core_type core,
            _In_ const rapl_domain domain,
            _In_ const std::streamoff offset);

    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
