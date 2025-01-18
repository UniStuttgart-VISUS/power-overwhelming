// <copyright file="oscilloscope_quantity.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/oscilloscope_quantity.h"

#include <memory>

#include "visus/pwrowg/convert_string.h"

#include "string_functions.h"


/*
 * visus::power_overwhelming::oscilloscope_quantity::oscilloscope_quantity
 */
visus::power_overwhelming::oscilloscope_quantity::oscilloscope_quantity(
        _In_ const float value, _In_opt_z_ const wchar_t *unit) 
        : _unit(nullptr), _value(value) {
    const auto u = convert_string<char>(unit);
    detail::safe_assign(this->_unit, u);
}


/*
 * visus::power_overwhelming::oscilloscope_quantity::oscilloscope_quantity
 */
visus::power_overwhelming::oscilloscope_quantity::oscilloscope_quantity(
        _In_ const float value, _In_opt_z_ const char *unit)
        : _unit(nullptr), _value(value) {
    detail::safe_assign(this->_unit, unit);
}


/*
 * visus::power_overwhelming::oscilloscope_quantity::~oscilloscope_quantity
 */
visus::power_overwhelming::oscilloscope_quantity::~oscilloscope_quantity(void) {
    detail::safe_assign(this->_unit, nullptr);
}


/*
 * visus::power_overwhelming::oscilloscope_quantity::oscilloscope_quantity
 */
visus::power_overwhelming::oscilloscope_quantity::oscilloscope_quantity(
        _In_ const oscilloscope_quantity& rhs)
        : _unit(nullptr), _value(rhs._value) {
    detail::safe_assign(this->_unit, rhs._unit);
}


/*
 * visus::power_overwhelming::oscilloscope_quantity::oscilloscope_quantity
 */
visus::power_overwhelming::oscilloscope_quantity::oscilloscope_quantity(
        _Inout_ oscilloscope_quantity&& rhs) noexcept
        :_unit(rhs._unit), _value(rhs._value) {
    rhs._unit = nullptr;
    rhs._value = 0.0f;
}


/*
 * visus::power_overwhelming::oscilloscope_quantity::unit
 */
_Ret_z_ const char *visus::power_overwhelming::oscilloscope_quantity::unit(
        void) const noexcept {
    return (this->_unit != nullptr) ? this->_unit : "";
}


/*
 * visus::power_overwhelming::oscilloscope_quantity::operator =
 */
visus::power_overwhelming::oscilloscope_quantity&
visus::power_overwhelming::oscilloscope_quantity::operator =(
        _In_ const oscilloscope_quantity& rhs) {
    if (this != std::addressof(rhs)) {
        detail::safe_assign(this->_unit, rhs._unit);
        this->_value = rhs._value;
    }

    return *this;
}


/*
 * visus::power_overwhelming::oscilloscope_quantity::operator =
 */
visus::power_overwhelming::oscilloscope_quantity&
visus::power_overwhelming::oscilloscope_quantity::operator =(
        _Inout_ oscilloscope_quantity&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        detail::safe_assign(this->_unit, std::move(rhs._unit));
        this->_value = rhs._value;
        rhs._value = 0.0f;
    }

    return *this;
}
