// <copyright file="log_mode.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Defines possible logging modes of the <see cref="hmc8015_sensor" />.
    /// </summary>
    enum class log_mode {

        /// <summary>
        /// Capture data until explicitly stopped or the memory is full.
        /// </summary>
        unlimited,

        /// <summary>
        /// Capture the specified number of samples.
        /// </summary>
        count,

        /// <summary>
        /// Capture for the specified duration after start.
        /// </summary>
        duration,

        /// <summary>
        /// Capture for the specified duration after the given start time.
        /// </summary>
        time_span
    };

} /* namespace power_overwhelming */
} /* namespace visus */
