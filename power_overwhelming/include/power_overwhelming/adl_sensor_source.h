// <copyright file="adl_sensor_source.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once


#include "power_overwhelming/power_overwhelming_api.h"


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Specifies possible sources for ADL sensors.
    /// </summary>
    enum class adl_sensor_source {

        /// <summary>
        /// 
        /// </summary>
        soc,

        /// <summary>
        /// 
        /// </summary>
        graphics,

        /// <summary>
        /// 
        /// </summary>
        asic,

        /// <summary>
        /// 
        /// </summary>
        cpu
    };

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
