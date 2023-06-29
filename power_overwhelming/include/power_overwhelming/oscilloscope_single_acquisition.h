// <copyright file="oscilloscope_single_acquisition.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "power_overwhelming/power_overwhelming_api.h"


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Configures the single acquisition mode of the oscilloscope.
    /// </summary>
    class POWER_OVERWHELMING_API oscilloscope_single_acquisition final {

    public:

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        oscilloscope_single_acquisition(void);

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
        /// <param name="count">The number of waveforms to acquire.</param>
        /// <returns><c>*this</c>.</returns>
        inline oscilloscope_single_acquisition& count(
                _In_ const unsigned int count) noexcept {
            this->_count = count;
            return *this;
        }

        /// <summary>
        /// Instructs the instrument to compute the number of points per
        /// waveform by itself.
        /// </summary>
        /// <returns><c>*this</c>.</returns>
        inline oscilloscope_single_acquisition& enable_automatic_points(
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
        inline oscilloscope_single_acquisition& points(
                _In_ const unsigned int points) noexcept {
            this->_points = points;
            return *this;
        }


    private:

        unsigned int _count;
        unsigned int _points;
    };

} /* namespace power_overwhelming */
} /* namespace visus */
