// <copyright file="async_sampling.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/async_sampling.h"


/*
 * visus::power_overwhelming::async_sampling::async_sampling
 */
visus::power_overwhelming::async_sampling::async_sampling(void)
        : _context(nullptr),
        _interval(1000),
        _on_measurement(nullptr),
        _on_measurement_data(nullptr),
        _timestamp_resolution(timestamp_resolution::milliseconds),
        _tinkerforge_sensor_source(
            power_overwhelming::tinkerforge_sensor_source::all) { }


/*
 * visus::power_overwhelming::async_sampling::from_source
 */
visus::power_overwhelming::async_sampling&
visus::power_overwhelming::async_sampling::from_source(
        _In_ const power_overwhelming::tinkerforge_sensor_source source)
        noexcept {
    this->_tinkerforge_sensor_source = source;
    return *this;
}


/*
 * visus::power_overwhelming::async_sampling::invoke
 */
bool visus::power_overwhelming::async_sampling::invoke(
        _In_ const measurement& sample) const {
    auto retval = (this->_on_measurement != nullptr);

    if (retval) {
        this->_on_measurement(sample, this->_context);
    }

    return retval;
}


/*
 * visus::power_overwhelming::async_sampling::invoke
 */
bool visus::power_overwhelming::async_sampling::invoke(
        _In_ const sensor& source,
        _In_ const measurement_data& sample) const {
    auto retval = (this->_on_measurement != nullptr);

    if (retval) {
        this->_on_measurement_data(source, sample, this->_context);
    }

    return retval;
}


/*
 * visus::power_overwhelming::async_sampling::is_disabled
 */
visus::power_overwhelming::async_sampling&
visus::power_overwhelming::async_sampling::is_disabled(void) noexcept {
    this->_on_measurement = nullptr;
    this->_on_measurement_data = nullptr;
    return *this;
}


/*
 * visus::power_overwhelming::async_sampling::passing_context
 */
visus::power_overwhelming::async_sampling&
visus::power_overwhelming::async_sampling::passing_context(
        _In_opt_ void *context) noexcept {
    this->_context = context;
    return *this;
}


/*
 * visus::power_overwhelming::async_sampling::produces_measurement
 */
visus::power_overwhelming::async_sampling&
visus::power_overwhelming::async_sampling::produces_measurement(
        _In_ const on_measurement_callback callback) noexcept {
    this->_on_measurement = callback;
    this->_on_measurement_data = nullptr;
    return *this;
}


/*
 * visus::power_overwhelming::async_sampling::produces_measurement_data
 */
visus::power_overwhelming::async_sampling&
visus::power_overwhelming::async_sampling::produces_measurement_data(
        _In_ const on_measurement_data_callback callback) noexcept {
    this->_on_measurement_data = callback;
    this->_on_measurement = nullptr;
    return *this;
}


/*
 * visus::power_overwhelming::async_sampling::sample_every
 */
visus::power_overwhelming::async_sampling&
visus::power_overwhelming::async_sampling::sample_every(
        _In_ const microseconds_type interval) noexcept {
    this->_interval = interval;
    return *this;
}


/*
 * visus::power_overwhelming::async_sampling::using_resolution
 */
visus::power_overwhelming::async_sampling&
visus::power_overwhelming::async_sampling::using_resolution(
        _In_ const timestamp_resolution resolution) noexcept {
    this->_timestamp_resolution = resolution;
    return *this;
}


/*
 * visus::power_overwhelming::async_sampling::operator =
 */
visus::power_overwhelming::async_sampling&
visus::power_overwhelming::async_sampling::operator =(
        _Inout_ async_sampling&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        this->_context = rhs._context;
        rhs._context = nullptr;
        this->_interval = rhs._interval;
        rhs._interval = 1000;
        this->_on_measurement = rhs._on_measurement;
        rhs._on_measurement = nullptr;
        this->_on_measurement_data = rhs._on_measurement_data;
        rhs._on_measurement_data = nullptr;
        this->_timestamp_resolution = rhs._timestamp_resolution;
        rhs._timestamp_resolution = timestamp_resolution::milliseconds;
        this->_tinkerforge_sensor_source = rhs._tinkerforge_sensor_source;
        rhs._tinkerforge_sensor_source
            = power_overwhelming::tinkerforge_sensor_source::all;
    }

    return *this;
}
