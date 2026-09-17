// <copyright file="reading_type.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 - 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_READING_TYPE_H)
#define _READING_TYPE_H
#pragma once

#include <cinttypes>
#include <cstdlib>
#include <string>

#include "visus/pwrowg/api.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Defines how a 64-bit sensor reading has to be interpreted.
/// </summary>
enum class reading_type : std::uint32_t {

    /// <summary>
    /// The reading is an IEE-754 floating point number
    ///  (<see langword="float" />).
    /// </summary>
    floating_point,

    /// <summary>
    /// The reading is a signed integer.
    /// </summary>
    signed_integer,

    /// <summary>
    /// The reading is an unsigned integer.
    /// </summary>
    unsigned_integer
};


/// <summary>
/// Converts a <see cref="reading_type" /> to a human-readable string
/// representation.
/// </summary>
/// <param name="dst">The buffer to receive the string representation. This
/// must be able to hold at least <paramref name="cnt" /> characters. This
/// parameter can be <see langword="nullptr" /> to measure the required size.
/// </param>
/// <param name="cnt">The number of characters that can be written to
/// <paramref name="dst" />.</param>
/// <param name="type">The reading type to be converted.</param>
/// <returns>The number of characters required to represent the reading type,
/// including the null-terminator.</returns>
std::size_t POWER_OVERWHELMING_API to_string(
    _Out_writes_opt_z_(cnt) wchar_t *dst,
    _In_ std::size_t cnt,
    _In_ const reading_type type) noexcept;


/// <summary>
/// Converts a <see cref="reading_type" /> to a human-readable string
/// representation.
/// </summary>
/// <param name="dst">The buffer to receive the string representation. This
/// must be able to hold at least <paramref name="cnt" /> characters. This
/// parameter can be <see langword="nullptr" /> to measure the required size.
/// </param>
/// <param name="cnt">The number of characters that can be written to
/// <paramref name="dst" />.</param>
/// <param name="type">The reading type to be converted.</param>
/// <returns>The number of characters required to represent the reading type,
/// including the null-terminator.</returns>
std::size_t POWER_OVERWHELMING_API to_string(
    _Out_writes_opt_z_(cnt) char *dst,
    _In_ std::size_t cnt,
    _In_ const reading_type type) noexcept;


/// <summary>
/// Converts a <see cref="reading_type" /> to a human-readable string
/// representation.
/// </summary>
/// <typeparam name="TChar">The character type, which must be one of
/// <see langword="char" /> or <see langword="wchar_t" />.</typeparam>
/// <param name="type">The reading type to be converted.</param>
/// <returns>The string representation of the type.</returns>
template<class TChar>
std::basic_string<TChar> to_string(const reading_type type) {
    constexpr auto n = static_cast<TChar *>(nullptr);
    std::basic_string<TChar> retval(to_string(n, 0, type), 0);
    to_string(&retval[0], retval.size() + 1, type);
    return retval;
}

PWROWG_NAMESPACE_END

#endif /* !defined(_READING_TYPE_H) */
