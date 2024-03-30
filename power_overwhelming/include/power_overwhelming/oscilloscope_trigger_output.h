// <copyright file="oscilloscope_trigger_output.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Defines possible modes for the auxilliary trigger output port.
    /// </summary>
    enum class oscilloscope_trigger_output {

        /// <summary>
        /// The auxilliary output is disabled.
        /// </summary>
        off,

        /// <summary>
        /// Outputs a pulse when the instrument triggers.
        /// </summary>
        pulse,

        /// <summary>
        /// Outputs a 10 MHz reference fequency.
        /// </summary>
        reference,

        /// <summary>
        /// Outputs a pulse when a mask is violated.
        /// </summary>
        mask
    };

} /* namespace power_overwhelming */
} /* namespace visus */
