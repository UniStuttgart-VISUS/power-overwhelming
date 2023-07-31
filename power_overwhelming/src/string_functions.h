// <copyright file="string_functions.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <algorithm>
#include <cassert>
#include <cctype>
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cwchar>
#include <memory>
#include <stdexcept>
#include <string>
#include <system_error>
#include <type_traits>
#include <vector>

#include "power_overwhelming/blob.h"
#include "power_overwhelming/literal.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// Tests two strings for equality.
    /// </summary>
     /// <remarks>
    /// This function is only exported from the library for testing purposes.
    /// </remarks>
    /// <param name="lhs">The left-hand side string. It is safe to
    /// pass <c>nullptr</c>, in which case the result will only be <c>true</c>
    /// if <paramref name="lhs" /> and <paramref name="rhs" /> are both
    /// <c>nullptr.</c></param>
    /// <param name="rhs">The right-hand side string. It is safe to
    /// pass <c>nullptr</c>, in which case the result will only be <c>true</c>
    /// if <paramref name="lhs" /> and <paramref name="rhs" /> are both
    /// <c>nullptr.</c></param>
    /// <param name="ignore_case">If <c>true</c>, consider both strings equal if
    /// they only differ in case. If <c>false</c>, which is the default, both
    /// strings must match exactly.</param>
    /// <returns><c>true</c> if both strings are equal, <c>false</c> otherwise.
    /// </returns>
    POWER_OVERWHELMING_API bool equals(_In_opt_z_ const char *lhs,
        _In_opt_z_ const char *rhs, _In_ const bool ignore_case = false);

    /// <summary>
    /// Tests two strings for equality.
    /// </summary>
     /// <remarks>
    /// This function is only exported from the library for testing purposes.
    /// <param name="lhs">The left-hand side string. It is safe to
    /// pass <c>nullptr</c>, in which case the result will only be <c>true</c>
    /// if <paramref name="lhs" /> and <paramref name="rhs" /> are both
    /// <c>nullptr.</c></param>
    /// <param name="rhs">The right-hand side string. It is safe to
    /// pass <c>nullptr</c>, in which case the result will only be <c>true</c>
    /// if <paramref name="lhs" /> and <paramref name="rhs" /> are both
    /// <c>nullptr.</c></param>
    /// <param name="ignore_case">If <c>true</c>, consider both strings equal if
    /// they only differ in case. If <c>false</c>, which is the default, both
    /// strings must match exactly.</param>
    /// <returns><c>true</c> if both strings are equal, <c>false</c> otherwise.
    /// </returns>
    POWER_OVERWHELMING_API bool equals(_In_opt_z_ const wchar_t *lhs,
        _In_opt_z_ const wchar_t *rhs, _In_ const bool ignore_case = false);


    /// <summary>
    /// Tests two strings for equality.
    /// </summary>
    /// <typeparam name="TChar">The type of a character in the string.
    /// </typeparam>
    /// <typeparam name="TTraits">The type of a character traits.</typeparam>
    /// <typeparam name="TAlloc">The allocator of the string.</typeparam>
    /// <param name="lhs">The left-hand side string.</param>
    /// <param name="rhs">The right-hand side string. It is safe to pass
    /// <c>nullptr</c>, in which case the result will always be <c>false</c>.
    /// </param>
    /// <param name="ignore_case">If <c>true</c>, consider both strings equal if
    /// they only differ in case. If <c>false</c>, which is the default, both
    /// strings must match exactly.</param>
    /// <returns><c>true</c> if both strings are equal, <c>false</c> otherwise.
    /// </returns>
    template<class TChar, class TTraits, class TAlloc>
    inline bool equals(
            _In_ const std::basic_string<TChar, TTraits, TAlloc>& lhs,
            _In_opt_z_ const TChar *rhs,
            _In_ const bool ignore_case = false) {
        return ((rhs != nullptr) && equals(lhs.c_str(), rhs, ignore_case));
    }

    /// <summary>
    /// Tests two strings for equality.
    /// </summary>
    /// <typeparam name="TChar">The type of a character in the string.
    /// </typeparam>
    /// <typeparam name="TTraits">The type of a character traits.</typeparam>
    /// <typeparam name="TAlloc">The allocator of the string.</typeparam>
    /// <param name="lhs">The left-hand side string. It is safe to pass
    /// <c>nullptr</c>, in which case the result will always be <c>false</c>.
    /// </param>
    /// <param name="rhs">The right-hand side string.</param>
    /// <param name="ignore_case">If <c>true</c>, consider both strings equal if
    /// they only differ in case. If <c>false</c>, which is the default, both
    /// strings must match exactly.</param>
    /// <returns><c>true</c> if both strings are equal, <c>false</c> otherwise.
    /// </returns>
    template<class TChar, class TTraits, class TAlloc>
    inline bool equals(
            _In_opt_z_ const TChar *lhs,
            _In_ const std::basic_string<TChar, TTraits, TAlloc>& rhs,
            _In_ const bool ignore_case = false) {
        return ((lhs != nullptr) && equals(lhs, rhs.c_str(), ignore_case));
    }

    /// <summary>
    /// Tests two strings for equality.
    /// </summary>
    /// <typeparam name="TChar">The type of a character in the string.
    /// </typeparam>
    /// <typeparam name="TTraits">The type of a character traits.</typeparam>
    /// <typeparam name="TAlloc">The allocator of the string.</typeparam>
    /// <param name="lhs">The left-hand side string.</param>
    /// <param name="rhs">The right-hand side string.</param>
    /// <param name="ignore_case">If <c>true</c>, consider both strings equal if
    /// they only differ in case. If <c>false</c>, which is the default, both
    /// strings must match exactly.</param>
    /// <returns><c>true</c> if both strings are equal, <c>false</c> otherwise.
    /// </returns>
    template<class TChar, class TTraits, class TAlloc>
    inline bool equals(
            _In_ const std::basic_string<TChar, TTraits, TAlloc>& lhs,
            _In_ const std::basic_string<TChar, TTraits, TAlloc>& rhs,
            _In_ const bool ignore_case = false) {
        return equals(lhs.c_str(), rhs.c_str(), ignore_case);
    }

    /// <summary>
    /// Format the given string into a new string.
    /// </summary>
    /// <typeparam name="TArgs">The list of arguments used to replace the
    /// placeholders in <paramref name="fmt" />.</typeparam>
    /// <param name="format">The <see cref="printf" />-style format string.
    /// </param>
    /// <param name="args">The arguments used to replace the placeholders in
    /// <paramref name="format" />.</param>
    /// <returns>The formatted string.</returns>
    template<class... TArgs>
    std::wstring format_string(_In_z_ const wchar_t *format, TArgs&&... args);

    /// <summary>
    /// Format the given string into a new string.
    /// </summary>
    /// <typeparam name="TArgs">The list of arguments used to replace the
    /// placeholders in <paramref name="fmt" />.</typeparam>
    /// <param name="format">The <see cref="printf" />-style format string.
    /// </param>
    /// <param name="args">The arguments used to replace the placeholders in
    /// <paramref name="format" />.</param>
    /// <returns>The formatted string.</returns>
    template<class... TArgs>
    std::string format_string(_In_z_ const char *format, TArgs&&... args);

    /// <summary>
    /// Parse the given text as floating-point number.
    /// </summary>
    /// <remarks>
    /// This function is only exported from the library for testing purposes.
    /// </remarks>
    /// <param name="str">The string to be parsed.</param>
    /// <returns>The number represented by the given string or zero in case
    /// the string does not represent a number.</returns>
    POWER_OVERWHELMING_API float parse_float(_In_opt_z_ const char *str);

    /// <summary>
    /// Parse the given text as signed integer number.
    /// </summary>
    /// <remarks>
    /// This function is only exported from the library for testing purposes.
    /// </remarks>
    /// <param name="str">The string to be parsed.</param>
    /// <returns>The number represented by the given string or zero in case
    /// the string does not represent a number.</returns>
    POWER_OVERWHELMING_API int parse_int(_In_opt_z_ const char *str);

    /// <summary>
    /// Parse the given text as unsigned integer number.
    /// </summary>
    /// <remarks>
    /// This function is only exported from the library for testing purposes.
    /// </remarks>
    /// <param name="str">The string to be parsed.</param>
    /// <returns>The number represented by the given string or zero in case
    /// the string does not represent a number.</returns>
    POWER_OVERWHELMING_API unsigned int parse_uint(_In_opt_z_ const char *str);

    /// <summary>
    /// Remove all white-space characters from <paramref name="str" />.
    /// </summary>
    /// <typeparam name="TChar">The type of a character in the string.
    /// </typeparam>
    /// <typeparam name="TTraits">The type of a character traits.</typeparam>
    /// <typeparam name="TAlloc">The allocator of the string.</typeparam>
    /// <param name="str">The string to remove all white-space characters from.
    /// </param>
    /// <returns>A copy of <paramref name="str" /> without white-space
    /// characters.</returns>
    template<class TChar, class TTraits, class TAlloc>
    std::basic_string<TChar> remove_spaces(
        _In_ const std::basic_string<TChar, TTraits, TAlloc>& str);

    /// <summary>
    /// Frees <paramref name="dst" />, if not <c>nullptr</c>, and assigns a copy
    /// of <paramref name="src" /> to it.
    /// </summary>
    /// <remarks>
    /// <para>This is a utility API for managing strings visible in the public
    /// API of the library. It is only exported for testing purposes.</para>
    /// <para>It is safe to assign a string to itself. Nothing will happen in
    /// this case.</para>
    /// </remarks>
    /// <typeparam name="TChar">The type of the characters.</typeparam>
    /// <param name="dst">The string variable to receive the copy of
    /// <paramref name="src" />. If not <c>nullptr</c>, it is assumed that this
    /// string has been allocated on the heap using <see cref="malloc /">.</param>
    /// <param name="src">The string to be copied. It is safe to pass
    /// <c>nullptr</c>.</param>
    /// <exception cref="std::bad_alloc">If the memory for
    /// <paramref name="dst" /> could not be allocated.</exception>
    template<class TChar>
    void safe_assign(_Inout_opt_z_ TChar *& dst, _In_opt_z_ const TChar *src);

    /// <summary>
    /// Frees <paramref name="dst" /> if necessary, moves
    /// <paramref name="src" /> to this variable and sets the source
    /// <c>nullptr</c>.
    /// </summary>
    /// <remarks>
    /// <para>This is a utility API for managing strings visible in the public
    /// API of the library. It is only exported for testing purposes.</para>
    /// <para>It is safe to assign a string to itself. Nothing will happen in
    /// this case.</para>
    /// </remarks>
    /// <typeparam name="TChar">The type of the characters.</typeparam>
    /// <param name="dst">The string variable to receive 
    /// <paramref name="src" />. If not <c>nullptr</c>, it is assumed that this
    /// string has been allocated on the heap using <see cref="malloc /">.
    /// </param>
    /// <param name="src">The pointer to be moved. If not <c>nullptr</c>, this
    /// string must have been allocated on the heap using <see cref="malloc" />.
    /// </param>
    template<class TChar> void safe_assign(_Inout_opt_z_ TChar *& dst,
        _Inout_opt_z_ TChar *&& src) noexcept;

    /// <summary>
    /// Frees <paramref name="dst" />, if not <c>nullptr</c>, and assigns a copy
    /// of <paramref name="src" /> to it.
    /// </summary>
    /// <remarks>
    /// <para>This is a utility API for managing strings visible in the public
    /// API of the library. It is only exported for testing purposes.</para>
    /// </remarks>
    /// <typeparam name="TChar">The type of the characters.</typeparam>
    /// <typeparam name="TTraits">The type of a character traits.</typeparam>
    /// <typeparam name="TAlloc">The allocator of the string.</typeparam>
    /// <param name="dst">The string variable to receive the copy of
    /// <paramref name="src" />. If not <c>nullptr</c>, it is assumed that this
    /// string has been allocated on the heap using <see cref="malloc /">.</param>
    /// <param name="src">The string to be copied.</param>
    /// <exception cref="std::bad_alloc">If the memory for
    /// <paramref name="dst" /> could not be allocated.</exception>
    template<class TChar, class TTraits, class TAlloc>
    inline void safe_assign(_Inout_opt_z_ TChar *& dst,
            _In_ const std::basic_string<TChar, TTraits, TAlloc>& src) {
        safe_assign(dst, src.c_str());
    }

    /// <summary>
    /// Copy a string into a <see cref="blob" />.
    /// </summary>
    /// <typeparam name="TChar">The type of the characters.</typeparam>
    /// <param name="dst">The blob variable to receive the copy of
    /// <paramref name="src" />. The blob will be resized to be able to hold
    /// the whole <paramref name="src" />.</param>
    /// <param name="src">The string to be copied.</param>
    /// <returns><see cref="dst" />.</returns>
    /// <exception cref="std::bad_alloc">If the memory for
    /// <paramref name="dst" /> could not be allocated.</exception>
    /// <returns><paramref name="dst" />.</returns>
    template<class TChar>
    blob& safe_assign(_Inout_ blob& dst, _In_opt_z_ const TChar *src);

    /// <summary>
    /// Copy a string into a <see cref="blob" />.
    /// </summary>
    /// <typeparam name="TChar">The type of the characters.</typeparam>
    /// <param name="dst">The blob variable to receive the copy of
    /// <paramref name="src" />. The blob will be resized to be able to hold
    /// the whole <paramref name="src" />.</param>
    /// <param name="src">The string to be copied.</param>
    /// <returns><see cref="dst" />.</returns>
    /// <exception cref="std::bad_alloc">If the memory for
    /// <paramref name="dst" /> could not be allocated.</exception>
    /// <returns><paramref name="dst" />.</returns>
    template<class TChar>
    blob safe_assign(_Inout_ blob&& dst, _In_opt_z_ const TChar *src);

    /// <summary>
    /// Copy a string into a <see cref="blob" />.
    /// </summary>
    /// <typeparam name="TChar">The type of the characters.</typeparam>
    /// <typeparam name="TTraits">The type of a character traits.</typeparam>
    /// <typeparam name="TAlloc">The allocator of the string.</typeparam>
    /// <param name="dst">The blob variable to receive the copy of
    /// <paramref name="src" />. The blob will be resized to be able to hold
    /// the whole <paramref name="src" />.</param>
    /// <param name="src">The string to be copied.</param>
    /// <returns><see cref="dst" />.</returns>
    /// <exception cref="std::bad_alloc">If the memory for
    /// <paramref name="dst" /> could not be allocated.</exception>
    /// <returns><paramref name="dst" />.</returns>
    template<class TChar, class TTraits, class TAlloc>
    inline blob& safe_assign(_Inout_ blob& dst,
            _In_opt_z_ const std::basic_string<TChar, TTraits, TAlloc>& src) {
        return safe_assign(dst, src.c_str());
    }

    /// <summary>
    /// Copy a string into a <see cref="blob" />.
    /// </summary>
    /// <typeparam name="TChar">The type of the characters.</typeparam>
    /// <typeparam name="TTraits">The type of a character traits.</typeparam>
    /// <typeparam name="TAlloc">The allocator of the string.</typeparam>
    /// <param name="dst">The blob variable to receive the copy of
    /// <paramref name="src" />. The blob will be resized to be able to hold
    /// the whole <paramref name="src" />.</param>
    /// <param name="src">The string to be copied.</param>
    /// <returns><see cref="dst" />.</returns>
    /// <exception cref="std::bad_alloc">If the memory for
    /// <paramref name="dst" /> could not be allocated.</exception>
    /// <returns><paramref name="dst" />.</returns>
    template<class TChar, class TTraits, class TAlloc>
    inline blob safe_assign(_Inout_ blob&& dst,
            _In_opt_z_ const std::basic_string<TChar, TTraits, TAlloc>& src) {
        return safe_assign(std::move(dst), src.c_str());
    }

    /// <summary>
    /// Frees <paramref name="dst" />.
    /// </summary>
    /// <typeparam name="TChar">The type of the characters.</typeparam>
    /// <param name="dst">The string variable to be freed. If not
    /// <c>nullptr</c>, the memory for this string must have been allocated on
    /// the heap using <see cref="malloc" />.</param>
    /// <param name="src">A <c>nullptr</c>.</param>
    template<class TChar> void safe_assign(_Inout_opt_z_ TChar *& dst,
        _In_ const std::nullptr_t src) noexcept;

    /// <summary>
    /// Duplicates <paramref name="src" />.
    /// </summary>
    /// <remarks>
    /// This function is only exported from the library for testing purposes.
    /// </remarks>
    /// <param name="src">The string variable to duplicated. The memory returned
    /// must be released using <see cref="free" />. It is safe to pass
    /// <c>nullptr</c>.</param>
    /// <exception cref="std::bad_alloc">If the memory for
    /// <paramref name="dst" /> could not be allocated.</exception>
    _Ret_maybenull_z_ POWER_OVERWHELMING_API wchar_t *safe_duplicate(
        _In_opt_z_ const wchar_t *src);

    /// <summary>
    /// Duplicates <paramref name="src" />.
    /// </summary>
    /// <remarks>
    /// This function is only exported from the library for testing purposes.
    /// </remarks>
    /// <param name="src">The string variable to duplicated. The memory returned
    /// must be released using <see cref="free" />. It is safe to pass
    /// <c>nullptr</c>.</param>
    /// <exception cref="std::bad_alloc">If the memory for
    /// <paramref name="dst" /> could not be allocated.</exception>
    _Ret_maybenull_z_ POWER_OVERWHELMING_API char *safe_duplicate(
        _In_opt_z_ const char *src);

    /// <summary>
    /// Tests whether <paramref name="str" /> starts with
    ///  <paramref name="start" />.
    /// </summary>
     /// <remarks>
    /// This function is only exported from the library for testing purposes.
    /// </remarks>
    /// <param name="str">The string to be tested whether it starts with
    /// <paramref name="start" />. It is safe to pass <c>nullptr</c>, in which
    /// case the result will always be <c>true</c> only if
    /// <paramref name="start" /> is also <c>nullptr</c>.</param>
    /// <param name="start">The string to be searched at the begin of
    /// <paramref name="str" />. It is safe to pass <c>nullptr</c>, in which
    /// case the result will always be <c>true</c>.</param>
    /// <param name="ignore_case">If <c>true</c>, consider the prefix equal if
    /// the strings only differ in case. If <c>false</c>, which is the default,
    /// both strings must match exactly.</param>
    /// <returns><c>true</c> if both strings are equal, <c>false</c> otherwise.
    /// </returns>
    POWER_OVERWHELMING_API bool starts_with(_In_opt_z_ const char *str,
        _In_opt_z_ const char *start, _In_ const bool ignore_case = false);

    /// <summary>
    /// Tests whether <paramref name="str" /> starts with
    ///  <paramref name="start" />.
    /// </summary>
     /// <remarks>
    /// This function is only exported from the library for testing purposes.
    /// </remarks>
    /// <param name="str">The string to be tested whether it starts with
    /// <paramref name="start" />. It is safe to pass <c>nullptr</c>, in which
    /// case the result will always be <c>true</c> only if
    /// <paramref name="start" /> is also <c>nullptr</c>.</param>
    /// <param name="start">The string to be searched at the begin of
    /// <paramref name="str" />. It is safe to pass <c>nullptr</c>, in which
    /// case the result will always be <c>true</c>.</param>
    /// <param name="ignore_case">If <c>true</c>, consider the prefix equal if
    /// the strings only differ in case. If <c>false</c>, which is the default,
    /// both strings must match exactly.</param>
    /// <returns><c>true</c> if both strings are equal, <c>false</c> otherwise.
    /// </returns>
    POWER_OVERWHELMING_API bool starts_with(_In_opt_z_ const wchar_t *str,
        _In_opt_z_ const wchar_t *start, _In_ const bool ignore_case = false);

    /// <summary>
    /// Determine the first character in the given string for which
    /// <paramref name="predicate" /> does not hold any more. If this pointer is
    /// used as the new start of the string, all characters at the begin for
    /// which the <paramref name="predicate" /> holds are trimmed away.
    /// </summary>
    /// <typeparam name="TChar">The type of the character in the string.
    /// </typeparam>
    /// <typeparam name="TPredicate">The type of the predicate functor, which
    /// must take a character of type <typeparamref name="TChar" /> and return a
    /// <c>bool</c>.</typeparam>
    /// <param name="str">The string to be trimmed. It is safe to pass
    /// <c>nullptr</c>, in which case the result will be <c>nullptr</c>, too.
    /// </param>
    /// <param name="predicate">The predicate that all characters that are to be
    /// removed must fulfil.</param>
    /// <returns>A pointer to the first character for which
    /// <paramref name="predicate" /> does not hold any more.</returns>
    template<class TChar, class TPredicate>
    _When_(str != nullptr, _Ret_z_) _When_(str == nullptr, _Ret_null_)
    TChar *trim_begin_if(_In_opt_z_ TChar *str,
        _In_ const TPredicate& predicate);

    /// <summary>
    /// Determine the first non-white space character from the begin of the
    /// given string. If this pointer is used as the start of the new string,
    /// all spaces have been trimmed from the end.
    /// </summary>
    /// <typeparam name="TChar">The type of the character in the string.
    /// </typeparam>
    /// <param name="str">The string to be trimmed. It is safe to pass
    /// <c>nullptr</c>, in which case the result will be <c>nullptr</c>, too.
    /// </param>
    /// <returns>A pointer to the first non-white space character.</returns>
    template<class TChar>
    _When_(str != nullptr, _Ret_z_) _When_(str == nullptr, _Ret_null_)
    inline TChar *trim_begin(_In_opt_z_ TChar *str) {
        return trim_begin_if(str, [](const TChar c) {
            return std::isspace(c);
        });
    }

    /// <summary>
    /// Determine the last character from the end of the given string for which
    /// <paramref name="predicate" /> does still hold. If this pointer is used
    /// as the new end of the string, all characters at the end for which the
    /// <paramref name="predicate" /> holds are trimmed away.
    /// </summary>
    /// <typeparam name="TChar">The type of the character in the string.
    /// </typeparam>
    /// <typeparam name="TPredicate">The type of the predicate functor, which
    /// must take a character of type <typeparamref name="TChar" /> and return a
    /// <c>bool</c>.</typeparam>
    /// <param name="str">The string to be trimmed. It is safe to pass
    /// <c>nullptr</c>, in which case the result will be <c>nullptr</c>, too.
    /// </param>
    /// <param name="predicate">The predicate that all characters that are to be
    /// removed must fulfil.</param>
    /// <returns>A pointer to the last character from the end for which the
    /// <paramref name="predicate" /> still holds.</returns>
    template<class TChar, class TPredicate>
    _When_(str != nullptr, _Ret_z_) _When_(str == nullptr, _Ret_null_)
    TChar *trim_end_if(_In_opt_z_ TChar *str, _In_ const TPredicate& predicate);

    /// <summary>
    /// Determine the last whitespace character from the end of the given
    /// string. If this pointer is used as the end of the new string, all spaces
    /// have been trimmed from the end.
    /// </summary>
    /// <typeparam name="TChar">The type of the character in the string.
    /// </typeparam>
    /// <param name="str">The string to be trimmed. It is safe to pass
    /// <c>nullptr</c>, in which case the result will be <c>nullptr</c>, too.
    /// </param>
    /// <returns>A pointer to the last character from the end of the string that
    /// is a white space character.</returns>
    template<class TChar>
    _When_(str != nullptr, _Ret_z_) _When_(str == nullptr, _Ret_null_)
    inline TChar *trim_end(_In_opt_z_ TChar *str) {
        return trim_end_if(str, [](const TChar c) { return std::isspace(c); });
    }

    /// <summary>
    /// Terminates the given string at the first occurrence of a new line.
    /// </summary>
    /// <typeparam name="TChar">The type of the character in the string.
    /// </typeparam>
    /// <param name="str">The string to be trimmed. It is safe to pass
    /// <c>nullptr</c>, in which case nothing will be done.</param>
    template<class TChar> void trim_eol(_In_opt_z_ TChar *str);

    /// <summary>
    /// Removes all characters matching the given predicate from the begin and
    /// end of the given string.
    /// </summary>
    /// <typeparam name="TChar">The type of the character in the string.
    /// </typeparam>
    /// <typeparam name="TPredicate">The type of the predicate functor, which
    /// must take a character of type <typeparamref name="TChar" /> and return a
    /// <c>bool</c>.</typeparam>
    /// <param name="str">The string to be trimmed. It is safe to pass
    /// <c>nullptr</c>, in which case the result will be <c>nullptr</c>, too.
    /// </param>
    /// <param name="predicate">The predicate that all characters to be removed
    /// must fulfil.</param>
    /// <returns>A pointer to the first character in <paramref name="str" /> for
    /// which <paramref name="predicate" /> does not hold any more. The
    /// characters at the end will be trimmed by setting the null-terminating
    /// character accordingly.</returns>
    template<class TChar, class TPredicate>
    _When_(str != nullptr, _Ret_z_) _When_(str == nullptr, _Ret_null_)
    TChar *trim_if(_In_opt_z_ TChar *str, _In_ const TPredicate& predicate);

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */

#include "string_functions.inl"
