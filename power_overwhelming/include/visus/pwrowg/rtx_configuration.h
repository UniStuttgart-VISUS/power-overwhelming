// <copyright file="rtx_configuration.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_RTX_CONFIGURATION_H)
#define _PWROWG_RTX_CONFIGURATION_H
#pragma once

#include "visus/pwrowg/guid.h"
#include "visus/pwrowg/rtx_instrument.h"
#include "visus/pwrowg/rtx_sensor_definition.h"
#include "visus/pwrowg/rtx_instrument_configuration.h"
#include "visus/pwrowg/rtx_sensor_trigger.h"
#include "visus/pwrowg/sensor_configuration.h"
#include "visus/pwrowg/type_erased_storage.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// The configuration for a sensor based on Rohde &amp; Schwarz RTA/RTB
/// oscilloscopes. As an oscilloscope only measures voltage over time, its
/// channel have no inherent meaning attached to them. Therefore, the sensor
/// will not work without manually configuring pairs of channel that measure
/// voltage and current for one rail. This is achieved by adding
/// <see cref="rtx_sensor_definition" />s to a configuration.
/// </summary>
class POWER_OVERWHELMING_API rtx_configuration final
        : public sensor_configuration {

public:

    /// <summary>
    /// The type used to represent a device timeout.
    /// </summary>
#if defined(POWER_OVERWHELMING_WITH_VISA)
    typedef rtx_instrument::timeout_type timeout_type;
#else /* !defined(POWER_OVERWHELMING_WITH_VISA) */
    typedef std::uint32_t timeout_type;
#endif /* !defined(POWER_OVERWHELMING_WITH_VISA) */

    /// <summary>
    /// A unique identifier for the <see cref="rtx_configuration" /> type.
    /// </summary>
    static const guid id;

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    rtx_configuration(void);

    /// <summary>
    /// Adds a new sensor definition to the configuration.
    /// </summary>
    /// <param name="sensor">The sensor to be added.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    rtx_configuration& add_sensor(_In_ const rtx_sensor_definition& sensor);

    /// <summary>
    /// Adds a new sensor definition to the configuration.
    /// </summary>
    /// <param name="sensor">The sensor to be added.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    rtx_configuration& add_sensor(_Inout_ rtx_sensor_definition&& sensor);

    /// <summary>
    /// Creates a new <see cref="rtx_sensor_definition" /> with the given parameters
    /// and adds it to the configuration.
    /// </summary>
    /// <param name="path"></param>
    /// <param name="voltage_channel"></param>
    /// <param name="current_channel"></param>
    /// <param name="waveform_points"></param>
    /// <returns></returns>
    rtx_configuration& add_sensor(_In_z_ const wchar_t *path,
        _In_ const rtx_channel& voltage_channel,
        _In_ const rtx_channel& current_channel,
        _In_ const rtx_waveform_points waveform_points
        = rtx_waveform_points::maximum);

    /// <summary>
    /// Creates a new <see cref="rtx_sensor_definition" /> with the given parameters
    /// and adds it to the configuration.
    /// </summary>
    /// <param name="path"></param>
    /// <param name="voltage_channel"></param>
    /// <param name="current_channel"></param>
    /// <param name="waveform_points"></param>
    /// <returns></returns>
    rtx_configuration& add_sensor(_In_z_ const char *path,
        _In_ const rtx_channel& voltage_channel,
        _In_ const rtx_channel& current_channel,
        _In_ const rtx_waveform_points waveform_points
        = rtx_waveform_points::maximum);

    /// <summary>
    /// Creates a new <see cref="rtx_sensor_definition" /> with the given parameters
    /// and adds it to the configuration.
    /// </summary>
    /// <param name="path"></param>
    /// <param name="channel_voltage"></param>
    /// <param name="attenuation_voltage"></param>
    /// <param name="channel_current"></param>
    /// <param name="attenuation_current"></param>
    /// <param name="waveform_points"></param>
    /// <returns></returns>
    rtx_configuration& add_sensor(_In_z_ const wchar_t *path,
        _In_ const std::uint32_t channel_voltage,
        _In_ const float attenuation_voltage,
        _In_ const std::uint32_t channel_current,
        _In_ const float attenuation_current,
        _In_ const rtx_waveform_points waveform_points
        = rtx_waveform_points::maximum);

    /// <summary>
    /// Creates a new <see cref="rtx_sensor_definition" /> with the given parameters
    /// and adds it to the configuration.
    /// </summary>
    /// <param name="path"></param>
    /// <param name="channel_voltage"></param>
    /// <param name="attenuation_voltage"></param>
    /// <param name="channel_current"></param>
    /// <param name="attenuation_current"></param>
    /// <param name="waveform_points"></param>
    /// <returns></returns>
    rtx_configuration& add_sensor(_In_z_ const char *path,
        _In_ const std::uint32_t channel_voltage,
        _In_ const float attenuation_voltage,
        _In_ const std::uint32_t channel_current,
        _In_ const float attenuation_current,
        _In_ const rtx_waveform_points waveform_points
        = rtx_waveform_points::maximum);

    /// <summary>
    /// Answer whether a non-default instrument configuration has been set that
    /// should vbe applied to the oscilloscopes after resetting them.
    /// </summary>
    /// <remarks>
    /// This property is <see langword="false" /> unless a configuration has
    /// been set by the user. If no specific configuration has been set, the
    /// instruments will remain in the default state after resetting, except for
    /// the settings influenced by the sensor definition and the trigger
    /// definition.
    /// </remarks>
    /// <returns><see langword="true" /> if the oscilloscopes should be
    /// configured according to the provided user settings,
    /// <see langword="false" /> otherwise.</returns>
    inline bool configure_instruments(void) const noexcept {
        return this->_configure_instruments;
    }

    /// <summary>
    /// Answer the number of sensors (voltage/current pairs) that have been
    /// configured.
    /// </summary>
    /// <returns>The number of configured sensors.</returns>
    std::size_t count_sensors(void) const noexcept;

    /// <summary>
    /// Gets the configuration that will be applied to the oscilloscopes at
    /// startup. Depending on the trigger configuration, the oscilloscope that
    /// is triggering might be configured differently from the other ones.
    /// </summary>
    /// <returns>The instrument configuration.</returns>
    inline const rtx_instrument_configuration& instrument_configuration(
            void) const noexcept {
        return this->_instrument_configuration;
    }

    /// <summary>
    /// Gets the configuration that will be applied to the oscilloscopes at
    /// startup. Depending on the trigger configuration, the oscilloscope that
    /// is triggering might be configured differently from the other ones.
    /// </summary>
    /// <returns>The instrument configuration.</returns>
    inline rtx_instrument_configuration& instrument_configuration(
            void) noexcept {
        return this->_instrument_configuration;
    }

    /// <summary>
    /// Sets a new default instrument configuration that will be applied to the
    /// oscilloscopes at startup.
    /// </summary>
    /// <param name="config"></param>
    /// <returns></returns>
    inline rtx_configuration& instrument_configuration(
            _In_ const rtx_instrument_configuration& config) {
        this->_instrument_configuration = config;
        this->_configure_instruments = true;
        return *this;
    }

    /// <summary>
    /// Sets a new default instrument configuration that will be applied to the
    /// oscilloscopes at startup.
    /// </summary>
    /// <param name="config"></param>
    /// <returns></returns>
    inline rtx_configuration& instrument_configuration(
            _Inout_ rtx_instrument_configuration&& config) noexcept {
        this->_instrument_configuration = std::move(config);
        this->_configure_instruments = true;
        return *this;
    }

    /// <summary>
    /// Indicates whether the oscilloscopes should be reset when enumerating the
    /// sensor descriptions.
    /// </summary>
    /// <returns><see langword="true" /> if the instruments should be reset,
    /// <see langword="false" /> (the default) otherwise.</returns>
    inline bool reset_on_enumerate(void) const noexcept {
        return this->_reset_on_enumerate;
    }

    /// <summary>
    /// Instructs the sensor array on whether it should reset the oscilloscopes
    /// when enumerating the sensor descriptions. This makes enumerating the
    /// instruments significantly slower, but if it is unclear whether the
    /// devices are in a defined state or not, it might be helpful to clear all
    /// VISA buffers on start to make sure that the device names etc. can be
    /// safely read or that the application fails early if this is not the case.
    /// </summary>
    /// <param name="reset">Controls whether the reset should be done or not.
    /// </param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    inline rtx_configuration& reset_on_enumerate(
            _In_ const bool reset) noexcept {
        this->_reset_on_enumerate = reset;
        return *this;
    }

    /// <summary>
    /// Answer the array of registered <see cref="rtx_sensor_definition" />s.
    /// </summary>
    /// <remarks>
    /// The size of the array can be obtained from
    /// <see cref="count_sensors" />.
    /// </remarks>
    /// <returns>The configured sensors.</returns>
    _Ret_valid_ const rtx_sensor_definition *sensors(void) const noexcept;

    /// <summary>
    /// Replaces any existing <see cref="rtx_sensor_definition" />s with the given
    /// array of new sensors.
    /// </summary>
    /// <param name="sensors">An array of at least <paramref name="cnt" /> sensor
    /// definitions.</param>
    /// <param name="cnt">The number of sensor definitions provided.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    rtx_configuration& sensors(
        _In_reads_opt_(cnt) rtx_sensor_definition *sensors,
        _In_ const std::size_t cnt);

    /// <summary>
    /// Gets the trigger configuration object.
    /// </summary>
    /// <returns>The sensor trigger configuration.</returns>
    inline const rtx_sensor_trigger& trigger(void) const noexcept {
        return this->_trigger;
    }

    /// <summary>
    /// Sets the trigger configuration.
    /// </summary>
    /// <param name="trigger">The new trigger configuration which determines how
    /// the underlying oscilloscopes are controlled.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    rtx_configuration& trigger(_In_ const rtx_sensor_trigger& trigger) {
        this->_trigger = trigger;
        return *this;
    }

    /// <summary>
    /// Answer the timeout to be used for all VISA instruments.
    /// </summary>
    /// <returns>The timeout in milliseconds.</returns>
    inline timeout_type timeout(void) const noexcept {
        return this->_timeout;
    }

    /// <summary>
    /// Sets the timeout to be used for all VISA instruments.
    /// </summary>
    /// <param name="timeout">The timeout, in milliseconds.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    rtx_configuration& timeout(_In_ const timeout_type timeout) noexcept {
        this->_timeout = timeout;
        return *this;
    }

    /// <summary>
    /// Sets the trigger configuration.
    /// </summary>
    /// <param name="trigger">The new trigger configuration which determines how
    /// the underlying oscilloscopes are controlled.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    rtx_configuration& trigger(_Inout_ rtx_sensor_trigger&& trigger) noexcept {
        this->_trigger = std::move(trigger);
        return *this;
    }

private:

    bool _configure_instruments;
    rtx_instrument_configuration _instrument_configuration;
    bool _reset_on_enumerate;
    type_erased_storage _sensors;
    timeout_type _timeout;
    rtx_sensor_trigger _trigger;
};

PWROWG_NAMESPACE_END

#endif /*!defined(_PWROWG_RTX_CONFIGURATION_H) */
