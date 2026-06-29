// <copyright file="daqmx_terminal_configuration.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_DAQMX_TERMINAL_CONFIGURATION_H)
#define _PWROWG_DAQMX_TERMINAL_CONFIGURATION_H
#pragma once

#include <cinttypes>

#include "visus/pwrowg/api.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// The possible input terminal configurations for a NI-DAQmx channel.
/// </summary>
enum class daqmx_terminal_configuration : std::int32_t {
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
    /// <summary>
    /// At run time, NI-DAQmx chooses the default terminal configuration for the
    /// channel.
    /// </summary>
    standard,

    /// <summary>
    /// Referenced single-ended mode. The measurement is made with respect to
    /// ground.
    /// </summary>
    referenced_single_ended,

    /// <summary>
    /// Non-referenced single-ended mode. The measurement is made with respect
    /// to a single-node analog input sense, but the potential at this node can
    /// vary with respect to the measurement system ground.
    /// </summary>
    non_referenced_single_ended,

    /// <summary>
    /// Differential mode. A differential measurement system is similar to a
    /// floating signal source in that the measurement is made with respect to
    /// a floating ground that is different from the measurement system ground.
    /// </summary>
    differential,

    /// <summary>
    /// Pseudo-differential mode. A pseudo-differential measurement system
    /// combines some characteristics of a differential input channel and a
    /// referenced single-ended (RSE) input channel. Like a differential input
    /// channel, a pseudo-differential measurement system exposes both the
    /// positive and negative sides of the channel. You connect the positive
    /// and negative inputs to the respective outputs of the unit under test.
    /// The negative input is tied to system ground through a relatively small
    /// impedance. The impedance between the negative input and ground may
    /// include both resistive and capacitive components. The positive and
    /// negative sides of the input channel are separated by a larger impedance.
    /// </summary>
    pseudo_differential,
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_DAQMX_TERMINAL_CONFIGURATION_H) */
