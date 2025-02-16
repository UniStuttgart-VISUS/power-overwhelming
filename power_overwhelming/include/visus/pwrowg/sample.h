// <copyright file="sample.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_SAMPLE_H)
#define _PWROWG_SAMPLE_H
#pragma once

#include "visus/pwrowg/timestamp.h"
#include "visus/pwrowg/reading.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Represents a single sample from a single sensor.
/// </summary>
struct sample final {

    /// <summary>
    /// The type used to index the sensor sources.
    /// </summary>
    typedef std::uint32_t source_type;

    /// <summary>
    /// The timestamp when the sample was obtained.
    /// </summary>
    PWROWG_NAMESPACE::timestamp timestamp;

    /// <summary>
    /// The zero-based index of the sensor that created the sample.
    /// </summary>
    source_type source;

    /// <summary>
    /// The actual sensor reading.
    /// </summary>
    PWROWG_NAMESPACE::reading reading;

    /// <summary>
    /// Initialises a new instance with the current timestamp.
    /// </summary>
    /// <param name="source">The zero-based index of the sensor that created the
    /// sample</param>
    /// <param name="reading">The value of the <see cref="reading" /> member.
    /// </param>
    inline sample(_In_ const source_type source = 0,
            _In_ const float reading = 0.0f)
        : timestamp(PWROWG_NAMESPACE::timestamp::now()),
            source(source) {
        this->reading.floating_point = reading;
    }

    /// <summary>
    /// Initialises a new instance with the current timestamp.
    /// </summary>
    /// <param name="source">The zero-based index of the sensor that created the
    /// sample</param>
    /// <param name="reading">The value of the <see cref="reading" /> member.
    /// </param>
    inline sample(_In_ const source_type source,
            _In_ const std::int32_t reading)
        : timestamp(PWROWG_NAMESPACE::timestamp::now()),
            source(source) {
        this->reading.signed_integer = reading;
    }

    /// <summary>
    /// Initialises a new instance with the current timestamp.
    /// </summary>
    /// <param name="source">The zero-based index of the sensor that created the
    /// sample</param>
    /// <param name="reading">The value of the <see cref="reading" /> member.
    /// </param>
    inline sample(_In_ const source_type source,
            _In_ const std::uint32_t reading)
        : timestamp(PWROWG_NAMESPACE::timestamp::now()),
            source(source) {
        this->reading.signed_integer = reading;
    }

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="source">The zero-based index of the sensor that created the
    /// sample</param>
    /// <param name="timestamp">The timestamp of the sample.</param>
    /// <param name="reading">The value of the <see cref="reading" /> member.
    /// </param>
    inline sample(_In_ const source_type source,
            _In_ const PWROWG_NAMESPACE::timestamp timestamp,
            _In_ const float reading = 0.0f)
        : timestamp(timestamp),
            source(source) {
        this->reading.floating_point = reading;
    }

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// </summary>
    /// <param name="source">The zero-based index of the sensor that created the
    /// sample</param>
    /// <param name="timestamp">The timestamp of the sample.</param>
    /// <param name="reading">The value of the <see cref="reading" /> member.
    /// </param>
    inline sample(_In_ const source_type source,
            _In_ const PWROWG_NAMESPACE::timestamp timestamp,
            _In_ const std::int32_t reading)
        : timestamp(timestamp),
            source(source) {
        this->reading.signed_integer = reading;
    }

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// </summary>
    /// <param name="source">The zero-based index of the sensor that created the
    /// sample</param>
    /// /// <param name="timestamp">The timestamp of the sample.</param>
    /// <param name="reading">The value of the <see cref="reading" /> member.
    /// </param>
    inline sample(_In_ const source_type source,
            _In_ const PWROWG_NAMESPACE::timestamp timestamp,
            _In_ const std::uint32_t reading)
        : timestamp(timestamp),
            source(source) {
        this->reading.unsigned_integer = reading;
    }
};

static_assert(sizeof(sample) == 16, "The sensor sample should use exactly "
    "2 * 64 bits. If this assertion fails, the timestamp, reading or sample "
    "data type got messed up.");

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_SAMPLE_H) */
