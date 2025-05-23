// <copyright file="nvml_test.cpp" company="Visualisierungsinstitut der Universit�t Stuttgart">
// Copyright � 2021 Visualisierungsinstitut der Universit�t Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph M�ller</author>

#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


PWROWG_TEST_NAMESPACE_BEGIN


TEST_CLASS(nvml_test) {

public:

    TEST_METHOD(test_scope) {
#if defined(POWER_OVERWHELMING_WITH_NVML)
        detail::nvml_scope scope;
        Assert::IsTrue(true, L"Not crashed in scope ctor.", LINE_INFO());
#endif /* defined(POWER_OVERWHELMING_WITH_NVML) */
    }

    TEST_METHOD(test_descriptions) {
#if defined(POWER_OVERWHELMING_WITH_NVML)
        typedef detail::nvml_sensor type;

        type::configuration_type config;
        std::vector<sensor_description> descs;
        descs.resize(type::descriptions(nullptr, 0, config));
        type::descriptions(descs.data(), descs.size(), config);

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
#endif /* defined(POWER_OVERWHELMING_WITH_NVML) */
    }

    TEST_METHOD(test_sensor_creation) {
#if defined(POWER_OVERWHELMING_WITH_NVML)
        typedef detail::nvml_sensor type;

        type::configuration_type config;
        std::vector<sensor_description> descs;
        descs.resize(type::descriptions(nullptr, 0, config));
        type::descriptions(descs.data(), descs.size(), config);

        detail::sensor_array_impl dummy;

        type::list_type sensors;
        const auto unused = type::from_descriptions(sensors, 0, descs.begin(), descs.end(), &dummy, config);
        Assert::AreEqual(descs.size(), sensors.size(), L"Sensors created", LINE_INFO());
        Assert::IsTrue(unused == descs.end(), L"All consumed", LINE_INFO());

        for (auto& s : sensors) {
            s.sample([](const sample *samples, const std::size_t cnt, const sensor_description *sensors, void *context) {
                Assert::AreEqual(std::size_t(1), cnt, L"NVML creates single sample", LINE_INFO());
            }, descs.data());
        }
#endif /* defined(POWER_OVERWHELMING_WITH_NVML) */
    }
};

PWROWG_TEST_NAMESPACE_END
