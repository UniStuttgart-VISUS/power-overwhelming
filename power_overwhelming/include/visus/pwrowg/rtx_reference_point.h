﻿// <copyright file="rtx_reference_point.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_RTX_REFERENCE_POINT_H)
#define _PWROWG_RTX_REFERENCE_POINT_H
#pragma once

#include <cinttypes>

#include "visus/pwrowg/api.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Specifies possible locations of the reference point in an oscilloscope
/// diagram on Rohde &amp; Schwarz devices.
/// </summary>
/// <remarks>
/// <para>The reference point determines the centre of time scaling
/// operations.</para>
/// <para>The values of the enumeration fields are the magic numbers for
/// Rohde &amp; Schwarz oscilloscopes multiplied by 100.</para>
/// </remarks>
enum class rtx_reference_point : std::uint32_t {

    /// <summary>
    /// The scaling origin is located on the left side of the diagram.
    /// </summary>
    left = 833,

    /// <summary>
    /// The scaling origin is located in the centre of the diagram, which is
    /// the default.
    /// </summary>
    middle = 5000,

    /// <summary>
    /// The scaling origin is located on the right side of the diagram.
    /// </summary>
    right = 9167
};


/// <summary>
/// Parse the given string as <see cref="rtx_reference_point" />.
/// </summary>
/// <param name="str">The string to be parsed.</param>
/// <returns>The parsed enumeration value.</returns>
/// <exception cref="std::invalid_argument">If <paramref name="str" /> is
/// <c>nullptr</c>.</exception>
/// <exception cref="std::invalid_argument">If <paramref name="str" /> does
/// not represent a valid enumeration member.<exception>
extern POWER_OVERWHELMING_API rtx_reference_point
parse_rtx_reference_point(_In_z_ const wchar_t *str);

/// <summary>
/// Convert the given reference point to a human-readable string
/// representation.
/// </summary>
/// <param name="point">The value to be converted.</param>
/// <returns>The string representation of the value.</returns>
/// <exception cref="std::invalid_argument">If the input is not
/// valid and therefore could not be converted.</exception>
extern POWER_OVERWHELMING_API _Ret_valid_ const wchar_t *to_string(
    _In_ const rtx_reference_point point);

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_RTX_REFERENCE_POINT_H) */
