// <copyright file="tinkerforge_sensor_source.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cinttypes>

#include "power_overwhelming/power_overwhelming_api.h"


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Specifies possible sources for Tinkerforge bricklets.
    /// </summary>
    enum class tinkerforge_sensor_source : std::uint32_t {

        /// <summary>
        /// Request sampling the current sensor only.
        /// </summary>
        current = 0x1,

        /// <summary>
        /// Requests sampling the voltage sensor only.
        /// </summary>
        voltage = 0x2,

        /// <summary>
        /// Requests sampling the power sensor only.
        /// </summary>
        power = 0x4,

        /// <summary>
        /// Requests sampling of all sensors.
        /// </summary>
        all = current | voltage | power
    };

    /// <summary>
    /// Combine two <see cref="tinkerforge_sensor_source" />s.
    /// </summary>
    /// <param name="lhs"></param>
    /// <param name="rhs"></param>
    /// <returns></returns>
    POWER_OVERWHELMING_API tinkerforge_sensor_source operator |(
        const tinkerforge_sensor_source lhs,
        const tinkerforge_sensor_source rhs);

    /// <summary>
    /// Test two <see cref="tinkerforge_sensor_source" />s.
    /// </summary>
    /// <param name="lhs"></param>
    /// <param name="rhs"></param>
    /// <returns></returns>
    POWER_OVERWHELMING_API tinkerforge_sensor_source operator &(
        const tinkerforge_sensor_source lhs,
        const tinkerforge_sensor_source rhs);

    /// <summary>
    /// Convert the given sensor source to a human-readable string
    /// representation.
    /// </summary>
    /// <param name="source">The source to be converted.</param>
    /// <returns>The name of the source.</returns>
    extern POWER_OVERWHELMING_API const wchar_t *to_string(
        const tinkerforge_sensor_source source);

} /* namespace power_overwhelming */
} /* namespace visus */
