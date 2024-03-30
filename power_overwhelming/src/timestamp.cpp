// <copyright file="timestamp.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/timestamp.h"


/*
 * visus::power_overwhelming::detail::create
 */
visus::power_overwhelming::timestamp
visus::power_overwhelming::timestamp::create(
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
    typedef duration<value_type, std::nano> intermediate_duration;

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
    auto retval = timestamp::from_tm(tm);

    // Add what cannot be represented in struct tm.
    retval += std::chrono::milliseconds(millis);
    retval += std::chrono::microseconds(micros);
    retval += std::chrono::nanoseconds(nanos);

    // Constructor will implicitly convert for us.
    return retval;
}


/*
 * visus::power_overwhelming::detail::from_system_clock
 */
visus::power_overwhelming::timestamp
visus::power_overwhelming::timestamp::from_system_clock(void) {
    return std::chrono::system_clock::now();
}


/*
 * visus::power_overwhelming::timestamp::from_time_t
 */
visus::power_overwhelming::timestamp
visus::power_overwhelming::timestamp::from_time_t(_In_ const std::time_t t) {
    return std::chrono::system_clock::from_time_t(t);
}


/*
 * visus::power_overwhelming::detail::create
 */
visus::power_overwhelming::timestamp
visus::power_overwhelming::timestamp::from_tm(_In_ std::tm& t) {
#if defined(_WIN32)
    const auto time = ::_mkgmtime(&t);
#else /* defined(_WIN32) */
    const auto time = ::timegm(&t);
#endif /* defined(_WIN32) */

    return std::chrono::system_clock::from_time_t(time);
}


/*
 * visus::power_overwhelming::timestamp::zero
 */
const visus::power_overwhelming::timestamp
visus::power_overwhelming::timestamp::zero(0);


/*
 * visus::power_overwhelming::timestamp::unix_offset
 */
const visus::power_overwhelming::timestamp::value_type
visus::power_overwhelming::timestamp::tick_rate;


/*
 * visus::power_overwhelming::timestamp::unix_offset
 */
const visus::power_overwhelming::timestamp::value_type
visus::power_overwhelming::timestamp::unix_offset;
