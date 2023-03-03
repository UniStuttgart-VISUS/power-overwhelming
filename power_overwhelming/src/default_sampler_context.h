// <copyright file="default_sampler_context.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cassert>
#include <chrono>
#include <map>
#include <mutex>
#include <thread>
#include <vector>

#include "power_overwhelming/measurement.h"

#include "thread_name.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// A context represents a thread that handles a specific sampling
    /// interval.
    /// </summary>
    /// <remarks>
    /// This template is to be used as parameter to <see cref="sampler" />. The
    /// policy-based design ensures that sensors requiring a special way of
    /// sampling can provide this by means of their own context.
    /// </remarks>
    /// <typeparam name="TSensorImpl">The type of the sensor implementation
    /// to be sampled by this sampler. This type must expose a synchronous
    /// <c>sample</c> method to be called by the sampling thread.</typeparam>
    template<class TSensorImpl>
    struct default_sampler_context {

        /// <summary>
        /// The type of the on-measurement callback and the user data pointer
        /// to be passed to it.
        /// </summary>
        typedef std::pair<measurement_callback, void *> callback_type;

        /// <summary>
        /// The type to express sampling intervals.
        /// </summary>
        typedef std::chrono::microseconds interval_type;

        /// <summary>
        /// The type of the sensor implementation to be sampled by this sampler.
        /// </summary>
        typedef TSensorImpl *sensor_type;

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
        std::map<sensor_type, callback_type> sensors;

        /// <summary>
        /// The thread sampling the <see cref="sensors" />.
        /// </summary>
        /// <remarks>
        /// The <see cref="sampler" /> will make sure that the thread exited
        /// before destroying the context. The context does not need to join
        /// the thread on destruction.
        /// </remarks>
        std::thread thread;

        /// <summary>
        /// Add the given sensor to the this context.
        /// </summary>
        /// <param name="sensor"></param>
        /// <param name="callback"></param>
        /// <param name="context"></param>
        /// <returns></returns>
        bool add(sensor_type sensor, const measurement_callback callback,
            void *context);

        /// <summary>
        /// Remove the sensor from the context.
        /// </summary>
        /// <param name="sensor">The sensor to be removed.</param>
        /// <returns><c>true</c> if the sensor has been removed, <c>false</c> if
        /// it has not been sampled in the first place.</returns>
        inline bool remove(sensor_type sensor) {
            std::lock_guard<decltype(this->lock)> l(this->lock);
            return (this->sensors.erase(sensor) > 0);
        }

        /// <summary>
        /// Performs sampling in this context.
        /// </summary>
        /// <remarks>
        /// <para>This is the sampling method running in <see cref="thread" />.
        /// </para>
        /// <para>The <see cref="add" /> method shall start the thread if
        /// adding the first sensor to <see cref="sensors" />.</para>
        /// <para>This method periodically samples all sensors in
        /// <see cref="sensors" /> as long as there is any callback left in
        /// the map. If <see cref="sensors" /> is empty, the method will exit.
        /// </para>
        /// </remarks>
        void sample(void);

        /// <summary>
        /// Answer whether the given sensor is sampled in this context.
        /// </summary>
        /// <param name="sensor">The sensor to be tested.</param>
        /// <returns><c>true</c> if the sensor is in the context, <c>false</c>
        /// otherwise.</returns>
        inline bool samples(const sensor_type sensor) {
            std::lock_guard<decltype(this->lock)> l(this->lock);
            return (this->sensors.find(sensor) != this->sensors.end());
        }
    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */

#include "default_sampler_context.inl"
