// <copyright file="tinkerforge_sensor_definition.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2023 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/tinkerforge_sensor_definition.h"

#include <stdexcept>

#include "string_functions.h"


/*
 * ...::tinkerforge_sensor_definition::tinkerforge_sensor_definition
 */
visus::power_overwhelming::tinkerforge_sensor_definition::tinkerforge_sensor_definition(
        _In_z_ const char *uid) : _description(nullptr), _uid(nullptr) {
    if (uid == nullptr) {
        throw std::invalid_argument("The UID of a Tinkerforge sensor cannot "
            "be null.");
    }

    // Note: This may throw, so it must be the only allocation here.
    detail::safe_assign(this->_uid, uid);
}


/*
 * ...::tinkerforge_sensor_definition::tinkerforge_sensor_definition
 */
visus::power_overwhelming::tinkerforge_sensor_definition::tinkerforge_sensor_definition(
        _In_ const tinkerforge_sensor_definition& rhs)
        : _description(nullptr), _uid(nullptr) {
    try {
        *this = rhs;
    } catch (...) {
        this->~tinkerforge_sensor_definition();
        throw;
    }
}


/*
 * ...::tinkerforge_sensor_definition::~tinkerforge_sensor_definition
 */
visus::power_overwhelming::tinkerforge_sensor_definition::~tinkerforge_sensor_definition(
        void) {
    detail::safe_assign(this->_description, nullptr);
    detail::safe_assign(this->_uid, nullptr);
}


/*
 * visus::power_overwhelming::tinkerforge_sensor_definition::description
 */
void visus::power_overwhelming::tinkerforge_sensor_definition::description(
        _In_opt_z_ const wchar_t *description) {
    detail::safe_assign(this->_description, description);
}


/*
 * visus::power_overwhelming::tinkerforge_sensor_definition::operator =
 */
visus::power_overwhelming::tinkerforge_sensor_definition&
visus::power_overwhelming::tinkerforge_sensor_definition::operator =(
        _In_ const tinkerforge_sensor_definition& rhs) {
    if (this != std::addressof(rhs)) {
        detail::safe_assign(this->_description, rhs._description);
        detail::safe_assign(this->_uid, rhs._uid);
    }

    return *this;
}


/*
 * visus::power_overwhelming::tinkerforge_sensor_definition::operator =
 */
visus::power_overwhelming::tinkerforge_sensor_definition&
visus::power_overwhelming::tinkerforge_sensor_definition::operator =(
        _In_ tinkerforge_sensor_definition&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        detail::safe_assign(this->_description, std::move(rhs._description));
        assert(rhs._description == nullptr);
        detail::safe_assign(this->_uid, std::move(rhs._uid));
        assert(rhs._uid == nullptr);
    }

    return *this;
}
