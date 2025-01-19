// <copyright file="set_thread_name.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "thread_name.h"

// See https://msdn.microsoft.com/de-de/library/xcb2z8hs.aspx?f=255&MSPPError=-2147217396


#if defined(_WIN32)
static const DWORD MS_VC_EXCEPTION = 0x406D1388;

#pragma pack(push, 8)
typedef struct tagTHREADNAME_INFO {
    DWORD dwType; // Must be 0x1000.
    LPCSTR szName; // Pointer to name (in user addr space).
    DWORD dwThreadID; // Thread ID (-1=caller thread).
    DWORD dwFlags; // Reserved for future use, must be zero.
} THREADNAME_INFO;
#pragma pack(pop)
#endif /* defined(_WIN32) */


/*
 * PWROWG_DETAIL_NAMESPACE::set_thread_name
 */
void PWROWG_DETAIL_NAMESPACE::set_thread_name(
    _In_ const native_thread_id thread_id,
    _In_z_ const char* thread_name) {
#if defined(_WIN32)
    if (thread_name != nullptr) {
        THREADNAME_INFO info;
        info.dwType = 0x1000;
        info.szName = thread_name;
        info.dwThreadID = thread_id;
        info.dwFlags = 0;

#pragma warning(push)
#pragma warning(disable: 6320 6322)
        __try {
            ::RaiseException(MS_VC_EXCEPTION, 0,
                sizeof(info) / sizeof(ULONG_PTR),
                reinterpret_cast<ULONG_PTR*>(&info));
        } __except (EXCEPTION_EXECUTE_HANDLER) {}
#pragma warning(pop)
    }
#endif /* defined(_WIN32) */
}


/*
 * PWROWG_DETAIL_NAMESPACE::set_thread_name
 */
void PWROWG_DETAIL_NAMESPACE::set_thread_name(_In_z_ const char* thread_name) {
#if defined(_WIN32)
    set_thread_name(::GetCurrentThreadId(), thread_name);
#endif /* defined(_WIN32) */
}
