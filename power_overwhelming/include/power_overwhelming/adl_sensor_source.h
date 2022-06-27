// <copyright file="adl_sensor_source.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cinttypes>
#include <limits>


#include "power_overwhelming/power_overwhelming_api.h"


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Specifies possible sources for ADL sensors.
    /// </summary>
    enum class adl_sensor_source : std::uint32_t {

        /// <summary>
        /// 
        /// </summary>
        soc = 0x0001,

        /// <summary>
        /// 
        /// </summary>
        graphics = 0x0002,

        /// <summary>
        /// 
        /// </summary>
        asic = 0x0004,

        /// <summary>
        /// 
        /// </summary>
        cpu = 0x0008,

        /// <summary>
        /// Represents all possible sensor sources.
        /// </summary>
        /// <remarks>
        /// This should only be used for filtering when creating the sensor
        /// instances. In end-user code, it is usually an indication that
        /// something is going wrong if this value is used.
        /// </remarks>
        all = (std::numeric_limits<std::uint32_t>::max)()
    };

    /// <summary>
    /// Combine two <see cref="adl_sensor_source" />s.
    /// </summary>
    /// <param name="lhs"></param>
    /// <param name="rhs"></param>
    /// <returns></returns>
    POWER_OVERWHELMING_API adl_sensor_source operator |(
        const adl_sensor_source lhs, const adl_sensor_source rhs);

    /// <summary>
    /// Test two <see cref="adl_sensor_source" />s.
    /// </summary>
    /// <param name="lhs"></param>
    /// <param name="rhs"></param>
    /// <returns></returns>
    POWER_OVERWHELMING_API adl_sensor_source operator &(
        const adl_sensor_source lhs, const adl_sensor_source rhs);

    /// <summary>
    /// Convert the given sensor source to a human-readable string
    /// representation.
    /// </summary>
    /// <param name="source">The source to be converted.</param>
    /// <returns>The name of the source.</returns>
    extern POWER_OVERWHELMING_API const wchar_t *to_string(
        const adl_sensor_source source);

} /* namespace power_overwhelming */
} /* namespace visus */
