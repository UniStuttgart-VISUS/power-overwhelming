// <copyright file="tinkerforge_conversion_time_traits.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_TNKERFORGE_SAMPLE_AVERAGING_TRAITS_H)
#define _PWROWG_TNKERFORGE_SAMPLE_AVERAGING_TRAITS_H
#pragma once

#include <cstdlib>

#include "visus/pwrowg/tinkerforge_sample_averaging.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Allows for reasoning about the sample averaging of a Tinkerforge ADC in
/// absolute terms.
/// </summary>
/// <typeparam name="Avg">The sample averaging method from the enumerated type.
/// </typeparam>
template<tinkerforge_sample_averaging Avg>
struct tinkerforge_sample_averaging_traits;


/// <summary>
/// Specialise for <see cref="tinkerforge_sample_averaging::average_of_1" />.
/// </summary>
template<> struct tinkerforge_sample_averaging_traits<
        tinkerforge_sample_averaging::average_of_1> {

    /// <summary>
    /// The number of samples being averaged.
    /// </summary>
    static constexpr std::size_t value { 1 };
};


/// <summary>
/// Specialise for <see cref="tinkerforge_sample_averaging::average_of_4" />.
/// </summary>
template<> struct tinkerforge_sample_averaging_traits<
        tinkerforge_sample_averaging::average_of_4> {

    /// <summary>
    /// The number of samples being averaged.
    /// </summary>
    static constexpr std::size_t value { 4 };
};

/// <summary>
/// Specialise for <see cref="tinkerforge_sample_averaging::average_of_16" />.
/// </summary>
template<> struct tinkerforge_sample_averaging_traits<
        tinkerforge_sample_averaging::average_of_16> {

    /// <summary>
    /// The number of samples being averaged.
    /// </summary>
    static constexpr std::size_t value { 16 };
};

/// <summary>
/// Specialise for <see cref="tinkerforge_sample_averaging::average_of_64" />.
/// </summary>
template<> struct tinkerforge_sample_averaging_traits<
        tinkerforge_sample_averaging::average_of_64> {

    /// <summary>
    /// The number of samples being averaged.
    /// </summary>
    static constexpr std::size_t value { 64 };
};

/// <summary>
/// Specialise for <see cref="tinkerforge_sample_averaging::average_of_128" />.
/// </summary>
template<> struct tinkerforge_sample_averaging_traits<
        tinkerforge_sample_averaging::average_of_128> {

    /// <summary>
    /// The number of samples being averaged.
    /// </summary>
    static constexpr std::size_t value { 128 };
};

/// <summary>
/// Specialise for <see cref="tinkerforge_sample_averaging::average_of_256" />.
/// </summary>
template<> struct tinkerforge_sample_averaging_traits<
        tinkerforge_sample_averaging::average_of_256> {

    /// <summary>
    /// The number of samples being averaged.
    /// </summary>
    static constexpr std::size_t value { 256 };
};

/// <summary>
/// Specialise for <see cref="tinkerforge_sample_averaging::average_of_512" />.
/// </summary>
template<> struct tinkerforge_sample_averaging_traits<
        tinkerforge_sample_averaging::average_of_512> {

    /// <summary>
    /// The number of samples being averaged.
    /// </summary>
    static constexpr std::size_t value { 512 };
};

/// <summary>
/// Specialise for <see cref="tinkerforge_sample_averaging::average_of_1024" />.
/// </summary>
template<> struct tinkerforge_sample_averaging_traits<
        tinkerforge_sample_averaging::average_of_1024> {

    /// <summary>
    /// The number of samples being averaged.
    /// </summary>
    static constexpr std::size_t value { 1024 };
};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_TNKERFORGE_SAMPLE_AVERAGING_TRAITS_H) */
