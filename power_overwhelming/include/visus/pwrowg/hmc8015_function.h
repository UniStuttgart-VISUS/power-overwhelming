// <copyright file="hmc8015_function.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_HMC8015_FUNCTION_H)
#define _PWROWG_HMC8015_FUNCTION_H
#pragma once

#include "visus/pwrowg/api.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Defines possible measurement functions of the Rohde &amp; Schwarz HMC8015
/// power analyser.
/// </summary>
enum class hmc8015_function {

    /// <summary>
    /// Measures/displays nothing.
    /// </summary>
    empty,

    /// <summary>
    /// The active power P.
    /// </summary>
    active_power,

    /// <summary>
    /// The apparent power S.
    /// </summary>
    apparent_power,

    /// <summary>
    /// The reactive power.
    /// </summary>
    reactive_power,

    /// <summary>
    /// The power factor, which is the ratio between the true power and the
    /// apparent power.
    /// </summary>
    power_factor,

    /// <summary>
    /// The phase difference.
    /// </summary>
    phase_difference,

    /// <summary>
    /// The voltage frequency.
    /// </summary>
    voltage_frequency,

    /// <summary>
    /// The current frequency.
    /// </summary>
    current_frequency,

    /// <summary>
    /// The true RMS voltage.
    /// </summary>
    rms_voltage,

    /// <summary>
    /// The voltage average.
    /// </summary>
    average_voltage,

    /// <summary>
    /// The true RMS current.
    /// </summary>
    rms_current,

    /// <summary>
    /// The current average.
    /// </summary>
    current_average,

    /// <summary>
    /// The total harmonic distortion of voltage.
    /// </summary>
    voltage_distortion,

    /// <summary>
    /// The total harmonic distortion of current.
    /// </summary>
    current_distortion,

    /// <summary>
    /// The PLL source frequency.
    /// </summary>
    phase_locked_loop_frequency,

    /// <summary>
    /// The integration time
    /// </summary>
    integration_time,

    /// <summary>
    /// Watt hour.
    /// </summary>
    watt_hour,

    /// <summary>
    /// Positive Watt hour.
    /// </summary>
    positive_watt_hour,

    /// <summary>
    /// Negative Watt hour.
    /// </summary>
    negative_watt_hour,

    /// <summary>
    /// Ampere hour.
    /// </summary>
    ampere_hour,

    /// <summary>
    /// Positive Ampere hour.
    /// </summary>
    positive_ampere_hour,

    /// <summary>
    /// Negative Ampere hour.
    /// </summary>
    negative_ampere_hour,

    /// <summary>
    /// The voltage range configured.
    /// </summary>
    voltage_range,

    /// <summary>
    /// The voltage range configured.
    /// </summary>
    current_range
};


/// <summary>
/// Convert the given measurement function to a string.
/// </summary>
/// <param name="function">The function to be converted.</param>
/// <returns>The string representation of the source.</returns>
/// <exception cref="std::invalid_argument">If the source is not valid and
/// therefore could not be converted.</exception>
extern POWER_OVERWHELMING_API _Ret_valid_ const wchar_t *to_string(
    _In_ const hmc8015_function function);

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_HMC8015_FUNCTION_H) */
