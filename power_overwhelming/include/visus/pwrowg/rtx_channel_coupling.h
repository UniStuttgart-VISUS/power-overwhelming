// <copyright file="rtx_channel_coupling.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_RTX_CHANNEL_COUPLING_H)
#define _PWROWG_RTX_CHANNEL_COUPLING_H
#pragma once

#include "visus/pwrowg/api.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Defines possible values for channel coupling and termination.
/// </summary>
enum class rtx_channel_coupling {

    /// <summary>
    /// DC coupling passes the input signal unchanged.
    /// </summary>
    direct_current_limit,

    /// <summary>
    /// Removes the DC offset voltage from the input signal.
    /// </summary>
    alternating_current_limit,

    /// <summary>
    /// Connection to a virtual ground.
    /// </summary>
    ground
};

/// <summary>
/// Parse the given string as <see cref="rtx_channel_coupling" />.
/// </summary>
/// <param name="str">The string to be parsed.</param>
/// <returns>The parsed enumeration value.</returns>
/// <exception cref="std::invalid_argument">If <paramref name="str" /> is
/// <c>nullptr</c>.</exception>
/// <exception cref="std::invalid_argument">If <paramref name="str" /> does
/// not represent a valid enumeration member.<exception>
extern POWER_OVERWHELMING_API rtx_channel_coupling
parse_rtx_channel_coupling(_In_z_ const wchar_t *str);

/// <summary>
/// Convert the given channel coupling to a human-readable string
/// representation.
/// </summary>
/// <param name="coupling">The value to be converted.</param>
/// <returns>The string representation of the value.</returns>
/// <exception cref="std::invalid_argument">If the input is not
/// valid and therefore could not be converted.</exception>
extern POWER_OVERWHELMING_API _Ret_valid_ const wchar_t *to_string(
    _In_ const rtx_channel_coupling coupling);

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_RTX_CHANNEL_COUPLING_H) */
