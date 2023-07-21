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
