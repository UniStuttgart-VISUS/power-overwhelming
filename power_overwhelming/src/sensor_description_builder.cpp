// <copyright file="sensor_description_builder.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "sensor_description_builder.h"

#include <stdexcept>

#include "visus/pwrowg/convert_string.h"

#include "string_functions.h"


/*
 * PWROWG_DETAIL_NAMESPACE::sensor_description_builder::measured_in
 */
PWROWG_DETAIL_NAMESPACE::sensor_description_builder&
PWROWG_DETAIL_NAMESPACE::sensor_description_builder::measured_in(
        _In_ const reading_unit unit) noexcept {
    this->_desc._reading_unit = unit;
    return *this;
}


/*
 * PWROWG_DETAIL_NAMESPACE::sensor_description_builder::produces
 */
PWROWG_DETAIL_NAMESPACE::sensor_description_builder&
PWROWG_DETAIL_NAMESPACE::sensor_description_builder::produces(
        _In_ const reading_type type) noexcept {
    this->_desc._reading_type = type;
    return *this;
}


/*
 * PWROWG_DETAIL_NAMESPACE::sensor_description_builder::with_editable_type
 */
PWROWG_DETAIL_NAMESPACE::sensor_description_builder&
PWROWG_DETAIL_NAMESPACE::sensor_description_builder::with_editable_type(
        _In_ const sensor_type type) noexcept {
    this->_desc._editable_type = type;
    return *this;
}


/*
 * PWROWG_DETAIL_NAMESPACE::sensor_description_builder::with_id
 */
PWROWG_DETAIL_NAMESPACE::sensor_description_builder&
PWROWG_DETAIL_NAMESPACE::sensor_description_builder::with_id(
        _In_z_ const wchar_t *id) {
    if (id == nullptr) {
        throw std::invalid_argument("A valid sensor ID must be provided.");
    }

    safe_assign(this->_desc._id, id);
    return *this;
}


/*
 * PWROWG_DETAIL_NAMESPACE::sensor_description_builder::with_id
 */
PWROWG_DETAIL_NAMESPACE::sensor_description_builder&
PWROWG_DETAIL_NAMESPACE::sensor_description_builder::with_id(
        _In_z_ const char *id) {
    if (id == nullptr) {
        throw std::invalid_argument("A valid sensor ID must be provided.");
    }

    safe_assign(this->_desc._id, PWROWG_NAMESPACE::convert_string<wchar_t>(id));
    return *this;
}


/*
 * PWROWG_DETAIL_NAMESPACE::sensor_description_builder::with_label
 */
PWROWG_DETAIL_NAMESPACE::sensor_description_builder&
PWROWG_DETAIL_NAMESPACE::sensor_description_builder::with_label(
        _In_opt_z_ const wchar_t *label) {
    safe_assign(this->_desc._label, label);
    return *this;
}


/*
 * PWROWG_DETAIL_NAMESPACE::sensor_description_builder::with_name
 */
PWROWG_DETAIL_NAMESPACE::sensor_description_builder&
PWROWG_DETAIL_NAMESPACE::sensor_description_builder::with_name(
        _In_z_ const wchar_t *name) {
    if (name == nullptr) {
        throw std::invalid_argument("A valid sensor name must be provided.");
    }

    safe_assign(this->_desc._name, name);
    return *this;
}


/*
 * PWROWG_DETAIL_NAMESPACE::sensor_description_builder::with_name
 */
PWROWG_DETAIL_NAMESPACE::sensor_description_builder&
PWROWG_DETAIL_NAMESPACE::sensor_description_builder::with_name(
        _In_z_ const char *name) {
    if (name == nullptr) {
        throw std::invalid_argument("A valid sensor name must be provided.");
    }

    safe_assign(this->_desc._name,
        PWROWG_NAMESPACE::convert_string<wchar_t>(name));
    return *this;
}

/*
 * PWROWG_DETAIL_NAMESPACE::sensor_description_builder::with_path
 */
PWROWG_DETAIL_NAMESPACE::sensor_description_builder&
PWROWG_DETAIL_NAMESPACE::sensor_description_builder::with_path(
        _In_z_ const wchar_t *path) {
    if (path == nullptr) {
        throw std::invalid_argument("A valid sensor path must be provided.");
    }

    safe_assign(this->_desc._path, path);
    return *this;
}


/*
 * PWROWG_DETAIL_NAMESPACE::sensor_description_builder::with_path
 */
PWROWG_DETAIL_NAMESPACE::sensor_description_builder&
PWROWG_DETAIL_NAMESPACE::sensor_description_builder::with_path(
        _In_z_ const char *path) {
    if (path == nullptr) {
        throw std::invalid_argument("A valid sensor path must be provided.");
    }

    safe_assign(this->_desc._path,
        PWROWG_NAMESPACE::convert_string<wchar_t>(path));
    return *this;
}


/*
 * PWROWG_DETAIL_NAMESPACE::sensor_description_builder::with_type
 */
PWROWG_DETAIL_NAMESPACE::sensor_description_builder&
PWROWG_DETAIL_NAMESPACE::sensor_description_builder::with_type(
        _In_ const sensor_type type) noexcept {
    this->_desc._sensor_type = type;
    return *this;
}


/*
 * PWROWG_DETAIL_NAMESPACE::sensor_description_builder::with_vendor
 */
PWROWG_DETAIL_NAMESPACE::sensor_description_builder&
PWROWG_DETAIL_NAMESPACE::sensor_description_builder::with_vendor(
        _In_opt_z_ const wchar_t *vendor) {
    safe_assign(this->_desc._vendor, vendor);
    return *this;
}
