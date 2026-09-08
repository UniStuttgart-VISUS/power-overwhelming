// <copyright file="pwog_file.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for more information.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/pwog_file.h"

#include <cassert>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <utility>

#include "io_util.h"


/*
 * PWROWG_NAMESPACE::pwog_file::read
 */
PWROWG_NAMESPACE::pwog_file PWROWG_NAMESPACE::pwog_file::read(
        _In_z_ const wchar_t *path) {
    pwog_file retval;

#if defined(_WIN32)
    retval._handle = detail::open(path, GENERIC_READ, FILE_SHARE_READ,
        OPEN_EXISTING);
#else /* defined(_WIN32) */
    retval._handle = detail::open(path, O_RDONLY | O_BINARY);
#endif /* defined(_WIN32) */

    retval.check_fourcc();
    retval.check_version();

    return retval;
}


/*
 * PWROWG_NAMESPACE::pwog_file::read
 */
PWROWG_NAMESPACE::pwog_file PWROWG_NAMESPACE::pwog_file::read(
        _In_z_ const char *path) {
    pwog_file retval;

#if defined(_WIN32)
    retval._handle = detail::open(path, GENERIC_READ, FILE_SHARE_READ,
        OPEN_EXISTING);
#else /* defined(_WIN32) */
    retval._handle = detail::open(path, O_RDONLY | O_BINARY);
#endif /* defined(_WIN32) */

    retval.check_fourcc();
    retval.check_version();

    return retval;
}


/*
 * PWROWG_NAMESPACE::pwog_file::pwog_file
 */
PWROWG_NAMESPACE::pwog_file::pwog_file(void) noexcept
    : _handle(invalid), _swap(false) { }


/*
 * PWROWG_NAMESPACE::pwog_file::pwog_file
 */
PWROWG_NAMESPACE::pwog_file::pwog_file(_Inout_ pwog_file&& rhs) noexcept
        : _handle(rhs._handle), _swap(rhs._swap) {
    rhs._handle = invalid;
}


/*
 * PWROWG_NAMESPACE::pwog_file::close
 */
void PWROWG_NAMESPACE::pwog_file::close(void) noexcept {
    if (*this) {
#if defined(_WIN32)
        ::CloseHandle(this->_handle);
#else /* defined(_WIN32) */
        ::close(this->_handle);
#endif /* defined(_WIN32) */
        this->_handle = invalid;
    }
}


/*
 * PWROWG_NAMESPACE::pwog_file::operator =
 */
PWROWG_NAMESPACE::pwog_file& PWROWG_NAMESPACE::pwog_file::operator =(
        _Inout_ pwog_file&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        this->close();
        assert(!*this);
        std::swap(this->_handle, rhs._handle);
        assert(!rhs);
        this->_swap = rhs._swap;
    }

    return *this;
}


/*
 * PWROWG_NAMESPACE::pwog_file::check_fourcc
 */
void PWROWG_NAMESPACE::pwog_file::check_fourcc(void) {
    std::decay_t<decltype(fourcc)> actual = 0;
    detail::read_bytes(this->_handle, &actual, sizeof(actual));

    if (actual != fourcc) {
        // If we did not find the expected FOURCC, it could be that the byte
        // order is reversed. We check that next and, in case of success, we
        // remember that we need to swap the byte order when reading.
        auto b = reinterpret_cast<std::uint8_t *>(&actual);
        auto e = b + sizeof(actual);
        std::reverse(b, e);

        if (actual != fourcc) {
            throw std::invalid_argument("The specified file does not start "
                "with the expected FOURCC.");
        }

        this->_swap = true;
    }
}


/*
 * PWROWG_NAMESPACE::pwog_file::check_version
 */
void PWROWG_NAMESPACE::pwog_file::check_version(void) {
    detail::read_bytes(this->_handle, this->_version, sizeof(this->_version));
    if ((this->_version[0] != 1) || (this->_version[1] != 0)) {
        throw std::invalid_argument("The specified file has a version that the "
            "reader does not understand.");
    }
}
