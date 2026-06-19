// <copyright file="timezone.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2024 - 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "timezone.h"


/// <summary>
/// Compare two <see cref="SYSTEMTIME" />s.
/// </summary>
static bool operator <(_In_ const SYSTEMTIME& lhs,
    _In_ const SYSTEMTIME& rhs) {
    FILETIME l, r;

    if (!::SystemTimeToFileTime(&lhs, &l)) {
        throw std::system_error(::GetLastError(), std::system_category());
    }

    if (!::SystemTimeToFileTime(&rhs, &r)) {
        throw std::system_error(::GetLastError(), std::system_category());
    }

    return (::CompareFileTime(&l, &r) < 0);
}


/*
 * visus::power_overwhelming::detail
 */
visus::power_overwhelming::timestamp::value_type
visus::power_overwhelming::detail::get_timezone_bias(void) {
#if defined(_WIN32)
    DYNAMIC_TIME_ZONE_INFORMATION tzi;
    if (::GetDynamicTimeZoneInformation(&tzi) == TIME_ZONE_ID_INVALID) {
        throw std::system_error(::GetLastError(), std::system_category());
    }

    // Apply the current year to the transition dates to compare to current
    // time.
    SYSTEMTIME now;
    GetSystemTime(&now);
    tzi.DaylightDate.wYear = now.wYear;
    tzi.StandardDate.wYear = now.wYear;

    // If the month is zero, no DST is defined. Otherwise, we assume to be in
    // DST and subsequently check whether this is actually the case.
    auto dst = ((tzi.DaylightDate.wMonth != 0)
        || (tzi.StandardDate.wMonth != 0));

    if (dst) {
        if (tzi.DaylightDate < tzi.StandardDate) {
            // DST start and end are in the same year.
            dst = ((tzi.DaylightDate < now) && (now < tzi.StandardDate));
        } else {
            // On the southern hemisphere, DST crosses the year boundary.
            dst = !((tzi.StandardDate < now) && (now < tzi.DaylightDate));
        }
    }

    auto retval = static_cast<timestamp::value_type>(tzi.Bias);

    if (dst) {
        retval += static_cast<timestamp::value_type>(tzi.DaylightBias);
    } else {
        retval += static_cast<timestamp::value_type>(tzi.StandardBias);
    }

    // Convert to seconds.
    retval *= 60LL;

#else /* defined(_WIN32) */
    static const time_t ts = 0;
    tm gmt;
    tm local;
    ::gmtime_r(&ts, &gmt);
    ::localtime_r(&ts, &local);
    timestamp::value_type retval = ::mktime(&gmt) - ::mktime(&local);
#endif /* defined(_WIN32) */

    // Convert seconds to 100 ns units.
    retval *= 1000LL * 10000LL;

    return retval;
}
