// <copyright file="csv_sink_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for more information.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


PWROWG_TEST_NAMESPACE_BEGIN

TEST_CLASS(csv_sink_test) {

    TEST_METHOD(char_sink) {
        typedef std::ofstream stream_type;
        typedef atomic_sink<csv_sink<stream_type>> sink_type;

        sensor_array_configuration config;
        stream_type stream;
        stream.open("test.csv");
        stream << setcsvdelimiter(',');

        sink_type sink(std::chrono::milliseconds(100), std::move(stream));
        config.deliver_context(&sink)
            .deliver_to(sink_type::sample_callback);

        auto sensors = sensor_array::for_all(std::move(config));
        sensors.start();
        std::this_thread::sleep_for(std::chrono::seconds(2));
        sensors.stop();

        sensors.start();
        std::this_thread::sleep_for(std::chrono::seconds(2));
        sensors.stop();

        sink.dispose();
    }

    TEST_METHOD(wchar_t_sink) {
        typedef std::wofstream stream_type;
        typedef atomic_sink<csv_sink<stream_type>> sink_type;

        sensor_array_configuration config;
        stream_type stream;
        stream.open(L"test.csv");
        stream << setcsvdelimiter(L',');

        sink_type sink(std::chrono::milliseconds(100), std::move(stream));
        config.deliver_context(&sink)
            .deliver_to(sink_type::sample_callback);

        auto sensors = sensor_array::for_all(std::move(config));
        sensors.start();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        sensors.stop();

        sink.dispose();
    }
};

PWROWG_TEST_NAMESPACE_END
