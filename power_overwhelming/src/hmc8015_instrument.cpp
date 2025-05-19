// <copyright file="hmc8015_instrument.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if defined(POWER_OVERWHELMING_WITH_VISA)
#include "visus/pwrowg/hmc8015_instrument.h"

#include <algorithm>
#include <cassert>
#include <limits>
#include <stdexcept>
#include <utility>

#include "visus/pwrowg/convert_string.h"
#include "visus/pwrowg/timestamp.h"

#include "string_functions.h"
#include "tokenise.h"
#include "visa_library.h"


/*
 * PWROWG_NAMESPACE::hmc8015_instrument::for_all
 */
std::size_t PWROWG_NAMESPACE::hmc8015_instrument::for_all(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) hmc8015_instrument *dst,
        _In_ std::size_t cnt,
        _In_ const std::int32_t timeout) {
    // Build the query for all R&S HMC8015 instruments.
    std::string query("?*::");      // Any protocol
    query += visa_instrument::rohde_und_schwarz;    // Only R&S
    query += "::";
    query += product_id;            // Only HMC8015
    query += "::?*::INSTR";         // All serial numbers.

    // Search the instruments using VISA.
    auto devices = PWROWG_DETAIL_NAMESPACE::visa_library::instance()
        .find_resource(query.c_str());

    // Guard against misuse.
    if (dst == nullptr) {
        cnt = 0;
    }

    // Create a sensor for each instrument we found.
    for (std::size_t i = 0; (i < cnt) && (i < devices.size()); ++i) {
        dst[i] = hmc8015_instrument(devices[i].c_str(), timeout);
    }

    return devices.size();
}


/*
 * PWROWG_NAMESPACE::hmc8015_instrument::hmc8015_instrument
 */
PWROWG_NAMESPACE::hmc8015_instrument::hmc8015_instrument(
        _In_z_ const wchar_t *path,
        _In_ const visa_instrument::timeout_type timeout)
        : visa_instrument(path, timeout) {
    this->initialise();
    this->configure();
}


/*
 * PWROWG_NAMESPACE::hmc8015_instrument::hmc8015_instrument
 */
PWROWG_NAMESPACE::hmc8015_instrument::hmc8015_instrument(
        _In_z_ const char *path,
        _In_ const visa_instrument::timeout_type timeout)
        : visa_instrument(path, timeout) {
    this->initialise();
    this->configure();
}


/*
 * PWROWG_NAMESPACE::hmc8015_instrument::hmc8015_instrument
 */
PWROWG_NAMESPACE::hmc8015_instrument::hmc8015_instrument(
        _Inout_ hmc8015_instrument&& rhs) noexcept
    : visa_instrument(std::move(rhs)) { }


/*
 * PWROWG_NAMESPACE::hmc8015_instrument::~hmc8015_instrument
 */
PWROWG_NAMESPACE::hmc8015_instrument::~hmc8015_instrument(void) {
    if (*this) {
        this->display(nullptr);
        // Reset the system state to local operations, but make sure that we
        // do not throw in the destructor. Therefore, we use the library
        // directly instead of the wrappers checking the state of the calls.
        this->write("SYST:LOC\n");
    }
}


/*
 * PWROWG_NAMESPACE::hmc8015_instrument::clear_internal_memory
 */
void PWROWG_NAMESPACE::hmc8015_instrument::clear_internal_memory(void) {
    const auto response = this->query("DATA:LIST? INT");
    const auto b = response.as<char>();
    assert(b != nullptr);
    assert(sizeof(char) == 1);
    const auto e = b + response.size();

    auto files = detail::tokenise(b, e, ',', true);

    for (auto& f : files) {
        detail::trim_if(f, [](const char c) {
            return (c == '"') || std::isspace(c);
        });

        this->delete_file_from_instrument(f.c_str());
    }
}


/*
 * PWROWG_NAMESPACE::hmc8015_instrument::copy_file_from_instrument
 */
PWROWG_NAMESPACE::blob
PWROWG_NAMESPACE::hmc8015_instrument::copy_file_from_instrument(
        _In_z_ const wchar_t *name, _In_ const bool use_usb) const {
    const auto n = convert_string<char>(name);
    return this->copy_file_from_instrument(n.c_str(), use_usb);
}


/*
 * PWROWG_NAMESPACE::hmc8015_instrument::copy_file_from_instrument
 */
PWROWG_NAMESPACE::blob
PWROWG_NAMESPACE::hmc8015_instrument::copy_file_from_instrument(
        _In_z_ const char *name, _In_  const bool use_usb) const {
    if ((name == nullptr) || (*name == 0)) {
        throw std::invalid_argument("The name of the file to read cannot be "
            "null or empty.");
    }

    auto path = detail::format_string("\"%s\", %s",
        name,
        (use_usb ? "EXT" : "INT"));
    return this->copy_file_from_instrument_or_usb(path.c_str());
}

/*
 * PWROWG_NAMESPACE::hmc8015_instrument::copy_file_from_instrument_or_usb
 */
PWROWG_NAMESPACE::blob
PWROWG_NAMESPACE::hmc8015_instrument::copy_file_from_instrument_or_usb(
        _In_z_ const wchar_t *name) const {
    const auto n = convert_string<char>(name);
    return this->copy_file_from_instrument_or_usb(n.c_str());
}


/*
 * PWROWG_NAMESPACE::hmc8015_instrument::copy_file_from_instrument_or_usb
 */
PWROWG_NAMESPACE::blob
PWROWG_NAMESPACE::hmc8015_instrument::copy_file_from_instrument_or_usb(
        _In_z_ const char *name) const {
    if ((name == nullptr) || (*name == 0)) {
        throw std::invalid_argument("The name of the file to read cannot be "
            "null or empty.");
    }

    auto query = detail::format_string("DATA:DATA? %s", name);
    this->write(query.c_str());
    return this->read_binary();
}


/*
 * PWROWG_NAMESPACE::hmc8015_instrument::custom_functions
 */
PWROWG_NAMESPACE::hmc8015_instrument&
PWROWG_NAMESPACE::hmc8015_instrument::custom_functions(
        _In_reads_(cnt) const hmc8015_function *functions,
        _In_ const std::size_t cnt) {
    if (functions == nullptr) {
        throw std::invalid_argument("The list of measurement functions must be "
            "valid.");
    }

    std::string cmd("CHAN1:MEAS:FUNC ");

    for (std::size_t i = 0; i < cnt; ++i) {
        if (i > 0) {
            cmd += ",";
        }
        cmd += convert_string<char>(to_string(functions[i]));
    }

    cmd += "\n";

    this->write(cmd.c_str());

    return *this;
}


/*
 * PWROWG_NAMESPACE::hmc8015_instrument::default_functions
 */
PWROWG_NAMESPACE::hmc8015_instrument&
PWROWG_NAMESPACE::hmc8015_instrument::default_functions(void) {
    this->write("CHAN1:MEAS:FUNC URMS, URAN, IRMS, IRAN, S, P\n");
    return *this;
}


/*
 * PWROWG_NAMESPACE::hmc8015_instrument::delete_file_from_instrument
 */
PWROWG_NAMESPACE::hmc8015_instrument&
PWROWG_NAMESPACE::hmc8015_instrument::delete_file_from_instrument(
        _In_z_ const wchar_t *name,
        _In_ const bool use_usb) {
    const auto n = convert_string<char>(name);
    return this->delete_file_from_instrument(n.c_str(), use_usb);
}


/*
 * PWROWG_NAMESPACE::hmc8015_instrument::delete_file_from_instrument
 */
PWROWG_NAMESPACE::hmc8015_instrument&
PWROWG_NAMESPACE::hmc8015_instrument::delete_file_from_instrument(
        _In_z_ const char *name,
        _In_ const bool use_usb) {
    if ((name == nullptr) || (*name == 0)) {
        throw std::invalid_argument("The name of the file to delete cannot be "
            "null or empty.");
    }

    auto path = detail::format_string("\"%s\", %s",
        name,
        (use_usb ? "EXT" : "INT"));
    return this->delete_file_from_instrument_or_usb(path.c_str());
}


/*
 * PWROWG_NAMESPACE::hmc8015_instrument::delete_file_from_instrument_or_usb
 */
PWROWG_NAMESPACE::hmc8015_instrument&
PWROWG_NAMESPACE::hmc8015_instrument::delete_file_from_instrument_or_usb(
        _In_z_ const wchar_t *name) {
    const auto n = convert_string<char>(name);
    return this->delete_file_from_instrument_or_usb(n.c_str());
}


/*
 * PWROWG_NAMESPACE::hmc8015_instrument::delete_file_from_instrument_or_usb
 */
PWROWG_NAMESPACE::hmc8015_instrument&
PWROWG_NAMESPACE::hmc8015_instrument::delete_file_from_instrument_or_usb(
        _In_z_ const char *name) {
    if ((name == nullptr) || (*name == 0)) {
        throw std::invalid_argument("The name of the file to delete cannot be "
            "null or empty.");
    }

    auto query = detail::format_string("DATA:DEL %s", name);
    this->write(query.c_str());
    return *this;
}


/*
 * PWROWG_NAMESPACE::hmc8015_instrument::display
 */
PWROWG_NAMESPACE::hmc8015_instrument&
PWROWG_NAMESPACE::hmc8015_instrument::display(
        _In_opt_z_ const char *text) {
    if (text != nullptr) {
        auto cmd = PWROWG_DETAIL_NAMESPACE::format_string(
            "DISP:TEXT:DATA \"%s\"\n", text);
        this->write(cmd);
    } else {
        this->write("DISP:TEXT:CLE\n");
    }

    return *this;
}


/*
 * PWROWG_NAMESPACE::hmc8015_instrument::display
 */
PWROWG_NAMESPACE::hmc8015_instrument&
PWROWG_NAMESPACE::hmc8015_instrument::display(
        _In_opt_z_ const wchar_t *text) {
    if (text != nullptr) {
        auto cmd = convert_string<char>(PWROWG_DETAIL_NAMESPACE::format_string(
            L"DISP:TEXT:DATA \"%s\"\n", text));
        this->write(cmd);
    } else {
        this->write("DISP:TEXT:CLE\n");
    }

    return *this;
}


/*
 * PWROWG_NAMESPACE::hmc8015_instrument::functions
 */
std::size_t PWROWG_NAMESPACE::hmc8015_instrument::functions(
        _Out_writes_opt_z_(cnt) char *dst,
        _In_ const std::size_t cnt) const {
    auto value = this->query("CHAN1:MEAS:FUNC?\n");

    // Copy as much as the output buffer can hold.
    if (dst != nullptr) {
        for (std::size_t i = 0; (i < cnt) && (i < value.size()); ++i) {
            _Analysis_assume_(value.as<char>(i) != nullptr);
            dst[i] = *value.as<char>(i);
        }

        // The last character in the reponse is always the line feed, which
        // we just override with the the string terminator.
        dst[cnt - 1] = 0;
    }

    return value.size();
}


/*
 * PWROWG_NAMESPACE::hmc8015_instrument::integrator_behaviour
 */
PWROWG_NAMESPACE::hmc8015_instrument&
PWROWG_NAMESPACE::hmc8015_instrument::integrator_behaviour(
        _In_ const hmc8015_integrator_mode mode,
        _In_ const int duration,
        _In_ const std::int32_t year,
        _In_ const std::int32_t month,
        _In_ const std::int32_t day,
        _In_ const std::int32_t hour,
        _In_ const std::int32_t minute,
        _In_ const std::int32_t second) {
    typedef std::numeric_limits<decltype(duration)> dur_limits;

    // Configure the logging mode.
    switch (mode) {
        case hmc8015_integrator_mode::duration:
            this->write("INT:MODE DUR\n");
            if (duration == dur_limits::lowest()) {
                this->write("INT:DUR MIN\n");
            } else if (duration == (dur_limits::max)()) {
                this->write("INT:DUR MAX\n");
            } else {
                auto cmd = PWROWG_DETAIL_NAMESPACE::format_string(
                    "INT:DUR %d\n", duration);
                this->write(cmd);
            }
            break;

        case hmc8015_integrator_mode::time_span:
            this->write("INT:MODE SPAN\n");

            {
                auto cmd = PWROWG_DETAIL_NAMESPACE::format_string(
                    "INT:STIM %d, %d, %d, %d, %d, %d\n",
                    year, month, day, hour, minute, second);
                this->write(cmd);
            }

            if (duration == dur_limits::lowest()) {
                this->write("INT:DUR MIN\n");
            } else if (duration == (dur_limits::max)()) {
                this->write("INT:DUR MAX\n");
            } else {
                auto cmd = PWROWG_DETAIL_NAMESPACE::format_string(
                    "INT:DUR %d\n", duration);
                this->write(cmd);
            }
            break;

        case hmc8015_integrator_mode::manual:
            this->write("INT:MODE MAN\n");
            break;

        default:
            throw std::invalid_argument("The specified integrator mode is not "
                "supported by the instrument.");
    }

    return *this;
}


/*
 * PWROWG_NAMESPACE::hmc8015_instrument::list_files_on_instrument
 */
std::size_t PWROWG_NAMESPACE::hmc8015_instrument::list_files_on_instrument(
        _Out_writes_opt_z_(cnt) char *dst,
        _In_ const std::size_t cnt,
        _In_ const bool use_usb) const {
    auto retval = this->query(use_usb ? "DATA:LIST? EXT" : "DATA:LIST? INT");

    if ((dst != nullptr) && (cnt > 0)) {
        const auto c = (std::min)(cnt, retval.size());
        std::copy_n(retval.begin(), c, dst);
        dst[c - 1] = 0;
    }

    return retval.size();
}


/*
 * PWROWG_NAMESPACE::hmc8015_instrument::log
 */
PWROWG_NAMESPACE::hmc8015_instrument&
PWROWG_NAMESPACE::hmc8015_instrument::log(_In_ const bool enable) {
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

    auto cmd = PWROWG_DETAIL_NAMESPACE::format_string("LOG:STAT %s\n",
        enable ? "ON" : "OFF");
    this->write(cmd);

    return *this;
}


/*
 * PWROWG_NAMESPACE::hmc8015_instrument::logging
 */
bool PWROWG_NAMESPACE::hmc8015_instrument::logging(void) const {
    auto response = this->query("LOG:STATE?\n");
    auto status = response.as<char>();
    return ((status != nullptr) && (*status != '0'));
}


/*
 * PWROWG_NAMESPACE::hmc8015_instrument::log_behaviour
 */
PWROWG_NAMESPACE::hmc8015_instrument&
PWROWG_NAMESPACE::hmc8015_instrument::log_behaviour(
        _In_ const float interval,
        _In_ const hmc8015_log_mode mode,
        _In_ const int value,
        _In_ const std::int32_t year,
        _In_ const std::int32_t month,
        _In_ const std::int32_t day,
        _In_ const std::int32_t hour,
        _In_ const std::int32_t minute,
        _In_ const std::int32_t second) {
    // Configure the logging mode.
    switch (mode) {
        case hmc8015_log_mode::count:
            this->write("LOG:MODE COUN\n");
            if (value == std::numeric_limits<decltype(value)>::lowest()) {
                this->write("LOG:COUN MIN\n");
            } else if (value == (std::numeric_limits<decltype(value)>::max)()) {
                this->write("LOG:COUN MAX\n");
            } else {
                auto cmd = PWROWG_DETAIL_NAMESPACE::format_string(
                    "LOG:COUN %d\n", value);
                this->write(cmd);
            }

            //this->_impl->printf("INT:MODE MAN\n");
            break;

        case hmc8015_log_mode::duration:
            this->write("LOG:MODE DUR\n");
            if (value == std::numeric_limits<decltype(value)>::lowest()) {
                this->write("LOG:DUR MIN\n");
            } else if (value == (std::numeric_limits<decltype(value)>::max)()) {
                this->write("LOG:DUR MAX\n");
            } else {
                auto cmd = PWROWG_DETAIL_NAMESPACE::format_string(
                    "LOG:DUR %d\n", value);
                this->write(cmd);
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

        case hmc8015_log_mode::time_span:
            throw std::invalid_argument("time_span does not work ...");
            this->write("LOG:MODE SPAN\n");

            {
                auto cmd = PWROWG_DETAIL_NAMESPACE::format_string(
                    "LOG:STIM %d, %d, %d, %d, %d, %d\n",
                    year, month, day, hour, minute, second);
                this->write(cmd);
            }

            if (value == std::numeric_limits<decltype(value)>::lowest()) {
                this->write("LOG:DUR MIN\n");
            } else if (value == (std::numeric_limits<decltype(value)>::max)()) {
                this->write("LOG:DUR MAX\n");
            } else {
                auto cmd = PWROWG_DETAIL_NAMESPACE::format_string(
                    "LOG:DUR %d\n", value);
                this->write(cmd.c_str());
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

        case hmc8015_log_mode::unlimited:
            this->write("LOG:MODE UNL\n");
            //this->_impl->printf("INT:MODE MAN\n");
            break;

        default:
            throw std::invalid_argument("The specified log mode is not "
                "supported by the instrument.");
    }

    // Configure the logging interval.
    if (interval == std::numeric_limits<decltype(interval)>::lowest()) {
        this->write("LOG:INT MIN\n");
    } else if (interval == (std::numeric_limits<decltype(interval)>::max)()) {
        this->write("LOG:INT MAX\n");
    } else {
        auto cmd = PWROWG_DETAIL_NAMESPACE::format_string("LOG:INT %f\n",
            interval);
        this->write(cmd);
    }

    // Use the first page configured in the constructor.
    this->write("LOG:PAGE 1\n");

    //// Wait for the device to finish.
    //this->operation_complete();

    return *this;
}


/*
 * PWROWG_NAMESPACE::hmc8015_instrument::log_file
 */
std::size_t PWROWG_NAMESPACE::hmc8015_instrument::log_file(
        _Out_writes_opt_z_(cnt) char *path, _In_ const std::size_t cnt) {
    auto value = this->query("LOG:FNAM?\n");

    // Copy as much as the output buffer can hold.
    if ((path != nullptr) && !value.empty()) {
        auto src = value.as<char>();
        _Analysis_assume_(src != nullptr);

        for (std::size_t i = 0; (i < cnt) && (i < value.size()); ++i) {
            path[i] = src[i];
        }

        // The last character in the reponse is always the line feed, which
        // we just override with the the string terminator.
        path[cnt - 1] = 0;
    }

    return value.size();
}


/*
 * PWROWG_NAMESPACE::hmc8015_instrument::log_file
 */
PWROWG_NAMESPACE::hmc8015_instrument&
PWROWG_NAMESPACE::hmc8015_instrument::log_file(
        _In_z_ const char *path,
        _In_ const bool overwrite,
        _In_ const bool use_usb) {
    if (path == nullptr) {
        throw std::invalid_argument("The path to the log file cannot be null.");
    }

    if (overwrite) {
        auto cmd = use_usb
            ? detail::format_string("DATA:DEL \"%s%s.CSV\", EXT\n",
                ext_log_directory, path)
            : detail::format_string("DATA:DEL \"%s.CSV\", INT\n", path);
        this->write(cmd);
        this->operation_complete();
        // Clear error in case file did not exist.
        this->clear_status();
    }

    {
        auto cmd = PWROWG_DETAIL_NAMESPACE::format_string(
            "LOG:FNAM \"%s\", %s\n", path, use_usb ? "EXT" : "INT");
        this->write(cmd);
        this->operation_complete();
    }

    this->throw_on_system_error();
    return *this;
}


/*
 * PWROWG_NAMESPACE::hmc8015_instrument::log_file
 */
PWROWG_NAMESPACE::hmc8015_instrument&
PWROWG_NAMESPACE::hmc8015_instrument::log_file(
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
 * PWROWG_NAMESPACE::hmc8015_instrument::reset_integrator
 */
PWROWG_NAMESPACE::hmc8015_instrument&
PWROWG_NAMESPACE::hmc8015_instrument::reset_integrator(void) {
    this->write("INT:RES\n");
    return *this;
}


/*
 * PWROWG_NAMESPACE::hmc8015_instrument::start_integrator
 */
PWROWG_NAMESPACE::hmc8015_instrument&
PWROWG_NAMESPACE::hmc8015_instrument::start_integrator(void) {
    this->write("INT:STAR\n");
    return *this;
}


/*
 * PWROWG_NAMESPACE::hmc8015_instrument::stop_integrator
 */
PWROWG_NAMESPACE::hmc8015_instrument&
PWROWG_NAMESPACE::hmc8015_instrument::stop_integrator(void) {
    this->write("INT:STOP\n");
    return *this;
}


/*
 * PWROWG_NAMESPACE::hmc8015_instrument::operator =
 */
PWROWG_NAMESPACE::hmc8015_instrument&
PWROWG_NAMESPACE::hmc8015_instrument::operator =(
        _Inout_ hmc8015_instrument&& rhs) noexcept {
    visa_instrument::operator =(std::move(rhs));
    return *this;
}

//
///*
// * PWROWG_NAMESPACE::hmc8015_instrument::sample_sync
// */
//PWROWG_NAMESPACE::measurement_data
//PWROWG_NAMESPACE::hmc8015_instrument::sample_sync(void) const {
//    assert(*this);
//
//    // TODO: could use CHAN1:MEAS:FORM BIN here.
//    auto response = this->_instrument.query("CHAN1:MEAS:DATA?\n");
//    auto timestamp = power_overwhelming::timestamp::now();
//    auto tokens = detail::tokenise(std::string(response.begin(),
//        response.end()), ',', true);
//
//    auto v = static_cast<measurement::value_type>(::atof(tokens[0].c_str()));
//    auto c = static_cast<measurement::value_type>(::atof(tokens[1].c_str()));
//    auto p = static_cast<measurement::value_type>(::atof(tokens[2].c_str()));
//
//    return measurement_data(timestamp, v, c, p);
//}


/*
 * PWROWG_NAMESPACE::hmc8015_instrument::configure
 */
void PWROWG_NAMESPACE::hmc8015_instrument::configure(void) {
    assert(*this);

    // Configure the display to show always the same stuff.
    // Default: URMS,IRMS,TPredicate,FPLL,URAN,IRAN,S,Q,LAMB,PHI
    this->write("VIEW:NUM:SHOW 1\n");
    this->write("VIEW:NUM:PAGE1:SIZE 10\n");
    this->write("VIEW:NUM:PAGE1:CELL1:FUNC URMS\n");
    this->write("VIEW:NUM:PAGE1:CELL2:FUNC IRMS\n");
    this->write("VIEW:NUM:PAGE1:CELL3:FUNC URAN\n");
    this->write("VIEW:NUM:PAGE1:CELL4:FUNC IRAN\n");
    //this->_impl->printf("VIEW:NUM:PAGE1:CELL3:FUNC UAVG\n");
    //this->_impl->printf("VIEW:NUM:PAGE1:CELL4:FUNC IAVG\n");
    this->write("VIEW:NUM:PAGE1:CELL5:FUNC P\n");
    this->write("VIEW:NUM:PAGE1:CELL6:FUNC S\n");
    this->write("VIEW:NUM:PAGE1:CELL7:FUNC Q\n");
    this->write("VIEW:NUM:PAGE1:CELL8:FUNC TIME\n");
    this->write("VIEW:NUM:PAGE1:CELL9:FUNC WH\n");
    this->write("VIEW:NUM:PAGE1:CELL10:FUNC AH\n");

    // Configure the stuff we want to measure.
    // Default: URMS,IRMS,TPredicate,FPLL,URAN,IRAN,S,Q,LAMB,PHI
    this->default_functions();

    this->write("CHAN1:ACQ:MODE AUTO\n");
}


/*
 * PWROWG_NAMESPACE::hmc8015_instrument::initialise
 */
void PWROWG_NAMESPACE::hmc8015_instrument::initialise(void) {
    assert(*this);

    // Reset the device to default state.
    this->reset();

    // Configure the device as in the R&S instrument driver.
    this->attribute(VI_ATTR_TMO_VALUE, 5000);
    this->buffer((VI_READ_BUF | VI_WRITE_BUF), 4096);
    this->attribute(VI_ATTR_WR_BUF_OPER_MODE, VI_FLUSH_ON_ACCESS);
    this->attribute(VI_ATTR_RD_BUF_OPER_MODE, VI_FLUSH_ON_ACCESS);

    //// Lock the system to indicate that it is controlled by the software. As
    //// locking the system is not critical, do not check for system errors here.
    //this->write("SYST:REM\n");

    // Clear any error that might have been caused by our setup. We do not want
    // to abort just because the display does not look as expected.
    this->clear_status();
}


/*
 * PWROWG_NAMESPACE::hmc8015_instrument::set_range
 */
void PWROWG_NAMESPACE::hmc8015_instrument::set_range(
        _In_ const std::int32_t channel, _In_z_ const char *quantity,
        _In_ const hmc8015_instrument_range range, _In_ const float value) {
    assert(*this);
    assert(quantity != nullptr);

    switch (range) {
        case hmc8015_instrument_range::automatically: {
            auto cmd = PWROWG_DETAIL_NAMESPACE::format_string(
                "CHAN%d:ACQ:%s:RANG:AUTO ON\n", channel, quantity);
            this->write(cmd);
            } break;

        case hmc8015_instrument_range::maximum: {
            auto cmd = PWROWG_DETAIL_NAMESPACE::format_string(
                "CHAN%d:ACQ:%s:RANG MAX\n", channel, quantity);
            this->write(cmd);
            } break;

        case hmc8015_instrument_range::minimum: {
            auto cmd = PWROWG_DETAIL_NAMESPACE::format_string(
                "CHAN%d:ACQ:%s:RANG MIN\n", channel, quantity);
            this->write(cmd);
            } break;

        case hmc8015_instrument_range::explicitly:
        default: {
            auto cmd = PWROWG_DETAIL_NAMESPACE::format_string(
                "CHAN%d:ACQ:%s:RANG %f\n", channel, quantity, value);
            this->write(cmd);
            } break;
    }
}

#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */
