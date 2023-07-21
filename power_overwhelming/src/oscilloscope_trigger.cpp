// <copyright file="oscilloscope_trigger.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/oscilloscope_trigger.h"

#include <stdexcept>

#include "power_overwhelming/convert_string.h"

#include "string_functions.h"


/*
 * visus::power_overwhelming::oscilloscope_trigger::~oscilloscope_trigger
 */
visus::power_overwhelming::oscilloscope_trigger::~oscilloscope_trigger(void) {
    detail::safe_assign(this->_hold_off, nullptr);
    detail::safe_assign(this->_source, nullptr);
}


/*
 * visus::power_overwhelming::oscilloscope_trigger::hold_off
 */
visus::power_overwhelming::oscilloscope_trigger&
visus::power_overwhelming::oscilloscope_trigger::hold_off(
        _In_opt_z_ const wchar_t *hold_off) {
    detail::safe_assign(this->_hold_off, convert_string<char>(hold_off));
    return *this;
}


/*
 * visus::power_overwhelming::oscilloscope_trigger::hold_off
 */
visus::power_overwhelming::oscilloscope_trigger&
visus::power_overwhelming::oscilloscope_trigger::hold_off(
        _In_opt_z_ const char *hold_off) {
    detail::safe_assign(this->_hold_off, hold_off);
    return *this;
}


/*
 * visus::power_overwhelming::oscilloscope_trigger::hold_off
 */
visus::power_overwhelming::oscilloscope_trigger&
visus::power_overwhelming::oscilloscope_trigger::hold_off(
        _In_opt_z_ const std::nullptr_t n) {
    detail::safe_assign(this->_hold_off, nullptr);
    return *this;
}


/*
 * visus::power_overwhelming::oscilloscope_trigger::mode
 */
visus::power_overwhelming::oscilloscope_trigger&
visus::power_overwhelming::oscilloscope_trigger::mode(
        _In_ const oscilloscope_trigger_mode mode) noexcept {
    this->_mode = mode;
    return *this;
}


/*
 * visus::power_overwhelming::oscilloscope_trigger::source
 */
visus::power_overwhelming::oscilloscope_trigger&
visus::power_overwhelming::oscilloscope_trigger::source(
        _In_z_ const wchar_t *source) {
    if (source == nullptr) {
        throw std::invalid_argument("The trigger source must not be null.");
    }

    detail::safe_assign(this->_source, convert_string<char>(source));
    return *this;
}


/*
 * visus::power_overwhelming::oscilloscope_trigger::source
 */
visus::power_overwhelming::oscilloscope_trigger&
visus::power_overwhelming::oscilloscope_trigger::source(
        _In_z_ const char *source) {
    if (source == nullptr) {
        throw std::invalid_argument("The trigger source must not be null.");
    }

    detail::safe_assign(this->_source, source);
    return *this;
}


/*
 * visus::power_overwhelming::oscilloscope_trigger::oscilloscope_trigger
 */
visus::power_overwhelming::oscilloscope_trigger::oscilloscope_trigger(
        _In_z_ const char *source)
    : _hold_off(nullptr), _mode(oscilloscope_trigger_mode::normal),
        _source(nullptr) {
    try {
        this->source(source);
    } catch (...) {
        // This is for safety reasons in case someone adds possible additional
        // points of failure (exceptions) above.
        this->~oscilloscope_trigger();
        throw;
    }
}


/*
 * visus::power_overwhelming::oscilloscope_trigger::oscilloscope_trigger
 */
visus::power_overwhelming::oscilloscope_trigger::oscilloscope_trigger(
        _In_ const oscilloscope_trigger& rhs)
        : _hold_off(nullptr), _mode(rhs._mode), _source(nullptr) {
    try {
        detail::safe_assign(this->_hold_off, rhs._hold_off);
        detail::safe_assign(this->_source, rhs._source);
    } catch (...) {
        // This is important as there are multiple potential failed allocations
        // possible in the code above.
        this->~oscilloscope_trigger();
        throw;
    }
}


/*
 * visus::power_overwhelming::oscilloscope_trigger::oscilloscope_trigger
 */
visus::power_overwhelming::oscilloscope_trigger::oscilloscope_trigger(
        _Inout_ oscilloscope_trigger&& rhs) noexcept
    : _hold_off(rhs._hold_off), _mode(rhs._mode),
        _source(rhs._source) {
    rhs._hold_off = nullptr;
    rhs._mode = oscilloscope_trigger_mode::normal;
    rhs._source = nullptr;
}


/*
 * visus::power_overwhelming::oscilloscope_trigger::operator =
 */
visus::power_overwhelming::oscilloscope_trigger&
visus::power_overwhelming::oscilloscope_trigger::operator =(
        _In_ const oscilloscope_trigger& rhs) {
    if (this != std::addressof(rhs)) {
        detail::safe_assign(this->_hold_off, rhs._hold_off);
        this->_mode = rhs._mode;
        detail::safe_assign(this->_source, rhs._source);
    }

    return *this;
}


/*
 * visus::power_overwhelming::oscilloscope_trigger::operator =
 */
visus::power_overwhelming::oscilloscope_trigger&
visus::power_overwhelming::oscilloscope_trigger::operator =(
        _Inout_ oscilloscope_trigger&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        detail::safe_assign(this->_hold_off, std::move(rhs._hold_off));
        this->_mode = rhs._mode;
        rhs._mode = oscilloscope_trigger_mode::normal;
        detail::safe_assign(this->_source, std::move(rhs._source));

    }

    return *this;
}
