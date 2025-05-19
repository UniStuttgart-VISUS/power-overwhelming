// <copyright file="rtx_trigger_coupling.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_RTX_TRIGGER_COUPLING_H)
#define _PWROWG_RTX_TRIGGER_COUPLING_H
#pragma once

#include "visus/pwrowg/api.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Defines possible couplings for trigger sources.
/// </summary>
enum class rtx_trigger_coupling {

    /// <summary>
    /// Direct current coupling.
    /// </summary>
    direct_current,

    /// <summary>
    /// Alternating current coupling, which will enable a high-pass filter
    /// to remove the DC offset voltage from the trigger signal.
    /// </summary>
    alternating_current,

    /// <summary>
    /// High-frequency coupling, which enables a 15 kHz high-pass filter
    /// to remove lower frequencies from the trigger signal.
    /// </summary>
    low_frequency_reject
};

/// <summary>
/// Parse the given string as <see cref="rtx_trigger_coupling" />.
/// </summary>
/// <param name="str">The string to be parsed.</param>
/// <returns>The parsed enumeration value.</returns>
/// <exception cref="std::invalid_argument">If <paramref name="str" /> is
/// <c>nullptr</c>.</exception>
/// <exception cref="std::invalid_argument">If <paramref name="str" /> does
/// not represent a valid enumeration member.<exception>
extern POWER_OVERWHELMING_API rtx_trigger_coupling
parse_rtx_trigger_coupling(_In_z_ const wchar_t *str);

/// <summary>
/// Convert the given trigger coupling to a human-readable string
/// representation.
/// </summary>
/// <param name="point">The value to be converted.</param>
/// <returns>The string representation of the value.</returns>
/// <exception cref="std::invalid_argument">If the input is not
/// valid and therefore could not be converted.</exception>
extern POWER_OVERWHELMING_API _Ret_valid_ const wchar_t *to_string(
    _In_ const rtx_trigger_coupling point);

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_RTX_TRIGGER_COUPLING_H) */
