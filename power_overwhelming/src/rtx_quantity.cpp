// <copyright file="rtx_quantity.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/rtx_quantity.h"

#include <memory>

#include "visus/pwrowg/convert_string.h"

#include "string_functions.h"


/*
 * PWROWG_NAMESPACE::rtx_quantity::rtx_quantity
 */
PWROWG_NAMESPACE::rtx_quantity::rtx_quantity(
        _In_ const float value, _In_opt_z_ const wchar_t *unit) 
        : _unit(nullptr), _value(value) {
    const auto u = convert_string<char>(unit);
    detail::safe_assign(this->_unit, u);
}


/*
 * PWROWG_NAMESPACE::rtx_quantity::rtx_quantity
 */
PWROWG_NAMESPACE::rtx_quantity::rtx_quantity(
        _In_ const float value, _In_opt_z_ const char *unit)
        : _unit(nullptr), _value(value) {
    detail::safe_assign(this->_unit, unit);
}


/*
 * PWROWG_NAMESPACE::rtx_quantity::~rtx_quantity
 */
PWROWG_NAMESPACE::rtx_quantity::~rtx_quantity(void) {
    detail::safe_assign(this->_unit, nullptr);
}


/*
 * PWROWG_NAMESPACE::rtx_quantity::rtx_quantity
 */
PWROWG_NAMESPACE::rtx_quantity::rtx_quantity(
        _In_ const rtx_quantity& rhs)
        : _unit(nullptr), _value(rhs._value) {
    detail::safe_assign(this->_unit, rhs._unit);
}


/*
 * PWROWG_NAMESPACE::rtx_quantity::rtx_quantity
 */
PWROWG_NAMESPACE::rtx_quantity::rtx_quantity(
        _Inout_ rtx_quantity&& rhs) noexcept
        :_unit(rhs._unit), _value(rhs._value) {
    rhs._unit = nullptr;
    rhs._value = 0.0f;
}


/*
 * PWROWG_NAMESPACE::rtx_quantity::unit
 */
_Ret_z_ const char *PWROWG_NAMESPACE::rtx_quantity::unit(void) const noexcept {
    return (this->_unit != nullptr) ? this->_unit : "";
}


/*
 * PWROWG_NAMESPACE::rtx_quantity::operator =
 */
PWROWG_NAMESPACE::rtx_quantity&
PWROWG_NAMESPACE::rtx_quantity::operator =(_In_ const rtx_quantity& rhs) {
    if (this != std::addressof(rhs)) {
        detail::safe_assign(this->_unit, rhs._unit);
        this->_value = rhs._value;
    }

    return *this;
}


/*
 * PWROWG_NAMESPACE::rtx_quantity::operator =
 */
PWROWG_NAMESPACE::rtx_quantity&
PWROWG_NAMESPACE::rtx_quantity::operator =(
        _Inout_ rtx_quantity&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        detail::safe_assign(this->_unit, std::move(rhs._unit));
        this->_value = rhs._value;
        rhs._value = 0.0f;
    }

    return *this;
}
