// <copyright file="emi_sampler_context.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cassert>
#include <cinttypes>
#include <chrono>
#include <map>
#include <mutex>
#include <thread>
#include <unordered_map>
#include <vector>

#include "power_overwhelming/emi_sensor.h"
#include "power_overwhelming/measurement.h"

#include "emi_device_factory.h"
#include "thread_name.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /* Forward declarations. */
    struct emi_sensor_impl;


    /// <summary>
    /// A context represents a thread that handles sampling
    /// <see cref="emi_sensor" />s at a specific interval.
    /// </summary>
    struct emi_sampler_context {

        /// <summary>
        /// The type of the on-measurement callback and the user data pointer
        /// to be passed to it.
        /// </summary>
        typedef std::pair<measurement_callback, void *> callback_type;

        /// <summary>
        /// The type used to reference EMI devices.
        /// </summary>
        typedef emi_device_factory::device_type device_type;

        /// <summary>
        /// The type to express sampling intervals.
        /// </summary>
        typedef std::chrono::microseconds interval_type;

        /// <summary>
        /// The type of the sensor implementation, which must be the EMI sensor
        /// implementation.
        /// </summary>
        typedef emi_sensor_impl *sensor_type;

#if defined(_WIN32)
        /// <summary>
        /// The sampling interval.
        /// </summary>
        interval_type interval;

        /// <summary>
        /// A lock protecting the list of <see cref="sensors" />.
        /// </summary>
        std::mutex lock;

        /// <summary>
        /// The sensors to sample along with the callback to be invoked, grouped
        /// by their EMI device, such that we can sample all channels of each
        /// device at once.
        /// </summary>
        std::map<device_type, std::map<sensor_type, callback_type>> sensors;

        /// <summary>
        /// The thread sampling the <see cref="sensors" />.
        /// </summary>
        std::thread thread;
#endif /* defined(_WIN32) */

        /// <summary>
        /// Add the given sensor to the this context.
        /// </summary>
        bool add(sensor_type sensor, const measurement_callback callback,
            void *context);

        /// <summary>
        /// Remove the sensor from the context.
        /// </summary>
        bool remove(sensor_type sensor);

        /// <summary>
        /// Performs sampling in this context.
        /// </summary>
        void sample(void);

        /// <summary>
        /// Answer whether the given sensor is sampled in this context.
        /// </summary>
        bool samples(const sensor_type sensor);
    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
