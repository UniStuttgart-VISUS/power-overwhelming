// <copyright file="timestamp.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


/*
 * visus::power_overwhelming::timestamp::timestamp
 */
template<class TClock, class TDuration>
visus::power_overwhelming::timestamp::timestamp(
        _In_ const std::chrono::time_point<TClock, TDuration> t) {
    using namespace std::chrono;
    typedef duration<value_type, std::ratio<1, tick_rate>> duration_type;

    const auto dz = duration_type(timestamp::unix_offset);

    // Find out what the difference between the time point 't' and the UNIX
    // epoch is. Because we cannot rely on the epoch of the STL clock being the
    // UNIX epoch (until C++ 20), we use time_t, which is guaranteed to
    // represent the UNIX epoch.
    const auto st = time_point_cast<system_clock::duration>(t);
    const auto uz = system_clock::from_time_t(0);
    const auto dt = st - uz;

    // Transform the origin of the timestamp clock to the origin of FILETIME.
    this->_value = timestamp::to_ticks(dt + dz);
}


/*
 * visus::power_overwhelming::timestamp::to_duration
 */
template<class TPeriod>
std::chrono::duration<visus::power_overwhelming::timestamp::value_type, TPeriod>
visus::power_overwhelming::timestamp::to_duration(void) const {
    using namespace std::chrono;
    typedef duration<value_type, std::ratio<1, tick_rate>> duration_type;
    duration_type retval(this->_value);
    return duration_cast<duration<value_type, TPeriod>>(retval);
}


/*
 * visus::power_overwhelming::timestamp::to_time_point
 */
template<class TClock>
typename TClock::time_point visus::power_overwhelming::timestamp::to_time_point(
        void) const {
    using namespace std::chrono;
    typedef duration<value_type, std::ratio<1, tick_rate>> duration_type;

    const auto dz = duration_type(timestamp::unix_offset);

    // Find out what the difference between the time point 't' and the UNIX
    // epoch is. Because we cannot rely on the epoch of the STL clock being the
    // UNIX epoch (until C++ 20), we use time_t, which is guaranteed to
    // represent the UNIX epoch.
    const auto uz = system_clock::from_time_t(0).time_since_epoch();
    const auto d = duration_type(this->_value);
    const auto dt = d + uz - dz;

    return time_point<TClock>(dt);
}


#if false
/*
 * visus::power_overwhelming::detail::convert
 */
template<class TRep, class TPeriod>
visus::power_overwhelming::timestamp_type
visus::power_overwhelming::detail::convert(
        _In_ const std::chrono::duration<TRep, TPeriod> dur,
        _In_ const timestamp_resolution resolution) {
    using namespace std::chrono;
    typedef duration<timestamp_type, filetime_period> filetime_dur;

    switch (resolution) {
        case timestamp_resolution::hundred_nanoseconds:
            return duration_cast<filetime_dur>(dur).count();

        case timestamp_resolution::microseconds:
            return duration_cast<microseconds>(dur).count();

        case timestamp_resolution::milliseconds:
            return duration_cast<milliseconds>(dur).count();

        // This would always overflow, so we do not support it any more.
        //case timestamp_resolution::nanoseconds:
        //    return duration_cast<nanoseconds>(dur).count();

        case timestamp_resolution::seconds:
            return duration_cast<seconds>(dur).count();

        default:
            throw std::invalid_argument("The specified timestamp_resolution "
                "is unsupported.");
    }
}


/*
 * visus::power_overwhelming::detail::convert
 */
template<class TDuration>
visus::power_overwhelming::timestamp_type
visus::power_overwhelming::detail::convert(
        _In_ const std::chrono::time_point<std::chrono::system_clock,
            TDuration>& timestamp,
        _In_ const timestamp_resolution resolution) {
    using namespace std::chrono;

    // The offset of the FILETIME epoch to the UNIX epoch.
    const auto dz = duration<timestamp_type,
        detail::filetime_period>(116444736000000000LL);

    // Find out what the difference between the time point and the UNIX
    // epoch is. Because we cannot rely on the epoch of the STL clock being the
    // UNIX epoch (until C++ 20), use time_t, which is guaranteed to represent
    // the UNIX epoch.
    auto dt = time_point_cast<system_clock::duration>(timestamp)
        - system_clock::from_time_t(0);

    // Transform the origin of the timestamp clock to the origin of FILETIME.
    return convert(dt + dz, resolution);
}
#endif
