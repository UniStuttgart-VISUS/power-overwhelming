// <copyright file="pwog_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"

#include <visus/pwrowg/pwog_file.h>

#include <sensor_description_builder.h>


PWROWG_TEST_NAMESPACE_BEGIN

TEST_CLASS(pwog_test) {

public:

    TEST_METHOD(read_write_char) {
        auto file = pwog_file::create("test.pwog", true);
        Assert::IsTrue(file, L"File valid", LINE_INFO());

        Assert::ExpectException<std::system_error>([&file](void) {
            file = pwog_file::create("test.pwog", false);
        }, L"Overwriting fails without force flag", LINE_INFO());

        {
            pwog_meta_data m("key1", "value1");
            file.write(m);
        }

        {
            pwog_meta_data m("key2", "value2");
            file << m;
        }

        Assert::AreEqual(std::size_t(0), file.meta_data(nullptr, 0), L"No meta data in write mode", LINE_INFO());

        Assert::ExpectException<std::logic_error>([&file](void) {
            sample s;
            file << s;
        }, L"Cannot write samples without descriptions", LINE_INFO());

        {
            detail::sensor_description_builder builder;
            auto d = builder
                .with_class(guid::create())
                .with_id("VISUS/Test1")
                .with_label(L"Label 1")
                .with_name("Test sensor #1")
                .with_path("test1")
                .with_type(sensor_type::external)
                .with_vendor(L"VISUS")
                .produces(reading_type::floating_point)
                .measured_in(reading_unit::watt)
                .build();
            file << d;

            std::array<sensor_description, 3> descs;
            descs[0] = builder
                .with_class(guid::create())
                .with_id("VISOS/Test2")
                .with_label(L"Label 2")
                .with_name("Test sensor #2")
                .with_path("test2")
                .with_type(sensor_type::memory)
                .with_vendor(L"VISOS")
                .produces(reading_type::signed_integer)
                .measured_in(reading_unit::ampere_hour)
                .build();
            descs[1] = builder
                .with_class(guid::create())
                .with_id("PLUS/Test3")
                .with_label(L"Label 3")
                .with_name("Test sensor #3")
                .with_path("test3")
                .with_type(sensor_type::software)
                .with_vendor(L"PLUS")
                .produces(reading_type::unsigned_integer)
                .measured_in(reading_unit::coulomb)
                .build();
            descs[2] = builder
                .with_class(guid::create())
                .with_id("NVIDIA/Test4")
                .with_label(L"Label 4")
                .with_name("Test sensor #4")
                .with_path("test4")
                .with_type(sensor_type::software)
                .with_vendor(L"Team Green")
                .produces(reading_type::floating_point)
                .measured_in(reading_unit::watt)
                .build();
            file.write(descs.data(), descs.size());
        }

        Assert::AreEqual(std::size_t(0), file.sensors(nullptr, 0), L"No sensor descriptions in write mode", LINE_INFO());

        Assert::ExpectException<std::logic_error>([&file](void) {
            pwog_meta_data m("key2", "value2");
            file << m;
        }, L"Cannot write any more meta data", LINE_INFO());

        {
            sample s(0, timestamp(42), 42.0f);
            file << s;
        }

        Assert::ExpectException<std::logic_error>([&file](void) {
            pwog_meta_data m("key2", "value2");
            file << m;
        }, L"Cannot write any more meta data", LINE_INFO());

        Assert::ExpectException<std::logic_error>([&file](void) {
            detail::sensor_description_builder builder;
            file << builder.build();
        }, L"Cannot write any more sensor descriptions", LINE_INFO());

        {
            std::array<sample, 3> samples{
                sample(1, timestamp(43), -43),
                sample(2, timestamp(44), 44),
                sample(3, timestamp(45), 45.0f),
            };
            file.write(samples.data(), samples.size());
        }

        file.close();
        Assert::IsFalse(file, L"File closed", LINE_INFO());

        file = pwog_file::read("test.pwog");
        Assert::IsTrue(file, L"File valid", LINE_INFO());

        {
            auto v = file["key1"];
            Assert::IsNotNull(v, L"key1 exists", LINE_INFO());
            Assert::AreEqual("value1", v, L"key1 value", LINE_INFO());
        }

        {
            auto v = file["key2"];
            Assert::IsNotNull(v, L"key2 exists", LINE_INFO());
            Assert::AreEqual("value2", v, L"key2 value", LINE_INFO());
        }

        {
            auto v = file["key3"];
            Assert::IsNull(v, L"key3 does not exist", LINE_INFO());
        }

        std::vector<const char *> keys(file.meta_data(nullptr, 0));
        Assert::AreEqual(std::size_t(2), keys.size(), L"Meta data count", LINE_INFO());
        file.meta_data(keys.data(), keys.size());
        Assert::IsTrue(std::find_if(keys.begin(), keys.end(),
            [](const char* key) { return std::strcmp(key, "key1") == 0; }) != keys.end(),
            L"Meta data key 1", LINE_INFO());
        Assert::IsTrue(std::find_if(keys.begin(), keys.end(),
            [](const char* key) { return std::strcmp(key, "key2") == 0; }) != keys.end(),
            L"Meta data key 2", LINE_INFO());

        {
            auto s = file[0];
            Assert::IsNotNull(s, L"Sensor 0 exists", LINE_INFO());
            Assert::AreEqual(L"VISUS/Test1", s->id(), L"Sensor 0 ID", LINE_INFO());
            Assert::AreEqual(L"Label 1", s->label(), L"Sensor 0 label", LINE_INFO());
            Assert::AreEqual(L"Test sensor #1", s->name(), L"Sensor 0 name", LINE_INFO());
            Assert::AreEqual(L"test1", s->path(), L"Sensor 0 path", LINE_INFO());
            Assert::AreEqual(L"VISUS", s->vendor(), L"Sensor 0 vendor", LINE_INFO());
            Assert::AreEqual(int(sensor_type::external), int(s->sensor_type()), L"Sensor 0 type", LINE_INFO());
            Assert::AreEqual(int(reading_type::floating_point), int(s->reading_type()), L"Sensor 0 reading type", LINE_INFO());
            Assert::AreEqual(int(reading_unit::watt), int(s->reading_unit()), L"Sensor 0 reading unit", LINE_INFO());
        }

        {
            auto s = file[1];
            Assert::IsNotNull(s, L"Sensor 1 exists", LINE_INFO());
            Assert::AreEqual(L"VISOS/Test2", s->id(), L"Sensor 1 ID", LINE_INFO());
            Assert::AreEqual(L"Label 2", s->label(), L"Sensor 1 label", LINE_INFO());
            Assert::AreEqual(L"Test sensor #2", s->name(), L"Sensor 1 name", LINE_INFO());
            Assert::AreEqual(L"test2", s->path(), L"Sensor 1 path", LINE_INFO());
            Assert::AreEqual(L"VISOS", s->vendor(), L"Sensor 1 vendor", LINE_INFO());
            Assert::AreEqual(int(sensor_type::memory), int(s->sensor_type()), L"Sensor 1 type", LINE_INFO());
            Assert::AreEqual(int(reading_type::signed_integer), int(s->reading_type()), L"Sensor 1 reading type", LINE_INFO());
            Assert::AreEqual(int(reading_unit::ampere_hour), int(s->reading_unit()), L"Sensor 1 reading unit", LINE_INFO());
        }

        {
            auto s = file[2];
            Assert::IsNotNull(s, L"Sensor 2 exists", LINE_INFO());
            Assert::AreEqual(L"PLUS/Test3", s->id(), L"Sensor 2 ID", LINE_INFO());
            Assert::AreEqual(L"Label 3", s->label(), L"Sensor 2 label", LINE_INFO());
            Assert::AreEqual(L"Test sensor #3", s->name(), L"Sensor 2 name", LINE_INFO());
            Assert::AreEqual(L"test3", s->path(), L"Sensor 2 path", LINE_INFO());
            Assert::AreEqual(L"PLUS", s->vendor(), L"Sensor 2 vendor", LINE_INFO());
            Assert::AreEqual(int(sensor_type::software), int(s->sensor_type()), L"Sensor 2 type", LINE_INFO());
            Assert::AreEqual(int(reading_type::unsigned_integer), int(s->reading_type()), L"Sensor 2 reading type", LINE_INFO());
            Assert::AreEqual(int(reading_unit::coulomb), int(s->reading_unit()), L"Sensor 2 reading unit", LINE_INFO());
        }

        {
            auto s = file[3];
            Assert::IsNotNull(s, L"Sensor 3 exists", LINE_INFO());
            Assert::AreEqual(L"NVIDIA/Test4", s->id(), L"Sensor 3 ID", LINE_INFO());
            Assert::AreEqual(L"Label 4", s->label(), L"Sensor 3 label", LINE_INFO());
            Assert::AreEqual(L"Test sensor #4", s->name(), L"Sensor 3 name", LINE_INFO());
            Assert::AreEqual(L"test4", s->path(), L"Sensor 3 path", LINE_INFO());
            Assert::AreEqual(L"Team Green", s->vendor(), L"Sensor 3 vendor", LINE_INFO());
            Assert::AreEqual(int(sensor_type::software), int(s->sensor_type()), L"Sensor 3 type", LINE_INFO());
            Assert::AreEqual(int(reading_type::floating_point), int(s->reading_type()), L"Sensor 3 reading type", LINE_INFO());
            Assert::AreEqual(int(reading_unit::watt), int(s->reading_unit()), L"Sensor 3 reading unit", LINE_INFO());
        }

        {
            auto s = file[4];
            Assert::IsNull(s, L"Sensor 4 does not exist", LINE_INFO());
        }

        std::vector<sensor_description> sensors(file.sensors(nullptr, 0));
        Assert::AreEqual(std::size_t(4), sensors.size(), L"Sensor count", LINE_INFO());
        file.sensors(sensors.data(), sensors.size());

        {
            auto& s = sensors[0];
            Assert::AreEqual(L"VISUS/Test1", s.id(), L"Sensor 0 ID", LINE_INFO());
            Assert::AreEqual(L"Label 1", s.label(), L"Sensor 0 label", LINE_INFO());
            Assert::AreEqual(L"Test sensor #1", s.name(), L"Sensor 0 name", LINE_INFO());
            Assert::AreEqual(L"test1", s.path(), L"Sensor 0 path", LINE_INFO());
            Assert::AreEqual(L"VISUS", s.vendor(), L"Sensor 0 vendor", LINE_INFO());
            Assert::AreEqual(int(sensor_type::external), int(s.sensor_type()), L"Sensor 0 type", LINE_INFO());
            Assert::AreEqual(int(reading_type::floating_point), int(s.reading_type()), L"Sensor 0 reading type", LINE_INFO());
            Assert::AreEqual(int(reading_unit::watt), int(s.reading_unit()), L"Sensor 0 reading unit", LINE_INFO());
        }

        {
            auto& s = sensors[1];
            Assert::AreEqual(L"VISOS/Test2", s.id(), L"Sensor 1 ID", LINE_INFO());
            Assert::AreEqual(L"Label 2", s.label(), L"Sensor 1 label", LINE_INFO());
            Assert::AreEqual(L"Test sensor #2", s.name(), L"Sensor 1 name", LINE_INFO());
            Assert::AreEqual(L"test2", s.path(), L"Sensor 1 path", LINE_INFO());
            Assert::AreEqual(L"VISOS", s.vendor(), L"Sensor 1 vendor", LINE_INFO());
            Assert::AreEqual(int(sensor_type::memory), int(s.sensor_type()), L"Sensor 1 type", LINE_INFO());
            Assert::AreEqual(int(reading_type::signed_integer), int(s.reading_type()), L"Sensor 1 reading type", LINE_INFO());
            Assert::AreEqual(int(reading_unit::ampere_hour), int(s.reading_unit()), L"Sensor 1 reading unit", LINE_INFO());
        }

        {
            auto& s = sensors[2];
            Assert::AreEqual(L"PLUS/Test3", s.id(), L"Sensor 2 ID", LINE_INFO());
            Assert::AreEqual(L"Label 3", s.label(), L"Sensor 2 label", LINE_INFO());
            Assert::AreEqual(L"Test sensor #3", s.name(), L"Sensor 2 name", LINE_INFO());
            Assert::AreEqual(L"test3", s.path(), L"Sensor 2 path", LINE_INFO());
            Assert::AreEqual(L"PLUS", s.vendor(), L"Sensor 2 vendor", LINE_INFO());
            Assert::AreEqual(int(sensor_type::software), int(s.sensor_type()), L"Sensor 2 type", LINE_INFO());
            Assert::AreEqual(int(reading_type::unsigned_integer), int(s.reading_type()), L"Sensor 2 reading type", LINE_INFO());
            Assert::AreEqual(int(reading_unit::coulomb), int(s.reading_unit()), L"Sensor 2 reading unit", LINE_INFO());
        }

        {
            auto& s = sensors[3];
            Assert::AreEqual(L"NVIDIA/Test4", s.id(), L"Sensor 3 ID", LINE_INFO());
            Assert::AreEqual(L"Label 4", s.label(), L"Sensor 3 label", LINE_INFO());
            Assert::AreEqual(L"Test sensor #4", s.name(), L"Sensor 3 name", LINE_INFO());
            Assert::AreEqual(L"test4", s.path(), L"Sensor 3 path", LINE_INFO());
            Assert::AreEqual(L"Team Green", s.vendor(), L"Sensor 3 vendor", LINE_INFO());
            Assert::AreEqual(int(sensor_type::software), int(s.sensor_type()), L"Sensor 3 type", LINE_INFO());
            Assert::AreEqual(int(reading_type::floating_point), int(s.reading_type()), L"Sensor 3 reading type", LINE_INFO());
            Assert::AreEqual(int(reading_unit::watt), int(s.reading_unit()), L"Sensor 3 reading unit", LINE_INFO());
        }

        {
            std::array<sample, 5> samples;
            const auto cnt = file.read(samples.data(), samples.size());
            Assert::AreEqual(std::size_t(4), cnt, L"Sample count", LINE_INFO());

            Assert::AreEqual(sample::source_type(0), samples[0].source, L"Sample 0 source", LINE_INFO());
            Assert::AreEqual(timestamp::value_type(42), samples[0].timestamp.value(), L"Sample 0 timestamp", LINE_INFO());
            Assert::AreEqual(42.0f, samples[0].reading.floating_point, L"Sample 0 reading", LINE_INFO());

            Assert::AreEqual(sample::source_type(1), samples[1].source, L"Sample 1 source", LINE_INFO());
            Assert::AreEqual(timestamp::value_type(43), samples[1].timestamp.value(), L"Sample 1 timestamp", LINE_INFO());
            Assert::AreEqual(-43, samples[1].reading.signed_integer, L"Sample 1 reading", LINE_INFO());

            Assert::AreEqual(sample::source_type(2), samples[2].source, L"Sample 2 source", LINE_INFO());
            Assert::AreEqual(timestamp::value_type(44), samples[2].timestamp.value(), L"Sample 2 timestamp", LINE_INFO());
            Assert::AreEqual(std::uint32_t(44), samples[2].reading.unsigned_integer, L"Sample 2 reading", LINE_INFO());

            Assert::AreEqual(sample::source_type(3), samples[3].source, L"Sample 3 source", LINE_INFO());
            Assert::AreEqual(timestamp::value_type(45), samples[3].timestamp.value(), L"Sample 3 timestamp", LINE_INFO());
            Assert::AreEqual(45.0f, samples[3].reading.floating_point, L"Sample 3 reading", LINE_INFO());
        }

        {
            std::array<sample, 5> samples;
            const auto cnt = file.read(1, samples.data(), samples.size());
            Assert::AreEqual(std::size_t(3), cnt, L"Sample count", LINE_INFO());

            Assert::AreEqual(sample::source_type(1), samples[0].source, L"Sample 1 source", LINE_INFO());
            Assert::AreEqual(timestamp::value_type(43), samples[0].timestamp.value(), L"Sample 1 timestamp", LINE_INFO());
            Assert::AreEqual(-43, samples[0].reading.signed_integer, L"Sample 1 reading", LINE_INFO());

            Assert::AreEqual(sample::source_type(2), samples[1].source, L"Sample 2 source", LINE_INFO());
            Assert::AreEqual(timestamp::value_type(44), samples[1].timestamp.value(), L"Sample 2 timestamp", LINE_INFO());
            Assert::AreEqual(std::uint32_t(44), samples[1].reading.unsigned_integer, L"Sample 2 reading", LINE_INFO());

            Assert::AreEqual(sample::source_type(3), samples[2].source, L"Sample 3 source", LINE_INFO());
            Assert::AreEqual(timestamp::value_type(45), samples[2].timestamp.value(), L"Sample 3 timestamp", LINE_INFO());
            Assert::AreEqual(45.0f, samples[2].reading.floating_point, L"Sample 3 reading", LINE_INFO());
        }

        {
            std::array<sample, 5> samples;
            const auto cnt = file.read(10, samples.data(), samples.size());
            Assert::AreEqual(std::size_t(0), cnt, L"Sample count", LINE_INFO());
        }

#if defined(POWER_OVERWHELMING_WITH_PARQUET)
        pwog_file::to_parquet("pwog.parquet", file, parquet_identity_column::id, false, 1);
#endif /* defined(POWER_OVERWHELMING_WITH_PARQUET) */
    }

    TEST_METHOD(read_write_wchar_t) {
        auto file = pwog_file::create(L"test.pwog", true);
        Assert::IsTrue(file, L"File valid", LINE_INFO());

        Assert::ExpectException<std::system_error>([&file](void) {
            file = pwog_file::create("test.pwog", false);
        }, L"Overwriting fails without force flag", LINE_INFO());

        {
            pwog_meta_data m("key1", "value1");
            file.write(m);
        }

        {
            pwog_meta_data m("key2", "value2");
            file << m;
        }

        Assert::AreEqual(std::size_t(0), file.meta_data(nullptr, 0), L"No meta data in write mode", LINE_INFO());

        Assert::ExpectException<std::logic_error>([&file](void) {
            sample s;
            file << s;
        }, L"Cannot write samples without descriptions", LINE_INFO());

        {
            detail::sensor_description_builder builder;
            auto d = builder
                .with_class(guid::create())
                .with_id("VISUS/Test1")
                .with_label(L"Label 1")
                .with_name("Test sensor #1")
                .with_path("test1")
                .with_type(sensor_type::external)
                .with_vendor(L"VISUS")
                .produces(reading_type::floating_point)
                .measured_in(reading_unit::watt)
                .build();
            file << d;

            std::array<sensor_description, 3> descs;
            descs[0] = builder
                .with_class(guid::create())
                .with_id("VISOS/Test2")
                .with_label(L"Label 2")
                .with_name("Test sensor #2")
                .with_path("test2")
                .with_type(sensor_type::memory)
                .with_vendor(L"VISOS")
                .produces(reading_type::signed_integer)
                .measured_in(reading_unit::ampere_hour)
                .build();
            descs[1] = builder
                .with_class(guid::create())
                .with_id("PLUS/Test3")
                .with_label(L"Label 3")
                .with_name("Test sensor #3")
                .with_path("test3")
                .with_type(sensor_type::software)
                .with_vendor(L"PLUS")
                .produces(reading_type::unsigned_integer)
                .measured_in(reading_unit::coulomb)
                .build();
            descs[2] = builder
                .with_class(guid::create())
                .with_id("NVIDIA/Test4")
                .with_label(L"Label 4")
                .with_name("Test sensor #4")
                .with_path("test4")
                .with_type(sensor_type::software)
                .with_vendor(L"Team Green")
                .produces(reading_type::floating_point)
                .measured_in(reading_unit::watt)
                .build();
            file.write(descs.data(), descs.size());
        }

        Assert::AreEqual(std::size_t(0), file.sensors(nullptr, 0), L"No sensor descriptions in write mode", LINE_INFO());

        Assert::ExpectException<std::logic_error>([&file](void) {
            pwog_meta_data m("key2", "value2");
            file << m;
        }, L"Cannot write any more meta data", LINE_INFO());

        {
            sample s(0, timestamp(42), 42.0f);
            file << s;
        }

        Assert::ExpectException<std::logic_error>([&file](void) {
            pwog_meta_data m("key2", "value2");
            file << m;
        }, L"Cannot write any more meta data", LINE_INFO());

        Assert::ExpectException<std::logic_error>([&file](void) {
            detail::sensor_description_builder builder;
            file << builder.build();
        }, L"Cannot write any more sensor descriptions", LINE_INFO());

        {
            std::array<sample, 3> samples{
                sample(1, timestamp(43), -43),
                sample(2, timestamp(44), 44),
                sample(3, timestamp(45), 45.0f),
            };
            file.write(samples.data(), samples.size());
        }

        file.close();
        Assert::IsFalse(file, L"File closed", LINE_INFO());

        file = pwog_file::read(L"test.pwog");
        Assert::IsTrue(file, L"File valid", LINE_INFO());

        {
            auto v = file["key1"];
            Assert::IsNotNull(v, L"key1 exists", LINE_INFO());
            Assert::AreEqual("value1", v, L"key1 value", LINE_INFO());
        }

        {
            auto v = file["key2"];
            Assert::IsNotNull(v, L"key2 exists", LINE_INFO());
            Assert::AreEqual("value2", v, L"key2 value", LINE_INFO());
        }

        {
            auto v = file["key3"];
            Assert::IsNull(v, L"key3 does not exist", LINE_INFO());
        }

        std::vector<const char *> keys(file.meta_data(nullptr, 0));
        Assert::AreEqual(std::size_t(2), keys.size(), L"Meta data count", LINE_INFO());
        file.meta_data(keys.data(), keys.size());
        Assert::IsTrue(std::find_if(keys.begin(), keys.end(),
            [](const char* key) { return std::strcmp(key, "key1") == 0; }) != keys.end(),
            L"Meta data key 1", LINE_INFO());
        Assert::IsTrue(std::find_if(keys.begin(), keys.end(),
            [](const char* key) { return std::strcmp(key, "key2") == 0; }) != keys.end(),
            L"Meta data key 2", LINE_INFO());

        {
            auto s = file[0];
            Assert::IsNotNull(s, L"Sensor 0 exists", LINE_INFO());
            Assert::AreEqual(L"VISUS/Test1", s->id(), L"Sensor 0 ID", LINE_INFO());
            Assert::AreEqual(L"Label 1", s->label(), L"Sensor 0 label", LINE_INFO());
            Assert::AreEqual(L"Test sensor #1", s->name(), L"Sensor 0 name", LINE_INFO());
            Assert::AreEqual(L"test1", s->path(), L"Sensor 0 path", LINE_INFO());
            Assert::AreEqual(L"VISUS", s->vendor(), L"Sensor 0 vendor", LINE_INFO());
            Assert::AreEqual(int(sensor_type::external), int(s->sensor_type()), L"Sensor 0 type", LINE_INFO());
            Assert::AreEqual(int(reading_type::floating_point), int(s->reading_type()), L"Sensor 0 reading type", LINE_INFO());
            Assert::AreEqual(int(reading_unit::watt), int(s->reading_unit()), L"Sensor 0 reading unit", LINE_INFO());
        }

        {
            auto s = file[1];
            Assert::IsNotNull(s, L"Sensor 1 exists", LINE_INFO());
            Assert::AreEqual(L"VISOS/Test2", s->id(), L"Sensor 1 ID", LINE_INFO());
            Assert::AreEqual(L"Label 2", s->label(), L"Sensor 1 label", LINE_INFO());
            Assert::AreEqual(L"Test sensor #2", s->name(), L"Sensor 1 name", LINE_INFO());
            Assert::AreEqual(L"test2", s->path(), L"Sensor 1 path", LINE_INFO());
            Assert::AreEqual(L"VISOS", s->vendor(), L"Sensor 1 vendor", LINE_INFO());
            Assert::AreEqual(int(sensor_type::memory), int(s->sensor_type()), L"Sensor 1 type", LINE_INFO());
            Assert::AreEqual(int(reading_type::signed_integer), int(s->reading_type()), L"Sensor 1 reading type", LINE_INFO());
            Assert::AreEqual(int(reading_unit::ampere_hour), int(s->reading_unit()), L"Sensor 1 reading unit", LINE_INFO());
        }

        {
            auto s = file[2];
            Assert::IsNotNull(s, L"Sensor 2 exists", LINE_INFO());
            Assert::AreEqual(L"PLUS/Test3", s->id(), L"Sensor 2 ID", LINE_INFO());
            Assert::AreEqual(L"Label 3", s->label(), L"Sensor 2 label", LINE_INFO());
            Assert::AreEqual(L"Test sensor #3", s->name(), L"Sensor 2 name", LINE_INFO());
            Assert::AreEqual(L"test3", s->path(), L"Sensor 2 path", LINE_INFO());
            Assert::AreEqual(L"PLUS", s->vendor(), L"Sensor 2 vendor", LINE_INFO());
            Assert::AreEqual(int(sensor_type::software), int(s->sensor_type()), L"Sensor 2 type", LINE_INFO());
            Assert::AreEqual(int(reading_type::unsigned_integer), int(s->reading_type()), L"Sensor 2 reading type", LINE_INFO());
            Assert::AreEqual(int(reading_unit::coulomb), int(s->reading_unit()), L"Sensor 2 reading unit", LINE_INFO());
        }

        {
            auto s = file[3];
            Assert::IsNotNull(s, L"Sensor 3 exists", LINE_INFO());
            Assert::AreEqual(L"NVIDIA/Test4", s->id(), L"Sensor 3 ID", LINE_INFO());
            Assert::AreEqual(L"Label 4", s->label(), L"Sensor 3 label", LINE_INFO());
            Assert::AreEqual(L"Test sensor #4", s->name(), L"Sensor 3 name", LINE_INFO());
            Assert::AreEqual(L"test4", s->path(), L"Sensor 3 path", LINE_INFO());
            Assert::AreEqual(L"Team Green", s->vendor(), L"Sensor 3 vendor", LINE_INFO());
            Assert::AreEqual(int(sensor_type::software), int(s->sensor_type()), L"Sensor 3 type", LINE_INFO());
            Assert::AreEqual(int(reading_type::floating_point), int(s->reading_type()), L"Sensor 3 reading type", LINE_INFO());
            Assert::AreEqual(int(reading_unit::watt), int(s->reading_unit()), L"Sensor 3 reading unit", LINE_INFO());
        }

        {
            auto s = file[4];
            Assert::IsNull(s, L"Sensor 4 does not exist", LINE_INFO());
        }

        std::vector<sensor_description> sensors(file.sensors(nullptr, 0));
        Assert::AreEqual(std::size_t(4), sensors.size(), L"Sensor count", LINE_INFO());
        file.sensors(sensors.data(), sensors.size());

        {
            auto& s = sensors[0];
            Assert::AreEqual(L"VISUS/Test1", s.id(), L"Sensor 0 ID", LINE_INFO());
            Assert::AreEqual(L"Label 1", s.label(), L"Sensor 0 label", LINE_INFO());
            Assert::AreEqual(L"Test sensor #1", s.name(), L"Sensor 0 name", LINE_INFO());
            Assert::AreEqual(L"test1", s.path(), L"Sensor 0 path", LINE_INFO());
            Assert::AreEqual(L"VISUS", s.vendor(), L"Sensor 0 vendor", LINE_INFO());
            Assert::AreEqual(int(sensor_type::external), int(s.sensor_type()), L"Sensor 0 type", LINE_INFO());
            Assert::AreEqual(int(reading_type::floating_point), int(s.reading_type()), L"Sensor 0 reading type", LINE_INFO());
            Assert::AreEqual(int(reading_unit::watt), int(s.reading_unit()), L"Sensor 0 reading unit", LINE_INFO());
        }

        {
            auto& s = sensors[1];
            Assert::AreEqual(L"VISOS/Test2", s.id(), L"Sensor 1 ID", LINE_INFO());
            Assert::AreEqual(L"Label 2", s.label(), L"Sensor 1 label", LINE_INFO());
            Assert::AreEqual(L"Test sensor #2", s.name(), L"Sensor 1 name", LINE_INFO());
            Assert::AreEqual(L"test2", s.path(), L"Sensor 1 path", LINE_INFO());
            Assert::AreEqual(L"VISOS", s.vendor(), L"Sensor 1 vendor", LINE_INFO());
            Assert::AreEqual(int(sensor_type::memory), int(s.sensor_type()), L"Sensor 1 type", LINE_INFO());
            Assert::AreEqual(int(reading_type::signed_integer), int(s.reading_type()), L"Sensor 1 reading type", LINE_INFO());
            Assert::AreEqual(int(reading_unit::ampere_hour), int(s.reading_unit()), L"Sensor 1 reading unit", LINE_INFO());
        }

        {
            auto& s = sensors[2];
            Assert::AreEqual(L"PLUS/Test3", s.id(), L"Sensor 2 ID", LINE_INFO());
            Assert::AreEqual(L"Label 3", s.label(), L"Sensor 2 label", LINE_INFO());
            Assert::AreEqual(L"Test sensor #3", s.name(), L"Sensor 2 name", LINE_INFO());
            Assert::AreEqual(L"test3", s.path(), L"Sensor 2 path", LINE_INFO());
            Assert::AreEqual(L"PLUS", s.vendor(), L"Sensor 2 vendor", LINE_INFO());
            Assert::AreEqual(int(sensor_type::software), int(s.sensor_type()), L"Sensor 2 type", LINE_INFO());
            Assert::AreEqual(int(reading_type::unsigned_integer), int(s.reading_type()), L"Sensor 2 reading type", LINE_INFO());
            Assert::AreEqual(int(reading_unit::coulomb), int(s.reading_unit()), L"Sensor 2 reading unit", LINE_INFO());
        }

        {
            auto& s = sensors[3];
            Assert::AreEqual(L"NVIDIA/Test4", s.id(), L"Sensor 3 ID", LINE_INFO());
            Assert::AreEqual(L"Label 4", s.label(), L"Sensor 3 label", LINE_INFO());
            Assert::AreEqual(L"Test sensor #4", s.name(), L"Sensor 3 name", LINE_INFO());
            Assert::AreEqual(L"test4", s.path(), L"Sensor 3 path", LINE_INFO());
            Assert::AreEqual(L"Team Green", s.vendor(), L"Sensor 3 vendor", LINE_INFO());
            Assert::AreEqual(int(sensor_type::software), int(s.sensor_type()), L"Sensor 3 type", LINE_INFO());
            Assert::AreEqual(int(reading_type::floating_point), int(s.reading_type()), L"Sensor 3 reading type", LINE_INFO());
            Assert::AreEqual(int(reading_unit::watt), int(s.reading_unit()), L"Sensor 3 reading unit", LINE_INFO());
        }

        {
            std::array<sample, 5> samples;
            const auto cnt = file.read(samples.data(), samples.size());
            Assert::AreEqual(std::size_t(4), cnt, L"Sample count", LINE_INFO());

            Assert::AreEqual(sample::source_type(0), samples[0].source, L"Sample 0 source", LINE_INFO());
            Assert::AreEqual(timestamp::value_type(42), samples[0].timestamp.value(), L"Sample 0 timestamp", LINE_INFO());
            Assert::AreEqual(42.0f, samples[0].reading.floating_point, L"Sample 0 reading", LINE_INFO());

            Assert::AreEqual(sample::source_type(1), samples[1].source, L"Sample 1 source", LINE_INFO());
            Assert::AreEqual(timestamp::value_type(43), samples[1].timestamp.value(), L"Sample 1 timestamp", LINE_INFO());
            Assert::AreEqual(-43, samples[1].reading.signed_integer, L"Sample 1 reading", LINE_INFO());

            Assert::AreEqual(sample::source_type(2), samples[2].source, L"Sample 2 source", LINE_INFO());
            Assert::AreEqual(timestamp::value_type(44), samples[2].timestamp.value(), L"Sample 2 timestamp", LINE_INFO());
            Assert::AreEqual(std::uint32_t(44), samples[2].reading.unsigned_integer, L"Sample 2 reading", LINE_INFO());

            Assert::AreEqual(sample::source_type(3), samples[3].source, L"Sample 3 source", LINE_INFO());
            Assert::AreEqual(timestamp::value_type(45), samples[3].timestamp.value(), L"Sample 3 timestamp", LINE_INFO());
            Assert::AreEqual(45.0f, samples[3].reading.floating_point, L"Sample 3 reading", LINE_INFO());
        }

        {
            std::array<sample, 5> samples;
            const auto cnt = file.read(1, samples.data(), samples.size());
            Assert::AreEqual(std::size_t(3), cnt, L"Sample count", LINE_INFO());

            Assert::AreEqual(sample::source_type(1), samples[0].source, L"Sample 1 source", LINE_INFO());
            Assert::AreEqual(timestamp::value_type(43), samples[0].timestamp.value(), L"Sample 1 timestamp", LINE_INFO());
            Assert::AreEqual(-43, samples[0].reading.signed_integer, L"Sample 1 reading", LINE_INFO());

            Assert::AreEqual(sample::source_type(2), samples[1].source, L"Sample 2 source", LINE_INFO());
            Assert::AreEqual(timestamp::value_type(44), samples[1].timestamp.value(), L"Sample 2 timestamp", LINE_INFO());
            Assert::AreEqual(std::uint32_t(44), samples[1].reading.unsigned_integer, L"Sample 2 reading", LINE_INFO());

            Assert::AreEqual(sample::source_type(3), samples[2].source, L"Sample 3 source", LINE_INFO());
            Assert::AreEqual(timestamp::value_type(45), samples[2].timestamp.value(), L"Sample 3 timestamp", LINE_INFO());
            Assert::AreEqual(45.0f, samples[2].reading.floating_point, L"Sample 3 reading", LINE_INFO());
        }

        {
            std::array<sample, 5> samples;
            const auto cnt = file.read(10, samples.data(), samples.size());
            Assert::AreEqual(std::size_t(0), cnt, L"Sample count", LINE_INFO());
        }

#if defined(POWER_OVERWHELMING_WITH_PARQUET)
        pwog_file::to_parquet(L"pwog.parquet", file, parquet_identity_column::id, false, 1);
#endif /* defined(POWER_OVERWHELMING_WITH_PARQUET) */
    }

};

PWROWG_TEST_NAMESPACE_END
