// <copyright file="dump_readings.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/sensor_array.h"

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

#if defined(_WIN32)
#include <Windows.h>
#include <conio.h>
#include <processenv.h>
#include <tchar.h>
#endif /* defined(_WIN32) */

#include "visus/pwrowg/convert_string.h"
#include "visus/pwrowg/pwog_file.h"
#include "visus/pwrowg/rtx_configuration.h"
#include "visus/pwrowg/string_functions.h"

#if !defined(_tmain)
#define _tmain main
#define TCHAR char
#define _T(x) (x)
#define _tcsrchr strrchr
#endif /* !defined(_tmain) */


/// <summary>
/// Finds the command line switch <paramref name="name"/> in the given command
/// line.
/// </summary>
template<class TIterator> TIterator find_switch(_In_ const TIterator begin,
    _In_ const TIterator end, _In_z_ const char* name) {
    return std::find_if(begin, end, [name](_In_ const char* arg) {
        return visus::pwrowg::detail::equals(arg, name, true);
        });
}

/// <summary>
/// Finds the value of the command line argument <paramref name="name"/> in the
/// given command line.
/// </summary>
template<class TIterator> TIterator find_argument(_In_ const TIterator begin,
    _In_ const TIterator end, _In_z_ const char* name) {
    auto retval = find_switch(begin, end, name);
    if (retval != end) {
        ++retval;
    }
    return retval;
}


/// <summary>
/// Entry point of the dump_sensors application, which dumps sensor readings
/// until a key is pressed.
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
int _tmain(const int argc, const TCHAR **argv) {
    using namespace visus::pwrowg;

    std::wcout << L"dump_readings" << std::endl;
    std::wcout
        << L"© 2023 - 2026 Visualisierungsinstitut der Universität Stuttgart."
        << std::endl << std::endl;

    try {
        // Process command line arguments.
        const auto end = argv + argc;

        std::chrono::milliseconds interval(10);
        {
            auto it = ::find_argument(argv, end, "--interval");
            if (it != end) {
                const auto v = visus::pwrowg::convert_string<char>(*it);
                interval = std::chrono::milliseconds(std::stoll(v));
            }
        }

        const auto manual = (::find_switch(argv, end, "--manual") != end);

        const TCHAR *output = nullptr;
        {
            auto it = ::find_argument(argv, end, "--output");
            output = *it;
        }

        const auto overwrite = (::find_switch(argv, end, "--overwrite") != end);

        const TCHAR* rtx_config = nullptr;
        {
            auto it = ::find_argument(argv, end, "--rtx-config");
            rtx_config = *it;
        }

        std::chrono::milliseconds timespan(5000);
        {
            auto it = ::find_argument(argv, end, "--timespan");
            if (it != end) {
                const auto v = visus::pwrowg::convert_string<char>(*it);
                timespan = std::chrono::milliseconds(std::stoll(v));
            }
        }

        const auto use_id = (::find_switch(argv, end, "--use-id") != end);

        // Set up the sensors.
        sensor_array_configuration sensor_config;
        sensor_config.sample_every(interval);

#if defined(POWER_OVERWHELMING_WITH_VISA)
        if (rtx_config != nullptr) {
            sensor_config.configure<rtx_configuration>([rtx_config](auto& c) {
                c = rtx_configuration::load(rtx_config);
            });
        }
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */

        // This structure is used for recording the samples in RAM before
        // writing them to disk. It is unused when dumping to the console.
        struct {
            bool count_only;
            std::size_t expected;
            std::vector<sample> samples;
        } file_context;
        file_context.count_only = false;
        file_context.expected = 0;

        if (output != nullptr) {
            // If we have an output file, record everything to RAM and write it
            // to disk at the end.
            sensor_config.deliver_to([](
                        _In_reads_(cnt_samples) const sample* samples,
                        _In_ const std::size_t cnt_samples,
                        _In_opt_ const sensor_description* sensors,
                        _In_ const std::size_t,
                        _In_ void *context) {
                    assert(context != nullptr);
                    auto ctx = static_cast<decltype(file_context) *>(context);

                    if (ctx->count_only) {
                        ctx->expected += cnt_samples;
                    } else {
                        std::copy(samples, samples + cnt_samples,
                            std::back_inserter(ctx->samples));
                    }
                }).deliver_context(&file_context);

        } else {
            // If we have no file, dump it do the console.
            sensor_config.deliver_to([](
                    _In_reads_(cnt_samples) const sample *samples,
                    _In_ const std::size_t cnt_samples,
                    _In_opt_ const sensor_description *sensors,
                    _In_ const std::size_t,
                    _In_opt_ void *) {
                for (std::size_t i = 0; i < cnt_samples; ++i) {
                    std::wcout << sensors[samples[i].source].id()
                        << L"@" << samples[i].timestamp << L": ";
                    switch (sensors[samples[i].source].reading_type()) {
                        case reading_type::floating_point:
                            std::wcout << samples[i].reading.floating_point;
                            break;

                        case reading_type::signed_integer:
                            std::wcout << samples[i].reading.signed_integer;
                            break;

                        case reading_type::unsigned_integer:
                            std::wcout << samples[i].reading.unsigned_integer;
                            break;

                        default:
                            assert(false);
                            break;
                    }
                    std::wcout << std::endl;
                }
            });
        }

        auto sensors = sensor_array::for_all(std::move(sensor_config));

        // If we have a file, measure how many samples we can expect.
        if (output != nullptr) {
            std::wcout << L"Measuring how many samples to expect within "
                << timespan.count() << L" ms..." << std::endl;
            file_context.count_only = true;
            sensors.start();
            std::this_thread::sleep_for(timespan);
            sensors.stop();

            file_context.samples.reserve(file_context.expected * 1.25);
            std::wcout << L"Received " << file_context.expected
                << L", reserving space for " << file_context.samples.capacity()
                << L" samples for the actual measurement." << std::endl;
            std::wcout << std::endl;
            file_context.count_only = false;
        }

        if (manual) {
#if defined(_WIN32)
            std::wcout << L"Sensors are ready, press any key to start "
                L"measuring." << std::endl;
            ::getch();
#else /* !defined(_WIN32) */
            std::wcout << L"Sensors are ready, press enter to start measuring."
                << std::endl;
            std::cin.get();
#endif /* !defined(_WIN32) */
        }
        
        sensors.start();
        std::this_thread::sleep_for(timespan);
        sensors.stop();

        if (output != nullptr) {
            std::wcout << L"Writing " << file_context.samples.size()
                << L" samples to " << output << L"..." << std::endl;
            const auto ext = ::_tcsrchr(output, _T('.'));

            time_t time;
            char timestamp[8 + 6 + 1] = { 0 };
            ::time(&time);
            auto tm = ::gmtime(&time);
            if (::strftime(timestamp, std::size(timestamp), "%Y%m%d%H%M%S", tm)
                    <= 0) {
                timestamp[0] = 0;
            }

            if ((ext == nullptr) || detail::equals(ext, _T(".pwog"), true)) {
                // Write our custom binary format, starting with meta data.
                auto file = pwog_file::create(output, overwrite);
#if defined(_WIN32)
                file << make_pwog_meta_data("Command", ::GetCommandLineA());
#endif /* defined(_WIN32) */
                file << make_pwog_meta_data("Interval",
                    std::to_string(interval.count()));
                file << make_pwog_meta_data("Timespan",
                    std::to_string(timespan.count()));
                file << make_pwog_meta_data("Timestamp", timestamp);

                // Record the sensors.
                for (auto& s : sensors) {
                    file << s;
                }

                // Dump the samples.
                file.write(file_context.samples.data(),
                    file_context.samples.size());
            } else {
                // Assume CSV.
                std::ofstream stream(output,
                    overwrite ? std::ios::trunc : std::ios::app);

                std::vector<std::string> ids;
                if (use_id) {
                    ids.reserve(sensors.size());
                    std::transform(sensors.begin(),
                        sensors.end(),
                        std::back_inserter(ids), [](const auto& s) {
                            return convert_string<char>(s.id());
                        });
                }

#if defined(_WIN32)
                stream << "# Command: " << ::GetCommandLineA() << std::endl;
#endif /* defined(_WIN32) */
                stream << "# Interval (ms): " << interval.count() << std::endl;
                stream << "# Timespan (ms): " << timespan.count() << std::endl;
                stream << "# Timestamp (UTC): " << timestamp << std::endl;
                stream << "#" << std::endl;

                stream << "# Index;Sensor ID;Name;Path;Label;Unit"
                    << std::endl;
                std::size_t idx = 0;
                for (auto & s : sensors) {
                    stream << "#" << idx++ << ";";
                    stream << convert_string<char>(s.id()) << ";";
                    stream << convert_string<char>(s.name()) << ";";
                    stream << convert_string<char>(s.path()) << ";";
                    stream << convert_string<char>(s.label()) << ";";
                    stream << to_string<char>(s.reading_unit()) << std::endl;
                }

                stream << "Timestamp;Sensor;Reading" << std::endl;
                for (auto& s : file_context.samples) {
                    stream << s.timestamp << ";";

                    if (use_id) {
                        assert(s.source < ids.size());
                        stream << ids[s.source] << ";";
                    } else {
                        stream << s.source << ";";
                    }

                    switch (sensors[s.source].reading_type()) {
                        case reading_type::floating_point:
                            stream << s.reading.floating_point;
                            break;
                        case reading_type::signed_integer:
                            stream << s.reading.signed_integer;
                            break;
                        case reading_type::unsigned_integer:
                            stream << s.reading.unsigned_integer;
                            break;
                        default:
                            assert(false);
                            break;
                    }

                    stream << std::endl;
                }
            }
        }

        return 0;
    } catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
        return -1;
    }
}
