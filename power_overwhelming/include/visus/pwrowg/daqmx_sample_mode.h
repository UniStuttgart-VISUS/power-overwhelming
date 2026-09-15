// <copyright file="daqmx_sample_mode.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_DAQMX_SAMPLE_MODE_H)
#define _PWROWG_DAQMX_SAMPLE_MODE_H
#pragma once

#include "visus/pwrowg/daqmx_types.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Specifies the possible sample modes for a NI-DAQmx task.
/// </summary>
enum class daqmx_sample_mode : std::int32_t {

    /// <summary>
    /// Acquire or generate the specified number of samples.
    /// </summary>
    finite = __PWOWG_DAQMX_VALUE(DAQmx_Val_FiniteSamps, 10178),

    /// <summary>
    /// Acquire or generate samples until the task is stopped.
    /// </summary>
    continuous = __PWOWG_DAQMX_VALUE(DAQmx_Val_ContSamps, 10123),

    /// <summary>
    /// Acquire or generate samples continuously using hardware timing without a
    /// buffer. Hardware-timed single-point acquisition and generation is only
    /// supported for the sample clock and change detection timing types.
    /// </summary>
    hardware_timed_single_point
        = __PWOWG_DAQMX_VALUE(DAQmx_Val_HWTimedSinglePoint, 12522)
};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_DAQMX_SAMPLE_MODE_H) */
