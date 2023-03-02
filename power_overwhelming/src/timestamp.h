// <copyright file="timestamp.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cinttypes>

#if defined(_WIN32)
#include <Windows.h>
#endif /* defined(_WIN32) */

#include "power_overwhelming/power_overwhelming_api.h"
#include "power_overwhelming/timestamp_resolution.h"


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// The type used to store timestamps.
    /// </summary>
#if defined(_WIN32)
    typedef decltype(LARGE_INTEGER::QuadPart) timestamp_type;
#else  /* defined(_WIN32) */
    typedef std::int64_t value_type;
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
    inline POWER_OVERWHELMING_API decltype(LARGE_INTEGER::QuadPart) convert(
            const LARGE_INTEGER& fileTime,
            const timestamp_resolution resolution) {
        return convert(fileTime.QuadPart, resolution);
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
} /* namespace detail */

    /// <summary>
    /// Create a new timestamp using the specified resolution per tick.
    /// </summary>
    /// <param name="resolution">The resolution of the timestamp being returned.
    /// </param>
    /// <returns>The value of the current timestamp.</returns>
    /// <exception cref="std::invalid_argument">If a timestamp fo the requested
    /// <paramref name="resolution" /> cannot be created.</exception>
    timestamp_type POWER_OVERWHELMING_API create_timestamp(
        const timestamp_resolution resolution);

} /* namespace power_overwhelming */
} /* namespace visus */
