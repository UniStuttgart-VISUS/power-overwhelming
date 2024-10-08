﻿// <copyright file="collector.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// Backport of C++ 17 <c>std::size</c>.
    /// </summary>
    template<class TContainer>
    inline constexpr auto count_sensors(const TContainer& sensors)
            -> decltype(sensors.size()) {
        return sensors.size();
    }

    /// <summary>
    /// Backport of C++ 17 <c>std::size</c>.
    /// </summary>
    template<class TValue, std::size_t Count>
    inline constexpr std::size_t count_sensors(
            const TValue(&sensors)[Count]) noexcept {
        return Count;
    }

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */


/*
 * visus::power_overwhelming::collector::from_sensor_lists
 */
template<class... TSensorLists>
visus::power_overwhelming::collector
visus::power_overwhelming::collector::from_sensor_lists(
        _In_ const collector_settings& settings,
        TSensorLists&&... sensors) {
    std::array<std::vector<std::unique_ptr<sensor>>,
        sizeof...(sensors)> instances = { move_to_heap(sensors)... };
    typedef typename decltype(instances)::value_type sensor_type;

    const auto cnt = std::accumulate(instances.begin(),
        instances.end(), static_cast<std::size_t>(0),
            [](const std::size_t s, const sensor_type& v) {
        return detail::count_sensors(v) + s;
    });

    auto retval = collector::prepare(settings, cnt);

    for (auto& l : instances) {
        for (auto& i : l) {
            // See 'from_sensors' for the rationale of this.
            retval.add(i.release());
        }
    }

    return retval;
}

/*
 * visus::power_overwhelming::collector::from_sensors
 */
template<class... TSensors>
visus::power_overwhelming::collector
visus::power_overwhelming::collector::from_sensors(
        _In_ const collector_settings& settings,
        TSensors&&... sensors) {
    std::array<std::unique_ptr<sensor>, sizeof...(sensors)> instances = {
        std::unique_ptr<sensor>(new typename std::decay<TSensors>::type(
            std::move(sensors)))...
    };

    auto retval = collector::prepare(settings, instances.size());

    for (auto& i : instances) {
        // Note: We release this on purpose as the library and the calling code
        // might have been compiled with different versions of the STL. The
        // unique_ptr here is only for releasing the memory in case of
        // an exeception.
        retval.add(i.release());
    }

    return retval;
}


/*
 * visus::power_overwhelming::collector::move_to_heap
 */
template<class TSensorList>
std::vector<std::unique_ptr<visus::power_overwhelming::sensor>>
visus::power_overwhelming::collector::move_to_heap(TSensorList&& sensors) {
    typedef typename std::decay<decltype(sensors.front())>::type sensor_type;

    decltype(move_to_heap(sensors)) retval;
    retval.reserve(detail::count_sensors(sensors));

    std::transform(sensors.begin(), sensors.end(), std::back_inserter(retval),
            [](sensor_type& s) {
        return std::unique_ptr<sensor>(new sensor_type(std::move(s)));
    });

    return retval;
}
