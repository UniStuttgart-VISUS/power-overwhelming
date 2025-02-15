// <copyright file="type_erased_storage.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/type_erased_storage.h"


/*
 * PWROWG_NAMESPACE::type_erased_storage::type_erased_storage
 */
PWROWG_NAMESPACE::type_erased_storage::type_erased_storage(void) noexcept
    : _cp(nullptr), _data(nullptr), _dtor(nullptr) {
    assert(!*this);
}


/*
 * PWROWG_NAMESPACE::type_erased_storage::type_erased_storage
 */
PWROWG_NAMESPACE::type_erased_storage::type_erased_storage(
        _In_ const type_erased_storage& rhs)
        : _cp(rhs._cp), _data(nullptr), _dtor(rhs._dtor) {
    if (this->_cp != nullptr) {
        this->_cp(this->_data, rhs._data);

    } else if (rhs._data != nullptr) {
        throw std::logic_error("The object contained in a type-erased storage "
            "block is not copyable.");
    }
}


/*
 * PWROWG_NAMESPACE::type_erased_storage::~type_erased_storage
 */
PWROWG_NAMESPACE::type_erased_storage::~type_erased_storage(void) noexcept {
    this->reset();
}


/*
 * PWROWG_NAMESPACE::type_erased_storage::reset
 */
void PWROWG_NAMESPACE::type_erased_storage::reset(void) noexcept {
    if (this->_dtor != nullptr) {
        this->_dtor(this->_data);
        this->_cp = nullptr;
        this->_data = nullptr;
        this->_dtor = nullptr;
    }
    assert(!*this);
}


/*
 * PWROWG_NAMESPACE::type_erased_storage::operator =
 */
PWROWG_NAMESPACE::type_erased_storage&
PWROWG_NAMESPACE::type_erased_storage::operator =(
        _In_ const type_erased_storage& rhs) {
    if (this != std::addressof(rhs)) {
        // As we do not know whether the type stored here and the type we are
        // going to assign are the same, we first need to destruct any existing
        // data before we can assign the input.
        this->reset();

        // Copy the operations next, which will ensure that we only copy stuff
        // that is copyable.
        this->_cp = rhs._cp;
        this->_dtor = rhs._dtor;

        if (this->_cp != nullptr) {
            this->_cp(this->_data, rhs._data);

        } else if (rhs._data != nullptr) {
            this->_cp = nullptr;
            this->_dtor = nullptr;
            throw std::logic_error("The object contained in a type-erased "
                "storage block is not copyable.");
        }
    }

    return *this;
}


/*
 * PWROWG_NAMESPACE::type_erased_storage::operator =
 */
PWROWG_NAMESPACE::type_erased_storage &
PWROWG_NAMESPACE::type_erased_storage::operator =(
        _Inout_ type_erased_storage&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        this->reset();
        this->_cp = rhs._cp;
        rhs._cp = nullptr;
        this->_data = rhs._data;
        rhs._data = nullptr;
        this->_dtor = rhs._dtor;
        rhs._dtor = nullptr;
    }

    return *this;
}
