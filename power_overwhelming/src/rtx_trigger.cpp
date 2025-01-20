// <copyright file="rtx_trigger.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/rtx_trigger.h"

#include <cassert>
#include <regex>
#include <stdexcept>
#include <string>
#include <utility>

#include "visus/pwrowg/convert_string.h"

#include "string_functions.h"


/*
 * PWROWG_NAMESPACE::rtx_trigger::edge
 */
PWROWG_NAMESPACE::rtx_trigger PWROWG_NAMESPACE::rtx_trigger::edge(
        _In_z_ const wchar_t *source) {
    return rtx_trigger(source, L"EDGE");
}


/*
 * PWROWG_NAMESPACE::rtx_trigger::edge
 */
PWROWG_NAMESPACE::rtx_trigger PWROWG_NAMESPACE::rtx_trigger::edge(
        _In_z_ const char *source) {
    return rtx_trigger(source, "EDGE");
}


/*
 * PWROWG_NAMESPACE::rtx_trigger::edge
 */
PWROWG_NAMESPACE::rtx_trigger PWROWG_NAMESPACE::rtx_trigger::edge(
        _In_ const input_type source) {
    const auto s = std::string("CH") + std::to_string(source);
    return rtx_trigger(s.c_str(), "EDGE");
}


/*
 * PWROWG_NAMESPACE::rtx_trigger::rtx_trigger
 */
PWROWG_NAMESPACE::rtx_trigger::rtx_trigger(
        _In_z_ const wchar_t *source, _In_z_ const wchar_t *type)
    : _coupling(rtx_trigger_coupling::direct_current),
        _hysteresis(rtx_trigger_hysteresis::automatic),
        _input(0),
        _mode(rtx_trigger_mode::automatic),
        _slope(rtx_trigger_slope::rising) {
    this->source(source);
    this->type(type);
}


/*
 * PWROWG_NAMESPACE::rtx_trigger::rtx_trigger
 */
PWROWG_NAMESPACE::rtx_trigger::rtx_trigger(
        _In_z_ const char *source, _In_z_ const char *type)
    : _coupling(rtx_trigger_coupling::direct_current),
        _hysteresis(rtx_trigger_hysteresis::automatic),
        _input(0),
        _mode(rtx_trigger_mode::automatic),
        _slope(rtx_trigger_slope::rising) {
    this->source(source);
    this->type(type);
}


/*
 * PWROWG_NAMESPACE::rtx_trigger::rtx_trigger
 */
PWROWG_NAMESPACE::rtx_trigger::rtx_trigger(
        _In_ const input_type source, _In_z_ const wchar_t *type)
    : _coupling(rtx_trigger_coupling::direct_current),
        _hysteresis(rtx_trigger_hysteresis::automatic),
        _input(source),
        _mode(rtx_trigger_mode::automatic),
        _slope(rtx_trigger_slope::rising) {
    const auto s = std::string("CH") + std::to_string(source);
    this->source(s.c_str());
    this->type(type);
}


/*
 * PWROWG_NAMESPACE::rtx_trigger::external
 */
PWROWG_NAMESPACE::rtx_trigger& PWROWG_NAMESPACE::rtx_trigger::external(
        _In_ const rtx_quantity& level,
        _In_ const rtx_trigger_slope slope) {
    this->level(5, level)
        .slope(slope)
        .source("EXT");
    return *this;
}


/*
 * PWROWG_NAMESPACE::rtx_trigger::external
 */
PWROWG_NAMESPACE::rtx_trigger& PWROWG_NAMESPACE::rtx_trigger::external(
        _In_ const float level,
        _In_ const rtx_trigger_slope slope) {
    return this->external(rtx_quantity(level, "V"), slope);
}


/*
 * PWROWG_NAMESPACE::rtx_trigger::hold_off
 */
PWROWG_NAMESPACE::rtx_trigger& PWROWG_NAMESPACE::rtx_trigger::hold_off(
        _In_opt_z_ const wchar_t *hold_off) {
    detail::safe_assign(this->_hold_off, convert_string<char>(hold_off));
    return *this;
}


/*
 * PWROWG_NAMESPACE::rtx_trigger::hold_off
 */
PWROWG_NAMESPACE::rtx_trigger& PWROWG_NAMESPACE::rtx_trigger::hold_off(
        _In_opt_z_ const char *hold_off) {
    detail::safe_assign(this->_hold_off, hold_off);
    return *this;
}


/*
 * PWROWG_NAMESPACE::rtx_trigger::hold_off
 */
PWROWG_NAMESPACE::rtx_trigger& PWROWG_NAMESPACE::rtx_trigger::hold_off(
        _In_opt_z_ const std::nullptr_t n) {
    detail::safe_assign(this->_hold_off, static_cast<char *>(nullptr));
    return *this;
}


/*
 * PWROWG_NAMESPACE::rtx_trigger::mode
 */
PWROWG_NAMESPACE::rtx_trigger& PWROWG_NAMESPACE::rtx_trigger::mode(
        _In_ const rtx_trigger_mode mode) noexcept {
    this->_mode = mode;
    return *this;
}


/*
 * PWROWG_NAMESPACE::rtx_trigger::source
 */
PWROWG_NAMESPACE::rtx_trigger& PWROWG_NAMESPACE::rtx_trigger::source(
        _In_z_ const wchar_t *source) {
    if (source == nullptr) {
        throw std::invalid_argument("The trigger source must not be null.");
    }

    auto s = convert_string<char>(source);
    return this->source(s.c_str());
}


/*
 * PWROWG_NAMESPACE::rtx_trigger::source
 */
PWROWG_NAMESPACE::rtx_trigger& PWROWG_NAMESPACE::rtx_trigger::source(
    _In_z_ const char *source) {
    if (source == nullptr) {
        throw std::invalid_argument("The trigger source must not be null.");
    }

    detail::safe_assign(this->_source, source);

    {
        std::cmatch match;
        std::string query;
        std::regex rx("^ch(\\d+)$", std::regex_constants::ECMAScript
            | std::regex_constants::icase);

        if (std::regex_match(this->_source.as<char>(), match, rx)) {
            auto c = match[1].str();
            this->_input = ::atoi(c.c_str());

        } else if (detail::equals(this->_source.as<char>(), "EXT", true)) {
            this->_input = 5;
        }
    }

    return *this;
}


/*
 * PWROWG_NAMESPACE::rtx_trigger::type
 */
PWROWG_NAMESPACE::rtx_trigger& PWROWG_NAMESPACE::rtx_trigger::type(
        _In_z_ const wchar_t *type) {
    if (type == nullptr) {
        throw std::invalid_argument("The trigger type must not be null.");
    }

    detail::safe_assign(this->_type, convert_string<char>(type));
    return *this;
}


/*
 * PWROWG_NAMESPACE::rtx_trigger::type
 */
PWROWG_NAMESPACE::rtx_trigger& PWROWG_NAMESPACE::rtx_trigger::type(
        _In_z_ const char *type) {
    if (type == nullptr) {
        throw std::invalid_argument("The trigger type must not be null.");
    }

    detail::safe_assign(this->_type, type);
    return *this;
}
