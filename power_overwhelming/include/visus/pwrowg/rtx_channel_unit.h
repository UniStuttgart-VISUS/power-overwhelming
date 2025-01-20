// <copyright file="rtx_channel_unit.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_RTX_CHANNEL_UNIT_H)
#define _PWROWG_RTX_CHANNEL_UNIT_H
#pragma once

#include "visus/pwrowg/api.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Defines possible units for a channel of the oscilloscope.
/// </summary>
enum class rtx_channel_unit {

    /// <summary>
    /// The channel measures voltage.
    /// </summary>
    volt,

    /// <summary>
    /// The channel measures current.
    /// </summary>
    ampere
};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_RTX_CHANNEL_UNIT_H) */
