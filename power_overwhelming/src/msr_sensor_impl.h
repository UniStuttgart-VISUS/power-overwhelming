// <copyright file="msr_sensor_impl.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <chrono>
#include <vector>

#include "visus/pwrowg/async_sampling.h"
#include "visus/pwrowg/cpu_affinity.h"
#include "visus/pwrowg/cpu_info.h"
#include "visus/pwrowg/msr_sensor.h"
#include "visus/pwrowg/rapl_domain.h"
#include "visus/pwrowg/measurement.h"

#include "basic_sampler_source.h"
#include "msr_device_factory.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /* Forward declarations. */
    struct msr_magic_config;


    /// <summary>
    /// Private data container for the <see cref="msr_sensor" />.
    /// </summary>
    struct msr_sensor_impl final
            : public basic_sampler_source<msr_sensor_impl> {

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
        static std::vector<rapl_domain> supported_domains(
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
        /// The value of the last sample.
        /// </summary>
        mutable msr_device::sample_type last_sample;

        /// <summary>
        /// The point in time when the sensor was last sampled.
        /// </summary>
        mutable std::chrono::system_clock::time_point last_time;

        /// <summary>
        /// The offset of the data the sensor samples in the MSR device file.
        /// </summary>
        std::streamoff offset;

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
        /// Finalises the instance.
        /// </summary>
        ~msr_sensor_impl(void) noexcept;

        /// <summary>
        /// Reads the current value of the register and optionally performs the
        /// unit conversion.
        /// </summary>
        /// <remarks>
        /// This method performs a read, but does not record it to
        /// <see cref="last_sample" /> and <see cref="last_time" />.
        /// </remarks>
        /// <param name="convert">If <c>true</c>, apply the
        /// <see cref="unit_divisor" /> before returning the value.</param>
        /// <returns>The current value of the MSR.</returns>
        msr_device::sample_type read(_In_ const bool convert) const;

        /// <summary>
        /// Obtain a new sample and create a measurement from its difference to
        /// <see cref="last_value" />.
        /// </summary>
        /// <returns>The result of the measurement.</returns>
        measurement_data sample(void) const;

        /// <summary>
        /// Sets the initial parameters.
        /// </summary>
        /// <param name="core">The core for which to open the MSR device
        /// file.</param>
        /// <param name="domain">The RAPL domain to sample, which is used to
        /// determine the file offset if <paramref name="config_override" /> is
        /// not provided.</param>
        /// <param name="config_override">A &quot;because-I-know&quot; override
        /// for the file offsets. If <c>nullptr</c>, the method will determine
        /// the offset of the RAPL domain manually.</param>
        /// <exception cref="runtime_error">If the CPU vendor could not be
        /// determined to find the RAPL offset.</exception>
        /// <exception cref="std::invalid_argument">If the RAPL domain is not
        /// supported for the specified CPU core.</exception>
        /// <exception cref="std::system_error">If the MSR device file could
        /// not be opened.</exception>
        void set(_In_ const msr_device::core_type core,
            _In_ const rapl_domain domain,
            _In_opt_ const msr_magic_config *config_override);
    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
