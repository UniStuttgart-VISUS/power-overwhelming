// <copyright file="rtx_instrument_configuration.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "power_overwhelming/oscilloscope_quantity.h"
#include "power_overwhelming/oscilloscope_single_acquisition.h"
#include "power_overwhelming/oscilloscope_edge_trigger.h"
#include "power_overwhelming/rtx_instrument.h"


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// This class stores the shared part of the configuration of an
    /// <see cref="rtx_sensor" />, which cannot be configured individually if
    /// multiple sensors are created on the same <see cref="rtx_instrument" />.
    /// </summary>
    /// <remarks>
    /// <para>When using an oscilloscope with four channels or more, it is
    /// possible to create an <see cref="rtx_sensor" /> for each pair of
    /// channels (one for voltage and one for current), thus having more than
    /// one sensor operating on the same <see cref="rtx_instrument" />. In this
    /// situation, not all of the parameters of the instrument can be configured
    /// individually. For instance, the length of the waveform being recorded
    /// on a trigger signal is the same for all channels. This configuration
    /// object groups all of these settings that will be shared between sensors
    /// on the same instrument.</para>
    /// <para>Settings grouped in this class need to be set only once for the
    /// set of sensors created from the same instruments. Likewise, it is
    /// strongly recommended to apply the same settings to all instruments when
    /// working with multiple oscilloscopes in order to produce consistent
    /// results.</para>
    /// </remarks>
    class POWER_OVERWHELMING_API rtx_instrument_configuration final {

    public:

        /// <summary>
        /// Applies the given <paramref name="configuration" /> to all
        /// given <paramref name="instruments" />.
        /// </summary>
        /// <param name="instruments">The array of instruments to apply the
        /// configuration to. It is safe to pass <c>nullptr</c>, in which case
        /// nothing will happen.</param>
        /// <param name="cnt">The number of elements in
        /// <paramref name="instruments" />.</param>
        /// <param name="configuration">The configuration to apply to. If
        /// <paramref name="master_slave" /> is set <c>true</c>, the first
        /// instrument will be considered the master device and all subsequent
        /// ones will get a slave configuration derived from
        /// <paramref name="configuration "/>. If the configuration is set to
        /// make the instrument beep once it was applied, every instrument past
        /// the first one will beep once more to indicate how many instruments
        /// have been configured at the end</param>
        /// <param name="master_slave">If <c>true</c>, apply the given
        /// configuration only to the first instrument and a slave configuration
        /// derived from it to all subsequent ones. If <c>false</c>, which is
        /// the default, apply the given configuration to all instruments.
        /// </param>
        /// <param name="level">The trigger level of the external trigger of the
        /// slave instruments. The external trigger usually uses 5V if passed on
        /// via the AUX output, so the default of 2.5 V is a safe bet.</param>
        /// <param name="slope">The slope on which to trigger, which is the
        /// rising one by default.</param>
        /// <exception cref="std::runtime_error">If the any of the given
        /// <paramref name="instruments" /> has been disposed by a move
        /// operation.</exception>
        /// <exception cref="visa_exception">If any of the API calls to the
        /// instrument failed.</exception>
        static void apply(_In_reads_(cnt) rtx_instrument *instruments,
            _In_ const std::size_t cnt,
            _In_ const rtx_instrument_configuration& configuration,
            _In_ const bool master_slave = false,
            _In_ const oscilloscope_quantity& level
            = oscilloscope_quantity(2.5f, "V"),
            _In_ const oscilloscope_trigger_slope slope
            = oscilloscope_trigger_slope::rising);

        /// <summary>
        /// Applies a master/slave configuration to the given insturments where
        /// the instrument with the specified device name receives the master
        /// configuration while all other instruments receive a slave
        /// configuration derived from that.
        /// </summary>
        /// <param name="instruments">The array of instruments to apply the
        /// configuration to. It is safe to pass <c>nullptr</c>, in which case
        /// nothing will happen.</param>
        /// <param name="cnt">The number of elements in
        /// <paramref name="instruments" />.</param>
        /// <param name="configuration">The configuration to apply to the master
        /// instrument. All other instruments will receive a slave configuration
        /// derived from this object.</param>
        /// <param name="master">The instrument name of the master instrument.
        /// </param>
        /// <param name="level">The trigger level of the external trigger of the
        /// slave instruments. The external trigger usually uses 5V if passed on
        /// via the AUX output, so the default of 2.5 V is a safe bet.</param>
        /// <param name="slope">The slope on which to trigger, which is the
        /// rising one by default.</param>
        /// <returns>The index of the master instrument in
        /// <paramref name="instruments" />. If this value is equal to or larger
        /// than <paramref name="cnt" />, the specified name of the master
        /// instrument was not found among the instruments provided. The
        /// configuration is most likely not working in this case, because all
        /// instruments have been configured as slave instruments.</returns>
        /// <exception cref="std::invalid_argument">If
        /// <paramref name="master" /> is <c>nullptr</c>.</exception>
        /// <exception cref="std::runtime_error">If the any of the given
        /// <paramref name="instruments" /> has been disposed by a move
        /// operation.</exception>
        /// <exception cref="visa_exception">If any of the API calls to the
        /// instrument failed.</exception>
        static std::size_t apply(_In_reads_(cnt) rtx_instrument *instruments,
            _In_ const std::size_t cnt,
            _In_ const rtx_instrument_configuration& configuration,
            _In_z_ const wchar_t *master,
            _In_ const oscilloscope_quantity& level
            = oscilloscope_quantity(2.5f, "V"),
            _In_ const oscilloscope_trigger_slope slope
            = oscilloscope_trigger_slope::rising);

        /// <summary>
        /// Applies a master/slave configuration to the given insturments where
        /// the instrument with the specified device name receives the master
        /// configuration while all other instruments receive a slave
        /// configuration derived from that.
        /// </summary>
        /// <param name="instruments">The array of instruments to apply the
        /// configuration to. It is safe to pass <c>nullptr</c>, in which case
        /// nothing will happen.</param>
        /// <param name="cnt">The number of elements in
        /// <paramref name="instruments" />.</param>
        /// <param name="configuration">The configuration to apply to the master
        /// instrument. All other instruments will receive a slave configuration
        /// derived from this object.</param>
        /// <param name="master">The instrument name of the master instrument.
        /// </param>
        /// <param name="level">The trigger level of the external trigger of the
        /// slave instruments. The external trigger usually uses 5V if passed on
        /// via the AUX output, so the default of 2.5 V is a safe bet.</param>
        /// <param name="slope">The slope on which to trigger, which is the
        /// rising one by default.</param>
        /// <returns>The index of the master instrument in
        /// <paramref name="instruments" />. If this value is equal to or larger
        /// than <paramref name="cnt" />, the specified name of the master
        /// instrument was not found among the instruments provided. The
        /// configuration is most likely not working in this case, because all
        /// instruments have been configured as slave instruments.</returns>
        /// <exception cref="std::invalid_argument">If
        /// <paramref name="master" /> is <c>nullptr</c>.</exception>
        /// <exception cref="std::runtime_error">If the any of the given
        /// <paramref name="instruments" /> has been disposed by a move
        /// operation.</exception>
        /// <exception cref="visa_exception">If any of the API calls to the
        /// instrument failed.</exception>
        static std::size_t apply(_In_reads_(cnt) rtx_instrument *instruments,
            _In_ const std::size_t cnt,
            _In_ const rtx_instrument_configuration& configuration,
            _In_z_ const char *master,
            _In_ const oscilloscope_quantity& level
            = oscilloscope_quantity(2.5f, "V"),
            _In_ const oscilloscope_trigger_slope slope
            = oscilloscope_trigger_slope::rising);

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <remarks>
        /// <para>The default configuration uses the defaults of the
        /// <see cref="oscilloscope_single_acquisition" /> and
        /// <see cref="oscilloscope_edge_trigger" /> with the following changes:
        /// On the acquisition, fast-segmentation is enabled and the number of
        /// points is computed automatically. The rationally for that is that we
        /// want the instrument to be as fast as possible in production mode.
        /// Furthermore, computing the number of samples automatically is most
        /// suitable for this construction, which is designed to require the
        /// least user input possible. The edge trigger is configured in
        /// <see cref="oscilloscope_trigger_mode::automatic" /> automatic, which
        /// ensures that the instrument forces a trigger if none occurs on the
        /// device. This might not be desirable if working with external
        /// triggers on the instrument, but it is the least error-prone way to
        /// configure the instrument. Therefore, it is again the most reasonable
        /// thing for this simplified constructor. If you have additional
        /// requirements, you must configure new instances using fully
        /// customised configuration objects.</para>
        /// </remarks>
        /// <param name="time_range">The time range the oscilloscope should
        /// acquire after it has been triggers.</param>
        /// <param name="samples">The number of samples to be acquired during
        /// <paramref name="time_range" />. If this is zero, which is the
        /// default, the instrument will be configured to determine the best
        /// number of samples on its own.</param>
        /// <param name="timeout">The timeout of the instrument (for connections
        /// and for I/O operations including <c>*OPC?</c> queries. If this value
        /// is zero, which is the default, the timeout will not be modified. Be
        /// aware that you must be able to wait for acqusitions to complete, so
        /// the timeout should be larger than the time range you intend to
        /// acquire.</param>
        explicit rtx_instrument_configuration(
            _In_ const oscilloscope_quantity time_range,
            _In_ const unsigned int samples = 0,
            _In_ visa_instrument::timeout_type timeout = 0);

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="time_range">The time range the oscilloscope should
        /// acquire after it has been triggers.</param>
        /// <param name="acquisition">The acquisition configuration to be
        /// applied to the instrument.</param>
        /// <param name="trigger">Configures how the instrument will be
        /// triggered.</param>
        /// <param name="timeout">The timeout of the instrument (for connections
        /// and for I/O operations including <c>*OPC?</c> queries. If this value
        /// is zero, which is the default, the timeout will not be modified. Be
        /// aware that you must be able to wait for acqusitions to complete, so
        /// the timeout should be larger than the time range you intend to
        /// acquire.</param>
        rtx_instrument_configuration(
            _In_ const oscilloscope_quantity time_range,
            _In_ const oscilloscope_single_acquisition& acquisition,
            _In_ const oscilloscope_edge_trigger& trigger,
            _In_ visa_instrument::timeout_type timeout = 0);

        /// <summary>
        /// Answers the way the instrument will acquire one or more samples.
        /// </summary>
        /// <returns>The acquisition configuration of the instrument.</returns>
        inline const oscilloscope_single_acquisition& acquisition(
                void) const noexcept {
            return this->_acquisition;
        }

        /// <summary>
        /// Creates a copy of the configuration, but configured such that the
        /// instrument is triggered by the external trigger.
        /// </summary>
        /// <param name="beep">Instructs the slave configuration to make the
        /// instrument beep <paramref name="beep" /> times once it was applied.
        /// </param>
        /// <param name="level">The trigger level of the external trigger of the
        /// slave instruments. The external trigger usually uses 5V if passed on
        /// via the AUX output, so the default of 2.5 V is a safe bet.</param>
        /// <param name="slope">The slope on which to trigger, which is the
        /// rising one by default.</param>
        /// <returns>A new configuration for instruments that are chained after
        /// the first one that is triggered as configured by the user.</returns>
        rtx_instrument_configuration as_slave(
            _In_ const std::size_t beep = 0,
            _In_ const oscilloscope_quantity& level
            = oscilloscope_quantity(2.5f, "V"),
            _In_ const oscilloscope_trigger_slope slope
            = oscilloscope_trigger_slope::rising) const;

        /// <summary>
        /// Applies the configuration on the given instrument.
        /// </summary>
        /// <remarks>
        /// <para>This method will block the calling thread until the instrument
        /// has applied all changes.</para>
        /// </remarks>
        /// <param name="instrument">The instrument to apply the configuration
        /// to.</param>
        /// <exception cref="std::runtime_error">If the given
        /// <paramref name="instrument" /> has been disposed by a move
        /// operation.</exception>
        /// <exception cref="visa_exception">If any of the API calls to the
        /// instrument failed.</exception>
        void apply(_Inout_ rtx_instrument& instrument) const;

        /// <summary>
        /// Answer how often the instrument should beep once
        /// <see cref="apply" /> completed.
        /// </summary>
        /// <returns>The number of beeps on apply.</returns>
        inline std::size_t beep_on_apply(void) const noexcept {
            return this->_beep_on_apply;
        }

        /// <summary>
        /// Configures object to make the instrument beep
        /// <paramref name="count" /> times once the <see cref="apply" /> method
        /// finishes.
        /// </summary>
        /// <param name="count">The number of beeps to emit. If zero, the
        /// instrument will not beep.</param>
        /// <returns><c>*this</c>.</returns>
        rtx_instrument_configuration& beep_on_apply(
            _In_ const std::size_t count) noexcept;

        /// <summary>
        /// Answer whether the instrument should be configured to beep if it
        /// encounters an error.
        /// </summary>
        /// <returns><c>true</c> if the beep should be enabled, <c>false</c>
        /// otherwise.</returns>
        inline bool beep_on_error(void) const noexcept {
            return this->_beep_on_error;
        }

        /// <summary>
        /// Configures the instrument to beep if it encounters an error.
        /// </summary>
        /// <param name="enable"><c>true</c> to enable the beep, <c>false</c>
        /// otherwise.</param>
        /// <returns><c>*this</c>.</returns>
        rtx_instrument_configuration& beep_on_error(
            _In_ const bool enable) noexcept;

        /// <summary>
        /// Answer whether the instrument should be configured to beep if a
        /// trigger occurs.
        /// </summary>
        /// <returns><c>true</c> if the beep should be enabled, <c>false</c>
        /// otherwise.</returns>
        inline bool beep_on_trigger(void) const noexcept {
            return this->_beep_on_trigger;
        }

        /// <summary>
        /// Configures the instrument to beep if a trigger occurs.
        /// </summary>
        /// <param name="enable"><c>true</c> to enable the beep, <c>false</c>
        /// otherwise.</param>
        /// <returns><c>*this</c>.</returns>
        rtx_instrument_configuration& beep_on_trigger(
            _In_ const bool enable) noexcept;

        /// <summary>
        /// Indicates whether this configuration is for a slave instrument that
        /// is being triggered by another instrument via the external trigger
        /// input.
        /// </summary>
        /// <returns><c>true</c> if the instrument is running as slave,
        /// <c>false</c> if it needs to be triggered by the user.</returns>
        inline bool slave(void) const noexcept {
            return this->_slave;
        }

        /// <summary>
        /// Answers the timeout of the instrument in milliseconds.
        /// </summary>
        /// <returns>The timeout of the instrument, or zero if the timeout
        /// should not be modified.</returns>
        inline visa_instrument::timeout_type timeout(void) const noexcept {
            return this->_timeout;
        }

        /// <summary>
        /// Answers the time range the instrument will cover when a new sample
        /// is being requested.
        /// </summary>
        /// <returns>The time range the instrument will acquire.</returns>
        inline const oscilloscope_quantity& time_range(void) const noexcept {
            return this->_time_range;
        }

        /// <summary>
        /// Answer the trigger configured on the instrument.
        /// </summary>
        /// <returns>The trigger to be configured on the instrument.</returns>
        inline const oscilloscope_edge_trigger& trigger(void) const noexcept {
            return this->_trigger;
        }

    private:

        oscilloscope_single_acquisition _acquisition;
        std::size_t _beep_on_apply;
        bool _beep_on_error;
        bool _beep_on_trigger;
        bool _slave;
        visa_instrument::timeout_type _timeout;
        oscilloscope_quantity _time_range;
        oscilloscope_edge_trigger _trigger;
    };

} /* namespace power_overwhelming */
} /* namespace visus */
