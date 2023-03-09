// <copyright file="collector.inl" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>


/*
 * visus::power_overwhelming::collector::from_sensors
 */
template<class... TSensors>
visus::power_overwhelming::collector
visus::power_overwhelming::collector::from_sensors(TSensors&&... sensors) {
    std::array<sensor *, sizeof...(sensors)> instances = {
        (new typename std::decay<TSensors>::type(std::move(sensors)))...
    };

    auto retval = collector::prepare(instances.size());

    for (auto& i : instances) {
        retval.add(i);
    }

    return retval;
}
