// <copyright file="conversion_time.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_TNKERFORGE_SAMPLE_AVERAGING_H)
#define _PWROWG_TNKERFORGE_SAMPLE_AVERAGING_H
#pragma once

#include <cinttypes>

#include "visus/pwrowg/api.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Possible values for averaging samples of Tinkerforge sensors.
/// </summary>
/// <remarks>
/// Constants are taken from
/// https://www.tinkerforge.com/de/doc/Software/Bricklets/VoltageCurrentV2_Bricklet_C.html#voltage-current-v2-bricklet-c-api
/// </remarks>
enum class tinkerforge_sample_averaging : std::uint8_t {

    /// <summary>
    /// Return the latest sample.
    /// </summary>
    average_of_1 = 0,

    /// <summary>
    /// Sliding average over four samples.
    /// </summary>
    average_of_4 = 1,

    /// <summary>
    /// Sliding average over 16 samples.
    /// </summary>
    average_of_16 = 2,

    /// <summary>
    /// Sliding average over 64 samples.
    /// </summary>
    average_of_64 = 3,

    /// <summary>
    /// Sliding average over 128 samples.
    /// </summary>
    average_of_128 = 4,

    /// <summary>
    /// Sliding average over 256 samples.
    /// </summary>
    average_of_256 = 5,

    /// <summary>
    /// Sliding average over 512 samples.
    /// </summary>
    average_of_512 = 6,

    /// <summary>
    /// Sliding average over 1024 samples.
    /// </summary>
    average_of_1024 = 7,
};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_TNKERFORGE_SAMPLE_AVERAGING_H) */
