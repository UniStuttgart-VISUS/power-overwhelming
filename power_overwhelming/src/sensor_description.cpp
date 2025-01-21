// <copyright file="sensor_description.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/sensor_description.h"

#include "visus/pwrowg/convert_string.h"

#include "string_functions.h"


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
