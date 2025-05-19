// <copyright file="regex_escape.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_REGEX_ESCAPE_H)
#define _PWROWG_REGEX_ESCAPE_H
#pragma once

#include <algorithm>
#include <regex>

#include "visus/pwrowg/literal.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Escape all special characters in the given string such that they match as
/// literals in a regular expression.
/// </summary>
/// <typeparam name="TChar">The character type.</typeparam>
/// <param name="str">The string to match literally in a regular expression.
/// </param>
/// <returns>The escaped string.</returns>
template<class TChar>
std::basic_string<TChar> regex_escape(
        _In_ const std::basic_string<TChar>& str) {
    static const std::basic_string<TChar> special
        = POWER_OVERWHELMING_TPL_LITERAL(TChar, "-[]{}()*+?.,\\^$|#");
    std::basic_string<TChar> retval;
    retval.reserve(str.size() + str.size() / 3);    // Just a heuristic ...

    for (auto c : str) {
        if (special.find(c) != decltype(special)::npos) {
            retval += POWER_OVERWHELMING_TPL_LITERAL(TChar, "\\");
        }

        retval += c;
    }

    return retval;
}

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_REGEX_ESCAPE_H) */
