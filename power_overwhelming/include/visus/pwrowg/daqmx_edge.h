// <copyright file="daqmx_edge.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_DAQMX_EDGE_H)
#define _PWROWG_DAQMX_EDGE_H
#pragma once

#include "visus/pwrowg/daqmx_types.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Specifies the possible trigger edges for a NI-DAQmx device.
/// </summary>
enum class daqmx_edge : std::int32_t {

    /// <summary>
    /// Acquire or generate samples on the rising edges of the sample clock.
    /// </summary>
    rising = __PWOWG_DAQMX_VALUE(DAQmx_Val_Rising, 10280),

    /// <summary>
    /// Acquire or generate samples on the falling edges of the sample clock.
    /// </summary>
    falling = __PWOWG_DAQMX_VALUE(DAQmx_Val_Falling, 10171),
};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_DAQMX_EDGE_H) */
