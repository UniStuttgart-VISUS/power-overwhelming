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
    //using namespace visus::power_overwhelming;

    //try {
    //    std::vector<oscilloscope_sensor_definition> definitions;
    //    std::vector<rtx_sensor> sensors;
    //    sensors.resize(rtx_sensor::for_all(nullptr, 0));
    //    rtx_sensor::for_all(sensors.data(), sensors.size());

    //    definitions.push_back(oscilloscope_sensor_definition(L"Test1",
    //        1, 10.0f, 2, 10.0f));

    //    // TODO: this is incomplete.

    //    for (auto& s : sensors) {
    //        s.reset();
    //        s.synchronise_clock();
    //        s.reference_position(oscilloscope_reference_point::middle);
    //        s.time_range(oscilloscope_quantity(500, "ms"));

    //        s.configure(definitions.data(), definitions.size());

    //        s.configure(oscilloscope_channel(1)
    //            .label(oscilloscope_label("PwrOwg"))
    //            .state(true)
    //            .gain(oscilloscope_quantity(10, "V"))
    //            .range(oscilloscope_quantity(7, L"V")));

    //        s.configure(oscilloscope_single_acquisition()
    //            .points(50000)
    //            .count(1));
 
    //        s.trigger_position(42.42f, "ms");
    //        s.trigger(oscilloscope_edge_trigger("CH1")
    //            .level(1, oscilloscope_quantity(2000.0f, "mV"))
    //            .slope(oscilloscope_trigger_slope::both)
    //            .mode(oscilloscope_trigger_mode::normal));

    //        auto data = s.data(1);

    //        //s.expression(1, "CH1*CH2", "W");
    //        std::wcout << s.name() << L":" << std::endl;
    //    }
    //       
    //} catch (std::exception& ex) {
    //    std::cerr << ex.what() << std::endl;
    //}
}


/*
 * ::query_rtx_instrument
 */
void query_rtx_instrument(void) {
    using namespace visus::power_overwhelming;

    try {
        auto devices = visa_instrument::find_resources(L"0x0AAD", L"0x01D6");

        for (auto d = devices.as<wchar_t>();
                (d != nullptr) && (*d != 0);
                d += ::wcslen(d) + 1) {
            auto is_new = false;
            rtx_instrument i(is_new, d);

            if (is_new) {
                std::wcout << L"Connected to new instrument." << std::endl;
            } else {
                std::wcout << L"Reused existing connection." << std::endl;
            }

            visa_instrument::foreach_instance([](visa_instrument& i, void *) {
                blob name(i.identify(nullptr, 0) * sizeof(wchar_t));
                i.identify(name.as<wchar_t>(), name.size() / sizeof(wchar_t));
                std::wcout << L"\"" << name.as<wchar_t>() << L"\""
                    << L" is an active VISA instrument."
                    << std::endl;
                return true;
            });

            i.synchronise_clock();
            i.reset(true, true);
            i.timeout(20000);

            i.reference_position(oscilloscope_reference_point::left);
            i.time_scale(oscilloscope_quantity(1, "s"));

            i.channel(oscilloscope_channel(1)
                .label(oscilloscope_label("podump#1"))
                .state(true)
                .attenuation(oscilloscope_quantity(10, "V"))
                .range(oscilloscope_quantity(7)));

            //i.channel(oscilloscope_channel(2)
            //    .label(oscilloscope_label("podump#2"))
            //    .state(true)
            //    .attenuation(oscilloscope_quantity(1, "V"))
            //    .range(oscilloscope_quantity(5)));

            i.trigger_position(oscilloscope_quantity(0.0f, "ms"));
            i.trigger(oscilloscope_edge_trigger("CH1")
                .level(1, oscilloscope_quantity(2000.0f, "mV"))
                .slope(oscilloscope_trigger_slope::rising)
                .mode(oscilloscope_trigger_mode::automatic));

            std::cout << "RTX interface type: "
                << i.interface_type()
                << std::endl
                << "RTX status before acquire: "
                << static_cast<int>(i.status())
                << std::endl
                << "RTX event status before acquire: "
                << static_cast<int>(i.event_status())
                << std::endl;

            i.acquisition(oscilloscope_single_acquisition()
                .points(100000)
                .count(1)
                .segmented(false)
                .segmented(false));

            i.operation_complete();
            i.acquisition(oscilloscope_acquisition_state::single);

            //i.query("*TRG;*OPC?\n");

            i.trigger();
            i.operation_complete();
            //i.trigger();

            auto b = std::chrono::high_resolution_clock::now();
            std::cout << "Segment "
                << i.history_segment()
                << " of "
                << i.history_segments()
                << std::endl;
            auto segment0 = i.data(1, oscilloscope_waveform_points::maximum);
            auto e = std::chrono::high_resolution_clock::now();
            std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(e - b).count() << std::endl;

            std::cout << "Record length: "
                << segment0.record_length() << std::endl
                << "Buffer size: "
                << segment0.end() - segment0.begin() << std::endl;


            //i.history_segment(-1);
            //std::cout << "Segment "
            //    << i.history_segment()
            //    << " of "
            //    << i.history_segments()
            //    << std::endl;
            //auto segment1 = i.data(1);
            int x = 1;
        }

    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
}
