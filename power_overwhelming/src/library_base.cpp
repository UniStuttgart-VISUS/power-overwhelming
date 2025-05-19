// <copyright file="library_base.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "library_base.h"

#include <memory>


/*
 * PWROWG_DETAIL_NAMESPACE::library_base::library_base
 */
PWROWG_DETAIL_NAMESPACE::library_base::library_base(
        library_base&& rhs) noexcept : _handle(rhs._handle) {
    rhs._handle = invalid_handle;
}


/*
 * PWROWG_DETAIL_NAMESPACE::library_base::~library_base
 */
PWROWG_DETAIL_NAMESPACE::library_base::~library_base(void) {
    if (this->_handle != invalid_handle) {
#if defined(_WIN32)
        ::FreeLibrary(this->_handle);
#else /* defined(_WIN32) */
        ::dlclose(this->_handle);
#endif /* defined(_WIN32) */
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::library_base::operator =
 */
PWROWG_DETAIL_NAMESPACE::library_base&
PWROWG_DETAIL_NAMESPACE::library_base::operator =(library_base&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        this->_handle = rhs._handle;
        rhs._handle = invalid_handle;
    }

    return *this;
}


/*
 * PWROWG_DETAIL_NAMESPACE::library_base::library_base
 */
PWROWG_DETAIL_NAMESPACE::library_base::library_base(
        handle_type&& handle) : _handle(handle) {
    if (this->_handle == invalid_handle) {
        throw new std::invalid_argument("A valid library handle must be "
            "provided.");
    }

    handle = invalid_handle;
}


/*
 * PWROWG_DETAIL_NAMESPACE::library_base::library_base
 */
PWROWG_DETAIL_NAMESPACE::library_base::library_base(
        const char_type *path)
#if defined(_WIN32)
        : _handle(::LoadLibrary(path)) {
#else /* defined(_WIN32) */
        : _handle(::dlopen(path, RTLD_LAZY)) {
#endif /* defined(_WIN32) */

    if (this->_handle == invalid_handle) {
#if defined(_WIN32)
        throw std::system_error(::GetLastError(), std::system_category());
#else /* defined(_WIN32) */
        throw std::runtime_error(::dlerror());
#endif /* defined(_WIN32) */
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::library_base::get_function
 */
PWROWG_DETAIL_NAMESPACE::library_base::function_type
PWROWG_DETAIL_NAMESPACE::library_base::get_function(
        const char *name) {
#if defined(_WIN32)
    auto retval = ::GetProcAddress(this->_handle, name);
#else /* defined(_WIN32) */
    auto retval = ::dlsym(this->_handle, name);
#endif /* defined(_WIN32) */

    if (retval == nullptr) {
#if defined(_WIN32)
        throw std::system_error(::GetLastError(), std::system_category());
#else /* defined(_WIN32) */
        throw std::runtime_error(::dlerror());
#endif /* defined(_WIN32) */
    }

    return retval;
}

