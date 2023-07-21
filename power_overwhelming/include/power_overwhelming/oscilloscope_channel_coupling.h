// <copyright file="oscilloscope_channel_coupling.h" company="Visualisierungsinstitut der Universit�t Stuttgart">
// Copyright � 2023 Visualisierungsinstitut der Universit�t Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph M�ller</author>

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
