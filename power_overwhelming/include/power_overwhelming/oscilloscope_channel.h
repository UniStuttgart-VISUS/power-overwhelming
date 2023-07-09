// <copyright file="oscilloscope_channel.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cinttypes>

#include "power_overwhelming/oscilloscope_channel_bandwidth.h"
#include "power_overwhelming/oscilloscope_channel_coupling.h"
#include "power_overwhelming/oscilloscope_channel_polarity.h"
#include "power_overwhelming/oscilloscope_channel_unit.h"
#include "power_overwhelming/oscilloscope_decimation_mode.h"
#include "power_overwhelming/oscilloscope_label.h"
#include "power_overwhelming/oscilloscope_quantity.h"


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// A container for the configuration of a single analog channel of an
    /// oscilloscope.
    /// </summary>
    class POWER_OVERWHELMING_API oscilloscope_channel final {

    public:

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="channel">The one-based index of the channel.</param>
        explicit oscilloscope_channel(_In_ const std::uint32_t channel);

        /// <summary>
        /// Finalises the instance.
        /// </summary>
        ~oscilloscope_channel(void) = default;

        /// <summary>
        /// Gets the attenuation of the probe.
        /// </summary>
        /// <returns>The attenuation and unit of the probe.</returns>
        inline const oscilloscope_quantity& attenuation(void) const noexcept {
            return this->_attenuation;
        }

        /// <summary>
        /// Sets the attenuation of the probe.
        /// </summary>
        /// <param name="attenuation">The attenuation and unit of the probe.
        /// Note that this parameter must have set a unit and does not work
        /// with the default unit unless the value is zero, in which case the
        /// instrument will ignore this setting and leave whatever the device
        /// has currently set (or what a probe that supports automatic
        /// configuration reports to the instrument).</param>
        /// <returns><c>*this</c>.</returns>
        /// <exception cref="std::invalid_argument">If the unit of the quantity
        /// is not set while the value is not zero.</exception>
        oscilloscope_channel& attenuation(
            _In_ const oscilloscope_quantity& attenuation);

        /// <summary>
        /// Gets the bandwidth limit for the channel.
        /// </summary>
        /// <returns>The bandwidth limit of the channel.</returns>
        inline oscilloscope_channel_bandwidth bandwidth(void) const noexcept {
            return this->_bandwidth;
        }

        /// <summary>
        /// Sets the bandwith limit for the channel.
        /// </summary>
        /// <param name="bandwidth">The bandwidth limit if any.</param>
        /// <returns><c>*this</c>.</returns>
        inline oscilloscope_channel& bandwidth(
                _In_ const oscilloscope_channel_bandwidth bandwidth) noexcept {
            this->_bandwidth = bandwidth;
            return *this;
        }

        /// <summary>
        /// Gets the one-based index of the channel.
        /// </summary>
        /// <returns>The index of the channel.</returns>
        inline std::uint32_t channel(void) const noexcept {
            return this->_channel;
        }

        /// <summary>
        /// Gets the channel signal coupling and termination.
        /// </summary>
        /// <returns>The channel signal coupling and termination.</returns>
        inline oscilloscope_channel_coupling coupling(void) const noexcept {
            return this->_coupling;
        }

        /// <summary>
        /// Sets the channel signal coupling and termination.
        /// </summary>
        /// <param name="coupling">The signal coupling for the channel.</param>
        /// <returns><c>*this</c>.</returns>
        inline oscilloscope_channel& coupling(
                _In_ const oscilloscope_channel_coupling coupling) noexcept {
            this->_coupling = coupling;
            return *this;
        }

        /// <summary>
        /// Gets the method to reduce the data stream of the ADC to waveform
        /// points.
        /// </summary>
        /// <returns>The desired decimation mode.</returns>
        inline oscilloscope_decimation_mode decimation_mode(
                void) const noexcept {
            return this->_decimation_mode;
        }

        /// <summary>
        /// Sets the method to reduce the data stream of the ADC.
        /// </summary>
        /// <param name="decimation_mode">The desired decimation mode.</param>
        /// <returns><c>*this</c>.</returns>
        inline oscilloscope_channel& count(
                _In_ const oscilloscope_decimation_mode decimation_mode)
                noexcept {
            this->_decimation_mode = decimation_mode;
            return *this;
        }

        /// <summary>
        /// Gets the channel label and its display state.
        /// </summary>
        /// <returns>The channel label.</returns>
        inline const oscilloscope_label& label(void) const noexcept {
            return this->_label;
        }

        /// <summary>
        /// Sets the channel label.
        /// </summary>
        /// <param name="label">The label for the channel and its visibility
        /// state.</param>
        /// <returns><c>*this</c>.</returns>
        inline oscilloscope_channel& label(
                _In_ const oscilloscope_label& label) noexcept {
            this->_label = label;
            return *this;
        }

        /// <summary>
        /// Gets the offset voltage to be subtracted to correct and
        /// offset-affected signal.
        /// </summary>
        /// <returns>The offset voltage.</returns>
        inline const oscilloscope_quantity& offset(void) const noexcept {
            return this->_offset;
        }

        /// <summary>
        /// Sets the offset voltage to be subtracted to correct and
        /// offset-affected signal.
        /// </summary>
        /// <param name="offset">The offset value.</param>
        /// <returns><c>*this</c>.</returns>
        inline oscilloscope_channel& offset(
                _In_ const oscilloscope_quantity& offset) noexcept {
            this->_offset = offset;
            return *this;
        }

        /// <summary>
        /// Indicates whether the signal amplitude is inverted or not.
        /// </summary>
        /// <returns>The state of the signal inversion.</returns>
        inline oscilloscope_channel_polarity polarity(void) const noexcept {
            return this->_polarity;
        }

        /// <summary>
        /// Sets the inversion state of the channel.
        /// </summary>
        /// <param name="polarity">The signal inversion state.</param>
        /// <returns><c>*this</c>.</returns>
        inline oscilloscope_channel& polarity(
            _In_ const oscilloscope_channel_polarity polarity) noexcept {
            this->_polarity = polarity;
            return *this;
        }

        /// <summary>
        /// Gets the voltage range across all vertical divisions of the diagram.
        /// </summary>
        /// <returns>The voltage range to be displayed.</returns>
        inline const oscilloscope_quantity& range(void) const noexcept {
            return this->_range;
        }

        /// <summary>
        /// Sets the voltage range across all vertical divisions of the diagram.
        /// </summary>
        /// <param name="offset">The voltage range.</param>
        /// <returns><c>*this</c>.</returns>
        inline oscilloscope_channel& range(
            _In_ const oscilloscope_quantity& range) noexcept {
            this->_range = range;
            return *this;
        }

        /// <summary>
        /// Changes the visibility of the channel label.
        /// </summary>
        /// <param name="visible"><c>true</c> for showing the label,
        /// <c>false</c> for hiding it.</param>
        /// <returns><c>*this</c>.</returns>
        inline oscilloscope_channel& show_label(
                _In_ const bool visible) noexcept {
            this->_label.visible(visible);
            return *this;
        }

        /// <summary>
        /// Gets the delay for the selected channel.
        /// </summary>
        /// <returns>The delay for the selected channel.</returns>
        inline const oscilloscope_quantity& skew(void) const noexcept {
            return this->_skew;
        }

        /// <summary>
        /// Sets the delay for the selected channel.
        /// </summary>
        /// <remarks>
        /// Deskew compensates delay differences between channels caused by the
        /// different length of cables, probes, andother sources. Correct deskew
        /// values are important for accurate triggering.
        /// </remarks>
        /// <param name="offset">The delay for the selected channel.</param>
        /// <returns><c>*this</c>.</returns>
        inline oscilloscope_channel& skew(
                _In_ const oscilloscope_quantity& skew) noexcept {
            this->_skew = skew;
            return *this;
        }

        /// <summary>
        /// Indicates whether the channel is turned on or off.
        /// </summary>
        /// <returns><c>true</c> if the channel is turned on, <c>false</c>
        /// otherwise.</returns>
        inline bool state(void) const noexcept {
            return this->_state;
        }

        /// <summary>
        /// Enables or disables the channel.
        /// </summary>
        /// <param name="enable"><c>true</c> for enabling the channel,
        /// <c>false</c> for disabling it.</param>
        /// <returns><c>*this</c>.</returns>
        inline oscilloscope_channel& state(_In_ const bool enable) noexcept {
            this->_state = enable;
            return *this;
        }

        /// <summary>
        /// Gets the zero offset.
        /// </summary>
        /// <returns>The zero offset.</returns>
        inline const oscilloscope_quantity& zero_offset(void) const noexcept {
            return this->_zero_offset;
        }

        /// <summary>
        /// Sets the zero offset.
        /// </summary>
        /// <remarks>
        /// <para>Differences in the device under test (DUT) and oscilloscope
        /// ground levels may cause larger zero errors affecting the waveform.
        /// If the DUT is ground-referenced, the zero offset corrects the zero
        /// error andsets the probe to the zero level.</para>
        /// <para>You can assess the zero error by measuring the mean value of
        /// a signal that should return zero.</para>
        /// <param name="zero_offset">The zero offset.</param>
        /// <returns><c>*this</c>.</returns>
        inline oscilloscope_channel& zero_offset(
            _In_ const oscilloscope_quantity& zero_offset) noexcept {
            this->_zero_offset = zero_offset;
            return *this;
        }

    private:

        oscilloscope_quantity _attenuation;
        oscilloscope_channel_bandwidth _bandwidth;
        std::uint32_t _channel;
        oscilloscope_channel_coupling _coupling;
        oscilloscope_decimation_mode _decimation_mode;
        oscilloscope_label _label;
        oscilloscope_quantity _offset;
        oscilloscope_channel_polarity _polarity;
        oscilloscope_quantity _range;
        oscilloscope_quantity _skew;
        bool _state;
        oscilloscope_quantity _zero_offset;
    };

} /* namespace power_overwhelming */
} /* namespace visus */
