// <copyright file="adl_throttling_sensor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/adl_throttling_sensor.h"

#include <cassert>

#include "adl_sensor_impl.h"
#include "timestamp.h"


/*
 * visus::power_overwhelming::adl_throttling_sensor::adl_throttling_sensor
 */
visus::power_overwhelming::adl_throttling_sensor::adl_throttling_sensor(
        void) noexcept
    : _impl(nullptr) { }


/*
 * visus::power_overwhelming::adl_throttling_sensor::~adl_throttling_sensor
 */
visus::power_overwhelming::adl_throttling_sensor::~adl_throttling_sensor(void) {
    delete this->_impl;
}


/*
 * visus::power_overwhelming::adl_throttling_sensor::name
 */
_Ret_maybenull_z_ const wchar_t *
visus::power_overwhelming::adl_throttling_sensor::name(void) const noexcept {
    return (this->_impl != nullptr)
        ? this->_impl->sensor_name.c_str()
        : nullptr;
}


/*
 * visus::power_overwhelming::adl_throttling_sensor::sample
 */
visus::power_overwhelming::throttling_sample
visus::power_overwhelming::adl_throttling_sensor::sample(
        _In_ const timestamp_resolution resolution) const {
    this->check_not_disposed();
    assert(this->_impl != nullptr);
    assert(this->_impl->state.load() == 1);
    const auto data = static_cast<ADLPMLogData *>(
        this->_impl->start_output.pLoggingAddress);
    const auto timestamp = this->_impl->timestamp(resolution);
    unsigned int value = 0;

    if (detail::adl_sensor_impl::filter_sensor_readings(value, *data,
            ADL_PMLOG_THROTTLER_STATUS)) {
        const auto notification = static_cast<ADL_THROTTLE_NOTIFICATION>(value);

        //ADL_PMLOG_THROTTLE_POWER = 1 << 0,
        //ADL_PMLOG_THROTTLE_THERMAL = 1 << 1,
        //ADL_PMLOG_THROTTLE_CURRENT = 1 << 2,


    } else {
        return throttling_sample(timestamp, throttling_state::none);
    }

    for (auto i = 0; (i < ADL_PMLOG_MAX_SENSORS)
            && (data->ulValues[i][0] != ADL_SENSOR_MAXTYPES); ++i) {
        auto s = static_cast<ADL_PMLOG_SENSORS>(data->ulValues[i][0]);
    }

    return throttling_sample();
}


/*
 * visus::power_overwhelming::adl_throttling_sensor::sample
 */
void visus::power_overwhelming::adl_throttling_sensor::sample(
        _Inout_ async_sampling&& async_sampling) {
    this->check_not_disposed();
}


/*
 * visus::power_overwhelming::adl_throttling_sensor::operator =
 */
visus::power_overwhelming::adl_throttling_sensor&
visus::power_overwhelming::adl_throttling_sensor::operator =(
        _Inout_ adl_throttling_sensor&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        delete this->_impl;
        this->_impl = rhs._impl;
        rhs._impl = nullptr;
    }

    return *this;
}


/*
 * visus::power_overwhelming::adl_throttling_sensor::operator bool
 */
visus::power_overwhelming::adl_throttling_sensor::operator bool(
        void) const noexcept {
    return (this->_impl != nullptr);
}
