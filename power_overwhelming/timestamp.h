// <copyright file="timestamp.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <chrono>
#include <cinttypes>

#if defined(_WIN32)
#include <Windows.h>
#endif /* defined(_WIN32) */

#include "power_overwhelming_api.h"
#include "timestamp_resolution.h"


namespace visus {
namespace power_overwhelming {

namespace detail {

    /// <summary>
    /// Allows for resolving an STL duration for the specified timestamp
    /// resolution.
    /// </summary>
    template<timestamp_resolution Resolution> struct duration_traits final { };

    template<>
    struct duration_traits<timestamp_resolution::microseconds> final {
        typedef std::chrono::microseconds type;
    };

    template<>
    struct duration_traits<timestamp_resolution::milliseconds> final {
        typedef std::chrono::milliseconds type;
    };

    template<> struct duration_traits<timestamp_resolution::nanoseconds> final {
        typedef std::chrono::nanoseconds type;
    };

    template<> struct duration_traits<timestamp_resolution::seconds> final {
        typedef std::chrono::seconds type;
    };

    /// <summary>
    /// The 100ns period defining the reolution of <see cref="FILETIME" />.
    /// </summary>
    typedef std::ratio<1, 10000000> filetime_period;

    /// <summary>
    /// The type used to store timestamps.
    /// </summary>
#if defined(_WIN32)
    typedef decltype(LARGE_INTEGER::QuadPart) timestamp_type;
#else  /* defined(_WIN32) */
    typedef std::int64_t value_type;
#endif /* defined(_WIN32) */

    /// <summary>
    /// Convert the given raw <see cref="FILETIME" /> to a timestamp of the
    /// specified resolution.
    /// </summary>
    /// <remarks>
    /// This API is only exposed for unit tests and should not be accessed by
    /// any other clients.
    /// </remarks>
    /// <param name="fileTime">The file time value in 100ns units.</param>
    /// <param name="resolution">The desired resolution of the timestamp.
    /// </param>
    /// <returns>The timestamp in the requested resolution.</returns>
    timestamp_type POWER_OVERWHELMING_API convert(const timestamp_type fileTime,
        const timestamp_resolution resolution);

#if defined(_WIN32)
    /// <summary>
    /// Convert the given raw <see cref="LARGE_INTEGER" /> to a timestamp of the
    /// specified resolution.
    /// </summary>
    /// <param name="fileTime">The file time value in 100ns units.</param>
    /// <param name="resolution">The desired resolution of the timestamp.
    /// </param>
    /// <returns>The timestamp in the requested resolution.</returns>
    inline decltype(LARGE_INTEGER::QuadPart) convert(
            const LARGE_INTEGER& fileTime,
            const timestamp_resolution resolution) {
        return convert(fileTime.QuadPart, resolution);
    }
#endif /* defined(_WIN32) */

#if defined(_WIN32)
    /// <summary>
    /// Convert the given raw <see cref="FILETIME" /> to a timestamp of the
    /// specified resolution.
    /// </summary>
    /// <param name="fileTime"></param>
    /// <returns></returns>
    inline decltype(LARGE_INTEGER::QuadPart) convert(
            const FILETIME& fileTime,
            const timestamp_resolution resolution) {
        LARGE_INTEGER largeInteger;
        largeInteger.HighPart = fileTime.dwHighDateTime;
        largeInteger.LowPart = fileTime.dwLowDateTime;
        return detail::convert(largeInteger.QuadPart, resolution);
    }
#endif /* defined(_WIN32) */

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
        /// The value type of the timestamp.
        /// </summary>
        typedef timestamp_type value_type;

        /// <summary>
        /// Samples system clock and converts its value into a timestamp.
        /// </summary>
        /// <returns>A new timestamp for the current point in time.</returns>
        static inline value_type create(void) {
#if defined(_WIN32)
            FILETIME time;
            ::GetSystemTimePreciseAsFileTime(&time);
            return create(time);
#else  /* defined(_WIN32) */
            return create<std::chrono::system_clock>();
#endif /* defined(_WIN32) */
        }

#if defined(_WIN32)
        /// <summary>
        /// Create a timestamp from a <see cref="FILETIME" />.
        /// </summary>
        /// <param name="fileTime"></param>
        /// <returns></returns>
        static inline constexpr value_type create(const FILETIME& fileTime) {
            return detail::convert(fileTime, Resolution);
        }
#endif /* defined(_WIN32) */

        /// <summary>
        /// Create a timestamp from a <see cref="std::time_point" />.
        /// </summary>
        /// <typeparam name="TTimePoint">The type of the time point representing
        /// the timestamp. This time point must come from a clock that allows for
        /// conversion from and to <see cref="time_t" />.</typeparam>
        /// <param name="timePoint"></param>
        /// <returns></returns>
        template<class TTimePoint>
        static value_type create(const TTimePoint& timePoint);

        /// <summary>
        /// Create a timestamp from a <see cref="std::clock" />.
        /// </summary>
        /// <typeparam name="TClock">The type of the clock to create the
        /// timestamp from. This clock must allow for conversion from and to
        /// <see cref="time_t" />.</typeparam>
        /// <returns></returns>
        template<class TClock> inline static value_type create(void) {
            return create(TClock::now());
        }
    };

    /// <summary>
    /// Create a new timestamp using the specified resolution per tick.
    /// </summary>
    /// <remarks>
    /// This API is only exposed for unit tests and should not be accessed by
    /// any other clients.
    /// </remarks>
    /// <param name="resolution"></param>
    /// <returns></returns>
    /// <exception cref="std::invalid_argument"></exception>
    visus::power_overwhelming::detail::timestamp_type POWER_OVERWHELMING_API
    create_timestamp(const timestamp_resolution resolution);

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */

#include "timestamp.inl"
