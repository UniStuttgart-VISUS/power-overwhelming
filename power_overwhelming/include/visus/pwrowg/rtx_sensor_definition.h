// <copyright file="rtx_sensor_definition.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "visus/pwrowg/blob.h"
#include "visus/pwrowg/oscilloscope_channel.h"
#include "visus/pwrowg/oscilloscope_waveform_points.h"


namespace visus {
namespace power_overwhelming {

    /* Forward declarations. */
    class rtx_instrument;

    /// <summary>
    /// Defines a power sensor using a voltage and a current probe of an
    /// R &amp; S RTA/RTB oscilloscope.
    /// </summary>
    class POWER_OVERWHELMING_API rtx_sensor_definition final {

    public:

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <remarks>
        /// Please note that instances initialises with the default constructor
        /// are not usable to create sensors.
        /// </remarks>
        rtx_sensor_definition(void) = default;

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="path">The path to the VISA instrument to be used for
        /// the sensor, which must not be <c>nullptr</c>.</param>
        /// <param name="description">The description of the sensor, which must
        /// not be <c>nullptr</c>.</param>
        /// <param name="voltage_channel">The configuration of the channel to
        /// which the voltage probe is attached.</param>
        /// <param name="current_channel">The configuration of the channel to
        /// which the current probe is attached.</param>
        /// <param name="waveform_points">Specifies which points of the waveform
        /// are downloaded from the instrument to the sensor. This parameter
        /// defaults to the maximum resolution available in the memory of the
        /// instrument.</param>
        /// <exception cref="std::invalid_argument">If <paramref name="path" />
        /// is <c>nullptr</c> or an empty string.</exception>
        /// <exception cref="std::invalid_argument">If
        /// <paramref name="channel_voltage" /> and 
        /// <paramref name="channel_current" /> are the same or if the quantity
        /// measured by any of the channels is not what their intended use is.
        /// </exception>
        /// <exception cref="std::bad_alloc">If the memory for storing the
        /// description could not be allocated.</exception>
        rtx_sensor_definition(_In_z_ const wchar_t *path,
            _In_ const oscilloscope_channel& voltage_channel,
            _In_ const oscilloscope_channel& current_channel,
            _In_opt_z_ const wchar_t *description = nullptr,
            _In_ const oscilloscope_waveform_points waveform_points
            = oscilloscope_waveform_points::maximum);

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="path">The path to the VISA instrument to be used for
        /// the sensor, which must not be <c>nullptr</c>.</param>
        /// <param name="voltage_channel">The configuration of the channel to
        /// which the voltage probe is attached.</param>
        /// <param name="current_channel">The configuration of the channel to
        /// which the current probe is attached.</param>
        /// <param name="description">The description of the sensor.</param>
        /// <param name="waveform_points">Specifies which points of the waveform
        /// are downloaded from the instrument to the sensor. This parameter
        /// defaults to the maximum resolution available in the memory of the
        /// instrument.</param>
        /// <exception cref="std::invalid_argument">If <paramref name="path" />
        /// is <c>nullptr</c> or an empty string.</exception>
        /// <exception cref="std::invalid_argument">If
        /// <paramref name="channel_voltage" /> and 
        /// <paramref name="channel_current" /> are the same or if the quantity
        /// measured by any of the channels is not what their intended use is.
        /// </exception>
        /// <exception cref="std::bad_alloc">If the memory for storing the
        /// description could not be allocated.</exception>
        rtx_sensor_definition(_In_z_ const char *path,
            _In_ const oscilloscope_channel& voltage_channel,
            _In_ const oscilloscope_channel& current_channel,
            _In_opt_z_ const wchar_t *description = nullptr,
            _In_ const oscilloscope_waveform_points waveform_points
            = oscilloscope_waveform_points::maximum);

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="path">The path to the VISA instrument to be used for
        /// the sensor, which must not be <c>nullptr</c>.</param>
        /// <param name="channel_voltage">The channel which to the voltage probe
        /// is attached.</param>
        /// <param name="attenuation_voltage">The attenuation of the voltage
        /// probe in [V]. Consult the manual of the instrument on which values
        /// are valid for this parameter.</param>
        /// <param name="channel_current">The channel which to the current probe
        /// is attached.</param>
        /// <param name="attenuation_current">The attenuation of the current
        /// probe in [A]. Consult the manual of the instrument on which values
        /// are valid for this parameter.</param>
        /// <param name="description">The description of the sensor.</param>
        /// <param name="waveform_points">Specifies which points of the waveform
        /// are downloaded from the instrument to the sensor. This parameter
        /// defaults to the maximum resolution available in the memory of the
        /// instrument.</param>
        /// <exception cref="std::invalid_argument">If <paramref name="path" />
        /// is <c>nullptr</c> or an empty string.</exception>
        /// <exception cref="std::invalid_argument">If
        /// <paramref name="channel_voltage" /> and 
        /// <paramref name="channel_current" /> are the same.</exception>
        /// <exception cref="std::bad_alloc">If the memory for storing the
        /// description could not be allocated.</exception>
        rtx_sensor_definition(_In_z_ const wchar_t *path,
            _In_ const std::uint32_t channel_voltage,
            _In_ const float attenuation_voltage,
            _In_ const std::uint32_t channel_current,
            _In_ const float attenuation_current,
            _In_z_ const wchar_t *description = nullptr,
            _In_ const oscilloscope_waveform_points waveform_points
            = oscilloscope_waveform_points::maximum);

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="path">The path to the VISA instrument to be used for
        /// the sensor, which must not be <c>nullptr</c>.</param>
        /// <param name="channel_voltage">The channel which to the voltage probe
        /// is attached.</param>
        /// <param name="attenuation_voltage">The attenuation of the voltage
        /// probe in [V]. Consult the manual of the instrument on which values
        /// are valid for this parameter.</param>
        /// <param name="channel_current">The channel which to the current probe
        /// is attached.</param>
        /// <param name="attenuation_current">The attenuation of the current
        /// probe in [A]. Consult the manual of the instrument on which values
        /// are valid for this parameter.</param>
        /// <param name="description">The description of the sensor.</param>
        /// <param name="waveform_points">Specifies which points of the waveform
        /// are downloaded from the instrument to the sensor. This parameter
        /// defaults to the maximum resolution available in the memory of the
        /// instrument.</param>
        /// <exception cref="std::invalid_argument">If <paramref name="path" />
        /// <c>nullptr</c> or an empty string.</exception>
        /// <exception cref="std::invalid_argument">If
        /// <paramref name="channel_voltage" /> and 
        /// <paramref name="channel_current" /> are the same.</exception>
        /// <exception cref="std::bad_alloc">If the memory for storing the
        /// description could not be allocated.</exception>
        rtx_sensor_definition(_In_z_ const char *path,
            _In_ const std::uint32_t channel_voltage,
            _In_ const float attenuation_voltage,
            _In_ const std::uint32_t channel_current,
            _In_ const float attenuation_current,
            _In_opt_z_ const wchar_t *description = nullptr,
            _In_ const oscilloscope_waveform_points waveform_points
            = oscilloscope_waveform_points::maximum);

        /// <summary>
        /// Applies the channel configurations on the given instrument.
        /// </summary>
        /// <remarks>
        /// <para>This method will block the calling thread until the instrument
        /// has applied all changes.</para>
        /// </remarks>
        /// <param name="instrument">The instrument to apply the configuration
        /// of the sensor channels to.</param>
        void apply(_Inout_ rtx_instrument& instrument) const;

        /// <summary>
        /// Gets the attenuation of the current probe.
        /// </summary>
        /// <returns>The attenuation of the current probe if the current probe.
        /// </returns>
        inline const oscilloscope_quantity& attenuation_current(
                void) const noexcept {
            return this->_current_channel.attenuation();
        }

        /// <summary>
        /// Gets the attenuation of the voltage probe.
        /// </summary>
        /// <returns>The attenuation of the voltage probe if the current probe.
        /// </returns>
        inline const oscilloscope_quantity& attenuation_voltage(
                void) const noexcept {
            return this->_voltage_channel.attenuation();
        }

        /// <summary>
        /// Gets the channel of the current probe.
        /// </summary>
        /// <returns>The number of the channel which to the current probe is
        /// attached.</returns>
        inline std::uint32_t channel_current(void) const noexcept {
            return this->_current_channel.channel();
        }

        /// <summary>
        /// Gets the channel of the voltage probe.
        /// </summary>
        /// <returns>The number of the channel which to the voltage probe is
        /// attached.</returns>
        inline std::uint32_t channel_voltage(void) const noexcept {
            return this->_voltage_channel.channel();
        }

        /// <summary>
        /// Gets the configuration of the channel measuring the current.
        /// </summary>
        /// <returns>The channel configuration object.</returns>
        inline const oscilloscope_channel& current_channel(
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
        rtx_sensor_definition& description(
            _In_opt_z_ const wchar_t *description);

        /// <summary>
        /// Gets the VISA device path of the underlying instrument.
        /// </summary>
        /// <returns>The VISA device path of the underlying instrumen. The
        /// object remains owner of the string returned.</returns>
        inline _Ret_z_ const char *path(void) const noexcept {
            auto retval = this->_path.as<char>();
            _Analysis_assume_(retval != nullptr);
            return retval;
        }

        /// <summary>
        /// Gets the configuration of the channel measuring the current.
        /// </summary>
        /// <returns>The channel configuration object.</returns>
        inline const oscilloscope_channel& voltage_channel(
                void) const noexcept {
            return this->_voltage_channel;
        }

        /// <summary>
        /// Answer the waveform points that should be downloaded if the data for
        /// the channels of the are transferred to the computer.
        /// </summary>
        /// <returns>The waveform points to download.</returns>
        inline oscilloscope_waveform_points waveform_points(
                void) const noexcept {
            return this->_waveform_points;
        }

        /// <summary>
        /// Answer whether the sensor definition is valid for creating a sensor.
        /// </summary>
        /// <returns><c>true</c> if the configuration is valid, <c>false</c> if
        /// this instance was created using the default constructor.</returns>
        operator bool(void) const noexcept;

    private:

        void make_labels(void);

        oscilloscope_channel _current_channel;
        blob _description;
        blob _path;
        oscilloscope_channel _voltage_channel;
        oscilloscope_waveform_points _waveform_points;
    };

} /* namespace power_overwhelming */
} /* namespace visus */
