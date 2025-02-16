// <copyright file="usb_pd_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


PWROWG_TEST_NAMESPACE_BEGIN


TEST_CLASS(usb_pd_test) {

public:

    TEST_METHOD(test_descriptions) {
        typedef detail::usb_pd_sensor type;

        type::configuration_type config;
        std::vector<sensor_description> descs;
        descs.resize(type::descriptions(nullptr, 0, config));
        type::descriptions(descs.data(), descs.size(), config);

        for (auto& d : descs) {
            Assert::AreEqual(int(reading_type::floating_point), int(d.reading_type()), L"produces floats", LINE_INFO());
            Assert::AreEqual(L"PassMark", d.vendor(), L"Vendor name", LINE_INFO());
            Assert::AreNotEqual(std::size_t(0), ::wcslen(d.id()), L"ID not empty", LINE_INFO());
            Assert::AreNotEqual(std::size_t(0), ::wcslen(d.name()), L"Name not empty", LINE_INFO());
            Assert::AreNotEqual(std::size_t(0), ::wcslen(d.path()), L"Path not empty", LINE_INFO());
        }
    }

    TEST_METHOD(test_sensor_creation) {
        typedef detail::usb_pd_sensor type;

        type::configuration_type config;
        std::vector<sensor_description> descs;
        descs.resize(type::descriptions(nullptr, 0, config));
        type::descriptions(descs.data(), descs.size(), config);

        type::list_type sensors;
        const auto unused = type::from_descriptions(sensors, 0, descs.begin(), descs.end(), config);
        Assert::AreEqual(descs.size() / 2, sensors.size(), L"Created in groups of two", LINE_INFO());
        Assert::IsTrue(unused == descs.end(), L"All consumed", LINE_INFO());

        for (auto& s : sensors) {
            auto evt = create_event();

            s.sample([](const sample *samples, const std::size_t cnt, void *context) {
                Assert::AreEqual(std::size_t(1), cnt, L"USB PD creates single sample", LINE_INFO());
            });
        }
    }
};

PWROWG_TEST_NAMESPACE_END
