// <copyright file="daqmx_time_trigger.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_DAQMX_TIME_TRIGGER_H)
#define _PWROWG_DAQMX_TIME_TRIGGER_H
#pragma once

#include "visus/pwrowg/daqmx_time_scale.h"
#include "visus/pwrowg/timestamp.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// If configured as the trigger of a <see cref="daqmx_task" />, the task will
/// start sampling at the specified point in time.
/// </summary>
class POWER_OVERWHELMING_API daqmx_time_trigger final {

public:

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="when">Specifies when to trigger.</param>
    /// <param name="timescale">Specifies the start trigger timestamp time
    /// scale.</param>
    daqmx_time_trigger(_In_ const timestamp when,
        _In_ const daqmx_time_scale timescale = daqmx_time_scale::host);

    /// <summary>
    /// Gets the time scale of the start time.
    /// </summary>
    /// <returns>The time scale.</returns>
    inline daqmx_time_scale time_scale(void) const noexcept {
        return this->_time_scale;
    }

    /// <summary>
    /// Gets the start time when the trigger will fire.
    /// </summary>
    /// <returns>The start time.</returns>
    inline timestamp when(void) const noexcept {
        return this->_when;
    }

private:

    daqmx_time_scale _time_scale;
    timestamp _when;
};

PWROWG_NAMESPACE_END

#endif /*!defined(_PWROWG_DAQMX_TIME_TRIGGER_H) */
