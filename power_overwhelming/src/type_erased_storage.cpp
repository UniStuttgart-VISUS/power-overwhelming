// <copyright file="type_erased_storage.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/type_erased_storage.h"

#include <memory>


/*
 * PWROWG_NAMESPACE::type_erased_storage::type_erased_storage
 */
PWROWG_NAMESPACE::type_erased_storage::type_erased_storage(void) noexcept
        : _cp(nullptr), _cp_ctor(nullptr), _dtor(nullptr), _mv(nullptr),
        _mv_ctor(nullptr) { }


/*
 * PWROWG_NAMESPACE::type_erased_storage::type_erased_storage
 */
PWROWG_NAMESPACE::type_erased_storage::type_erased_storage(
        _In_ const type_erased_storage& rhs)
    : _cp(rhs._cp), _cp_ctor(rhs._cp_ctor), _dtor(rhs._dtor), _mv(rhs._mv),
        _mv_ctor(rhs._mv_ctor) {
    this->_data.resize(rhs._data.size());

    if (!this->_data.empty()) {
        this->_cp_ctor(this->_data, rhs._data);
    }
}


/*
 * PWROWG_NAMESPACE::type_erased_storage::type_erased_storage
 */
PWROWG_NAMESPACE::type_erased_storage::type_erased_storage(
        _Inout_ type_erased_storage&& rhs) noexcept
    : _cp(rhs._cp), _cp_ctor(rhs._cp_ctor), _data(std::move(rhs._data)),
        _dtor(rhs._dtor), _mv(rhs._mv), _mv_ctor(rhs._mv_ctor) {
    rhs._cp = nullptr;
    rhs._cp_ctor = nullptr;
    rhs._dtor = nullptr;
    rhs._mv = nullptr;
    rhs._mv_ctor = nullptr;
}


/*
 * PWROWG_NAMESPACE::type_erased_storage::~type_erased_storage
 */
PWROWG_NAMESPACE::type_erased_storage::~type_erased_storage(void) noexcept {
    this->clear();
}


/*
 * PWROWG_NAMESPACE::type_erased_storage::operator =
 */
PWROWG_NAMESPACE::type_erased_storage&
PWROWG_NAMESPACE::type_erased_storage::operator =(
        _In_ const type_erased_storage& rhs) {
    //if (this != std::addressof(rhs)) {
    //    // As we do not know whether the type stored here and the type we are
    //    // going to assign are the same, we first need to destruct any existing
    //    // data before we can assign the input.
    //    this->clear();

    //    // Make sure that we have enough space.
    //    this->_data.resize(rhs._data.size());

    //    // If the input is non-empty, assign it.
    //    if (!this->_data.empty()) {
    //        this->_operations.copy(this->_data, rhs._data);
    //    }
    //}
    throw "TODO";

    return *this;
}


/*
 * PWROWG_NAMESPACE::type_erased_storage::operator =
 */
PWROWG_NAMESPACE::type_erased_storage&
PWROWG_NAMESPACE::type_erased_storage::operator =(
        _Inout_ type_erased_storage&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        // As we do not know whether we are assigning to the same type, we must
        // make sure that the destination (our data) has been properly cleaned
        // before we overwrite it.
        this->clear();

        // Move everything, and most importantly, make sure that the dtor on the
        // source side is erased such our data is not destructed by the source.
        this->_data = std::move(rhs._data);

        this->_cp = rhs._cp;
        rhs._cp = nullptr;

        this->_cp_ctor = rhs._cp_ctor;
        rhs._cp_ctor = nullptr;

        this->_dtor = rhs._dtor;
        rhs._dtor = nullptr;

        this->_mv = rhs._mv;
        rhs._mv = nullptr;

        this->_mv_ctor = rhs._mv_ctor;
        rhs._mv_ctor = nullptr;
    }

    return *this;
}


/*
 * PWROWG_NAMESPACE::type_erased_storage::clear
 */
void PWROWG_NAMESPACE::type_erased_storage::clear(void) noexcept {
    auto d = static_cast<void *>(this->_data);

    if ((d != nullptr) && (this->_dtor != nullptr)) {
        this->_dtor(d);
        this->_dtor = nullptr;
    }
}
