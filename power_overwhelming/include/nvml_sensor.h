// <copyright file="nvml_sensor.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "measurement.h"


namespace visus {
namespace power_overwhelming {

    /* Forward declarations */
    namespace detail { struct nvml_sensor_impl; }

    /// <summary>
    /// Implementation of a power sensor using the NVIDIA management library to
    /// read the internal sensors of the GPU.
    /// </summary>
    class POWER_OVERWHELMING_API nvml_sensor final {

    public:

        ///// <summary>
        ///// Create sensors for all supported NVIDIA cards in the system.
        ///// </summary>
        ///// <returns></returns>
        //static std::vector<nvml_sensor> for_all(void);

        /// <summary>
        /// Create a new instance for the device with the specified PCI bus ID.
        /// </summary>
        /// <param name="pciBusId"></param>
        /// <returns></returns>
        static nvml_sensor from_bus_id(const char *pciBusId);

        /// <summary>
        /// Create a new instance for the device with the specified unique ID.
        /// </summary>
        /// <param name="guid"></param>
        /// <returns></returns>
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
        /// found or another error occurred in NVML.</exception>
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
        nvml_sensor(void) noexcept;

        /// <summary>
        /// Move <paramref name="rhs" /> into a new instance.
        /// </summary>
        /// <param name="rhs"></param>
        /// <returns></returns>
        inline nvml_sensor(nvml_sensor &&rhs) noexcept : _impl(rhs._impl) {
            rhs._impl = nullptr;
        }

        /// <summary>
        /// Finalise the instance.
        /// </summary>
        ~nvml_sensor(void);

        /// <summary>
        /// Sample the sensor.
        /// </summary>
        /// <returns>A sensor sample with the information about power
        /// consumption that is available via NVML.</returns>
        measurement sample(void) const;

        /// <summary>
        /// Move assignment.
        /// </summary>
        /// <param name="rhs"></param>
        /// <returns></returns>
        nvml_sensor& operator =(nvml_sensor&& rhs) noexcept;

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

        detail::nvml_sensor_impl *_impl;

    };

} /* namespace power_overwhelming */
} /* namespace visus */
