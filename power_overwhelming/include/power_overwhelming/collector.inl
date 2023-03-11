﻿// <copyright file="collector.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>


/*
 * visus::power_overwhelming::collector::from_sensor_lists
 */
template<class... TSensorLists>
visus::power_overwhelming::collector
visus::power_overwhelming::collector::from_sensor_lists(
        TSensorLists&&... sensors) {
    std::array<std::vector<std::unique_ptr<sensor>>,
        sizeof...(sensors)> instances = { move_to_heap(sensors)... };

    const auto cnt = std::accumulate(instances.begin(),
        instances.end(), static_cast<std::size_t>(0),
            [](const std::size_t s, const decltype(instances)::value_type& v) {
        return std::size(v) + s;
    });

    auto retval = collector::prepare(cnt);

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
visus::power_overwhelming::collector::from_sensors(TSensors&&... sensors) {
    std::array<std::unique_ptr<sensor>, sizeof...(sensors)> instances = {
        std::unique_ptr<sensor>(new typename std::decay<TSensors>::type(
            std::move(sensors)))...
    };

    auto retval = collector::prepare(instances.size());

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
    retval.reserve(std::size(sensors));

    std::transform(sensors.begin(), sensors.end(), std::back_inserter(retval),
            [](typename sensor_type& s) {
        return std::unique_ptr<sensor>(new typename sensor_type(std::move(s)));
    });

    return retval;
}