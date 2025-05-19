// <copyright file="csv_column.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_CSV_COLUMN_H)
#define _PWROWG_CSV_COLUMN_H
#pragma once

#include <cinttypes>
#include <cstring>
#include <type_traits>

#include "visus/pwrowg/api.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Identifies optional columns that can be written to CSV output.
/// </summary>
enum class csv_column : std::uint32_t {

    /// <summary>
    /// Print only the absolute minimum, which is the sensor index, the
    /// timestamp and the sensor reading.
    /// </summary>
    none,

    /// <summary>
    /// Print the unique ID.
    /// </summary>
    id = 0x00000001,

    /// <summary>
    /// Print the human-readable sensor name.
    /// </summary>
    name = 0x00000002,

    /// <summary>
    /// Print the user-defined label if any.
    /// </summary>
    label = 0x00000004
};


/// <summary>
/// Combines <paramref name="lhs" /> and <paramref name="rhs" />.
/// </summary>
/// <param name="lhs"></param>
/// <param name="rhs"></param>
/// <returns></returns>
inline constexpr csv_column operator |(_In_ const csv_column lhs,
        _In_ const csv_column rhs) {
    typedef typename std::decay<decltype(lhs)>::type enum_type;
    typedef typename std::underlying_type<enum_type>::type mask_type;
    const auto l = static_cast<mask_type>(lhs);
    const auto r = static_cast<mask_type>(rhs);
    return static_cast<decltype(lhs)>(l | r);
}


/// <summary>
/// Tests <paramref name="lhs" /> and <paramref name="rhs" /> for shared bits.
/// </summary>
/// <param name="lhs"></param>
/// <param name="rhs"></param>
/// <returns></returns>
inline constexpr csv_column operator &(_In_ const csv_column lhs,
        _In_ const csv_column rhs) {
    typedef typename std::decay<decltype(lhs)>::type enum_type;
    typedef typename std::underlying_type<enum_type>::type mask_type;
    const auto l = static_cast<mask_type>(lhs);
    const auto r = static_cast<mask_type>(rhs);
    return static_cast<decltype(lhs)>(l & r);
}

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_CSV_COLUMN_H) */
