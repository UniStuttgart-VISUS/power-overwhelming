// <copyright file="friendly_timestamp.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT License. See LICENCE.txt for further details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_FRIENDLY_TIMESTAMP_H)
#define _PWROWG_FRIENDLY_TIMESTAMP_H
#pragma once

#include <string>
#include <stdexcept>

#include "visus/pwrowg/api.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Generates a human-readable UTC timestamp in the format
/// &quot;YYYYMMDDhhmmss&quot;.
/// </summary>
/// <param name="dst"></param>
/// <param name="cnt"></param>
/// <returns><see langword="true" /> if <paramref name="dst" /> was big enough
/// to hold the timestamp, <see langword="false" /> if <paramref name="dst" />
/// is invalid.</returns>
_Check_return_ bool PWROWG_TEST_API friendly_timestamp(
    _Out_writes_(cnt) wchar_t *dst,
    _In_ const std::size_t cnt);

/// <summary>
/// Generates a human-readable UTC timestamp in the format
/// &quot;YYYYMMDDhhmmss&quot;.
/// </summary>
/// <param name="dst"></param>
/// <param name="cnt"></param>
/// <returns><see langword="true" /> if <paramref name="dst" /> was big enough
/// to hold the timestamp, <see langword="false" /> if <paramref name="dst" />
/// is invalid.</returns>
_Check_return_ bool PWROWG_TEST_API friendly_timestamp(
    _Out_writes_(cnt) char *dst,
    _In_ const std::size_t cnt);

/// <summary>
/// Generates a human-readable UTC timestamp in the format
/// &quot;YYYYMMDDhhmmss&quot;.
/// </summary>
/// <typeparam name="TChar">The type of character to create the timestamp in.
/// </typeparam>
/// <returns>The timestamp string.</returns>
template<class TChar>
std::basic_string<TChar> friendly_timestamp() {
    std::basic_string<TChar> retval(8 + 6, static_cast<TChar>(0));
    if (friendly_timestamp(&retval[0], retval.size() + 1)) {
        return retval;
    } else {
        throw std::logic_error("The timestamp format seems to have changed "
            "as the friendly timestamp does not have the expected length.");
    }
}

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_FRIENDLY_TIMESTAMP_H) */
