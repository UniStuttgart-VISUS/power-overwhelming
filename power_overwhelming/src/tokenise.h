// <copyright file="tokenise.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2018 - 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// Licenced under the MIT License. See LICENCE.txt for further details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cwctype>
#include <string>
#include <vector>


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// Splits a string at the positions where the given
    /// <paramref name="predicate" /> yields true for a characeter, which is
    /// excluded from the tokens.
    /// </summary>
    /// <typeparam name="C">The character type.</typeparam>
    /// <typeparam name="P">The type of the predicate, which must be a functor
    /// accepting <typeparamref name="C" /> and returnig <c>bool</c>.</typeparam>
    /// <param name="str">The string to be split.</param>
    /// <param name="predicate">The predicate determining whether a character
    /// is a token border.</param>
    /// <param name="omitEmpty">If <c>true</c>, removes empty tokens. This
    /// defaults to <c>false</c>.</param>
    /// <returns>A vector holding the tokens (or the whole string if no
    /// occurrence of the delimiter characters was found).</returns>
    template<class C, class P>
    std::vector<std::basic_string<C>> tokenise_if(
        const std::basic_string<C>& str,
        const P predicate, const bool omitEmpty = false);

    /// <summary>
    /// Splits a string between whitespace characters.
    /// </summary>
    /// <param name="str">The string to be split.</param>
    /// <param name="omitEmpty">If <c>true</c>, removes empty tokens. This
    /// defaults to <c>false</c>.</param>
    /// <returns>A vector holding the tokens (or the whole string if no
    /// occurrence of the delimiter characters was found).</returns>
    inline std::vector<std::string> tokenise(
            const std::string& str,
            const bool omitEmpty = false) {
        return tokenise_if(str,
            [](const char c) { return std::isspace(c); },
            omitEmpty);
    }

    /// <summary>
    /// Splits a string between whitespace characters.
    /// </summary>
    /// <param name="str">The string to be split.</param>
    /// <param name="omitEmpty">If <c>true</c>, removes empty tokens. This
    /// defaults to <c>false</c>.</param>
    /// <returns>A vector holding the tokens (or the whole string if no
    /// occurrence of the delimiter characters was found).</returns>
    inline std::vector<std::wstring> tokenise(
            const std::wstring& str,
            const bool omitEmpty = false) {
        return tokenise_if(str,
            [](const wchar_t c) { return std::iswspace(c); },
            omitEmpty);
    }

    ///// <summary>
    ///// Splits a string at the given delimiters <paramref name="beginDelim" />
    ///// to <paramref name="endDelim" /> and returns a vector of the tokens.
    ///// </summary>
    ///// <typeparam name="C">The character type.</typeparam>
    ///// <typeparam name="I">An iterator over <typeparamref name="C" />.
    ///// </typeparam>
    ///// <param name="str">The string to be split.</param>
    ///// <param name="beginDelim">The begin of the range of delimiter
    ///// characters.</param>
    ///// <param name="endDelim">The end of the range of delimiter characters.
    ///// </param>
    ///// <param name="omitEmpty">If <c>true</c>, removes empty tokens. This
    ///// defaults to <c>false</c>.</param>
    ///// <returns>A vector holding the tokens (or the whole string if no
    ///// occurrence of the delimiter characters was found).</returns>
    //template<class C, class I>
    //inline std::vector<std::basic_string<C>> tokenise(
    //        const std::basic_string<C>& str,
    //        I beginDelim,
    //        I endDelim,
    //        const bool omitEmpty = false) {
    //    return tokenise(str, [beginDelim, endDelim](const C c) {
    //            return Contains(beginDelim, endDelim, c); 
    //        }, omitEmpty);
    //}

    /// <summary>
    /// Splits a string at the given separator 'sep' and returns a vector of the
    /// tokens.
    /// </summary>
    /// <typeparam name="C">The character type.</typeparam>
    /// <param name="str">The string to be split.</param>
    /// <param name="delim">The delimiter.</param>
    /// <param name="omitEmpty">If <c>true</c>, removes empty tokens. This
    /// defaults to <c>false</c>.</param>
    /// <returns>A vector holding the tokens (or the whole string if no
    /// occurrence of the delimiter characters was found).</returns>
    template<class C>
    inline std::vector<std::basic_string<C>> tokenise(
            const std::basic_string<C>& str,
            const C delim,
            const bool omitEmpty = false) {
        return tokenise_if(str, [delim](const C c) { return (c == delim); },
            omitEmpty);
    }

    /// <summary>
    /// Splits a string at the given separator string <paramref name="delim" />
    /// and returns a vector of the tokens.
    /// </summary>
    /// <typeparam name="C">The character type.</typeparam>
    /// <param name="str">The string to be split.</param>
    /// <param name="delim">The delimiter.</param>
    /// <param name="omitEmpty">If <c>true</c>, removes empty tokens. This
    /// defaults to <c>false</c>.</param>
    /// <returns>A vector holding the tokens (or the whole string if no
    /// occurrence of the delimiter characters was found).</returns>
    template<class C>
    std::vector<std::basic_string<C>> tokenise(const std::basic_string<C>& str,
        const std::basic_string<C>& delim, const bool omitEmpty = false);

    /// <summary>
    /// Splits a string at the given separator string <paramref name="delim" />
    /// and returns a vector of the tokens.
    /// </summary>
    /// <typeparam name="C">The character type.</typeparam>
    /// <param name="str">The string to be split.</param>
    /// <param name="delim">The delimiter.</param>
    /// <param name="omitEmpty">If <c>true</c>, removes empty tokens. This
    /// defaults to <c>false</c>.</param>
    /// <returns>A vector holding the tokens (or the whole string if no
    /// occurrence of the delimiter characters was found).</returns>
    template<class C>
    std::vector<std::basic_string<C>> tokenise(const std::basic_string<C> &str,
        const C *delim, const bool omitEmpty = false);

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */

#include "tokenise.inl"
