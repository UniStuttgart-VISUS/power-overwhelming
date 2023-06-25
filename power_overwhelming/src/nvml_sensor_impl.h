// <copyright file="nvml_sensor_impl.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <string>

#include <nvml.h>

#include "nvml_scope.h"
#include "sampler.h"
#include "timestamp.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// Private data container for the <see cref="nvml_sensor" />.
    /// </summary>
    struct nvml_sensor_impl final {

        /// <summary>
        /// A sampler for NVML sensors.
        /// </summary>
        static detail::sampler<default_sampler_context<
            nvml_sensor_impl>> sampler;

        /// <summary>
        /// The NVML device the sensor is reading from.
        /// </summary>
        nvmlDevice_t device;

        /// <summary>
        /// The unique ID which NVML uses to identify the device.
        /// </summary>
        std::string device_guid;

        /// <summary>
        /// The name of the device.
        /// </summary>
        std::wstring device_name;

        /// <summary>
        /// The NVML scope making sure the library is ready while the sensor
        /// exists.
        /// </summary>
        nvml_scope scope;

        /// <summary>
        /// The sensor name.
        /// </summary>
        std::wstring sensor_name;

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        inline nvml_sensor_impl(void) : device(nullptr) { }

        /// <summary>
        /// Finalises the instance.
        /// </summary>
        ~nvml_sensor_impl(void);

        /// <summary>
        /// Loads the name of <see cref="device" /> into
        /// <see cref="device_name" />, the device GUID into
        /// <see cref="device_guid" /> and regenerates the
        /// <see cref="sensor_name" />.
        /// </summary>
        void load_device_name(void);

        /// <summary>
        /// Sample the sensor.
        /// </summary>
        /// <param name="resolution">The resolution of the timestamp to be
        /// generated, which defaults to milliseconds.</param>
        /// <returns>A measurement from the sensor.</returns>
        measurement_data sample(const timestamp_resolution resolution
            = timestamp_resolution::milliseconds) const;
    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
