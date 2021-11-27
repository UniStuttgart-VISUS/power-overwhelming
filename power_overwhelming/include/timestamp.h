// <copyright file="timestamp.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <chrono>

#include <Windows.h>

#include "timestamp_resolution.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// The 100ns period defining the reolution of <see cref="FILETIME" />.
    /// </summary>
    typedef std::ratio<1, 10000000> filetime_period;

    /// <summary>
    /// Convert the given raw <see cref="FILETIME" /> to a timestamp of the
    /// specified resolution.
    /// </summary>
    /// <param name="fileTime">The file time value in 100ns units.</param>
    /// <param name="resolution">The desired resolution of the timestamp.
    /// </param>
    /// <returns>The timestamp in the requested resolution.</returns>
    static inline decltype(LARGE_INTEGER::QuadPart) convert(
            const decltype(LARGE_INTEGER::QuadPart) fileTime,
            const timestamp_resolution resolution) {
        using namespace std::chrono;
        duration<decltype(fileTime), filetime_period> ft(fileTime);

        switch (resolution) {
            case timestamp_resolution::microseconds:
                return duration_cast<microseconds>(ft).count();

            case timestamp_resolution::milliseconds:
                return duration_cast<milliseconds>(ft).count();

            case timestamp_resolution::nanoseconds:
                return duration_cast<nanoseconds>(ft).count();

            case timestamp_resolution::seconds:
                return duration_cast<seconds>(ft).count();

            default:
                return fileTime;
        }
    }

    /// <summary>
    /// Convert the given raw <see cref="LARGE_INTEGER" /> to a timestamp of the
    /// specified resolution.
    /// </summary>
    /// <param name="fileTime">The file time value in 100ns units.</param>
    /// <param name="resolution">The desired resolution of the timestamp.
    /// </param>
    /// <returns>The timestamp in the requested resolution.</returns>
    static inline decltype(LARGE_INTEGER::QuadPart) convert(
            const LARGE_INTEGER& fileTime,
            const timestamp_resolution resolution) {
        return convert(fileTime.QuadPart, resolution);
    }

    /// <summary>
    /// Convert the given raw <see cref="FILETIME" /> to a timestamp of the
    /// specified resolution.
    /// </summary>
    /// <param name="fileTime"></param>
    /// <returns></returns>
    static inline decltype(LARGE_INTEGER::QuadPart) convert(
            const FILETIME& fileTime,
            const timestamp_resolution resolution) {
        LARGE_INTEGER largeInteger;
        largeInteger.HighPart = fileTime.dwHighDateTime;
        largeInteger.LowPart = fileTime.dwLowDateTime;
        return detail::convert(largeInteger.QuadPart, resolution);
    }

    /// <summary>
    /// Implements a generator for timestamps from
    /// <see cref="GetSystemTimePreciseAsFileTime" />.
    /// </summary>
    /// <remarks>
    /// It seems that AMD is using this time source for its timestamps, so we
    /// need to create ours in a compatible way. Furthermore, Microsoft
    /// recommends using this API for retrieving precise timestamps that are
    /// related to the wall clock time.
    /// </remarks>
    /// <typeparam name="Resolution">The temporal resolution of the value being
    /// returned.</typeparam>
    template<timestamp_resolution Resolution> struct timestamp {

        /// <summary>
        /// The value type of the time stamp.
        /// </summary>
        typedef decltype(LARGE_INTEGER::QuadPart) value_type;

        /// <summary>
        /// Samples system clock and converts its value into atimestamp.
        /// </summary>
        /// <returns>A new timestamp for the current point in time.</returns>
        static inline value_type create(void) {
            FILETIME time;
            ::GetSystemTimePreciseAsFileTime(&time);
            return create(time);
        }

        /// <summary>
        /// Create a timestamp from a <see cref="FILETIME" />.
        /// </summary>
        /// <param name="fileTime"></param>
        /// <returns></returns>
        static inline constexpr value_type create(const FILETIME& fileTime) {
            return detail::convert(fileTime, Resolution);
        }
    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
