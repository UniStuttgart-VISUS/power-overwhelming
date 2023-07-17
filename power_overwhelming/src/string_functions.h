// <copyright file="string_functions.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <algorithm>
#include <cassert>
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


namespace visus {
namespace power_overwhelming {
namespace detail {

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
    /// <exception cref="std::bad_alloc">If the memory for
    /// <paramref name="dst" /> could not be allocated.</exception>
    /// <returns><paramref name="dst" />.</returns>
    template<class TChar>
    blob& safe_assign(_Inout_ blob& dst, _In_opt_z_ const TChar *src);

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
    /// <exception cref="std::bad_alloc">If the memory for
    /// <paramref name="dst" /> could not be allocated.</exception>
    /// <returns><paramref name="dst" />.</returns>
    template<class TChar, class TTraits, class TAlloc>
    inline blob& safe_assign(_Inout_ blob& dst,
            _In_opt_z_ const std::basic_string<TChar, TTraits, TAlloc>& src) {
        return safe_assign(dst, src.c_str());
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
    /// <param name="src">The string variable to duplicated. The memory returned
    /// must be released using <see cref="free" />. It is safe to pass
    /// <c>nullptr</c>.</param>
    /// <exception cref="std::bad_alloc">If the memory for
    /// <paramref name="dst" /> could not be allocated.</exception>
    _Ret_maybenull_z_ POWER_OVERWHELMING_API char *safe_duplicate(
        _In_opt_z_ const char *src);

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */

#include "string_functions.inl"
