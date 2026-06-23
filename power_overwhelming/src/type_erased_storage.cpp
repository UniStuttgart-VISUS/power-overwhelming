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
    : _cp(nullptr), _dtor(nullptr), _state(state::empty) {
    assert(!*this);
}


/*
 * PWROWG_NAMESPACE::type_erased_storage::type_erased_storage
 */
PWROWG_NAMESPACE::type_erased_storage::type_erased_storage(
        _In_ const type_erased_storage& rhs)
        : _cp(rhs._cp), _dtor(rhs._dtor), _state(state::empty) {
    if (rhs._state != state::empty) {
        this->_cp(this->_data, rhs._data);
        this->_state = rhs._state;
    }
}


/*
 * PWROWG_NAMESPACE::type_erased_storage::type_erased_storage
 */
PWROWG_NAMESPACE::type_erased_storage::type_erased_storage(
        _Inout_ type_erased_storage&& rhs) noexcept
        : _cp(rhs._cp), _data(rhs._data), _dtor(rhs._dtor), _state(rhs._state) {
    rhs._cp = nullptr;
#if (defined(_DEBUG) || defined(_DEBUG))
    ::memset(&rhs._data, 0xD0, sizeof(rhs._data));
#endif /* (defined(_DEBUG) || defined(_DEBUG)) */
    rhs._dtor = nullptr;
    rhs._state = state::empty;
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
    if (this->_state != state::empty) {
        assert(this->_dtor != nullptr);
        this->_dtor(this->_data);
        this->_cp = nullptr;
        this->_dtor = nullptr;
        this->_state = state::empty;
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
        assert(!*this);

        if (rhs._state != state::empty) {
            this->_cp = rhs._cp;
            this->_dtor = rhs._dtor;
            this->_cp(this->_data, rhs._data);
            this->_state = rhs._state;
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
        assert(!*this);
        this->_cp = rhs._cp;
        rhs._cp = nullptr;
        this->_data = rhs._data;
#if (defined(_DEBUG) || defined(_DEBUG))
        ::memset(&rhs._data, 0xD0, sizeof(rhs._data));
#endif /* (defined(_DEBUG) || defined(_DEBUG)) */
        this->_dtor = rhs._dtor;
        rhs._dtor = nullptr;
        this->_state = rhs._state;
        rhs._state = state::empty;
        assert(!rhs);
    }

    return *this;
}
