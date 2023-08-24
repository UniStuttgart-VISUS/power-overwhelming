// <copyright file="sampler_thread.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <chrono>
#include <memory>
#include <mutex>
#include <sstream>
#include <thread>
#include <vector>

#include "power_overwhelming/sampler_source.h"

#include "thread_name.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// A thread that performs periodic sampling of inherently synchronous
    /// sources.
    /// </summary>
    class sampler_thread {

    public:

        /// <summary>
        /// The type used to specify the sampling interval.
        /// </summary>
        typedef std::chrono::duration<sampler_source::interval_type,
            std::micro> interval_type;

        explicit sampler_thread(_In_ sampler_source *source);

        virtual ~sampler_thread(void) noexcept;

        void add(_In_ sampler_source *source);

        inline interval_type interval(void) const noexcept {
            return this->_interval;
        }

        /// <summary>
        /// Remove <paramref name="source" /> from being sampled by this thread
        /// and answer whether the thread can be terminated.
        /// </summary>
        /// <param name="source">The source to be removed.</param>
        /// <returns><c>true</c> if the thread has no sources to sample any
        /// more, <c>false</c> if there are other sources being sampled.
        /// </returns>
        bool remove(_In_ sampler_source *source);

        bool samples(_In_ const sampler_source *source) const;

    private:

        void sample(void);

        interval_type _interval;
        mutable std::mutex _lock;
        std::vector<sampler_source *> _sources;
        std::thread _thread;
    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
