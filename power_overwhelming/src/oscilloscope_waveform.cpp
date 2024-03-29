// <copyright file="oscilloscope_waveform.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/oscilloscope_waveform.h"

#include <chrono>
#include <cmath>
#include <ctime>
#include <memory>

#include "filetime_period.h"
#include "string_functions.h"
#include "tokenise.h"


/*
 * visus::power_overwhelming::oscilloscope_waveform::oscilloscope_waveform
 */
visus::power_overwhelming::oscilloscope_waveform::oscilloscope_waveform(void)
    : _record_length(0),
    _segment_offset(0.0f),
    _segment_timestamp(0),
    _time_begin(0),
    _time_end(0) { }


/*
 * visus::power_overwhelming::oscilloscope_waveform::oscilloscope_waveform
 */
visus::power_overwhelming::oscilloscope_waveform::oscilloscope_waveform(
        _In_z_ const char *header,
        _In_z_ const char *segment_date,
        _In_z_ const char *segment_time,
        _In_z_ const char *segment_offset,
        _Inout_ blob&& samples)
    : _record_length(0),
        _segment_offset(0),
        _segment_timestamp(0),
        _time_begin(0),
        _time_end(0) {
    if (header == nullptr) {
        throw std::invalid_argument("The data header must not be nullptr.");
    }
    if (segment_date == nullptr) {
        throw std::invalid_argument("The segment date must not be nullptr.");
    }
    if (segment_time == nullptr) {
        throw std::invalid_argument("The segment time must not be nullptr.");
    }
    if (segment_offset == nullptr) {
        throw std::invalid_argument("The segment offset must not be nullptr.");
    }

    {
        const auto tokens = detail::tokenise(std::string(header), ",", true);
        if (tokens.size() < 4) {
            throw std::invalid_argument("The specified data header does not have "
                "the expected format.");
        }

        this->_time_begin = std::stof(tokens[0]);
        this->_time_end = std::stof(tokens[1]);
        this->_record_length = std::stoul(tokens[2]);
    }

    if (this->_record_length > samples.size() / sizeof(float)) {
        throw std::invalid_argument("The number of samples in the data header "
            "does not match the sample data provided.");
    }

    {
        const auto date_tokens = detail::tokenise(std::string(segment_date),
            ",", true);
        const auto time_tokens = detail::tokenise(std::string(segment_time),
            ",", true);

        if (date_tokens.size() < 3) {
            throw std::invalid_argument("The specified segment date does not "
                "have the expected format.");
        }
        if (time_tokens.size() < 3) {
            throw std::invalid_argument("The specified segment timestamp does "
                "not have the expected format.");
        }

        const auto year = std::stoi(date_tokens[0]);
        const auto month = std::stoi(date_tokens[1]);
        const auto day = std::stoi(date_tokens[2]);

        const auto hours = std::stoi(time_tokens[0]);
        const auto minutes = std::stoi(time_tokens[1]);
        auto remainder = std::stof(time_tokens[2]);

        float seconds;
        remainder = std::modf(remainder, &seconds) * 1000;
        float millis;
        remainder = std::modf(remainder, &millis) * 1000;
        float micros;
        const auto nanos = std::modf(remainder, &micros) * 1000;

        this->_segment_timestamp = power_overwhelming::timestamp::create(
            year, month, day,
            hours, minutes, seconds,
            millis, micros, static_cast<int>(nanos));
    }

    this->_segment_offset = std::atof(segment_offset);

    // Do not move samples unless everything else succeeded.
    this->_samples = std::move(samples);
}


/*
 * visus::power_overwhelming::oscilloscope_waveform::oscilloscope_waveform
 */
visus::power_overwhelming::oscilloscope_waveform::oscilloscope_waveform(
        _Inout_ oscilloscope_waveform&& rhs) noexcept
    :_record_length(rhs._record_length),
        _samples(std::move(rhs._samples)),
        _segment_offset(rhs._segment_offset),
        _segment_timestamp(rhs._segment_timestamp),
        _time_begin(rhs._time_begin),
        _time_end(rhs._time_end) {
    rhs._record_length = 0;
    rhs._segment_offset = 0.0f;
    rhs._segment_timestamp = 0;
    rhs._time_begin = 0.0f;
    rhs._time_end = 0.0f;
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

    auto retval = this->_samples.as<float>();
    _Analysis_assume_(retval != nullptr);

    return retval[i];
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


/*
 * visus::power_overwhelming::oscilloscope_waveform::sample_timestamp
 */
visus::power_overwhelming::measurement_data::timestamp_type
visus::power_overwhelming::oscilloscope_waveform::sample_timestamp(
        _In_ const std::size_t i) const noexcept {
    throw "TODO";
    //using namespace std::chrono;
    //typedef duration<timestamp_type, detail::filetime_period> target_duration;
    //const auto count = static_cast<float>(this->_record_length);
    //const duration<double> dt(this->_time_end - this->_time_begin);
    //return this->segment_timestamp()
    //    + duration_cast<target_duration>((dt * i) / count).count();
}


/*
 * visus::power_overwhelming::oscilloscope_waveform::operator =
 */
visus::power_overwhelming::oscilloscope_waveform&
visus::power_overwhelming::oscilloscope_waveform::operator =(
        _Inout_ oscilloscope_waveform&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        this->_record_length = rhs._record_length;
        rhs._record_length = 0;
        this->_samples = std::move(rhs._samples);
        this->_segment_offset = rhs._segment_offset;
        rhs._segment_offset = 0.0f;
        this->_segment_timestamp = rhs._segment_timestamp;
        rhs._segment_timestamp = 0;
        this->_time_begin = rhs._time_begin;
        rhs._time_begin = 0.0f;
        this->_time_end = rhs._time_end;
        rhs._time_end = 0;
    }

    return *this;
}
