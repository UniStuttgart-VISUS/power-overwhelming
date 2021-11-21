// <copyright file="nvml_sensor_impl.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <string>

#include <nvml.h>

#include "nvml_scope.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// Private data container for the <see cref="nvml_sensor" />.
    /// </summary>
    struct nvml_sensor_impl final {

        /// <summary>
        /// The NVML scope, which must be the first member.
        /// </summary>
        nvml_scope _scope;

        /// <summary>
        /// The NVML device the sensor is reading from.
        /// </summary>
        nvmlDevice_t device;

        /// <summary>
        /// The name of the device.
        /// </summary>
        std::wstring device_name;

        /// <summary>
        /// The sensor name.
        /// </summary>
        std::wstring sensor_name;

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        inline nvml_sensor_impl(void) : device(nullptr) { }

        /// <summary>
        /// Loads the name of <see cref="device" /> into
        /// <see cref="device_name" /> and regenerates the
        /// <see cref="sensor_name" />.
        /// </summary>
        /// <param name=""></param>
        void load_device_name(void);
    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
