// <copyright file="rtx_channel_test.cpp" company="Visualisierungsinstitut der Universit�t Stuttgart">
// Copyright � 2023 Visualisierungsinstitut der Universit�t Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph M�ller</author>

#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace visus {
namespace power_overwhelming {
namespace test {

    TEST_CLASS(rtx_channel_test) {

    public:

        TEST_METHOD(test_default_ctor) {
            rtx_channel channel(2);

            Assert::AreEqual(int(rtx_channel_bandwidth::full), int(channel.bandwidth()), L"Default bandwith", LINE_INFO());
            Assert::AreEqual("", channel.attenuation().unit(), L"Default attenuation unit", LINE_INFO());
            Assert::AreEqual(0.0f, channel.attenuation().value(), L"Default attenuation value", LINE_INFO());
            Assert::AreEqual(2, int(channel.channel()), L"channel", LINE_INFO());
            Assert::AreEqual(int(rtx_channel_coupling::direct_current_limit), int(channel.coupling()), L"Default coupling", LINE_INFO());
            Assert::AreEqual("", channel.label().text(), L"Default label text", LINE_INFO());
            Assert::IsFalse(channel.label().visible(), L"Default label state", LINE_INFO());
            Assert::AreEqual("", channel.offset().unit(), L"Default offset unit", LINE_INFO());
            Assert::AreEqual(0.0f, channel.offset().value(), L"Default offset value", LINE_INFO());
            Assert::AreEqual(int(rtx_channel_polarity::normal), int(channel.polarity()), L"Default polarity", LINE_INFO());
            Assert::AreEqual("", channel.range().unit(), L"Default range unit", LINE_INFO());
            Assert::AreEqual(0.0f, channel.range().value(), L"Default range value", LINE_INFO());
            Assert::AreEqual("", channel.skew().unit(), L"Default skew unit", LINE_INFO());
            Assert::AreEqual(0.0f, channel.skew().value(), L"Default skew value", LINE_INFO());
            Assert::IsFalse(channel.state(), L"Default state", LINE_INFO());
            Assert::AreEqual("", channel.zero_offset().unit(), L"Default zero unit", LINE_INFO());
            Assert::AreEqual(0.0f, channel.zero_offset().value(), L"Default zero value", LINE_INFO());
        }

        TEST_METHOD(test_fluid_api) {
            rtx_channel channel(4);
            channel.attenuation(rtx_quantity(1.0f, "A"))
                .bandwidth(rtx_channel_bandwidth::limit_to_20_mhz)
                .coupling(rtx_channel_coupling::alternating_current_limit)
                .label(rtx_label("bla", true))
                .offset(rtx_quantity(42, "of"))
                .polarity(rtx_channel_polarity::inverted)
                .range(rtx_quantity(42.1f, "ra"))
                .skew(rtx_quantity(42.2f, "sk"))
                .state(true)
                .zero_offset(rtx_quantity(42.3f, "zu"));

            Assert::AreEqual("A", channel.attenuation().unit(), L"attenuation unit", LINE_INFO());
            Assert::AreEqual(1.0f, channel.attenuation().value(), L"attenuation value", LINE_INFO());
            Assert::AreEqual(int(rtx_channel_bandwidth::limit_to_20_mhz), int(channel.bandwidth()), L"bandwith", LINE_INFO());
            Assert::AreEqual(4, int(channel.channel()), L"channel", LINE_INFO());
            Assert::AreEqual(int(rtx_channel_coupling::alternating_current_limit), int(channel.coupling()), L"coupling", LINE_INFO());
            Assert::AreEqual("bla", channel.label().text(), L"label text", LINE_INFO());
            Assert::IsTrue(channel.label().visible(), L"label state", LINE_INFO());
            Assert::AreEqual("of", channel.offset().unit(), L"offset unit", LINE_INFO());
            Assert::AreEqual(42.0f, channel.offset().value(), L"offset value", LINE_INFO());
            Assert::AreEqual(int(rtx_channel_polarity::inverted), int(channel.polarity()), L"polarity", LINE_INFO());
            Assert::AreEqual("ra", channel.range().unit(), L"range unit", LINE_INFO());
            Assert::AreEqual(42.1f, channel.range().value(), L"range value", LINE_INFO());
            Assert::AreEqual("sk", channel.skew().unit(), L"skew unit", LINE_INFO());
            Assert::AreEqual(42.2f, channel.skew().value(), L"skew value", LINE_INFO());
            Assert::IsTrue(channel.state(), L"state", LINE_INFO());
            Assert::AreEqual("zu", channel.zero_offset().unit(), L"zero unit", LINE_INFO());
            Assert::AreEqual(42.3f, channel.zero_offset().value(), L"zero value", LINE_INFO());
        }

        TEST_METHOD(test_illegal_attenuation) {
            rtx_channel channel(42);

            Assert::ExpectException<std::invalid_argument>([&channel](void) {
                channel.attenuation(12.0f);
            });

            Assert::ExpectException<std::invalid_argument>([&channel](void) {
                channel.attenuation(rtx_quantity(12.0f));
            });
        }

        TEST_METHOD(test_parse_bandwidth) {
            Assert::AreEqual(int(rtx_channel_bandwidth::full), int(parse_rtx_channel_bandwidth(L"full")), L"full", LINE_INFO());
            Assert::AreEqual(int(rtx_channel_bandwidth::limit_to_20_mhz), int(parse_rtx_channel_bandwidth(L"limit_to_20_mhz")), L"limit_to_20_mhz", LINE_INFO());
            Assert::ExpectException<std::invalid_argument>([](void) {
                auto dummy = parse_rtx_channel_bandwidth(L"nullptr");
            }, L"nullptr", LINE_INFO());
            Assert::ExpectException<std::invalid_argument>([](void) {
                auto dummy = parse_rtx_channel_bandwidth(L"horst");
            }, L"invalid value", LINE_INFO());
        }

        TEST_METHOD(test_bandwidth_to_string) {
            Assert::AreEqual(L"full", to_string(rtx_channel_bandwidth::full), L"full", LINE_INFO());
            Assert::AreEqual(L"limit_to_20_mhz", to_string(rtx_channel_bandwidth::limit_to_20_mhz), L"limit_to_20_mhz", LINE_INFO());
            Assert::ExpectException<std::invalid_argument>([](void) {
                auto dummy = to_string(static_cast<rtx_channel_bandwidth>(-1));
            }, L"invalid value", LINE_INFO());
        }

        TEST_METHOD(test_parse_coupling) {
            Assert::AreEqual(int(rtx_channel_coupling::alternating_current_limit), int(parse_rtx_channel_coupling(L"alternating_current_limit")), L"alternating_current_limit", LINE_INFO());
            Assert::AreEqual(int(rtx_channel_coupling::direct_current_limit), int(parse_rtx_channel_coupling(L"direct_current_limit")), L"direct_current_limit", LINE_INFO());
            Assert::AreEqual(int(rtx_channel_coupling::ground), int(parse_rtx_channel_coupling(L"ground")), L"ground", LINE_INFO());
            Assert::ExpectException<std::invalid_argument>([](void) {
                auto dummy = parse_rtx_channel_bandwidth(L"nullptr");
            }, L"nullptr", LINE_INFO());
            Assert::ExpectException<std::invalid_argument>([](void) {
                auto dummy = parse_rtx_channel_bandwidth(L"horst");
            }, L"invalid value", LINE_INFO());
        }

        TEST_METHOD(test_coupling_to_string) {
            Assert::AreEqual(L"alternating_current_limit", to_string(rtx_channel_coupling::alternating_current_limit), L"alternating_current_limit", LINE_INFO());
            Assert::AreEqual(L"direct_current_limit", to_string(rtx_channel_coupling::direct_current_limit), L"direct_current_limit", LINE_INFO());
            Assert::AreEqual(L"ground", to_string(rtx_channel_coupling::ground), L"ground", LINE_INFO());
            Assert::ExpectException<std::invalid_argument>([](void) {
                auto dummy = to_string(static_cast<rtx_channel_bandwidth>(-1));
            }, L"invalid value", LINE_INFO());
        }

        TEST_METHOD(test_parse_polarity) {
            Assert::AreEqual(int(rtx_channel_polarity::normal), int(parse_rtx_channel_polarity(L"normal")), L"normal", LINE_INFO());
            Assert::AreEqual(int(rtx_channel_polarity::inverted), int(parse_rtx_channel_polarity(L"inverted")), L"inverted", LINE_INFO());
            Assert::ExpectException<std::invalid_argument>([](void) {
                auto dummy = parse_rtx_channel_polarity(L"nullptr");
            }, L"nullptr", LINE_INFO());
            Assert::ExpectException<std::invalid_argument>([](void) {
                auto dummy = parse_rtx_channel_polarity(L"horst");
            }, L"invalid value", LINE_INFO());
        }

        TEST_METHOD(test_polarity_to_string) {
            Assert::AreEqual(L"normal", to_string(rtx_channel_polarity::normal), L"normal", LINE_INFO());
            Assert::AreEqual(L"inverted", to_string(rtx_channel_polarity::inverted), L"inverted", LINE_INFO());
            Assert::ExpectException<std::invalid_argument>([](void) {
                auto dummy = to_string(static_cast<rtx_channel_polarity>(-1));
            }, L"invalid value", LINE_INFO());
        }
    };

} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
