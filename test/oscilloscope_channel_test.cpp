// <copyright file="oscilloscope_channel_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace visus {
namespace power_overwhelming {
namespace test {

    TEST_CLASS(oscilloscope_channel_test) {

    public:

        TEST_METHOD(test_default_ctor) {
            oscilloscope_channel channel(2);

            Assert::AreEqual(int(oscilloscope_channel_bandwidth::full), int(channel.bandwidth()), L"Default bandwith", LINE_INFO());
            Assert::AreEqual(2, int(channel.channel()), L"channel", LINE_INFO());
            Assert::AreEqual(int(oscilloscope_channel_coupling::direct_current_limit), int(channel.coupling()), L"Default coupling", LINE_INFO());
            Assert::AreEqual("V", channel.gain().unit(), L"Default gain unit", LINE_INFO());
            Assert::AreEqual(10.0f, channel.gain().value(), L"Default gain value", LINE_INFO());
            Assert::AreEqual("", channel.label().text(), L"Default label text", LINE_INFO());
            Assert::IsFalse(channel.label().visible(), L"Default label state", LINE_INFO());
            Assert::AreEqual("", channel.offset().unit(), L"Default offset unit", LINE_INFO());
            Assert::AreEqual(0.0f, channel.offset().value(), L"Default offset value", LINE_INFO());
            Assert::AreEqual(int(oscilloscope_channel_polarity::normal), int(channel.polarity()), L"Default polarity", LINE_INFO());
            Assert::AreEqual("", channel.range().unit(), L"Default range unit", LINE_INFO());
            Assert::AreEqual(0.0f, channel.range().value(), L"Default range value", LINE_INFO());
            Assert::AreEqual("", channel.skew().unit(), L"Default skew unit", LINE_INFO());
            Assert::AreEqual(0.0f, channel.skew().value(), L"Default skew value", LINE_INFO());
            Assert::IsFalse(channel.state(), L"Default state", LINE_INFO());
            Assert::AreEqual("", channel.zero_offset().unit(), L"Default zero unit", LINE_INFO());
            Assert::AreEqual(0.0f, channel.zero_offset().value(), L"Default zero value", LINE_INFO());
        }

        TEST_METHOD(test_fuild_api) {
            oscilloscope_channel channel(4);
            channel.bandwidth(oscilloscope_channel_bandwidth::limit_to_20_mhz)
                .coupling(oscilloscope_channel_coupling::alternating_current_limit)
                .gain(oscilloscope_quantity(1.0f, "A"))
                .label(oscilloscope_label("bla", true))
                .offset(oscilloscope_quantity(42, "of"))
                .polarity(oscilloscope_channel_polarity::inverted)
                .range(oscilloscope_quantity(42.1f, "ra"))
                .skew(oscilloscope_quantity(42.2f, "sk"))
                .state(true)
                .zero_offset(oscilloscope_quantity(42.3f, "zu"));

            Assert::AreEqual(int(oscilloscope_channel_bandwidth::limit_to_20_mhz), int(channel.bandwidth()), L"bandwith", LINE_INFO());
            Assert::AreEqual(4, int(channel.channel()), L"channel", LINE_INFO());
            Assert::AreEqual(int(oscilloscope_channel_coupling::alternating_current_limit), int(channel.coupling()), L"coupling", LINE_INFO());
            Assert::AreEqual("A", channel.gain().unit(), L"gain unit", LINE_INFO());
            Assert::AreEqual(1.0f, channel.gain().value(), L"gain value", LINE_INFO());
            Assert::AreEqual("bla", channel.label().text(), L"label text", LINE_INFO());
            Assert::IsTrue(channel.label().visible(), L"label state", LINE_INFO());
            Assert::AreEqual("of", channel.offset().unit(), L"offset unit", LINE_INFO());
            Assert::AreEqual(42.0f, channel.offset().value(), L"offset value", LINE_INFO());
            Assert::AreEqual(int(oscilloscope_channel_polarity::inverted), int(channel.polarity()), L"polarity", LINE_INFO());
            Assert::AreEqual("ra", channel.range().unit(), L"range unit", LINE_INFO());
            Assert::AreEqual(42.1f, channel.range().value(), L"range value", LINE_INFO());
            Assert::AreEqual("sk", channel.skew().unit(), L"skew unit", LINE_INFO());
            Assert::AreEqual(42.2f, channel.skew().value(), L"skew value", LINE_INFO());
            Assert::IsTrue(channel.state(), L"state", LINE_INFO());
            Assert::AreEqual("zu", channel.zero_offset().unit(), L"zero unit", LINE_INFO());
            Assert::AreEqual(42.3f, channel.zero_offset().value(), L"zero value", LINE_INFO());
        }
    };

} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
