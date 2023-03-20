// <copyright file="visa_sensor.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/visa_sensor.h"

#if !defined(_WIN32)
#include <system_error>

#include <sys/time.h>
#endif /* !defined(_WIN32) */

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
        _In_z_ const char *path, _In_ const std::int32_t timeout)
        : _impl(new detail::visa_sensor_impl(path, timeout)) {
    this->initialise();
}


/*
 * visus::power_overwhelming::detail::visa_sensor::visa_sensor
 */
visus::power_overwhelming::detail::visa_sensor::visa_sensor(
        _In_z_ const wchar_t *path, _In_ const std::int32_t timeout)
        : _impl(new detail::visa_sensor_impl(path, timeout)) {
    this->initialise();
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
_Ret_maybenull_z_ const wchar_t *
visus::power_overwhelming::detail::visa_sensor::name(void) const noexcept {
    return (this->_impl != nullptr)
        ? this->_impl->sensor_name.c_str()
        : nullptr;
}


/*
 * visus::power_overwhelming::detail::visa_sensor::path
 */
_Ret_maybenull_z_ const char *
visus::power_overwhelming::detail::visa_sensor::path(void) const noexcept {
    return (this->_impl != nullptr)
        ? this->_impl->path.c_str()
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
        _In_ const bool utc) {
    this->check_not_disposed();

#if defined(_WIN32)
    SYSTEMTIME time;
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

#else /* defined(_WIN32) */
    struct timeval tv;
    struct timezone tz;

    if (::gettimeofday(&tv, &tz) != 0) {
        throw std::system_error(errno, std::system_category());
    }

    if (utc) {
        tv.tv_sec -= tz.tz_minuteswest * 60;
    }

    auto time = localtime(&tv.tv_sec);

    this->_impl->printf("SYST:TIME %d, %d, %d\n",
        time->tm_hour, time->tm_min, time->tm_sec);
    this->throw_on_system_error();
    this->_impl->printf("SYST:DATE %d, %d, %d\n",
        time->tm_year + 1900, time->tm_mon + 1, time->tm_mday);
    this->throw_on_system_error();

#endif /* defined(_WIN32) */
}


/*
 * visus::power_overwhelming::detail::visa_sensor::operator =
 */
visus::power_overwhelming::detail::visa_sensor&
visus::power_overwhelming::detail::visa_sensor::operator =(
        _In_ visa_sensor&& rhs) noexcept {
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
 * visus::power_overwhelming::detail::visa_sensor::initialise
 */
void visus::power_overwhelming::detail::visa_sensor::initialise(void) {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    // Query the instrument name for use a sensor name.
    this->_impl->sensor_name = power_overwhelming::convert_string<wchar_t>(
        this->_impl->identify());

    // Reset the device to default state, but do not throw.
    this->_impl->printf("*RST\n");

    // Clear any error that might have been caused by our setup. We do not want
    // to abort just because the display does not look as expected.
    this->_impl->clear_status();
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
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
