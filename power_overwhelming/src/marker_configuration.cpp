// <copyright file="marker_configuration.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/marker_configuration.h"

#include <stdexcept>

#include "visus/pwrowg/multi_sz.h"


/*
 * PWROWG_NAMESPACE::marker_configuration::id
 */
const PWROWG_NAMESPACE::guid PWROWG_NAMESPACE::marker_configuration::id(
    0x8555E9C5, 0x5EEA, 0x42BD, 0xB0E3, 0x89, 0x8B, 0x75, 0xAF, 0x2F, 0x75);


/*
 * PWROWG_NAMESPACE::marker_configuration::~marker_configuration
 */
PWROWG_NAMESPACE::marker_configuration::~marker_configuration(void) noexcept {
    delete[] this->_names;
}


/*
 * PWROWG_NAMESPACE::marker_configuration::size
 */
std::size_t PWROWG_NAMESPACE::marker_configuration::size(void) const noexcept {
    return multi_sz<wchar_t>::count(this->_names);
}


/*
 * PWROWG_NAMESPACE::marker_configuration::operator =
 */
PWROWG_NAMESPACE::marker_configuration&
PWROWG_NAMESPACE::marker_configuration::operator =(
        _In_ const marker_configuration& rhs) {
    if (this != std::addressof(rhs)) {
        const auto len = multi_sz<wchar_t>::size(rhs._names);

        delete[] this->_names;

        if (len > 0) {
            this->_names = new wchar_t[len];
            ::memcpy(this->_names, rhs._names, len * sizeof(wchar_t));
        } else {
            this->_names = nullptr;
        }
    }

    return *this;
}


/*
 * PWROWG_NAMESPACE::marker_configuration::operator =
 */
PWROWG_NAMESPACE::marker_configuration&
PWROWG_NAMESPACE::marker_configuration::operator =(
        _Inout_ marker_configuration&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        delete[] this->_names;
        this->_names = rhs._names;
        rhs._names = nullptr;
    }

    return *this;
}


/*
 * PWROWG_NAMESPACE::marker_configuration::operator []
 */
_Ret_maybenull_z_ const wchar_t *
PWROWG_NAMESPACE::marker_configuration::operator [](
        _In_ const int index) const noexcept {
    return multi_sz<wchar_t>::at(this->_names, index);
}


/*
 * PWROWG_NAMESPACE::marker_configuration::operator +=
 */
int PWROWG_NAMESPACE::marker_configuration::operator +=(
        _In_z_ const wchar_t *name) {
    if (name == nullptr) {
        throw std::invalid_argument("A marker must have a valid name.");
    }

    auto names = multi_sz<wchar_t>::add(this->_names, name);
    delete[] this->_names;
    this->_names = names;

    return static_cast<int>(multi_sz<wchar_t>::count(this->_names)) - 1;
}
