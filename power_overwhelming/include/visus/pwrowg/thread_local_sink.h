// <copyright file="thread_local_sink.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for more information.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_THREAD_LOCAL_SINK_H)
#define _PWROWG_THREAD_LOCAL_SINK_H
#pragma once

#include <cassert>
#include <chrono>
#include <condition_variable>
#include <map>
#include <mutex>
#include <thread>
#include <vector>

#include "visus/pwrowg/atomic_utilities.h"
#include "visus/pwrowg/event.h"
#include "visus/pwrowg/on_exit.h"
#include "visus/pwrowg/sample.h"
#include "visus/pwrowg/sensor_description.h"
#include "visus/pwrowg/thread_name.h"
#include "visus/pwrowg/thread_statistics.h"
#include "visus/pwrowg/trace.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// A sink that collects samples in thread-local buffers that are periodically
/// published to a writer thread executing the write logic of
/// <typeparamref name="TSink" />.
/// </summary>
/// <typeparam name="TSink"></typeparam>
template<class TSink> class thread_local_sink final : public TSink {

public:

    /// <summary>
    /// The callback that must be registered with the sensor array to use the
    /// sink as target for the samples.
    /// </summary>
    /// <param name="samples"></param>
    /// <param name="cnt"></param>
    /// <param name="sensors"></param>
    /// <param name="context"></param>
    static void sample_callback(_In_reads_(cnt) const sample *samples,
        _In_ const std::size_t cnt,
        _In_ const sensor_description *sensors,
        _In_opt_ void *context);

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <typeparam name="TArgs">The types of the arguments passed to the
    /// constructor of <typeparamref name="TSink" />.</typeparam>
    /// <param name="page_size">The number of samples allocated at once.</param>
    /// <param name="args">The arguments passed tot he constructor of
    /// <typeparamref name="TSink" />.</param>
    template<class... TArgs>
    thread_local_sink(_In_ const std::size_t page_size, TArgs&&... args);

    /// <summary>
    /// Finalises the instance.
    /// </summary>
    ~thread_local_sink(void) noexcept;

    /// <summary>
    /// Disposes the sink, which stops the writer thread.
    /// </summary>
    /// <remarks>
    /// Use this to enforce that the sink is stopped before the sensor array it
    /// retrieves its samples from is destroyed, which might be a problem if both
    /// are local variables in the same scope.
    /// </remarks>
    void dispose(void) noexcept;

private:

    /// <summary>
    /// Possible states of the per-thread <see cref="page" />s.
    /// </summary>
    enum page_state {
        /// <summary>
        /// The page is empty and may be reused by the first thread that can
        /// change the state in a CAS operation.
        /// </summary>
        reusable = 0x00,

        /// <summary>
        /// The page is currently assigned to a source thread, but not writing
        /// at that moment. As long as the page is in this state and not in
        /// <see cref="receiving" />, the writer can assume that the page is
        /// done when it is tearing down.
        /// </summary>
        assigned = 0x01,

        /// <summary>
        /// The page is currently receiving samples in the sample callback. The
        /// writer thread must not touch it and wait for the state to change on
        /// teardown.
        /// </summary>
        callback = 0x02,

        /// <summary>
        /// Combination of <see cref="assigned" /> and <see cref="callback" />.
        /// </summary>
        assigned_callback = assigned | callback,

        /// <summary>
        /// The writer thread is reading the page and sending its contents to
        /// the sink implementation.
        /// </summary>
        writing = 0x04
    };

    /// <summary>
    /// Wraps a page of samples that is exclusively used by a single thread
    /// and published to the writer thread when full.
    /// </summary>
    struct page final {
        std::vector<sample> buffer;
        page *next;
        std::atomic<page_state> state;

        static inline void *operator new(_In_ const std::size_t size) {
            return detail::allocate_for_atomic(size);
        }

        static inline void operator delete(_In_ void *ptr) noexcept {
            detail::free_for_atomic(ptr);
        }

        inline explicit page(const std::size_t size)
            : buffer(size),
            next(nullptr),
            state(page_state::assigned_callback) { }

        inline bool is_state(_In_ const page_state reference) const noexcept {
            const auto s = this->state.load(std::memory_order_acquire);
            return ((s & reference) == reference);
        }
    };

    static constexpr auto alignment = detail::false_sharing_range;

    static thread_local std::map<thread_local_sink *, page *> buffer;

    /// <summary>
    /// The code running in the <see cref="_writer" /> thread.
    /// </summary>
    void write(void);

    /// <summary>
    /// Writes the sampes in the given page to the sink.
    /// </summary>
    void write_samples(_In_ page *p);

    event_type _event;
    std::thread _writer;
    alignas(alignment) std::atomic<page *> _pages;
    std::size_t _page_size;
    alignas(alignment) std::atomic<bool> _running;
    alignas(alignment) std::atomic<const sensor_description *> _sensors;
};

PWROWG_NAMESPACE_END

#include "visus/pwrowg/thread_local_sink.inl"

#endif /* !defined(_PWROWG_THREAD_LOCAL_SINK_H) */
