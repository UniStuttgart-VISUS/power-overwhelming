// <copyright file="daqmx_voltage_channel.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_DAQMX_VOLTAGE_CHANNEL_H)
#define _PWROWG_DAQMX_VOLTAGE_CHANNEL_H
#pragma once

#include "visus/pwrowg/daqmx_channel.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// A descriptor for a voltage channel of a NI-DAQmx-based sensor, which can be
/// used to add such a channel to a <see cref="daqmx_task" />.
/// </summary>
class POWER_OVERWHELMING_API daqmx_voltage_channel final
        : public daqmx_channel {

public:

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="channel">The name of the physical channel, which should
    /// be something like &quot;Dev1/ai0&quot; for the first analog input.
    /// </param>
    explicit inline daqmx_voltage_channel(_In_z_ const wchar_t *channel)
        : daqmx_channel(channel) { }

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="channel">The name of the physical channel, which should
    /// be something like &quot;Dev1/ai0&quot; for the first analog input.
    /// </param>
    explicit inline daqmx_voltage_channel(_In_z_ const char *channel)
        : daqmx_channel(channel) { }

    using daqmx_channel::max_value;

    /// <summary>
    /// Sets the maximum expected value in Volts.
    /// </summary>
    /// <param name="value">The maximum expected value for the channel, in
    /// Volts.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    inline daqmx_voltage_channel& max_value(_In_ const double value) noexcept {
        daqmx_channel::max_value(value);
        return *this;
    }

    using daqmx_channel::min_value;

    /// <summary>
    /// Sets the minimal expected value in Volts.
    /// </summary>
    /// <param name="value">The minimum expected value for the channel, in
    /// Volts.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    inline daqmx_voltage_channel& min_value(_In_ const double value) noexcept {
        daqmx_channel::min_value(value);
        return *this;
    }

    using daqmx_channel::name;

    /// <summary>
    /// Sets the name of the virtual channel.
    /// </summary>
    /// <param name="value">The name of the virtual channel</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    inline daqmx_voltage_channel& name(_In_z_ const wchar_t *value) {
        daqmx_channel::name(value);
        return *this;
    }

    /// <summary>
    /// Sets the name of the virtual channel.
    /// </summary>
    /// <param name="value">The name of the virtual channel</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    inline daqmx_voltage_channel& name(_In_z_ const char *value) {
        daqmx_channel::name(value);
        return *this;
    }

    /// <summary>
    /// Sets the name of the virtual channel.
    /// </summary>
    /// <typeparam name="TChar">The character type of the string.</typeparam>
    /// <typeparam name="TTraits">The character traits of the string.
    /// </typeparam>
    /// <typeparam name="TAlloc">The allocator of the string.</typeparam>
    /// <param name="value">The name of the virtual channel</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    template<class TChar, class TTraits, class TAlloc>
    inline daqmx_voltage_channel& name(
            _In_ const std::basic_string<TChar, TTraits, TAlloc>& value) {
        daqmx_channel::name(value);
        return *this;
    }

    using daqmx_channel::terminal_configuration;

    /// <summary>
    /// Sets the input terminal configuration for the channel.
    /// </summary>
    /// <param name="value">The input terminal configuration.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    inline daqmx_voltage_channel& terminal_configuration(
            _In_ const daqmx_terminal_configuration value) noexcept {
        daqmx_channel::terminal_configuration(value);
        return *this;
    }
};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_DAQMX_VOLTAGE_CHANNEL_H) */
