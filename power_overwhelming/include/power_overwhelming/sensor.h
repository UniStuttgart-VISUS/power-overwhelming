// <copyright file="sensor.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cinttypes>

#include "power_overwhelming/measurement.h"
#include "power_overwhelming/timestamp_resolution.h"


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
        /// Sample the sensor using a timestamp with the specified resolution.
        /// </summary>
        /// <param name="resolution">The resolution of the timestamp to be
        /// created. This value basically determines the unit in which the
        /// timestamp in the return value is measured.</param>
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
        measurement sample(_In_ const timestamp_resolution resolution) const;

        /// <summary>
        /// Sample the sensor using a timestamp with the specified resolution,
        /// but do not attach the sensor that produces the data to the sample.
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
        /// </remarks>
        /// <param name="resolution">The resolution of the timestamp to be
        /// created. This value basically determines the unit in which the
        /// timestamp in the return value is measured.</param>
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
        inline measurement_data sample_data(
                    _In_ const timestamp_resolution resolution) const {
            return this->sample_sync(resolution);
        }

        /// <summary>
        /// Sample the sensor using a timestamp with millisecond resolution.
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
        inline measurement sample(void) const {
            return this->sample(timestamp_resolution::milliseconds);
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
        /// Synchronously sample the sensor using a timestamp with the specified
        /// resolution.
        /// </summary>
        /// <param name="resolution">The resolution of the timestamp to be
        /// created.</param>
        /// <returns>A single measurement made by the sensor.</returns>
        virtual measurement_data sample_sync(
            _In_ const timestamp_resolution resolution) const = 0;
    };

} /* namespace power_overwhelming */
} /* namespace visus */
