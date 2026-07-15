// <copyright file="daqmx_immediate_trigger.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_DAQMX_IMMEDIATE_TRIGGER_H)
#define _PWROWG_DAQMX_IMMEDIATE_TRIGGER_H
#pragma once

#include "visus/pwrowg/api.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// If configured as the trigger of a <see cref="daqmx_task" />, the task will
/// start sampling immediately after it is started.
/// </summary>
class POWER_OVERWHELMING_API daqmx_immediate_trigger final {

public:

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    daqmx_immediate_trigger(void) = default;

};

PWROWG_NAMESPACE_END

#endif /*!defined(_PWROWG_DAQMX_IMMEDIATE_TRIGGER_H) */
