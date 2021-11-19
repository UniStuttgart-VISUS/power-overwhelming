// <copyright file="nvml_sensor.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#if defined(POWER_OVERWHELMING_WITH_NVML)
#include <vector>

#include "nvml_exception.h"
#include "nvml_scope.h"
#include "timestamp.h"


namespace visus {
namespace power_overwhelming {


    template<class TMeasurement> class nvml_sensor {

    public:

        /// <summary>
        /// The type of the measurements filled by the sensor.
        /// </summary>
        typedef TMeasurement measurement_type;

        /// <summary>
        /// The type of timestamps assigned to measurements.
        /// </summary>
        typedef typename TMeasurement::timestamp_type timestamp_type;

        /// <summary>
        /// The type that measurements are stored in.
        /// </summary>
        typedef typename TMeasurement::value_type value_type;

        /// <summary>
        /// Create sensors for all supported NVIDIA cards in the system.
        /// </summary>
        /// <returns></returns>
        static std::vector<nvml_sensor> for_all(void);

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
        nvml_sensor(nvml_sensor&& rhs) noexcept;

        /// <summary>
        /// Finalise the instance.
        /// </summary>
        ~nvml_sensor(void);

        /// <summary>
        /// Sample the sensor.
        /// </summary>
        /// <returns>A sensor sample with the information about power
        /// consumption that is available via NVML.</returns>
        measurement_type sample(void) const;

        /// <summary>
        /// Move assignment.
        /// </summary>
        /// <param name="rhs"></param>
        /// <returns></returns>
        nvml_sensor& operator =(nvml_sensor&& rhs) noexcept;

    private:

        nvml_scope __scope;     // Must be first!
        nvmlDevice_t _device;

    };

} /* namespace power_overwhelming */
} /* namespace visus */

#include "nvml_sensor.inl"
#endif /* defined(POWER_OVERWHELMING_WITH_NVML) */
