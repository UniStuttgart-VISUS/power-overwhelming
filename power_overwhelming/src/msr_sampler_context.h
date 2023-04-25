// <copyright file="msr_sampler_context.h" company="Visualisierungsinstitut der Universität Stuttgart">
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

#include "power_overwhelming/cpu_affinity.h"
#include "power_overwhelming/msr_sensor.h"
#include "power_overwhelming/measurement.h"

#include "msr_device_factory.h"
#include "thread_name.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /* Forward declarations. */
    struct msr_sensor_impl;


    /// <summary>
    /// A context represents a thread that handles sampling
    /// <see cref="msr_sensor" />s at a specific interval.
    /// </summary>
    struct msr_sampler_context {

        /// <summary>
        /// The per-sensor information we need to know to invoke the right
        /// callback with the right input.
        /// </summary>
        struct sensor_config {
            measurement_callback callback;
            void *context;
            timestamp_resolution resolution;

            inline sensor_config(_In_ const timestamp_resolution resolution,
                    _In_ measurement_callback callback,
                    _In_opt_ void *context)
                : callback(callback),
                    context(context),
                    resolution(resolution) { }
        };

        /// <summary>
        /// The type used to reference RAPL MSR devices.
        /// </summary>
        typedef msr_device_factory::device_type device_type;

        /// <summary>
        /// The type to express sampling intervals.
        /// </summary>
        typedef std::chrono::microseconds interval_type;

        /// <summary>
        /// The type of the sensor implementation, which must be the MSR sensor
        /// implementation.
        /// </summary>
        typedef msr_sensor_impl *sensor_type;

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
        /// by their MSR device, such that we can sample all channels of each
        /// device at once.
        /// </summary>
        std::map<device_type, std::map<sensor_type, sensor_config>> sensors;

        /// <summary>
        /// The thread sampling the <see cref="sensors" />.
        /// </summary>
        std::thread thread;

        /// <summary>
        /// Add the given sensor to the this context.
        /// </summary>
        bool add(_In_ sensor_type sensor,
            _In_ const timestamp_resolution timestamp_resolution,
            _In_ const measurement_callback callback,
            _In_opt_ void *context);

        // TODO: remove once API changed to include resolution.
        inline bool add(sensor_type sensor, const measurement_callback callback, void *context) {
            return this->add(sensor, timestamp_resolution::milliseconds, callback, context);
        }

        /// <summary>
        /// Remove the sensor from the context.
        /// </summary>
        bool remove(_In_ sensor_type sensor);

        /// <summary>
        /// Performs sampling in this context.
        /// </summary>
        void sample(void);

        /// <summary>
        /// Answer whether the given sensor is sampled in this context.
        /// </summary>
        bool samples(_In_ const sensor_type sensor);
    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
