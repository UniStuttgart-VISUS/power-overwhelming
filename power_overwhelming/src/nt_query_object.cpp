// <copyright file="nt_query_object" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if defined(_WIN32)
#include "nt_query_object.h"

#include <memory>
#include <stdexcept>
#include <system_error>


/*
 * PWROWG_DETAIL_NAMESPACE::nt_query_object::nt_query_object
 */
PWROWG_DETAIL_NAMESPACE::nt_query_object::nt_query_object(void) {
    this->_ntdll = ::LoadLibraryW(L"ntdll.dll");
    if (this->_ntdll == nullptr) {
        throw std::system_error(::GetLastError(), std::system_category());
    }

    this->_function = reinterpret_cast<decltype(this->_function)>(
        ::GetProcAddress(this->_ntdll, "NtQueryObject"));
}


/*
 * PWROWG_DETAIL_NAMESPACE::nt_query_object::~nt_query_object
 */
PWROWG_DETAIL_NAMESPACE::nt_query_object::~nt_query_object(void) noexcept {
    if (this->_ntdll != nullptr) {
        ::FreeLibrary(this->_ntdll);
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::nt_query_object::operator =
 */
PWROWG_DETAIL_NAMESPACE::nt_query_object&
PWROWG_DETAIL_NAMESPACE::nt_query_object::operator =(
        _Inout_ nt_query_object&& rhs) noexcept {
    if (std::addressof(rhs) != this) {
        if (this->_ntdll != nullptr) {
            ::FreeLibrary(this->_ntdll);
        }

        this->_function = rhs._function;
        rhs._function = nullptr;
        this->_ntdll = rhs._ntdll;
        rhs._ntdll = nullptr;
    }

    return *this;
}


/*
 * PWROWG_DETAIL_NAMESPACE::nt_query_object::operator ()
 */
NTSTATUS PWROWG_DETAIL_NAMESPACE::nt_query_object::operator ()(
        _In_opt_ HANDLE handle,
        _In_ OBJECT_INFORMATION_CLASS info_class,
        _Out_writes_bytes_opt_(cnt) PVOID info,
        _In_ const ULONG cnt,
        _Out_opt_ PULONG output) {
    if (this->_function == nullptr) {
        throw std::logic_error("A moved nt_query_object instance cannot be "
            "called.");
    }

    return this->_function(handle, info_class, info, cnt, output);
}

#endif /* defined(_WIN32) */
