// <copyright file="rtx_decimation_mode.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_RTX_DECIMATION_MODE_H)
#define _PWROWG_RTX_DECIMATION_MODE_H
#pragma once

#include "visus/pwrowg/api.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Selects the method to reduce the data stream of the ADS to a stream of
/// waveform points with lower sample rate.
/// </summary>
enum class rtx_decimation_mode {

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
/// Parse the given string as <see cref="rtx_decimation_mode" />.
/// </summary>
/// <param name="str">The string to be parsed.</param>
/// <returns>The parsed enumeration value.</returns>
/// <exception cref="std::invalid_argument">If <paramref name="str" /> is
/// <c>nullptr</c>.</exception>
/// <exception cref="std::invalid_argument">If <paramref name="str" /> does
/// not represent a valid enumeration member.<exception>
extern POWER_OVERWHELMING_API rtx_decimation_mode
parse_rtx_decimation_mode(_In_z_ const wchar_t *str);

/// <summary>
/// Convert the given decimation mode to a human-readable string
/// representation.
/// </summary>
/// <param name="mode">The value to be converted.</param>
/// <returns>The string representation of the value.</returns>
/// <exception cref="std::invalid_argument">If the input is not
/// valid and therefore could not be converted.</exception>
extern POWER_OVERWHELMING_API _Ret_valid_ const wchar_t *to_string(
    _In_ const rtx_decimation_mode polarity);

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_RTX_DECIMATION_MODE_H) */
