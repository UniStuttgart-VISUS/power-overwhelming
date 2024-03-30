// <copyright file="blob.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/blob.h"

#include <cassert>
#include <cstring>
#include <memory>


/*
 * visus::power_overwhelming::blob::blob
 */
visus::power_overwhelming::blob::blob(_In_ const blob& rhs)
        : _data(nullptr), _size(rhs._size) {
    if (rhs._data != nullptr) {
        this->_data = new byte_type[this->_size];
        ::memcpy(this->_data, rhs._data, this->_size);
    }

    assert((this->_data != nullptr) || (this->_size == 0));
}


/*
 * visus::power_overwhelming::blob::blob
 */
visus::power_overwhelming::blob::blob(_Inout_ blob&& rhs) noexcept
        : _data(rhs._data), _size(rhs._size) {
    rhs._data = nullptr;
    rhs._size = 0;
    assert(rhs._data == nullptr);
    assert(rhs._size == 0);
}


/*
 * visus::power_overwhelming::blob::~blob
 */
visus::power_overwhelming::blob::~blob(void) {
    delete[] this->_data;
}


/*
 * visus::power_overwhelming::blob::at
 */
_Ret_maybenull_ void *visus::power_overwhelming::blob::at(
        _In_ const std::size_t offset) noexcept {
    assert((this->_data != nullptr) || (this->_size == 0));
    return (offset < this->_size)
        ? this->_data + offset
        : nullptr;
}


/*
 * visus::power_overwhelming::blob::at
 */
_Ret_maybenull_ const void *visus::power_overwhelming::blob::at(
        _In_ const std::size_t offset) const noexcept {
    assert((this->_data != nullptr) || (this->_size == 0));
    return (offset < this->_size)
        ? this->_data + offset
        : nullptr;
}


/*
 * visus::power_overwhelming::blob::clear
 */
void visus::power_overwhelming::blob::clear(void) {
    delete[] this->_data;
    this->_data = nullptr;
    this->_size = 0;
}


/*
 * visus::power_overwhelming::blob::end
 */
_Ret_maybenull_ visus::power_overwhelming::blob::byte_type *
visus::power_overwhelming::blob::end(void) noexcept {
    return (this->_data != nullptr)
        ? reinterpret_cast<byte_type *>(this->_data) + this->_size
        : nullptr;
}


/*
 * visus::power_overwhelming::blob::end
 */
_Ret_maybenull_ const visus::power_overwhelming::blob::byte_type *
visus::power_overwhelming::blob::end(void) const noexcept {
    return (this->_data != nullptr)
        ? reinterpret_cast<const byte_type *>(this->_data) + this->_size
        : nullptr;
}


/*
 * visus::power_overwhelming::blob::grow
 */
bool visus::power_overwhelming::blob::grow(_In_ const std::size_t size) {
    const auto retval = (size > this->_size);

    if (retval) {
        const auto existing = this->_data;
        this->_data = new byte_type[size];

        if (existing != nullptr) {
            ::memcpy(this->_data, existing, this->_size);
            delete[] existing;
            this->_size = size;
        }
    }

    return retval;
}


/*
 * visus::power_overwhelming::blob::rbegin
 */
_Ret_maybenull_ visus::power_overwhelming::blob::byte_type *
visus::power_overwhelming::blob::rbegin(void) noexcept {
    return ((this->_data != nullptr) && (this->_size > 0))
        ? reinterpret_cast<byte_type *>(this->_data) + this->_size - 1
        : nullptr;
}


/*
 * visus::power_overwhelming::blob::rbegin
 */
_Ret_maybenull_ const visus::power_overwhelming::blob::byte_type *
visus::power_overwhelming::blob::rbegin(void) const noexcept {
    return ((this->_data != nullptr) && (this->_size > 0))
        ? reinterpret_cast<const byte_type *>(this->_data) + this->_size - 1
        : nullptr;
}


/*
 * visus::power_overwhelming::blob::rend
 */
_Ret_maybenull_ visus::power_overwhelming::blob::byte_type *
visus::power_overwhelming::blob::rend(void) noexcept {
    return (this->_data != nullptr)
        ? this->_data - 1
        : nullptr;
}


/*
 * visus::power_overwhelming::blob::rend
 */
_Ret_maybenull_ const visus::power_overwhelming::blob::byte_type *
visus::power_overwhelming::blob::rend(void) const noexcept {
    return (this->_data != nullptr)
        ? this->_data - 1
        : nullptr;
}


/*
 * visus::power_overwhelming::blob::reserve
 */
bool visus::power_overwhelming::blob::reserve(_In_ const std::size_t size) {
    const auto retval = (size > this->_size);

    if (retval) {
        delete[] this->_data;
        this->_size = size;
        this->_data = new byte_type[this->_size];
    }

    return retval;
}


/*
 * visus::power_overwhelming::blob::resize
 */
void visus::power_overwhelming::blob::resize(_In_ const std::size_t size) {
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
 * visus::power_overwhelming::blob::truncate
 */
void visus::power_overwhelming::blob::truncate(_In_ const std::size_t size) {
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
 * visus::power_overwhelming::blob::operator =
 */
visus::power_overwhelming::blob& visus::power_overwhelming::blob::operator =(
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
 * visus::power_overwhelming::blob::operator =
 */
visus::power_overwhelming::blob& visus::power_overwhelming::blob::operator =(
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