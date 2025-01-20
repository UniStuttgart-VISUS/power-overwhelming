// <copyright file="rtx_trigger_mode.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>

#if !defined(_PWROWG_RTX_TRIGGER_MODE_H)
#define _PWROWG_RTX_TRIGGER_MODE_H
#pragma once

#include "visus/pwrowg/api.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Defines possible modes how the oscilloscope triggers.
/// </summary>
enum class rtx_trigger_mode {

    /// <summary>
    /// The instrument triggers repeatedly after a time interval if the
    /// configured tigger conditions are not fulfiled. If a real trigger
    /// occurs, it takses precedence.
    /// </summary>
    automatic,

    /// <summary>
    /// The instrument only aquires tata if a real tigger occurs.
    /// </summary>
    normal
};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_RTX_TRIGGER_MODE_H) */
