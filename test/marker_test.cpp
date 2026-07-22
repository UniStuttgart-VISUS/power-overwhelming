// <copyright file="marker_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 - 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"

#include <marker_sensor.h>
#include <visus/pwrowg/tinkerforge_configuration.h>
#include <visus/pwrowg/usb_pd_configuration.h>


PWROWG_TEST_NAMESPACE_BEGIN

TEST_CLASS(marker_test) {

public:

    TEST_METHOD(test_run) {
        typedef detail::marker_sensor type;

        sensor_array_configuration config;
        config.exclude<hmc8015_configuration>()
            .exclude<tinkerforge_configuration>()
            .exclude<usb_pd_configuration>();
        config.deliver_to([](const sample *s, std::size_t c, const sensor_description *d, void *) {
            Assert::AreEqual(int(reading_type::unsigned_integer), int(d[s->source].reading_type()), L"Correct value type", LINE_INFO());
            auto is1 = std::any_of(s, s + c, [](const sample& ss) { return (ss.reading.unsigned_integer == 1); });
            auto is2 = std::any_of(s, s + c, [](const sample& ss) { return (ss.reading.unsigned_integer == 2); });
            Assert::IsTrue(is1 || is2, L"Only 1 and 2 are emitted", LINE_INFO());
        });

        auto sensors = sensor_array::for_matches(std::move(config), is_marker_sensor);
        Assert::AreEqual(std::size_t(1), sensors.size(), L"Single description", LINE_INFO());

        auto controller = sensors.controller<marker_configuration>();
        Assert::IsNotNull(controller, L"Have marker controller", LINE_INFO());

        Assert::AreEqual(L"VISUS/Marker", sensors.begin()->id(), L"Sensor ID", LINE_INFO());
        Assert::AreEqual(L"VISUS", sensors.begin()->vendor(), L"Vendor", LINE_INFO());

        for (auto& s : sensors) {
            Assert::IsFalse(controller->emit(0u));
            sensors.start();
            Assert::IsTrue(controller->emit(1));
            Assert::IsTrue(controller->emit(2));
            sensors.stop();
            Assert::IsFalse(controller->emit(3));
        }
    }
};

PWROWG_TEST_NAMESPACE_END
