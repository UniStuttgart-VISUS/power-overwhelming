// <copyright file="timestamp.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "timestamp.h"


/*
 * visus::power_overwhelming::detail::convert
 */
visus::power_overwhelming::timestamp_type
visus::power_overwhelming::detail::convert(
        const timestamp_type file_time,
        const timestamp_resolution resolution) {
    using namespace std::chrono;
    duration<decltype(file_time), filetime_period> ft(file_time);

    switch (resolution) {
        case timestamp_resolution::microseconds:
            return duration_cast<microseconds>(ft).count();

        case timestamp_resolution::milliseconds:
            return duration_cast<milliseconds>(ft).count();

        case timestamp_resolution::nanoseconds:
            return duration_cast<nanoseconds>(ft).count();

        case timestamp_resolution::hundred_nanoseconds:
            return file_time;

        case timestamp_resolution::seconds:
            return duration_cast<seconds>(ft).count();

        default:
            return file_time;
    }
}


/*
 * visus::power_overwhelming::detail::create_timestamp
 */
visus::power_overwhelming::timestamp_type
visus::power_overwhelming::detail::create_timestamp(
        const timestamp_resolution resolution) {
#if defined(_WIN32)
    FILETIME time;
    ::GetSystemTimePreciseAsFileTime(&time);
    return detail::convert(time, resolution);

#else /* defined(_WIN32) */
    return detail::convert(std::chrono::system_clock::now(), resolution);
#endif /* defined(_WIN32) */
}
