// <copyright file="sampler.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <functional>
#include <memory>
#include <stdexcept>
#include <vector>

#include "default_sampler_context.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// A utility class that manages threads for asynchronously sampling sensors
    /// that do not have an asynchronous API themselves.
    /// </summary>
    /// <remarks>
    /// The sampler is not working on the <see cref="sensor" /> interface, but
    /// on the sensor implementation, because the abstract sensor class might be
    /// disposed whereas the sensor implementation used in the PIMPL pattern is
    /// guaranteed to live on until the last sensor was destroyed. Implementors
    /// should make sure that the sensor implementation unregisters itself from
    /// the sampler in its destructor to make sure that there are no dangling
    /// pointers in the sampler.
    /// </remarks>
    /// <typeparam name="TContext">The type of the sampler context that
    /// implements the per-sensor sampling functionality. The interface must be
    /// like <see cref="default_sampler_context" />.</typeparam>
    template<class TContext> class sampler final {

    public:

        /// <summary>
        /// The type of the sampler context that implements the per-sensor
        /// sampling functionality.
        /// </summary>
        typedef TContext context_type;

        /// <summary>
        /// The type to express sampling intervals.
        /// </summary>
        typedef typename TContext::interval_type interval_type;

        /// <summary>
        /// The type of the sensor implementation to be sampled by this sampler.
        /// </summary>
        typedef typename TContext::sensor_type sensor_type;

        /// <summary>
        /// Finalises the instance.
        /// </summary>
        ~sampler(void);

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
        /// Indicates whether the sampler is currently processing any active
        /// sensor.
        /// </summary>
        /// <returns><c>true</c> if there is any sensor to be sampled in the
        /// sampler, <c>false</c> otherwise.</returns>
        bool samples(void) const;

    private:

        /// <summary>
        /// The list of sampling threads.
        /// </summary>
        std::vector<std::unique_ptr<context_type>> _contexts;

        /// <summary>
        /// A lock for protecting <see cref="_contexts" />.
        /// </summary>
        mutable std::mutex _lock;
    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */

#include "sampler.inl"
