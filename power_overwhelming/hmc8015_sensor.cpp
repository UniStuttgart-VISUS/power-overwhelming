// <copyright file="hmc8015_sensor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "hmc8015_sensor.h"

#include <algorithm>
#include <cassert>
#include <limits>
#include <stdexcept>
#include <utility>

#include "convert_string.h"
#include "timestamp.h"
#include "tokenise.h"
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

    // Configure the display to show always the same stuff.
    // Default: URMS,IRMS,P,FPLL,URAN,IRAN,S,Q,LAMB,PHI
    this->_impl->printf("VIEW:NUM:SHOW 1\n");
    this->_impl->printf("VIEW:NUM:PAGE1:SIZE 10\n");
    this->_impl->printf("VIEW:NUM:PAGE1:CELL1:FUNC URMS\n");
    this->_impl->printf("VIEW:NUM:PAGE1:CELL2:FUNC IRMS\n");
    this->_impl->printf("VIEW:NUM:PAGE1:CELL3:FUNC URAN\n");
    this->_impl->printf("VIEW:NUM:PAGE1:CELL4:FUNC IRAN\n");
    //this->_impl->printf("VIEW:NUM:PAGE1:CELL3:FUNC UAVG\n");
    //this->_impl->printf("VIEW:NUM:PAGE1:CELL4:FUNC IAVG\n");
    this->_impl->printf("VIEW:NUM:PAGE1:CELL5:FUNC P\n");
    this->_impl->printf("VIEW:NUM:PAGE1:CELL6:FUNC S\n");
    this->_impl->printf("VIEW:NUM:PAGE1:CELL7:FUNC Q\n");
    this->_impl->printf("VIEW:NUM:PAGE1:CELL8:FUNC TIME\n");
    this->_impl->printf("VIEW:NUM:PAGE1:CELL9:FUNC WH\n");
    this->_impl->printf("VIEW:NUM:PAGE1:CELL10:FUNC AH\n");

    // Configure the stuff we want to measure.
    // Default: URMS,IRMS,P,FPLL,URAN,IRAN,S,Q,LAMB,PHI
    this->_impl->printf("CHAN1:MEAS:FUNC URMS, IRMS, P\n");

    // Clear any error that might have been caused by our setup. We do not want
    // to abort just because the display does not look as expected.
    this->_impl->clear_status();
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
 * visus::power_overwhelming::hmc8015_sensor::is_log
 */
bool visus::power_overwhelming::hmc8015_sensor::is_log(void) {
    this->check_not_disposed();
    auto response = this->_impl->query("LOG:STATE?\n");
    return (!response.empty() && (response[0] != '0'));
}


/*
 * visus::power_overwhelming::hmc8015_sensor::log
 */
void visus::power_overwhelming::hmc8015_sensor::log(const bool enable) {
    this->check_not_disposed();
    this->_impl->printf("LOG:STAT %s\n", enable ? "ON" : "OFF");
    this->_impl->throw_on_system_error();
}


/*
 * visus::power_overwhelming::hmc8015_sensor::log_behaviour
 */
void visus::power_overwhelming::hmc8015_sensor::log_behaviour(
        const float interval, const log_mode mode, const int value,
        const std::int32_t year, const std::int32_t month,
        const std::int32_t day, const std::int32_t hour,
        const std::int32_t minute, const std::int32_t second) {
    this->check_not_disposed();

    switch (mode) {
        case log_mode::count:
            this->_impl->printf("LOG:MODE COUN\n");
            if (value == std::numeric_limits<decltype(value)>::lowest()) {
                this->_impl->printf("LOG:COUN MIN\n");
            } else if (value == (std::numeric_limits<decltype(value)>::max)()) {
                this->_impl->printf("LOG:COUN MAX\n");
            } else {
                this->_impl->printf("LOG:COUN %d\n", value);
            }
            break;

        case log_mode::duration:
            this->_impl->printf("LOG:MODE DUR\n");
            if (value == std::numeric_limits<decltype(value)>::lowest()) {
                this->_impl->printf("LOG:DUR MIN\n");
            } else if (value == (std::numeric_limits<decltype(value)>::max)()) {
                this->_impl->printf("LOG:DUR MAX\n");
            } else {
                this->_impl->printf("LOG:DUR %d\n", value);
            }
            break;

        case log_mode::time_span:
            this->_impl->printf("LOG:MODE SPAN\n");
            this->_impl->printf("LOG:STIM %d, %d, %d, %d, %d, %d\n", year,
                month, day, hour, minute, second);
            if (value == std::numeric_limits<decltype(value)>::lowest()) {
                this->_impl->printf("LOG:DUR MIN\n");
            } else if (value == (std::numeric_limits<decltype(value)>::max)()) {
                this->_impl->printf("LOG:DUR MAX\n");
            } else {
                this->_impl->printf("LOG:DUR %d\n", value);
            }
            break;

        case log_mode::unlimited:
            this->_impl->printf("LOG:MODE UNL\n");
            break;

        default:
            throw std::invalid_argument("The specified log mode is not "
                "supported by the instrument.");
    }

    if (interval == std::numeric_limits<decltype(interval)>::lowest()) {
        this->_impl->printf("LOG:INT MIN\n");
    } else if (interval == (std::numeric_limits<decltype(interval)>::max)()) {
        this->_impl->printf("LOG:INT MAX\n");
    } else {
        this->_impl->printf("LOG:INT %f\n", interval);
    }

    this->_impl->throw_on_system_error();
}


/*
 * visus::power_overwhelming::hmc8015_sensor::log_file
 */
std::size_t visus::power_overwhelming::hmc8015_sensor::log_file(
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
 * visus::power_overwhelming::hmc8015_sensor::log_file
 */
void visus::power_overwhelming::hmc8015_sensor::log_file(const char *path,
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
 * visus::power_overwhelming::hmc8015_sensor::sample
 */
visus::power_overwhelming::measurement
visus::power_overwhelming::hmc8015_sensor::sample(
        const timestamp_resolution resolution) {
    this->check_not_disposed();
    auto response = this->_impl->query("CHAN1:MEAS:DATA?\n");
    auto timestamp = detail::create_timestamp(resolution);
    auto tokens = detail::tokenise(std::string(response.begin(),
        response.end()), ',', true);

    auto v = static_cast<measurement::value_type>(::atof(tokens[0].c_str()));
    auto c = static_cast<measurement::value_type>(::atof(tokens[1].c_str()));
    auto p = static_cast<measurement::value_type>(::atof(tokens[2].c_str()));

    return measurement(this->name(), timestamp, v, c, p);
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


/*
 * visus::power_overwhelming::hmc8015_sensor::set_range
 */
void visus::power_overwhelming::hmc8015_sensor::set_range(
        const std::int32_t channel, const char *quantity,
        const instrument_range range, const float value) {
    assert(quantity != nullptr);
    this->check_not_disposed();

    switch (range) {
        case instrument_range::automatically:
            this->_impl->printf("CHAN%d:ACQ:%s:RANG:AUTO ON\n", channel,
                quantity);
            break;

        case instrument_range::maximum:
            this->_impl->printf("CHAN%d:ACQ:%s:RANG MAX\n", channel,
                quantity);
            break;

        case instrument_range::minimum:
            this->_impl->printf("CHAN%d:ACQ:%s:RANG MIN\n", channel,
                quantity);
            break;

        case instrument_range::explicitly:
        default:
            this->_impl->printf("CHAN%d:ACQ:%s:RANG %f\n", channel,
                quantity, value);
            break;
    }

    this->_impl->throw_on_system_error();
}
