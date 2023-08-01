// <copyright file="sampler.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <algorithm>
#include <chrono>
#include <mutex>
#include <set>
#include <sstream>
#include <stdexcept>
#include <thread>

#include "async_measurement_data_source.h"
#include "with_context.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// Generic sampler thread for delivering data from sensors of the same
    /// type at the same rate.
    /// </summary>
    /// <remarks>
    /// <para>The sampler keeps a set of sources that must implement the
    /// <see cref="async_measurement_data_source" /> interface and queries these
    /// sources periodically at the configured interval. Therefore, sources must
    /// be registered only with a sampler that matches their
    /// <see cref="async_sampling" /> configuration. The caller is responsible
    /// for ensuring that this is the case.</para>
    /// </remarks>
    /// <typeparam name="TSource">The type of the sensor source, which must
    /// derive from <see cref="async_measurement_data_source" /> or provide a
    /// similar interface in order to be used with the generic implementation of
    /// a sampler for inherently synchronous sensors.</typeparam>
    template<class TSource> class basic_sampler {

    public:

        /// <summary>
        /// The type used to specify the sampling interval.
        /// </summary>
        typedef std::chrono::duration<async_sampling::microseconds_type,
            std::micro> interval_type;

        /// <summary>
        /// The type of the source that provides the samples.
        /// </summary>
        typedef TSource *source_type;

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="interval">The sampling interval of the instance.
        /// </param>
        explicit basic_sampler(_In_ const interval_type interval);

        /// <summary>
        /// Finalises the instance.
        /// </summary>
        /// <remarks>
        /// The destructor blocks until the sampler thread has exited.
        /// </remarks>
        ~basic_sampler(void) noexcept;

        /// <summary>
        /// Answer the interval of the sampler.
        /// </summary>
        /// <returns>The sampling interval.</returns>
        inline interval_type interval(void) const noexcept {
            return this->_interval;
        }

        /// <summary>
        /// Answer whether this sampler samples the specified source.
        /// </summary>
        /// <param name="source">The source to search. It is safe to pass
        /// <c>nullptr</c>, in which case the result will always be
        /// <c>false</c>.</param>
        /// <returns><c>true</c> if the sensor was found in the sampler,
        /// <c>false</c> otherwise.</returns>
        bool samples(_In_opt_ const source_type source) const;

        /// <summary>
        /// Registers <paramref name="source" /> to be sampled by this thread.
        /// </summary>
        /// <remarks>
        /// <para>The sampler thread will start if this is the first source to
        /// be registered.</para>
        /// </remarks>
        /// <param name="source">The source to be sampled. This must be a valid
        /// source that has a <see cref="async_sampling" /> configuration for
        /// the same interval as the sampler. The caller is responsible to make
        /// sure that the source lives as long as it is registered in the
        /// sampler. It is safe to register the same source multiple times, in
        /// which case nothing will happen.</param>
        /// <returns><c>*this</c>.</returns>
        basic_sampler& operator +=(_In_ source_type source);

        /// <summary>
        /// Unregisters <paramref name="source" /> from the sampler.
        /// </summary>
        /// <remarks>
        /// <para>The sampler thread is stopped if the source was the last
        /// source in the sampler. The method will not return until the sampler
        /// thread has exited.</para>
        /// </remarks>
        /// <param name="source">The source to be removed. It is safe to pass
        /// sources that are not sampled by the sampler, in which case nothing
        /// will happen.</param>
        /// <returns><c>*this</c>.</returns>
        basic_sampler& operator -=(_In_ source_type source);

        /// <summary>
        /// Indicates whether the sampler thread is currently processing any
        /// active sensor.
        /// </summary>
        /// <returns><c>true</c> if the sampler thread is running and processing
        /// at least one sensor, <c>false</c> otherwise.</returns>
        operator bool(void) const;

    private:

        /// <summary>
        /// The entry point of the sampler thread.
        /// </summary>
        void sample(void);

        mutable std::mutex _lock;
        interval_type _interval;
        std::set<source_type> _sources;
        std::thread _thread;
    };


    /// <summary>
    /// 
    /// </summary>
    typedef basic_sampler<async_measurement_data_source> sampler;

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */

#include "sampler.inl"
