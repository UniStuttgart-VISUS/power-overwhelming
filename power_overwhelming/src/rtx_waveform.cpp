﻿// <copyright file="rtx_waveform.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// <author>Christoph Müller</author>

#include "visus/pwrowg/rtx_waveform.h"

#include <chrono>
#include <cmath>
#include <ctime>
#include <memory>

#include "string_functions.h"
#include "tokenise.h"


/*
 * PWROWG_NAMESPACE::rtx_waveform::rtx_waveform
 */
PWROWG_NAMESPACE::rtx_waveform::rtx_waveform(void)
    : _record_length(0),
    _segment_offset(0.0f),
    _segment_timestamp(0),
    _time_begin(0),
    _time_increment(0) { }


/*
 * PWROWG_NAMESPACE::rtx_waveform::rtx_waveform
 */
PWROWG_NAMESPACE::rtx_waveform::rtx_waveform(
        _In_z_ const char *xorg,
        _In_z_ const char *xinc,
        _In_z_ const char *segment_date,
        _In_z_ const char *segment_time,
        _In_z_ const char *segment_offset,
        _Inout_ blob&& samples)
    : _record_length(0),
        _segment_offset(0),
        _segment_timestamp(0),
        _time_begin(0),
        _time_increment(0) {
    if (xorg == nullptr) {
        throw std::invalid_argument("The X origin must not be nullptr.");
    }
    if (xinc == nullptr) {
        throw std::invalid_argument("The X increment must not be nullptr.");
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

    assert(samples.size() % sizeof(float) == 0);
    this->_record_length = samples.size() / sizeof(float);

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

        this->_segment_timestamp = PWROWG_NAMESPACE::timestamp::create(
            year, month, day,
            hours, minutes, seconds,
            millis, micros, static_cast<int>(nanos));
    }

    this->_segment_offset = std::atof(segment_offset);
    this->_time_begin = std::atof(xorg);
    this->_time_increment = std::atof(xinc);

    // Do not move samples unless everything else succeeded.
    this->_samples = std::move(samples);
}


/*
 * PWROWG_NAMESPACE::rtx_waveform::rtx_waveform
 */
PWROWG_NAMESPACE::rtx_waveform::rtx_waveform(
        _Inout_ rtx_waveform&& rhs) noexcept
    :_record_length(rhs._record_length),
        _samples(std::move(rhs._samples)),
        _segment_offset(rhs._segment_offset),
        _segment_timestamp(rhs._segment_timestamp),
        _time_begin(rhs._time_begin),
        _time_increment(rhs._time_increment) {
    rhs._record_length = 0;
    rhs._segment_offset = 0.0f;
    rhs._segment_timestamp = timestamp::zero;
    rhs._time_begin = 0.0f;
    rhs._time_increment = 0.0f;
}


/*
 * PWROWG_NAMESPACE::rtx_waveform::time_end
 */
float PWROWG_NAMESPACE::rtx_waveform::time_end(
        void) const noexcept {
    if (this->_samples.empty()) {
        return this->_time_begin;
    } else {
        return this->sample_time(this->_record_length - 1);
    }
}


/*
 * PWROWG_NAMESPACE::rtx_waveform::sample
 */
float PWROWG_NAMESPACE::rtx_waveform::sample(
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
 * PWROWG_NAMESPACE::rtx_waveform::sample_timestamp
 */
PWROWG_NAMESPACE::timestamp PWROWG_NAMESPACE::rtx_waveform::sample_timestamp(
        _In_ const std::size_t i) const noexcept {
    using namespace std::chrono;
    typedef duration<timestamp::value_type, std::ratio<1, timestamp::tick_rate>>
        target_duration;
    const duration<float> dt(this->sample_time(i));
    return this->segment_timestamp() + duration_cast<target_duration>(dt);
}


/*
 * PWROWG_NAMESPACE::rtx_waveform::operator =
 */
PWROWG_NAMESPACE::rtx_waveform&
PWROWG_NAMESPACE::rtx_waveform::operator =(
        _Inout_ rtx_waveform&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        this->_record_length = rhs._record_length;
        rhs._record_length = 0;
        this->_samples = std::move(rhs._samples);
        this->_segment_offset = rhs._segment_offset;
        rhs._segment_offset = 0.0f;
        this->_segment_timestamp = rhs._segment_timestamp;
        rhs._segment_timestamp = timestamp::zero;
        this->_time_begin = rhs._time_begin;
        rhs._time_begin = 0.0f;
        this->_time_increment = rhs._time_increment;
        rhs._time_increment = 0.0f;
    }

    return *this;
}
