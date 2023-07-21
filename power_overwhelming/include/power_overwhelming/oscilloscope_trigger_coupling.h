// <copyright file="oscilloscope_trigger_coupling.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Defines possible couplings for trigger sources.
    /// </summary>
    enum class oscilloscope_trigger_coupling {

        /// <summary>
        /// Direct current coupling.
        /// </summary>
        direct_current,

        /// <summary>
        /// Alternating current coupling, which will enable a high-pass filter
        /// to remove the DC offset voltage from the trigger signal.
        /// </summary>
        alternating_current,

        /// <summary>
        /// High-frequency coupling, which enables a 15 kHz high-pass filter
        /// to remove lower frequencies from the trigger signal.
        /// </summary>
        low_frequency_reject
    };

} /* namespace power_overwhelming */
} /* namespace visus */
