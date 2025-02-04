// <copyright file="nvml_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


PWROWG_TEST_NAMESPACE_BEGIN


TEST_CLASS(nvml_test) {

public:

    TEST_METHOD(test_scope) {
        detail::nvml_scope scope;
        Assert::IsTrue(true, L"Not crashed in scope ctor.", LINE_INFO());
    }

    TEST_METHOD(test_descriptions) {
        detail::nvml_sensor::configuration_type config;
        auto descs = detail::nvml_sensor::descriptions(config);

        for (auto& d : descs) {
            Assert::AreEqual(int(reading_unit::watt), int(d.reading_unit()), L"produces watts", LINE_INFO());
            Assert::AreEqual(int(reading_type::floating_point), int(d.reading_type()), L"produces floats", LINE_INFO());
            Assert::AreEqual(L"NVIDIA", d.vendor(), L"Vendor name", LINE_INFO());
            Assert::IsTrue((d.sensor_type() & sensor_type::gpu) == sensor_type::gpu, L"GPU sensor", LINE_INFO());
            Assert::IsTrue((d.sensor_type() & sensor_type::software) == sensor_type::software, L"Software sensor", LINE_INFO());
            Assert::IsTrue((d.sensor_type() & sensor_type::power) == sensor_type::power, L"Power sensor", LINE_INFO());
            Assert::AreNotEqual(std::size_t(0), ::wcslen(d.id()), L"ID not empty", LINE_INFO());
            Assert::AreNotEqual(std::size_t(0), ::wcslen(d.name()), L"Name not empty", LINE_INFO());
            Assert::AreNotEqual(std::size_t(0), ::wcslen(d.path()), L"Path not empty", LINE_INFO());
        }
    }

    //TEST_METHOD(test_sensor) {
    //    {
    //        auto sensors = nvml_sensor<measurement<>>::for_all();
    //    }

    //    Assert::ExpectException<nvml_exception>([](void) {
    //        auto sensor = nvml_sensor<measurement<>>::from_bus_id(nullptr);
    //    });

    //    Assert::ExpectException<nvml_exception>([](void) {
    //        auto sensor = nvml_sensor<measurement<>>::from_guid(nullptr);
    //    });

    //    Assert::ExpectException<nvml_exception>([](void) {
    //        auto sensor = nvml_sensor<measurement<>>::from_index(UINT_MAX);
    //    });

    //    Assert::ExpectException<nvml_exception>([](void) {
    //        auto sensor = nvml_sensor<measurement<>>::from_serial(nullptr);
    //    });

    //    {
    //        auto sensor = nvml_sensor<measurement<>>::from_index(0);
    //        auto measurement = sensor.sample();
    //    }
    //}
};

PWROWG_TEST_NAMESPACE_END
