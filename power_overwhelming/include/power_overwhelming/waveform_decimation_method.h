// <copyright file="waveform_decimation_method.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once


namespace visus {
namespace power_overwhelming {


    /// <summary>
    /// Specifies how an oscilloscope-based sensor should convert the waveforms
    /// it acquired into a single sample.
    /// </summary>
    enum class waveform_decimation_method {

        /// <summary>
        /// Use the first sample point in the waveform.
        /// </summary>
        first,

        /// <summary>
        /// Use the middle sample point in the waveform.
        /// </summary>
        middle,

        /// <summary>
        /// Use the last sample point in the waveform.
        /// </summary>
        last,

        /// <summary>
        /// Compute the arithmetic mean.
        /// </summary>
        mean,

        /// <summary>
        /// Compute the root-mean square
        /// </summary>
        rms

    };

} /* namespace power_overwhelming */
} /* namespace visus */
