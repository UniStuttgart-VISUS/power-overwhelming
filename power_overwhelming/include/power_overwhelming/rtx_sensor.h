// <copyright file="rtx_sensor.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "power_overwhelming/sensor.h"
#include "power_overwhelming/rtx_instrument.h"
#include "power_overwhelming/rtx_instrument_configuration.h"
#include "power_overwhelming/rtx_sensor_definition.h"


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// A sensor using a Rohde &amp; Schwarz RTA and RTB series oscilloscope.
    /// </summary>
    class POWER_OVERWHELMING_API rtx_sensor final : public sensor {

    public:

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
        rtx_instrument& configure_instrument(
            _In_reads_(cnt) rtx_sensor *sensors,
            _In_ const std::size_t cnt,
            _In_ const rtx_instrument_configuration& configuration);

        /// <summary>
        /// Create sensor objects for all Rohde &amp; Schwarz RTA/RTB
        /// instruments that can be enumerated via VISA.
        /// </summary>
        /// <param name="dst ">An array receiving the sensors. If this is
        /// <c>nullptr</c>, nothing is returned. This buffer must be able to
        /// hold at least <paramref name="cnt" /> elements.</param>
        /// <param name="cnt">The number of sensors that can be stored in
        /// <paramref name="dst" />.</param>
        /// <param name="timeout">The timeout in milliseconds for establishing a
        /// connection to each instrument that was found. This parameter defaults
        /// to <see cref="visa_instrument::default_timeout" />.</param>
        /// <returns>The number of RTA/RTB instruments found, regardless of how
        /// many have been returned to <paramref name="dst" />.</returns>
        static std::size_t for_all(
            _When_(dst != nullptr, _Out_writes_opt_(cnt)) rtx_sensor *dst,
            _In_ std::size_t cnt,
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
            _In_ const oscilloscope_channel& voltage_channel,
            _In_ const oscilloscope_channel& current_channel,
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
        /// Initialises a new instance.
        /// </summary>
        rtx_sensor(void) = default;

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="definition">The definition of the sensor, which must
        /// contain the path of the instrument and the configuration of the
        /// voltage and the current channel.</param>
        /// <param name="timeout">The timeout for connecting to the instrument,
        /// in milliseconds, which is also set as the initial VISA timeout. Make
        /// sure to choose a sufficiently large number to wait for the channels
        /// being configured. This parameter defaults to
        /// <see cref="visa_instrument::default_timeout" />.</param>
        /// <exception cref="std::invalid_argument">If <paramref name="path" />
        /// is <c>nullptr</c>.</exception>
        /// <exception cref="std::bad_alloc">If the memory for the sensor state
        /// could not be allocated.</exception>
        /// <exception cref="std::system_error">If the VISA library could not be
        /// loaded.</exception>
        /// <exception cref="visa_exception">If the sensor could not be
        /// initialised.</exception>
        explicit rtx_sensor(_In_ const rtx_sensor_definition& definition,
            _In_ const visa_instrument::timeout_type timeout
            = visa_instrument::default_timeout);

        /// <summary>
        /// Move <paramref name="rhs" /> into a new instance.
        /// </summary>
        /// <param name="rhs">The object to be moved.</param>
        rtx_sensor(rtx_sensor&& rhs) noexcept = default;

        /// <summary>
        /// Finalise the instance.
        /// </summary>
        virtual ~rtx_sensor(void) = default;

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
        inline _Ret_maybenull_z_ const char *path(void) const noexcept {
            return this->_instrument.path();
        }

        using sensor::sample;

        /// <summary>
        /// Synchonises the date and time on the instrument with the system
        /// clock of the computer calling this API.
        /// </summary>
        /// <param name="utc">If <c>true</c>, UTC will be used, the local time
        /// otherwise. This parameter defaults to <c>false</c>.</param>
        /// <returns><c>*this</c>.</returns>
        /// <exception cref="std::runtime_error">If the method is called on an
        /// object that has been disposed by moving it.</exception>
        /// <exception cref="visa_exception">If the VISA command was not
        /// processed successfully.</exception>
        inline rtx_sensor& synchronise_clock(_In_ const bool utc = false) {
            this->_instrument.synchronise_clock(utc);
            return *this;
        }

        /// <summary>
        /// Move assignment.
        /// </summary>
        /// <param name="rhs">The right-hand side operand</param>
        /// <returns><c>*this</c></returns>
        rtx_sensor& operator =(rtx_sensor&& rhs) noexcept = default;

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
        measurement_data sample_sync(
            _In_ const timestamp_resolution resolution) const override;

    private:

        void initialise(_In_ const rtx_sensor_definition& definition,
            _In_ const visa_instrument::timeout_type timeout);

        std::uint32_t _channel_current;
        std::uint32_t _channel_voltage;
        rtx_instrument _instrument;
        blob _name;
    };

} /* namespace power_overwhelming */
} /* namespace visus */
