// <copyright file="tinkerforge_sensor_definition.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/tinkerforge_sensor_definition.h"

#include <cstring>
#include <memory>
#include <stdexcept>


/*
 * ...::tinkerforge_sensor_definition::tinkerforge_sensor_definition
 */
visus::power_overwhelming::tinkerforge_sensor_definition::tinkerforge_sensor_definition(
        const char *uid) : _description(nullptr), _uid(nullptr) {
    if (uid == nullptr) {
        throw std::invalid_argument("The UID of a Tinkerforge sensor cannot "
            "be null.");
    }

    this->_uid = ::strdup(uid);
    if (this->_uid == nullptr) {
        throw std::bad_alloc();
    }
}


/*
 * ...::tinkerforge_sensor_definition::tinkerforge_sensor_definition
 */
visus::power_overwhelming::tinkerforge_sensor_definition::tinkerforge_sensor_definition(
        const tinkerforge_sensor_definition& rhs)
        : _description(nullptr), _uid(nullptr) {
    *this = rhs;
}


/*
 * ...::tinkerforge_sensor_definition::~tinkerforge_sensor_definition
 */
visus::power_overwhelming::tinkerforge_sensor_definition::~tinkerforge_sensor_definition(
        void) {
    if (this->_description != nullptr) {
        ::free(this->_description);
    }
    if (this->_uid != nullptr) {
        ::free(this->_uid);
    }
}


/*
 * visus::power_overwhelming::tinkerforge_sensor_definition::description
 */
void visus::power_overwhelming::tinkerforge_sensor_definition::description(
        const wchar_t *description) {
    if (this->_description != nullptr) {
        ::free(this->_description);
    }

    if (description != nullptr) {
        this->_description = ::wcsdup(description);
        if (this->_description == nullptr) {
            throw std::bad_alloc();
        }

    } else {
        this->_description = nullptr;
    }
}


/*
 * visus::power_overwhelming::tinkerforge_sensor_definition::operator =
 */
visus::power_overwhelming::tinkerforge_sensor_definition&
visus::power_overwhelming::tinkerforge_sensor_definition::operator =(
        const tinkerforge_sensor_definition& rhs) {
    if (this != std::addressof(rhs)) {
        this->description(rhs._description);

        if (this->_uid != nullptr) {
            ::free(this->_uid);
        }

        if (rhs._uid != nullptr) {
            this->_uid = ::strdup(rhs._uid);
            if (this->_uid == nullptr) {
                throw std::bad_alloc();
            }

        } else {
            this->_uid = nullptr;
        }
    }

    return *this;
}


/*
 * visus::power_overwhelming::tinkerforge_sensor_definition::operator =
 */
visus::power_overwhelming::tinkerforge_sensor_definition&
visus::power_overwhelming::tinkerforge_sensor_definition::operator =(
        tinkerforge_sensor_definition&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        if (this->_description != nullptr) {
            ::free(this->_description);
        }

        this->_description = rhs._description;
        rhs._description = nullptr;

        if (this->_uid != nullptr) {
            ::free(this->_uid);
        }

        this->_uid = rhs._uid;
        rhs._uid = nullptr;
    }

    return *this;
}
