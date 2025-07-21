// <copyright file="tokenise.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2018 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT License. See LICENCE.txt for further details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_TOKENISE_H)
#define _PWROWG_TOKENISE_H
#pragma once

#include <cwctype>
#include <string>
#include <vector>


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Splits a range of characters at the positions where the given
/// <paramref name="predicate" /> yields true for a characeter, which is
/// excluded from the tokens.
/// </summary>
/// <typeparam name="TChar">The character type.</typeparam>
/// <typeparam name="TPredicate">The type of the predicate, which must be a
/// functor accepting <typeparamref name="TChar" /> and returnig <c>bool</c>.
/// </typeparam>
/// <param name="begin">The begin of the string to be split. It is safe to pass
/// <c>nullptr</c>, in which case the return value will be empty.</param>
/// <param name="end">The end of the string to split. If this is <c>nullptr</c>,
/// the string designated by <paramref name="begin" /> is assumed to be
/// null-terminated.</param>
/// <param name="predicate">The predicate determining whether a character
/// is a token border.</param>
/// <param name="omit_empty">If <c>true</c>, removes empty tokens. This
/// defaults to <c>false</c>.</param>
/// <returns>A vector holding the tokens (or the whole string if no
/// occurrence of the delimiter characters was found).</returns>
template<class TChar, class TPredicate>
std::vector<std::basic_string<TChar>> tokenise_range_if(
    _In_opt_ const TChar *begin,
    _In_opt_ const TChar *end,
    _In_ const TPredicate predicate,
    _In_ const bool omit_empty = false);

/// <summary>
/// Splits a string at the positions where the given
/// <paramref name="predicate" /> yields true for a characeter, which is
/// excluded from the tokens.
/// </summary>
/// <typeparam name="TChar">The character type.</typeparam>
/// <typeparam name="TPredicate">The type of the predicate, which must be a
/// functor accepting <typeparamref name="TChar" /> and returnig <c>bool</c>.
/// </typeparam>
/// <param name="str">The string to be split. It is safe to pass <c>nullptr</c>,
/// in which case the return value will be empty.</param>
/// <param name="predicate">The predicate determining whether a character
/// is a token border.</param>
/// <param name="omit_empty">If <c>true</c>, removes empty tokens. This
/// defaults to <c>false</c>.</param>
/// <returns>A vector holding the tokens (or the whole string if no
/// occurrence of the delimiter characters was found).</returns>
template<class TChar, class TPredicate>
inline std::vector<std::basic_string<TChar>> tokenise_if(
        _In_opt_z_ const TChar *str,
        _In_ const TPredicate predicate,
        _In_ const bool omit_empty = false) {
    return tokenise_range_if(str, nullptr, predicate, omit_empty);
}

/// <summary>
/// Splits a string at the positions where the given
/// <paramref name="predicate" /> yields true for a characeter, which is
/// excluded from the tokens.
/// </summary>
/// <typeparam name="TChar">The character type.</typeparam>
/// <typeparam name="TTraits">The character traits.</typeparam>
/// <typeparam name="TAlloc">The allocator of the string.</typeparam>
/// <typeparam name="TPredicate">The type of the predicate, which must be a
/// functor accepting <typeparamref name="TChar" /> and returnig <c>bool</c>.
/// </typeparam>
/// <param name="str">The string to be split.</param>
/// <param name="predicate">The predicate determining whether a character
/// is a token border.</param>
/// <param name="omit_empty">If <c>true</c>, removes empty tokens. This
/// defaults to <c>false</c>.</param>
/// <returns>A vector holding the tokens (or the whole string if no
/// occurrence of the delimiter characters was found).</returns>
template<class TChar, class TTraits, class TAlloc, class TPredicate>
inline std::vector<std::basic_string<TChar>> tokenise_if(
        _In_ const std::basic_string<TChar, TTraits, TAlloc>& str,
        _In_ const TPredicate predicate,
        _In_ const bool omit_emtpy = false) {
    return tokenise_range_if(str.c_str(),
        static_cast<const TChar *>(nullptr),
        predicate,
        omit_emtpy);
}

/// <summary>
/// Splits a string between whitespace characters.
/// </summary>
/// <param name="begin">The begin of the string to be split. It is safe to pass
/// <c>nullptr</c>, in which case the return value will be empty.</param>
/// <param name="end">The end of the string to split. If this is <c>nullptr</c>,
/// the string designated by <paramref name="begin" /> is assumed to be
/// null-terminated.</param>
/// <param name="omit_empty">If <c>true</c>, removes empty tokens. This
/// defaults to <c>false</c>.</param>
/// <returns>A vector holding the tokens (or the whole string if no
/// occurrence of the delimiter characters was found).</returns>
inline std::vector<std::string> tokenise_range(
        _In_opt_ const char *begin,
        _In_opt_ const char *end,
        _In_ const bool omit_empty = false) {
    return tokenise_range_if(begin, end,
        [](const char c) { return std::isspace(c); },
        omit_empty);
}

/// <summary>
/// Splits a string between whitespace characters.
/// </summary>
/// <param name="begin">The begin of the string to be split. It is safe to pass
/// <c>nullptr</c>, in which case the return value will be empty.</param>
/// <param name="end">The end of the string to split. If this is <c>nullptr</c>,
/// the string designated by <paramref name="begin" /> is assumed to be
/// null-terminated.</param>
/// <param name="omit_empty">If <c>true</c>, removes empty tokens. This
/// defaults to <c>false</c>.</param>
/// <returns>A vector holding the tokens (or the whole string if no
/// occurrence of the delimiter characters was found).</returns>
inline std::vector<std::wstring> tokenise_range(
        _In_opt_ const wchar_t *begin,
        _In_opt_ const wchar_t *end,
        _In_ const bool omit_empty = false) {
    return tokenise_range_if(begin, end,
        [](const wchar_t c) { return std::iswspace(c); },
        omit_empty);
}

/// <summary>
/// Splits a string between whitespace characters.
/// </summary>
/// <typeparam name="TChar">The character type.</typeparam>
/// <param name="str">The string to be split.</param>
/// <param name="omit_empty">If <c>true</c>, removes empty tokens. This
/// defaults to <c>false</c>.</param>
/// <returns>A vector holding the tokens (or the whole string if no
/// occurrence of the delimiter characters was found).</returns>
template<class TChar, class TTraits, class TAlloc>
inline std::vector<std::basic_string<TChar>> tokenise(
        _In_ const std::basic_string<TChar, TTraits, TAlloc>& str,
        _In_ const bool omit_empty = false) {
    return tokenise_range(str.c_str(), nullptr, omit_empty);
}

/// <summary>
/// Splits a string at the given separator 'sep' and returns a vector of the
/// tokens.
/// </summary>
/// <typeparam name="TChar">The character type.</typeparam>
/// <param name="begin">The begin of the string to be split. It is safe to pass
/// <c>nullptr</c>, in which case the return value will be empty.</param>
/// <param name="end">The end of the string to split. If this is <c>nullptr</c>,
/// the string designated by <paramref name="begin" /> is assumed to be
/// null-terminated.</param>
/// <param name="delim">The delimiter.</param>
/// <param name="omit_empty">If <c>true</c>, removes empty tokens. This
/// defaults to <c>false</c>.</param>
/// <returns>A vector holding the tokens (or the whole string if no
/// occurrence of the delimiter characters was found).</returns>
template<class TChar>
inline std::vector<std::basic_string<TChar>> tokenise(
        _In_opt_ const TChar *begin,
        _In_opt_ const TChar *end,
        _In_ const TChar delim,
        _In_ const bool omit_empty = false) {
    return tokenise_range_if(begin, end,
        [delim](const TChar c) { return (c == delim); },
        omit_empty);
}

/// <summary>
/// Splits a string at the given separator 'sep' and returns a vector of the
/// tokens.
/// </summary>
/// <typeparam name="TChar">The character type.</typeparam>
/// <param name="str">The string to be split.</param>
/// <param name="delim">The delimiter.</param>
/// <param name="omit_empty">If <c>true</c>, removes empty tokens. This
/// defaults to <c>false</c>.</param>
/// <returns>A vector holding the tokens (or the whole string if no
/// occurrence of the delimiter characters was found).</returns>
template<class TChar>
inline std::vector<std::basic_string<TChar>> tokenise(
        _In_opt_z_ const TChar *str,
        _In_ const TChar delim,
        _In_ const bool omit_empty = false) {
    return tokenise(str, delim, omit_empty);
}

/// <summary>
/// Splits a string at the given separator 'sep' and returns a vector of the
/// tokens.
/// </summary>
/// <typeparam name="TChar">The character type.</typeparam>
/// <typeparam name="TTraits">The character traits.</typeparam>
/// <typeparam name="TAlloc">The allocator of the string.</typeparam>
/// <param name="str">The string to be split. It is safe to pass <c>nullptr</c>,
/// in which case the return value will be empty.</param>
/// <param name="delim">The delimiter.</param>
/// <param name="omit_empty">If <c>true</c>, removes empty tokens. This
/// defaults to <c>false</c>.</param>
/// <returns>A vector holding the tokens (or the whole string if no
/// occurrence of the delimiter characters was found).</returns>
template<class TChar, class TTraits, class TAlloc>
inline std::vector<std::basic_string<TChar>> tokenise(
        _In_ const std::basic_string<TChar, TTraits, TAlloc>& str,
        _In_ const TChar delim,
        _In_ const bool omit_empty = false) {
    return tokenise_if(str, nullptr, delim, omit_empty);
}

/// <summary>
/// Splits a string at the given separator string <paramref name="delim" />
/// and returns a vector of the tokens.
/// </summary>
/// <typeparam name="TChar">The character type.</typeparam>
/// <typeparam name="TTraits">The character traits.</typeparam>
/// <typeparam name="TAlloc">The allocator of the string.</typeparam>
/// <param name="str">The string to be split.</param>
/// <param name="delim">The delimiter.</param>
/// <param name="omit_empty">If <c>true</c>, removes empty tokens. This
/// defaults to <c>false</c>.</param>
/// <returns>A vector holding the tokens (or the whole string if no
/// occurrence of the delimiter characters was found).</returns>
template<class TChar, class TTraits, class TAlloc>
std::vector<std::basic_string<TChar, TTraits, TAlloc>> tokenise(
    _In_ const std::basic_string<TChar, TTraits, TAlloc>& str,
    _In_ const std::basic_string<TChar, TTraits, TAlloc>& delim,
    _In_ const bool omitEmpty = false);

/// <summary>
/// Splits a string at the given separator string <paramref name="delim" />
/// and returns a vector of the tokens.
/// </summary>
/// <typeparam name="TChar">The character type.</typeparam>
/// <typeparam name="TTraits">The character traits.</typeparam>
/// <typeparam name="TAlloc">The allocator of the string.</typeparam>
/// <param name="str">The string to be split.</param>
/// <param name="delim">The delimiter.</param>
/// <param name="omit_empty">If <c>true</c>, removes empty tokens. This
/// defaults to <c>false</c>.</param>
/// <returns>A vector holding the tokens (or the whole string if no
/// occurrence of the delimiter characters was found).</returns>
template<class TChar, class TTraits, class TAlloc>
std::vector<std::basic_string<TChar, TTraits, TAlloc>> tokenise(
    _In_ const std::basic_string<TChar, TTraits, TAlloc>& str,
    _In_z_ const TChar *delim,
    _In_ const bool omitEmpty = false);

PWROWG_DETAIL_NAMESPACE_END

#include "trrojan/tokenise.inl"

#endif /* !defined(_PWROWG_TOKENISE_H) */
