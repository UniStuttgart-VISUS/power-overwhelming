// <copyright file="literal.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2017 - 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "power_overwhelming/power_overwhelming_api.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

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
        static constexpr char_type select(_In_ const char n,
                _In_ const wchar_t w) {
            return n;
        }
        static _Ret_maybenull_z_ constexpr const char_type *select(
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
        static constexpr char_type select(_In_ const char n,
                _In_ const wchar_t w) {
            return w;
        }
        static _Ret_maybenull_z_ constexpr const char_type *select(
                _In_opt_z_ const char *n,
                _In_opt_z_ const wchar_t *w) {
            return w;
        }
    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */


/// <summary>
/// Generates a literal string <paramref name="l" />, which is either ASCII or
/// Unicode depending on the template parameter <paramref name="T" />.
/// </summary>
#define POWER_OVERWHELMING_TPL_LITERAL(T, l)\
    visus::power_overwhelming::detail::literal_selector<T>::select(l, L##l)
