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
    /// <remarks>
    /// This API is only exposed for unit tests and should not be accessed by
    /// any other clients.
    /// </remarks>
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
    /// same 100ns resolution.
    /// </summary>
    /// <remarks>
    /// This API is only exposed for unit tests and should not be accessed by
    /// any other clients.
    /// </remarks>
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
    /// Convert a timestamp with the given <paramref name="src_resolution" /> to
    /// the specified <paramref name="dst_resolution" />.
    /// </summary>
    /// <remarks>
    /// This API is only exposed for unit tests and should not be accessed by
    /// any other clients.
    /// </remarks>
    /// <param name="src_resolution"></param>
    /// <param name="src"></param>
    /// <param name="dst_resolution"></param>
    /// <returns></returns>
    timestamp_type POWER_OVERWHELMING_API convert(
        _In_ const timestamp_resolution src_resolution,
        _In_ const timestamp_type src,
        _In_ const timestamp_resolution dst_resolution);

    /// <summary>
    /// Create a new timestamp using the specified resolution per tick.
    /// </summary>
    /// <remarks>
    /// This API is only exposed for unit tests and should not be accessed by
    /// any other clients.
    /// </remarks>
    /// <param name="resolution">The resolution of the timestamp being returned.
    /// </param>
    /// <returns>The value of the current timestamp.</returns>
    /// <exception cref="std::invalid_argument">If a timestamp fo the requested
    /// <paramref name="resolution" /> cannot be created.</exception>
    timestamp_type POWER_OVERWHELMING_API create_timestamp(
        _In_ const timestamp_resolution resolution);

    /// <summary>
    /// Create a new timestamp with the specified value.
    /// </summary>
    /// <remarks>
    /// <para>As timestamps in Power Overwhelming are UTC, the input is assumed
    /// to be UTC, too.</para>
    /// <para>This API is only exposed for unit tests and should not be accessed
    /// by any other clients.</para>
    /// </remarks>
    /// <param name="resolution">The resolution of the timestamp being returned.
    /// </param>
    /// <param name="year">The year of the timestamp.</param>
    /// <param name="month">The one-based month of the timestamp.</param>
    /// <param name="day">The one-based day of the timestamp.</param>
    /// <param name="hours">The hours in 24-hours format.</param>
    /// <param name="minutes">The minutes. This parameter defaults to zero.
    /// </param>
    /// <param name="seconds">The seconds. This parameter defaults to zero.
    /// </param>
    /// <param name="millis">The milliseconds. This parameter defaults to zero.
    /// </param>
    /// <param name="nanos">The nanoseconds. This parameter defaults to zero.
    /// </param>
    /// <param name="micros">The microseconds. This parameter defaults to zero.
    /// </param>
    /// <returns>The timestamp with the specified value in the given resolution.
    /// </returns>
    /// <exception cref="std::invalid_argument">If a timestamp fo the requested
    /// <paramref name="resolution" /> cannot be created.</exception>
    timestamp_type POWER_OVERWHELMING_API create_timestamp(
        _In_ const timestamp_resolution resolution,
        _In_ const int year,
        _In_ const int month,
        _In_ const int day,
        _In_ const int hours = 0,
        _In_ const int minutes = 0,
        _In_ const int seconds = 0,
        _In_ const int millis = 0,
        _In_ const int micros = 0,
        _In_ const int nanos = 0);

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */

#include "timestamp.inl"
