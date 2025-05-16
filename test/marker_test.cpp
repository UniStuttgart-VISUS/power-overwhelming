// <copyright file="marker_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


PWROWG_TEST_NAMESPACE_BEGIN


TEST_CLASS(marker_test) {

public:

    TEST_METHOD(test_descriptions) {
        marker_configuration config;
        Assert::AreEqual(std::size_t(0), config.size(), L"Empty", LINE_INFO());
        Assert::IsNull(config[0], L"No first marker", LINE_INFO());

        config += L"Erich";
        Assert::AreEqual(std::size_t(1), config.size(), L"One marker", LINE_INFO());
        Assert::AreEqual(L"Erich", config[0], L"First marker", LINE_INFO());
        Assert::IsNull(config[1], L"No second marker", LINE_INFO());

        config += L"Walter";
        Assert::AreEqual(std::size_t(2), config.size(), L"Two markers", LINE_INFO());
        Assert::AreEqual(L"Erich", config[0], L"First marker unchanged", LINE_INFO());
        Assert::AreEqual(L"Walter", config[1], L"Second marker", LINE_INFO());
        Assert::IsNull(config[2], L"No third marker", LINE_INFO());

        config.clear();
        Assert::AreEqual(std::size_t(0), config.size(), L"Empty", LINE_INFO());
        Assert::IsNull(config[0], L"No first marker", LINE_INFO());
    }

    TEST_METHOD(test_sensor_creation) {
        typedef detail::marker_sensor type;

        type::configuration_type config;
        Assert::AreEqual(std::size_t(0), type::descriptions(nullptr, 0, config), L"Nothing without marker", LINE_INFO());

        config += L"Erich";
        std::vector<sensor_description> descs;
        descs.resize(type::descriptions(nullptr, 0, config));
        type::descriptions(descs.data(), descs.size(), config);
        Assert::AreEqual(std::size_t(1), type::descriptions(nullptr, 0, config), L"Single sensor with marker", LINE_INFO());

        Assert::AreEqual(L"VISUS/Marker", descs[0].id(), L"Sensor ID", LINE_INFO());
        Assert::AreEqual(L"VISUS", descs[0].vendor(), L"Vendor", LINE_INFO());

        detail::sensor_array_impl dummy;

        type::list_type sensors;
        const auto unused = type::from_descriptions(sensors, 0, descs.begin(), descs.end(), &dummy, config);
        Assert::AreEqual(std::size_t(1), sensors.size(), L"Always one sensor", LINE_INFO());
        Assert::IsTrue(unused == descs.end(), L"All consumed", LINE_INFO());

        for (auto& s : sensors) {
            auto evt = create_event();

            //s.sample([](const sample *samples, const std::size_t cnt, const sensor_description *descs, void *context) {
            //    Assert::AreEqual(std::size_t(1), cnt, L"USB PD creates single sample", LINE_INFO());
            //}, descs.data(), nullptr);
        }
    }
};

PWROWG_TEST_NAMESPACE_END
