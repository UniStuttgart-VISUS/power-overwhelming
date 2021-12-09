// <copyright file="hmc8015_sensor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "hmc8015_sensor.h"

#include <algorithm>
#include <stdexcept>
#include <utility>

#include <rsidr_core.h>

#include "convert_string.h"
#include "visa_library.h"
#include "visa_sensor_impl.h"


/*
 * visus::power_overwhelming::hmc8015_sensor::for_all
 */
std::size_t visus::power_overwhelming::hmc8015_sensor::for_all(
        hmc8015_sensor *out_sensors, const std::size_t cnt_sensors,
        const std::int32_t timeout) {
    // Build the query for all R&S HMC8015 instruments.
    std::string query("?*::");      // Any protocol
    query += vendor_id;             // Only R&S
    query += "::";
    query += product_id;            // Only HMC8015
    query += "::?*::INSTR";         // All serial numbers.

    // Search the instruments using VISA.
    auto devices = detail::visa_library::instance().find_resource(
        query.c_str());

    // Create a sensor for each instrument we found.
    for (std::size_t i = 0; (i < cnt_sensors) && (i < devices.size()); ++i) {
        out_sensors[i] = hmc8015_sensor(devices[i].c_str(), timeout);
    }

    return devices.size();
}


/*
 * visus::power_overwhelming::hmc8015_sensor::hmc8015_sensor
 */
visus::power_overwhelming::hmc8015_sensor::hmc8015_sensor(void)
    : _impl(nullptr) { }


/*
 * visus::power_overwhelming::hmc8015_sensor::hmc8015_sensor
 */
visus::power_overwhelming::hmc8015_sensor::hmc8015_sensor(
        const char *path, const std::int32_t timeout)
    : _impl(new detail::visa_sensor_impl(path, timeout)) {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    // Configure the device as in the R&S instrument driver.
    this->_impl->set_attribute(VI_ATTR_TMO_VALUE, 5000);
    this->_impl->set_buffer((VI_READ_BUF | VI_WRITE_BUF), 4096);
    this->_impl->set_attribute(VI_ATTR_WR_BUF_OPER_MODE, VI_FLUSH_ON_ACCESS);
    this->_impl->set_attribute(VI_ATTR_RD_BUF_OPER_MODE, VI_FLUSH_ON_ACCESS);

    // Query the instrument name for use a sensor name.
    this->_impl->sensor_name = detail::convert_string(this->_impl->identify());

    // Lock the system to indicate that it is controlled by the software. As
    // locking the system is not critical, do not check for system errors here.
    this->_impl->printf("SYST:REM\n");
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
}


/*
 * visus::power_overwhelming::hmc8015_sensor::~hmc8015_sensor
 */
visus::power_overwhelming::hmc8015_sensor::~hmc8015_sensor(void) {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    if (this->_impl != nullptr) {
        // Reset the system state to local operations, but make sure that we
        // do not throw in the destructor. Therefore, we use the library
        // directly instead of the wrappers checking the state of the calls.
        detail::visa_library::instance().viPrintf(this->_impl->scope,
            "SYST:LOC\n");
    }
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */

    delete this->_impl;
}


/*
 * visus::power_overwhelming::hmc8015_sensor::get_log_file
 */
std::size_t visus::power_overwhelming::hmc8015_sensor::get_log_file(
        char *path, const std::size_t cnt) {
    if (path != nullptr) {
        this->check_not_disposed();
        this->_impl->printf("LOG:FNAM?\n");

        // Read everything to prevent spurious responses in future calls.
        auto value = this->_impl->read();

        // Copy as must as the output buffer can hold.
        for (std::size_t i = 0; (i < cnt) && (i < value.size()); ++i) {
            path[i] = value[i];
        }

        // The last character in the reponse is always the line feed, which
        // we just override with the the string terminator.
        path[cnt - 1] = 0;

        return value.size();
    } else {
        return 0;
    }
}


/*
 * visus::power_overwhelming::hmc8015_sensor::get_logging
 */
bool visus::power_overwhelming::hmc8015_sensor::get_logging(void) {
    this->check_not_disposed();
    auto response = this->_impl->query("LOG:STATE?\n");
    return (!response.empty() && (response[0] != '0'));
}


/*
 * visus::power_overwhelming::hmc8015_sensor::name
 */
const wchar_t *visus::power_overwhelming::hmc8015_sensor::name(
        void) const noexcept {
    return (this->_impl != nullptr)
        ? this->_impl->sensor_name.c_str()
        : nullptr;
}


/*
 * visus::power_overwhelming::hmc8015_sensor::reset
 */
void visus::power_overwhelming::hmc8015_sensor::reset(void) {
    this->check_not_disposed();
    this->_impl->reset();
}


/*
 * visus::power_overwhelming::hmc8015_sensor::set_log_count
 */
void visus::power_overwhelming::hmc8015_sensor::set_log_count(
        const std::uint32_t count) {
    this->check_not_disposed();
    this->_impl->printf("LOG:MODE COUN\n");
    this->_impl->throw_on_system_error();
    this->_impl->printf("LOG:COUN %u\n", count);
    this->_impl->throw_on_system_error();
}


/*
 * visus::power_overwhelming::hmc8015_sensor::set_log_file
 */
void visus::power_overwhelming::hmc8015_sensor::set_log_file(const char *path,
        const bool overwrite, const bool use_usb) {
    if (path == nullptr) {
        throw std::invalid_argument("The path to the log file cannot be null.");
    }

    this->check_not_disposed();
    auto location = use_usb ? "EXT" : "INT";
    this->_impl->printf("LOG:DEL \"%s\", %s\n", path, location);
    this->_impl->clear_status();    // Clear error in case file did not exist.
    this->_impl->printf("LOG:FNAM \"%s\", %s\n", path, location);
    this->_impl->throw_on_system_error();
}


/*
 * visus::power_overwhelming::hmc8015_sensor::set_log_interval
 */
void visus::power_overwhelming::hmc8015_sensor::set_log_interval(
        const float seconds) {
    this->check_not_disposed();
    this->_impl->printf("LOG:INT %f\n", seconds);
    this->_impl->throw_on_system_error();
}


#if false
/*
 * visus::power_overwhelming::hmc8015_sensor::set_log_time
 */
void visus::power_overwhelming::hmc8015_sensor::set_log_time(
        const std::uint32_t time) {
    this->_impl->printf("LOG:MODE TIME\n");
    this->_impl->throw_on_system_error();
    this->_impl->printf("LOG:TIME %u\n", time);
    this->_impl->throw_on_system_error();
}
#endif


/*
 * visus::power_overwhelming::hmc8015_sensor::set_log_unlimited
 */
void visus::power_overwhelming::hmc8015_sensor::set_log_unlimited(void) {
    this->check_not_disposed();
    this->_impl->printf("LOG:MODE UNL\n");
    this->_impl->throw_on_system_error();
}


/*
 * visus::power_overwhelming::hmc8015_sensor::set_logging
 */
void visus::power_overwhelming::hmc8015_sensor::set_logging(const bool enable) {
    this->check_not_disposed();
    this->_impl->printf("LOG:STAT %s\n", enable ? "ON" : "OFF");
    this->_impl->throw_on_system_error();
}


/*
 * visus::power_overwhelming::hmc8015_sensor::synchronise_clock
 */
void visus::power_overwhelming::hmc8015_sensor::synchronise_clock(
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
    //this->_impl->throw_on_system_error();
    this->_impl->printf("SYST:DATE %d, %d, %d\n",
        time.wYear, time.wMonth, time.wDay);
    //this->_impl->throw_on_system_error();
}


/*
 * visus::power_overwhelming::hmc8015_sensor::operator =
 */
visus::power_overwhelming::hmc8015_sensor&
visus::power_overwhelming::hmc8015_sensor::operator =(
        hmc8015_sensor&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        this->_impl = rhs._impl;
        rhs._impl = nullptr;
    }

    return *this;
}


/*
 * visus::power_overwhelming::hmc8015_sensor::operator bool
 */
visus::power_overwhelming::hmc8015_sensor::operator bool(void) const noexcept {
    return (this->_impl != nullptr);
}


/*
 * visus::power_overwhelming::hmc8015_sensor::check_not_disposed
 */
void visus::power_overwhelming::hmc8015_sensor::check_not_disposed(void) {
    if (!*this) {
        throw std::runtime_error("The requested operation cannot be performed "
            "on a disposed instance of hmc8015_sensor.");
    }
}
