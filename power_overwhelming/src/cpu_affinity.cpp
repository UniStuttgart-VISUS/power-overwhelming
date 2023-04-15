// <copyright file="cpu_affinity.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/cpu_affinity.h"

#include <limits>
#include <stdexcept>
#include <system_error>

#if defined(_WIN32)
#include <Windows.h>
#else /* defined(_WIN32) */
#include <errno.h>
#include <sched.h>
#endif /* defined(_WIN32) */

using visus::power_overwhelming::thread_affinity_restore_point;


/*
 * ...::thread_affinity_restore_point::thread_affinity_restore_point
 */
thread_affinity_restore_point::thread_affinity_restore_point(void) {
#if (defined(_WIN32_WINNT) && (_WIN32_WINNT >= 0x0601))
    auto affinity = new GROUP_AFFINITY();

    if (!::GetThreadGroupAffinity(::GetCurrentThread(), affinity)) {
        auto error = ::GetLastError();
        delete affinity;
        throw std::system_error(error, std::system_category());
    }

    this->_affinity = affinity;

#elif defined(_WIN32)
    // Cf. https://stackoverflow.com/questions/6601862/query-thread-not-process-processor-affinity#6601917
    auto thread = ::GetCurrentThread();
    DWORD_PTR mask = 1;

    while (mask) {
        auto affinity = ::SetThreadAffinityMask(thread, mask);
        if (affinity == 0) {
            // Operation failed, so either try again or fail depending on the
            // last error.
            auto error = ::GetLastError();
            if (error != ERROR_INVALID_PARAMETER) {
                throw std::system_error(error, std::system_category());
            }

            mask <<= 1;

        } else {
            // If this succeeded, we know the current mask. Restore the state
            // and save the mask.
            if (!::SetThreadAffinityMask(thread, affinity)) {
                throw std::system_error(::GetLastError(),
                    std::system_category());
            }

            this->_affinity = new decltype(affinity)(affinity);
        }
    }

#else /* (defined(_WIN32_WINNT) && (_WIN32_WINNT >= 0x0601)) */
    cpu_set_t affinity;
    if (::sched_getaffinity(0, sizeof(affinity), &affinity) == -1) {
        throw std::system_error(errno, std::system_category());
    }

    this->_affinity = new decltype(affinity)(affinity);
#endif /* (defined(_WIN32_WINNT) && (_WIN32_WINNT >= 0x0601)) */
}


/*
* ...::thread_affinity_restore_point::~thread_affinity_restore_point
 */
thread_affinity_restore_point::~thread_affinity_restore_point(void) {
    // Note: If the restore here fails, we just need to accept it, because we
    // cannot throw in a destructor.
#if (defined(_WIN32_WINNT) && (_WIN32_WINNT >= 0x0601))
    auto affinity = static_cast<GROUP_AFFINITY *>(this->_affinity);
    ::SetThreadGroupAffinity(::GetCurrentThread(), affinity, nullptr);
    delete affinity;

#elif defined(_WIN32)
    auto affinity = static_cast<DWORD_PTR *>(this->_affinity);
    ::SetThreadAffinityMask(::GetCurrentThread(), *affinity);
    delete affinity;

#else /* (defined(_WIN32_WINNT) && (_WIN32_WINNT >= 0x0601)) */
    auto affinity = static_cast<cpu_set_t *>(this->_affinity);
    ::sched_setaffinity(0, sizeof(cpu_set_t), affinity);
    delete affinity;
#endif /* (defined(_WIN32_WINNT) && (_WIN32_WINNT >= 0x0601)) */
}


/*
 * visus::power_overwhelming::set_thread_affinity
 */
void visus::power_overwhelming::set_thread_affinity(
        _In_ const std::uint32_t logical_cpu) {
#if (defined(_WIN32_WINNT) && (_WIN32_WINNT >= 0x0601))
    const auto groups = ::GetActiveProcessorGroupCount();
    GROUP_AFFINITY affinity { 0 };
    std::decay<decltype(logical_cpu)>::type total = 0;

    // Search the group in which 'logical_cpu' falls.
    for (; affinity.Group < groups; ++affinity.Group) {
        const auto current = ::GetActiveProcessorCount(affinity.Group);
        if (total + current > logical_cpu) {
            affinity.Mask = logical_cpu - total;
            break;
        } else {
            total += current;
        }
    }

    if (affinity.Group >= groups) {
        // Logical CPU number is invalid.
        throw std::system_error(ERROR_NOT_FOUND, std::system_category(),
            "The specified logical CPU number is too large.");
    }

    affinity.Mask = 1ULL << affinity.Mask;

    if (!::SetThreadGroupAffinity(::GetCurrentThread(), &affinity, nullptr)) {
        throw std::system_error(::GetLastError(), std::system_category());
    }

#elif defined(_WIN32)
    // Clients before Windows 7 do not support more than 64 cores, because they
    // lack the thread group affinity API.
    if (logical_cpu > std::numeric_limits<DWORD_PTR>::digits) {
        throw std::invalid_argument("Setting the CPU affinity is limited to 64 "
            "cores on this operating system.");
    }

    const auto mask = static_cast<DWORD_PTR>(1) << logical_cpu;
    if (!::SetThreadAffinityMask(::GetCurrentThread(), mask)) {
        throw std::system_error(::GetLastError(), std::system_category());
    }

#else /* (defined(_WIN32_WINNT) && (_WIN32_WINNT >= 0x0601)) */
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(logical_cpu, &cpuset);

    if (::sched_setaffinity(0, sizeof(cpuset), &cpuset)) {
        throw std::system_error(errno, std::system_category());
    }
#endif /* (defined(_WIN32_WINNT) && (_WIN32_WINNT >= 0x0601)) */
}
