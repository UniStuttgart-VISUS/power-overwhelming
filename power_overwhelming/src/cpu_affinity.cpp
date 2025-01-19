// <copyright file="cpu_affinity.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/cpu_affinity.h"

#include <limits>
#include <stdexcept>
#include <system_error>

#if defined(_WIN32)
#include <Windows.h>
#else /* defined(_WIN32) */
#include <errno.h>
#include <sched.h>
#endif /* defined(_WIN32) */


#define ERROR_MSG_TOO_MANY_CORES "Setting the CPU affinity is limited on this "\
    "operating system. The specified core is out of the range of what "\
    "the operating system can handle."


/*
 * PWROWG_NAMESPACE::thread_affinity_scope::thread_affinity_scope
 */
PWROWG_NAMESPACE::thread_affinity_scope::thread_affinity_scope(
        _In_ const std::uint32_t logical_cpu) {


#if (defined(_WIN32_WINNT) && (_WIN32_WINNT >= 0x0601))
    GROUP_AFFINITY affinity;
    if (!::GetThreadGroupAffinity(::GetCurrentThread(), &affinity)) {
        throw std::system_error(::GetLastError(), std::system_category());
    }

    set_thread_affinity(logical_cpu);
    this->_affinity = new decltype(affinity)(affinity);

#elif defined(_WIN32)
    if (logical_cpu > std::numeric_limits<DWORD_PTR>::digits) {
        throw std::system_error(WINCODEC_ERR_VALUEOUTOFRANGE,
            std::system_category(), ERROR_MSG_TOO_MANY_CORES);
    }

    const auto mask = static_cast<DWORD_PTR>(1) << logical_cpu;

    // Old Windows is special in that setting a new thread affinity and
    // retieving the previous state are the same operation.
    auto affinity = ::SetThreadAffinityMask(::GetCurrentThread(), mask);
    if (affinity == 0) {
        throw std::system_error(::GetLastError(), std::system_category());
    }

    this->_affinity = new decltype(affinity)(affinity);

#else /* (defined(_WIN32_WINNT) && (_WIN32_WINNT >= 0x0601)) */
    cpu_set_t affinity;
    if (::sched_getaffinity(0, sizeof(affinity), &affinity) == -1) {
        throw std::system_error(errno, std::system_category());
    }

    set_thread_affinity(logical_cpu);
    this->_affinity = new decltype(affinity)(affinity);
#endif /* (defined(_WIN32_WINNT) && (_WIN32_WINNT >= 0x0601)) */
}


/*
* PWROWG_NAMESPACE::thread_affinity_scope::~thread_affinity_scope
 */
PWROWG_NAMESPACE::thread_affinity_scope::~thread_affinity_scope(void) {
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
 * PWROWG_NAMESPACE::set_thread_affinity
 */
void PWROWG_NAMESPACE::set_thread_affinity(
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
        throw std::system_error(WINCODEC_ERR_VALUEOUTOFRANGE,
            std::system_category(), ERROR_MSG_TOO_MANY_CORES);
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
