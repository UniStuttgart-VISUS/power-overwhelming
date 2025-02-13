// <copyright file="rohde_und_schwarz.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"
#include "rohde_und_schwarz.h"

#include "visus/pwrowg/event.h"



/*
 * ::query_hmc8015
 */
void query_hmc8015(void) {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    using namespace visus::pwrowg;

    try {
        std::vector<hmc8015_instrument> sensors;
        sensors.resize(hmc8015_sensor::for_all(nullptr, 0));
        hmc8015_sensor::for_all(sensors.data(), sensors.size(), 10000);

        for (auto& s : sensors) {
            s.display("Die Kraft ist überwältigend!");
            s.synchronise_clock();
            s.log_file("podump.csv", true, true);
            s.current_range(instrument_range::maximum);
            s.voltage_range(instrument_range::explicitly, 300);

            {
                std::vector<char> f(s.functions(nullptr, 0));
                s.functions(f.data(), f.size());
                std::cout << "Active functions: " << f.data() << std::endl;
            }

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
            std::wcout << s.logging() << std::endl;

            {
                hmc8015_function input[] = { hmc8015_function::apparent_power, hmc8015_function::ampere_hour };
                s.custom_functions(input, 2);
                std::vector<char> functions(s.functions(nullptr, 0));
                s.functions(functions.data(), functions.size());
                std::cout << "Active functions: " << functions.data() << std::endl;
            }

            {
                s.custom_functions({ hmc8015_function::rms_current, hmc8015_function::rms_voltage });
                std::vector<char> functions(s.functions(nullptr, 0));
                s.functions(functions.data(), functions.size());
                std::cout << "Active functions: " << functions.data() << std::endl;
            }

            std::vector<char> path(1024);
            s.log_file(path.data(), path.size());
            std::this_thread::sleep_for(std::chrono::seconds(6));
            s.log(false);

            std::wcout << s.name() << L":" << std::endl;
            s.default_functions();
            auto m = s.sample();
            std::wcout << m.timestamp() << L": " << m.voltage() << " V * "
                << m.current() << " A = " << m.power() << L" W"
                << std::endl;

            auto log_data = s.copy_file_from_instrument("podump.csv", true);
            std::string log(log_data.begin(), log_data.end());
            std::cout << log << std::endl;

            s.delete_file_from_instrument("podump.csv", true);
        }

    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */
}



/*
 * ::query_rtx_instrument
 */
void query_rtx_instrument(void) {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    using namespace visus::pwrowg;

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

            i.reset(rtx_instrument_reset::all)
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
            std::wcout << L"The horizontal time range is "
                << i.time_range().value() << L"s." << std::endl;
            std::wcout << L"The horizontal time scale is "
                << i.time_scale().value() << L"s." << std::endl;

            for (std::size_t c = 1; c <= i.channels(); ++c){
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
                auto a = i.acquisition();
                std::wcout << L"Automatic points enabled: "
                    << a.automatic_points() << std::endl;
                std::wcout << L"Number of segments: "
                    << a.count() << std::endl;
                std::wcout << L"Number of points: "
                    << a.points() << std::endl;
                std::wcout << L"Fast segmentation: "
                    << a.segmented() << std::endl;
                std::wcout << L"Acquisition state is "
                    << int(a.state()) << std::endl;
            }

            {
                auto t = i.trigger();
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

            i.reference_position(rtx_reference_point::left);
            i.time_scale(rtx_quantity(10, "ms"));

            i.channel(rtx_channel(1)
                .label(rtx_label("podump#1"))
                .state(true)
                .attenuation(rtx_quantity(10, "V"))
                .range(rtx_quantity(7)));

            //i.channel(rtx_channel(2)
            //    .label(rtx_label("podump#2"))
            //    .state(true)
            //    .attenuation(rtx_quantity(1, "V"))
            //    .range(rtx_quantity(5)));

            std::cout << "Main " << std::this_thread::get_id() << std::endl;
            auto event = visus::power_overwhelming::create_event();
            i.on_operation_complete([](visa_instrument &i, void *) {
                std::cout << "OPC in thread #" << std::this_thread::get_id() << std::endl;
            }, &i);
            i.on_operation_complete_ex([&event](visa_instrument& i) {
                std::cout << "OPC in thread #" << std::this_thread::get_id() << std::endl;
                visus::power_overwhelming::set_event(event);
            });
            i.operation_complete_async();
            visus::power_overwhelming::wait_event(event);
            i.on_operation_complete(nullptr);

            i.trigger_position(rtx_quantity(0.0f, "ms"));
            i.trigger(rtx_trigger::edge("EXT")
                .level(5, rtx_quantity(2000.0f, "mV"))
                .slope(rtx_trigger_slope::rising)
                .mode(rtx_trigger_mode::automatic))
                .operation_complete();
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

            i.acquisition(rtx_acquisition()
                .points(100000)
                .count(2)
                .segmented(false))
                .operation_complete();
            i.throw_on_system_error();

            i.save_state_to_instrument(L"_PODUMP.SET").operation_complete();
            i.reset(visus::power_overwhelming::rtx_instrument_reset::all);
            i.load_state_from_instrument(L"_PODUMP.SET").operation_complete();
            i.delete_file_from_instrument(L"_PODUMP.SET", L"/INT/SETTINGS");

            {
                auto state = i.copy_state_from_instrument();
                std::ofstream of;
                of.open("podump.set", std::ios::binary | std::ios::trunc);
                of.write(state.as<char>(), state.size());
                of.close();
                i.reset(visus::power_overwhelming::rtx_instrument_reset::reset);
                i.copy_state_to_instrument(state);
            }

            i.acquisition(rtx_acquisition_state::single)
                .operation_complete()
                .throw_on_system_error();

            for (std::size_t s = 0; s < i.history_segments(); ++s) {
                i.history_segment(0 - s).operation_complete();
                i.beep(s + 1);

                std::cout << "Segment "
                    << i.history_segment()
                    << " of "
                    << i.history_segments()
                    << std::endl;
                
                auto b = std::chrono::high_resolution_clock::now();
                auto segment = i.data(1, rtx_waveform_points::maximum);
                auto e = std::chrono::high_resolution_clock::now();
                std::cout << "Download took "
                    << std::chrono::duration_cast<std::chrono::milliseconds>(e - b).count()
                    << " ms" << std::endl;

                std::cout << "Record length: "
                    << segment.record_length() << std::endl
                    << "Buffer size: "
                    << segment.end() - segment.begin() << std::endl
                    << "Begin: " << segment.time_begin() << std::endl
                    << "End: " << segment.time_end() << std::endl
                    << "Offset: " << segment.segment_offset() << std::endl
                    << "Timestamp: " << segment.segment_timestamp() << std::endl;
            }

            i.channel(rtx_channel(2).state(true));
            i.acquisition(rtx_acquisition_state::single);
            auto sample = i.data(rtx_waveform_points::maximum);
            std::cout << "Sample size: " << sample.size() << std::endl;
        }

    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */
}


/*
 * ::configure_rtx_instrument
 */
void configure_rtx_instrument(void) {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    using namespace visus::pwrowg;

    try {
        std::vector<rtx_instrument> devices(rtx_instrument::all(nullptr, 0));
        rtx_instrument::all(devices.data(), devices.size());

        rtx_instrument_configuration config(12,
            rtx_acquisition().points(12000).segmented(true),
            rtx_trigger::edge("CH1"));
        config.prevent_automatic_roll();

        for (auto& i : devices) {
            i.reset();
            config.apply(i);

            rtx_instrument_configuration actual(i);
            std::cout << "acquisition.count: "
                << actual.acquisition().count() << std::endl
                << "acquisition.segmented: "
                << actual.acquisition().segmented() << std::endl
                << "min_time_base: " << actual.min_time_base() << std::endl
                << "timeout: " << actual.timeout() << std::endl
                << "time_range: " << actual.time_range().value() << std::endl;
        }

    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */
}
