// <copyright file="thread_statistics.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/thread_statistics.h"

#include <cassert>
#include <cstring>

#include "visus/pwrowg/convert_string.h"
#include "visus/pwrowg/on_exit.h"

#include "io_util.h"


/*
 * PWROWG_NAMESPACE::thread_statistics::thread_statistics
 */
PWROWG_NAMESPACE::thread_statistics::thread_statistics(
        _In_z_ const wchar_t *path) {
#if defined(POWER_OVERWHELMING_WITH_THREAD_STATS)
#if defined(_WIN32)
    this->_handle = detail::open(path, GENERIC_WRITE, 0, CREATE_ALWAYS);
    assert(this->_handle != INVALID_HANDLE_VALUE);
#else /* defined(_WIN32) */
    this->_handle = detail::open(path, O_WRONLY | O_CREAT | O_TRUNC);
    assert(this->_handle != -1);
#endif /* defined(_WIN32) */
#endif /* defined(POWER_OVERWHELMING_WITH_THREAD_STATS) */
}


/*
 * PWROWG_NAMESPACE::thread_statistics::thread_statistics
 */
PWROWG_NAMESPACE::thread_statistics::thread_statistics(
        _In_z_ const char *path) {
#if defined(POWER_OVERWHELMING_WITH_THREAD_STATS)
#if defined(_WIN32)
    this->_handle = detail::open(path, GENERIC_WRITE, 0, CREATE_ALWAYS);
    assert(this->_handle != INVALID_HANDLE_VALUE);
#else /* defined(_WIN32) */
    this->_handle = detail::open(path, O_WRONLY | O_CREAT | O_TRUNC);
    assert(this->_handle != -1);
#endif /* defined(_WIN32) */
#endif /* defined(POWER_OVERWHELMING_WITH_THREAD_STATS) */
}


/*
 * PWROWG_NAMESPACE::thread_statistics::~thread_statistics
 */
PWROWG_NAMESPACE::thread_statistics::~thread_statistics(void) noexcept {
#if defined(POWER_OVERWHELMING_WITH_THREAD_STATS)
    try {
#if defined(_WIN32)
        assert(this->_handle != INVALID_HANDLE_VALUE);
        this->write("{");

        {
            auto id = std::to_string(::GetCurrentThreadId());
            this->write("\"id\": ");
            this->write(id.c_str(), id.size());
        }

        {
            wchar_t *name;
            if SUCCEEDED(::GetThreadDescription(::GetCurrentThread(), &name)) {
                pwrowg_on_exit([&name] { ::LocalFree(name); });
                auto n = PWROWG_NAMESPACE::convert_string<char>(name);
                this->write(",");
                this->write("\"name\": \"");
                this->write(n.c_str(), n.size());
                this->write("\"", 1);
            }
        }

        {
            ULONG64 cycles;
            if (::QueryThreadCycleTime(::GetCurrentThread(), &cycles)) {
                auto c = std::to_string(cycles);
                this->write(",");
                this->write("\"cycles\": ");
                this->write(c.c_str(), c.size());
            }
        }

        {
            FILETIME create, exit, kernel, user;
            LARGE_INTEGER li;

            if (::GetThreadTimes(::GetCurrentThread(), &create, &exit,
                    &kernel, &user)) {
                li.HighPart = kernel.dwHighDateTime;
                li.LowPart = kernel.dwLowDateTime;
                auto k = std::to_string(li.QuadPart);
                this->write(",");
                this->write("\"kernel\": ");
                this->write(k.c_str(), k.size());

                li.HighPart = user.dwHighDateTime;
                li.LowPart = user.dwLowDateTime;
                auto u = std::to_string(li.QuadPart);
                this->write(",");
                this->write("\"user\": ");
                this->write(u.c_str(), u.size());
            }
        }

        this->write("}");
        ::CloseHandle(this->_handle);
#else /* defined(_WIN32) */
        assert(this->_handle != -1);
        ::close(this->_handle);
#endif /* defined(_WIN32) */
    } catch (...) {
        PWROWG_TRACE(_T("Failed writing thread statistics."));
    }
#endif /* defined(POWER_OVERWHELMING_WITH_THREAD_STATS) */
}


/*
 * PWROWG_NAMESPACE::thread_statistics::write
 */
void PWROWG_NAMESPACE::thread_statistics::write(_In_z_ const char *text) {
    detail::write_all_bytes(this->_handle, text, ::strlen(text));
}


/*
 * PWROWG_NAMESPACE::thread_statistics::write
 */
void PWROWG_NAMESPACE::thread_statistics::write(
        _In_reads_(cnt) const char *text,
        _In_ const std::size_t cnt) {
    detail::write_all_bytes(this->_handle, text, cnt);
}
