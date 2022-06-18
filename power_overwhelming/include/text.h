// <copyright file="text.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <string>
#include <vector>

#include "literal.h"
#include "power_overwhelming_api.h"


namespace visus {
namespace power_overwhelming {

namespace detail {

    extern std::size_t POWER_OVERWHELMING_API convert_string(
        char *output, const std::size_t cnt_output,
        const wchar_t *input, const std::size_t cnt_input);

    extern std::size_t POWER_OVERWHELMING_API convert_string(
        wchar_t *output, const std::size_t cnt_output,
        const char *input, const std::size_t cnt_input);
}

    /// <summary>
    /// Converts a string to the given character set.
    /// </summary>
    /// <typeparam name="TOutput">The character set of the target string.
    /// </typeparam>
    /// <typeparam name="TInput">The character set of the original string.
    /// </typeparam>
    /// </typeparam>
    /// <param name="str">The string to be converted. If is safe to pass
    /// <c>nullptr</c>, in which case an empty string will be assumed.</param>
    /// <returns>The converted string.</returns>
    template<class TOutput, class TInput>
    typename std::enable_if<std::is_same<TOutput, TInput>::value,
        std::basic_string<TOutput>>::type convert_string(const TInput *str);

    /// <summary>
    /// Converts a string to the given character set.
    /// </summary>
    /// <typeparam name="TOutput">The character set of the target string.
    /// </typeparam>
    /// <typeparam name="TInput">The character set of the original string.
    /// </typeparam>
    /// </typeparam>
    /// <param name="str">The string to be converted. If is safe to pass
    /// <c>nullptr</c>, in which case an empty string will be assumed.</param>
    /// <returns>The converted string.</returns>
    template<class TOutput, class TInput>
    typename std::enable_if<!std::is_same<TOutput, TInput>::value,
        std::basic_string<TOutput>>::type convert_string(const TInput *str);

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

#include "text.inl"
