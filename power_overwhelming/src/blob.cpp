// <copyright file="blob.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/blob.h"

#include <cassert>
#include <cstring>
#include <memory>


/*
 * PWROWG_NAMESPACE::blob::blob
 */
PWROWG_NAMESPACE::blob::blob(_In_ const blob& rhs)
        : _data(nullptr), _size(rhs._size) {
    if (rhs._data != nullptr) {
        this->_data = new byte_type[this->_size];
        ::memcpy(this->_data, rhs._data, this->_size);
    }

    assert((this->_data != nullptr) || (this->_size == 0));
}


/*
 * PWROWG_NAMESPACE::blob::blob
 */
PWROWG_NAMESPACE::blob::blob(_Inout_ blob&& rhs) noexcept
        : _data(rhs._data), _size(rhs._size) {
    rhs._data = nullptr;
    rhs._size = 0;
    assert(rhs._data == nullptr);
    assert(rhs._size == 0);
}


/*
 * PWROWG_NAMESPACE::blob::~blob
 */
PWROWG_NAMESPACE::blob::~blob(void) {
    delete[] this->_data;
}


/*
 * PWROWG_NAMESPACE::blob::at
 */
_Ret_maybenull_ void *PWROWG_NAMESPACE::blob::at(
        _In_ const std::size_t offset) noexcept {
    assert((this->_data != nullptr) || (this->_size == 0));
    return (offset < this->_size)
        ? this->_data + offset
        : nullptr;
}


/*
 * PWROWG_NAMESPACE::blob::at
 */
_Ret_maybenull_ const void *PWROWG_NAMESPACE::blob::at(
        _In_ const std::size_t offset) const noexcept {
    assert((this->_data != nullptr) || (this->_size == 0));
    return (offset < this->_size)
        ? this->_data + offset
        : nullptr;
}


/*
 * PWROWG_NAMESPACE::blob::clear
 */
void PWROWG_NAMESPACE::blob::clear(void) {
    delete[] this->_data;
    this->_data = nullptr;
    this->_size = 0;
}


/*
 * PWROWG_NAMESPACE::blob::end
 */
_Ret_maybenull_ PWROWG_NAMESPACE::blob::byte_type *
PWROWG_NAMESPACE::blob::end(void) noexcept {
    return (this->_data != nullptr)
        ? reinterpret_cast<byte_type *>(this->_data) + this->_size
        : nullptr;
}


/*
 * PWROWG_NAMESPACE::blob::end
 */
_Ret_maybenull_ const PWROWG_NAMESPACE::blob::byte_type *
PWROWG_NAMESPACE::blob::end(void) const noexcept {
    return (this->_data != nullptr)
        ? reinterpret_cast<const byte_type *>(this->_data) + this->_size
        : nullptr;
}


/*
 * PWROWG_NAMESPACE::blob::grow
 */
bool PWROWG_NAMESPACE::blob::grow(_In_ const std::size_t size) {
    const auto retval = (size > this->_size);

    if (retval) {
        const auto existing = this->_data;
        this->_data = new byte_type[size];

        if (existing != nullptr) {
            ::memcpy(this->_data, existing, this->_size);
            delete[] existing;
        }

        this->_size = size;
    }

    return retval;
}


/*
 * PWROWG_NAMESPACE::blob::rbegin
 */
_Ret_maybenull_ PWROWG_NAMESPACE::blob::byte_type *
PWROWG_NAMESPACE::blob::rbegin(void) noexcept {
    return ((this->_data != nullptr) && (this->_size > 0))
        ? reinterpret_cast<byte_type *>(this->_data) + this->_size - 1
        : nullptr;
}


/*
 * PWROWG_NAMESPACE::blob::rbegin
 */
_Ret_maybenull_ const PWROWG_NAMESPACE::blob::byte_type *
PWROWG_NAMESPACE::blob::rbegin(void) const noexcept {
    return ((this->_data != nullptr) && (this->_size > 0))
        ? reinterpret_cast<const byte_type *>(this->_data) + this->_size - 1
        : nullptr;
}


/*
 * PWROWG_NAMESPACE::blob::rend
 */
_Ret_maybenull_ PWROWG_NAMESPACE::blob::byte_type *
PWROWG_NAMESPACE::blob::rend(void) noexcept {
    return (this->_data != nullptr)
        ? this->_data - 1
        : nullptr;
}


/*
 * PWROWG_NAMESPACE::blob::rend
 */
_Ret_maybenull_ const PWROWG_NAMESPACE::blob::byte_type *
PWROWG_NAMESPACE::blob::rend(void) const noexcept {
    return (this->_data != nullptr)
        ? this->_data - 1
        : nullptr;
}


/*
 * PWROWG_NAMESPACE::blob::reserve
 */
bool PWROWG_NAMESPACE::blob::reserve(_In_ const std::size_t size) {
    const auto retval = (size > this->_size);

    if (retval) {
        delete[] this->_data;
        this->_size = size;
        this->_data = new byte_type[this->_size];
    }

    return retval;
}


/*
 * PWROWG_NAMESPACE::blob::resize
 */
void PWROWG_NAMESPACE::blob::resize(_In_ const std::size_t size) {
    if (this->_size != size) {
        delete[] this->_data;
        this->_size = size;

        if (this->_size > 0) {
            this->_data = new byte_type[this->_size];
        } else {
            this->_data = nullptr;
        }
    }
}


/*
 * PWROWG_NAMESPACE::blob::truncate
 */
void PWROWG_NAMESPACE::blob::truncate(_In_ const std::size_t size) {
    if (this->_size != size) {
        const auto existing = this->_data;

        if (size > 0) {
            this->_data = new byte_type[size];
        } else {
            this->_data = nullptr;
        }

        if ((this->_data != nullptr) && (existing != nullptr)) {
            ::memcpy(this->_data, existing, (std::min)(this->_size, size));
        }

        delete[] existing;
        this->_size = size;
    }
}


/*
 * PWROWG_NAMESPACE::blob::operator =
 */
PWROWG_NAMESPACE::blob& PWROWG_NAMESPACE::blob::operator =(
        _In_ const blob& rhs) {
    if (this != std::addressof(rhs)) {
        if ((this->_data != nullptr) && (this->_size != rhs._size)) {
            delete[] this->_data;
            this->_data = nullptr;
        }

        this->_size = rhs._size;
        if ((this->_data == nullptr) && (rhs._data != nullptr)) {
            this->_data = new byte_type[this->_size];
        }

        if (this->_data != nullptr) {
            assert(rhs._data != nullptr);
            ::memcpy(this->_data, rhs._data, this->_size);
        }
    }

    assert((this->_data != nullptr) || (rhs._data == nullptr));
    assert((this->_data != nullptr) || (this->_size == 0));
    assert(this->_size == rhs._size);
    return *this;
}


/*
 * PWROWG_NAMESPACE::blob::operator =
 */
PWROWG_NAMESPACE::blob& PWROWG_NAMESPACE::blob::operator =(
        _Inout_ blob&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        this->_data = rhs._data;
        rhs._data = nullptr;
        this->_size = rhs._size;
        rhs._size = 0;
    }

    assert(rhs._data == nullptr);
    assert(rhs._size == 0);
    return *this;
}