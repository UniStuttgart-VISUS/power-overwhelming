// <copyright file="rtx_sensor_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace visus {
namespace power_overwhelming {
namespace test {

    TEST_CLASS(rtx_sensor_test) {

    public:

        TEST_METHOD(test_sensor_definition_ctor) {
            Assert::ExpectException<std::invalid_argument>([](void) {
                rtx_sensor_definition d((wchar_t *) nullptr, oscilloscope_channel(0), oscilloscope_channel(1));
            }, L"Invalid path", LINE_INFO());

            Assert::ExpectException<std::invalid_argument>([](void) {
                rtx_sensor_definition d((wchar_t *) nullptr, 0, 0.1f, 1, 0.2f);
            }, L"Invalid path", LINE_INFO());

            Assert::ExpectException<std::invalid_argument>([](void) {
                rtx_sensor_definition d((char *) nullptr, oscilloscope_channel(0), oscilloscope_channel(1));
            }, L"Invalid path", LINE_INFO());

            Assert::ExpectException<std::invalid_argument>([](void) {
                rtx_sensor_definition d((char *) nullptr, 0, 0.1f, 1, 0.2f);
            }, L"Invalid path", LINE_INFO());

            Assert::ExpectException<std::invalid_argument>([](void) {
                rtx_sensor_definition d(L"bla", oscilloscope_channel(0), oscilloscope_channel(0));
            }, L"Invalid channels", LINE_INFO());

            Assert::ExpectException<std::invalid_argument>([](void) {
                rtx_sensor_definition d(L"bla", 0, 0.1f, 0, 0.2f);
            }, L"Invalid channels", LINE_INFO());

            {
                rtx_sensor_definition d(L"bla",
                    oscilloscope_channel(1).attenuation(oscilloscope_quantity(0.1f, "V")),
                    oscilloscope_channel(2).attenuation(oscilloscope_quantity(0.2f, "A")),
                    L"Horst",
                    oscilloscope_waveform_points::visible);
                Assert::AreEqual("bla", d.path(), L"Path is \"bla\"", LINE_INFO());
                Assert::AreEqual(L"Horst", d.description(), L"Description is \"Horst\"", LINE_INFO());
                Assert::AreEqual(std::uint32_t(1), d.channel_voltage(), L"Channel for voltage", LINE_INFO());
                Assert::AreEqual(std::uint32_t(2), d.channel_current(), L"Channel for current", LINE_INFO());
                Assert::AreEqual(0.1f, d.attenuation_voltage().value(), L"Attenuation of voltage", LINE_INFO());
                Assert::AreEqual(0.2f, d.attenuation_current().value(), L"Attenuation of current", LINE_INFO());
                Assert::AreEqual(int(oscilloscope_waveform_points::visible), int(d.waveform_points()), L"Waveform points", LINE_INFO());
            }

            {
                rtx_sensor_definition d("bla",
                    oscilloscope_channel(1).attenuation(oscilloscope_quantity(0.1f, "V")),
                    oscilloscope_channel(2).attenuation(oscilloscope_quantity(0.2f, "A")),
                    L"Horst",
                    oscilloscope_waveform_points::visible);
                Assert::AreEqual("bla", d.path(), L"Path is \"bla\"", LINE_INFO());
                Assert::AreEqual(L"Horst", d.description(), L"Description is \"Horst\"", LINE_INFO());
                Assert::AreEqual(std::uint32_t(1), d.channel_voltage(), L"Channel for voltage", LINE_INFO());
                Assert::AreEqual(std::uint32_t(2), d.channel_current(), L"Channel for current", LINE_INFO());
                Assert::AreEqual(0.1f, d.attenuation_voltage().value(), L"Attenuation of voltage", LINE_INFO());
                Assert::AreEqual(0.2f, d.attenuation_current().value(), L"Attenuation of current", LINE_INFO());
                Assert::AreEqual(int(oscilloscope_waveform_points::visible), int(d.waveform_points()), L"Waveform points", LINE_INFO());
            }

            {
                rtx_sensor_definition d(L"bla", 1, 0.1f, 2, 0.2f, L"Horst", oscilloscope_waveform_points::visible);
                Assert::AreEqual("bla", d.path(), L"Path is \"bla\"", LINE_INFO());
                Assert::AreEqual(L"Horst", d.description(), L"Description is \"Horst\"", LINE_INFO());
                Assert::AreEqual(std::uint32_t(1), d.channel_voltage(), L"Channel for voltage", LINE_INFO());
                Assert::AreEqual(std::uint32_t(2), d.channel_current(), L"Channel for current", LINE_INFO());
                Assert::AreEqual(0.1f, d.attenuation_voltage().value(), L"Attenuation of voltage", LINE_INFO());
                Assert::AreEqual(0.2f, d.attenuation_current().value(), L"Attenuation of current", LINE_INFO());
                Assert::AreEqual(int(oscilloscope_waveform_points::visible), int(d.waveform_points()), L"Waveform points", LINE_INFO());
            }

            {
                rtx_sensor_definition d("bla", 1, 0.1f, 2, 0.2f, L"Horst", oscilloscope_waveform_points::visible);
                Assert::AreEqual("bla", d.path(), L"Path is \"bla\"", LINE_INFO());
                Assert::AreEqual(L"Horst", d.description(), L"Description is \"Horst\"", LINE_INFO());
                Assert::AreEqual(std::uint32_t(1), d.channel_voltage(), L"Channel for voltage", LINE_INFO());
                Assert::AreEqual(std::uint32_t(2), d.channel_current(), L"Channel for current", LINE_INFO());
                Assert::AreEqual(0.1f, d.attenuation_voltage().value(), L"Attenuation of voltage", LINE_INFO());
                Assert::AreEqual(0.2f, d.attenuation_current().value(), L"Attenuation of current", LINE_INFO());
                Assert::AreEqual(int(oscilloscope_waveform_points::visible), int(d.waveform_points()), L"Waveform points", LINE_INFO());
            }
        }

        TEST_METHOD(test_sensor_definition_copy) {
            {
                rtx_sensor_definition d(L"bla",
                    oscilloscope_channel(1).attenuation(oscilloscope_quantity(0.1f, "V")),
                    oscilloscope_channel(2).attenuation(oscilloscope_quantity(0.2f, "A")),
                    L"Horst");
                Assert::AreEqual("bla", d.path(), L"Path is \"bla\"", LINE_INFO());
                Assert::AreEqual(L"Horst", d.description(), L"Description is \"Horst\"", LINE_INFO());
                Assert::AreEqual(std::uint32_t(1), d.channel_voltage(), L"Channel for voltage", LINE_INFO());
                Assert::AreEqual(std::uint32_t(2), d.channel_current(), L"Channel for current", LINE_INFO());
                Assert::AreEqual(0.1f, d.attenuation_voltage().value(), L"Attenuation of voltage", LINE_INFO());
                Assert::AreEqual(0.2f, d.attenuation_current().value(), L"Attenuation of current", LINE_INFO());
                Assert::AreEqual(int(oscilloscope_waveform_points::maximum), int(d.waveform_points()), L"Waveform points", LINE_INFO());

                rtx_sensor_definition dd(L"foo",
                    oscilloscope_channel(3),
                    oscilloscope_channel(4),
                    L"Hugo",
                    oscilloscope_waveform_points::visible);
                Assert::AreEqual("foo", dd.path(), L"Path is \"foo\"", LINE_INFO());
                Assert::AreEqual(L"Hugo", dd.description(), L"Description is \"Hugo\"", LINE_INFO());
                Assert::AreEqual(std::uint32_t(3), dd.channel_voltage(), L"Channel for voltage", LINE_INFO());
                Assert::AreEqual(std::uint32_t(4), dd.channel_current(), L"Channel for current", LINE_INFO());
                Assert::AreEqual(0.0f, dd.attenuation_voltage().value(), L"Attenuation of voltage", LINE_INFO());
                Assert::AreEqual(0.0f, dd.attenuation_current().value(), L"Attenuation of current", LINE_INFO());
                Assert::AreEqual(int(oscilloscope_waveform_points::visible), int(dd.waveform_points()), L"Waveform points", LINE_INFO());

                dd = d;
                Assert::AreEqual(d.path(), dd.path(), L"Path copied", LINE_INFO());
                Assert::AreEqual(d.description(), dd.description(), L"Description copied", LINE_INFO());
                Assert::AreEqual(d.channel_voltage(), dd.channel_voltage(), L"Channel for voltage copied", LINE_INFO());
                Assert::AreEqual(d.channel_current(), dd.channel_current(), L"Channel for current copied", LINE_INFO());
                Assert::AreEqual(d.attenuation_voltage().value(), dd.attenuation_voltage().value(), L"Attenuation of voltage copied", LINE_INFO());
                Assert::AreEqual(d.attenuation_current().value(), dd.attenuation_current().value(), L"Attenuation of current copied", LINE_INFO());
                Assert::AreEqual(int(d.waveform_points()), int(dd.waveform_points()), L"Waveform points", LINE_INFO());
            }

            {
                rtx_sensor_definition d(L"bla",
                    oscilloscope_channel(1).attenuation(oscilloscope_quantity(0.1f, "V")),
                    oscilloscope_channel(2).attenuation(oscilloscope_quantity(0.2f, "A")),
                    L"Horst",
                    oscilloscope_waveform_points::maximum_visible);
                Assert::AreEqual("bla", d.path(), L"Path is \"bla\"", LINE_INFO());
                Assert::AreEqual(L"Horst", d.description(), L"Description is \"Horst\"", LINE_INFO());
                Assert::AreEqual(std::uint32_t(1), d.channel_voltage(), L"Channel for voltage", LINE_INFO());
                Assert::AreEqual(std::uint32_t(2), d.channel_current(), L"Channel for current", LINE_INFO());
                Assert::AreEqual(0.1f, d.attenuation_voltage().value(), L"Attenuation of voltage", LINE_INFO());
                Assert::AreEqual(0.2f, d.attenuation_current().value(), L"Attenuation of current", LINE_INFO());
                Assert::AreEqual(int(oscilloscope_waveform_points::maximum_visible), int(d.waveform_points()), L"Waveform points", LINE_INFO());


                rtx_sensor_definition dd(d);
                Assert::AreEqual(d.path(), dd.path(), L"Path copied", LINE_INFO());
                Assert::AreEqual(d.description(), dd.description(), L"Description copied", LINE_INFO());
                Assert::AreEqual(d.channel_voltage(), dd.channel_voltage(), L"Channel for voltage copied", LINE_INFO());
                Assert::AreEqual(d.channel_current(), dd.channel_current(), L"Channel for current copied", LINE_INFO());
                Assert::AreEqual(d.attenuation_voltage().value(), dd.attenuation_voltage().value(), L"Attenuation of voltage copied", LINE_INFO());
                Assert::AreEqual(d.attenuation_current().value(), dd.attenuation_current().value(), L"Attenuation of current copied", LINE_INFO());
                Assert::AreEqual(int(d.waveform_points()), int(dd.waveform_points()), L"Waveform points", LINE_INFO());
            }
        }

        TEST_METHOD(test_instrument_configuration) {
            const auto trigger = oscilloscope_edge_trigger("CH1").level(1, 2.0f);
            const oscilloscope_quantity time_range(10, "s");
            const auto acquisition = oscilloscope_single_acquisition().count(16).points(10000);

            {
                const rtx_instrument_configuration c(time_range);
                Assert::IsTrue(c.acquisition().automatic_points(), L"Default acquisition.automatic_poits", LINE_INFO());
                Assert::AreEqual(std::size_t(0), c.beep_on_apply(), L"Default beep_on_apply", LINE_INFO());
                Assert::IsFalse(c.beep_on_error(), L"Default beep_on_error", LINE_INFO());
                Assert::IsFalse(c.beep_on_trigger(), L"Default beep_on_trigger", LINE_INFO());
                Assert::AreEqual(int(1), int(c.acquisition().count()), L"Default acquisition.count", LINE_INFO());
                Assert::IsTrue(c.acquisition().segmented(), L"Default acquisition.segmented", LINE_INFO());
                Assert::IsFalse(c.slave(), L"Default slave", LINE_INFO());
                Assert::AreEqual(int(0), int(c.timeout()), L"Default timeout", LINE_INFO());
                Assert::AreEqual(time_range.value(), c.time_range().value(), L"Default time_range.value", LINE_INFO());
                Assert::AreEqual(time_range.unit(), c.time_range().unit(), L"Default time_range.unit", LINE_INFO());
                Assert::AreEqual(int(5), int(c.trigger().input()), L"Default trigger.input", LINE_INFO());
            }

            {
                const auto c = rtx_instrument_configuration(time_range, acquisition, trigger, 2000).beep_on_apply(42).beep_on_error(true).beep_on_trigger(true);
                Assert::AreEqual(std::size_t(42), c.beep_on_apply(), L"Explicit beep_on_apply", LINE_INFO());
                Assert::IsTrue(c.beep_on_error(), L"Explicit beep_on_error", LINE_INFO());
                Assert::IsTrue(c.beep_on_trigger(), L"Explicit beep_on_trigger", LINE_INFO());
                Assert::IsFalse(c.acquisition().automatic_points(), L"Explicit acquisition.automatic_poits", LINE_INFO());
                Assert::AreEqual(int(16), int(c.acquisition().count()), L"Explicit acquisition.count", LINE_INFO());
                Assert::IsFalse(c.acquisition().segmented(), L"Explicit acquisition.segmented", LINE_INFO());
                Assert::IsFalse(c.slave(), L"Explicit slave", LINE_INFO());
                Assert::AreEqual(int(2000), int(c.timeout()), L"Explicit timeout", LINE_INFO());
                Assert::AreEqual(time_range.value(), c.time_range().value(), L"Explicit time_range.value", LINE_INFO());
                Assert::AreEqual(time_range.unit(), c.time_range().unit(), L"Explicit time_range.unit", LINE_INFO());
                Assert::AreEqual(int(1), int(c.trigger().input()), L"Explicit trigger.input", LINE_INFO());
            }

            {
                const auto c = rtx_instrument_configuration(time_range, acquisition, trigger, 2000).as_slave();
                Assert::IsFalse(c.acquisition().automatic_points(), L"as_slave acquisition.automatic_poits", LINE_INFO());
                Assert::AreEqual(int(16), int(c.acquisition().count()), L"as_slave acquisition.count", LINE_INFO());
                Assert::IsFalse(c.acquisition().segmented(), L"as_slave acquisition.segmented", LINE_INFO());
                Assert::IsTrue(c.slave(), L"as_slave slave", LINE_INFO());
                Assert::AreEqual(int(2000), int(c.timeout()), L"as_slave timeout", LINE_INFO());
                Assert::AreEqual(time_range.value(), c.time_range().value(), L"as_slave time_range.value", LINE_INFO());
                Assert::AreEqual(time_range.unit(), c.time_range().unit(), L"as_slave time_range.unit", LINE_INFO());
                Assert::AreEqual(int(5), int(c.trigger().input()), L"as_slave trigger.input", LINE_INFO());
            }

        }

    };
} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
