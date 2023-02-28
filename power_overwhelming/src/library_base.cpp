// <copyright file="library_base.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "library_base.h"

#include <memory>


/*
 * visus::power_overwhelming::detail::library_base::library_base
 */
visus::power_overwhelming::detail::library_base::library_base(
        library_base &&rhs) noexcept : _handle(rhs._handle) {
    rhs._handle = NULL;
}


/*
 * visus::power_overwhelming::detail::library_base::~library_base
 */
visus::power_overwhelming::detail::library_base::~library_base(void) {
    if (this->_handle != NULL) {
        ::FreeLibrary(this->_handle);
    }
}


/*
 * visus::power_overwhelming::detail::library_base::operator =
 */
visus::power_overwhelming::detail::library_base&
visus::power_overwhelming::detail::library_base::operator =(
        library_base&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        this->_handle = rhs._handle;
        rhs._handle = NULL;
    }

    return *this;
}


/*
 * visus::power_overwhelming::detail::library_base::library_base
 */
visus::power_overwhelming::detail::library_base::library_base(
        HMODULE&& handle) : _handle(handle) {
    if (this->_handle == NULL) {
        throw new std::invalid_argument("A valid library handle must be "
            "provided.");
    }

    handle = NULL;
}


/*
 * visus::power_overwhelming::detail::library_base::library_base
 */
visus::power_overwhelming::detail::library_base::library_base(
        const TCHAR *path) : _handle(::LoadLibrary(path)) {
    if (this->_handle == NULL) {
        throw std::system_error(::GetLastError(), std::system_category());
    }
}


/*
 * visus::power_overwhelming::detail::library_base::get_function
 */
FARPROC visus::power_overwhelming::detail::library_base::get_function(
        const char *name) {
    auto retval = ::GetProcAddress(this->_handle, name);

    if (retval == nullptr) {
        throw std::system_error(::GetLastError(), std::system_category());
    }

    return retval;
}

