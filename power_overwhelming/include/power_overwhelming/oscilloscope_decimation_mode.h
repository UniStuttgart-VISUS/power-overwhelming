// <copyright file="oscilloscope_decimation_mode.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "power_overwhelming/power_overwhelming_api.h"


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


    /// <summary>
    /// Parse the given string as <see cref="oscilloscope_decimation_mode" />.
    /// </summary>
    /// <param name="str">The string to be parsed.</param>
    /// <returns>The parsed enumeration value.</returns>
    /// <exception cref="std::invalid_argument">If <paramref name="str" /> is
    /// <c>nullptr</c>.</exception>
    /// <exception cref="std::invalid_argument">If <paramref name="str" /> does
    /// not represent a valid enumeration member.<exception>
    extern POWER_OVERWHELMING_API oscilloscope_decimation_mode
    parse_oscilloscope_decimation_mode(_In_z_ const wchar_t *str);

    /// <summary>
    /// Convert the given decimation mode to a human-readable string
    /// representation.
    /// </summary>
    /// <param name="mode">The value to be converted.</param>
    /// <returns>The string representation of the value.</returns>
    /// <exception cref="std::invalid_argument">If the input is not
    /// valid and therefore could not be converted.</exception>
    extern POWER_OVERWHELMING_API _Ret_valid_ const wchar_t *to_string(
        _In_ const oscilloscope_decimation_mode polarity);

} /* namespace power_overwhelming */
} /* namespace visus */
