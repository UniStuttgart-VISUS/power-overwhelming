// <copyright file="oscilloscope_trigger_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace visus {
namespace power_overwhelming {
namespace test {

    TEST_CLASS(oscilloscope_trigger_test) {

    public:

        TEST_METHOD(test_edge_trigger_ctor) {
            oscilloscope_edge_trigger trigger("CH1");

            Assert::AreEqual(int(oscilloscope_trigger_coupling::direct_current), int(trigger.coupling()), L"Default coupling", LINE_INFO());
            Assert::IsNull(trigger.hold_off(), L"Default hold_off", LINE_INFO());
            Assert::AreEqual(int(oscilloscope_trigger_hysteresis::automatic), int(trigger.hysteresis()), L"Default hysteresis", LINE_INFO());
            Assert::AreEqual(0, int(trigger.input()), L"Default input", LINE_INFO());
            Assert::AreEqual("", trigger.level().unit(), L"Default level unit", LINE_INFO());
            Assert::AreEqual(0.0f, trigger.level().value(), L"Default level value", LINE_INFO());
            Assert::AreEqual(int(oscilloscope_trigger_mode::normal), int(trigger.mode()), L"Default mode", LINE_INFO());
            Assert::AreEqual(int(oscilloscope_trigger_slope::rising), int(trigger.slope()), L"Default slope", LINE_INFO());
            Assert::AreEqual("CH1", trigger.source(), L"Default source", LINE_INFO());
            Assert::AreEqual("EDGE", trigger.type(), L"Default type", LINE_INFO());
        }

        TEST_METHOD(test_edge_trigger_fluid_api) {
            oscilloscope_edge_trigger trigger("CH1");
            trigger.coupling(oscilloscope_trigger_coupling::alternating_current)
                .hysteresis(oscilloscope_trigger_hysteresis::high)
                .level(2, oscilloscope_quantity(42, "lvl"))
                .slope(oscilloscope_trigger_slope::falling)
                .coupling(oscilloscope_trigger_coupling::alternating_current)
                .hold_off("holdoff")
                .mode(oscilloscope_trigger_mode::automatic)
                .source("CH2");

            Assert::AreEqual(int(oscilloscope_trigger_coupling::alternating_current), int(trigger.coupling()), L"Set coupling", LINE_INFO());
            Assert::AreEqual("holdoff", trigger.hold_off(), L"Set hold_off", LINE_INFO());
            Assert::AreEqual(int(oscilloscope_trigger_hysteresis::high), int(trigger.hysteresis()), L"Set hysteresis", LINE_INFO());
            Assert::AreEqual(2, int(trigger.input()), L"Set input", LINE_INFO());
            Assert::AreEqual("lvl", trigger.level().unit(), L"Set level unit", LINE_INFO());
            Assert::AreEqual(42.0f, trigger.level().value(), L"Set level value", LINE_INFO());
            Assert::AreEqual(int(oscilloscope_trigger_mode::automatic), int(trigger.mode()), L"Set mode", LINE_INFO());
            Assert::AreEqual(int(oscilloscope_trigger_slope::falling), int(trigger.slope()), L"Set slope", LINE_INFO());
            Assert::AreEqual("CH2", trigger.source(), L"Set source", LINE_INFO());
            Assert::AreEqual("EDGE", trigger.type(), L"Set type", LINE_INFO());
        }
    };

} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
