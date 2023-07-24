// <copyright file="oscilloscope_acquisition.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "power_overwhelming/oscilloscope_acquisition_state.h"
#include "power_overwhelming/power_overwhelming_api.h"


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Configures the acquisition mode of the oscilloscope.
    /// </summary>
    /// <remarks>
    /// <para>Not all properties might be relevant for all modes.</para>
    /// <para>For programmatic measurements, callers should typically configure
    /// a single acquisition (possibly with multiple segments) as free running
    /// acquisitions cannot be safely synchronised with the application logic.
    /// </para>
    /// </remarks>
    class POWER_OVERWHELMING_API oscilloscope_acquisition final {

    public:

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        oscilloscope_acquisition(void);

        /// <summary>
        /// Answer whether the number of points should be computed by the
        /// instrument.
        /// </summary>
        /// <returns><c>true</c> if the instrument should compute the record
        /// length, <c>false</c> otherwise.</returns>
        inline bool automatic_points(void) const noexcept {
            return (this->_points == 0);
        }

        /// <summary>
        /// Answer the number of waveforms to be acquired on trigger.
        /// </summary>
        /// <returns>The number of waveforms to be acquired.</returns>
        inline unsigned int count(void) const noexcept {
            return this->_count;
        }

        /// <summary>
        /// Sets the number of waveforms (segments) to be acquired on a single
        /// trigger.
        /// </summary>
        /// <para>This setting is only relevant for single acqusition mode.
        /// </para>
        /// <param name="count">The number of waveforms to acquire.</param>
        /// <returns><c>*this</c>.</returns>
        inline oscilloscope_acquisition& count(
                _In_ const unsigned int count) noexcept {
            this->_count = count;
            return *this;
        }

        /// <summary>
        /// Instructs the instrument to compute the number of points per
        /// waveform by itself.
        /// </summary>
        /// <returns><c>*this</c>.</returns>
        inline oscilloscope_acquisition& enable_automatic_points(
                void) noexcept {
            this->_points = 0;
            return *this;
        }

        /// <summary>
        /// Answer the number of points recorded per waveform.
        /// </summary>
        /// <remarks>
        /// <para>If this value is zero, the device should be configured to
        /// compute the appropriate record length on its own.</para>
        /// </remarks>
        /// <returns>The number of points in a waveform segment.</returns>
        inline unsigned int points(void) const noexcept {
            return this->_points;
        }

        /// <summary>
        /// Set the number of points per waveform.
        /// </summary>
        /// <param name="points">The number of waveforms to acquire. This is an
        /// enumerated value and if it is not matched excatly, the instrument
        /// will choose the closest one.</param>
        /// <returns><c>*this</c>.</returns>
        inline oscilloscope_acquisition& points(
                _In_ const unsigned int points) noexcept {
            this->_points = points;
            return *this;
        }

        /// <summary>
        /// Answer whether fast segmentation is enabled during the acquisition.
        /// </summary>
        /// <returns><c>true</c> if fast segmentation is enabled, <c>false</c>
        /// otherwise.</returns>
        inline bool segmented(void) const noexcept {
            return this->_segmented;
        }

        /// <summary>
        /// Enables or disables fast segmentation.
        /// </summary>
        /// <remarks>
        /// <para>If fast segmentation is enabled, the acquisitions are
        /// performed as fast as possible without processing and displaying the
        /// waveforms. Once the acquisition has been stopped, the data is
        /// processed and the latest waveform is displayed. Older waveforms are
        ///  stored in segments.</para>
        /// <para>This setting is primarily for single acqusition mode.</para>
        /// </remarks>
        /// <param name="segmented"><c>true</c> to enable fast segmentation,
        /// <c>false</c> to disable it.</param>
        /// <returns><c>*this</c>.</returns>
        inline oscilloscope_acquisition& segmented(
                _In_ const bool segmented) noexcept {
            this->_segmented = segmented;
            return *this;
        }

        /// <summary>
        /// Answer the current or requested state of the acquistion.
        /// </summary>
        /// <remarks>
        /// <para>This member only reflects the actual state of the instrument
        /// if the <see cref="oscilloscope_acquisition" /> was obtained from the
        /// instrument.</para>
        /// </remarks>
        /// <returns>The acquisition state.</returns>
        inline oscilloscope_acquisition_state state(void) const noexcept {
            return this->_state;
        }

        /// <summary>
        /// Sets the desired acquisition state.
        /// </summary>
        /// <remarks>
        /// The default acquisition state is
        /// <see cref="oscilloscope_acquisition_state::unknown" />, which leaves
        /// the state untouched when this object is used to configure an
        /// instrument.
        /// </remarks>
        /// <param name="state">The desired acquisition state. If this parameter
        /// is <see cref="oscilloscope_acquisition_state::unknown" />, the state
        /// will remain unchanged if the object is used to configure an
        /// instrument.</param>
        /// <returns><c>*this</c>.</returns>
        inline oscilloscope_acquisition& state(
                _In_ const oscilloscope_acquisition_state state) noexcept {
            this->_state = state;
            return *this;
        }

    private:

        unsigned int _count;
        unsigned int _points;
        bool _segmented;
        oscilloscope_acquisition_state _state;
    };

} /* namespace power_overwhelming */
} /* namespace visus */
