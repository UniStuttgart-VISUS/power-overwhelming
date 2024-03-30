// <copyright file="RaplThreadAffinity.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <ntddk.h>


/// <summary>
/// Sets the thread affinity of the callingt thread to the logical CPU core
/// identified by the given index.
/// </summary>
/// <remarks>
/// The new thread affinity is effective immediately if called below or at
/// APC_LEVEL.
/// </remarks>
/// <param name="logicalCpu">The zero-based index of the CPU core to bind the
/// calling thread to.</param>
/// <param name="previousAffinity">A <see cref="PGROUP_AFFINITY" /> to receive
/// the previous thread affinity, which can be used to restore the thread's
/// state when done.</param>
/// <returns><c>STATUS_SUCCESS</c> in case of success,
/// <c>STATUS_NOT_FOUND</c> if <paramref name="logical_cpu" /> does not
/// designate a valid CPU core on the machine.</returns>
_IRQL_requires_min_(PASSIVE_LEVEL)
_IRQL_requires_max_(APC_LEVEL)
extern NTSTATUS RaplSetThreadAffinity(_In_ const __int32 logicalCpu,
    _Out_ PGROUP_AFFINITY previousAffinity) noexcept;
