// <copyright file="pwoginfo.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

#include "visus/pwrowg/convert_string.h"
#include "visus/pwrowg/pwog_file.h"
#include "visus/pwrowg/string_functions.h"


/// <summary>
/// Finds the command line switch <paramref name="name"/> in the given command
/// line.
/// </summary>
template<class TIterator> TIterator find_switch(_In_ const TIterator begin,
        _In_ const TIterator end, _In_z_ const char *name) {
    return std::find_if(begin, end, [name](_In_ const char *arg) {
        return visus::pwrowg::detail::equals(arg, name, true);
    });
}

/// <summary>
/// Finds the value of the command line argument <paramref name="name"/> in the
/// given command line.
/// </summary>
template<class TIterator> TIterator find_argument(_In_ const TIterator begin,
        _In_ const TIterator end, _In_z_ const char *name) {
    auto retval = find_switch(begin, end, name);
    if (retval != end) {
        ++retval;
    }
    return retval;
}


/// <summary>
/// Entry point of the pwoginfo application, which shows a summary of the
/// contents of a PWOG file.
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
int main(const int argc, const char **argv) {
    using namespace visus::pwrowg;
    typedef std::underlying_type_t<reading_type> reading_t;
    typedef std::underlying_type_t<sensor_type> sensor_t;
    typedef std::underlying_type_t<reading_unit> unit_t;

    const auto end = argv + argc;

    try {
        // Process command line arguments.
        const char *path = nullptr;
        {
            auto it = ::find_argument(argv, end, "--path");
            if (it == end) {
                throw std::invalid_argument("Missing required argument --path");
            }
            path = *it;
        }

        const auto statistics = (::find_switch(argv, end, "--statistics") != end);

        // Read and dump embedded meta data.
        auto file = pwog_file::read(path);

        std::vector<const char *> meta_data(file.meta_data(nullptr, 0));
        file.meta_data(meta_data.data(), meta_data.size());

        std::cout << "Meta data:" << std::endl;
        for (auto m : meta_data) {
            std::cout << "\t" << m << ": " << file[m] << std::endl;
        }

        std::vector<sensor_description> sensors(file.sensors(nullptr, 0));
        file.sensors(sensors.data(), sensors.size());

        std::cout << std::endl << "Sensors:" << std::endl;
        for (auto& s : sensors) {
            std::cout << convert_string<char>(s.id()) << std::endl;
            std::cout << "\tName: " << convert_string<char>(s.name())
                << std::endl;
            std::cout << "\tLabel: " << convert_string<char>(s.label())
                << std::endl;
            std::cout << "\tVendor: " << convert_string<char>(s.vendor())
                << std::endl;
            std::cout << "\tPath: " << convert_string<char>(s.path())
                << std::endl;
            std::cout << "\tClass: " << s.sensor_class().to_string<char>()
                << std::endl;
            std::cout << "\tType: 0x"
                << std::hex << static_cast<sensor_t>(s.sensor_type())
                << std::dec << std::endl;
            std::cout << "\tReading type: " << visus::pwrowg::to_string<char>(
                s.reading_type()) << std::endl;
            std::cout << "\tUnit: " << visus::pwrowg::to_string<char>(
                s.reading_unit()) << std::endl;
        }

        std::cout << std::endl << "Expected samples: " << file.samples()
            << std::endl;

        if (statistics) {
            auto begin = (std::numeric_limits<timestamp::value_type>::max)();
            auto end = (std::numeric_limits<timestamp::value_type>::min)();
            std::vector<float> averages(sensors.size(), 0.0f);
            std::vector<float> minima(sensors.size(),
                (std::numeric_limits<float>::max)());
            std::vector<float> maxima(sensors.size(),
                (std::numeric_limits<float>::min)());
            std::vector<sample> samples(1024);
            std::size_t total = 0;
            std::vector<std::size_t> totals(sensors.size(), 0);

            std::size_t cnt = 0;
            while ((cnt = file.read(samples.data(), samples.size())) > 0) {
                for (std::size_t i = 0; i < cnt; ++i, ++total) {
                    const auto& sample = samples[i];
                    auto& average = averages[sample.source];
                    auto& maximum = maxima[sample.source];
                    auto& minimum = minima[sample.source];
                    auto& total = ++totals[sample.source];

                    if (sample.timestamp.value() < begin) {
                        begin = sample.timestamp.value();
                    }

                    if (sample.timestamp.value() > end) {
                        end = sample.timestamp.value();
                    }

                    assert(sample.source < sensors.size());
                    switch (sensors[sample.source].reading_type()) {
                        case reading_type::floating_point: {
                            const auto reading = sample.reading.floating_point;

                            if (reading < minimum) {
                                minimum = reading;
                            }

                            if (reading > maximum) {
                                maximum = reading;
                            }

                            average += (reading - average) / total;
                            } break;

                        case reading_type::signed_integer: {
                            const auto reading = static_cast<float>(
                                sample.reading.signed_integer);

                            if (reading < minimum) {
                                minimum = reading;
                            }

                            if (reading > maximum) {
                                maximum = reading;
                            }

                            average += (reading - average) / total;
                            } break;

                        case reading_type::unsigned_integer: {
                            const auto reading = static_cast<float>(
                                sample.reading.unsigned_integer);

                            if (reading < minimum) {
                                minimum = reading;
                            }

                            if (reading > maximum) {
                                maximum = reading;
                            }

                            average += (reading - average) / total;
                            } break;
                    }
                }
            }

            std::cout << std::endl << "Statistics:" << std::endl;
            std::cout << "\tBegin: " << begin << std::endl;
            std::cout << "\tEnd: " << end << std::endl;
            std::cout << "\tTotal samples: " << total << std::endl;
            assert(totals.size() == sensors.size());
            for (std::size_t i = 0; i < totals.size(); ++i) {
                const auto s = convert_string<char>(sensors[i].id());
                std::cout << "\tSamples from " << s << ": " << totals[i]
                    << std::endl;
                std::cout << "\tMinimum of " << s << ": "
                    << minima[i] << std::endl;
                std::cout << "\tAverage of " << s << ": "
                    << averages[i] << std::endl;
                std::cout << "\tMaximum of " << s << ": "
                    << maxima[i] << std::endl;
            }
        }

        return 0;
    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return -1;
    }
}
