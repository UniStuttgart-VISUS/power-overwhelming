// <copyright file="hmc8015_configuration.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/hmc8015_configuration.h"

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
        : _cnt_functions(0), _functions(nullptr), _log_to_usb(false),
        _timeout(5000) { }


/*
 * PWROWG_NAMESPACE::hmc8015_configuration::hmc8015_configuration
 */
PWROWG_NAMESPACE::hmc8015_configuration::hmc8015_configuration(
        _In_ const hmc8015_configuration& rhs) noexcept
        : _functions(nullptr) {
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
    detail::safe_assign(this->_log_file, path);
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
 * PWROWG_NAMESPACE::hmc8015_configuration::operator =
 */
PWROWG_NAMESPACE::hmc8015_configuration&
PWROWG_NAMESPACE::hmc8015_configuration::operator =(
        _In_ const hmc8015_configuration& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        this->functions(rhs._functions, rhs._cnt_functions);
        this->_log_file = rhs._log_file;
        this->_log_to_usb = rhs._log_to_usb;
        this->_timeout = rhs._timeout;
    }

    return *this;
}
