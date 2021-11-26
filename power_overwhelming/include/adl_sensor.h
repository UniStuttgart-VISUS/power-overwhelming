// <copyright file="adl_sensor.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "adl_sensor_source.h"
#include "measurement.h"


namespace visus {
namespace power_overwhelming {

    /* Forward declarations */
    namespace detail { struct adl_sensor_impl; }

    /// <summary>
    /// A sensor drawing its information from the AMD display library (ADL).
    /// </summary>
    /// <typeparam name="TMeasurement"></typeparam>
    class POWER_OVERWHELMING_API adl_sensor final {

    public:

        /// <summary>
        /// Create sensors for all supported AMD cards in the system.
        /// </summary>
        /// <remarks>
        /// <para>It is safe to call this method on systems without AMD GPU.
        /// Zero is returned in this case.</para>
        /// </remarks>
        /// <param name="outSensors">Receives the sensors, if not
        /// <c>nullptr</c>.</param>
        /// <param name="cntSensors">The available space in
        /// <paramref name="outSensors" />.</param>
        /// <returns>The number of sensors available on the system, regardless
        /// of the size of the output array. If this number is larger than
        /// <paramref name="cntSensors" />, not all sensors have been returned.
        /// </returns>
        static std::size_t for_all(adl_sensor *outSensors,
            const std::size_t cntSensors);

        /// <summary>
        /// Create a new instance for the specified adapter index.
        /// </summary>
        /// <param name="index">The adapter index to create the sensor for.
        /// </param>
        /// <param name="source">The sensor source to retrieve. If the source
        /// is not supported, the method will fail.</param>
        /// <returns></returns>
        /// <exception cref="adl_exception">If the specified device was not
        /// found, or another error occurred in ADL.</exception>
        static adl_sensor from_index(const int index,
            const adl_sensor_source source);

        /// <summary>
        /// Create a new instance for the unique device ID.
        /// </summary>
        /// <param name="udid">The unique device ID to create the sensor for.
        /// </param>
        /// <param name="source">The sensor source to retrieve. If the source
        /// is not supported, the method will fail.</param>
        /// <returns></returns>
        /// <exception cref="std::invalid_argument">If <paramref name="udid" />
        /// is <c>nullptr</c> or if it did not match exactly one device.
        /// </exception>
        /// <exception cref="adl_exception">If the specified device was not
        /// found, or another error occurred in ADL.</exception>
        static adl_sensor from_udid(const char *udid,
            const adl_sensor_source source);

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <exception cref="std::bad_alloc">If the memory for the sensor state
        /// could not be allocated.</exception>
        /// <exception cref="std::system_error">If the ADL could not be loaded.
        /// </exception>
        /// <exception cref="adl_exception">If the ADL could not be initialised.
        /// </exception>
        adl_sensor(void);

        /// <summary>
        /// Move <paramref name="rhs" /> into a new instance.
        /// </summary>
        /// <param name="rhs"></param>
        /// <returns></returns>
        inline adl_sensor(adl_sensor&& rhs) noexcept : _impl(rhs._impl) {
            rhs._impl = nullptr;
        }

        /// <summary>
        /// Initialise a new instance from a status block.
        /// </summary>
        /// <remarks>
        /// This constructor is intended for internal use only.
        /// </remarks>
        /// <param name="impl">The status block, which must have been allocated
        /// using <c>new</c>. The object takes ownership of the status block.
        /// </param>
        inline explicit adl_sensor(detail::adl_sensor_impl *&& impl) noexcept
                : _impl(impl) {
            impl = nullptr;
        }

        /// <summary>
        /// Finalise the instance.
        /// </summary>
        ~adl_sensor(void);

        /// <summary>
        /// Gets the name of the sensor.
        /// </summary>
        /// <returns>The implementation-defined, human-readable name of the
        /// sensor.</returns>
        const wchar_t *name(void) const noexcept;

        /// <summary>
        /// Sample the sensor.
        /// </summary>
        /// <typeparam name="Resolution">The desired resolution of the timestamp
        /// being created for the measurement.</typeparam>
        /// <returns>A sensor sample with the information about power
        /// consumption that is available via ADL.</returns>
        /// <exception cref="std::runtime_error">If a sensor that has been moved
        /// is sampled.</exception>
        /// <exception cref="adl_exception">If the sensor could not be sampled.
        /// </exception>
        template<timestamp_resolution Resolution>
        inline measurement sample(void) const {
            this->sample(Resolution);
        }

        /// <summary>
        /// Sample the sensor using a timestamp with millisecond resolution.
        /// </summary>
        /// <returns>A sensor sample with the information about power
        /// consumption that is available via ADL.</returns>
        /// <exception cref="std::runtime_error">If a sensor that has been moved
        /// is sampled.</exception>
        /// <exception cref="adl_exception">If the sensor could not be sampled.
        /// </exception>
        inline measurement sample(void) const {
            return this->sample(timestamp_resolution::milliseconds);
        }

        /// <summary>
        /// Move assignment.
        /// </summary>
        /// <param name="rhs">The right-hand side operand</param>
        /// <returns><c>*this</c></returns>
        adl_sensor& operator =(adl_sensor&& rhs) noexcept;

        /// <summary>
        /// Determines whether the sensor is valid.
        /// </summary>
        /// <remarks>
        /// A sensor is considered valid until it has been disposed by a move
        /// operation.
        /// </remarks>
        /// <returns><c>true</c> if the sensor is valid, <c>false</c>
        /// otherwise.</returns>
        operator bool(void) const noexcept;

    private:

        measurement sample(const timestamp_resolution resolution) const;

        detail::adl_sensor_impl *_impl;

    };

} /* namespace power_overwhelming */
} /* namespace visus */
