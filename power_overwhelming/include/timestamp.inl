// <copyright file="timestamp.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>



/*
 * visus::power_overwhelming::detail::convert
 */
decltype(LARGE_INTEGER::QuadPart) visus::power_overwhelming::detail::convert(
        const decltype(LARGE_INTEGER::QuadPart) fileTime,
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
 * visus::power_overwhelming::detail::timestamp<Resolution>::create
 */
template<visus::power_overwhelming::timestamp_resolution Resolution>
template<class TTimePoint>
typename visus::power_overwhelming::detail::timestamp<Resolution>::value_type
visus::power_overwhelming::detail::timestamp<Resolution>::create(
        const TTimePoint& timePoint) {
    typedef typename TTimePoint::clock clock_type;

    FILETIME fileTime;
    SYSTEMTIME systemTime;

    // Find out what the UNIX epoch is as FILETIME, because this is the only way
    // we can relate an STL time_point safely to a real date.
    ::ZeroMemory(&systemTime, sizeof(systemTime));
    systemTime.wYear = 1970;
    systemTime.wMonth = 1;
    systemTime.wDay = 1;

    if (!::SystemTimeToFileTime(&systemTime, &fileTime)) {
        throw std::system_error(::GetLastError(), std::system_category());
    }

    auto dz = detail::convert(fileTime, Resolution);

    // Find out what the difference between the given time_point and the UNIX
    // epoch is. Because we cannot rely on the epoch of the STL clock being the
    // UNIX epock, use time_t, which is guaranteed to represent the UNIX epoch.
    auto dt = std::chrono::duration_cast<duration_traits<Resolution>::type>(
        timePoint - clock_type::from_time_t(0)).count();

    // Transform the origin of the timestamp clock to the origin of FILETIME.
    return (dt + dz);
}
