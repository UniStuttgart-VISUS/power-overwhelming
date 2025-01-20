// <copyright file="timestamp.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/timestamp.h"

#include "zero_memory.h"


/*
 * PWROWG_NAMESPACE::detail::create
 */
PWROWG_NAMESPACE::timestamp
PWROWG_NAMESPACE::timestamp::create(
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
 * PWROWG_NAMESPACE::detail::from_system_clock
 */
PWROWG_NAMESPACE::timestamp
PWROWG_NAMESPACE::timestamp::from_system_clock(void) {
    return std::chrono::system_clock::now();
}


/*
 * PWROWG_NAMESPACE::timestamp::from_time_t
 */
PWROWG_NAMESPACE::timestamp
PWROWG_NAMESPACE::timestamp::from_time_t(_In_ const std::time_t t) {
    return std::chrono::system_clock::from_time_t(t);
}


/*
 * PWROWG_NAMESPACE::detail::create
 */
PWROWG_NAMESPACE::timestamp
PWROWG_NAMESPACE::timestamp::from_tm(_In_ std::tm& t) {
#if defined(_WIN32)
    const auto time = ::_mkgmtime(&t);
#else /* defined(_WIN32) */
    const auto time = ::timegm(&t);
#endif /* defined(_WIN32) */

    return std::chrono::system_clock::from_time_t(time);
}


/*
 * PWROWG_NAMESPACE::timestamp::zero
 */
const PWROWG_NAMESPACE::timestamp
PWROWG_NAMESPACE::timestamp::zero(0);


/*
 * PWROWG_NAMESPACE::timestamp::unix_offset
 */
const PWROWG_NAMESPACE::timestamp::value_type
PWROWG_NAMESPACE::timestamp::tick_rate;


/*
 * PWROWG_NAMESPACE::timestamp::unix_offset
 */
const PWROWG_NAMESPACE::timestamp::value_type
PWROWG_NAMESPACE::timestamp::unix_offset;
