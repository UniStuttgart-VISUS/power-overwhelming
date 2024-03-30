// <copyright file="integrator_mode.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Defines possible modes of integrator of the the
    /// <see cref="hmc8015_sensor" />.
    /// </summary>
    enum class integrator_mode {

        /// <summary>
        /// Manual integration (user triggered). This is the default behaviour.
        /// </summary>
        manual,

        /// <summary>
        /// Integrate for a specified duration.
        /// </summary>
        duration,

        /// <summary>
        /// Integrate for a specified time span (start and end).
        /// </summary>
        time_span,
    };

} /* namespace power_overwhelming */
} /* namespace visus */
