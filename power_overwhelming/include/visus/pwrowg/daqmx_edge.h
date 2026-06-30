// <copyright file="daqmx_edge.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_DAQMX_EDGE_H)
#define _PWROWG_DAQMX_EDGE_H
#pragma once

#include <cinttypes>

#if defined(POWER_OVERWHELMING_WITH_DAQMX)
#include <NIDAQmx.h>
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */

#include "visus/pwrowg/api.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Specifies the possible trigger edges for a NI-DAQmx device.
/// </summary>
enum class daqmx_edge : std::int32_t {

#if defined(POWER_OVERWHELMING_WITH_DAQMX)
    /// <summary>
    /// Acquire or generate samples on the rising edges of the sample clock.
    /// </summary>
    rising = DAQmx_Val_Rising,

    /// <summary>
    /// Acquire or generate samples on the falling edges of the sample clock.
    /// </summary>
    falling = DAQmx_Val_Falling,
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_DAQMX_EDGE_H) */
