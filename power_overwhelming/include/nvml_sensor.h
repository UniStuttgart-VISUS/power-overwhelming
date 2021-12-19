// <copyright file="nvml_sensor.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "sensor.h"


namespace visus {
namespace power_overwhelming {

    /* Forward declarations */
    namespace detail { struct nvml_sensor_impl; }

    /// <summary>
    /// Implementation of a power sensor using the NVIDIA management library to
    /// read the internal sensors of the GPU.
    /// </summary>
    class POWER_OVERWHELMING_API nvml_sensor final : public sensor {

    public:

        /// <summary>
        /// Create sensors for all supported NVIDIA cards in the system.
        /// </summary>
        /// <remarks>
        /// <para>It is safe to call the method on machines without NVIDIA GPU.
        /// In this case, zero is returned.</para>
        /// </remarks>
        /// <param name="outSensors">Receives the sensors, if not
        /// <c>nullptr</c>.</param>
        /// <param name="cntSensors">The available space in
        /// <paramref name="outSensors" />.</param>
        /// <returns>The number of sensors available on the system, regardless
        /// of the size of the output array. If this number is larger than
        /// <paramref name="cntSensors" />, not all sensors have been returned.
        /// </returns>
        static std::size_t for_all(nvml_sensor *outSensors,
            const std::size_t cntSensors);

        /// <summary>
        /// Create a new instance for the device with the specified PCI bus ID.
        /// </summary>
        /// <param name="pciBusId"></param>
        /// <returns></returns>
        /// <exception cref="nvml_exception">If the specified device was not
        /// found, is not unique or another error occurred in NVML.</exception>
        static nvml_sensor from_bus_id(const char *pciBusId);

        /// <summary>
        /// Create a new instance for the device with the specified unique ID.
        /// </summary>
        /// <param name="guid"></param>
        /// <returns></returns>
        /// <exception cref="nvml_exception">If the specified device was not
        /// found, is not unique or another error occurred in NVML.</exception>
        static nvml_sensor from_guid(const char *guid);

        /// <summary>
        /// Create a new instance from a device index.
        /// </summary>
        /// <remarks>
        /// <para>Device indices start at zero and go up to the number of
        /// supported NVIDIA cards minus one.</para>
        /// <para>Please note that the indices may not match the indices of
        /// CUDA devices and/or DXGI adapters.</para>
        /// </remarks>
        /// <param name="index"></param>
        /// <returns></returns>
        /// <exception cref="nvml_exception">If the specified device was not
        /// found, is not unique or another error occurred in NVML.</exception>
        static nvml_sensor from_index(const unsigned int index);

        /// <summary>
        /// Create a new instance for a specific device serial number printed on
        /// the board.
        /// </summary>
        /// <param name="serial"></param>
        /// <returns></returns>
        /// <exception cref="nvml_exception">If the specified device was not
        /// found, is not unique or another error occurred in NVML.</exception>
        static nvml_sensor from_serial(const char *serial);

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <exception cref="std::bad_alloc">If the memory for the sensor state
        /// could not be allocated.</exception>
        /// <exception cref="std::system_error">If the NVML library could not be
        /// loaded.</exception>
        /// <exception cref="nvml_exception">If the NVML library could not be
        /// initialised.</exception>
        nvml_sensor(void);

        /// <summary>
        /// Move <paramref name="rhs" /> into a new instance.
        /// </summary>
        /// <param name="rhs">The object to be moved.</param>
        inline nvml_sensor(nvml_sensor&& rhs) noexcept : _impl(rhs._impl) {
            rhs._impl = nullptr;
        }

        /// <summary>
        /// Finalise the instance.
        /// </summary>
        ~nvml_sensor(void);

        /// <summary>
        /// Gets the name of the sensor.
        /// </summary>
        /// <returns>The implementation-defined, human-readable name of the
        /// sensor.</returns>
        const wchar_t *name(void) const noexcept;

        /// <inheritdoc />
        virtual measurement sample(
            const timestamp_resolution resolution) const override;

        /// <summary>
        /// Move assignment.
        /// </summary>
        /// <param name="rhs">The right-hand side operand</param>
        /// <returns><c>*this</c></returns>
        nvml_sensor& operator =(nvml_sensor&& rhs) noexcept;

        /// <inheritdoc />
        virtual operator bool(void) const noexcept override;

    private:

        measurement sample(const measurement::timestamp_type timestamp) const;

        detail::nvml_sensor_impl *_impl;

    };

} /* namespace power_overwhelming */
} /* namespace visus */
