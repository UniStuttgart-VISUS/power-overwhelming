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
};

static_assert(sizeof(sample) == 16, "The sensor sample should use exactly "
    "2 * 64 bits. If this assertion fails, the timestamp, reading or sample "
    "data type got messed up.");

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_SAMPLE_H) */
