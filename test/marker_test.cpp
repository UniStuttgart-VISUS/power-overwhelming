// <copyright file="marker_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 - 2026 Visualisierungsinstitut der Universität Stuttgart.
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

        sensor_array_configuration config;
        config.configure<marker_configuration>([](marker_configuration &c) { c += L"Erich"; })
            .exclude<hmc8015_configuration>()
            .exclude<tinkerforge_configuration>()
            .exclude<usb_pd_configuration>();

        auto sensors = sensor_array::for_matches(std::move(config), is_marker_sensor);
        Assert::AreEqual(std::size_t(1), sensors.markers(), L"# of markers", LINE_INFO());

        std::vector<sensor_description> descs;
        descs.resize(sensors.descriptions(nullptr, 0));
        sensors.descriptions(descs.data(), descs.size());
        Assert::AreEqual(std::size_t(1), descs.size(), L"Single sensor with marker", LINE_INFO());

        Assert::AreEqual(L"VISUS/Marker", descs[0].id(), L"Sensor ID", LINE_INFO());
        Assert::AreEqual(L"VISUS", descs[0].vendor(), L"Vendor", LINE_INFO());

        for (auto& s : sensors) {
            Assert::IsFalse(sensors.marker(0));
            sensors.start();
            Assert::IsFalse(sensors.marker(1));
            Assert::IsTrue(sensors.marker(0));
            sensors.stop();
        }
    }

    TEST_METHOD(test_marker_name) {
        typedef detail::marker_sensor type;

        sensor_array_configuration config;
        config.configure<marker_configuration>([](marker_configuration &c) { c += L"Erich"; })
            .exclude<hmc8015_configuration>()
            .exclude<tinkerforge_configuration>()
            .exclude<usb_pd_configuration>();

        auto sensors = sensor_array::for_matches(std::move(config), is_marker_sensor);

        {
            std::vector<wchar_t> name(sensors.marker(static_cast<wchar_t *>(nullptr), 0, 0));
            Assert::AreEqual(std::size_t(6), sensors.marker(name.data(), name.size(), 0), L"Buffer length", LINE_INFO());
            Assert::AreEqual(L"Erich", name.data(), L"Marker name", LINE_INFO());
        }

        {
            std::vector<char> name(sensors.marker(static_cast<char *>(nullptr), 0, 0));
            Assert::AreEqual(std::size_t(6), sensors.marker(name.data(), name.size(), 0), L"Buffer length", LINE_INFO());
            Assert::AreEqual("Erich", name.data(), L"Marker name", LINE_INFO());
        }

        Assert::AreEqual(std::size_t(0), sensors.marker(static_cast<wchar_t *>(nullptr), 0, 42), L"Inexistent marker", LINE_INFO());
        Assert::AreEqual(std::size_t(0), sensors.marker(static_cast<char *>(nullptr), 0, 42), L"Inexistent marker", LINE_INFO());
    }
};

PWROWG_TEST_NAMESPACE_END
