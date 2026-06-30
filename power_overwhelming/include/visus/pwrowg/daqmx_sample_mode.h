// <copyright file="daqmx_sample_mode.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_DAQMX_SAMPLE_MODE_H)
#define _PWROWG_DAQMX_SAMPLE_MODE_H
#pragma once

#include <cinttypes>

#if defined(POWER_OVERWHELMING_WITH_DAQMX)
#include <NIDAQmx.h>
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */

#include "visus/pwrowg/api.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Specifies the possible sample modes for a NI-DAQmx task.
/// </summary>
enum class daqmx_sample_mode : std::int32_t {
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
    /// <summary>
    /// Acquire or generate the specified number of samples.
    /// </summary>
    finite = DAQmx_Val_FiniteSamps,

    /// <summary>
    /// Acquire or generate samples until the task is stopped.
    /// </summary>
    continuous = DAQmx_Val_ContSamps,

    /// <summary>
    /// Acquire or generate samples continuously using hardware timing without a
    /// buffer. Hardware-timed single-point acquisition and generation is only
    /// supported for the sample clock and change detection timing types.
    /// </summary>
    hardware_timed_single_point = DAQmx_Val_HWTimedSinglePoint
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_DAQMX_SAMPLE_MODE_H) */
