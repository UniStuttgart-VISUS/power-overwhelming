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
        std::vector<rtx_sensor_definition> definitions;
        definitions.resize(rtx_sensor::get_definitions(nullptr, 0));
        definitions.resize(rtx_sensor::get_definitions(definitions.data(), definitions.size()));

        std::cout << "Sensor definitions found:" << std::endl;
        for (auto& d : definitions) {
            std::wcout << d.description() << std::endl;
        }

        std::vector<rtx_sensor> sensors(definitions.size());
        for (std::size_t i = 0; i < definitions.size(); ++i) {
            sensors[i] = rtx_sensor(definitions[i]);
            std::wcout << L"Created " << sensors[i].name() << std::endl;
        }
    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }

    try {
        std::vector<rtx_sensor> sensors;
        sensors.resize(rtx_sensor::for_all(nullptr, 0));
        rtx_sensor::for_all(sensors.data(), sensors.size());

        for (auto& s : sensors) {
            std::wcout << L"Enumerated " << s.name() << std::endl;
        }

        for (auto& s : sensors) {
            auto waveform = s.acquire(timestamp_resolution::hundred_nanoseconds);
            std::wcout << L"Acquired " << waveform.size()
                << " samples from " << waveform.sensor()
                << std::endl;

            for (std::size_t i = 0; (i < 8) && (i < waveform.size()); ++i) {
                auto& s = waveform.sample(i);
                std::wcout << s.timestamp() << L": "
                    << s.voltage() << L"V, "
                    << s.current() << L"A, "
                    << s.power() << L"W"
                    << std::endl;
            }

            auto sample = s.sample(timestamp_resolution::hundred_nanoseconds);
            std::wcout << sample.sensor() << L"@"
                << sample.timestamp() << L": "
                << sample.voltage() << L"V, "
                << sample.current() << L"A, "
                << sample.power() << L"W"
                << std::endl;
        }
    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
}


/*
 * ::query_rtx_instrument
 */
void query_rtx_instrument(void) {
    using namespace visus::power_overwhelming;

    try {
        std::vector<rtx_instrument> devices(rtx_instrument::all(nullptr, 0));
        rtx_instrument::all(devices.data(), devices.size());

        for (auto& i : devices) {
            visa_instrument::foreach_instance([](visa_instrument& i, void *) {
                blob name(i.identify(nullptr, 0) * sizeof(wchar_t));
                i.identify(name.as<wchar_t>(), name.size() / sizeof(wchar_t));
                std::wcout << L"\"" << name.as<wchar_t>() << L"\""
                    << L" is an active VISA instrument."
                    << std::endl;
                return true;
            });

            i.reset(true, true)
                .enable_system_checks()
                .timeout(20000);
            i.synchronise_clock()
                .service_request_status(visa_status_byte::master_status)
                .operation_complete();

            {
                i.name("test-instrument").operation_complete();
                std::vector<wchar_t> name(i.name(nullptr, 0));
                i.name(name.data(), name.size());
                std::wcout << L"The user-defined device name is \""
                    << name.data() << "\"." << std::endl;
            }

            std::wcout << L"The device has " << i.channels() << L" channels."
                << std::endl;
            std::wcout << L"The device has currently " << i.history_segments()
                << L" history segments in memory." << std::endl;
            std::wcout << L"The h orizontal time range is "
                << i.time_range().value() << L"s." << std::endl;
            std::wcout << L"The horizontal time scale is "
                << i.time_scale().value() << L"s." << std::endl;
            std::wcout << L"Acquisition state is "
                << int(i.acquisition()) << std::endl;

            for (std::uint16_t c = 1; c <= i.channels(); ++c){
                auto channel = i.channel(c);
                std::wcout << L"Channel " << c << L" attenuation: "
                    << channel.attenuation().value() << std::endl;
                std::wcout << L"Channel " << c << L" bandwidth: "
                    << int(channel.bandwidth()) << std::endl;
                std::wcout << L"Channel " << c << L" channel: "
                    << channel.channel() << std::endl;
                std::wcout << L"Channel " << c << L" coupling: "
                    << int(channel.coupling()) << std::endl;
                std::wcout << L"Channel " << c << L" decimation_mode: "
                    << int(channel.decimation_mode()) << std::endl;
                std::wcout << L"Channel " << c << L" label: "
                    << channel.label().text() << L", visible: "
                    << channel.label().visible() << std::endl;
                std::wcout << L"Channel " << c << L" offset: "
                    << channel.offset().value() << std::endl;
                std::wcout << L"Channel " << c << L" polarity: "
                    << int(channel.polarity()) << std::endl;
                std::wcout << L"Channel " << c << L" range: "
                    << channel.range().value() << std::endl;
                std::wcout << L"Channel " << c << L" skew: "
                    << channel.skew().value() << std::endl;
                std::wcout << L"Channel " << c << L" state: "
                    << channel.state() << std::endl;
                std::wcout << L"Channel " << c << L" zero_offset: "
                    << channel.zero_offset().value() << std::endl;

                std::vector<wchar_t> u(i.unit(nullptr, 0, c));
                i.unit(u.data(), u.size(), c);
                std::wcout << L"Probe " << c << L" measures "
                    << u.data() << std::endl;
                i.beep(c);
            }

            {
                auto a = i.single_acquisition();
                std::wcout << L"Automatic points enabled: "
                    << a.automatic_points() << std::endl;
                std::wcout << L"Number of segments: "
                    << a.count() << std::endl;
                std::wcout << L"Number of points: "
                    << a.points() << std::endl;
                std::wcout << L"Fast segmentation: "
                    << a.segmented() << std::endl;
            }

            {
                auto t = i.edge_trigger();
                std::wcout << L"Trigger coupling: "
                    << int(t.coupling()) << std::endl;
                std::wcout << L"Trigger hold-off: "
                    << convert_string<wchar_t>(t.hold_off()) << std::endl;
                std::wcout << L"Trigger hysteresis: "
                    << int(t.hysteresis()) << std::endl;
                std::wcout << L"Trigger input: "
                    << t.input() << std::endl;
                std::wcout << L"Trigger level: "
                    << t.level().value() << std::endl;
                std::wcout << L"Trigger mode: "
                    << int(t.mode()) << std::endl;
                std::wcout << L"Trigger slope: "
                    << int(t.slope()) << std::endl;
                std::wcout << L"Trigger slope: "
                    << convert_string<wchar_t>(t.source()) << std::endl;
                std::wcout << L"Trigger type: "
                    << convert_string<wchar_t>(t.type()) << std::endl;
            }

            i.reference_position(oscilloscope_reference_point::left);
            i.time_scale(oscilloscope_quantity(10, "ms"));

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

            std::cout << "Main " << std::this_thread::get_id() << std::endl;
            i.on_operation_complete([](visa_instrument& i, void *) {
                std::cout << "bla " << std::this_thread::get_id() << std::endl;
            });
            i.operation_complete_async();

            i.trigger_position(oscilloscope_quantity(0.0f, "ms"));
            i.trigger(oscilloscope_edge_trigger("EXT")
                .level(5, oscilloscope_quantity(2000.0f, "mV"))
                .slope(oscilloscope_trigger_slope::rising)
                .mode(oscilloscope_trigger_mode::normal));
            i.throw_on_system_error();

            std::cout << "RTX interface type: "
                << i.interface_type()
                << std::endl
                << "RTX status before acquire: "
                << static_cast<int>(i.status())
                << std::endl
                << "SRE before acquire: "
                << static_cast<int>(i.service_request_status())
                << std::endl
                << "ESE before acquire: "
                << static_cast<int>(i.event_status())
                << std::endl;

            i.acquisition(oscilloscope_single_acquisition()
                .points(100000)
                .count(1)
                .segmented(false))
                .operation_complete();
            i.throw_on_system_error();

            //i.save_state_to_instrument(L"_PODUMP.SET").operation_complete();
            //i.reset(true, true);
            //i.load_state_from_instrument(L"_PODUMP.SET").operation_complete();

            i.acquisition(oscilloscope_acquisition_state::single)
                .operation_complete();
            //i.operation_complete();

            i.trigger();
            i.operation_complete();
            i.throw_on_system_error();

            auto b = std::chrono::high_resolution_clock::now();
            std::cout << "Segment "
                << i.history_segment()
                << " of "
                << i.history_segments()
                << std::endl;
            auto segment0 = i.data(1, oscilloscope_waveform_points::maximum);
            auto e = std::chrono::high_resolution_clock::now();
            std::cout << "Download took "
                << std::chrono::duration_cast<std::chrono::milliseconds>(e - b).count()
                << " ms" << std::endl;

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
            int x = 1234;
        }

    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
}
