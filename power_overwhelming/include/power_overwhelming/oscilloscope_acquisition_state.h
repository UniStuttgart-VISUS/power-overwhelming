// <copyright file="oscilloscope_acquisition_state.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cinttypes>


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Specifies possible acquisition states of a Rohde &amp; Schwarz
    /// oscilloscope.
    /// </summary>
    enum class oscilloscope_acquisition_state {

        /// <summary>
        /// The state could not be retrieved or should not be modified in case
        /// of a setter.
        /// </summary>
        unknown = 0x0000,

        /// <summary>
        /// Starts the acquisition.
        /// </summary>
        run,

        /// <summary>
        /// Stops the acquisition when it is finished.
        /// </summary>
        stop,

        /// <summary>
        /// Immediately interrupt the current acquisition.
        /// </summary>
        interrupt,

        /// <summary>
        /// Trigger a single acquisition.
        /// </summary>
        single
    };

} /* namespace power_overwhelming */
} /* namespace visus */
