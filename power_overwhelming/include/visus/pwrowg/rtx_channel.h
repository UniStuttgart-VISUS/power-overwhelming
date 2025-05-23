﻿// <copyright file="rtx_channel.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_RTX_CHANNEL_H)
#define _PWROWG_RTX_CHANNEL_H
#pragma once

#include <cinttypes>

#include "visus/pwrowg/rtx_channel_bandwidth.h"
#include "visus/pwrowg/rtx_channel_coupling.h"
#include "visus/pwrowg/rtx_channel_polarity.h"
#include "visus/pwrowg/rtx_channel_unit.h"
#include "visus/pwrowg/rtx_decimation_mode.h"
#include "visus/pwrowg/rtx_label.h"
#include "visus/pwrowg/rtx_quantity.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// A container for the configuration of a single analog channel of an
/// oscilloscope.
/// </summary>
class POWER_OVERWHELMING_API rtx_channel final {

public:

    /// <summary>
    /// The type to number channels.
    /// </summary>
    typedef std::uint32_t channel_type;

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="channel">The one-based index of the channel. This
    /// parameter defaults to zero, which will create an unusable instance.
    /// </param>
    explicit rtx_channel(_In_ const channel_type channel = 0);

    /// <summary>
    /// Initialises a new intance.
    /// </summary>
    /// <param name="channel">The one-based index of the channel.</param>
    /// <param name="channel_template">An existing channel configuration
    /// that is being copied to <paramref name="channel" />.</param>
    rtx_channel(_In_ const channel_type channel,
        _In_ const rtx_channel& channel_template);

    /// <summary>
    /// Finalises the instance.
    /// </summary>
    ~rtx_channel(void) = default;

    /// <summary>
    /// Gets the attenuation of the probe.
    /// </summary>
    /// <returns>The attenuation and unit of the probe.</returns>
    inline const rtx_quantity& attenuation(void) const noexcept {
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
    rtx_channel& attenuation(
        _In_ const rtx_quantity& attenuation);

    /// <summary>
    /// Gets the bandwidth limit for the channel.
    /// </summary>
    /// <returns>The bandwidth limit of the channel.</returns>
    inline rtx_channel_bandwidth bandwidth(void) const noexcept {
        return this->_bandwidth;
    }

    /// <summary>
    /// Sets the bandwith limit for the channel.
    /// </summary>
    /// <param name="bandwidth">The bandwidth limit if any.</param>
    /// <returns><c>*this</c>.</returns>
    inline rtx_channel& bandwidth(
            _In_ const rtx_channel_bandwidth bandwidth) noexcept {
        this->_bandwidth = bandwidth;
        return *this;
    }

    /// <summary>
    /// Gets the one-based index of the channel.
    /// </summary>
    /// <returns>The index of the channel.</returns>
    inline channel_type channel(void) const noexcept {
        return this->_channel;
    }

    /// <summary>
    /// Gets the channel signal coupling and termination.
    /// </summary>
    /// <returns>The channel signal coupling and termination.</returns>
    inline rtx_channel_coupling coupling(void) const noexcept {
        return this->_coupling;
    }

    /// <summary>
    /// Sets the channel signal coupling and termination.
    /// </summary>
    /// <param name="coupling">The signal coupling for the channel.</param>
    /// <returns><c>*this</c>.</returns>
    inline rtx_channel& coupling(
            _In_ const rtx_channel_coupling coupling) noexcept {
        this->_coupling = coupling;
        return *this;
    }

    /// <summary>
    /// Gets the method to reduce the data stream of the ADC to waveform
    /// points.
    /// </summary>
    /// <returns>The desired decimation mode.</returns>
    inline rtx_decimation_mode decimation_mode(
            void) const noexcept {
        return this->_decimation_mode;
    }

    /// <summary>
    /// Sets the method to reduce the data stream of the ADC.
    /// </summary>
    /// <param name="decimation_mode">The desired decimation mode.</param>
    /// <returns><c>*this</c>.</returns>
    inline rtx_channel& decimation_mode(
            _In_ const rtx_decimation_mode decimation_mode) noexcept {
        this->_decimation_mode = decimation_mode;
        return *this;
    }

    /// <summary>
    /// Gets the channel label and its display state.
    /// </summary>
    /// <returns>The channel label.</returns>
    inline const rtx_label& label(void) const noexcept {
        return this->_label;
    }

    /// <summary>
    /// Sets the channel label.
    /// </summary>
    /// <param name="label">The label for the channel and its visibility
    /// state.</param>
    /// <returns><c>*this</c>.</returns>
    inline rtx_channel& label(
            _In_ const rtx_label& label) noexcept {
        this->_label = label;
        return *this;
    }

    /// <summary>
    /// Gets the offset voltage to be subtracted to correct and
    /// offset-affected signal.
    /// </summary>
    /// <returns>The offset voltage.</returns>
    inline const rtx_quantity& offset(void) const noexcept {
        return this->_offset;
    }

    /// <summary>
    /// Sets the offset voltage to be subtracted to correct and
    /// offset-affected signal.
    /// </summary>
    /// <param name="offset">The offset value.</param>
    /// <returns><c>*this</c>.</returns>
    inline rtx_channel& offset(
            _In_ const rtx_quantity& offset) noexcept {
        this->_offset = offset;
        return *this;
    }

    /// <summary>
    /// Indicates whether the signal amplitude is inverted or not.
    /// </summary>
    /// <returns>The state of the signal inversion.</returns>
    inline rtx_channel_polarity polarity(void) const noexcept {
        return this->_polarity;
    }

    /// <summary>
    /// Sets the inversion state of the channel.
    /// </summary>
    /// <param name="polarity">The signal inversion state.</param>
    /// <returns><c>*this</c>.</returns>
    inline rtx_channel& polarity(
        _In_ const rtx_channel_polarity polarity) noexcept {
        this->_polarity = polarity;
        return *this;
    }

    /// <summary>
    /// Gets the voltage range across all vertical divisions of the diagram.
    /// </summary>
    /// <returns>The voltage range to be displayed.</returns>
    inline const rtx_quantity& range(void) const noexcept {
        return this->_range;
    }

    /// <summary>
    /// Sets the voltage range across all vertical divisions of the diagram.
    /// </summary>
    /// <param name="offset">The voltage range.</param>
    /// <returns><c>*this</c>.</returns>
    inline rtx_channel& range(
        _In_ const rtx_quantity& range) noexcept {
        this->_range = range;
        return *this;
    }

    /// <summary>
    /// Changes the visibility of the channel label.
    /// </summary>
    /// <param name="visible"><c>true</c> for showing the label,
    /// <c>false</c> for hiding it.</param>
    /// <returns><c>*this</c>.</returns>
    inline rtx_channel& show_label(
            _In_ const bool visible) noexcept {
        this->_label.visible(visible);
        return *this;
    }

    /// <summary>
    /// Gets the delay for the selected channel.
    /// </summary>
    /// <returns>The delay for the selected channel.</returns>
    inline const rtx_quantity& skew(void) const noexcept {
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
    inline rtx_channel& skew(
            _In_ const rtx_quantity& skew) noexcept {
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
    inline rtx_channel& state(_In_ const bool enable) noexcept {
        this->_state = enable;
        return *this;
    }

    /// <summary>
    /// Answer whether the probe should be zero-adjusted after the channel
    /// was configured.
    /// </summary>
    /// <returns><c>true</c> if zero adjust is enabled, <c>false</c>
    /// otherwise.</returns>
    inline bool zero_adjust(void) const noexcept {
        return this->_zero_adjust;
    }

    /// <summary>
    /// Enables or disables whether the probe attached to the channel should
    /// be ajusted to <see cref="zero_adjust_offset" />.
    /// </summary>
    /// <remarks>
    /// Zero adjustment has no effect unless an Rohde &amp; Schwarz RT-ZCxxB
    /// probe is connected to the channel.
    /// </remarks>
    /// <param name="enabled"><c>true</c> for enabling the function,
    /// <c>false</c> for disabling it.</param>
    /// <returns><c>*this</c>.</returns>
    inline rtx_channel& zero_adjust(
            _In_ const bool enabled) noexcept {
        this->_zero_adjust = enabled;
        return *this;
    }

    /// <summary>
    /// Enables or disables whether the probe attached to the channel should
    /// be ajusted to <paramref name="offset" />.
    /// </summary>
    /// <remarks>
    /// Zero adjustment has no effect unless an Rohde &amp; Schwarz RT-ZCxxB
    /// probe is connected to the channel.
    /// </remarks>
    /// <param name="offset">The offset in percent, which will be clamped to
    /// [-100, 100].</param>
    /// <returns><c>*this</c>.</returns>
    inline rtx_channel& zero_adjust(_In_ const float offset) noexcept {
        this->zero_adjust(true);
        this->zero_adjust_offset(offset);
        return *this;
    }

    /// <summary>
    /// Answer the zero adjustment level as positive or negative percentage.
    /// </summary>
    /// <returns>The zero adjustment level to be applied.</returns>
    inline float zero_adjust_offset(void) const noexcept {
        return this->_zero_adjust_offset;
    }

    /// <summary>
    /// Set the zero adjustment offset.
    /// </summary>
    /// <remarks>
    /// Zero adjustment has no effect unless an Rohde &amp; Schwarz RT-ZCxxB
    /// probe is connected to the channel.
    /// </remarks>
    /// <param name="offset">The offset in percent, which will be clamped to
    /// [-100, 100].</param>
    /// <returns><c>*this</c>.</returns>
    rtx_channel& zero_adjust_offset(
        _In_ const float offset) noexcept;

    /// <summary>
    /// Gets the zero offset.
    /// </summary>
    /// <returns>The zero offset.</returns>
    inline const rtx_quantity& zero_offset(void) const noexcept {
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
    /// </remarks>
    /// <returns><c>*this</c>.</returns>
    inline rtx_channel& zero_offset(
            _In_ const rtx_quantity& zero_offset) noexcept {
        this->_zero_offset = zero_offset;
        return *this;
    }

private:

    rtx_quantity _attenuation;
    rtx_channel_bandwidth _bandwidth;
    channel_type _channel;
    rtx_channel_coupling _coupling;
    rtx_decimation_mode _decimation_mode;
    rtx_label _label;
    rtx_quantity _offset;
    rtx_channel_polarity _polarity;
    rtx_quantity _range;
    rtx_quantity _skew;
    bool _state;
    bool _zero_adjust;
    float _zero_adjust_offset;
    rtx_quantity _zero_offset;
};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_RTX_CHANNEL_H) */
