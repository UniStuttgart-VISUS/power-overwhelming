// <copyright file="reading_type.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_READING_TYPE_H)
#define _READING_TYPE_H
#pragma once

#include "visus/pwrowg/api.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Defines how a 64-bit sensor reading has to be interpreted.
/// </summary>
enum class reading_type {

    /// <summary>
    /// The reading is an IEE-754 floating point number (<c>double</c>).
    /// </summary>
    floating_point,

    /// <summary>
    /// The reading is a signed integer.
    /// </summary>
    signed_integer,

    /// <summary>
    /// The reading is an unsigned integer.
    /// </summary>
    unsigned_integer
};

PWROWG_NAMESPACE_END

#endif /* !defined(_READING_TYPE_H) */
