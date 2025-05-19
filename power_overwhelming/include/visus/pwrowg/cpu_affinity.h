// <copyright file="cpu_affinity.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_CPU_AFFINITY_H)
#define _PWROWG_CPU_AFFINITY_H
#pragma once

#include <cinttypes>

#include "visus/pwrowg/api.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// A RAII container that temporarily sets the CPU affinity of the calling
/// thread to the specified core and resets it to the previous state in its
/// destructor
/// </summary>
class POWER_OVERWHELMING_API thread_affinity_scope final {

public:

    /// <summary>
    /// Initialises a new instance by preserving the thread affinity of the
    /// calling thread.
    /// </summary>
    /// <param name="logical_cpu">The index of the logical CPU the thread
    /// should be bound to.</param>
    /// <exception cref="std::system_error">If the current thread affinity
    /// could not be determined or the new affinity could not be set.
    /// </exception>
    thread_affinity_scope(_In_ const std::uint32_t logical_cpu);

    thread_affinity_scope(const thread_affinity_scope&) = delete;

    /// <summary>
    /// Finalises the instance by restoring the saved thread affinity.
    /// </summary>
    ~thread_affinity_scope(void);

    thread_affinity_scope& operator =(
        const thread_affinity_scope&) = delete;

private:

    void *_affinity;
};


/// <summary>
/// Sets the CPU affinity of the calling thread to the given logical CPU.
/// </summary>
/// <param name="logical_cpu">The index of the logical CPU to which the CPU
/// affinity is set.</param>
/// <exception cref="std::system_error">If the operation failed.</exception>
extern POWER_OVERWHELMING_API void set_thread_affinity(
    _In_ const std::uint32_t logical_cpu);

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_CPU_AFFINITY_H) */
