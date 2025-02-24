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

    TEST_METHOD(test_enumeration) {
        auto paths = ::usb_pd_tester_enumerate(1000, 100);

        if (paths != nullptr) {
            auto p = paths;

            while (*p != 0) {
                auto tester = ::usb_pd_tester_open(p);
                Assert::IsNotNull(tester, L"Can open tester", LINE_INFO());
                ::usb_pd_tester_close(tester);
                p += ::strlen(p) + 1;
            }
        }

        ::usb_pd_tester_free(paths);
    }

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

        detail::sensor_array_impl dummy;

        type::list_type sensors;
        const auto unused = type::from_descriptions(sensors, 0, descs.begin(), descs.end(), &dummy, config);
        Assert::AreEqual(descs.size() / 2, sensors.size(), L"Created in groups of two", LINE_INFO());
        Assert::IsTrue(unused == descs.end(), L"All consumed", LINE_INFO());

        for (auto& s : sensors) {
            auto evt = create_event();

            s.sample([](const sample *samples, const std::size_t cnt, const sensor_description *descs, void *context) {
                Assert::AreEqual(std::size_t(1), cnt, L"USB PD creates single sample", LINE_INFO());
            }, descs.data(), nullptr);
        }
    }
};

PWROWG_TEST_NAMESPACE_END
