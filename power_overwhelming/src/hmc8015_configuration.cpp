// <copyright file="hmc8015_configuration.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/hmc8015_configuration.h"

#include <cctype>
#include <iterator>
#include <memory>

#include "visus/pwrowg/convert_string.h"

#include "string_functions.h"


/*
 * PWROWG_NAMESPACE::hmc8015_configuration::id
 */
const PWROWG_NAMESPACE::guid PWROWG_NAMESPACE::hmc8015_configuration::id(
    0x20AC841C, 0xAE4D, 0x494B, 0xA861, 0x99, 0x28, 0x70, 0xEC, 0x03, 0x3E);


/*
 * PWROWG_NAMESPACE::hmc8015_configuration::hmc8015_configuration
 */
PWROWG_NAMESPACE::hmc8015_configuration::hmc8015_configuration(void) noexcept
        : _current_range(hmc8015_instrument_range::automatically),
        _current_range_value(0.0f),
        _cnt_functions(0),
        _functions(nullptr),
        _log_to_usb(false),
        _timeout(5000),
        _voltage_range(hmc8015_instrument_range::automatically),
        _voltage_range_value(0.0f) {
    this->timestamp_column(nullptr);
}


/*
 * PWROWG_NAMESPACE::hmc8015_configuration::hmc8015_configuration
 */
PWROWG_NAMESPACE::hmc8015_configuration::hmc8015_configuration(
        _In_ const hmc8015_configuration& rhs) noexcept
        : _cnt_functions(0), _functions(nullptr) {
    *this = rhs;
}


/*
 * PWROWG_NAMESPACE::hmc8015_configuration::~hmc8015_configuration
 */
PWROWG_NAMESPACE::hmc8015_configuration::~hmc8015_configuration(void) noexcept {
    delete[] this->_functions;
}


/*
 * PWROWG_NAMESPACE::hmc8015_configuration::functions
 */
PWROWG_NAMESPACE::hmc8015_configuration&
PWROWG_NAMESPACE::hmc8015_configuration::functions(
        _In_reads_opt_(cnt) const hmc8015_function *functions,
        _In_ const std::size_t cnt) {
    delete[] this->_functions;

    if ((functions != nullptr) && (cnt > 0)) {
        this->_cnt_functions = cnt;
        this->_functions = new hmc8015_function[this->_cnt_functions];
        std::copy(functions,
            functions + this->_cnt_functions,
            this->_functions);

    } else {
        this->_cnt_functions = 0;
        this->_functions = nullptr;
    }

    return *this;
}


/*
 * PWROWG_NAMESPACE::hmc8015_configuration::functions
 */
PWROWG_NAMESPACE::hmc8015_configuration&
PWROWG_NAMESPACE::hmc8015_configuration::functions(
        _In_ const hmc8015_function function) {
    auto existing = this->_functions;

    this->_functions = new hmc8015_function[this->_cnt_functions + 1];

    if (existing != nullptr) {
        std::copy(existing,
            existing + this->_cnt_functions,
            this->_functions);
    }

    this->_functions[this->_cnt_functions++] = function;

    return *this;
}


/*
 * PWROWG_NAMESPACE::hmc8015_configuration::log_file
 */
PWROWG_NAMESPACE::hmc8015_configuration&
PWROWG_NAMESPACE::hmc8015_configuration::log_file(_In_opt_z_ const char *path) {
    if (path != nullptr) {
        // If we have user input, make sure that it conforms with the
        // requirements of the instrument.
        const auto l = ::strlen(path);

        std::string p;
        p.reserve(l);

        // The device used all-uppercase. I think this is not mandatory, but who
        // knows ...
        std::transform(path,
            path + l,
            std::back_inserter(p),
            [](const char c) { return std::toupper(c); });

        // Erase user-defined extension, because the device will add ".CSV".
        const auto e = p.find_last_of('.');
        if (e != std::string::npos) {
            p.erase(e);
        }

        // Make sure that we have a valid 8+3 filename.
        if (p.length() > 8) {
            p.erase(8);
        }

        detail::safe_assign(this->_log_file, p);

    } else {
        detail::safe_assign(this->_log_file, path);
    }

    return *this;
}


/*
 * PWROWG_NAMESPACE::hmc8015_configuration::log_file
 */
PWROWG_NAMESPACE::hmc8015_configuration&
PWROWG_NAMESPACE::hmc8015_configuration::log_file(
        _In_opt_z_ const wchar_t *path) {
    if (path == nullptr) {
        detail::safe_assign(this->_log_file, path);
    } else {
        auto p = convert_string<wchar_t>(path);
        detail::safe_assign(this->_log_file, p);
    }

    return *this;
}


/*
 * PWROWG_NAMESPACE::hmc8015_configuration::timestamp_column
 */
PWROWG_NAMESPACE::hmc8015_configuration&
PWROWG_NAMESPACE::hmc8015_configuration::timestamp_column(
        _In_opt_z_ const char *name) {
    if ((name == nullptr) || (*name == 0)) {
        detail::safe_assign(this->_timestamp_column, "Timestamp");
    } else {
        detail::safe_assign(this->_timestamp_column, name);
    }

    return *this;
}


/*
 * PWROWG_NAMESPACE::hmc8015_configuration::timestamp_column
 */
PWROWG_NAMESPACE::hmc8015_configuration&
PWROWG_NAMESPACE::hmc8015_configuration::timestamp_column(
        _In_z_ const wchar_t *name) {
    auto n = convert_string<char>(name);
    return this->timestamp_column(n.c_str());
}


/*
 * PWROWG_NAMESPACE::hmc8015_configuration::timestamp_column
 */
PWROWG_NAMESPACE::hmc8015_configuration&
PWROWG_NAMESPACE::hmc8015_configuration::timestamp_column(
        _In_opt_z_ const std::nullptr_t name) {
    return this->timestamp_column(static_cast<char *>(nullptr));
}


/*
 * PWROWG_NAMESPACE::hmc8015_configuration::operator =
 */
PWROWG_NAMESPACE::hmc8015_configuration&
PWROWG_NAMESPACE::hmc8015_configuration::operator =(
        _In_ const hmc8015_configuration& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        this->_current_range = rhs._current_range;
        this->_current_range_value = rhs._current_range_value;
        this->functions(rhs._functions, rhs._cnt_functions);
        this->_log_file = rhs._log_file;
        this->_log_to_usb = rhs._log_to_usb;
        this->_timeout = rhs._timeout;
        this->_voltage_range = rhs._voltage_range;
        this->_voltage_range_value = rhs._voltage_range_value;
    }

    return *this;
}
