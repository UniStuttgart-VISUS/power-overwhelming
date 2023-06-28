// <copyright file="rohde_und_schwarz.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"
#include "rohde_und_schwarz.h"


/*
 * ::query_hmc8015
 */
void query_hmc8015(void) {
    using namespace visus::power_overwhelming;

    try {
        std::vector<hmc8015_sensor> sensors;
        sensors.resize(hmc8015_sensor::for_all(nullptr, 0));
        hmc8015_sensor::for_all(sensors.data(), sensors.size());

        for (auto &s : sensors) {
            s.display("Die Kraft ist überwältigend!");
            s.synchronise_clock();
            s.log_file("podump.csv", true, true);
            s.current_range(instrument_range::maximum);
            s.voltage_range(instrument_range::explicitly, 300);

#if defined(_WIN32)
            SYSTEMTIME now;
            ::GetLocalTime(&now);

            std::wcout << now.wHour << ":"
                << now.wMinute << ":"
                << now.wSecond << std::endl;
#endif /* defined(_WIN32) */

            //s.log_behaviour(std::numeric_limits<float>::lowest(),
            //    log_mode::time_span, 5, now.wYear, now.wMonth,
            //    now.wDay, now.wHour, now.wMinute, now.wSecond + 5);
            s.log_behaviour(std::numeric_limits<float>::lowest(),
                log_mode::duration);
            s.log(true);
            std::wcout << s.is_log() << std::endl;

            std::vector<char> path(1024);
            s.log_file(path.data(), path.size());
            std::this_thread::sleep_for(std::chrono::seconds(6));
            s.log(false);

            std::wcout << s.name() << L":" << std::endl;
            auto m = s.sample(timestamp_resolution::milliseconds);
            std::wcout << m.timestamp() << L": " << m.voltage() << " V * "
                << m.current() << " A = " << m.power() << L" W"
                << std::endl;
        }

    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
}


/*
 * ::query_rtx
 */
void query_rtx(void) {
    using namespace visus::power_overwhelming;

    try {
        std::vector<oscilloscope_sensor_definition> definitions;
        std::vector<rtx_sensor> sensors;
        sensors.resize(rtx_sensor::for_all(nullptr, 0));
        rtx_sensor::for_all(sensors.data(), sensors.size());

        definitions.push_back(oscilloscope_sensor_definition(L"Test1",
            1, 10.0f, 2, 10.0f));

        // TODO: this is incomplete.

        for (auto& s : sensors) {
            s.reset();
            s.synchronise_clock();
            s.reference_position(oscilloscope_reference_point::middle);
            s.time_scale(1);
            s.trigger_position(42.42f, "ms");
            s.trigger(oscilloscope_edge_trigger("CH1")
                .level(1, 2000.0f, "mV")
                .slope(oscilloscope_trigger_slope::both)
                .mode(oscilloscope_trigger_mode::normal));

            s.configure(definitions.data(), definitions.size());
            //s.expression(1, "CH1*CH2", "W");
            std::wcout << s.name() << L":" << std::endl;
        }

    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
}
