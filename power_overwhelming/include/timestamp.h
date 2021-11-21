// <copyright file="timestamp.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <chrono>
#include <cinttypes>

#include "timestamp_resolution.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// Traits class that resolves the target ticks for the given resolution.
    /// </summary>
    template<timestamp_resolution Resolution>
    struct timestamp_resolution_traits { };

    /// <summary>
    /// Specialisation for milliseconds.
    /// </summary>
    template<>
    struct timestamp_resolution_traits<timestamp_resolution::milliseconds> {
        typedef std::chrono::milliseconds type;
    };

    /// <summary>
    /// Specialisation for nanoseconds.
    /// </summary>
    template<>
    struct timestamp_resolution_traits<timestamp_resolution::nanoseconds> {
        typedef std::chrono::nanoseconds type;
    };

    /// <summary>
    /// Specialisation for seconds.
    /// </summary>
    template<>
    struct timestamp_resolution_traits<timestamp_resolution::seconds> {
        typedef std::chrono::seconds type;
    };


    /// <summary>
    /// Implements a generator for timestamps from the STL high-resolution
    /// clock.
    /// </summary>
    /// <typeparam name="Resolution">The temporal resolution of the value being
    /// returned.</typeparam>
    template<timestamp_resolution Resolution> struct timestamp {

        /// <summary>
        /// The duration type of the specified
        /// <typeparamref name="Resolution" />.
        /// </summary>
        typedef typename timestamp_resolution_traits<Resolution>::type
            duration_type;

        /// <summary>
        /// The value type of the time stamp.
        /// </summary>
        typedef typename duration_type::rep value_type;

        /// <summary>
        /// Samples the high-resolution clock and converts its value into a
        /// timestamp.
        /// </summary>
        /// <returns>A new timestamp for the current point in time.</returns>
        static inline value_type create(void) {
            const auto n = std::chrono::high_resolution_clock::now();
            const auto v = n.time_since_epoch();
            return std::chrono::duration_cast<duration_type>(v).count();
        }
    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
