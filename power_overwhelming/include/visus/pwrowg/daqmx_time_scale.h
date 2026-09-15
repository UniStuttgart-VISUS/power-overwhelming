// <copyright file="daqmx_time_scale.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_DAQMX_TIME_SCALE_H)
#define _PWROWG_DAQMX_TIME_SCALE_H
#pragma once

#include <cinttypes>

#if defined(POWER_OVERWHELMING_WITH_DAQMX)
#include <NIDAQmx.h>
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */

#include "visus/pwrowg/api.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Specifies the pssible time scales for a NI-DAQmx device.
/// </summary>
enum class daqmx_time_scale : std::int32_t {

#if defined(POWER_OVERWHELMING_WITH_DAQMX)
    /// <summary>
    /// Use the host device.
    /// </summary>
    host = DAQmx_Val_HostTime,

    /// <summary>
    /// Use the I/O device.
    /// </summary>
    io = DAQmx_Val_IODeviceTime
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_DAQMX_TIME_SCALE_H) */
