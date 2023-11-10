// <copyright file="oscilloscope_trigger.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/oscilloscope_trigger.h"

#include <cassert>
#include <regex>
#include <stdexcept>
#include <string>
#include <utility>

#include "power_overwhelming/convert_string.h"

#include "string_functions.h"


/*
 * visus::power_overwhelming::oscilloscope_trigger::edge
 */
visus::power_overwhelming::oscilloscope_trigger
visus::power_overwhelming::oscilloscope_trigger::edge(
        _In_z_ const wchar_t *source) {
    return oscilloscope_trigger(source, L"EDGE");
}


/*
 * visus::power_overwhelming::oscilloscope_trigger::edge
 */
visus::power_overwhelming::oscilloscope_trigger
visus::power_overwhelming::oscilloscope_trigger::edge(
        _In_z_ const char *source) {
    return oscilloscope_trigger(source, "EDGE");
}


/*
 * visus::power_overwhelming::oscilloscope_trigger::edge
 */
visus::power_overwhelming::oscilloscope_trigger
visus::power_overwhelming::oscilloscope_trigger::edge(
        _In_ const input_type source) {
    const auto s = std::string("CH") + std::to_string(source);
    return oscilloscope_trigger(s.c_str(), "EDGE");
}


/*
 * visus::power_overwhelming::oscilloscope_trigger::oscilloscope_trigger
 */
visus::power_overwhelming::oscilloscope_trigger::oscilloscope_trigger(
        _In_z_ const wchar_t *source, _In_z_ const wchar_t *type)
    : _coupling(oscilloscope_trigger_coupling::direct_current),
        _hysteresis(oscilloscope_trigger_hysteresis::automatic),
        _input(0),
        _mode(oscilloscope_trigger_mode::automatic),
        _slope(oscilloscope_trigger_slope::rising) {
    this->source(source);
    this->type(type);
}


/*
 * visus::power_overwhelming::oscilloscope_trigger::oscilloscope_trigger
 */
visus::power_overwhelming::oscilloscope_trigger::oscilloscope_trigger(
        _In_z_ const char *source, _In_z_ const char *type)
    : _coupling(oscilloscope_trigger_coupling::direct_current),
        _hysteresis(oscilloscope_trigger_hysteresis::automatic),
        _input(0),
        _mode(oscilloscope_trigger_mode::automatic),
        _slope(oscilloscope_trigger_slope::rising) {
    this->source(source);
    this->type(type);
}


/*
 * visus::power_overwhelming::oscilloscope_trigger::oscilloscope_trigger
 */
visus::power_overwhelming::oscilloscope_trigger::oscilloscope_trigger(
        _In_ const input_type source, _In_z_ const wchar_t *type)
    : _coupling(oscilloscope_trigger_coupling::direct_current),
        _hysteresis(oscilloscope_trigger_hysteresis::automatic),
        _input(source),
        _mode(oscilloscope_trigger_mode::automatic),
        _slope(oscilloscope_trigger_slope::rising) {
    const auto s = std::string("CH") + std::to_string(source);
    this->source(s.c_str());
    this->type(type);
}


/*
 * visus::power_overwhelming::oscilloscope_trigger::external
 */
visus::power_overwhelming::oscilloscope_trigger&
visus::power_overwhelming::oscilloscope_trigger::external(
        _In_ const oscilloscope_quantity& level,
        _In_ const oscilloscope_trigger_slope slope) {
    this->level(5, level)
        .slope(slope)
        .source("EXT");
    return *this;
}


/*
 * visus::power_overwhelming::oscilloscope_trigger::external
 */
visus::power_overwhelming::oscilloscope_trigger&
visus::power_overwhelming::oscilloscope_trigger::external(
        _In_ const float level,
        _In_ const oscilloscope_trigger_slope slope) {
    return this->external(oscilloscope_quantity(level, "V"), slope);
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

    auto s = convert_string<char>(source);
    return this->source(s.c_str());
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
 * visus::power_overwhelming::oscilloscope_trigger::type
 */
visus::power_overwhelming::oscilloscope_trigger&
visus::power_overwhelming::oscilloscope_trigger::type(_In_z_ const wchar_t *type) {
    if (type == nullptr) {
        throw std::invalid_argument("The trigger type must not be null.");
    }

    detail::safe_assign(this->_type, convert_string<char>(type));
    return *this;
}


/*
 * visus::power_overwhelming::oscilloscope_trigger::type
 */
visus::power_overwhelming::oscilloscope_trigger&
visus::power_overwhelming::oscilloscope_trigger::type(_In_z_ const char *type) {
    if (type == nullptr) {
        throw std::invalid_argument("The trigger type must not be null.");
    }

    detail::safe_assign(this->_type, type);
    return *this;
}
