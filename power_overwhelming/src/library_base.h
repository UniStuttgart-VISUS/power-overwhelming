// <copyright file="library_base.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_LIBRARY_BASE_H)
#define _PWROWG_LIBRARY_BASE_H

#pragma once

#include <array>
#include <system_error>

#if defined(_WIN32)
#include <windows.h>
#else /* defined(_WIN32) */
#include <dlfcn.h>
#endif /* defined(_WIN32) */

#include "visus/pwrowg/api.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Base class for managing libraries that are lazily loaded.
/// </summary>
/// <remarks>
/// Rationale: If we statically link against vendor-specific management
/// libraries, applications will only work if all of these libraries are
/// available on the system, ie. if the system has NVIDIA and AMD GPUs. This is
/// highly unlikely. Explicitly loading the libraries on demand solves this
/// issue.
/// </remarks>
class library_base {

public:

#if defined(_WIN32)
    typedef TCHAR char_type;
#else /* defined(_WIN32) */
    typedef char char_type;
#endif /* defined(_WIN32) */

#if defined(_WIN32)
    typedef FARPROC function_type;
#else /* defined(_WIN32) */
    typedef void *function_type;
#endif /* defined(_WIN32) */

#if defined(_WIN32)
    typedef HMODULE handle_type;
#else /* defined(_WIN32) */
    typedef void *handle_type;
#endif /* defined(_WIN32) */

    static constexpr handle_type invalid_handle
#if defined(_WIN32)
        = NULL;
#else /* defined(_WIN32) */
        = nullptr;
#endif /* defined(_WIN32) */

    library_base(const library_base&) = delete;

    library_base(library_base&& rhs) noexcept;

    ~library_base(void);

    library_base& operator =(const library_base& rhs) = delete;

    library_base& operator =(library_base&& rhs) noexcept;

    inline operator bool(void) const noexcept {
            return (this->_handle != invalid_handle);
    }

protected:

    explicit library_base(handle_type&& handle);

    explicit library_base(const char_type *path);

    template<class... TPaths> library_base(TPaths&&... paths);

    function_type get_function(const char *name);

    template<class TFunction>
    inline TFunction get_function(const char *name) {
            return reinterpret_cast<TFunction>(this->get_function(name));
    }

private:

    handle_type _handle;
};

PWROWG_DETAIL_NAMESPACE_END


/*
 * PWROWG_DETAIL_NAMESPACE::library_base::library_base
 */
template<class... TPaths>
PWROWG_DETAIL_NAMESPACE::library_base::library_base(TPaths&&... paths)
        : _handle(invalid_handle) {
    std::array<const char_type *, sizeof...(TPaths)> ps = { paths... };

    for (auto& p : ps) {
#if defined(_WIN32)
        this->_handle = ::LoadLibrary(p);
#else /* defined(_WIN32) */
        this->_handle = ::dlopen(p, RTLD_LAZY);
#endif /* defined(_WIN32) */
        if (this->_handle != invalid_handle) {
            break;
        }
    }

    if (this->_handle == invalid_handle) {
#if defined(_WIN32)
        throw std::system_error(::GetLastError(), std::system_category());
#else /* defined(_WIN32) */
        throw std::runtime_error(::dlerror());
#endif /* defined(_WIN32) */
    }
}

#endif /* !defined(_PWROWG_LIBRARY_BASE_H) */
