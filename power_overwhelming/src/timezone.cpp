// <copyright file="timezone.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2024 - 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "timezone.h"


#if defined(_WIN32)
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
#endif /* defined(_WIN32) */


/*
 * visus::power_overwhelming::detail
 */
visus::power_overwhelming::timestamp::value_type
visus::power_overwhelming::detail::get_timezone_bias(void) {
#if defined(_WIN32)
    timestamp::value_type retval = 0;
    DYNAMIC_TIME_ZONE_INFORMATION tzi;

    switch (::GetDynamicTimeZoneInformation(&tzi)) {
        case TIME_ZONE_ID_STANDARD:
            retval = tzi.Bias + tzi.StandardBias;
            break;

        case TIME_ZONE_ID_DAYLIGHT:
            retval = tzi.Bias + tzi.DaylightBias;
            break;

        default:
            retval = tzi.Bias;
            break;
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
