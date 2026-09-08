// <copyright file="pwog_file.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for more information.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/pwog_file.h"

#include <algorithm>
#include <cassert>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <utility>

#include "io_util.h"


/*
 * PWROWG_NAMESPACE::pwog_file::create
 */
PWROWG_NAMESPACE::pwog_file PWROWG_NAMESPACE::pwog_file::create(
        _In_z_ const wchar_t *path,
        _In_ const bool force) {
    pwog_file retval;

#if defined(_WIN32)
    retval._handle = detail::open(path, GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ, force ? CREATE_ALWAYS : CREATE_NEW);
#else /* defined(_WIN32) */
    retval._handle = detail::open(path, O_RDWR | O_CREAT
        | (force ? O_TRUNC : O_EXCL), S_IRWXU);
#endif /* defined(_WIN32) */

    retval.write_fourcc();
    retval.write_version();

    return retval;
}


/*
 * PWROWG_NAMESPACE::pwog_file::create
 */
PWROWG_NAMESPACE::pwog_file PWROWG_NAMESPACE::pwog_file::create(
        _In_z_ const char *path,
        _In_ const bool force) {
    pwog_file retval;

#if defined(_WIN32)
    retval._handle = detail::open(path, GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ, force ? CREATE_ALWAYS : CREATE_NEW);
#else /* defined(_WIN32) */
    retval._handle = detail::open(path, O_RDWR | O_CREAT
        | (force ? O_TRUNC : O_EXCL), S_IRWXU);
#endif /* defined(_WIN32) */

    retval.write_fourcc();
    retval.write_version();

    return retval;
}


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
    retval._handle = detail::open(path, O_RDONLY);
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
    retval._handle = detail::open(path, O_RDONLY);
#endif /* defined(_WIN32) */

    retval.check_fourcc();
    retval.check_version();

    return retval;
}


/*
 * PWROWG_NAMESPACE::pwog_file::pwog_file
 */
PWROWG_NAMESPACE::pwog_file::pwog_file(void) noexcept
    : _handle(invalid), _swap(false), _version { 1, 0 } { }


/*
 * PWROWG_NAMESPACE::pwog_file::pwog_file
 */
PWROWG_NAMESPACE::pwog_file::pwog_file(_Inout_ pwog_file&& rhs) noexcept
        : _handle(rhs._handle), _swap(rhs._swap) {
    rhs._handle = invalid;
    std::copy(std::begin(rhs._version),
        std::end(rhs._version),
        std::begin(this->_version));
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
        std::copy(std::begin(rhs._version),
            std::end(rhs._version),
            std::begin(this->_version));
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


/*
 * PWROWG_NAMESPACE::pwog_file::write_fourcc
 */
void PWROWG_NAMESPACE::pwog_file::write_fourcc(void) {
    assert(!this->_swap);   // We can always write our native format.
    detail::write_all_bytes(this->_handle, &fourcc, sizeof(fourcc));
}


/*
 * PWROWG_NAMESPACE::pwog_file::write_version
 */
void PWROWG_NAMESPACE::pwog_file::write_version(void) {
    assert(this->_version[0] == 1);
    assert(this->_version[1] == 0);
    detail::write_all_bytes(this->_handle, this->_version,
        sizeof(this->_version));
}
