// <copyright file="regex_escape.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <algorithm>
#include <regex>

#include "power_overwhelming/literal.h"


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Escape all special characters in the given string such that they match
    /// as literals in a regular expression.
    /// </summary>
    /// <typeparam name="TChar">The character type.</typeparam>
    /// <param name="str">The string to match literally in a regular expression.
    /// </param>
    /// <returns>The escaped string.</returns>
    template<class TChar>
    std::basic_string<TChar> regex_escape(const std::basic_string<TChar>& str) {
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

} /* namespace power_overwhelming */
} /* namespace visus */
