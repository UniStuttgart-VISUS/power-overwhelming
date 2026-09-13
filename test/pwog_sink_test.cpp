// <copyright file="pwog_sink_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for more information.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"

#include <visus/pwrowg/hmc8015_configuration.h>
#include <visus/pwrowg/pwog_sink.h>
#include <visus/pwrowg/thread_local_sink.h>
#include <visus/pwrowg/tinkerforge_configuration.h>
#include <visus/pwrowg/usb_pd_configuration.h>


PWROWG_TEST_NAMESPACE_BEGIN

TEST_CLASS(pwog_sink_test) {

    TEST_METHOD(via_array_char) {
        typedef thread_local_sink<pwog_sink> sink_type;

        sensor_array_configuration sensor_config;
        sensor_config.exclude<hmc8015_configuration>()
            .exclude<tinkerforge_configuration>()
            .exclude<usb_pd_configuration>();

        auto sink = std::make_unique<sink_type>(10, "pwog_sink_test.pwog");
        sensor_config.deliver_context(sink.get())
            .deliver_to(sink_type::sample_callback);

        auto sensors = sensor_array::for_all(std::move(sensor_config));
        sensors.start();
        std::this_thread::sleep_for(std::chrono::seconds(2));
        sensors.stop();

        sensors.start();
        std::this_thread::sleep_for(std::chrono::seconds(2));
        sensors.stop();

        sink.reset();

        auto file = pwog_file::read("pwog_sink_test.pwog");
        Assert::IsTrue(file, L"File was written.", LINE_INFO());
        Assert::IsNotNull(file["Timestamp"], L"Timestamp meta data was written.", LINE_INFO());
        Assert::IsNotNull(file["CommandLine"], L"CommandLine meta data was written.", LINE_INFO());
        Assert::IsTrue(file.sensors(nullptr, 0) > 0, L"Sensor meta data was written.", LINE_INFO());
    }

};

PWROWG_TEST_NAMESPACE_END
