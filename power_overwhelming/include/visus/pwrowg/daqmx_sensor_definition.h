// <copyright file="daqmx_sensor_definition.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_DAQMX_SENSOR_DEFINITION_H)
#define _PWROWG_DAQMX_SENSOR_DEFINITION_H
#pragma once

#include "visus/pwrowg/blob.h"


PWROWG_NAMESPACE_BEGIN

// Forward declarations.
class daqmx_current_channel;
class daqmx_power_channel;
class daqmx_voltage_channel;


/// <summary>
/// Defines a power sensor using a voltage and a current channel of a NI-DAQmx
/// or a computed power channel on such a device.
/// </summary>
class POWER_OVERWHELMING_API daqmx_sensor_definition final {

public:

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <remarks>
    /// Please note that instances initialises with the default constructor
    /// are not usable to create sensors.
    /// </remarks>
    daqmx_sensor_definition(void) noexcept
        : _current_channel(nullptr),
        _power_channel(nullptr),
        _voltage_channel(nullptr),
        _voltage_for_current_channel(nullptr),
        _volt_per_ampere(0.0f) { }

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="voltage_channel"></param>
    /// <param name="current_channel"></param>
    /// <param name="description"></param>
    daqmx_sensor_definition(
        _In_ const daqmx_voltage_channel& voltage_channel,
        _In_ const daqmx_current_channel& current_channel,
        _In_opt_z_ const wchar_t *description = nullptr);

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="power_channel"></param>
    /// <param name="description"></param>
    explicit daqmx_sensor_definition(
        _In_ const daqmx_power_channel& power_channel,
        _In_opt_z_ const wchar_t *description = nullptr);

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="voltage_channel"></param>
    /// <param name="current_channel"></param>
    /// <param name="description"></param>
    daqmx_sensor_definition(
        _In_ const daqmx_voltage_channel& voltage_channel,
        _In_ const daqmx_voltage_channel& current_channel,
        _In_ const double volt_per_ampere,
        _In_opt_z_ const wchar_t *description = nullptr);

    /// <summary>
    /// Initialise a clone.
    /// </summary>
    /// <param name="other">The object to be cloned.</param>
    inline daqmx_sensor_definition(_In_ const daqmx_sensor_definition& other)
            : _current_channel(nullptr),
            _power_channel(nullptr),
            _voltage_channel(nullptr),
            _voltage_for_current_channel(nullptr) {
        *this = other;
    }

    /// <summary>
    /// Finalises the instance.
    /// </summary>
    ~daqmx_sensor_definition(void) noexcept;

    /// <summary>
    /// Answer the current channel, which may be <see langword="nullptr" /> if
    /// the sensor is defined using the built-in computed power channel.
    /// </summary>
    /// <returns>The current channel.</returns>
    inline _Ret_maybenull_ const daqmx_current_channel *current_channel(
            void) const noexcept {
        return this->_current_channel;
    }

    /// <summary>
    /// Gets the description of the sensor.
    /// </summary>
    /// <returns>The description of the sensor. The object remains owner of
    /// the string returned.</returns>
    inline _Ret_z_ const wchar_t *description(void) const noexcept {
        auto retval = this->_description.as<wchar_t>();
        _Analysis_assume_(retval != nullptr);
        return retval;
    }

    /// <summary>
    /// Sets a user-defined description of the sensor.
    /// </summary>
    /// <param name="description">The new description of the sensor.</param>
    /// <returns><c>*this</c>.</returns>
    daqmx_sensor_definition& description(_In_opt_z_ const wchar_t *description);

    /// <summary>
    /// Answer the power channel, which may be <see langword="nullptr" /> if
    /// the sensor is defined using a pair of voltage and current channels.
    /// </summary>
    /// <returns>The power channel.</returns>
    inline _Ret_maybenull_ const daqmx_power_channel *power_channel(
            void) const noexcept {
        return this->_power_channel;
    }

    /// <summary>
    /// Answer the voltage channel, which may be <see langword="nullptr" /> if
    /// the sensor is defined using the built-in computed power channel.
    /// </summary>
    /// <returns>The voltage channel.</returns>
    inline _Ret_maybenull_ const daqmx_voltage_channel *voltage_channel(
            void) const noexcept {
        return this->_voltage_channel;
    }

    /// <summary>
    /// Answer the current channel in case a current clamp is attached to a
    /// voltage channel to get current. This may be <see langword="nullptr" />
    /// if the sensor is defined using the built-in computed power channel.
    /// </summary>
    /// <returns>The current channel.</returns>
    inline _Ret_maybenull_ const daqmx_voltage_channel *
    voltage_for_current_channel(void) const noexcept {
        return this->_voltage_for_current_channel;
    }

    /// <summary>
    /// Answer the voltage reported per ampere of current for a configuration
    /// using a <see cref="voltage_for_current_channel" />. This value is
    /// undefined for any other kind of sensor definition.
    /// </summary>
    /// <returns>The Volts reported for an Ampere.</returns>
    inline double volt_per_ampere(void) const noexcept {
        return this->_volt_per_ampere;
    }

    /// <summary>
    /// Assignment.
    /// </summary>
    /// <param name="rhs">The right-hand-side operand.</param>
    /// <returns><c>*<see cref="this" /></c>.</returns>
    daqmx_sensor_definition& operator =(
        _In_ const daqmx_sensor_definition& rhs);

    /// <summary>
    /// Answer whether the sensor definition is valid for creating a sensor.
    /// </summary>
    /// <returns><c>true</c> if the configuration is valid, <c>false</c> if
    /// this instance was created using the default constructor.</returns>
    operator bool(void) const noexcept;

private:

    daqmx_current_channel *_current_channel;
    blob _description;
    daqmx_power_channel *_power_channel;
    daqmx_voltage_channel *_voltage_channel;
    daqmx_voltage_channel *_voltage_for_current_channel;
    double _volt_per_ampere;
};

PWROWG_NAMESPACE_END

#endif /*!defined(_PWROWG_DAQMX_SENSOR_DEFINITION_H) */
