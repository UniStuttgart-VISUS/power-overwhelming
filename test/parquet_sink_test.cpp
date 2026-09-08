// <copyright file="parquet_sink_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for more information.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"

#if defined(POWER_OVERWHELMING_WITH_PARQUET)
#include <arrow/io/api.h>

#include <parquet/arrow/reader.h>

#include <visus/pwrowg/hmc8015_configuration.h>
#include <visus/pwrowg/parquet_sink.h>
#include <visus/pwrowg/thread_local_sink.h>
#include <visus/pwrowg/tinkerforge_configuration.h>
#include <visus/pwrowg/usb_pd_configuration.h>


PWROWG_TEST_NAMESPACE_BEGIN

TEST_CLASS(parquet_sink_test) {

    TEST_METHOD(id_float) {
        typedef thread_local_sink<parquet_sink> sink_type;

        parquet_configuration output_config(L"id_float.parquet");
        output_config.identity(parquet_identity_column::id);
        output_config.raw(false);

        sensor_array_configuration sensor_config;
        sensor_config.exclude<hmc8015_configuration>()
            .exclude<tinkerforge_configuration>()
            .exclude<usb_pd_configuration>();

        sink_type sink(10, output_config);
        sensor_config.deliver_context(&sink)
            .deliver_to(sink_type::sample_callback);

        auto sensors = sensor_array::for_all(std::move(sensor_config));
        sensors.start();
        std::this_thread::sleep_for(std::chrono::seconds(2));
        sensors.stop();

        sensors.start();
        std::this_thread::sleep_for(std::chrono::seconds(2));
        sensors.stop();

        sink.dispose();

        auto file = arrow::io::ReadableFile::Open("id_float.parquet");
        Assert::IsTrue(file.ok(), L"Open file", LINE_INFO());

        auto reader = parquet::arrow::OpenFile(*file, arrow::default_memory_pool());
        Assert::IsTrue(reader.ok(), L"Open reader", LINE_INFO());

        std::shared_ptr<arrow::Table> table;
        Assert::IsTrue(reader.ValueUnsafe()->ReadTable(&table).ok(), L"Read table", LINE_INFO());
    }

    TEST_METHOD(label_raw) {
        typedef thread_local_sink<parquet_sink> sink_type;

        parquet_configuration output_config(L"label_raw.parquet");
        output_config.identity(parquet_identity_column::label);
        output_config.raw(true);

        sensor_array_configuration sensor_config;
        sensor_config.exclude<hmc8015_configuration>()
            .exclude<tinkerforge_configuration>()
            .exclude<usb_pd_configuration>();

        sink_type sink(10, output_config);
        sensor_config.deliver_context(&sink)
            .deliver_to(sink_type::sample_callback);

        auto sensors = sensor_array::for_all(std::move(sensor_config));
        sensors.start();
        std::this_thread::sleep_for(std::chrono::seconds(2));
        sensors.stop();

        sensors.start();
        std::this_thread::sleep_for(std::chrono::seconds(2));
        sensors.stop();

        sink.dispose();
    }

};

PWROWG_TEST_NAMESPACE_END
#endif /* defined(POWER_OVERWHELMING_WITH_PARQUET) */
