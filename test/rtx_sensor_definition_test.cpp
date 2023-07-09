// <copyright file="rtx_sensor_definition_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace visus {
namespace power_overwhelming {
namespace test {

    TEST_CLASS(rtx_sensor_definition_test) {

    public:

        TEST_METHOD(test_ctor) {
            Assert::ExpectException<std::invalid_argument>([](void) {
                rtx_sensor_definition d(nullptr, oscilloscope_channel(0), oscilloscope_channel(1));
            }, L"Invalid description", LINE_INFO());

            Assert::ExpectException<std::invalid_argument>([](void) {
                rtx_sensor_definition d(nullptr, 0, 0.1f, 1, 0.2f);
            }, L"Invalid description", LINE_INFO());

            Assert::ExpectException<std::invalid_argument>([](void) {
                rtx_sensor_definition d(L"test", oscilloscope_channel(0), oscilloscope_channel(0));
            }, L"Invalid channels", LINE_INFO());

            Assert::ExpectException<std::invalid_argument>([](void) {
                rtx_sensor_definition d(L"test", 0, 0.1f, 0, 0.2f);
            }, L"Invalid channels", LINE_INFO());

            {
                rtx_sensor_definition d(L"Horst",
                    oscilloscope_channel(1).attenuation(oscilloscope_quantity(0.1f, "V")),
                    oscilloscope_channel(2).attenuation(oscilloscope_quantity(0.2f, "A")),
                    oscilloscope_waveform_points::visible);
                Assert::AreEqual(L"Horst", d.description(), L"Description is \"Horst\"", LINE_INFO());
                Assert::AreEqual(std::uint32_t(1), d.channel_voltage(), L"Channel for voltage", LINE_INFO());
                Assert::AreEqual(std::uint32_t(2), d.channel_current(), L"Channel for current", LINE_INFO());
                Assert::AreEqual(0.1f, d.attenuation_voltage().value(), L"Attenuation of voltage", LINE_INFO());
                Assert::AreEqual(0.2f, d.attenuation_current().value(), L"Attenuation of current", LINE_INFO());
                Assert::AreEqual(int(oscilloscope_waveform_points::visible), int(d.waveform_points()), L"Waveform points", LINE_INFO());
            }

            {
                rtx_sensor_definition d(L"Horst", 1, 0.1f, 2, 0.2f, oscilloscope_waveform_points::visible);
                Assert::AreEqual(L"Horst", d.description(), L"Description is \"Horst\"", LINE_INFO());
                Assert::AreEqual(std::uint32_t(1), d.channel_voltage(), L"Channel for voltage", LINE_INFO());
                Assert::AreEqual(std::uint32_t(2), d.channel_current(), L"Channel for current", LINE_INFO());
                Assert::AreEqual(0.1f, d.attenuation_voltage().value(), L"Attenuation of voltage", LINE_INFO());
                Assert::AreEqual(0.2f, d.attenuation_current().value(), L"Attenuation of current", LINE_INFO());
                Assert::AreEqual(int(oscilloscope_waveform_points::visible), int(d.waveform_points()), L"Waveform points", LINE_INFO());
            }
        }

        TEST_METHOD(test_assignment) {
            {
                rtx_sensor_definition d(L"Horst",
                    oscilloscope_channel(1).attenuation(oscilloscope_quantity(0.1f, "V")),
                    oscilloscope_channel(2).attenuation(oscilloscope_quantity(0.2f, "A")));
                Assert::AreEqual(L"Horst", d.description(), L"Description is \"Horst\"", LINE_INFO());
                Assert::AreEqual(std::uint32_t(1), d.channel_voltage(), L"Channel for voltage", LINE_INFO());
                Assert::AreEqual(std::uint32_t(2), d.channel_current(), L"Channel for current", LINE_INFO());
                Assert::AreEqual(0.1f, d.attenuation_voltage().value(), L"Attenuation of voltage", LINE_INFO());
                Assert::AreEqual(0.2f, d.attenuation_current().value(), L"Attenuation of current", LINE_INFO());
                Assert::AreEqual(int(oscilloscope_waveform_points::maximum), int(d.waveform_points()), L"Waveform points", LINE_INFO());

                rtx_sensor_definition dd(L"Hugo",
                    oscilloscope_channel(3),
                    oscilloscope_channel(4),
                    oscilloscope_waveform_points::visible);
                Assert::AreEqual(L"Hugo", dd.description(), L"Description is \"Hugo\"", LINE_INFO());
                Assert::AreEqual(std::uint32_t(3), dd.channel_voltage(), L"Channel for voltage", LINE_INFO());
                Assert::AreEqual(std::uint32_t(4), dd.channel_current(), L"Channel for current", LINE_INFO());
                Assert::AreEqual(0.0f, dd.attenuation_voltage().value(), L"Attenuation of voltage", LINE_INFO());
                Assert::AreEqual(0.0f, dd.attenuation_current().value(), L"Attenuation of current", LINE_INFO());
                Assert::AreEqual(int(oscilloscope_waveform_points::visible), int(dd.waveform_points()), L"Waveform points", LINE_INFO());

                dd = d;
                Assert::AreEqual(d.description(), dd.description(), L"Description copied", LINE_INFO());
                Assert::AreEqual(d.channel_voltage(), dd.channel_voltage(), L"Channel for voltage copied", LINE_INFO());
                Assert::AreEqual(d.channel_current(), dd.channel_current(), L"Channel for current copied", LINE_INFO());
                Assert::AreEqual(d.attenuation_voltage().value(), dd.attenuation_voltage().value(), L"Attenuation of voltage copied", LINE_INFO());
                Assert::AreEqual(d.attenuation_current().value(), dd.attenuation_current().value(), L"Attenuation of current copied", LINE_INFO());
                Assert::AreEqual(int(d.waveform_points()), int(dd.waveform_points()), L"Waveform points", LINE_INFO());
            }

            {
                rtx_sensor_definition d(L"Horst",
                    oscilloscope_channel(1).attenuation(oscilloscope_quantity(0.1f, "V")),
                    oscilloscope_channel(2).attenuation(oscilloscope_quantity(0.2f, "A")),
                    oscilloscope_waveform_points::maximum_visible);
                Assert::AreEqual(L"Horst", d.description(), L"Description is \"Horst\"", LINE_INFO());
                Assert::AreEqual(std::uint32_t(1), d.channel_voltage(), L"Channel for voltage", LINE_INFO());
                Assert::AreEqual(std::uint32_t(2), d.channel_current(), L"Channel for current", LINE_INFO());
                Assert::AreEqual(0.1f, d.attenuation_voltage().value(), L"Attenuation of voltage", LINE_INFO());
                Assert::AreEqual(0.2f, d.attenuation_current().value(), L"Attenuation of current", LINE_INFO());
                Assert::AreEqual(int(oscilloscope_waveform_points::maximum_visible), int(d.waveform_points()), L"Waveform points", LINE_INFO());


                rtx_sensor_definition dd(d);
                Assert::AreEqual(d.description(), dd.description(), L"Description copied", LINE_INFO());
                Assert::AreEqual(d.channel_voltage(), dd.channel_voltage(), L"Channel for voltage copied", LINE_INFO());
                Assert::AreEqual(d.channel_current(), dd.channel_current(), L"Channel for current copied", LINE_INFO());
                Assert::AreEqual(d.attenuation_voltage().value(), dd.attenuation_voltage().value(), L"Attenuation of voltage copied", LINE_INFO());
                Assert::AreEqual(d.attenuation_current().value(), dd.attenuation_current().value(), L"Attenuation of current copied", LINE_INFO());
                Assert::AreEqual(int(d.waveform_points()), int(dd.waveform_points()), L"Waveform points", LINE_INFO());
            }
        }

    };
} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
