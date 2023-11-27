// <copyright file="timestamp.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "timestamp.h"

#include <cassert>
#include <ctime>
#include <system_error>


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// Answer how many 100ns units are in a quantity of one of the specified
    /// <paramref name="resolution" />.
    /// </summary>
    static constexpr timestamp_type hundred_ns(
            _In_ const timestamp_resolution resolution) noexcept {
        switch (resolution) {
            case timestamp_resolution::microseconds:
                return 10;

            case timestamp_resolution::milliseconds:
                return (10 * 1000);

            case timestamp_resolution::hundred_nanoseconds:
                return 1;

            case timestamp_resolution::seconds:
                return (10 * 1000 * 1000);

            default:
                assert(false);
                return 0;
        }
    }

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */



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

        // This would always overflow, so we do not support it any more.
        //case timestamp_resolution::nanoseconds:
        //    return duration_cast<nanoseconds>(ft).count();

        case timestamp_resolution::hundred_nanoseconds:
            return file_time;

        case timestamp_resolution::seconds:
            return duration_cast<seconds>(ft).count();

        default:
            return file_time;
    }
}


/*
 * visus::power_overwhelming::detail::convert
 */
visus::power_overwhelming::timestamp_type
visus::power_overwhelming::detail::convert(
        _In_ const timestamp_resolution src_resolution,
        _In_ const timestamp_type src,
        _In_ const timestamp_resolution dst_resolution) {
    using namespace std::chrono;

    if (src_resolution == dst_resolution) {
        return src;
    } else {
        auto sfactor = hundred_ns(src_resolution);
        auto dfactor = hundred_ns(dst_resolution);
        return (src * sfactor) / dfactor;
    }
}


/*
 * visus::power_overwhelming::detail::create_timestamp
 */
visus::power_overwhelming::timestamp_type
visus::power_overwhelming::detail::create_timestamp(
        _In_ const timestamp_resolution resolution) {
#if defined(_WIN32)
    FILETIME time;
    ::GetSystemTimePreciseAsFileTime(&time);
    return detail::convert(time, resolution);

#else /* defined(_WIN32) */
    return detail::convert(std::chrono::system_clock::now(), resolution);
#endif /* defined(_WIN32) */
}


/*
 * visus::power_overwhelming::detail::create_timestamp
 */
visus::power_overwhelming::timestamp_type
visus::power_overwhelming::detail::create_timestamp(
        _In_ const timestamp_resolution resolution,
        _In_ const int year,
        _In_ const int month,
        _In_ const int day,
        _In_ const int hours,
        _In_ const int minutes,
        _In_ const int seconds,
        _In_ const int millis,
        _In_ const int micros,
        _In_ const int nanos) {
    using namespace std::chrono;
    typedef duration<timestamp_type, std::nano> intermediate_duration;

    std::tm tm;
    ::ZeroMemory(&tm, sizeof(tm));
    tm.tm_year = year - 1900;
    tm.tm_mon = month - 1;
    tm.tm_mday = day;
    tm.tm_hour = hours;
    tm.tm_min = minutes;
    tm.tm_sec = seconds;
    tm.tm_isdst = -1;

    // Create the time point that represents the input.
#if defined(_WIN32)
    const auto time = ::_mkgmtime(&tm);
#else /* defined(_WIN32) */
    const auto time = ::timegm(&tm);
#endif /* defined(_WIN32) */

    const auto sysclk = system_clock::from_time_t(time);
    auto time_point = time_point_cast<intermediate_duration>(sysclk);

    // Add what cannot be represented in struct tm.
    time_point += std::chrono::milliseconds(millis);
    time_point += std::chrono::microseconds(micros);
    time_point += std::chrono::nanoseconds(nanos);

    // Convert the result.
    return convert(time_point, resolution);
}


/*
 * visus::power_overwhelming::detail::get_timezone_bias
 */
visus::power_overwhelming::timestamp_type
visus::power_overwhelming::detail::get_timezone_bias(void) {
#if defined(_WIN32)
    TIME_ZONE_INFORMATION tzi;
    if (::GetTimeZoneInformation(&tzi) == TIME_ZONE_ID_INVALID) {
        throw std::system_error(::GetLastError(), std::system_category());
    }

    return static_cast<timestamp_type>(tzi.Bias) * 60LL * 1000LL * 10000LL;
#else /* defined(_WIN32) */
    static const time_t ts = 0;
    tm gmt;
    tm local;
    ::gmtime_r(&ts, &gmt);
    ::localtime_r(&ts, &local);
    return ::mktime(&gmt) - ::mktime(&local);
#endif /* defined(_WIN32) */
}
