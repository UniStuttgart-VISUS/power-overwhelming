// <copyright file="emi_sensor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"
#include "emi_sensor.h"


/*
 * ::sample_emi_sensor
 */
void sample_emi_sensor(void) {
    using namespace visus::power_overwhelming;

#if defined(_WIN32)
    try {
        std::vector<emi_sensor> sensors;
        sensors.resize(emi_sensor::for_all(nullptr, 0));
        emi_sensor::for_all(sensors.data(), sensors.size());

        for (auto& s : sensors) {
            std::wcout << s.name() << L":" << std::endl;
            auto m = s.sample();
            std::wcout << m.timestamp() << L" (" << m.sensor() << L"): "
                << m.power() << L" W" << std::endl;
        }
    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
#endif /* defined(_WIN32) */
}
