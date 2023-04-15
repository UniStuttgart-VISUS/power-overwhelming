// <copyright file="timestamp.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "timestamp.h"

#include <stdexcept>

#include "filetime_period.h"


/*
 * visus::power_overwhelming::detail::convert
 */
visus::power_overwhelming::timestamp_type
visus::power_overwhelming::detail::convert(
        const timestamp_type fileTime,
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


/*
 * visus::power_overwhelming::create_timestamp
 */
visus::power_overwhelming::timestamp_type
visus::power_overwhelming::create_timestamp(
        const timestamp_resolution resolution) {
#if defined(_WIN32)
    FILETIME time;
    ::GetSystemTimePreciseAsFileTime(&time);
    return detail::convert(time, resolution);

#else /* defined(_WIN32) */
    using namespace std::chrono;

    // The offset of the FILETIME epoch to the UNIX epoch.
    const auto dz = duration<timestamp_type,
        detail::filetime_period>(11644473600000LL);

    // Find out what the difference between the time point and the UNIX
    // epoch is. Because we cannot rely on the epoch of the STL clock being the
    // UNIX epoch (until C++ 20), use time_t, which is guaranteed to represent
    // the UNIX epoch.
    auto dt = system_clock::now() - system_clock::from_time_t(0);

    // Transform the origin of the timestamp clock to the origin of FILETIME.
    switch (resolution) {
        case timestamp_resolution::microseconds:
            return duration_cast<microseconds>(dt + dz).count();

        case timestamp_resolution::milliseconds:
            return duration_cast<milliseconds>(dt + dz).count();

        // TODO: This overflows, so we do not support it.
        //case timestamp_resolution::nanoseconds:
        //    return duration_cast<nanoseconds>(dt + dz).count();

        case timestamp_resolution::seconds:
            return duration_cast<seconds>(dt + dz).count();

        default:
            throw std::invalid_argument("The specified timestamp_resolution "
                "is unsupported.");
    }
#endif /* defined(_WIN32) */
}
