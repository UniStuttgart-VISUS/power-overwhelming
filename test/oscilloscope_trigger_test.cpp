// <copyright file="rtx_trigger_test.cpp" company="Visualisierungsinstitut der Universit�t Stuttgart">
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

    TEST_CLASS(rtx_trigger_test) {

    public:

        TEST_METHOD(test_edge_trigger_ctor) {
            const auto trigger = rtx_trigger::edge("CH1");

            Assert::AreEqual(int(rtx_trigger_coupling::direct_current), int(trigger.coupling()), L"Default coupling", LINE_INFO());
            Assert::IsNull(trigger.hold_off(), L"Default hold_off", LINE_INFO());
            Assert::AreEqual(int(rtx_trigger_hysteresis::automatic), int(trigger.hysteresis()), L"Default hysteresis", LINE_INFO());
            Assert::AreEqual(1, int(trigger.input()), L"Default input", LINE_INFO());
            Assert::AreEqual("", trigger.level().unit(), L"Default level unit", LINE_INFO());
            Assert::AreEqual(0.0f, trigger.level().value(), L"Default level value", LINE_INFO());
            Assert::AreEqual(int(rtx_trigger_mode::automatic), int(trigger.mode()), L"Default mode", LINE_INFO());
            Assert::AreEqual(int(rtx_trigger_slope::rising), int(trigger.slope()), L"Default slope", LINE_INFO());
            Assert::AreEqual("CH1", trigger.source(), L"Default source", LINE_INFO());
            Assert::AreEqual("EDGE", trigger.type(), L"Default type", LINE_INFO());
        }

        TEST_METHOD(test_edge_trigger_fluid_api) {
            auto trigger = rtx_trigger::edge("CH1");
            trigger.coupling(rtx_trigger_coupling::alternating_current)
                .hysteresis(rtx_trigger_hysteresis::high)
                .level(2, rtx_quantity(42, "lvl"))
                .slope(rtx_trigger_slope::falling)
                .coupling(rtx_trigger_coupling::alternating_current)
                .hold_off("holdoff")
                .mode(rtx_trigger_mode::automatic)
                .source("CH2");

            Assert::AreEqual(int(rtx_trigger_coupling::alternating_current), int(trigger.coupling()), L"Set coupling", LINE_INFO());
            Assert::AreEqual("holdoff", trigger.hold_off(), L"Set hold_off", LINE_INFO());
            Assert::AreEqual(int(rtx_trigger_hysteresis::high), int(trigger.hysteresis()), L"Set hysteresis", LINE_INFO());
            Assert::AreEqual(2, int(trigger.input()), L"Set input", LINE_INFO());
            Assert::AreEqual("lvl", trigger.level().unit(), L"Set level unit", LINE_INFO());
            Assert::AreEqual(42.0f, trigger.level().value(), L"Set level value", LINE_INFO());
            Assert::AreEqual(int(rtx_trigger_mode::automatic), int(trigger.mode()), L"Set mode", LINE_INFO());
            Assert::AreEqual(int(rtx_trigger_slope::falling), int(trigger.slope()), L"Set slope", LINE_INFO());
            Assert::AreEqual("CH2", trigger.source(), L"Set source", LINE_INFO());
            Assert::AreEqual("EDGE", trigger.type(), L"Set type", LINE_INFO());
        }

        TEST_METHOD(test_edge_trigger_copy_ctor) {
            auto expected = rtx_trigger::edge("CH1");
            expected.coupling(rtx_trigger_coupling::alternating_current)
                .hysteresis(rtx_trigger_hysteresis::high)
                .level(2, rtx_quantity(42, "lvl"))
                .slope(rtx_trigger_slope::falling)
                .coupling(rtx_trigger_coupling::alternating_current)
                .hold_off("holdoff")
                .mode(rtx_trigger_mode::automatic)
                .source("CH2");

            rtx_trigger trigger(expected);

            Assert::AreEqual(int(expected.coupling()), int(trigger.coupling()), L"Copy coupling", LINE_INFO());
            Assert::AreEqual(expected.hold_off(), trigger.hold_off(), L"Copy hold_off", LINE_INFO());
            Assert::AreEqual(int(expected.hysteresis()), int(trigger.hysteresis()), L"Copy hysteresis", LINE_INFO());
            Assert::AreEqual(int(expected.input()), int(trigger.input()), L"Copy input", LINE_INFO());
            Assert::AreEqual(expected.level().unit(), trigger.level().unit(), L"Copy level unit", LINE_INFO());
            Assert::AreEqual(expected.level().value(), trigger.level().value(), L"Copy level value", LINE_INFO());
            Assert::AreEqual(int(expected.mode()), int(trigger.mode()), L"Copy mode", LINE_INFO());
            Assert::AreEqual(int(expected.slope()), int(trigger.slope()), L"Copy slope", LINE_INFO());
            Assert::AreEqual(expected.source(), trigger.source(), L"Copy source", LINE_INFO());
            Assert::AreEqual(expected.type(), trigger.type(), L"Copy type", LINE_INFO());
        }

        TEST_METHOD(test_edge_trigger_assignment) {
            auto expected = rtx_trigger::edge("CH1");
            expected.coupling(rtx_trigger_coupling::alternating_current)
                .hysteresis(rtx_trigger_hysteresis::high)
                .level(2, rtx_quantity(42, "lvl"))
                .slope(rtx_trigger_slope::falling)
                .coupling(rtx_trigger_coupling::alternating_current)
                .hold_off("holdoff")
                .mode(rtx_trigger_mode::automatic)
                .source("CH2");

            rtx_trigger trigger("CH2", "HORST");
            trigger = expected;

            Assert::AreEqual(int(expected.coupling()), int(trigger.coupling()), L"Copy coupling", LINE_INFO());
            Assert::AreEqual(expected.hold_off(), trigger.hold_off(), L"Copy hold_off", LINE_INFO());
            Assert::AreEqual(int(expected.hysteresis()), int(trigger.hysteresis()), L"Copy hysteresis", LINE_INFO());
            Assert::AreEqual(int(expected.input()), int(trigger.input()), L"Copy input", LINE_INFO());
            Assert::AreEqual(expected.level().unit(), trigger.level().unit(), L"Copy level unit", LINE_INFO());
            Assert::AreEqual(expected.level().value(), trigger.level().value(), L"Copy level value", LINE_INFO());
            Assert::AreEqual(int(expected.mode()), int(trigger.mode()), L"Copy mode", LINE_INFO());
            Assert::AreEqual(int(expected.slope()), int(trigger.slope()), L"Copy slope", LINE_INFO());
            Assert::AreEqual(expected.source(), trigger.source(), L"Copy source", LINE_INFO());
            Assert::AreEqual(expected.type(), trigger.type(), L"Copy type", LINE_INFO());
        }

        TEST_METHOD(test_parse_coupling) {
            Assert::AreEqual(int(rtx_trigger_coupling::alternating_current), int(parse_rtx_trigger_coupling(L"alternating_current")), L"alternating_current", LINE_INFO());
            Assert::AreEqual(int(rtx_trigger_coupling::direct_current), int(parse_rtx_trigger_coupling(L"direct_current")), L"direct_current", LINE_INFO());
            Assert::AreEqual(int(rtx_trigger_coupling::low_frequency_reject), int(parse_rtx_trigger_coupling(L"low_frequency_reject")), L"low_frequency_reject", LINE_INFO());
            Assert::ExpectException<std::invalid_argument>([](void) {
                auto dummy = parse_rtx_channel_polarity(L"nullptr");
            }, L"nullptr", LINE_INFO());
            Assert::ExpectException<std::invalid_argument>([](void) {
                auto dummy = parse_rtx_channel_polarity(L"horst");
            }, L"invalid value", LINE_INFO());
        }

        TEST_METHOD(test_coupling_to_string) {
            Assert::AreEqual(L"alternating_current", to_string(rtx_trigger_coupling::alternating_current), L"alternating_current", LINE_INFO());
            Assert::AreEqual(L"direct_current", to_string(rtx_trigger_coupling::direct_current), L"direct_current", LINE_INFO());
            Assert::AreEqual(L"low_frequency_reject", to_string(rtx_trigger_coupling::low_frequency_reject), L"low_frequency_reject", LINE_INFO());
            Assert::ExpectException<std::invalid_argument>([](void) {
                auto dummy = to_string(static_cast<rtx_trigger_coupling>(-1));
            }, L"invalid value", LINE_INFO());
        }
    };

} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
