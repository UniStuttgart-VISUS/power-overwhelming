// <copyright file="thread_affinity.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "RaplThreadAffinity.h"


/*
 * ::RaplSetThreadAffinity
 */
_IRQL_requires_min_(PASSIVE_LEVEL)
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS RaplSetThreadAffinity(_In_ const __int32 logicalCpu,
        _Out_ PGROUP_AFFINITY previousAffinity) noexcept {
    KdPrint(("[PWROWG] Set thread affinity to logical CPU %d.\r\n",
        logicalCpu));

    const auto groups = ::KeQueryActiveGroupCount();
    GROUP_AFFINITY affinity { 0 };
    __int32 total = 0;

    // Search the group in which 'logicalCpu' falls.
    for (; affinity.Group < groups; ++affinity.Group) {
        const auto current = ::KeQueryActiveProcessorCountEx(affinity.Group);
        if (total + current > logicalCpu) {
            affinity.Mask = static_cast<KAFFINITY>(logicalCpu) - total;
            break;
        } else {
            total += current;
        }
    }

    if (affinity.Group >= groups) {
        // Logical CPU number is invalid.
        return STATUS_NOT_FOUND;
    }

    affinity.Mask = 1ULL << affinity.Mask;

    ::KeSetSystemGroupAffinityThread(&affinity, previousAffinity);
    return STATUS_SUCCESS;
}
