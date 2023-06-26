// <copyright file="timestamp.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// The offset between the FILETIME epoch and the Unix time epoch.
    /// </summary>
    const auto unix_time_offset = std::chrono::duration<
        timestamp_type, filetime_period>(116444736000000000LL);

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */


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
    typedef duration<timestamp_type, filetime_period> filetime_dur;

    // Find out what the difference between the time point and the UNIX
    // epoch is. Because we cannot rely on the epoch of the STL clock being the
    // UNIX epoch (until C++ 20), use time_t, which is guaranteed to represent
    // the UNIX epoch.
    auto dt = time_point_cast<system_clock::duration>(timestamp)
        - system_clock::from_time_t(0);

    // Transform the origin of the timestamp clock to the origin of FILETIME.
    switch (resolution) {
        case timestamp_resolution::hundred_nanoseconds:
            return duration_cast<filetime_dur>(dt + unix_time_offset).count();

        case timestamp_resolution::microseconds:
            return duration_cast<microseconds>(dt + unix_time_offset).count();

        case timestamp_resolution::milliseconds:
            return duration_cast<milliseconds>(dt + unix_time_offset).count();

        case timestamp_resolution::nanoseconds:
            return duration_cast<nanoseconds>(dt + unix_time_offset).count();

        case timestamp_resolution::seconds:
            return duration_cast<seconds>(dt + unix_time_offset).count();

        default:
            throw std::invalid_argument("The specified timestamp_resolution "
                "is unsupported.");
    }
}


/*
 * visus::power_overwhelming::to_time_point
 */
template<class TDuration>
std::chrono::time_point<std::chrono::system_clock, TDuration>
visus::power_overwhelming::to_time_point(
        _In_ const timestamp_type timestamp,
        _In_ const timestamp_resolution resolution) {
    using namespace std::chrono;
    typedef duration<timestamp_type, detail::filetime_period> filetime_dur;

    // Convert the input to FILETIME ticks for applying the Unix offset.
    filetime_dur ticks;
    switch (resolution) {
        case timestamp_resolution::hundred_nanoseconds:
            ticks = filetime_dur(timestamp);
            break;

        case timestamp_resolution::microseconds:
            ticks = duration_cast<filetime_dur>(microseconds(timestamp));
            break;

        case timestamp_resolution::milliseconds:
            ticks = duration_cast<filetime_dur>(milliseconds(timestamp));
            break;

        case timestamp_resolution::nanoseconds:
            ticks = duration_cast<filetime_dur>(nanoseconds(timestamp));
            break;

        case timestamp_resolution::seconds:
            ticks = duration_cast<filetime_dur>(seconds(timestamp));
            break;

        default:
            throw std::invalid_argument("The specified timestamp_resolution "
                "is unsupported.");
    }

    ticks -= detail::unix_time_offset;
    // At this point, we have FILETIME ticks sinse the Unix epoch.

    const time_point<system_clock, filetime_dur> retval(ticks);
    return time_point_cast<TDuration>(retval);
}
