// <copyright file="msr_sensor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/msr_sensor.h"

#include "msr_sensor_impl.h"


/*
 * visus::power_overwhelming::msr_sensor::for_all
 */
std::size_t visus::power_overwhelming::msr_sensor::for_all(
        _Out_writes_opt_(cnt_sensors) msr_sensor *out_sensors,
        _In_ const std::size_t cnt_sensors) {
    throw "TODO";
}


/*
 * visus::power_overwhelming::msr_sensor::msr_sensor
 */
visus::power_overwhelming::msr_sensor::msr_sensor(void)
    : _impl(new detail::msr_sensor_impl()) { }


/*
 * visus::power_overwhelming::msr_sensor::~msr_sensor
 */
visus::power_overwhelming::msr_sensor::~msr_sensor(void) {
    delete this->_impl;
}


/*
 * visus::power_overwhelming::msr_sensor::name
 */
_Ret_maybenull_z_ const wchar_t *visus::power_overwhelming::msr_sensor::name(
        void) const noexcept {
    return (this->_impl != nullptr)
        ? this->_impl->sensor_name.c_str()
        : nullptr;
}


/*
 * visus::power_overwhelming::msr_sensor::sample
 */
visus::power_overwhelming::measurement
visus::power_overwhelming::msr_sensor::sample(
        _In_ const timestamp_resolution resolution) const {
    throw "TODO";
}


/*
 * visus::power_overwhelming::msr_sensor::operator =
 */
visus::power_overwhelming::msr_sensor&
visus::power_overwhelming::msr_sensor::operator =(_In_ msr_sensor&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        this->_impl = rhs._impl;
        rhs._impl = nullptr;
    }

    return *this;
}


/*
 * visus::power_overwhelming::msr_sensor::operator bool
 */
visus::power_overwhelming::msr_sensor::operator bool(void) const noexcept {
    return (this->_impl != nullptr);
}
