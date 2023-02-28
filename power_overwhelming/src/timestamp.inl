// <copyright file="timestamp.inl" company="Visualisierungsinstitut der Universit�t Stuttgart">
// Copyright � 2021 Visualisierungsinstitut der Universit�t Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph M�ller</author>


/*
 * visus::power_overwhelming::detail::timestamp<Resolution>::create
 */
template<visus::power_overwhelming::timestamp_resolution Resolution>
template<class TTimePoint>
typename visus::power_overwhelming::detail::timestamp<Resolution>::value_type
visus::power_overwhelming::detail::timestamp<Resolution>::create(
        const TTimePoint& timePoint) {
    typedef typename TTimePoint::clock clock_type;

#if false
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

    const auto dz = detail::convert(fileTime, Resolution);
#else
    // All of the above will always yield the following magic number:
    const auto dz = 11644473600000LL;
#endif

    // Find out what the difference between the given time_point and the UNIX
    // epoch is. Because we cannot rely on the epoch of the STL clock being the
    // UNIX epoch, use time_t, which is guaranteed to represent the UNIX epoch.
    auto dt = std::chrono::duration_cast<duration_traits<Resolution>::type>(
        timePoint - clock_type::from_time_t(0)).count();

    // Transform the origin of the timestamp clock to the origin of FILETIME.
    return (dt + dz);
}