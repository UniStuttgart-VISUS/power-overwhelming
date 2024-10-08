﻿// <copyright file="sensor.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cinttypes>

#include "power_overwhelming/async_sampling.h"
#include "power_overwhelming/measurement.h"


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Defines the interface for a power sensor.
    /// </summary>
    class POWER_OVERWHELMING_API sensor {

    public:

        /// <summary>
        /// The type to represent microseconds intervals in.
        /// </summary>
        typedef std::uint64_t microseconds_type;

        /// <summary>
        /// The default sampling interval of one millisecond.
        /// </summary>
        static constexpr microseconds_type default_sampling_period = 1000;

        /// <summary>
        /// Finalises the instance.
        /// </summary>
        virtual ~sensor(void) = default;

        /// <summary>
        /// Gets the name of the sensor.
        /// </summary>
        /// <remarks>
        /// Implementors should make resonable effort to make this name unique,
        /// first by including their sensor type and second by including some
        /// kind of unique device identifier if multiple instances of the sensor
        /// are supported on a single machine.
        /// </remarks>
        /// <returns>The implementation-defined, human-readable name of the
        /// sensor. This value may be <c>nullptr</c> if the sensor has been
        /// disposed.</returns>
        virtual _Ret_maybenull_z_ const wchar_t *name(void) const noexcept = 0;

        /// <summary>
        /// Sample the sensor.
        /// </summary>
        /// <returns>A single measurement made by the sensor.</returns>
        /// <exception cref="std::runtime_error">If a sensor that has been moved
        /// (and therefore disposed) is sampled.</exception>
        /// <exception cref="adl_exception">If an ADL sensor could not be
        /// sampled.</exception>
        /// <exception cref="nvml_exception">If an NVML sensor could not be
        /// sampled.</exception>
        /// <exception cref="tinkerforge_exception">If a Tinkerforge sensor
        /// could not be sampled.</exception>
        /// <exception cref="visa_exception">If a sensor based on a VISA
        /// instrument could not be sampled.</exception>
        /// <exception cref="std::system_error">If a sensor could not be sampled
        /// due to a system call failing.</exception>
        measurement sample(void) const;

        /// <summary>
        /// Enables the specified asynchronous sampling on the sensor.
        /// </summary>
        /// <param name="async_sampling">The asynchronous sampling configuration
        /// for the sensor.</param>
        void sample(_Inout_ async_sampling&& async_sampling);

        /// <summary>
        /// Sample the sensor using a timestamp, but do not attach the sensor
        /// that produces the data to the sample.
        /// </summary>
        /// <remarks>
        /// <para>This new method is an alternative to
        /// <see cref="sensor::sample" /> that does not incur the cost for
        /// copying the name of the sensor producing the data to the sample. It
        /// is suitable for applications that keep track of the sensors and the
        /// samples on their own and that cause the least possible overhead on
        /// the machine the code is running on. This is specifically interesting
        /// for applications using sensors that can only be sampled on the
        /// machine under observation, like GPU power sensors and the RAPL
        /// registers.</para>
        /// <para>Please be aware that you might not be able to obtain all
        /// information about the sensor that the data originate from when
        /// using this method. This is the case if the underlying API can
        /// produce samples from different sources. Such sensors must be
        /// configured to make sure that they only return the data expected
        /// when using this method for sampling.</para>
        /// <para>Rationale: The naming of this method (and of
        /// <see cref="measurement_data" />) is a bit weird, which is due to the
        /// fact that samples without the originating sensor embedded have been
        /// added later to the library. The previous type and method names have
        /// not been changed at this point in order to not break existing code
        /// relying on the library.</para>
        /// </remarks>
        /// <returns>A single measurement made by the sensor.</returns>
        /// <exception cref="std::runtime_error">If a sensor that has been moved
        /// (and therefore disposed) is sampled.</exception>
        /// <exception cref="adl_exception">If an ADL sensor could not be
        /// sampled.</exception>
        /// <exception cref="nvml_exception">If an NVML sensor could not be
        /// sampled.</exception>
        /// <exception cref="tinkerforge_exception">If a Tinkerforge sensor
        /// could not be sampled.</exception>
        /// <exception cref="visa_exception">If a sensor based on a VISA
        /// instrument could not be sampled.</exception>
        /// <exception cref="std::system_error">If a sensor could not be sampled
        /// due to a system call failing.</exception>
        inline measurement_data sample_data(void) const {
            return this->sample_sync();
        }

        /// <summary>
        /// Determines whether the sensor is valid.
        /// </summary>
        /// <remarks>
        /// <para>A sensor is considered valid until it has been disposed by a
        /// move operation.</para>
        /// <para>Sensor implementations typically use the PIMPL pattern to hide
        /// any device-specific APIs that users of the library should not have
        /// to link themselves. This operator should evaluate whether the
        /// implementation pointer is still valid or has been disposed by a move
        /// operation.</para>
        /// </remarks>
        /// <returns><c>true</c> if the sensor is valid, <c>false</c>
        /// otherwise.</returns>
        virtual operator bool(void) const noexcept = 0;

    protected:

        /// <summary>
        /// Checks whether the sensor instance is valid and throws a
        /// <see cref="std::runtime_error" /> if this is not the case.
        /// </summary>
        /// <remarks>
        /// Implementors should use this method as guard in their
        /// <see cref="sample" /> methods.
        /// </remarks>
        /// <exception cref="std::runtime_error">If a sensor that has been moved
        /// (and therefore disposed) is sampled.</exception>
        void check_not_disposed(void) const;

        /// <summary>
        /// Apply the given asynchronous sampling configuration.
        /// </summary>
        /// <remarks>
        /// <para>Implementors can assume that the base class will call this method
        /// only if the sensor has not been disposed.</para>
        /// </remarks>
        /// <param name="sampling">The new asynchronous sampling configuration
        /// of the sensor, which may enable, change or disable asynchronous
        /// sampling.</param>
        virtual void sample_async(_Inout_ async_sampling&& sampling) = 0;

        /// <summary>
        /// Synchronously sample the senso.
        /// </summary>
        /// <remarks>
        /// <para>Implementors can assume that the base class will call this method
        /// only if the sensor has not been disposed.</para>
        /// </remarks>
        /// <returns>A single measurement made by the sensor.</returns>
        virtual measurement_data sample_sync(void) const = 0;
    };

} /* namespace power_overwhelming */
} /* namespace visus */
