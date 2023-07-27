// <copyright file="oscilloscope_trigger.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/oscilloscope_trigger.h"

#include <stdexcept>

#include "power_overwhelming/convert_string.h"

#include "string_functions.h"


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
    detail::safe_assign(this->_hold_off, static_cast<char *>(nullptr));
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
        : _mode(oscilloscope_trigger_mode::normal) {
    this->source(source);
}
