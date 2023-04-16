﻿// <copyright file="msr_sensor.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <ios>

#include "power_overwhelming/rapl_domain.h"
#include "power_overwhelming/sensor.h"


namespace visus {
namespace power_overwhelming {

    /* Forward declarations */
    namespace detail { struct msr_sensor_impl; }

    /// <summary>
    /// Implementation of a power sensor using the MSR files for reading RAPL
    /// registers.
    /// </summary>
    class POWER_OVERWHELMING_API msr_sensor final : public sensor {

    public:

        /// <summary>
        /// The type used to index CPU cores.
        /// </summary>
        typedef std::uint32_t core_type;

        /// <summary>
        /// Creates a new sensor for the specified core and RAPL domain,
        /// forcing the specified <see cref="offset" /> for the location of the
        /// energy sample in the MSR device file.
        /// </summary>
        /// <remarks>
        /// <para>This factory method exists due to the fact that the whole RAPL
        /// stuff is poorly documented and the implementation is copied from
        /// all over the internet. Furthermore, there is no centralised
        /// implementation for that stuff in Linux we can rely on to be up to
        /// date. Therefore, this method provides the opportunity for callers
        /// who know that a specific CPU supports a specific RAPL domain at a
        /// specific offset in the MSR device file to force the creation of the
        /// sensor, bypassing all built-in sanity checks based on the
        /// aforementioned sketchy information.</para>
        /// </remarks>
        /// <param name="core">The index of the CPU core for which the MSR
        /// sensor should be opened.</param>
        /// <param name="domain">The RAPL domain that is being sampled by the
        /// sensor. This information is only used for creating the sensor name,
        /// but has no effect on the actual data that are being read by the
        /// sensor.</param>
        /// <param name="offset">The offset into the MSR device file where the
        /// samlpes are read from.</param>
        /// <returns>A new instance of the MSR sensor for the specified
        /// configuration.</returns>
        /// <exception cref="std::system_error">If the MSR device file could not
        /// be opened.</exception>
        static msr_sensor force_create(_In_ const core_type core,
            _In_ const rapl_domain domain, _In_ const std::streamoff offset);

        /// <summary>
        /// Create sensors for all MSR files.
        /// </summary>
        /// <param name="out_sensors">Receives the sensors, if not
        /// <c>nullptr</c>.</param>
        /// <param name="cnt_sensors">The available space in
        /// <paramref name="out_sensors" />.</param>
        /// <returns>The number of sensors available on the system, regardless
        /// of the size of the output array. If this number is larger than
        /// <paramref name="cntSensors" />, not all sensors have been returned.
        /// </returns>
        /// <exception cref="std::system_error">If enumerating or opening the
        /// devices failed.</exception>
        static std::size_t for_all(
            _Out_writes_opt_(cnt_sensors) msr_sensor *out_sensors,
            _In_ const std::size_t cnt_sensors);

        /// <summary>
        /// Create an MSR sensor for the specified core and RAPL domain.
        /// </summary>
        /// <param name="core">The index of the CPU core for which the MSR
        /// sensor should be opened.</param>
        /// <param name="domain">The RAPL domain that is being sampled.</param>
        /// <returns></returns>
        /// <exception cref="runtime_error">If the CPU vendor could not be
        /// determined to find the RAPL offset.</exception>
        /// <exception cref="std::invalid_argument">If the RAPL domain is not
        /// supported for the specified CPU core.</exception>
        /// <exception cref="std::system_error">If the MSR device file could not
        /// be opened.</exception>
        static msr_sensor for_core(_In_ const core_type core,
            _In_ const rapl_domain domain);

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        msr_sensor(void);

        /// <summary>
        /// Move <paramref name="rhs" /> into a new instance.
        /// </summary>
        /// <param name="rhs">The object to be moved.</param>
        inline msr_sensor(_In_ msr_sensor&& rhs) noexcept : _impl(rhs._impl) {
            rhs._impl = nullptr;
        }

        /// <summary>
        /// Finalise the instance.
        /// </summary>
        virtual ~msr_sensor(void);

        /// <summary>
        /// Answer the core the sensor is sampling.
        /// </summary>
        /// <returns>The index ofo the core the sensor is sampling.</returns>
        /// <exception cref="std::runtime_error">If the method is called on a
        /// sensor that has been disposed.</exception>
        core_type core(void) const;

        /// <summary>
        /// Answer the RAPL domain the sensor is sampling.
        /// </summary>
        /// <returns>The RAPL domain the sensor is sampling.</returns>
        /// <exception cref="std::runtime_error">If the method is called on a
        /// sensor that has been disposed.</exception>
        rapl_domain domain(void) const;

        /// <inheritdoc />
        virtual _Ret_maybenull_z_ const wchar_t *name(
            void) const noexcept override;

        /// <summary>
        /// Answer the location in the MSR device file the sensor is sampling.
        /// </summary>
        /// <remarks>
        /// This information is of limited use for end users, but is mainly
        /// required to implement serialisation.
        /// </remarks>
        /// <returns>The offset in bytes at which the sampled data are
        /// searched.</returns>
        /// <exception cref="std::runtime_error">If the method is called on a
        /// sensor that has been disposed.</exception>
        std::streamoff offset(void) const;

        /// <inheritdoc />
        virtual measurement sample(
            _In_ const timestamp_resolution resolution) const override;

        /// <summary>
        /// Move assignment.
        /// </summary>
        /// <param name="rhs">The right-hand side operand</param>
        /// <returns><c>*this</c></returns>
        msr_sensor& operator =(_In_ msr_sensor&& rhs) noexcept;

        /// <inheritdoc />
        virtual operator bool(void) const noexcept override;

    private:

        detail::msr_sensor_impl *_impl;

        friend struct detail::msr_sensor_impl;
    };

} /* namespace power_overwhelming */
} /* namespace visus */