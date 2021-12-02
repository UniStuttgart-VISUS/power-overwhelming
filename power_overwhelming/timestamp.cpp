// <copyright file="timestamp.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "timestamp.h"

#include <stdexcept>


/*
 * visus::power_overwhelming::detail::convert
 */
std::int64_t visus::power_overwhelming::detail::convert(
        const std::int64_t fileTime,
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
 * visus::power_overwhelming::detail::create_timestamp
 */
std::int64_t visus::power_overwhelming::detail::create_timestamp(
        const timestamp_resolution resolution) {
    switch (resolution) {
        case timestamp_resolution::microseconds:
            return timestamp<timestamp_resolution::microseconds>::create();

        case timestamp_resolution::milliseconds:
            return timestamp<timestamp_resolution::milliseconds>::create();

        case timestamp_resolution::nanoseconds:
            return timestamp<timestamp_resolution::nanoseconds>::create();

        case timestamp_resolution::seconds:
            return timestamp<timestamp_resolution::seconds>::create();

        default:
            throw std::invalid_argument("The specified timestamp_resolution "
                "is unsupported.");
    }
}
