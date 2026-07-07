// <copyright file="daqmx_sample_event_type.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_DAQMX_SAMPLE_EVENT_TYPE_H)
#define _PWROWG_DAQMX_SAMPLE_EVENT_TYPE_H
#pragma once

#include <cinttypes>

#if defined(POWER_OVERWHELMING_WITH_DAQMX)
#include <NIDAQmx.h>
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */

#include "visus/pwrowg/api.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Specifies types of n-sample events from a NI-DAQmx device.
/// </summary>
enum class daqmx_sample_event_type : std::int32_t {

#if defined(POWER_OVERWHELMING_WITH_DAQMX)
    /// <summary>
    /// This event type is only supported for input tasks. Events occur when
    /// the specified number of samples are acquired into the buffer from the
    /// device.
    /// </summary>
    acquired = DAQmx_Val_Acquired_Into_Buffer,

    /// <summary>
    /// This event type is only supported for output tasks. Events occur when
    /// the specified number of samples are transferred from the buffer to the
    /// device.
    /// </summary>
    transferred = DAQmx_Val_Transferred_From_Buffer,
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_DAQMX_SAMPLE_EVENT_TYPE_H) */
