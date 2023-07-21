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

        case timestamp_resolution::nanoseconds:
            return duration_cast<nanoseconds>(dur).count();

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

    // Find out what the difference between the time point and the UNIX
    // epoch is. Because we cannot rely on the epoch of the STL clock being the
    // UNIX epoch (until C++ 20), use time_t, which is guaranteed to represent
    // the UNIX epoch.
    auto dt = time_point_cast<system_clock::duration>(timestamp)
        - system_clock::from_time_t(0);

    // Transform the origin of the timestamp clock to the origin of FILETIME.
    return convert(dt + dz, resolution);
}
