// <copyright file="sampler.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cassert>
#include <chrono>
#include <map>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <thread>
#include <vector>

#include "power_overwhelming/measurement.h"


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
    /// <typeparam name="TSensorImpl">The type of the sensor implementation to
    /// be sampled by this sampler. This type must expose a synchronous
    /// <c>sample</c> method to be called by the sampling thread.</typeparam>
    template<class TSensorImpl> class sampler final {

    public:

        /// <summary>
        /// The type to express sampling intervals.
        /// </summary>
        typedef std::chrono::microseconds interval_type;

        /// <summary>
        /// The type of the sensor implementation to be sampled by this sampler.
        /// </summary>
        typedef TSensorImpl *sensor_type;

        /// <summary>
        /// Finalises the instance.
        /// </summary>
        ~sampler(void);

        bool add(sensor_type sensor, const measurement_callback callback,
            const interval_type interval);

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
        /// Answer whether this sampler samples the specified sensor ad any
        /// interval.
        /// </summary>
        /// <param name="sensor">The sensor to search. It is safe to pass
        /// <c>nullptr</c>, in which case the result will always be
        /// <c>false</c>.</param>
        /// <returns><c>true</c> if the sensor was found in the sampler,
        /// <c>false</c> otherwise.</returns>
        bool samples(sensor_type sensor);

    private:

        /// <summary>
        /// A context represents a thread that handles a specific sampling
        /// interval.
        /// </summary>
        struct context {

            /// <summary>
            /// The sampling interval.
            /// </summary>
            interval_type interval;

            /// <summary>
            /// A lock protecting the list of <see cref="sensors" />.
            /// </summary>
            std::mutex lock;

            /// <summary>
            /// The sensors to sample along with the callback to be invoked.
            /// </summary>
            std::map<sensor_type, measurement_callback> sensors;

            /// <summary>
            /// The thread sampling the <see cref="sensors" />.
            /// </summary>
            std::thread thread;

            /// <summary>
            /// Add the given sensor to the this context.
            /// </summary>
            /// <param name="sensor"></param>
            /// <param name="callback"></param>
            /// <returns></returns>
            bool add(sensor_type sensor, const measurement_callback callback);

            /// <summary>
            /// Performs sampling in this context.
            /// </summary>
            void sample(void);
        };

        /// <summary>
        /// The list of sampling threads.
        /// </summary>
        std::vector<std::unique_ptr<context>> _contexts;

        /// <summary>
        /// A lock for protecting <see cref="_contexts" />.
        /// </summary>
        std::mutex _lock;
    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */

#include "sampler.inl"
