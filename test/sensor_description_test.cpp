// <copyright file="sensor_description_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


PWROWG_TEST_NAMESPACE_BEGIN


TEST_CLASS(sensor_description_test) {

public:

    TEST_METHOD(test_builder) {
        auto d = detail::sensor_description_builder::create()
            .with_id("id")
            .with_label(L"label")
            .with_name("name")
            .with_path("path")
            .with_private_data(42)
            .with_type(sensor_type::cpu)
            .with_vendor(L"vendor")
            .measured_in(reading_unit::ampere)
            .produces(reading_type::floating_point)
            .build();

        Assert::AreEqual(L"id", d.id(), L"id", LINE_INFO());
        Assert::AreEqual(L"label", d.label(), L"label", LINE_INFO());
        Assert::AreEqual(L"name", d.name(), L"name", LINE_INFO());
        Assert::AreEqual(L"path", d.path(), L"path", LINE_INFO());
        Assert::AreEqual(int(sensor_type::cpu), int(d.sensor_type()), L"sensor_type", LINE_INFO());
        Assert::AreEqual(L"vendor", d.vendor(), L"vendor", LINE_INFO());
        Assert::AreEqual(int(reading_unit::ampere), int(d.reading_unit()), L"reading_unit", LINE_INFO());
        Assert::AreEqual(int(reading_type::floating_point), int(d.reading_type()), L"reading_type", LINE_INFO());
        Assert::AreEqual(int(42), *detail::sensor_description_builder::private_data<int>(d), L"private_data", LINE_INFO());
    }

    TEST_METHOD(test_editable_type) {
        auto d = detail::sensor_description_builder::create()
            .with_editable_type(sensor_type::hardware | sensor_type::software)
            .with_type(sensor_type::cpu)
            .build();

        Assert::AreEqual(int(sensor_type::cpu), int(d.sensor_type()), L"sensor_type", LINE_INFO());
        d.sensor_type(sensor_type::hardware);
        Assert::AreEqual(int(sensor_type::cpu | sensor_type::hardware), int(d.sensor_type()), L"cpu not erased", LINE_INFO());
        d.sensor_type(sensor_type::software);
        Assert::AreEqual(int(sensor_type::cpu | sensor_type::software), int(d.sensor_type()), L"change hardware -> software", LINE_INFO());
        d.sensor_type(sensor_type::gpu);
        Assert::AreEqual(int(sensor_type::cpu), int(d.sensor_type()), L"erase everything, keep non-editable", LINE_INFO());
    }

    TEST_METHOD(test_sensor_registry) {
        Assert::IsTrue(detail::sensor_registry::size() > 0, L"Any sensor in registry", LINE_INFO());

        detail::sensor_array_configuration_impl config;
        std::vector<sensor_description> descs;
        detail::sensor_registry::configure(config);
        detail::sensor_registry::descriptions(std::back_inserter(descs), config);

        std::vector<std::shared_ptr<detail::sensor>> sensors;
        detail::sensor_registry::create(std::back_inserter(sensors), descs.begin(), descs.end());
    }

    TEST_METHOD(test_sampler_detection) {
        Assert::IsTrue(detail::sensor_array_impl::has_sync_sample<detail::nvml_sensor>::type::value, L"NVML is synchronous", LINE_INFO());
        Assert::IsFalse(detail::sensor_array_impl::has_async_sample<detail::nvml_sensor>::type::value, L"NVML is not asynchronous", LINE_INFO());
        Assert::IsTrue(detail::sensor_array_impl::has_async_sample<detail::tinkerforge_sensor>::type::value, L"NVML is asynchronous", LINE_INFO());
        Assert::IsFalse(detail::sensor_array_impl::has_sync_sample<detail::tinkerforge_sensor>::type::value, L"NVML is not synchronous", LINE_INFO());
    }
};

PWROWG_TEST_NAMESPACE_END
