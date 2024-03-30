// <copyright file="timezone.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "timezone.h"


/*
 * visus::power_overwhelming::detail::get_timezone_bias
 */
visus::power_overwhelming::timestamp::value_type
visus::power_overwhelming::detail::get_timezone_bias(void) {
#if defined(_WIN32)
    TIME_ZONE_INFORMATION tzi;
    if (::GetTimeZoneInformation(&tzi) == TIME_ZONE_ID_INVALID) {
        throw std::system_error(::GetLastError(), std::system_category());
    }

    return static_cast<timestamp::value_type>(tzi.Bias)
        * 60LL * 1000LL * 10000LL;
#else /* defined(_WIN32) */
    static const time_t ts = 0;
    tm gmt;
    tm local;
    ::gmtime_r(&ts, &gmt);
    ::localtime_r(&ts, &local);
    return ::mktime(&gmt) - ::mktime(&local);
#endif /* defined(_WIN32) */
}
