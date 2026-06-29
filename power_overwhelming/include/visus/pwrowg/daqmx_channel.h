// <copyright file="daqmx_channel.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_DAQMX_CHANNEL_H)
#define _PWROWG_DAQMX_CHANNEL_H
#pragma once

#include <string>

#include "visus/pwrowg/blob.h"
#include "visus/pwrowg/daqmx_terminal_configuration.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// The base implementation of a channel configuration for NI-DAQmx devices.
/// </summary>
class POWER_OVERWHELMING_API daqmx_channel {

public:

    /// <summary>
    /// Gets the name of the physical channel to create the virtual channel on.
    /// </summary>
    /// <returns>The name of the physical channel.</returns>
    _Ret_z_ inline const char *channel(void) const noexcept {
        return this->_channel.as<char>();
    }

    /// <summary>
    /// Gets the maximum expected value in the unit used for the channel.
    /// </summary>
    /// <returns>The maximum expected value.</returns>
    inline double max_value(void) const noexcept {
        return this->_max_value;
    }

    /// <summary>
    /// Gets the minimum expected value in the unit used for the channel.
    /// </summary>
    /// <returns>The minimum expected value.</returns>
    inline double min_value(void) const noexcept {
        return this->_min_value;
    }

    /// <summary>
    /// Gets the name to assign to the virtual channel.
    /// </summary>
    /// <returns>The user-defined name of the channel.</returns>
    _Ret_z_ const char *name(void) const noexcept;

    /// <summary>
    /// Gets the input terminal configuration for the channel.
    /// </summary>
    /// <returns>The input terminal configuration.</returns>
    inline daqmx_terminal_configuration terminal_configuration(
            void) const noexcept {
        return this->_terminal_configuration;
    }

protected:

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="channel">The name of the physical channel, which should
    /// be something like &quot;Dev1/ai0&quot; for the first analog input.
    /// </param>
    explicit daqmx_channel(_In_z_ const wchar_t *channel);

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="channel">The name of the physical channel, which should
    /// be something like &quot;Dev1/ai0&quot; for the first analog input.
    /// </param>
    explicit daqmx_channel(_In_z_ const char *channel);

    /// <summary>
    /// Finalises the instance.
    /// </summary>
    virtual ~daqmx_channel(void) noexcept = default;

    /// <summary>
    /// Sets the maximum expected value.
    /// </summary>
    /// <param name="value">The maximum expected value for the channel.</param>
    inline void max_value(_In_ const double value) noexcept {
        this->_max_value = value;
    }

    /// <summary>
    /// Sets the minimal expected value.
    /// </summary>
    /// <param name="value">The minimum expected value for the channel.</param>
    inline void min_value(_In_ const double value) noexcept {
        this->_min_value = value;
    }

    /// <summary>
    /// Sets the name of the virtual channel.
    /// </summary>
    /// <param name="value">The name of the virtual channel</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    void name(_In_z_ const wchar_t *value);

    /// <summary>
    /// Sets the name of the virtual channel.
    /// </summary>
    /// <param name="value">The name of the virtual channel</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    void name(_In_z_ const char *value);

    /// <summary>
    /// Sets the name of the virtual channel.
    /// </summary>
    /// <typeparam name="TChar">The character type of the string.</typeparam>
    /// <typeparam name="TTraits">The character traits of the string.
    /// </typeparam>
    /// <typeparam name="TAlloc">The allocator of the string.</typeparam>
    /// <param name="value">The name of the virtual channel</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    template<class TChar, class TTraits, class TAlloc> inline void name(
            _In_ const std::basic_string<TChar, TTraits, TAlloc>& value) {
        return this->name(value.c_str());
    }

    /// <summary>
    /// Sets the input terminal configuration for the channel.
    /// </summary>
    /// <param name="value">The input terminal configuration.</param>
    inline void terminal_configuration(
            _In_ const daqmx_terminal_configuration value) noexcept {
        this->_terminal_configuration = value;
    }

private:

    blob _channel;
    double _max_value;
    double _min_value;
    blob _name;
    daqmx_terminal_configuration _terminal_configuration;
};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_DAQMX_CHANNEL_H) */
