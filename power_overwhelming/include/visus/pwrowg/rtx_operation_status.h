// <copyright file="rtx_operation_status.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_RTX_OPERATION_STATUS_H)
#define _PWROWG_RTX_OPERATION_STATUS_H
#pragma once

#include <cinttypes>
#include <type_traits>

#include "visus/pwrowg/api.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Defines the semantics of the bits in the operation status condition
/// register.
/// </summary>
enum class rtx_operation_status : std::uint16_t {

    /// <summary>
    /// Indicates that no bit is set.
    /// </summary>
    none = 0x00,

    /// <summary>
    /// Indicates that the instrument is performing a self-alignment.
    /// </summary>
    alignment = 0x01,

    /// <summary>
    /// Indicates that the instrument is performing a self-test.
    /// </summary>
    self_test = 0x02,

    /// <summary>
    /// Indicates that the instrument is performing an automatic setup.
    /// </summary>
    auto_set = 0x04,

    /// <summary>
    /// The instrument is waiting for a trigger event to occur.
    /// </summary>
    waiting = 0x08,
};


/// <summary>
/// Performs a bitwise combination of the given
/// <see cref="rtx_operation_status" />s.
/// </summary>
/// <param name="lhs">The left-hand side operand.</param>
/// <param name="rhs">The right-hand side operand.</param>
/// <returns>The combined operation status bits.</returns>
inline rtx_operation_status operator |(
        _In_ const rtx_operation_status lhs,
        _In_ const rtx_operation_status rhs) {
    typedef std::decay<decltype(lhs)>::type enum_type;
    auto l = static_cast<std::underlying_type<enum_type>::type>(lhs);
    auto r = static_cast<std::underlying_type<enum_type>::type>(rhs);
    return static_cast<enum_type>(l | r);
}


/// <summary>
/// Performs a bitwise intersection of the given
/// <see cref="rtx_operation_status" />s.
/// </summary>
/// <param name="lhs">The left-hand side operand.</param>
/// <param name="rhs">The right-hand side operand.</param>
/// <returns>The intersected operation status bits.</returns>
inline rtx_operation_status operator &(
        _In_ const rtx_operation_status lhs,
        _In_ const rtx_operation_status rhs) {
    typedef std::decay<decltype(lhs)>::type enum_type;
    auto l = static_cast<std::underlying_type<enum_type>::type>(lhs);
    auto r = static_cast<std::underlying_type<enum_type>::type>(rhs);
    return static_cast<enum_type>(l & r);
}


/// <summary>
/// Invers the given <see cref="rtx_operation_status" /> flags.
/// </summary>
/// <param name="status">The flags to invert.</param>
/// <returns>The inverse of <paramref name="status" />.</returns>
inline rtx_operation_status operator ~(
        _In_ const rtx_operation_status status) {
    typedef std::decay<decltype(status)>::type enum_type;
    auto s = static_cast<std::underlying_type<enum_type>::type>(status);
    return static_cast<enum_type>(~s);
}


/// <summary>
/// Answer whether the intersection between <paramref name="lhs" /> and
/// <paramref name="rhs" /> is not empty.
/// </summary>
/// <param name="lhs">The left-hand side operand.</param>
/// <param name="rhs">The right-hand side operand.</param>
/// <returns><c>true</c> if both operands have at least one bit in common,
/// <c>false</c> otherwise.</returns>
inline bool operator &&(_In_ const rtx_operation_status lhs,
        _In_ const rtx_operation_status rhs) {
    typedef std::decay<decltype(lhs)>::type enum_type;
    auto l = static_cast<std::underlying_type<enum_type>::type>(lhs);
    auto r = static_cast<std::underlying_type<enum_type>::type>(rhs);
    return ((l & r) != 0);
}

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_RTX_OPERATION_STATUS_H) */
