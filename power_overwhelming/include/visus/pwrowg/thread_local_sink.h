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

#include "visus/pwrowg/atomic_collector.h"
#include "visus/pwrowg/sample.h"
#include "visus/pwrowg/sensor_description.h"
#include "visus/pwrowg/thread_name.h"
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

    static constexpr auto alignment = detail::false_sharing_range;

    static thread_local std::map<thread_local_sink *, std::size_t> buffer;

    /// <summary>
    /// The code running in the <see cref="_writer" /> thread.
    /// </summary>
    void write(void);

    std::vector<std::vector<sample>> _buffers;
    std::condition_variable _condition;
    std::mutex _lock;
    std::vector<std::size_t> _ready;
    std::thread _writer;
    std::size_t _page_size;
    alignas(alignment) std::atomic<bool> _running;
    alignas(alignment) std::atomic<const sensor_description *> _sensors;
};

PWROWG_NAMESPACE_END

#include "visus/pwrowg/thread_local_sink.inl"

#endif /* !defined(_PWROWG_THREAD_LOCAL_SINK_H) */
