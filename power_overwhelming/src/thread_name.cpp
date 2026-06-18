// <copyright file="set_thread_name.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 - 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/thread_name.h"

#include <system_error>

#if !defined(_WIN32)
#include <unistd.h>

#include <linux/prctl.h>

#include <sys/prctl.h>
#include <sys/types.h>
#endif /* !defined(_WIN32) */

#include "visus/pwrowg/convert_string.h"
#include "visus/pwrowg/on_exit.h"


/*
 * PWROWG_NAMESPACE::set_thread_name
 */
void PWROWG_NAMESPACE::set_thread_name(
        _In_ const native_thread_id thread_id,
        _In_z_ const char *thread_name) {
#if defined(_WIN32)
    if (thread_name != nullptr) {
        auto handle = ::OpenThread(THREAD_SET_LIMITED_INFORMATION, FALSE,
            thread_id);
        if (handle == NULL) {
            throw std::system_error(::GetLastError(), std::system_category());
        }
        pwrowg_on_exit([&handle] { ::CloseHandle(handle); });

        auto name = convert_string<wchar_t>(thread_name);
        ::SetThreadDescription(handle, name.c_str());
    }
#endif /* defined(_WIN32) */
}


/*
 * PWROWG_NAMESPACE::set_thread_name
 */
void PWROWG_NAMESPACE::set_thread_name(
        _In_z_ const char *thread_name) {
#if defined(_WIN32)
    set_thread_name(::GetCurrentThreadId(), thread_name);
#else /* defined(_WIN32) */
    ::prctl(PR_SET_NAME, thread_name);
#endif /* defined(_WIN32) */
}
