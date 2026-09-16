// <copyright file="hdf5_sink_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for more information.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"

#include <visus/pwrowg/hdf5_sink.h>
#include <visus/pwrowg/hmc8015_configuration.h>
#include <visus/pwrowg/thread_local_sink.h>
#include <visus/pwrowg/tinkerforge_configuration.h>
#include <visus/pwrowg/usb_pd_configuration.h>


PWROWG_TEST_NAMESPACE_BEGIN

#if defined(POWER_OVERWHELMING_WITH_HDF5)
TEST_CLASS(hdf5_sink_test) {

    TEST_METHOD(from_char_path) {
        typedef thread_local_sink<hdf5_sink> sink_type;

        sensor_array_configuration sensor_config;
        sensor_config.exclude<hmc8015_configuration>()
            .exclude<tinkerforge_configuration>()
            .exclude<usb_pd_configuration>();

        hdf5_configuration sink_config("pwog_sink_test.h5", true);
        sink_config.chunk_size(10).raw(false);

        auto sink = std::make_unique<sink_type>(10, true, sink_config);
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
    }

};
#endif /* defined(POWER_OVERWHELMING_WITH_HDF5) */

PWROWG_TEST_NAMESPACE_END
