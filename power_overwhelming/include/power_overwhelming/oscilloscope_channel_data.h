// <copyright file="oscilloscope_channel_data.h" company="Visualisierungsinstitut der Universität Stuttgart">
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
    class POWER_OVERWHELMING_API oscilloscope_channel_data final {

    public:

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="header"></param>
        /// <param name="samples"></param>
        oscilloscope_channel_data(_In_z_ const char *header,
            _Inout_ blob&& samples);

        /// <summary>
        /// The length of the waveform in number of samples.
        /// </summary>
        /// <returns></returns>
        inline std::size_t record_length(void) const noexcept {
            return this->_record_length;
        }

        /// <summary>
        /// The offset of the begin of the waveform in seconds.
        /// </summary>
        /// <param name=""></param>
        /// <returns></returns>
        inline float time_begin(void) const noexcept {
            return this->_time_begin;
        }

        /// <summary>
        /// The offset of the end of the waveform in seconds.
        /// </summary>
        /// <param name=""></param>
        /// <returns></returns>
        inline float time_end(void) const noexcept {
            return this->_time_end;
        }

        /// <summary>
        /// A pointer to the first sample of the waveform.
        /// </summary>
        /// <param name=""></param>
        /// <returns></returns>
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
