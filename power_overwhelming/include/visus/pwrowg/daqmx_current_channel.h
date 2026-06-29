// <copyright file="daqmx_current_channel.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_DAQMX_CURRENT_CHANNEL_H)
#define _PWROWG_DAQMX_CURRENT_CHANNEL_H
#pragma once

#include "visus/pwrowg/daqmx_channel.h"
#include "visus/pwrowg/daqmx_shunt_resistor_location.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// A descriptor for a current channel of a NI-DAQmx-based sensor, which can be
/// used to add such a channel to a <see cref="daqmx_task" />.
/// </summary>
class POWER_OVERWHELMING_API daqmx_current_channel final
        : public daqmx_channel {

public:

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="channel">The name of the physical channel, which should
    /// be something like &quot;ai0&quot; for the first analog input.</param>
    explicit daqmx_current_channel(_In_z_ const wchar_t *channel);

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="channel">The name of the physical channel, which should
    /// be something like &quot;ai0&quot; for the first analog input.</param>
    explicit daqmx_current_channel(_In_z_ const char *channel);

    using daqmx_channel::max_value;

    /// <summary>
    /// Sets the maximum expected value in Amperes.
    /// </summary>
    /// <param name="value">The maximum expected value for the channel, in
    /// Amperes.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    inline daqmx_current_channel& max_value(_In_ const double value) noexcept {
        daqmx_channel::max_value(value);
        return *this;
    }

    using daqmx_channel::min_value;

    /// <summary>
    /// Sets the minimum expected value in Amperes.
    /// </summary>
    /// <param name="value">The minimum expected value for the channel, in
    /// Amperes.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    inline daqmx_current_channel& min_value(_In_ const double value) noexcept {
        daqmx_channel::min_value(value);
        return *this;
    }

    using daqmx_channel::name;

    /// <summary>
    /// Sets the name of the virtual channel.
    /// </summary>
    /// <param name="value">The name of the virtual channel</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    inline daqmx_current_channel& name(_In_z_ const wchar_t *value) {
        daqmx_channel::name(value);
        return *this;
    }

    /// <summary>
    /// Sets the name of the virtual channel.
    /// </summary>
    /// <param name="value">The name of the virtual channel</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    inline daqmx_current_channel& name(_In_z_ const char *value) {
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
    inline daqmx_current_channel& name(
            _In_ const std::basic_string<TChar, TTraits, TAlloc>& value) {
        daqmx_channel::name(value);
        return *this;
    }

    /// <summary>
    /// The value, in Ohms, of an external shunt resistor used for the channel,
    /// which is used when <see cref="shunt_resistor_location::external" /> is
    /// set.
    /// </summary>
    /// <returns>The value of the external shunt resistor, in Ohms.</returns>
    inline double shunt_resistor_value(void) const noexcept {
        return this->_shunt_resistor_value;
    }

    /// <summary>
    /// Sets the value, in Ohms, of an external shunt resistor used for the
    /// channel. This value is ignored if the internal shunt resistor is used.
    /// </summary>
    /// <param name="value">The value of the external shunt resistor, in
    /// Ohms.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    inline daqmx_current_channel& shunt_resistor_value(
            _In_ const double value) noexcept {
        this->_shunt_resistor_value = value;
        return *this;
    }

    /// <summary>
    /// Indicates which shunt resistor is used for the channel.
    /// </summary>
    /// <returns>The shunt resistor to be used for the channel.</returns>
    inline daqmx_shunt_resistor_location shunt_resistor_location(
            void) const noexcept {
        return this->_shunt_resistor_location;
    }

    /// <summary>
    /// Configures which shunt resistor is used for the channel. If an external
    /// resistor is configured, its value must be set using the
    /// <see cref="shunt_resistor_value" /> method.
    /// </summary>
    /// <param name="value">The shunt resistor to be used for the channel.
    /// </param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    inline daqmx_current_channel& shunt_resistor_location(
            _In_ const daqmx_shunt_resistor_location value) noexcept {
        this->_shunt_resistor_location = value;
        return *this;
    }

    using daqmx_channel::terminal_configuration;

    /// <summary>
    /// Sets the input terminal configuration for the channel.
    /// </summary>
    /// <param name="value">The input terminal configuration.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    inline daqmx_current_channel& terminal_configuration(
            _In_ const daqmx_terminal_configuration value) noexcept {
        daqmx_channel::terminal_configuration(value);
        return *this;
    }

private:

    double _shunt_resistor_value;
    daqmx_shunt_resistor_location _shunt_resistor_location;
};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_DAQMX_CURRENT_CHANNEL_H) */
