// <copyright file="tinkerforge_conversion_time.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_TINKERFORGE_CONVERSION_TIME_H)
#define _PWROWG_TINKERFORGE_CONVERSION_TIME_H
#pragma once

#include <cinttypes>

#include "visus/pwrowg/api.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Possible conversion times for the Tinkerforge ADCs.
/// </summary>
enum class tinkerforge_conversion_time : std::uint8_t {

    /// <summary>
    /// A conversion time of 140 µs.
    /// </summary>
    microseconds_140 = 0,

    /// <summary>
    /// A conversion time of 204 µs.
    /// </summary>
    microseconds_204 = 1,

    /// <summary>
    /// A conversion time of 332 µs.
    /// </summary>
    microseconds_332 = 2,

    /// <summary>
    /// A conversion time of 588 µs.
    /// </summary>
    microseconds_588 = 3,

    /// <summary>
    /// A conversion time of 1.1 ms.
    /// </summary>
    milliseconds_1_1 = 4,

    /// <summary>
    /// A conversion time of 2.116 ms.
    /// </summary>
    milliseconds_2_116 = 5,

    /// <summary>
    /// A conversion time of 4.156 ms.
    /// </summary>
    milliseconds_4_156 = 6,

    /// <summary>
    /// A conversion time of 8.244 ms.
    /// </summary>
    milliseconds_8_244 = 7

};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_TINKERFORGE_CONVERSION_TIME_H) */
