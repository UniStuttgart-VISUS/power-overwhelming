// <copyright file="hmc8015_sensor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/hmc8015_sensor.h"

#include <algorithm>
#include <cassert>
#include <limits>
#include <stdexcept>
#include <utility>

#include "power_overwhelming/convert_string.h"

#include "timestamp.h"
#include "tokenise.h"
#include "visa_library.h"
#include "visa_sensor_impl.h"


/*
 * visus::power_overwhelming::hmc8015_sensor::for_all
 */
std::size_t visus::power_overwhelming::hmc8015_sensor::for_all(
        _Out_writes_opt_(cnt_sensors) hmc8015_sensor *out_sensors,
        _In_ std::size_t cnt_sensors,
        _In_ const std::int32_t timeout) {
    // Build the query for all R&S HMC8015 instruments.
    std::string query("?*::");      // Any protocol
    query += rohde_und_schwarz;     // Only R&S
    query += "::";
    query += product_id;            // Only HMC8015
    query += "::?*::INSTR";         // All serial numbers.

    // Search the instruments using VISA.
    auto devices = detail::visa_library::instance().find_resource(
        query.c_str());

    // Guard against misuse.
    if (out_sensors == nullptr) {
        cnt_sensors = 0;
    }

    // Create a sensor for each instrument we found.
    for (std::size_t i = 0; (i < cnt_sensors) && (i < devices.size()); ++i) {
        out_sensors[i] = hmc8015_sensor(devices[i].c_str(), timeout);
    }

    return devices.size();
}


/*
 * visus::power_overwhelming::hmc8015_sensor::hmc8015_sensor
 */
visus::power_overwhelming::hmc8015_sensor::hmc8015_sensor(
        _In_z_ const char *path, _In_ const std::int32_t timeout)
        : detail::visa_sensor(path, timeout) {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    auto impl = static_cast<detail::visa_sensor_impl&>(*this);

    // Configure the device as in the R&S instrument driver.
    impl.set_attribute(VI_ATTR_TMO_VALUE, 5000);
    impl.set_buffer((VI_READ_BUF | VI_WRITE_BUF), 4096);
    impl.set_attribute(VI_ATTR_WR_BUF_OPER_MODE, VI_FLUSH_ON_ACCESS);
    impl.set_attribute(VI_ATTR_RD_BUF_OPER_MODE, VI_FLUSH_ON_ACCESS);

    // Lock the system to indicate that it is controlled by the software. As
    // locking the system is not critical, do not check for system errors here.
    impl.printf("SYST:REM\n");

    // Reset the device to default state.
    impl.printf("*RST\n");

    // Clear any error that might have been caused by our setup. We do not want
    // to abort just because the display does not look as expected.
    impl.clear_status();
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
}


/*
 * visus::power_overwhelming::hmc8015_sensor::~hmc8015_sensor
 */
visus::power_overwhelming::hmc8015_sensor::~hmc8015_sensor(void) {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    auto impl = static_cast<detail::visa_sensor_impl *>(*this);

    if (impl != nullptr) {
        // Reset the system state to local operations, but make sure that we
        // do not throw in the destructor. Therefore, we use the library
        // directly instead of the wrappers checking the state of the calls.
        detail::visa_library::instance().viPrintf(impl->scope,
            "SYST:LOC\n");
    }
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
}


/*
 * visus::power_overwhelming::hmc8015_sensor::display
 */
void visus::power_overwhelming::hmc8015_sensor::display(
        _In_opt_z_ const char *text) {
    auto impl = static_cast<detail::visa_sensor_impl &>(*this);

    if (text != nullptr) {
        impl.printf("DISP:TEXT:DATA \"%s\"\n", text);
    } else {
        impl.printf("DISP:TEXT:CLE\n");
    }

    this->throw_on_system_error();
}


/*
 * visus::power_overwhelming::hmc8015_sensor::display
 */
void visus::power_overwhelming::hmc8015_sensor::display(
        _In_opt_z_ const wchar_t *text) {
    if (text == nullptr) {
        this->display(static_cast<char *>(nullptr));
    } else {
        auto t = convert_string<char>(text);
        this->display(t.c_str());
    }
}


/*
 * visus::power_overwhelming::hmc8015_sensor::is_log
 */
bool visus::power_overwhelming::hmc8015_sensor::is_log(void) {
    auto impl = static_cast<detail::visa_sensor_impl &>(*this);
    auto response = impl.query("LOG:STATE?\n");
    return (!response.empty() && (response[0] != '0'));
}


/*
 * visus::power_overwhelming::hmc8015_sensor::log
 */
void visus::power_overwhelming::hmc8015_sensor::log(_In_ const bool enable) {
    auto impl = static_cast<detail::visa_sensor_impl&>(*this);

    //if (enable) {
    //    this->_impl->printf("INT:STAT ON\n");
    //    this->_impl->throw_on_system_error();

    //    this->_impl->printf("INT:RES\n");
    //    this->_impl->throw_on_system_error();

    //    this->_impl->printf("INT:STAR\n");
    //    this->_impl->throw_on_system_error();

    //} else {
    //    this->_impl->printf("INT:STOP\n");
    //    this->_impl->throw_on_system_error();

    //    this->_impl->printf("INT:STAT OFF\n");
    //    this->_impl->throw_on_system_error();
    //}

    impl.printf("LOG:STAT %s\n", enable ? "ON" : "OFF");
    this->throw_on_system_error();
}


/*
 * visus::power_overwhelming::hmc8015_sensor::log_behaviour
 */
void visus::power_overwhelming::hmc8015_sensor::log_behaviour(
        _In_ const float interval,
        _In_ const log_mode mode,
        _In_ const int value,
        _In_ const std::int32_t year,
        _In_ const std::int32_t month,
        _In_ const std::int32_t day,
        _In_ const std::int32_t hour,
        _In_ const std::int32_t minute,
        _In_ const std::int32_t second) {
    auto impl = static_cast<detail::visa_sensor_impl&>(*this);

    // Configure the logging mode.
    switch (mode) {
        case log_mode::count:
            impl.printf("LOG:MODE COUN\n");
            if (value == std::numeric_limits<decltype(value)>::lowest()) {
                impl.printf("LOG:COUN MIN\n");
            } else if (value == (std::numeric_limits<decltype(value)>::max)()) {
                impl.printf("LOG:COUN MAX\n");
            } else {
                impl.printf("LOG:COUN %d\n", value);
            }

            //this->_impl->printf("INT:MODE MAN\n");
            break;

        case log_mode::duration:
            impl.printf("LOG:MODE DUR\n");
            if (value == std::numeric_limits<decltype(value)>::lowest()) {
                impl.printf("LOG:DUR MIN\n");
            } else if (value == (std::numeric_limits<decltype(value)>::max)()) {
                impl.printf("LOG:DUR MAX\n");
            } else {
                impl.printf("LOG:DUR %d\n", value);
            }

            //this->_impl->printf("INT:MODE DUR\n");
            //if (value == std::numeric_limits<decltype(value)>::lowest()) {
            //    this->_impl->printf("INT:DUR MIN\n");
            //} else if (value == (std::numeric_limits<decltype(value)>::max)()) {
            //    this->_impl->printf("INT:DUR MAX\n");
            //} else {
            //    this->_impl->printf("INT:DUR %d\n", value);
            //}
            break;

        case log_mode::time_span:
            throw std::invalid_argument("time_span does not work ...");
            impl.printf("LOG:MODE SPAN\n");
            impl.printf("LOG:STIM %d, %d, %d, %d, %d, %d\n", year,
                month, day, hour, minute, second);
            if (value == std::numeric_limits<decltype(value)>::lowest()) {
                impl.printf("LOG:DUR MIN\n");
            } else if (value == (std::numeric_limits<decltype(value)>::max)()) {
                impl.printf("LOG:DUR MAX\n");
            } else {
                impl.printf("LOG:DUR %d\n", value);
            }

            //this->_impl->printf("INT:MODE SPAN\n");
            //this->_impl->printf("INT:STIM %d, %d, %d, %d, %d, %d\n", year,
            //    month, day, hour, minute, second);
            //if (value == std::numeric_limits<decltype(value)>::lowest()) {
            //    this->_impl->printf("INT:DUR MIN\n");
            //} else if (value == (std::numeric_limits<decltype(value)>::max)()) {
            //    this->_impl->printf("INT:DUR MAX\n");
            //} else {
            //    this->_impl->printf("INT:DUR %d\n", value);
            //}
            break;

        case log_mode::unlimited:
            impl.printf("LOG:MODE UNL\n");
            //this->_impl->printf("INT:MODE MAN\n");
            break;

        default:
            throw std::invalid_argument("The specified log mode is not "
                "supported by the instrument.");
    }

    this->throw_on_system_error();

    // Configure the logging interval.
    if (interval == std::numeric_limits<decltype(interval)>::lowest()) {
        impl.printf("LOG:INT MIN\n");
    } else if (interval == (std::numeric_limits<decltype(interval)>::max)()) {
        impl.printf("LOG:INT MAX\n");
    } else {
        impl.printf("LOG:INT %f\n", interval);
    }

    this->throw_on_system_error();

    // Use the first page configured in the constructor.
    impl.printf("LOG:PAGE 1\n");
    this->throw_on_system_error();
}


/*
 * visus::power_overwhelming::hmc8015_sensor::log_file
 */
std::size_t visus::power_overwhelming::hmc8015_sensor::log_file(
        _Out_writes_opt_z_(cnt) char *path, _In_ const std::size_t cnt) {
    auto impl = static_cast<detail::visa_sensor_impl&>(*this);

    this->check_not_disposed();
    impl.printf("LOG:FNAM?\n");

    // Read everything to prevent spurious responses in future calls.
    auto value = impl.read();

    // Copy as much as the output buffer can hold.
    if (path != nullptr) {
        for (std::size_t i = 0; (i < cnt) && (i < value.size()); ++i) {
            path[i] = value[i];
        }

        // The last character in the reponse is always the line feed, which
        // we just override with the the string terminator.
        path[cnt - 1] = 0;
    }

    return value.size();
}


/*
 * visus::power_overwhelming::hmc8015_sensor::log_file
 */
void visus::power_overwhelming::hmc8015_sensor::log_file(
        _In_z_ const char *path,
        _In_ const bool overwrite,
        _In_ const bool use_usb) {
    if (path == nullptr) {
        throw std::invalid_argument("The path to the log file cannot be null.");
    }

    auto impl = static_cast<detail::visa_sensor_impl&>(*this);
    auto location = use_usb ? "EXT" : "INT";

    impl.printf("DATA:DEL \"%s\", %s\n", path, location);
    impl.clear_status();    // Clear error in case file did not exist.

    impl.printf("LOG:FNAM \"%s\", %s\n", path, location);
    this->throw_on_system_error();
}


/*
 * visus::power_overwhelming::hmc8015_sensor::log_file
 */
void visus::power_overwhelming::hmc8015_sensor::log_file(
        _In_z_ const wchar_t *path,
        _In_ const bool overwrite,
        _In_ const bool use_usb) {
    if (path == nullptr) {
        throw std::invalid_argument("The path to the log file cannot be null.");
    }

    auto p = convert_string<char>(path);
    this->log_file(p.c_str(), overwrite, use_usb);
}


/*
 * visus::power_overwhelming::hmc8015_sensor::reset
 */
void visus::power_overwhelming::hmc8015_sensor::reset(void) {
    visa_sensor::reset();
    this->configure();
    this->throw_on_system_error();
    this->clear_status();
    this->throw_on_system_error();
}


/*
 * visus::power_overwhelming::hmc8015_sensor::sample
 */
visus::power_overwhelming::measurement
visus::power_overwhelming::hmc8015_sensor::sample(
        _In_ const timestamp_resolution resolution) const {
    auto impl = static_cast<detail::visa_sensor_impl&>(*this);
    auto response = impl.query("CHAN1:MEAS:DATA?\n");
    auto timestamp = create_timestamp(resolution);
    auto tokens = detail::tokenise(std::string(response.begin(),
        response.end()), ',', true);

    auto v = static_cast<measurement::value_type>(::atof(tokens[0].c_str()));
    auto c = static_cast<measurement::value_type>(::atof(tokens[1].c_str()));
    auto p = static_cast<measurement::value_type>(::atof(tokens[2].c_str()));

    _Analysis_assume_(this->name() != nullptr);
    return measurement(this->name(), timestamp, v, c, p);
}



/*
 * visus::power_overwhelming::hmc8015_sensor::configure
 */
void visus::power_overwhelming::hmc8015_sensor::configure(void) {
    auto impl = static_cast<detail::visa_sensor_impl&>(*this);

    // Configure the display to show always the same stuff.
    // Default: URMS,IRMS,P,FPLL,URAN,IRAN,S,Q,LAMB,PHI
    impl.printf("VIEW:NUM:SHOW 1\n");
    impl.printf("VIEW:NUM:PAGE1:SIZE 10\n");
    impl.printf("VIEW:NUM:PAGE1:CELL1:FUNC URMS\n");
    impl.printf("VIEW:NUM:PAGE1:CELL2:FUNC IRMS\n");
    impl.printf("VIEW:NUM:PAGE1:CELL3:FUNC URAN\n");
    impl.printf("VIEW:NUM:PAGE1:CELL4:FUNC IRAN\n");
    //this->_impl->printf("VIEW:NUM:PAGE1:CELL3:FUNC UAVG\n");
    //this->_impl->printf("VIEW:NUM:PAGE1:CELL4:FUNC IAVG\n");
    impl.printf("VIEW:NUM:PAGE1:CELL5:FUNC P\n");
    impl.printf("VIEW:NUM:PAGE1:CELL6:FUNC S\n");
    impl.printf("VIEW:NUM:PAGE1:CELL7:FUNC Q\n");
    impl.printf("VIEW:NUM:PAGE1:CELL8:FUNC TIME\n");
    impl.printf("VIEW:NUM:PAGE1:CELL9:FUNC WH\n");
    impl.printf("VIEW:NUM:PAGE1:CELL10:FUNC AH\n");

    // Configure the stuff we want to measure.
    // Default: URMS,IRMS,P,FPLL,URAN,IRAN,S,Q,LAMB,PHI
    impl.printf("CHAN1:MEAS:FUNC URMS, URAN, IRMS, IRAN, S, P\n");

    impl.printf("CHAN1:ACQ:MODE AUTO\n");
}


/*
 * visus::power_overwhelming::hmc8015_sensor::set_range
 */
void visus::power_overwhelming::hmc8015_sensor::set_range(
        _In_ const std::int32_t channel, _In_z_ const char *quantity,
        _In_ const instrument_range range, _In_ const float value) {
    assert(quantity != nullptr);
    auto impl = static_cast<detail::visa_sensor_impl &>(*this);

    switch (range) {
        case instrument_range::automatically:
            impl.printf("CHAN%d:ACQ:%s:RANG:AUTO ON\n", channel,
                quantity);
            break;

        case instrument_range::maximum:
            impl.printf("CHAN%d:ACQ:%s:RANG MAX\n", channel,
                quantity);
            break;

        case instrument_range::minimum:
            impl.printf("CHAN%d:ACQ:%s:RANG MIN\n", channel,
                quantity);
            break;

        case instrument_range::explicitly:
        default:
            impl.printf("CHAN%d:ACQ:%s:RANG %f\n", channel,
                quantity, value);
            break;
    }

    this->throw_on_system_error();
}
