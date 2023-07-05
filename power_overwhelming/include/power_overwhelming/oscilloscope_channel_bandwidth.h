// <copyright file="oscilloscope_channel_bandwidth.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Defines possible values for the channel bandwidth
    /// </summary>
    enum class oscilloscope_channel_bandwidth {

        /// <summary>
        /// Use the full bandwidth.
        /// </summary>
        full,

        /// <summary>
        /// Limit to 20 Mhz in order to reduce high-frequency noise.
        /// </summary>
        limit_to_20_mhz,

    };

} /* namespace power_overwhelming */
} /* namespace visus */
