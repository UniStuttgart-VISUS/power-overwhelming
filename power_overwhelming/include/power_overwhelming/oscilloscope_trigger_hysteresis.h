// <copyright file="oscilloscope_trigger_hysteresis.h" company="Visualisierungsinstitut der Universit�t Stuttgart">
// Copyright � 2023 Visualisierungsinstitut der Universit�t Stuttgart.
// Licenced under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph M�ller</author>

#pragma once


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Defines possible hysteresis ranges around trigger levels on
    /// oscilloscopes.
    /// </summary>
    enum class oscilloscope_trigger_hysteresis {

        /// <summary>
        /// Let the instrument decide, which is the default on reset.
        /// </summary>
        automatic,

        /// <summary>
        /// Small range.
        /// </summary>
        low,

        /// <summary>
        /// Medium range.
        /// </summary>
        medium,

        /// <summary>
        /// Large range.
        /// </summary>
        high
    };

} /* namespace power_overwhelming */
} /* namespace visus */
