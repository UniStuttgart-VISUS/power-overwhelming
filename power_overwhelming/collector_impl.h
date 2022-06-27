// <copyright file="collector_impl.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/sensor.h"

#include <atomic>
#include <chrono>
#include <fstream>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// Private data container for <see cref="collector" />.
    /// </summary>
    struct collector_impl final {

        /// <summary>
        /// Processes asynchronously created measurements.
        /// </summary>
        /// <param name="m"></param>
        /// <param name="context"></param>
        static void on_measurement(const measurement& m, void *context);

        /// <summary>
        /// Buffers the measurements until a marker is reached.
        /// </summary>
        std::vector<measurement> buffer;

        /// <summary>
        /// Indicates whether a have a valid marker.
        /// </summary>
        /// <remarks>
        /// This flag serves two purposes: first, it can be set and read
        /// asynchronously, and second, it allows empty strings as valid
        /// markers.
        /// </remarks>
        std::atomic<bool> have_marker;

        /// <summary>
        /// The lock protecting the buffer.
        /// </summary>
        std::mutex lock;

        /// <summary>
        /// The current marker value.
        /// </summary>
        std::wstring marker;

        /// <summary>
        /// Indicates whether the collector thread should continue running.
        /// </summary>
        std::atomic<bool> running;

        /// <summary>
        /// The desired sampling interval.
        /// </summary>
        std::chrono::microseconds sampling_interval;

        /// <summary>
        /// Indicates whether collecting sensor data requires a marker being
        /// set.
        /// </summary>
        bool require_marker;

        /// <summary>
        /// The list of sensors.
        /// </summary>
        std::vector<std::unique_ptr<sensor>> sensors;

        /// <summary>
        /// The output stream for the results.
        /// </summary>
        std::wofstream stream;

        /// <summary>
        /// The resolution of the timestamps being created.
        /// </summary>
        timestamp_resolution timestamp_resolution;

        /// <summary>
        /// The collector thread.
        /// </summary>
        std::thread thread;

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        collector_impl(void);

        /// <summary>
        /// Finalises the instance.
        /// </summary>
        ~collector_impl(void);

        /// <summary>
        /// Answer whether data can be written to the buffer.
        /// </summary>
        /// <returns></returns>
        bool can_buffer(void) const;

        /// <summary>
        /// Runs in <see cref="thread" /> and collects the data.
        /// </summary>
        void collect(void);

        /// <summary>
        /// Write data from <see cref="buffer" /> to <see cref="stream" /> and
        /// clear the buffer.
        /// </summary>
        /// <remarks>
        /// The caller must hold <see cref="lock" />!
        /// </remarks>
        void flush_buffer(void);

        /// <summary>
        /// Starts the collector thread if not running.
        /// </summary>
        void start(void);

        /// <summary>
        /// Stops the collector thread.
        /// </summary>
        void stop(void);
    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
