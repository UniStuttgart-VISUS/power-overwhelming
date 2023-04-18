// <copyright file="thread_affinity.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "thread_affinity.h"


/*
 * ::rapl_set_thread_affinity
 */
_IRQL_requires_min_(PASSIVE_LEVEL)
_IRQL_requires_max_(APC_LEVEL)
NTSTATUS rapl_set_thread_affinity(_In_ const __int32 logical_cpu,
        _Out_ PGROUP_AFFINITY previous_affinity) {
    const auto groups = ::KeQueryActiveGroupCount();
    GROUP_AFFINITY affinity { 0 };
    __int32 total = 0;

    // Search the group in which 'logical_cpu' falls.
    for (; affinity.Group < groups; ++affinity.Group) {
        const auto current = ::KeQueryActiveProcessorCountEx(affinity.Group);
        if (total + current > logical_cpu) {
            affinity.Mask = static_cast<KAFFINITY>(logical_cpu) - total;
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

    ::KeSetSystemGroupAffinityThread(&affinity, previous_affinity);
    return STATUS_SUCCESS;
}
