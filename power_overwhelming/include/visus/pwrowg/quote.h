// <copyright file="quote.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_QUOTE_H)
#define _PWROWG_QUOTE_H
#pragma once

#include <string>

#include "visus/pwrowg/literal.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Enclose the given string in quotes.
/// </summary>
/// <typeparam name="TChar">The type of a character in the string.
/// </typeparam>
/// <param name="str">The string to be quoted. It is safe to pass
/// <c>nullptr</c>, which will be interpreted as an empty string.</param>
/// <param name="quote">The quote character, which defaults to double
/// quotes.</param>
/// <returns>The quoted input string.</returns>
template<class TChar>
std::basic_string<TChar> quote(_In_opt_z_ const TChar *str,
    _In_ const TChar quote = POWER_OVERWHELMING_TPL_LITERAL(TChar, '"'));

PWROWG_NAMESPACE_END

#include "visus/pwrowg/quote.inl"

#endif /* !defined(_PWROWG_QUOTE_H) */