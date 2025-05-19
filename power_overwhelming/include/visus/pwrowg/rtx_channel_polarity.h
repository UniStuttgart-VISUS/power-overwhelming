// <copyright file="rtx_channel_polarity.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_RTX_CHANNEL_POLARITY_H)
#define _PWROWG_RTX_CHANNEL_POLARITY_H
#pragma once

#include "visus/pwrowg/api.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Defines possible values for the channel polarity.
/// </summary>
enum class rtx_channel_polarity {

    /// <summary>
    /// The data are unmodified
    /// </summary>
    normal,

    /// <summary>
    /// Reflect the voltage values of all signal components against the
    /// ground level.
    /// </summary>
    /// <remarks>
    /// Inversion affects only the display of the signal, but not the
    /// trigger.
    /// </remarks>
    inverted,
};

/// <summary>
/// Parse the given string as <see cref="rtx_channel_polarity" />.
/// </summary>
/// <param name="str">The string to be parsed.</param>
/// <returns>The parsed enumeration value.</returns>
/// <exception cref="std::invalid_argument">If <paramref name="str" /> is
/// <c>nullptr</c>.</exception>
/// <exception cref="std::invalid_argument">If <paramref name="str" /> does
/// not represent a valid enumeration member.<exception>
extern POWER_OVERWHELMING_API rtx_channel_polarity
parse_rtx_channel_polarity(_In_z_ const wchar_t *str);

/// <summary>
/// Convert the given channel polarity to a human-readable string
/// representation.
/// </summary>
/// <param name="polarity">The value to be converted.</param>
/// <returns>The string representation of the value.</returns>
/// <exception cref="std::invalid_argument">If the input is not
/// valid and therefore could not be converted.</exception>
extern POWER_OVERWHELMING_API _Ret_valid_ const wchar_t *to_string(
    _In_ const rtx_channel_polarity polarity);

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_RTX_CHANNEL_POLARITY_H) */
