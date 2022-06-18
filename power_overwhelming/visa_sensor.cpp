// <copyright file="visa_sensor.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/visa_sensor.h"

#include "power_overwhelming/convert_string.h"

#include "visa_sensor_impl.h"


/*
 * visus::power_overwhelming::detail::visa_sensor::visa_sensor
 */
visus::power_overwhelming::detail::visa_sensor::visa_sensor(void)
    : _impl(nullptr) { }


/*
 * visus::power_overwhelming::detail::visa_sensor::visa_sensor
 */
visus::power_overwhelming::detail::visa_sensor::visa_sensor(
        const char *path, const std::int32_t timeout)
        : _impl(new detail::visa_sensor_impl(path, timeout)) {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    // Query the instrument name for use a sensor name.
    this->_impl->sensor_name = detail::convert_string(this->_impl->identify());

    // Reset the device to default state, but do not throw.
    this->_impl->printf("*RST\n");

    // Clear any error that might have been caused by our setup. We do not want
    // to abort just because the display does not look as expected.
    this->_impl->clear_status();
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
}


/*
 * visus::power_overwhelming::detail::visa_sensor::~visa_sensor
 */
visus::power_overwhelming::detail::visa_sensor::~visa_sensor(void) {
    delete this->_impl;
}


/*
 * visus::power_overwhelming::detail::visa_sensor::name
 */
const wchar_t *visus::power_overwhelming::detail::visa_sensor::name(
        void) const noexcept {
    return (this->_impl != nullptr)
        ? this->_impl->sensor_name.c_str()
        : nullptr;
}


/*
 * visus::power_overwhelming::detail::visa_sensor::reset
 */
void visus::power_overwhelming::detail::visa_sensor::reset(void) {
    auto impl = static_cast<detail::visa_sensor_impl&>(*this);
    impl.printf("*RST\n");
    this->throw_on_system_error();
}


/*
 * visus::power_overwhelming::detail::visa_sensor::synchronise_clock
 */
void visus::power_overwhelming::detail::visa_sensor::synchronise_clock(
    const bool utc) {
    SYSTEMTIME time;

    this->check_not_disposed();

    if (utc) {
        ::GetSystemTime(&time);
    } else {
        ::GetLocalTime(&time);
    }

    this->_impl->printf("SYST:TIME %d, %d, %d\n",
        time.wHour, time.wMinute, time.wSecond);
    this->throw_on_system_error();
    this->_impl->printf("SYST:DATE %d, %d, %d\n",
        time.wYear, time.wMonth, time.wDay);
    this->throw_on_system_error();
}


/*
 * visus::power_overwhelming::detail::visa_sensor::operator =
 */
visus::power_overwhelming::detail::visa_sensor&
visus::power_overwhelming::detail::visa_sensor::operator =(
        visa_sensor&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        this->_impl = rhs._impl;
        rhs._impl = nullptr;
    }

    return *this;
}


/*
 * visus::power_overwhelming::detail::visa_sensor::operator bool
 */
visus::power_overwhelming::detail::visa_sensor::operator bool(
        void) const noexcept {
    return (this->_impl != nullptr);
}


/*
 * visus::power_overwhelming::detail::visa_sensor::clear_status
 */
void visus::power_overwhelming::detail::visa_sensor::clear_status(void) {
    this->check_not_disposed();
    this->_impl->clear_status();
    this->throw_on_system_error();
}


/*
 * visus::power_overwhelming::detail::visa_sensor::throw_on_system_error
 */
void visus::power_overwhelming::detail::visa_sensor::throw_on_system_error(
        void) {
    if (this->_impl != nullptr) {
        std::string message;
        auto error = this->_impl->system_error(message);

        if (error != 0) {
            if (message.empty()) {
                message = std::to_string(error);
            }

            throw std::runtime_error(message);
        }
    }
}


/*
 * visus::power_overwhelming::detail::visa_sensor::operator visa_sensor_impl
 */
visus::power_overwhelming::detail::visa_sensor::operator
visus::power_overwhelming::detail::visa_sensor_impl& (void) const {
    this->check_not_disposed();
    return *this->_impl;
}
