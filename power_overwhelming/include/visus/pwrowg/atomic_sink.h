// <copyright file="atomic_sink.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for more information.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_ATOMIC_SINK_H)
#define _PWROWG_ATOMIC_SINK_H
#pragma once

#include <cassert>
#include <chrono>
#include <thread>
#include <vector>

#include "visus/pwrowg/atomic_collector.h"
#include "visus/pwrowg/sample.h"
#include "visus/pwrowg/sensor_description.h"
#include "visus/pwrowg/thread_name.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// A CRTP-based adapter class that collects data in a
/// <see cref="atomic_collector" /> and calls the <c>write_sample</c> method of
/// <typeparamref name="TSink" /> to periodically persist the data.
/// </summary>
/// <typeparam name="TSink">The type of the sink, which must have a protected
/// method <c>write_sample</c> that perists a single <see cref="sample" />.
/// </typeparam>
/// <typeparam name="PageSize">The number of samples collected in a single page
/// of the underlying <see cref="atomic_collector" />.</typeparam>
template<class TSink, std::size_t PageSize = 512>
class atomic_sink final : public TSink {

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

    template<class TRep, class TPeriod, class... TArgs>
    atomic_sink(_In_ const std::chrono::duration<TRep, TPeriod> interval,
        TArgs&&... args);

    /// <summary>
    /// Finalises the instance.
    /// </summary>
    ~atomic_sink(void) noexcept;

private:

    /// <summary>
    /// The atomic collector used to dump the samples to.
    /// </summary>
    typedef atomic_collector<sample, PageSize> collector_type;

    /// <summary>
    /// The code running in the <see cref="_writer" /> thread.
    /// </summary>
    void write(void);

    collector_type _collector;
    std::chrono::milliseconds _interval;
    std::thread _writer;
    alignas(false_sharing_range) std::atomic<bool> _running;
    alignas(false_sharing_range) std::atomic<const sensor_description *>
        _sensors;
};

PWROWG_NAMESPACE_END

#include "visus/pwrowg/atomic_sink.inl"

#endif /* !defined(_PWROWG_ATOMIC_SINK_H) */
