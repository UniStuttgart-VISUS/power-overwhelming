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

#include "string_functions.h"
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
    query += visa_instrument::rohde_und_schwarz;    // Only R&S
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
        _In_z_ const wchar_t *path,
        _In_ const visa_instrument::timeout_type timeout)
        : _instrument(path, timeout), _name(nullptr) {
    this->initialise();
    this->configure();
}


/*
 * visus::power_overwhelming::hmc8015_sensor::hmc8015_sensor
 */
visus::power_overwhelming::hmc8015_sensor::hmc8015_sensor(
        _In_z_ const char *path,
        _In_ const visa_instrument::timeout_type timeout)
        : _instrument(path, timeout), _name(nullptr) {
    this->initialise();
    this->configure();
}


/*
 * visus::power_overwhelming::hmc8015_sensor::hmc8015_sensor
 */
visus::power_overwhelming::hmc8015_sensor::hmc8015_sensor(
        _Inout_ hmc8015_sensor&& rhs) noexcept
    : _instrument(std::move(rhs._instrument)), _name(rhs._name) {
    rhs._name = nullptr;
}


/*
 * visus::power_overwhelming::hmc8015_sensor::~hmc8015_sensor
 */
visus::power_overwhelming::hmc8015_sensor::~hmc8015_sensor(void) {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    if (this->_instrument) {
        // Reset the system state to local operations, but make sure that we
        // do not throw in the destructor. Therefore, we use the library
        // directly instead of the wrappers checking the state of the calls.
        this->_instrument.write("SYST:LOC\n");
    }

    delete[] this->_name;
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
}


/*
 * visus::power_overwhelming::hmc8015_sensor::display
 */
visus::power_overwhelming::hmc8015_sensor&
visus::power_overwhelming::hmc8015_sensor::display(
        _In_opt_z_ const char *text) {
    if (text != nullptr) {
        auto cmd = detail::format_string("DISP:TEXT:DATA \"%s\"\n", text);
        this->_instrument.write(cmd);
    } else {
        this->_instrument.write("DISP:TEXT:CLE\n");
    }

    this->_instrument.throw_on_system_error();
    return *this;
}


/*
 * visus::power_overwhelming::hmc8015_sensor::display
 */
visus::power_overwhelming::hmc8015_sensor&
visus::power_overwhelming::hmc8015_sensor::display(
        _In_opt_z_ const wchar_t *text) {
    if (text != nullptr) {
        auto cmd = convert_string<char>(detail::format_string(
            L"DISP:TEXT:DATA \"%s\"\n", text));
        this->_instrument.write(cmd);
    } else {
        this->_instrument.write("DISP:TEXT:CLE\n");
    }

    this->_instrument.throw_on_system_error();
    return *this;
}


/*
 * visus::power_overwhelming::hmc8015_sensor::is_log
 */
bool visus::power_overwhelming::hmc8015_sensor::is_log(void) {
    auto response = this->_instrument.query("LOG:STATE?\n");
    return (!response.empty() && (*response.as<char>() != '0'));
}


/*
 * visus::power_overwhelming::hmc8015_sensor::log
 */
visus::power_overwhelming::hmc8015_sensor&
visus::power_overwhelming::hmc8015_sensor::log(_In_ const bool enable) {
    this->check_not_disposed();

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

    auto cmd = detail::format_string("LOG:STAT %s\n", enable ? "ON" : "OFF");
    this->_instrument.write(cmd);

    this->_instrument.throw_on_system_error();
    return *this;
}


/*
 * visus::power_overwhelming::hmc8015_sensor::log_behaviour
 */
visus::power_overwhelming::hmc8015_sensor&
visus::power_overwhelming::hmc8015_sensor::log_behaviour(
        _In_ const float interval,
        _In_ const log_mode mode,
        _In_ const int value,
        _In_ const std::int32_t year,
        _In_ const std::int32_t month,
        _In_ const std::int32_t day,
        _In_ const std::int32_t hour,
        _In_ const std::int32_t minute,
        _In_ const std::int32_t second) {
    // Configure the logging mode.
    switch (mode) {
        case log_mode::count:
            this->_instrument.write("LOG:MODE COUN\n");
            if (value == std::numeric_limits<decltype(value)>::lowest()) {
                this->_instrument.write("LOG:COUN MIN\n");
            } else if (value == (std::numeric_limits<decltype(value)>::max)()) {
                this->_instrument.write("LOG:COUN MAX\n");
            } else {
                auto cmd = detail::format_string("LOG:COUN %d\n", value);
                this->_instrument.write(cmd);
            }

            //this->_impl->printf("INT:MODE MAN\n");
            break;

        case log_mode::duration:
            this->_instrument.write("LOG:MODE DUR\n");
            if (value == std::numeric_limits<decltype(value)>::lowest()) {
                this->_instrument.write("LOG:DUR MIN\n");
            } else if (value == (std::numeric_limits<decltype(value)>::max)()) {
                this->_instrument.write("LOG:DUR MAX\n");
            } else {
                auto cmd = detail::format_string("LOG:DUR %d\n", value);
                this->_instrument.write(cmd);
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
            this->_instrument.write("LOG:MODE SPAN\n");

            {
                auto cmd = detail::format_string(
                    "LOG:STIM %d, %d, %d, %d, %d, %d\n",
                    year, month, day, hour, minute, second);
                this->_instrument.write(cmd);
            }

            if (value == std::numeric_limits<decltype(value)>::lowest()) {
                this->_instrument.write("LOG:DUR MIN\n");
            } else if (value == (std::numeric_limits<decltype(value)>::max)()) {
                this->_instrument.write("LOG:DUR MAX\n");
            } else {
                auto cmd = detail::format_string("LOG:DUR %d\n", value);
                this->_instrument.write(cmd.c_str());
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
            this->_instrument.write("LOG:MODE UNL\n");
            //this->_impl->printf("INT:MODE MAN\n");
            break;

        default:
            throw std::invalid_argument("The specified log mode is not "
                "supported by the instrument.");
    }

    this->_instrument.throw_on_system_error();

    // Configure the logging interval.
    if (interval == std::numeric_limits<decltype(interval)>::lowest()) {
        this->_instrument.write("LOG:INT MIN\n");
    } else if (interval == (std::numeric_limits<decltype(interval)>::max)()) {
        this->_instrument.write("LOG:INT MAX\n");
    } else {
        auto cmd = detail::format_string("LOG:INT %f\n", interval);
        this->_instrument.write(cmd);
    }

    this->_instrument.throw_on_system_error();

    // Use the first page configured in the constructor.
    this->_instrument.write("LOG:PAGE 1\n");
    this->_instrument.throw_on_system_error();
}


/*
 * visus::power_overwhelming::hmc8015_sensor::log_file
 */
std::size_t visus::power_overwhelming::hmc8015_sensor::log_file(
        _Out_writes_opt_z_(cnt) char *path, _In_ const std::size_t cnt) {
    auto value = this->_instrument.query("LOG:FNAM?\n");

    // Copy as much as the output buffer can hold.
    if (path != nullptr) {
        for (std::size_t i = 0; (i < cnt) && (i < value.size()); ++i) {
            path[i] = *value.as<char>(i);
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
visus::power_overwhelming::hmc8015_sensor&
visus::power_overwhelming::hmc8015_sensor::log_file(
        _In_z_ const char *path,
        _In_ const bool overwrite,
        _In_ const bool use_usb) {
    if (path == nullptr) {
        throw std::invalid_argument("The path to the log file cannot be null.");
    }

    auto location = use_usb ? "EXT" : "INT";

    if (overwrite) {
        auto cmd = detail::format_string("DATA:DEL \"%s\", %s\n", path,
            location);
        this->_instrument.write(cmd);
        // Clear error in case file did not exist.
        this->_instrument.clear_status();
    }

    {
        auto cmd = detail::format_string("LOG:FNAM \"%s\", %s\n", path,
            location);
        this->_instrument.write(cmd);
    }

    this->_instrument.throw_on_system_error();
    return *this;
}


/*
 * visus::power_overwhelming::hmc8015_sensor::log_file
 */
visus::power_overwhelming::hmc8015_sensor&
visus::power_overwhelming::hmc8015_sensor::log_file(
        _In_z_ const wchar_t *path,
        _In_ const bool overwrite,
        _In_ const bool use_usb) {
    if (path == nullptr) {
        throw std::invalid_argument("The path to the log file cannot be null.");
    }

    auto p = convert_string<char>(path);
    return this->log_file(p.c_str(), overwrite, use_usb);
}


/*
 * visus::power_overwhelming::hmc8015_sensor::name
 */
_Ret_maybenull_z_ const wchar_t *
visus::power_overwhelming::hmc8015_sensor::name(void) const noexcept {
    return this->_name;
}

/*
 * visus::power_overwhelming::hmc8015_sensor::reset
 */
visus::power_overwhelming::hmc8015_sensor&
visus::power_overwhelming::hmc8015_sensor::reset(void) {
    this->_instrument.reset();
    this->configure();
    this->_instrument.throw_on_system_error();
    this->_instrument.clear_status();
    this->_instrument.throw_on_system_error();
    return *this;
}


/*
 * visus::power_overwhelming::hmc8015_sensor::operator =
 */
visus::power_overwhelming::hmc8015_sensor&
visus::power_overwhelming::hmc8015_sensor::operator =(
        _Inout_ hmc8015_sensor&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        this->_instrument = std::move(rhs._instrument);
        assert(rhs._instrument == false);
        this->_name = rhs._name;
        rhs._name = nullptr;
    }

    return *this;
}


/*
 * visus::power_overwhelming::hmc8015_sensor::operator bool
 */
visus::power_overwhelming::hmc8015_sensor::operator bool(void) const noexcept {
    return static_cast<bool>(this->_instrument);
}


/*
 * visus::power_overwhelming::hmc8015_sensor::sample_sync
 */
visus::power_overwhelming::measurement_data
visus::power_overwhelming::hmc8015_sensor::sample_sync(
        _In_ const timestamp_resolution resolution) const {
    auto response = this->_instrument.query("CHAN1:MEAS:DATA?\n");
    auto timestamp = detail::create_timestamp(resolution);
    auto tokens = detail::tokenise(std::string(response.begin(),
        response.end()), ',', true);

    auto v = static_cast<measurement::value_type>(::atof(tokens[0].c_str()));
    auto c = static_cast<measurement::value_type>(::atof(tokens[1].c_str()));
    auto p = static_cast<measurement::value_type>(::atof(tokens[2].c_str()));

    return measurement_data(timestamp, v, c, p);
}


/*
 * visus::power_overwhelming::hmc8015_sensor::configure
 */
void visus::power_overwhelming::hmc8015_sensor::configure(void) {
    // Configure the display to show always the same stuff.
    // Default: URMS,IRMS,P,FPLL,URAN,IRAN,S,Q,LAMB,PHI
    this->_instrument.write("VIEW:NUM:SHOW 1\n");
    this->_instrument.write("VIEW:NUM:PAGE1:SIZE 10\n");
    this->_instrument.write("VIEW:NUM:PAGE1:CELL1:FUNC URMS\n");
    this->_instrument.write("VIEW:NUM:PAGE1:CELL2:FUNC IRMS\n");
    this->_instrument.write("VIEW:NUM:PAGE1:CELL3:FUNC URAN\n");
    this->_instrument.write("VIEW:NUM:PAGE1:CELL4:FUNC IRAN\n");
    //this->_impl->printf("VIEW:NUM:PAGE1:CELL3:FUNC UAVG\n");
    //this->_impl->printf("VIEW:NUM:PAGE1:CELL4:FUNC IAVG\n");
    this->_instrument.write("VIEW:NUM:PAGE1:CELL5:FUNC P\n");
    this->_instrument.write("VIEW:NUM:PAGE1:CELL6:FUNC S\n");
    this->_instrument.write("VIEW:NUM:PAGE1:CELL7:FUNC Q\n");
    this->_instrument.write("VIEW:NUM:PAGE1:CELL8:FUNC TIME\n");
    this->_instrument.write("VIEW:NUM:PAGE1:CELL9:FUNC WH\n");
    this->_instrument.write("VIEW:NUM:PAGE1:CELL10:FUNC AH\n");

    // Configure the stuff we want to measure.
    // Default: URMS,IRMS,P,FPLL,URAN,IRAN,S,Q,LAMB,PHI
    this->_instrument.write("CHAN1:MEAS:FUNC URMS, URAN, IRMS, IRAN, S, P\n");

    this->_instrument.write("CHAN1:ACQ:MODE AUTO\n");
}


/*
 * visus::power_overwhelming::hmc8015_sensor::initialise
 */
void visus::power_overwhelming::hmc8015_sensor::initialise(void) {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    // Query the instrument name for use a sensor name.
    {
        auto l = this->_instrument.identify(static_cast<wchar_t *>(nullptr), 0);
        this->_name = new wchar_t[l];
        this->_instrument.identify(this->_name, l);
    }

    // Reset the device to default state.
    this->_instrument.reset();

    // Configure the device as in the R&S instrument driver.
    this->_instrument.attribute(VI_ATTR_TMO_VALUE, 5000);
    this->_instrument.buffer((VI_READ_BUF | VI_WRITE_BUF), 4096);
    this->_instrument.attribute(VI_ATTR_WR_BUF_OPER_MODE, VI_FLUSH_ON_ACCESS);
    this->_instrument.attribute(VI_ATTR_RD_BUF_OPER_MODE, VI_FLUSH_ON_ACCESS);

    // Lock the system to indicate that it is controlled by the software. As
    // locking the system is not critical, do not check for system errors here.
    this->_instrument.write("SYST:REM\n");

    // Clear any error that might have been caused by our setup. We do not want
    // to abort just because the display does not look as expected.
    this->_instrument.clear_status();
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
}


/*
 * visus::power_overwhelming::hmc8015_sensor::set_range
 */
void visus::power_overwhelming::hmc8015_sensor::set_range(
        _In_ const std::int32_t channel, _In_z_ const char *quantity,
        _In_ const instrument_range range, _In_ const float value) {
    assert(quantity != nullptr);

    switch (range) {
        case instrument_range::automatically: {
            auto cmd = detail::format_string("CHAN%d:ACQ:%s:RANG:AUTO ON\n",
                channel, quantity);
            this->_instrument.write(cmd);
            } break;

        case instrument_range::maximum: {
            auto cmd = detail::format_string("CHAN%d:ACQ:%s:RANG MAX\n",
                channel, quantity);
            this->_instrument.write(cmd);
            } break;

        case instrument_range::minimum: {
            auto cmd = detail::format_string("CHAN%d:ACQ:%s:RANG MIN\n",
                channel, quantity);
            this->_instrument.write(cmd);
            } break;

        case instrument_range::explicitly:
        default: {
            auto cmd = detail::format_string("CHAN%d:ACQ:%s:RANG %f\n",
                channel, quantity, value);
            this->_instrument.write(cmd);
            } break;
    }

    this->_instrument.throw_on_system_error();
}
