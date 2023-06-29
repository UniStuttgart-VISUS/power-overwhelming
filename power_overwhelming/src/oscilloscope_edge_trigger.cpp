// <copyright file="oscilloscope_edge_trigger.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/oscilloscope_edge_trigger.h"

#include <cassert>
#include <stdexcept>
#include <string>
#include <utility>

#include "power_overwhelming/convert_string.h"

#include "string_functions.h"


/*
 * ...::power_overwhelming::oscilloscope_edge_trigger::oscilloscope_edge_trigger
 */
visus::power_overwhelming::oscilloscope_edge_trigger::oscilloscope_edge_trigger(
        _In_ const char *source)
    : oscilloscope_trigger(source),
        _coupling(oscilloscope_trigger_coupling::direct_current),
        _hysteresis(oscilloscope_trigger_hysteresis::automatic),
        _input(0),
        _level_unit(nullptr),
        _level_value(0),
        _slope(oscilloscope_trigger_slope::rising) { }


/*
 * ...::power_overwhelming::oscilloscope_edge_trigger::oscilloscope_edge_trigger
 */
visus::power_overwhelming::oscilloscope_edge_trigger::oscilloscope_edge_trigger(
        _In_ const oscilloscope_edge_trigger& rhs)
    : oscilloscope_trigger(rhs),
        _coupling(rhs._coupling),
        _hysteresis(rhs._hysteresis),
        _input(rhs._input),
        _level_unit(nullptr),
        _level_value(rhs._level_value),
        _slope(rhs._slope) {
    try {
        detail::safe_assign(this->_level_unit, rhs._level_unit);
    } catch (...) {
        this->~oscilloscope_edge_trigger();
        throw;
    }
}


/*
 * ...::power_overwhelming::oscilloscope_edge_trigger::oscilloscope_edge_trigger
 */
visus::power_overwhelming::oscilloscope_edge_trigger::oscilloscope_edge_trigger(
        _Inout_ oscilloscope_edge_trigger&& rhs) noexcept
    : oscilloscope_trigger(std::move(rhs)), _coupling(rhs._coupling),
        _hysteresis(rhs._hysteresis), _input(rhs._input),
        _level_unit(rhs._level_unit), _level_value(rhs._level_value),
        _slope(rhs._slope) {
    rhs._coupling = oscilloscope_trigger_coupling::direct_current;
    rhs._hysteresis = oscilloscope_trigger_hysteresis::automatic;
    rhs._input = 0;
    rhs._level_unit = nullptr;
    rhs._level_value = 0.0f;
}


/*
 * ...::oscilloscope_edge_trigger::~oscilloscope_edge_trigger
 */
visus::power_overwhelming::oscilloscope_edge_trigger::~oscilloscope_edge_trigger(
        void) {
    detail::safe_assign(this->_level_unit, nullptr);
}


/*
 * visus::power_overwhelming::oscilloscope_edge_trigger::level
 */
visus::power_overwhelming::oscilloscope_edge_trigger&
visus::power_overwhelming::oscilloscope_edge_trigger::level(
        _In_ const input_type input, _In_ const float value,
        _In_z_ const wchar_t *unit) {
    if (unit == nullptr) {
        throw std::invalid_argument("A valid unit must be proided for the "
            "trigger level.");
    }

    this->_input = input;
    detail::safe_assign(this->_level_unit, convert_string<char>(unit));
    this->_level_value = value;

    return *this;
}


/*
 * visus::power_overwhelming::oscilloscope_edge_trigger::level
 */
visus::power_overwhelming::oscilloscope_edge_trigger&
visus::power_overwhelming::oscilloscope_edge_trigger::level(
        _In_ const input_type input, _In_ const float value,
        _In_z_ const char *unit) {
    this->_input = input;
    detail::safe_assign(this->_level_unit, (unit != nullptr) ? unit : "");
    this->_level_value = value;
    return *this;
}


/*
 * visus::power_overwhelming::oscilloscope_edge_trigger::type
 */
_Ret_z_ const char *visus::power_overwhelming::oscilloscope_edge_trigger::type(
        void) const noexcept {
    return "EDGE";
}


/*
 * visus::power_overwhelming::oscilloscope_edge_trigger::operator =
 */
visus::power_overwhelming::oscilloscope_edge_trigger&
visus::power_overwhelming::oscilloscope_edge_trigger::operator =(
        _In_ const oscilloscope_edge_trigger& rhs) {
    if (this != std::addressof(rhs)) {
        oscilloscope_trigger::operator =(rhs);

        this->_coupling = rhs._coupling;
        this->_hysteresis = rhs._hysteresis;
        detail::safe_assign(this->_level_unit, rhs._level_unit);
        this->_level_value = rhs._level_value;
        this->_slope = rhs._slope;
    }

    return *this;
}


/*
 * visus::power_overwhelming::oscilloscope_edge_trigger::operator =
 */
visus::power_overwhelming::oscilloscope_edge_trigger&
visus::power_overwhelming::oscilloscope_edge_trigger::operator =(
        _Inout_ oscilloscope_edge_trigger&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        oscilloscope_trigger::operator =(std::move(rhs));
        this->_coupling = rhs._coupling;
        rhs._coupling = oscilloscope_trigger_coupling::direct_current;

        this->_hysteresis = rhs._hysteresis;
        rhs._hysteresis = oscilloscope_trigger_hysteresis::automatic;

        detail::safe_assign(this->_level_unit, rhs._level_unit);
        assert(rhs._level_unit == nullptr);

        this->_level_value = rhs._level_value;
        rhs._level_value = 0.0f;

        this->_slope = rhs._slope;
        rhs._slope = oscilloscope_trigger_slope::rising;
    }

    return *this;
}
