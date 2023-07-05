// <copyright file="oscilloscope_channel_polarity.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Defines possible values for the channel polarity.
    /// </summary>
    enum class oscilloscope_channel_polarity {

        /// <summary>
        /// The data are unmodified
        /// </summary>
        normal,

        /// <summary>
        /// Reflect the voltage values of all signal components against the
        /// ground level.
        /// </summary>
        /// <remarks>
        /// Inversion affects only the display of the signal, but not the
        /// trigger.
        /// </remarks>
        inverted,
    };

} /* namespace power_overwhelming */
} /* namespace visus */
