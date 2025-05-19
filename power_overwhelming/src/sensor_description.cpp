// <copyright file="sensor_description.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/sensor_description.h"

#include <type_traits>

#include "visus/pwrowg/convert_string.h"

#include "string_functions.h"


/*
 * PWROWG_NAMESPACE::sensor_description::sensor_description
 */
PWROWG_NAMESPACE::sensor_description::sensor_description(void) noexcept
    : _editable_type(sensor_type::unknown),
    _reading_type(reading_type::floating_point),
    _reading_unit(reading_unit::unknown),
    _sensor_type(sensor_type::unknown) { }


/*
 * PWROWG_NAMESPACE::sensor_description::label
 */
PWROWG_NAMESPACE::sensor_description&
PWROWG_NAMESPACE::sensor_description::label(_In_opt_z_ const wchar_t *label) {
    PWROWG_DETAIL_NAMESPACE::safe_assign(this->_label, label);
    return *this;
}


/*
 * PWROWG_NAMESPACE::sensor_description::label
 */
PWROWG_NAMESPACE::sensor_description&
PWROWG_NAMESPACE::sensor_description::label(_In_opt_z_ const char *label) {
    auto l = convert_string<wchar_t>(label);
    PWROWG_DETAIL_NAMESPACE::safe_assign(this->_label, l);
    return *this;
}


/*
 * PWROWG_NAMESPACE::sensor_description::sensor_type
 */
PWROWG_NAMESPACE::sensor_description&
PWROWG_NAMESPACE::sensor_description::sensor_type(
        _In_ const PWROWG_NAMESPACE::sensor_type type) noexcept {
    typedef typename std::decay<decltype(type)>::type enum_type;
    typedef typename std::underlying_type<enum_type>::type mask_type;

    // Erase all bits that the user cannot set from the input.
    const auto i = static_cast<mask_type>(type)
        & static_cast<mask_type>(this->_editable_type);

    // Erase all editable bits in the type.
    auto t = static_cast<mask_type>(this->_sensor_type);
    t &= ~static_cast<mask_type>(this->_editable_type);

    // Replace the editable bits with the input.
    this->_sensor_type = static_cast<enum_type>(t | i);

    return *this;
}
