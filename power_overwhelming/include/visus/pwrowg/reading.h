// <copyright file="reading.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_READING_H)
#define _READING_H
#pragma once

#include <cinttypes>

#include "visus/pwrowg/api.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Represents the value of a single sensor reading.
/// </summary>
/// <remarks>
/// <para>The correct interpretation of the data is defined by the
/// <see cref="reading_type" /> in the <see cref="sensor_description" /> of
/// the sensor that produced the reading.</para>
/// </remarks>
union reading final {

    /// <summary>
    /// THe value as raw bytes.
    /// </summary>
    std::uint8_t bytes[4];

    /// <summary>
    /// The value as IEE-754 floating point number.
    /// </summary>
    float floating_point;

    /// <summary>
    /// The reading as a signed integer.
    /// </summary>
    std::int32_t signed_integer;

    /// <summary>
    /// The reading as an unsigned integer.
    /// </summary>
    std::uint32_t unsigned_integer;
};

static_assert(sizeof(reading) == 4, "The size of a reading must be four bytes. "
    "If this assertion fails, something got messed up in the declaration of "
    "the reading union.");

PWROWG_NAMESPACE_END

#endif /* !defined(_READING_H) */
