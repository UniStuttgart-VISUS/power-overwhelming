// <copyright file="reading_unit.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 - 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_READING_UNIT_H)
#define _READING_UNIT_H
#pragma once

#include <cinttypes>
#include <cstdlib>
#include <string>

#include "visus/pwrowg/api.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Enumerates possible units used for <see cref="reading" />s.
/// </summary>
enum class reading_unit : std::uint32_t {

    /// <summary>
    /// The unit is unknown. Consult the documentation of the sensor for how the
    /// data need to be interpreted.
    /// </summary>
    unknown = 0,

    /// <summary>
    /// Ampère, the unit for current.
    /// </summary>
    ampere,

    /// <summary>
    /// Volt, the unit for voltage.
    /// </summary>
    volt,

    /// <summary>
    /// Watt, the unit for power.
    /// </summary>
    watt,

    /// <summary>
    /// Joule, the unit for energy.
    /// </summary>
    joule,

    /// <summary>
    /// Watt-hours, an alternative non-SI unit for energy.
    /// </summary>
    watt_hour,

    /// <summary>
    /// Coulomb, the unit for electric charge.
    /// </summary>
    coulomb,

    /// <summary>
    /// Ampere-hours, an alternative non-SI unit for electric charge.
    /// </summary>
    ampere_hour,

    /// <summary>
    /// Degrees Celsius for temperature.
    /// </summary>
    celsius,

    /// <summary>
    /// Kelvin for temperature.
    /// </summary>
    kelvin
};


/// <summary>
/// Converts a <see cref="reading_unit" /> to its SI unit symbol.
/// </summary>
/// <param name="dst">The buffer to receive the string representation. This
/// must be able to hold at least <paramref name="cnt" /> characters. This
/// parameter can be <see langword="nullptr" /> to measure the required size.
/// </param>
/// <param name="cnt">The number of characters that can be written to
/// <paramref name="dst" />.</param>
/// <param name="unit">The unit to be converted.</param>
/// <returns>The number of characters required to represent the unit, including
/// the null-terminator.</returns>
std::size_t POWER_OVERWHELMING_API to_string(
    _Out_writes_opt_z_(cnt) wchar_t *dst,
    _In_ std::size_t cnt,
    _In_ const reading_unit unit) noexcept;


/// <summary>
/// Converts a <see cref="reading_unit" /> to its SI unit symbol.
/// </summary>
/// <param name="dst">The buffer to receive the string representation. This
/// must be able to hold at least <paramref name="cnt" /> characters. This
/// parameter can be <see langword="nullptr" /> to measure the required size.
/// </param>
/// <param name="cnt">The number of characters that can be written to
/// <paramref name="dst" />.</param>
/// <param name="unit">The unit to be converted.</param>
/// <returns>The number of characters required to represent the unit, including
/// the null-terminator.</returns>
std::size_t POWER_OVERWHELMING_API to_string(
    _Out_writes_opt_z_(cnt) char *dst,
    _In_ std::size_t cnt,
    _In_ const reading_unit unit) noexcept;


/// <summary>
/// Converts a <see cref="reading_unit" /> to its SI unit symbol.
/// </summary>
/// <typeparam name="TChar">The character unit, which must be one of
/// <see langword="char" /> or <see langword="wchar_t" />.</typeparam>
/// <param name="unit">The unit to be converted.</param>
/// <returns>The unit symbol.</returns>
template<class TChar>
std::basic_string<TChar> to_string(const reading_unit unit) {
    constexpr auto n = static_cast<TChar *>(nullptr);
    std::basic_string<TChar> retval(to_string(n, 0, unit), 0);
    to_string(&retval[0], retval.size() + 1, unit);
    return retval;
}

PWROWG_NAMESPACE_END

#endif /* !defined(_READING_UNIT_H) */
