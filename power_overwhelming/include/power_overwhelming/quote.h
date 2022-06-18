// <copyright file="quote.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <string>

#include "literal.h"
#include "power_overwhelming_api.h"


namespace visus {
namespace power_overwhelming {


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
    std::basic_string<TChar> quote(const TChar *str,
        const TChar quote = POWER_OVERWHELMING_TPL_LITERAL(TChar, '"'));

} /* namespace power_overwhelming */
} /* namespace visus */

#include "power_overwhelming/quote.inl"
