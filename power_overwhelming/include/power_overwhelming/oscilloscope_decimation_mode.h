// <copyright file="oscilloscope_decimation_mode.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Selects the method to reduce the data stream of the ADS to a stream of
    /// waveform points with lower sample rate.
    /// </summary>
    enum class oscilloscope_decimation_mode {

        /// <summary>
        /// Input data is acquired with a sample rate which is aligned to the
        // time base (horizontal scale) and the record length.
        /// </summary>
        sample,

        /// <summary>
        /// The minimum and the maximum of n samples in a sample interval are
        ///  recorded as waveform points.
        /// </summary>
        peak_detect,

        /// <summary>
        /// The average of n sample points is recorded as waveform point.
        /// </summary>
        high_resolution
    };

} /* namespace power_overwhelming */
} /* namespace visus */
