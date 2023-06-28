// <copyright file="oscilloscope_trigger_mode.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Defines possible modes how the oscilloscope triggers.
    /// </summary>
    enum class oscilloscope_trigger_mode {

        /// <summary>
        /// The instrument triggers repeatedly after a time interval if the
        /// configured tigger conditions are not fulfiled. If a real trigger
        /// occurs, it takses precedence.
        /// </summary>
        automatic,

        /// <summary>
        /// The instrument only aquires tata if a real tigger occurs.
        /// </summary>
        normal
    };

} /* namespace power_overwhelming */
} /* namespace visus */
