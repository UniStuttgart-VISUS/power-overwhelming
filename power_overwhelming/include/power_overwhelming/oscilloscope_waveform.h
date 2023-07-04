// <copyright file="oscilloscope_waveform.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "power_overwhelming/blob.h"


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Defines a container for data obtained from an oscilloscope channel.
    /// </summary>
    class POWER_OVERWHELMING_API oscilloscope_waveform final {

    public:

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="header">The header string for the waveform data.
        /// Header data are a CSV string of the time points of the begin and
        /// the end of the waveform, the number of samples in the waveform and
        /// the number of values per sample.
        /// </param>
        /// <param name="samples">A blob holding the <c>float</c> samples of
        /// the waveform.</param>
        /// <exception cref="std::invalid_argument">If
        /// <paramref name="header" /> is null or does not have the expected
        /// format, or if the number of samples specified in the header does
        /// not match the size of <paramref name="samples" />.
        oscilloscope_waveform(_In_z_ const char *header,
            _Inout_ blob&& samples);

        /// <summary>
        /// A pointer to the first sample of the waveform.
        /// </summary>
        /// <returns>A pointer to the first sample.</returns>
        inline const float *begin(void) const noexcept {
            return this->samples();
        }

        /// <summary>
        /// A pointer past the last sample of the waveform.
        /// </summary>
        /// <returns>A pointer to invalid memory past the last sample.
        /// </returns>
        inline const float *end(void) const noexcept {
            return this->samples() + this->_record_length;
        }

        /// <summary>
        /// The length of the waveform in number of samples.
        /// </summary>
        /// <returns>The number of samples in the waveform.</returns>
        inline std::size_t record_length(void) const noexcept {
            return this->_record_length;
        }

        /// <summary>
        /// The offset of the begin of the waveform in seconds.
        /// </summary>
        /// <returns>The time offset of the first sample from the configured
        /// origin of the time axis, in seconds.</returns>
        inline float time_begin(void) const noexcept {
            return this->_time_begin;
        }

        /// <summary>
        /// The offset of the end of the waveform in seconds.
        /// </summary>
        /// <returns>The end of the time axis in seconds.</returns>
        inline float time_end(void) const noexcept {
            return this->_time_end;
        }

        /// <summary>
        /// A pointer to the first sample of the waveform.
        /// </summary>
        /// <returns>A pointer to the first sample.</returns>
        inline const float *samples(void) const noexcept {
            return this->_samples.as<float>();
        }

    private:

        std::size_t _record_length;
        blob _samples;
        float _time_begin;
        float _time_end;
    };

} /* namespace power_overwhelming */
} /* namespace visus */
