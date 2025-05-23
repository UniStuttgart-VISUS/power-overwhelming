﻿// <copyright file="rtx_sensor.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "visus/pwrowg/measurement_data_series.h"
#include "visus/pwrowg/rtx_sample.h"
#include "visus/pwrowg/sensor.h"
#include "visus/pwrowg/rtx_instrument.h"
#include "visus/pwrowg/rtx_instrument_configuration.h"
#include "visus/pwrowg/rtx_sensor_definition.h"
#include "visus/pwrowg/waveform_decimation_method.h"


namespace visus {
namespace power_overwhelming {

    /* Forward declarations */
    namespace detail { struct rtx_sensor_impl; }


    /// <summary>
    /// A sensor using a Rohde &amp; Schwarz RTA and RTB series oscilloscope.
    /// </summary>
    class POWER_OVERWHELMING_API rtx_sensor final : public sensor {

    public:

        //static void acquire(_Out_writes_(cnt) measurement_data_series *dst,
        //    _In_reads_(cnt) rtx_sensor *sensors,
        //    _In_ const std::size_t cnt,
        //    _In_ const timestamp_resolution resolution
        //    = timestamp_resolution::milliseconds);

        /// <summary>
        /// Applies the given configuration to the instruments used by the
        /// given sensors.
        /// </summary>
        /// <param name="sensors">An array of sensors for which a consistent
        /// configuration should be applied on the underlying instrument.
        /// </param>
        /// <param name="cnt">The number of <paramref name="sensors" />.</param>
        /// <param name="configuration">The configuration to be applied to the
        /// instruments used by the sensors.</param>
        /// <returns>A reference to the instrument that was designated as the
        /// master instrument and needs to be triggered in order to initiate
        /// the measurement. All other instrumens are configured as slaves and
        /// receive the trigger signal via the external trigger input.</returns>
        /// <exception cref="invalid_argument">If the
        /// <paramref name="sensors" /> array is <c>nullptr</c>, or if
        /// <paramref name="cnt" /> is zero, or if
        /// <paramref name="configuration" /> is a configuration for a slave
        /// instrument.</exception>
        static _Ret_maybenull_ rtx_instrument *configure_instrument(
            _In_reads_(cnt) rtx_sensor *sensors,
            _In_ const std::size_t cnt,
            _In_ const rtx_instrument_configuration& configuration);

        /// <summary>
        /// Create sensor objects for all Rohde &amp; Schwarz RTA/RTB
        /// instruments that can be enumerated via VISA.
        /// </summary>
        /// <remarks>
        /// <para>This method will apply a default configuration to all
        /// channels, which assume the voltage probe attached to all odd
        /// channels and the corresponding current probe to the next even
        /// channel. If the number of channels is not divisible by two, the
        /// channels at the end are unused.</para>
        /// <para>Aside from the channel index and the quantity (voltage or
        /// current), the default configuration of
        /// <see cref="rtx_channel" /> is applied to each channel. If
        /// you need to customise the probes, use <see cref="get_definitions" />
        /// with a custom template and create the sensors from there.</para>
        /// <para>The method will apply the default
        /// <see cref="rtx_instrument_configuration" /> with the provided
        /// <paramref name="time_range" /> to all instruments used by the
        /// sensors. The instrument used by the first sensor returned will
        /// be configured to be the master instrument that must be triggered
        /// for measurement. All other instruments are configured as slaves
        /// that trigger on the external trigger input. If this is not
        /// desirable, you can always reconfigure the instruments by calling
        /// <see cref="configure_instrument" /> on the list of sensors.</para>
        /// </remarks>
        /// <param name="dst ">An array receiving the sensors. If this is
        /// <c>nullptr</c>, nothing is returned. This buffer must be able to
        /// hold at least <paramref name="cnt" /> elements.</param>
        /// <param name="cnt">The number of sensors that can be stored in
        /// <paramref name="dst" />.</param>
        /// <param name="time_range">The time range in milliseconds for a
        /// single acquisition, that is configured on all instruments using the
        /// <see cref="rtx_instrument_configuration" />. Callers can modify
        /// this parts afterwards by passing all sensors to
        /// <see cref="configure_instrument" /> with another configuration
        /// object.</param>
        /// <param name="samples">The number of samples the instrument is
        /// configured to acquire during <paramref name="time_range" />. This
        /// parameter defaults to the minimum of 5000 sample points. Note that
        /// increasing the number of points might significantly slow down the
        /// sensor as the download of the data becomes slower.</param>
        /// <param name="decimation_method">Determines how the sensor converts
        /// a waveform into a single sample.</param>
        /// <param name="timeout">The timeout in milliseconds for establishing a
        /// connection to each instrument that was found. This parameter defaults
        /// to <see cref="visa_instrument::default_timeout" />.</param>
        /// <returns>The number of RTA/RTB instruments found, regardless of how
        /// many have been returned to <paramref name="dst" />.</returns>
        static std::size_t for_all(
            _When_(dst != nullptr, _Out_writes_opt_(cnt)) rtx_sensor *dst,
            _In_ std::size_t cnt,
            _In_ const visa_instrument::timeout_type time_range = 200,
            _In_ const unsigned int samples = 5000,
            _In_ const waveform_decimation_method decimation_method
            = waveform_decimation_method::rms,
            _In_ const visa_instrument::timeout_type timeout
            = visa_instrument::default_timeout);

        /// <summary>
        /// Determines all possible <see cref="rtx_sensor" />s from instruments
        /// connected to the local machine.
        /// </summary>
        /// <param name="dst">A buffer to receive at most
        /// <paramref name="cnt" /> definitions for oscilloscope sensors. It
        /// is safe to pass <c>nullptr</c>, in which case nothing will be
        /// written.</param>
        /// <param name="cnt">The number of elements that can be written to
        /// <paramref name="dst" />.</param>
        /// <param name="voltage_channel">A configuration template for the
        /// voltage channels. The method will copy this template except for
        /// the channel indices, which will be created on the fly.</param>
        /// <param name="current_channel">A configuration template for the
        /// current channels. The method will copy this template except for
        /// the channel indices, which will be created on the fly.</param>
        /// <param name="force_cannels">If not zero, make the method assume that
        /// all devices support the specified number of channels instead of
        /// probing the devices. As the probing code relies on queries failing
        /// and timeouts, this can be a massive speed and reliability boost in
        /// case all instruments are known to have the same number of channels.
        /// </param>
        /// <param name="timeout">A timeout in milliseconds which is used when
        /// connecting to the instrument. This parameter defaults to
        /// <see cref="visa_instrument::default_timeout" />.</param>
        /// <returns>The number of sensor definitions available, regardless of
        /// whether all of them were written or not.</returns>
        static std::size_t get_definitions(
            _When_(dst != nullptr, _Out_writes_opt_(cnt)) rtx_sensor_definition *dst,
            _In_ const std::size_t cnt,
            _In_ const rtx_channel& voltage_channel,
            _In_ const rtx_channel& current_channel,
            _In_ const std::size_t force_channels = 0,
            _In_ const visa_instrument::timeout_type timeout
            = visa_instrument::default_timeout);

        /// <summary>
        /// Determines all possible <see cref="rtx_sensor" />s from instruments
        /// connected to the local machine.
        /// </summary>
        /// <param name="dst">A buffer to receive at most
        /// <paramref name="cnt" /> definitions for oscilloscope sensors. It
        /// is safe to pass <c>nullptr</c>, in which case nothing will be
        /// written.</param>
        /// <param name="cnt">The number of elements that can be written to
        /// <paramref name="dst" />.</param>
        /// <param name="voltage_attenuation">The attenuation that will be
        /// configured for probes measuring voltage.</param>
        /// <param name="current_attenuation">The attenuation that will be
        /// configurated for probes measuring current.</param>
        /// <param name="decimation_method">Determines how the sensor converts
        /// a waveform into a single sample.</param>
        /// <param name="timeout">A timeout in milliseconds which is used when
        /// connecting to the instrument. This parameter defaults to
        /// <see cref="visa_instrument::default_timeout" />.</param>
        /// <returns>The number of sensor definitions available, regardless of
        /// whether all of them were written or not.</returns>
        static std::size_t get_definitions(
            _When_(dst != nullptr, _Out_writes_opt_(cnt)) rtx_sensor_definition *dst,
            _In_ const std::size_t cnt,
            _In_ const float voltage_attenuation = 10.0f,
            _In_ const float current_attenuation = 10.0f,
            _In_ const std::size_t force_channels = 0,
            _In_ const visa_instrument::timeout_type timeout
            = visa_instrument::default_timeout);

        /// <summary>
        /// Obtains two or more waveforms from the given instrument.
        /// </summary>
        /// <param name="device">The instrument to be sampled.</param>
        /// <returns>The <see cref="rtx_sample" /> obtained from the
        /// instrument.</returns>
        static rtx_sample sample(_In_ const rtx_instrument& device);

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        rtx_sensor(void);

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="definition">The definition of the sensor, which must
        /// contain the path of the instrument and the configuration of the
        /// voltage and the current channel.</param>
        /// <param name="decimation_method">Determines how the sensor converts
        /// a waveform into a single sample.</param>
        /// <param name="timeout">The timeout for connecting to the instrument,
        /// in milliseconds, which is also set as the initial VISA timeout. Make
        /// sure to choose a sufficiently large number to wait for the channels
        /// being configured. This parameter defaults to
        /// <see cref="visa_instrument::default_timeout" />.</param>
        /// <param name="instrument_config">If not <c>nullptr</c>, apply the
        /// specified configuration to the instrument used provided the
        /// instrument has not yet been opened before.</param>
        /// <exception cref="std::invalid_argument">If <paramref name="path" />
        /// is <c>nullptr</c>.</exception>
        /// <exception cref="std::bad_alloc">If the memory for the sensor state
        /// could not be allocated.</exception>
        /// <exception cref="std::system_error">If the VISA library could not be
        /// loaded.</exception>
        /// <exception cref="visa_exception">If the sensor could not be
        /// initialised.</exception>
        explicit rtx_sensor(_In_ const rtx_sensor_definition& definition,
            _In_ const waveform_decimation_method decimation_method
            = waveform_decimation_method::rms,
            _In_ const visa_instrument::timeout_type timeout
            = visa_instrument::default_timeout,
            _In_opt_ const rtx_instrument_configuration *instrument_config
            = nullptr);

        /// <summary>
        /// Move <paramref name="rhs" /> into a new instance.
        /// </summary>
        /// <param name="rhs">The object to be moved.</param>
        rtx_sensor(_Inout_ rtx_sensor&& rhs) noexcept;

        /// <summary>
        /// Finalise the instance.
        /// </summary>
        virtual ~rtx_sensor(void) noexcept;

        /// <summary>
        /// Acquires two waveforms from the underlying instrument and combines
        /// these into a data series of corresponding voltage and current
        /// measurements.
        /// </summary>
        /// <remarks>
        /// <para>This method assumes that the instrument and its channels have
        /// been properly configured and not been changed since. Most
        /// importantly, it is assume that the instrument is in single
        /// acquisition mode.</para>
        /// <para>The method will run a single acquisition on the instrument and
        /// afterwards download the full-resolution data of the channels
        /// configured for voltage and current for this sensor. Other sensors
        /// using the same instrument might acquire data as well, but these will
        /// not be processed.</para>
        /// <para>This method will block until the acquisition completed.
        /// Callers must make sure that, if a trigger has been configured and
        /// the instrument is triggering in normal mode, the trigger actually
        /// occurs within the timeout period of the instrument. If the
        /// acquisition times out because of the lack of a trigger, the method
        /// will fail.</para>
        /// <para>This method will download two waveforms from the instrument at
        /// their native resolution. This might take a significant amount of
        /// time, during which the calling thread will be blocked, depending on
        /// the number of sample points the underlying instrument is configured
        /// to obtain for a single acquisition.</para>
        /// </remarks>
        /// <returns>The data series for the waveforms acquired from the
        /// instrument.</returns>
        measurement_data_series acquire(void) const;

        /// <summary>
        /// Answer the channel on which the current is measured.
        /// </summary>
        /// <returns>The one-based index of the channel with the current probe.
        /// </returns>
        rtx_instrument::channel_type channel_current(void) const noexcept;

        /// <summary>
        /// Answer the channel on which voltage is measured.
        /// </summary>
        /// <returns>The one-based index of the channel with the voltage probe.
        /// </returns>
        rtx_instrument::channel_type channel_voltage(void) const noexcept;

        /// <summary>
        /// Answer the method the sensor uses to transform a waveform into a
        /// single sample of type <see cref="measurement_data" />.
        /// </summary>
        /// <returns>The decimation method collapsing a waveform into a single
        /// sample.</returns>
        waveform_decimation_method decimation_method(void) const noexcept;

        /// <summary>
        /// Answer the instrument that is being used by the sensor.
        /// </summary>
        /// <remarks>
        /// <para>The instrument may be used by more than one sensor. Make sure
        /// not to make any changes to the configuration of the instrument that
        /// might influence the sensors created on the instrument. Additionally,
        /// you should not trigger manual acquisitions on an instrument that is
        /// used by one or more sensors, but only acquire data via the sensor.
        /// </para>
        /// </remarks>
        /// <returns>The instrument used by the sensor. The sensor remains the
        /// owner of the memory returned. Callers must not release or move the
        /// instrument returned.</returns>
        _Ret_maybenull_ rtx_instrument *instrument(void) noexcept;

        /// <summary>
        /// Answer the instrument that is being used by the sensor.
        /// </summary>
        /// <remarks>
        /// <para>The instrument may be used by more than one sensor. Make sure
        /// not to make any changes to the configuration of the instrument that
        /// might influence the sensors created on the instrument. Additionally,
        /// you should not trigger manual acquisitions on an instrument that is
        /// used by one or more sensors, but only acquire data via the sensor.
        /// </para>
        /// </remarks>
        /// <returns>The instrument used by the sensor. The sensor remains the
        /// owner of the memory returned. Callers must not release or move the
        /// instrument returned.</returns>
        _Ret_maybenull_ const rtx_instrument *instrument(void) const noexcept;

        /// <summary>
        /// Gets the name of the sensor.
        /// </summary>
        /// <remarks>
        /// It is safe to call this method on a disposed object, in which case
        /// the name will be <c>nullptr</c>.
        /// </remarks>
        /// <returns>The implementation-defined, human-readable name of the
        /// sensor.</returns>
        _Ret_maybenull_z_ virtual const wchar_t *name(
            void) const noexcept override;

        /// <summary>
        /// Gets the VISA path of the instrument.
        /// </summary>
        /// <returns>The path of the instrument.</returns>
        _Ret_maybenull_z_ const char *path(void) const noexcept;

        using sensor::sample;

        /// <summary>
        /// Move assignment.
        /// </summary>
        /// <param name="rhs">The right-hand side operand</param>
        /// <returns><c>*this</c></returns>
        rtx_sensor& operator =(_Inout_ rtx_sensor&& rhs) noexcept;

        /// <summary>
        /// Determines whether the sensor is valid.
        /// </summary>
        /// <remarks>
        /// A sensor is considered valid until it has been disposed by a move
        /// operation.
        /// </remarks>
        /// <returns><c>true</c> if the sensor is valid, <c>false</c>
        /// otherwise.</returns>
        virtual operator bool(void) const noexcept override;

    protected:

        /// <inheritdoc />
        void sample_async(_Inout_ async_sampling&& sampling) override;

        /// <inheritdoc />
        measurement_data sample_sync(void) const override;

    private:

        static void configure_new(_In_ rtx_instrument& instrument,
            _In_opt_ void *configuration);

        static measurement_data decimate(
            _In_ const measurement_data_series& series,
            _In_ const waveform_decimation_method method);

        rtx_instrument& check_not_disposed(void);

        const rtx_instrument& check_not_disposed(void) const;

        void initialise(_In_ const rtx_sensor_definition& definition,
            _In_ const visa_instrument::timeout_type timeout);

        detail::rtx_sensor_impl *_impl;
    };

} /* namespace power_overwhelming */
} /* namespace visus */
