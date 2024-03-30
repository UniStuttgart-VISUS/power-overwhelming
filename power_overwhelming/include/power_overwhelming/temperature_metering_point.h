// <copyright file="temperature_metering_point.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2024 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cinttypes>


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Provides several well-known metering points for measuring the
    /// temperature on the GPU.
    /// </summary>
    enum class temperature_metering_point : std::uint32_t {

        /// <summary>
        /// The metering point is unknown and must be derived from the native
        /// identifier value of the underlying API.
        /// </summary>
        unknown,

        /// <summary>
        /// The metering point is the hotspot of the GPU.
        /// </summary>
        hotspot,

        /// <summary>
        /// The metering point is the GPU memory.
        /// </summary>
        memory
    };

} /* namespace power_overwhelming */
} /* namespace visus */
