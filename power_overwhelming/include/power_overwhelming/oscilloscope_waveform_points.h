// <copyright file="oscilloscope_waveform_points.h" company="Visualisierungsinstitut der Universit�t Stuttgart">
// Copyright � 2023 Visualisierungsinstitut der Universit�t Stuttgart.
// Licenced under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph M�ller</author>

#pragma once


namespace visus {
namespace power_overwhelming {


    /// <summary>
    /// Specifies possible types of waveform points to be selected for transfer.
    /// </summary>
    enum class oscilloscope_waveform_points {

        /// <summary>
        /// The default, which are the points visible on screen at the
        /// resolution visible on screen.
        /// </summary>
        visible,

        /// <summary>
        /// All points a maximum resolution as they are available in memory.
        /// </summary>
        maximum,

        /// <summary>
        /// Points at maximum resolution available in memory, but only for the
        /// visible range.
        /// </summary>
        maximum_visible

    };

} /* namespace power_overwhelming */
} /* namespace visus */
