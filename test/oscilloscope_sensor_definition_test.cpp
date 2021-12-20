// <copyright file="oscilloscope_sensor_definition_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace visus {
namespace power_overwhelming {
namespace test {

    TEST_CLASS(oscilloscope_sensor_definition_test) {

    public:

        TEST_METHOD(test_ctor) {
            Assert::ExpectException<std::invalid_argument>([](void) {
                oscilloscope_sensor_definition d(nullptr, 0, 0);
            }, L"Invalid description", LINE_INFO());

            Assert::ExpectException<std::invalid_argument>([](void) {
                oscilloscope_sensor_definition d(nullptr, 0, 0.0f, 0, 0.0f);
            }, L"Invalid description", LINE_INFO());

            Assert::ExpectException<std::invalid_argument>([](void) {
                oscilloscope_sensor_definition d(L"test", 0, 0);
            }, L"Invalid channels", LINE_INFO());

            Assert::ExpectException<std::invalid_argument>([](void) {
                oscilloscope_sensor_definition d(L"test", 0, 0.0f, 0, 0.0f);
            }, L"Invalid channels", LINE_INFO());

            {
                oscilloscope_sensor_definition d(L"Horst", 1, 0.1f, 2, 0.2f);
                Assert::AreEqual(L"Horst", d.description(), L"Description is \"Horst\"", LINE_INFO());
                Assert::AreEqual(std::uint32_t(1), d.channel_voltage(), L"Channel for voltage", LINE_INFO());
                Assert::AreEqual(std::uint32_t(2), d.channel_current(), L"Channel for current", LINE_INFO());
                Assert::AreEqual(0.1f, d.attenuation_voltage(), L"Attenuation of voltage", LINE_INFO());
                Assert::AreEqual(0.2f, d.attenuation_current(), L"Attenuation of current", LINE_INFO());
                Assert::IsFalse(d.auto_attenuation_voltage(), L"Auto-attenuation of voltage", LINE_INFO());
                Assert::IsFalse(d.auto_attenuation_current(), L"Auto-attenuation of current", LINE_INFO());
            }

            {
                oscilloscope_sensor_definition d(L"Horst", 1, 2);
                Assert::AreEqual(L"Horst", d.description(), L"Description is \"Horst\"", LINE_INFO());
                Assert::AreEqual(std::uint32_t(1), d.channel_voltage(), L"Channel for voltage", LINE_INFO());
                Assert::AreEqual(std::uint32_t(2), d.channel_current(), L"Channel for current", LINE_INFO());
                Assert::AreEqual(0.0f, d.attenuation_voltage(), L"Attenuation of voltage", LINE_INFO());
                Assert::AreEqual(0.0f, d.attenuation_current(), L"Attenuation of current", LINE_INFO());
                Assert::IsTrue(d.auto_attenuation_voltage(), L"Auto-attenuation of voltage", LINE_INFO());
                Assert::IsTrue(d.auto_attenuation_current(), L"Auto-attenuation of current", LINE_INFO());
            }
        }

        TEST_METHOD(test_assignment) {
            {
                oscilloscope_sensor_definition d(L"Horst", 1, 0.1f, 2, 0.2f);
                Assert::AreEqual(L"Horst", d.description(), L"Description is \"Horst\"", LINE_INFO());
                Assert::AreEqual(std::uint32_t(1), d.channel_voltage(), L"Channel for voltage", LINE_INFO());
                Assert::AreEqual(std::uint32_t(2), d.channel_current(), L"Channel for current", LINE_INFO());
                Assert::AreEqual(0.1f, d.attenuation_voltage(), L"Attenuation of voltage", LINE_INFO());
                Assert::AreEqual(0.2f, d.attenuation_current(), L"Attenuation of current", LINE_INFO());

                oscilloscope_sensor_definition dd(L"Hugo", 3, 4);
                Assert::AreEqual(L"Hugo", dd.description(), L"Description is \"Hugo\"", LINE_INFO());
                Assert::AreEqual(std::uint32_t(3), dd.channel_voltage(), L"Channel for voltage", LINE_INFO());
                Assert::AreEqual(std::uint32_t(4), dd.channel_current(), L"Channel for current", LINE_INFO());
                Assert::AreEqual(0.0f, dd.attenuation_voltage(), L"Attenuation of voltage", LINE_INFO());
                Assert::AreEqual(0.0f, dd.attenuation_current(), L"Attenuation of current", LINE_INFO());

                dd = d;
                Assert::AreEqual(d.description(), dd.description(), L"Description copied", LINE_INFO());
                Assert::AreEqual(d.channel_voltage(), dd.channel_voltage(), L"Channel for voltage copied", LINE_INFO());
                Assert::AreEqual(d.channel_current(), dd.channel_current(), L"Channel for current copied", LINE_INFO());
                Assert::AreEqual(d.attenuation_voltage(), dd.attenuation_voltage(), L"Attenuation of voltage copied", LINE_INFO());
                Assert::AreEqual(d.attenuation_current(), dd.attenuation_current(), L"Attenuation of current copied", LINE_INFO());
            }

            {
                oscilloscope_sensor_definition d(L"Horst", 1, 0.1f, 2, 0.2f);
                Assert::AreEqual(L"Horst", d.description(), L"Description is \"Horst\"", LINE_INFO());
                Assert::AreEqual(std::uint32_t(1), d.channel_voltage(), L"Channel for voltage", LINE_INFO());
                Assert::AreEqual(std::uint32_t(2), d.channel_current(), L"Channel for current", LINE_INFO());
                Assert::AreEqual(0.1f, d.attenuation_voltage(), L"Attenuation of voltage", LINE_INFO());
                Assert::AreEqual(0.2f, d.attenuation_current(), L"Attenuation of current", LINE_INFO());

                oscilloscope_sensor_definition dd(d);
                Assert::AreEqual(d.description(), dd.description(), L"Description copied", LINE_INFO());
                Assert::AreEqual(d.channel_voltage(), dd.channel_voltage(), L"Channel for voltage copied", LINE_INFO());
                Assert::AreEqual(d.channel_current(), dd.channel_current(), L"Channel for current copied", LINE_INFO());
                Assert::AreEqual(d.attenuation_voltage(), dd.attenuation_voltage(), L"Attenuation of voltage copied", LINE_INFO());
                Assert::AreEqual(d.attenuation_current(), dd.attenuation_current(), L"Attenuation of current copied", LINE_INFO());
            }
        }

    };
} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
