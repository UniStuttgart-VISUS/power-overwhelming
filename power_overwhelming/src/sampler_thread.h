// <copyright file="sampler_thread.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <chrono>
#include <functional>
#include <memory>
#include <stdexcept>
#include <sstream>
#include <string>
#include <thread>
#include <typeinfo>
#include <vector>

#include "sampler_context.h"
#include "thread_name.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// A utility class that manages threads for asynchronously sampling sensors
    /// that do not have an asynchronous API themselves.
    /// </summary>
    /// <remarks>
    /// <para>The sampler class is not working on the <see cref="sensor" />
    /// interface, but on the sensor implementation, because the abstract sensor
    /// class might be disposed whereas the sensor implementation used in the
    /// PIMPL pattern is guaranteed to live on until the last sensor was
    /// destroyed. Implementors should make sure that the sensor implementation
    /// unregisters itself from the sampler in its destructor to make sure that
    /// there are no dangling pointers in the sampler.</para>
    /// </remarks>
    /// <typeparam name="TContext">The type of the sampler context that
    /// implements the per-sensor sampling functionality. The interface must be
    /// like <see cref="default_sampler_context" />.</typeparam>
    template<class TContext> class basic_sampler_thread final {

    public:

        /// <summary>
        /// The type of the context the sampler thread gets its data from.
        /// </summary>
        /// <remarks>
        /// <para>This class must implement the interface defined by
        /// <see cref="basic_sampler_context" />, ie it must provide the actual
        /// source of the samples and the configuration of the sampler thread.
        /// </para>
        /// </remarks>
        typedef TContext context_type;

        /// <summary>
        /// The type to express sampling intervals.
        /// </summary>
        typedef std::chrono::duration<async_sampling::microseconds_type,
            std::micro> interval_type;

        /// <summary>
        /// Finalises the instance.
        /// </summary>
        ~basic_sampler_thread(void);

        /// <summary>
        /// Add a new sensor to be sampled.
        /// </summary>
        /// <param name="sensor"></param>
        /// <param name="callback"></param>
        /// <param name="user_context"></param>
        /// <param name="interval"></param>
        /// <returns></returns>
        bool add(sensor_type sensor, const measurement_callback callback,
            void *user_context, const interval_type interval);

        /// <summary>
        /// Remove the sensor from the list of sensors being sampled by this
        /// sampler.
        /// </summary>
        /// <param name="sensor">The sensor to be removed. If is safe to pass
        /// <c>nullptr</c>, in which case nothing will happen.</param>
        /// <returns><c>true</c> if the sensor has been removed, <c>false</c> if
        /// it has not been sampled in the first place.</returns>
        bool remove(sensor_type sensor);

        /// <summary>
        /// Answer whether this sampler samples the specified sensor at any
        /// interval.
        /// </summary>
        /// <param name="sensor">The sensor to search. It is safe to pass
        /// <c>nullptr</c>, in which case the result will always be
        /// <c>false</c>.</param>
        /// <returns><c>true</c> if the sensor was found in the sampler,
        /// <c>false</c> otherwise.</returns>
        bool samples(sensor_type sensor) const;

        /// <summary>
        /// Indicates whether the sampler thread is currently processing any
        /// active sensor.
        /// </summary>
        /// <returns><c>true</c> if the sampler thread is running and processing
        /// at least one sensor, <c>false</c> otherwise.</returns>
        bool samples(void) const;

    private:

        /// <summary>
        /// Sample all <see cref="_contexts" />.
        /// </summary>
        /// <remarks>
        /// This is the method that is executed in the sampler
        /// <see cref="_thread" />. It will continue until it discovers that
        /// <see cref="_contexts" /> is empty. Afterwards, a new thread needs to
        /// be started if sensors are re-added.
        /// </remarks>
        void sample(void);

        /// <summary>
        /// The list of contexts sampled by this thread.
        /// </summary>
        std::vector<context_type> _contexts;

        /// <summary>
        /// The sampling interval of <see cref="_thread" />.
        /// </summary>
        interval_type _interval;

        /// <summary>
        /// A lock for protecting <see cref="_contexts" />.
        /// </summary>
        mutable std::mutex _lock;

        /// <summary>
        /// The sampler thread processing the configured
        /// <see cref="_contexts" />.
        /// </summary>
        std::thread _thread;
    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */

#include "sampler_thread.inl"
