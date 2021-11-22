// <copyright file="adl_sensor_source.h" company="Visualisierungsinstitut der Universit�t Stuttgart">
// Copyright � 2021 Visualisierungsinstitut der Universit�t Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph M�ller</author>

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
