// <copyright file="oscilloscope_trigger_slope.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Defines possible slopes for edge triggers on an oscillosope.
    /// </summary>
    enum class oscilloscope_trigger_slope {

        /// <summary>
        /// Triggers on rising and falling edges.
        /// </summary>
        both,

        /// <summary>
        /// Triggers on the rising edge only.
        /// </summary>
        rising,

        /// <summary>
        /// Triggers on the falling edge only.
        /// </summary>
        falling
    };

} /* namespace power_overwhelming */
} /* namespace visus */
