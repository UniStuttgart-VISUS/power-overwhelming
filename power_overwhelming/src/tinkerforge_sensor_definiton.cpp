// <copyright file="tinkerforge_sensor_definiton.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/tinkerforge_sensor_definiton.h"

#include <cstring>
#include <memory>
#include <stdexcept>


/*
 * ...::tinkerforge_sensor_definiton::tinkerforge_sensor_definiton
 */
visus::power_overwhelming::tinkerforge_sensor_definiton::tinkerforge_sensor_definiton(
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
 * ...::tinkerforge_sensor_definiton::tinkerforge_sensor_definiton
 */
visus::power_overwhelming::tinkerforge_sensor_definiton::tinkerforge_sensor_definiton(
        const tinkerforge_sensor_definiton& rhs)
        : _description(nullptr), _uid(nullptr) {
    *this = rhs;
}


/*
 * ...::tinkerforge_sensor_definiton::~tinkerforge_sensor_definiton
 */
visus::power_overwhelming::tinkerforge_sensor_definiton::~tinkerforge_sensor_definiton(
        void) {
    if (this->_description != nullptr) {
        ::free(this->_description);
    }
    if (this->_uid != nullptr) {
        ::free(this->_uid);
    }
}


/*
 * visus::power_overwhelming::tinkerforge_sensor_definiton::description
 */
void visus::power_overwhelming::tinkerforge_sensor_definiton::description(
        const wchar_t *description) {
    if (this->_description != nullptr) {
        ::free(this->_description);
    }

    if (description != nullptr) {
        this->_description = ::_wcsdup(description);
        if (this->_description == nullptr) {
            throw std::bad_alloc();
        }

    } else {
        this->_description = nullptr;
    }
}


/*
 * visus::power_overwhelming::tinkerforge_sensor_definiton::operator =
 */
visus::power_overwhelming::tinkerforge_sensor_definiton&
visus::power_overwhelming::tinkerforge_sensor_definiton::operator =(
        const tinkerforge_sensor_definiton& rhs) {
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
 * visus::power_overwhelming::tinkerforge_sensor_definiton::operator =
 */
visus::power_overwhelming::tinkerforge_sensor_definiton&
visus::power_overwhelming::tinkerforge_sensor_definiton::operator =(
        tinkerforge_sensor_definiton&& rhs) noexcept {
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
