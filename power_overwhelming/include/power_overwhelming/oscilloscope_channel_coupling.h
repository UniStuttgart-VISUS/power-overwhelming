// <copyright file="oscilloscope_channel_coupling.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Defines possible values for channel coupling and termination.
    /// </summary>
    enum class oscilloscope_channel_coupling {

        /// <summary>
        /// DC coupling passes the input signal unchanged.
        /// </summary>
        direct_current_limit,

        /// <summary>
        /// Removes the DC offset voltage from the input signal.
        /// </summary>
        alternating_current_limit,

        /// <summary>
        /// Connection to a virtual ground.
        /// </summary>
        ground
    };

} /* namespace power_overwhelming */
} /* namespace visus */
