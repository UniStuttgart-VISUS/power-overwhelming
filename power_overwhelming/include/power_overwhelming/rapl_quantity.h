// <copyright file="rapl_quantity.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Possible quantities that can be provided via RAPL registers.
    /// </summary>
    enum class rapl_quantity {

        /// <summary>
        /// Energy in Joules or derived from it.
        /// </summary>
        energy,

        /// <summary>
        /// Power in Watts or derived from it.
        /// </summary>
        power,

        /// <summary>
        /// Time in seconds or derived from it.
        /// </summary>
        time,
    };

} /* namespace power_overwhelming */
} /* namespace visus */
