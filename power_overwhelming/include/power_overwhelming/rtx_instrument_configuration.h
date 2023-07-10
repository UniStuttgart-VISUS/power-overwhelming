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
        /// Initialises a new instance.
        /// </summary>
        /// <param name="time_range">The time range the oscilloscope should
        /// acquire after it has been triggers.</param>
        /// <param name="timeout">The timeout of the instrument. If this value
        /// is zero, which is the default, the timeout will not be modified.
        /// </param>
        explicit rtx_instrument_configuration(
            _In_ const oscilloscope_quantity time_range,
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
        /// <param name="timeout">The timeout of the instrument. If this value
        /// is zero, which is the default, the timeout will not be modified.
        /// </param>
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
        /// <returns>A new configuration for instruments that are chained after
        /// the first one that is triggered as configured by the user.</returns>
        rtx_instrument_configuration as_slave(void) const;

        /// <summary>
        /// Applies the configuration on the given instrument.
        /// </summary>
        /// <remarks>
        /// <para>This method will block the calling thread until the instrument
        /// has applied all changes.</para>
        /// </remarks>
        /// <param name="instrument">The instrument to apply the configuration
        /// to.</param>
        void apply(_Inout_ rtx_instrument& instrument) const;

        /// <summary>
        /// Indicates whether this configuration is for a slave instrument that
        /// is being triggered by another instrument via the external trigger
        /// input.
        /// </summary>
        /// <returns><c>true</c> if the instrument is running as slave,
        /// <c>false</c> if it needs to be triggered by the user.</returns>
        inline const bool slave(void) const noexcept {
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

        static oscilloscope_edge_trigger external_trigger(void);

        oscilloscope_single_acquisition _acquisition;
        bool _slave;
        visa_instrument::timeout_type _timeout;
        oscilloscope_quantity _time_range;
        oscilloscope_edge_trigger _trigger;

    };

} /* namespace power_overwhelming */
} /* namespace visus */
