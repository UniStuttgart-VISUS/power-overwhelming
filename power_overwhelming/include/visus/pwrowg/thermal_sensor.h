// <copyright file="thermal_sensor.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "power_overwhelming/async_sampling.h"
#include "power_overwhelming/temperature_metering_point.h"
#include "power_overwhelming/thermal_sample.h"
#include "power_overwhelming/timestamp.h"


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Defines the interface for a temperature sensors.
    /// </summary>
    class POWER_OVERWHELMING_API thermal_sensor {

    public:

        /// <summary>
        /// Finalises the instance.
        /// </summary>
        virtual ~thermal_sensor(void) = default;

        /// <summary>
        /// Answer the well-known metering point from which the sensor gets its
        ///  data.
        /// </summary>
        /// <returns>The metering point or
        /// <see cref="temperature_metering_point::unknown" /> if the underlying
        /// API uses a metering point that cannot be mapped to any of the
        /// well-known ones.</returns>
        virtual temperature_metering_point metering_point(
            void) const noexcept = 0;

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
        /// Enables the specified asynchronous sampling on the sensor.
        /// </summary>
        /// <param name="async_sampling">The asynchronous sampling configuration
        /// for the sensor.</param>
        virtual void sample(_Inout_ async_sampling&& async_sampling) = 0;

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
    };

} /* namespace power_overwhelming */
} /* namespace visus */
