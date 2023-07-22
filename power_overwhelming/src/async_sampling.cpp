// <copyright file="async_sampling.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

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
        : _context(nullptr),
        _context_deleter(nullptr),
        _interval(default_interval),
        _on_measurement(nullptr),
        _on_measurement_data(nullptr),
        _timestamp_resolution(timestamp_resolution::milliseconds),
        _tinkerforge_sensor_source(
            power_overwhelming::tinkerforge_sensor_source::all),
        _triggered(false) { }


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
        _In_ const sensor& source,
        _In_ const measurement_data& sample) const {
    auto context = const_cast<void *>(this->_context);
    auto retval = false;

    if (this->_on_measurement_data != nullptr) {
        this->_on_measurement_data(source, sample, context);
        retval = true;

    } else if (this->_on_measurement != nullptr) {
        auto s = source.name();
        if (s != nullptr) {
            this->_on_measurement(measurement(s, sample), context);
        }
        retval = true;
    }

    return retval;
}


/*
 * visus::power_overwhelming::async_sampling::delivers_measurements_to
 */
visus::power_overwhelming::async_sampling&
visus::power_overwhelming::async_sampling::delivers_measurements_to(
        _In_ const on_measurement_callback callback) noexcept {
#if defined(_WIN32)
    ::OutputDebugString(_T("PWROWG PERFORMANCE WARNING: Asynchronous sampling ")
        _T("of measurement is only provided for backwards compatibility. Use ")
        _T("measurement_data to reduce the amount of heap allocations for ")
        _T("samples being delivered.\r\n"));
#endif /* defined(_WIN32) */
    this->_on_measurement = callback;
    this->_on_measurement_data = nullptr;
    return *this;
}


/*
 * visus::power_overwhelming::async_sampling::delivers_measurement_data_to
 */
visus::power_overwhelming::async_sampling&
visus::power_overwhelming::async_sampling::delivers_measurement_data_to(
        _In_ const on_measurement_data_callback callback) noexcept {
    this->_on_measurement_data = callback;
    this->_on_measurement = nullptr;
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
    this->_on_measurement = nullptr;
    this->_on_measurement_data = nullptr;
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
        this->passes_context(rhs._context);  // Make sure deleter is called.
        rhs._context = nullptr;
        this->_context_deleter = rhs._context_deleter;
        rhs._context_deleter = nullptr;
        this->_interval = rhs._interval;
        rhs._interval = default_interval;
        this->_on_measurement = rhs._on_measurement;
        rhs._on_measurement = nullptr;
        this->_on_measurement_data = rhs._on_measurement_data;
        rhs._on_measurement_data = nullptr;
        this->_timestamp_resolution = rhs._timestamp_resolution;
        rhs._timestamp_resolution = timestamp_resolution::milliseconds;
        this->_tinkerforge_sensor_source = rhs._tinkerforge_sensor_source;
        rhs._tinkerforge_sensor_source
            = power_overwhelming::tinkerforge_sensor_source::all;
        this->_triggered = rhs._triggered;
        rhs._triggered = false;
    }

    return *this;
}
