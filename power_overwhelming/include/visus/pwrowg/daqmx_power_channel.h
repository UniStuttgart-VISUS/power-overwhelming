// <copyright file="daqmx_power_channel.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_DAQMX_POWER_CHANNEL_H)
#define _PWROWG_DAQMX_POWER_CHANNEL_H
#pragma once

#include "visus/pwrowg/daqmx_channel.h"
#include "visus/pwrowg/daqmx_shunt_resistor_location.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// A descriptor for a computed power channel of a NI-DAQmx-based sensor, which
/// can be used to add such a channel to a <see cref="daqmx_task" />.
/// </summary>
/// <remarks>
/// The &quot;default&quot; channel is the voltage channel.
/// </remarks>
class POWER_OVERWHELMING_API daqmx_power_channel final : public daqmx_channel {

public:

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="voltage_channel">The name of the physical channel measuring
    /// voltage, which should be something like &quot;Dev1/ai0&quot; for the
    /// first analog input.</param>
    /// <param name="current_channel">The name of the physical channel measuring
    /// current, which should be something like &quot;Dev1/ai1&quot; for the
    /// second analog input.</param>
    daqmx_power_channel(_In_z_ const wchar_t *voltage_channel,
        _In_z_ const wchar_t *current_channel);

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="voltage_channel">The name of the physical channel measuring
    /// voltage, which should be something like &quot;ai0&quot; for the first
    /// analog input.</param>
    /// <param name="current_channel">The name of the physical channel measuring
    /// current, which should be something like &quot;ai1&quot; for the second
    /// analog input.</param>
    daqmx_power_channel(_In_z_ const char *voltage_channel,
        _In_z_ const char *current_channel);

    /// <summary>
    /// Gets the name of the physical channel measuring current.
    /// </summary>
    /// <returns>The name of the physical channel measuring current.</returns>
    _Ret_z_ inline const char *current_channel(void) const noexcept {
        return this->_current_channel.as<char>();
    }

    /// <summary>
    /// Gets the maximum expected current in Amperes.
    /// </summary>
    /// <returns>The maximum expected current, in Amperes.</returns>
    inline double current_max_value(void) const noexcept {
        return this->_current_max_value;
    }

    /// <summary>
    /// Sets the maximum expected current in Amperes.
    /// </summary>
    /// <param name="value">The maximum expected current for the channel, in
    /// Amperes.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    inline daqmx_power_channel& current_max_value(
            _In_ const double value) noexcept {
        this->_current_max_value = value;
        return *this;
    }

    /// <summary>
    /// Gets the minimum expected current in Amperes.
    /// </summary>
    /// <returns>The minimum expected current, in Amperes.</returns>
    inline double current_min_value(void) const noexcept {
        return this->_current_min_value;
    }

    /// <summary>
    /// Sets the minimum expected current in Amperes.
    /// </summary>
    /// <param name="value">The minimum expected current for the channel, in
    /// Amperes.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    inline daqmx_power_channel& current_min_value(
            _In_ const double value) noexcept {
        this->_current_min_value = value;
        return *this;
    }

    using daqmx_channel::name;

    /// <summary>
    /// Sets the name of the virtual channel.
    /// </summary>
    /// <param name="value">The name of the virtual channel</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    inline daqmx_power_channel& name(_In_z_ const wchar_t *value) {
        daqmx_channel::name(value);
        return *this;
    }

    /// <summary>
    /// Sets the name of the virtual channel.
    /// </summary>
    /// <param name="value">The name of the virtual channel</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    inline daqmx_power_channel& name(_In_z_ const char *value) {
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
    inline daqmx_power_channel& name(
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
    inline daqmx_power_channel& shunt_resistor_value(
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
    inline daqmx_power_channel& shunt_resistor_location(
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
    inline daqmx_power_channel& terminal_configuration(
            _In_ const daqmx_terminal_configuration value) noexcept {
        daqmx_channel::terminal_configuration(value);
        return *this;
    }

    /// <summary>
    /// Gets the name of the physical channel measuring voltage.
    /// </summary>
    /// <returns>The name of the physical channel measuring voltage.</returns>
    _Ret_z_ inline const char *voltage_channel(void) const noexcept {
        return daqmx_channel::channel();
    }

    /// <summary>
    /// Gets the maximum expected voltage in Volts.
    /// </summary>
    /// <returns>The maximum expected voltage, in Volts.</returns>
    inline double voltage_max_value(void) const noexcept {
        return daqmx_channel::max_value();
    }

    /// <summary>
    /// Sets the maximum expected voltage in Volts.
    /// </summary>
    /// <param name="value">The maximum expected voltage, in Volts.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    inline daqmx_power_channel& voltage_max_value(
            _In_ const double value) noexcept {
        daqmx_channel::max_value(value);
        return *this;
    }

    /// <summary>
    /// Gets the minimum expected voltage in Volts.
    /// </summary>
    /// <returns>The minimum expected voltage, in Volts.</returns>
    inline double voltage_min_value(void) const noexcept {
        return daqmx_channel::min_value();
    }

    /// <summary>
    /// Sets the minimum expected voltage in Volts.
    /// </summary>
    /// <param name="value">The minimum expected voltage, in Volts.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    inline daqmx_power_channel& voltage_min_value(
            _In_ const double value) noexcept {
        daqmx_channel::min_value(value);
        return *this;
    }

private:

    blob _current_channel;
    double _current_max_value;
    double _current_min_value;
    double _shunt_resistor_value;
    daqmx_shunt_resistor_location _shunt_resistor_location;
};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_DAQMX_POWER_CHANNEL_H) */
