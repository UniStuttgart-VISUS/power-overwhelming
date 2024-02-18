﻿// <copyright file="async_sampling.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>

#include "power_overwhelming/async_sampling.h"

#if defined(_WIN32)
#include <Windows.h>
#include <tchar.h>
#endif /* defined(_WIN32) */

#include "power_overwhelming/sensor.h"


/*
 * visus::power_overwhelming::async_sampling::default_interval
 */
const visus::power_overwhelming::async_sampling::microseconds_type
visus::power_overwhelming::async_sampling::default_interval;


/*
 * visus::power_overwhelming::async_sampling::async_sampling
 */
visus::power_overwhelming::async_sampling::async_sampling(void)
        : _callback({ nullptr }),
        _context(nullptr),
        _context_deleter(nullptr),
        _delivery_method(async_delivery_method::on_measurement_data),
        _interval(default_interval),
        _minimum_sleep(0),
        _timestamp_resolution(timestamp_resolution::milliseconds),
        _tinkerforge_sensor_source(
            power_overwhelming::tinkerforge_sensor_source::all) { }


/*
 * visus::power_overwhelming::async_sampling::~async_sampling
 */
visus::power_overwhelming::async_sampling::~async_sampling(void) noexcept {
    this->passes_context(nullptr);
}


/*
 * visus::power_overwhelming::async_sampling::deliver
 */
bool visus::power_overwhelming::async_sampling::deliver(
        _In_z_ const wchar_t *source,
        _In_reads_(cnt) const measurement_data *samples,
        _In_ const std::size_t cnt) const {
    auto context = const_cast<void *>(this->_context);
    auto retval = (this->_callback.on_measurement != nullptr);

    switch (this->_delivery_method) {
        case async_delivery_method::on_measurement:
            if (retval) {
                for (std::size_t i = 0; i < cnt; ++i) {
                    this->_callback.on_measurement(
                        measurement(source, samples[i]), context);
                }
            }
            break;

        case async_delivery_method::on_measurement_data:
            if (retval) {
                this->_callback.on_measurement_data(source, samples, cnt,
                    context);
            }
            break;

        default:
            retval = false;
    }

    return retval;
}


/*
 * visus::power_overwhelming::async_sampling::delivers_measurements_to
 */
visus::power_overwhelming::async_sampling&
visus::power_overwhelming::async_sampling::delivers_measurements_to(
        _In_opt_ const on_measurement_callback callback) noexcept {
#if defined(_WIN32)
    ::OutputDebugString(_T("PWROWG PERFORMANCE WARNING: Asynchronous sampling ")
        _T("of measurement is only provided for backwards compatibility. Use ")
        _T("measurement_data to reduce the amount of heap allocations for ")
        _T("samples being delivered.\r\n"));
#endif /* defined(_WIN32) */
    this->_callback.on_measurement = callback;
    this->_delivery_method = async_delivery_method::on_measurement;
    return *this;
}


/*
 * visus::power_overwhelming::async_sampling::delivers_measurement_data_to
 */
visus::power_overwhelming::async_sampling&
visus::power_overwhelming::async_sampling::delivers_measurement_data_to(
        _In_opt_ const on_measurement_data_callback callback) noexcept {
    this->_callback.on_measurement_data = callback;
    this->_delivery_method = async_delivery_method::on_measurement_data;
    return *this;
}


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
 * visus::power_overwhelming::async_sampling::is_disabled
 */
visus::power_overwhelming::async_sampling&
visus::power_overwhelming::async_sampling::is_disabled(void) noexcept {
    this->_callback.on_measurement = nullptr;
    return *this;
}


/*
 * visus::power_overwhelming::async_sampling::passes_context
 */
visus::power_overwhelming::async_sampling&
visus::power_overwhelming::async_sampling::passes_context(
        _In_opt_ void *context) noexcept {
    if ((this->_context_deleter != nullptr) && (this->_context != nullptr)) {
        // If there is an existing context owned by the object, free it first.
        this->_context_deleter(this->_context);
    }

    // Register a caller-owned context.
    this->_context = context;

    // Unregister the deleter to prevent deletion of non-owned context.
    this->_context_deleter = nullptr;

    return *this;
}


/*
 * visus::power_overwhelming::async_sampling::samples_every
 */
visus::power_overwhelming::async_sampling&
visus::power_overwhelming::async_sampling::samples_every(
        _In_ const microseconds_type interval) noexcept {
    this->_interval = interval;
    return *this;
}


/*
 * visus::power_overwhelming::async_sampling::stores_and_passes_context
 */
visus::power_overwhelming::async_sampling&
visus::power_overwhelming::async_sampling::stores_and_passes_context(
        _In_ void *context,
        _In_ void(CALLBACK *context_deleter)(void *)) {
    this->passes_context(context);
    this->_context_deleter = context_deleter;
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
        this->_callback = rhs._callback;
        rhs._callback.on_measurement = nullptr;
        this->passes_context(rhs._context);  // Make sure deleter is called.
        rhs._context = nullptr;
        this->_context_deleter = rhs._context_deleter;
        rhs._context_deleter = nullptr;
        this->_delivery_method = rhs._delivery_method;
        this->_interval = rhs._interval;
        rhs._interval = default_interval;
        this->_timestamp_resolution = rhs._timestamp_resolution;
        rhs._timestamp_resolution = timestamp_resolution::milliseconds;
        this->_tinkerforge_sensor_source = rhs._tinkerforge_sensor_source;
        rhs._tinkerforge_sensor_source
            = power_overwhelming::tinkerforge_sensor_source::all;
    }

    return *this;
}
