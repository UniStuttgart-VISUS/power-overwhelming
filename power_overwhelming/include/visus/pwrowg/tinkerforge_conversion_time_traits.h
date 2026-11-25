// <copyright file="tinkerforge_conversion_time_traits.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_TINKERFORGE_CONVERSION_TIME_TRAITS_H)
#define _PWROWG_TINKERFORGE_CONVERSION_TIME_TRAITS_H
#pragma once

#include <chrono>

#include "visus/pwrowg/tinkerforge_conversion_time.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Allows for reasoning about the conversion time of a Tinkerforge ADC in
/// absolute terms.
/// </summary>
/// <typeparam name="Time">The conversion time from the enumerated type.
/// </typeparam>
template<tinkerforge_conversion_time Time>
struct tinkerforge_conversion_time_traits;

/// <summary>
/// Specialise for <see cref="tinkerforge_conversion_time::microseconds_140" />.
/// </summary>
template<> struct tinkerforge_conversion_time_traits<
        tinkerforge_conversion_time::microseconds_140> {

    /// <summary>
    /// The numeric value of the conversion time.
    /// </summary>
    static constexpr std::chrono::microseconds value { 140 };
};

/// <summary>
/// Specialise for <see cref="tinkerforge_conversion_time::microseconds_204" />.
/// </summary>
template<> struct tinkerforge_conversion_time_traits<
        tinkerforge_conversion_time::microseconds_204> {

    /// <summary>
    /// The numeric value of the conversion time.
    /// </summary>
    static constexpr std::chrono::microseconds value{ 204 };
};

/// <summary>
/// Specialise for <see cref="tinkerforge_conversion_time::microseconds_332" />.
/// </summary>
template<> struct tinkerforge_conversion_time_traits<
        tinkerforge_conversion_time::microseconds_332> {

    /// <summary>
    /// The numeric value of the conversion time.
    /// </summary>
    static constexpr std::chrono::microseconds value{ 332 };
};

/// <summary>
/// Specialise for <see cref="tinkerforge_conversion_time::microseconds_588" />.
/// </summary>
template<> struct tinkerforge_conversion_time_traits<
        tinkerforge_conversion_time::microseconds_588> {

    /// <summary>
    /// The numeric value of the conversion time.
    /// </summary>
    static constexpr std::chrono::microseconds value{ 588 };
};

/// <summary>
/// Specialise for <see cref="tinkerforge_conversion_time::milliseconds_1_1" />.
/// </summary>
template<> struct tinkerforge_conversion_time_traits<
        tinkerforge_conversion_time::milliseconds_1_1> {

    /// <summary>
    /// The numeric value of the conversion time.
    /// </summary>
    static constexpr std::chrono::microseconds value { 1100 };
};

/// <summary>
/// Specialise for
/// <see cref="tinkerforge_conversion_time::milliseconds_2_116" />.
/// </summary>
template<> struct tinkerforge_conversion_time_traits<
        tinkerforge_conversion_time::milliseconds_2_116> {

    /// <summary>
    /// The numeric value of the conversion time.
    /// </summary>
    static constexpr std::chrono::microseconds value { 2116 };
};

/// <summary>
/// Specialise for
/// <see cref="tinkerforge_conversion_time::milliseconds_4_156" />.
/// </summary>
template<> struct tinkerforge_conversion_time_traits<
        tinkerforge_conversion_time::milliseconds_4_156> {

    /// <summary>
    /// The numeric value of the conversion time.
    /// </summary>
    static constexpr std::chrono::microseconds value { 4156 };
};

/// <summary>
/// Specialise for
/// <see cref="tinkerforge_conversion_time::milliseconds_8_244" />.
/// </summary>
template<> struct tinkerforge_conversion_time_traits<
        tinkerforge_conversion_time::milliseconds_8_244> {

    /// <summary>
    /// The numeric value of the conversion time.
    /// </summary>
    static constexpr std::chrono::microseconds value { 8244 };
};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_TINKERFORGE_CONVERSION_TIME_TRAITS_H) */
