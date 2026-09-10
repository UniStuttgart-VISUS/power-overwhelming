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
    retval.initialise(detail::open(path, GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ, force ? CREATE_ALWAYS : CREATE_NEW),
        state::header);
#else /* defined(_WIN32) */
    retval.initialise(detail::open(path, O_RDWR | O_CREAT
        | (force ? O_TRUNC : O_EXCL), S_IRWXU),
        state::header);
#endif /* defined(_WIN32) */

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
    retval.initialise(detail::open(path, GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ, force ? CREATE_ALWAYS : CREATE_NEW),
        state::header);
#else /* defined(_WIN32) */
    retval.initialise(detail::open(path, O_RDWR | O_CREAT
        | (force ? O_TRUNC : O_EXCL), S_IRWXU),
        state::header);
#endif /* defined(_WIN32) */

    return retval;
}


/*
 * PWROWG_NAMESPACE::pwog_file::read
 */
PWROWG_NAMESPACE::pwog_file PWROWG_NAMESPACE::pwog_file::read(
        _In_z_ const wchar_t *path) {
    pwog_file retval;

#if defined(_WIN32)
    retval.initialise(
        detail::open(path, GENERIC_READ, FILE_SHARE_READ, OPEN_EXISTING),
        state::read);
#else /* defined(_WIN32) */
    retval.initialise(detail::open(path, O_RDONLY), state::read);
#endif /* defined(_WIN32) */

    return retval;
}


/*
 * PWROWG_NAMESPACE::pwog_file::read
 */
PWROWG_NAMESPACE::pwog_file PWROWG_NAMESPACE::pwog_file::read(
        _In_z_ const char *path) {
    pwog_file retval;

#if defined(_WIN32)
    retval.initialise(
        detail::open(path, GENERIC_READ, FILE_SHARE_READ, OPEN_EXISTING),
        state::read);
#else /* defined(_WIN32) */
    retval.initialise(detail::open(path, O_RDONLY), state::read);
#endif /* defined(_WIN32) */

    return retval;
}


/*
 * PWROWG_NAMESPACE::pwog_file::pwog_file
 */
PWROWG_NAMESPACE::pwog_file::pwog_file(void) noexcept
    : _handle(invalid), _state(state::read), _swap(false), _version { 1, 0 } { }


/*
 * PWROWG_NAMESPACE::pwog_file::pwog_file
 */
PWROWG_NAMESPACE::pwog_file::pwog_file(_Inout_ pwog_file&& rhs) noexcept
        : _handle(rhs._handle), _state(rhs._state), _swap(rhs._swap) {
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
        this->_state = rhs._state;
        this->_swap = rhs._swap;
        std::copy(std::begin(rhs._version),
            std::end(rhs._version),
            std::begin(this->_version));
    }

    return *this;
}


/*
 * PWROWG_NAMESPACE::pwog_file::operator <<
 */
PWROWG_NAMESPACE::pwog_file& PWROWG_NAMESPACE::pwog_file::operator <<(
        _In_ const sensor_description& sensor) {
    switch (this->_state) {
        case state::meta_data:
            this->_state = state::sensors;
            __fallthrough;
        case state::sensors:
            break;

        default:
            throw std::logic_error("The file is not in the state to receive "
                "sensor descriptions.");
    }

    throw "TODO";

    return *this;
}


/*
 * PWROWG_NAMESPACE::pwog_file::operator <<
 */
PWROWG_NAMESPACE::pwog_file& PWROWG_NAMESPACE::pwog_file::operator <<(
        _In_ const sample& sample) {
    switch (this->_state) {
        case state::sensors:
            this->_state = state::samples;
            __fallthrough;
        case state::samples:
            break;

        default:
            throw std::logic_error("The file is not in the state to receive "
                "samples.");
    }

    static_assert(sizeof(sample)
        == sizeof(PWROWG_NAMESPACE::sample::reading)
        + sizeof(PWROWG_NAMESPACE::sample::source)
        + sizeof(PWROWG_NAMESPACE::sample::timestamp), "The implementation "
        "expected samples to be without padding.");

    throw "TODO";

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
 * PWROWG_NAMESPACE::pwog_file::initialise
 */
void PWROWG_NAMESPACE::pwog_file::initialise(
        _In_ const handle_type handle,
        _In_ const state state) {
    assert(handle != invalid);
    assert((state == state::read) || (state == state::header));
    assert(this->_handle == invalid);
    this->_handle = handle;

    switch (this->_state = state) {
        case state::read:
            this->check_fourcc();
            this->check_version();
            break;

        case state::header:
            // We can always write our native format.
            assert(!this->_swap);
            detail::write_all_bytes(this->_handle, &fourcc, sizeof(fourcc));
            // Adjust this as the version changes.
            assert(this->_version[0] == 1);
            assert(this->_version[1] == 0);
            detail::write_all_bytes(this->_handle, this->_version,
                sizeof(this->_version));
            // Meta data are next.
            this->_state = state::meta_data;
            break;
    }
}


/*
 * PWROWG_NAMESPACE::pwog_file::write
 */
void PWROWG_NAMESPACE::pwog_file::write(_In_opt_z_ const char *string) {
    if (string != nullptr) {
        const auto len = std::strlen(string) + 1;
        detail::write_all_bytes(this->_handle, string, len);
    } else {
        const char n = 0;
        detail::write_all_bytes(this->_handle, &n, sizeof(n));
    }
}


/*
 * PWROWG_NAMESPACE::pwog_file::write
 */
void PWROWG_NAMESPACE::pwog_file::write(_In_z_ const wchar_t *string) {
    const auto s = convert_string<char>(string);
    this->write(s.c_str());
}
