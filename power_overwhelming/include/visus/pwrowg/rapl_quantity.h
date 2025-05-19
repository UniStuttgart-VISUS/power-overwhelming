// <copyright file="rapl_quantity.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_RAPL_QUANTITY_H)
#define _PWROWG_RAPL_QUANTITY_H
#pragma once

#include "visus/pwrowg/api.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Possible quantities that can be provided via RAPL registers.
/// </summary>
enum class rapl_quantity {

    /// <summary>
    /// Energy in Joules or derived from it.
    /// </summary>
    energy,

    /// <summary>
    /// Power in Watts or derived from it.
    /// </summary>
    power,

    /// <summary>
    /// Time in seconds or derived from it.
    /// </summary>
    time,
};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_RAPL_QUANTITY_H) */
