// <copyright file="literal.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2017 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_LITERAL_H)
#define _PWROWG_LITERAL_H
#pragma once

#include "visus/pwrowg/api.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// A helper class for selecting a literal string based on a template
/// parameter.
/// </summary>
/// <remarks>
/// This must be used by means of the <c>POWER_OVERWHALMING_TPL_LITERAL</c>
/// macro.
/// </remarks>
/// <typeparam name="TChar">The type of a character.</typeparam>
template<class TChar> struct literal_selector {
    typedef TChar char_type;
};

/// <summary>
/// Specialisation for ASCII characters.
/// </summary>
template<> struct literal_selector<char> {
    typedef char char_type;
    static inline constexpr char_type select(_In_ const char n,
            _In_ const wchar_t w) {
        return n;
    }
    static inline _Ret_maybenull_z_ constexpr const char_type *select(
            _In_opt_z_ const char *n,
            _In_opt_z_ const wchar_t *w) {
        return n;
    }
};

/// <summary>
/// Specialisation for Unicode characters.
/// </summary>
template<> struct literal_selector<wchar_t> {
    typedef wchar_t char_type;
    static inline constexpr char_type select(_In_ const char n,
            _In_ const wchar_t w) {
        return w;
    }
    static inline _Ret_maybenull_z_ constexpr const char_type *select(
            _In_opt_z_ const char *n,
            _In_opt_z_ const wchar_t *w) {
        return w;
    }
};

PWROWG_DETAIL_NAMESPACE_END


/// <summary>
/// Generates a literal string <paramref name="l" />, which is either ASCII or
/// Unicode depending on the template parameter <paramref name="T" />.
/// </summary>
#define PWROWG_TPL_LITERAL(T, l)\
PWROWG_DETAIL_NAMESPACE::literal_selector<T>::select(l, L##l)

/// <summary>
/// Provides backwards compatibility for <see cref="PWROWG_TPL_LITERAL" />.
/// </summary>
#define POWER_OVERWHELMING_TPL_LITERAL(T, l) PWROWG_TPL_LITERAL(T, l)

#endif /* !defined(_PWROWG_LITERAL_H) */