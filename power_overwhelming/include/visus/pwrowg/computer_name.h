﻿// <copyright file="computer_name.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_COMPUTER_NAME_H)
#define _PWROWG_COMPUTER_NAME_H
#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "visus/pwrowg/api.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Answer the name of the computer the calling code is running on.
/// </summary>
/// <remarks>
/// Call with <c>nullptr</c> and a buffer size of zero to determine the
/// required buffer size and call again with the actual buffer.
/// </remarks>
/// <param name="dst">Receives the name of the computer if not
/// <c>nullptr</c>. On exit, this value is only to be considered
/// valid if the return value is less or equal to
/// <paramref name="cnt" />.</param>
/// <param name="cnt">The size of <paramref name="dst" /> in number of
/// characters.</param>
/// <returns>The required size of the <paramref name="dst" /> buffer to
/// store the computer name, including the terminating null.</returns>
/// <exception cref="std::system_error">In case the operation failed.
/// </exception>
std::size_t POWER_OVERWHELMING_API computer_name(
    _Out_writes_opt_z_(cnt) char *dst,
    _In_ const std::size_t cnt);

/// <summary>
/// Answer the name of the computer the calling code is running on.
/// </summary>
/// <remarks>
/// Call with <c>nullptr</c> and a buffer size of zero to determine the
/// required buffer size and call again with the actual buffer.
/// </remarks>
/// <param name="dst">Receives the name of the computer if not
/// <c>nullptr</c>. On exit, this value is only to be considered
/// valid if the return value is less or equal to
/// <paramref name="cnt" />.</param>
/// <param name="cnt">The size of <paramref name="dst" /> in number of
/// characters.</param>
/// <returns>The required size of the <paramref name="dst" /> buffer to
/// store the computer name, including the terminating null.</returns>
/// <exception cref="std::system_error">In case the operation failed.
/// </exception>
std::size_t POWER_OVERWHELMING_API computer_name(
    _Out_writes_opt_z_(cnt) wchar_t *dst,
    _In_ const std::size_t cnt);

/// <summary>
/// Answer the name of the computer the calling code is running on.
/// </summary>
/// <typeparam name="TChar">The type of the character to return, which can
/// be <c>char</c> or <c>whar_t</c>.</typeparam>
/// <returns>The computer name.</returns>
/// <exception cref="std::system_error">In case the operation failed.
/// </exception>
template<class TChar> inline std::basic_string<TChar> computer_name(void) {
    static constexpr auto np = static_cast<TChar *>(nullptr);
    std::vector<TChar> retval(computer_name(np, 0));
    computer_name(retval.data(), retval.size());
    return retval.data();
}

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_COMPUTER_NAME_H) */
