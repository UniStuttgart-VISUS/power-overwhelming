// <copyright file="nt_query_object" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if defined(_WIN32)
#include <Windows.h>
#include <ntstatus.h>
#include <winternl.h>

#include "visus/pwrowg/api.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// A wrapper for the <see cref="NtQueryObject" /> syscall.
/// </summary>
class nt_query_object final {

public:

    nt_query_object(void);

    inline nt_query_object(_Inout_ nt_query_object&& rhs) noexcept
            : _function(rhs._function), _ntdll(rhs._ntdll) {
        rhs._function = nullptr;
        rhs._ntdll = nullptr;
    }

    ~nt_query_object(void) noexcept;

    nt_query_object& operator =(_Inout_ nt_query_object&& rhs) noexcept;

    NTSTATUS operator ()(
        _In_opt_ HANDLE handle,
        _In_ OBJECT_INFORMATION_CLASS info_class,
        _Out_writes_bytes_opt_(cnt) PVOID info,
        _In_ const ULONG cnt,
        _Out_opt_ PULONG output);

private:

    decltype(&::NtQueryObject) _function;
    HMODULE _ntdll;
};


PWROWG_DETAIL_NAMESPACE_END

#endif /* defined(_WIN32) */
