// <copyright file="nvml_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>


#include <iostream>

#include <measurement.h>
#include <nvml_sensor.h>
#include <tchar.h>


/// <summary>
/// Entry point of the application.
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
int _tmain(const int argc, const TCHAR **argv) {
    using namespace visus::power_overwhelming;

    try {
        auto sensors = nvml_sensor<measurement<>>::for_all();

        for (auto& s : sensors) {
            auto m = s.sample();
            std::cout << m.timestamp().time_since_epoch().count()
                << ": " << m.power() << " W" << std::endl;
        }

        return 0;
    } catch (std::exception &ex) {
        std::cerr << ex.what() << std::endl;
        return -1;
    }
}
