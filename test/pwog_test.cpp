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
    }

};

PWROWG_TEST_NAMESPACE_END
