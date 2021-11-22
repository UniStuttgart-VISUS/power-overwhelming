// <copyright file="adl_sensor_source.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once


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

} /* namespace power_overwhelming */
} /* namespace visus */
