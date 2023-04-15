// <copyright file="cpu_affinity.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cinttypes>

#include "power_overwhelming/power_overwhelming_api.h"


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// A RAII container that preserves the thread affinity at its time of
    /// construction and restores it when it is deleted.
    /// </summary>
    class POWER_OVERWHELMING_API thread_affinity_restore_point final {

    public:

        /// <summary>
        /// Initialises a new instance by preserving the thread affinity of the
        /// calling thread.
        /// </summary>
        /// <exception cref="std::system_error">If the current thread affinity
        /// could not be determined.</exception>
        thread_affinity_restore_point(void);

        thread_affinity_restore_point(
            const thread_affinity_restore_point&) = delete;

        /// <summary>
        /// Finalises the instance by restoring the saved thread affinity.
        /// </summary>
        ~thread_affinity_restore_point(void);

        thread_affinity_restore_point& operator =(
            const thread_affinity_restore_point&) = delete;

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

} /* namespace power_overwhelming */
} /* namespace visus */
