// <copyright file="oscilloscope_waveform.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/oscilloscope_waveform.h"

#include "string_functions.h"
#include "tokenise.h"


/*
 * visus::power_overwhelming::oscilloscope_waveform::oscilloscope_waveform
 */
visus::power_overwhelming::oscilloscope_waveform::oscilloscope_waveform(
        _In_z_ const char *header,
        _In_ const float segment_offset,
        _Inout_ blob&& samples)
        : _record_length(0), _segment_offset(segment_offset), _time_begin(0),
        _time_end(0) {
    if (header == nullptr) {
        throw std::invalid_argument("The data header must not be nullptr.");
    }

    const auto tokens = detail::tokenise(std::string(header), ",", true);
    if (tokens.size() < 4) {
        throw std::invalid_argument("The specified data header does not have "
            "the expected format.");
    }

    this->_time_begin = std::stof(tokens[0]);
    this->_time_end = std::stof(tokens[1]);
    this->_record_length = std::stoul(tokens[2]);

    if (this->_record_length > samples.size() / sizeof(float)) {
        throw std::invalid_argument("The number of samples in the data header "
            "does not match the sample data provided.");
    }

    // Do not move samples unless everything else succeeded.
    this->_samples = std::move(samples);
}


/*
 * visus::power_overwhelming::oscilloscope_waveform::sample
 */
float visus::power_overwhelming::oscilloscope_waveform::sample(
        _In_ const std::size_t i) const {
    if (this->_samples.empty()) {
        throw std::range_error("An empty waveform cannot be sampled.");
    }
    if (i >= this->_record_length) {
        throw std::range_error("The specified sample index is out of range.");
    }

    return this->_samples.as<float>()[i];
}


/*
 * visus::power_overwhelming::oscilloscope_waveform::sample_distance
 */
float visus::power_overwhelming::oscilloscope_waveform::sample_distance(
        void) const noexcept {
    if (this->_record_length == 0) {
        return 0.0f;

    } else {
        // This should be the same as "CHAN:DATA:XINC?", but without an
        // additional query.
        const auto count = static_cast<float>(this->_record_length);
        const auto dt = this->_time_end - this->_time_begin;
        return (dt / count);
    }
}
