// <copyright file="rtx_trigger_output.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>

#if !defined(_PWROWG_RTX_TRIGGER_OUTPUT_H)
#define _PWROWG_RTX_TRIGGER_OUTPUT_H
#pragma once

#include "visus/pwrowg/api.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Defines possible modes for the auxilliary trigger output port.
/// </summary>
enum class rtx_trigger_output {

    /// <summary>
    /// The auxilliary output is disabled.
    /// </summary>
    off,

    /// <summary>
    /// Outputs a pulse when the instrument triggers.
    /// </summary>
    pulse,

    /// <summary>
    /// Outputs a 10 MHz reference fequency.
    /// </summary>
    reference,

    /// <summary>
    /// Outputs a pulse when a mask is violated.
    /// </summary>
    mask
};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_RTX_TRIGGER_OUTPUT_H) */
