// <copyright file="timestamp.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <chrono>
#include <cinttypes>
#include <stdexcept>

#if defined(_WIN32)
#include <Windows.h>
#endif /* defined(_WIN32) */

#include "power_overwhelming/power_overwhelming_api.h"
#include "power_overwhelming/timestamp_resolution.h"

#include "filetime_period.h"


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// The type used to store timestamps.
    /// </summary>
#if defined(_WIN32)
    typedef decltype(LARGE_INTEGER::QuadPart) timestamp_type;
#else  /* defined(_WIN32) */
    typedef std::int64_t timestamp_type;
#endif /* defined(_WIN32) */

namespace detail {

    /// <summary>
    /// Convert the given raw <see cref="FILETIME" /> to a timestamp of the
    /// specified resolution.
    /// </summary>
    /// <remarks>
    /// This API is only exposed for unit tests and should not be accessed by
    /// any other clients.
    /// </remarks>
    /// <param name="file_time">The file time value in 100ns units.</param>
    /// <param name="resolution">The desired resolution of the timestamp.
    /// </param>
    /// <returns>The timestamp in the requested resolution.</returns>
    timestamp_type POWER_OVERWHELMING_API convert(
        const timestamp_type file_time,
        const timestamp_resolution resolution);

#if defined(_WIN32)
    /// <summary>
    /// Convert the given raw <see cref="LARGE_INTEGER" /> to a timestamp of the
    /// specified resolution.
    /// </summary>
    /// <param name="file_time">The file time value in 100ns units.</param>
    /// <param name="resolution">The desired resolution of the timestamp.
    /// </param>
    /// <returns>The timestamp in the requested resolution.</returns>
    inline POWER_OVERWHELMING_API decltype(LARGE_INTEGER::QuadPart) convert(
            const LARGE_INTEGER& file_time,
            const timestamp_resolution resolution) {
        return convert(file_time.QuadPart, resolution);
    }
#endif /* defined(_WIN32) */

#if defined(_WIN32)
    /// <summary>
    /// Convert the given raw <see cref="FILETIME" /> to a 64-bit integer of the
    /// same 100ns resolution
    /// </summary>
    /// <param name="fileTime"></param>
    /// <returns></returns>
    inline POWER_OVERWHELMING_API decltype(LARGE_INTEGER::QuadPart) convert(
            const FILETIME& fileTime) {
        LARGE_INTEGER largeInteger;
        largeInteger.HighPart = fileTime.dwHighDateTime;
        largeInteger.LowPart = fileTime.dwLowDateTime;
        return largeInteger.QuadPart;
    }
#endif /* defined(_WIN32) */

#if defined(_WIN32)
    /// <summary>
    /// Convert the given raw <see cref="FILETIME" /> to a timestamp of the
    /// specified resolution.
    /// </summary>
    /// <param name="fileTime"></param>
    /// <returns></returns>
    inline POWER_OVERWHELMING_API decltype(LARGE_INTEGER::QuadPart) convert(
            const FILETIME& fileTime,
            const timestamp_resolution resolution) {
        return convert(convert(fileTime), resolution);
    }
#endif /* defined(_WIN32) */

    /// <summary>
    /// Convert an STL duration into ticks of the specified resolution.
    /// </summary>
    /// <typeparam name="TRep"></typeparam>
    /// <typeparam name="TPeriod"></typeparam>
    /// <param name="dur"></param>
    /// <param name="resolution"></param>
    /// <returns></returns>
    template<class TRep, class TPeriod>
    timestamp_type convert(_In_ const std::chrono::duration<TRep, TPeriod> dur,
        _In_ const timestamp_resolution resolution);

    /// <summary>
    /// Convert an STL time point to a time stamp.
    /// </summary>
    /// <typeparam name="TDuration"></typeparam>
    /// <param name="timestamp">The STL time point to convert.</param>
    /// <param name="resolution">The resolution of the timestamp being returned.
    /// </param>
    /// <returns>The value of the current timestamp.</returns>
    /// <exception cref="std::invalid_argument">If a timestamp fo the requested
    /// <paramref name="resolution" /> cannot be created.</exception>
    template<class TDuration> timestamp_type convert(
        _In_ const std::chrono::time_point<std::chrono::system_clock,
            TDuration>& timestamp,
        _In_ const timestamp_resolution resolution);

    /// <summary>
    /// Create a new timestamp using the specified resolution per tick.
    /// </summary>
    /// <param name="resolution">The resolution of the timestamp being returned.
    /// </param>
    /// <returns>The value of the current timestamp.</returns>
    /// <exception cref="std::invalid_argument">If a timestamp fo the requested
    /// <paramref name="resolution" /> cannot be created.</exception>
    timestamp_type POWER_OVERWHELMING_API create_timestamp(
        _In_ const timestamp_resolution resolution);

} /* namespace detail */

    /// <summary>
    /// Convert a timestamp of the specified resolution into an STL time point.
    /// </summary>
    /// <typeparam name="TDuration">The unit of duration for measuring the time
    /// since the clock's epoch.</typeparam>
    /// <param name="timestamp">The timestamp to be converted.</param>
    /// <param name="resolution">The resolution of the timestamp provided as
    /// the <pararmef name="timestamp" /> parameter.</param>
    /// <returns>The STL time point representing the timestamp.</returns>
    template<class TDuration>
    std::chrono::time_point<std::chrono::system_clock, TDuration> to_time_point(
        _In_ const timestamp_type timestamp,
        _In_ const timestamp_resolution resolution);

} /* namespace power_overwhelming */
} /* namespace visus */

#include "timestamp.inl"
