// <copyright file="daqmx_shunt_resistor_location.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_DAQMX_SHUNT_RESISTOR_LOCATION_H)
#define _PWROWG_DAQMX_SHUNT_RESISTOR_LOCATION_H
#pragma once

#include <cinttypes>

#if defined(POWER_OVERWHELMING_WITH_DAQMX)
#include <NIDAQmx.h>
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */

#include "visus/pwrowg/api.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// The locations of the shunt resistor for a NI-DAQmx current channel.
/// </summary>
enum class daqmx_shunt_resistor_location : std::int32_t {
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
    /// <summary>
    /// At run time, NI-DAQmx chooses the default shunt resistor location for
    /// the channel.
    /// </summary>
    standard = DAQmx_Val_Default,

    /// <summary>
    /// Use the built-in shunt resistor of the device.
    /// </summary>
    internal = DAQmx_Val_Internal,

    /// <summary>
    /// Use a shunt resistor external to the device.
    /// </summary>
    external = DAQmx_Val_External
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_DAQMX_SHUNT_RESISTOR_LOCATION_H) */
