// <copyright file="convert_string.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_CONVERT_STRING_H)
#define _PWROWG_CONVERT_STRING_H
#pragma once

#include <cassert>
#include <string>
#include <vector>

#include "visus/pwrowg/api.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

extern std::size_t POWER_OVERWHELMING_API convert_string(
    _Out_writes_opt_z_(cnt_output) char *output,
    _In_ const std::size_t cnt_output,
    _In_reads_or_z_(cnt_input) const wchar_t *input,
    _In_ const std::size_t cnt_input);

extern std::size_t POWER_OVERWHELMING_API convert_string(
    _Out_writes_opt_z_(cnt_output) wchar_t *output,
    _In_ const std::size_t cnt_output,
    _In_reads_or_z_(cnt_input) const char *input,
    _In_ const std::size_t cnt_input);

extern std::size_t POWER_OVERWHELMING_API convert_to_oem_string(
    _Out_writes_opt_z_(cnt_output) char* output,
    _In_ const std::size_t cnt_output,
    _In_reads_or_z_(cnt_input) const wchar_t* input,
    _In_ const int cnt_input);

PWROWG_DETAIL_NAMESPACE_END


PWROWG_NAMESPACE_BEGIN

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
    std::basic_string<TOutput>>::type
convert_string(_In_opt_z_ const TInput *str);

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
    std::basic_string<TOutput>>::type
convert_string(_In_opt_z_ const TInput *str);

/// <summary>
/// Converts a string to the given character set.
/// </summary>
/// <typeparam name="TOutput"></typeparam>
/// <typeparam name="TInput"></typeparam>
/// <typeparam name="TTraits"></typeparam>
/// <typeparam name="TAlloc"></typeparam>
/// <param name="str"></param>
/// <returns></returns>
template<class TOutput, class TInput, class TTraits, class TAlloc>
inline std::basic_string<TOutput> convert_string(
        _In_ const std::basic_string<TInput, TTraits, TAlloc>& str) {
    return convert_string<TOutput>(str.c_str());
}

/// <summary>
/// Performs an identity conversion between two strings of the same character
/// set.
/// </summary>
/// <typeparam name="TChar"></typeparam>
/// <param name="str"></param>
/// <returns></returns>
template<class TChar> inline const std::basic_string<TChar>& convert_string(
        _In_ const std::basic_string<TChar>& str) {
    return str;
}

/// <summary>
/// Converts the given wide string to the OEM code page of the Windows terminal.
/// </summary>
/// <param name="str">A non-<see langword="nullptr" /> string pointer.</param>
/// <returns></returns>
inline std::string convert_to_oem_string(_In_z_ const wchar_t* str) {
    const auto cnt = detail::convert_to_oem_string(nullptr, 0, str, -1);
    assert(cnt > 0);
    std::string retval(cnt - 1, '\0');
    detail::convert_to_oem_string(&retval[0], retval.size() + 1, str, -1);
    return retval;
}

PWROWG_NAMESPACE_END

#include "visus/pwrowg/convert_string.inl"

#endif /* !defined(_PWROWG_CONVERT_STRING_H) */
