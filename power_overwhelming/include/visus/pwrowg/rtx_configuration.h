// <copyright file="rtx_configuration.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_RTX_CONFIGURATION_H)
#define _PWROWG_RTX_CONFIGURATION_H
#pragma once

#include <chrono>
#include <cstdlib>
#include <type_traits>

#include "visus/pwrowg/guid.h"
#include "visus/pwrowg/rtx_quantity.h"
#include "visus/pwrowg/rtx_sensor_definition.h"
#include "visus/pwrowg/rtx_instrument_configuration.h"
#include "visus/pwrowg/rtx_instrument_reset.h"
#include "visus/pwrowg/rtx_sensor_trigger.h"
#include "visus/pwrowg/sensor_configuration.h"
#include "visus/pwrowg/string_functions.h"
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
    /// Deserialises a JSON string into a new
    /// <see cref="rtx_configuration" /> object.
    /// </summary>
    /// <param name="json">The JSON text to be parsed.</param>
    /// <returns>The configuration object encoded in the given JSON.</returns>
    static rtx_configuration from_json(_In_z_ const char *json);

    /// <summary>
    /// Loads an <see cref="rtx_configuration" /> from a JSON file.
    /// </summary>
    /// <param name="path">The path to the JSON file to be parsed.</param>
    /// <returns>The configuration object encoded in the given JSON file.
    /// </returns>
    static rtx_configuration load(_In_z_ const wchar_t *path);


    /// <summary>
    /// Loads an <see cref="rtx_configuration" /> from a JSON file.
    /// </summary>
    /// <param name="path">The path to the JSON file to be parsed.</param>
    /// <returns>The configuration object encoded in the given JSON file.
    /// </returns>
    static rtx_configuration load(_In_z_ const char *path);

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
    /// Gets the base configuration to be applied to all instruments.
    /// </summary>
    /// <returns>The base configuration to be applied to all instruments.
    /// </returns>
    inline const rtx_instrument_configuration& base_configuration(
            void) const noexcept {
        return this->_base_configuration;
    }

    /// <summary>
    /// Sets the base configuration to be applied to all instruments.
    /// </summary>
    /// <remarks>
    /// This configuration is the baseline for all instruments, but the settings
    /// for each instrument will be adjusted depending on the sensor definition
    /// on said instrument. That means that settings that are relevant for the
    /// sensor might be overwritten before applying the configuration to the
    /// instrument.
    /// </remarks>
    /// <param name="config">The base configuration.</param>
    /// <returns><c>*<see cref="this" /></c>.</returns>
    inline rtx_configuration& base_configuration(
            _In_ const rtx_instrument_configuration& config) noexcept {
        this->_base_configuration = config;
        return *this;
    }

    /// <summary>
    /// Sets the base configuration to be applied to all instruments.
    /// </summary>
    /// <remarks>
    /// This configuration is the baseline for all instruments, but the settings
    /// for each instrument will be adjusted depending on the sensor definition
    /// on said instrument. That means that settings that are relevant for the
    /// sensor might be overwritten before applying the configuration to the
    /// instrument.
    /// </remarks>
    /// <param name="config">The base configuration.</param>
    /// <returns><c>*<see cref="this" /></c>.</returns>
    inline rtx_configuration& base_configuration(
            _Inout_ rtx_instrument_configuration&& config) noexcept {
        this->_base_configuration = std::move(config);
        return *this;
    }

    /// <summary>
    /// Answer the number of sensors (voltage/current pairs) that have been
    /// configured.
    /// </summary>
    /// <returns>The number of configured sensors.</returns>
    std::size_t count_sensors(void) const noexcept;

    /// <summary>
    /// Answer how often the sensor should try to increase the download timeout
    /// before giving up.
    /// </summary>
    /// <returns>The number of retries for downloading channel data.</returns>
    inline std::size_t download_retries(void) const noexcept {
        return this->_download_retries;
    }

    /// <summary>
    /// Configure how often the sensor should retry downloading the channel data
    /// if the operation timed out.
    /// </summary>
    /// <param name="download_retries">The number of retries, or zero if the
    /// download must succeed on first try.</param>
    /// <returns><c>*<see cref="this" /></c>.</returns>
    inline rtx_configuration& download_retries(
            _In_ const std::size_t download_retries) noexcept {
        this->_download_retries = download_retries;
        return *this;
    }

    /// <summary>
    /// Answer the initial timeout for the data download in milliseconds.
    /// </summary>
    /// <returns>The download timeout in milliseconds, or zero if the default
    /// timeout of the instrument should be used.</returns>
    inline timeout_type download_timeout(void) const noexcept {
        return this->_download_timeout;
    }

    /// <summary>
    /// Configure a custom timeout for downloading the channel data.
    /// </summary>
    /// <param name="download_timeout">The timeout used for downloading the
    /// channel data, or zero to use the timeout set on the instrument when the
    /// download is started.</param>
    /// <returns><c>*<see cref="this" /></c>.</returns>
    inline rtx_configuration& download_timeout(
            _In_ const timeout_type download_timeout) noexcept {
        this->_download_timeout = download_timeout;
        return *this;
    }

    /// <summary>
    /// Answer the flags used to reset the instrument on start or when
    /// enumerating.
    /// </summary>
    /// <returns>The reset flags, which defaults to
    /// <see cref="rtx_instrument_reset::reset" /> and
    /// <see cref="rtx_instrument_reset::status" />.</returns>
    inline rtx_instrument_reset reset_flags(void) const noexcept {
        return this->_reset_flags;
    }

    /// <summary>
    /// Sets what it to reset when starting the sensor or when enumerating.
    /// </summary>
    /// <param name="flags">The reset flags.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    inline rtx_configuration& reset_flags(
            _In_ const rtx_instrument_reset flags) noexcept {
        this->_reset_flags = flags;
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
    /// Saves the configuration to a JSON file.
    /// </summary>
    /// <param name="path">The location of the output file.</param>
    void save(_In_z_ const wchar_t *path) const;

    /// <summary>
    /// Saves the configuration to a JSON file.
    /// </summary>
    /// <param name="path">The location of the output file.</param>
    void save(_In_z_ const char *path) const;

    /// <summary>
    /// Answer the <paramref name="index" />th sensor.
    /// </summary>
    /// <param name="index">The zero-based index of the sensor.</param>
    /// <returns>The sensor definition at the specified index.</returns>
    /// <exception cref="std::out_of_range">The index is greater than or equal
    /// to the number of sensors.</exception>
    const rtx_sensor_definition& sensor(_In_ const std::size_t index) const;

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

    rtx_instrument_configuration _base_configuration;
    std::size_t _download_retries;
    timeout_type _download_timeout;
    rtx_instrument_reset _reset_flags;
    bool _reset_on_enumerate;
    type_erased_storage _sensors;
    rtx_sensor_trigger _trigger;

};

PWROWG_NAMESPACE_END

#endif /*!defined(_PWROWG_RTX_CONFIGURATION_H) */
