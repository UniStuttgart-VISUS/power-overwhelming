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
    /// The timestamp when the sample was obtained.
    /// </summary>
    PWROWG_NAMESPACE::timestamp timestamp;

    /// <summary>
    /// The actual sensor reading.
    /// </summary>
    PWROWG_NAMESPACE::reading reading;

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="reading">The value of the <see cref="reading" /> member.
    /// </param>
    inline sample(_In_ const double reading = 0.0f)
            : timestamp(PWROWG_NAMESPACE::timestamp::now()) {
        this->reading.floating_point = reading;
    }

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="reading">The value of the <see cref="reading" /> member.
    /// </param>
    inline sample(_In_ const float reading)
            : timestamp(PWROWG_NAMESPACE::timestamp::now()) {
        this->reading.floating_point = reading;
    }

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="reading">The value of the <see cref="reading" /> member.
    /// </param>
    inline sample(_In_ const std::int64_t reading)
            : timestamp(PWROWG_NAMESPACE::timestamp::now()) {
        this->reading.signed_integer = reading;
    }

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="reading">The value of the <see cref="reading" /> member.
    /// </param>
    inline sample(_In_ const std::int32_t reading)
        : timestamp(PWROWG_NAMESPACE::timestamp::now()) {
        this->reading.signed_integer = reading;
    }

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="reading">The value of the <see cref="reading" /> member.
    /// </param>
    inline sample(_In_ const std::uint64_t reading)
            : timestamp(PWROWG_NAMESPACE::timestamp::now()) {
        this->reading.unsigned_integer = reading;
    }


    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="reading">The value of the <see cref="reading" /> member.
    /// </param>
    inline sample(_In_ const std::uint32_t reading)
        : timestamp(PWROWG_NAMESPACE::timestamp::now()) {
        this->reading.signed_integer = reading;
    }

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="timestamp">The timestamp of the sample.</param>
    /// <param name="reading">The value of the <see cref="reading" /> member.
    /// </param>
    inline sample(_In_ const PWROWG_NAMESPACE::timestamp timestamp,
            _In_ const double reading = 0.0f)
            : timestamp(timestamp) {
        this->reading.floating_point = reading;
    }

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="timestamp">The timestamp of the sample.</param>
    /// <param name="reading">The value of the <see cref="reading" /> member.
    /// </param>
    inline sample(_In_ const PWROWG_NAMESPACE::timestamp timestamp,
            _In_ const float reading)
            : timestamp(timestamp) {
        this->reading.floating_point = reading;
    }

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="timestamp">The timestamp of the sample.</param>
    /// <param name="reading">The value of the <see cref="reading" /> member.
    /// </param>
    inline sample(_In_ const PWROWG_NAMESPACE::timestamp timestamp,
            _In_ const std::int64_t reading)
            : timestamp(timestamp) {
        this->reading.signed_integer = reading;
    }

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="timestamp">The timestamp of the sample.</param>
    /// <param name="reading">The value of the <see cref="reading" /> member.
    /// </param>
    inline sample(_In_ const PWROWG_NAMESPACE::timestamp timestamp,
            _In_ const std::int32_t reading)
            : timestamp(timestamp) {
        this->reading.signed_integer = reading;
    }

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// /// <param name="timestamp">The timestamp of the sample.</param>
    /// <param name="reading">The value of the <see cref="reading" /> member.
    /// </param>
    inline sample(_In_ const PWROWG_NAMESPACE::timestamp timestamp,
            _In_ const std::uint64_t reading)
            : timestamp(timestamp) {
        this->reading.unsigned_integer = reading;
    }

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// /// <param name="timestamp">The timestamp of the sample.</param>
    /// <param name="reading">The value of the <see cref="reading" /> member.
    /// </param>
    inline sample(_In_ const PWROWG_NAMESPACE::timestamp timestamp,
            _In_ const std::uint32_t reading)
            : timestamp(timestamp) {
        this->reading.unsigned_integer = reading;
    }
};

static_assert(sizeof(sample) == 16, "The sensor sample should use exactly "
    "2 * 64 bits. If this assertion fails, the timestamp, reading or sample "
    "data type got messed up.");

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_SAMPLE_H) */
