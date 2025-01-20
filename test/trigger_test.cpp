// <copyright file="trigger_test.cpp" company="Visualisierungsinstitut der Universit�t Stuttgart">
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

    TEST_CLASS(trigger_test) {

    public:

        TEST_METHOD(test_edge) {
            {
                auto t = rtx_trigger::edge("CH1");
                Assert::AreEqual(int(rtx_trigger_coupling::direct_current), int(t.coupling()), L"Default coupling", LINE_INFO());
                Assert::IsNull(t.hold_off(), L"Default hold_off", LINE_INFO());
                Assert::AreEqual(int(rtx_trigger_hysteresis::automatic), int(t.hysteresis()), L"Default hysteresis", LINE_INFO());
                Assert::AreEqual(1, int(t.input()), L"Default input", LINE_INFO());
                Assert::AreEqual("", t.level().unit(), L"Default level_unit", LINE_INFO());
                Assert::AreEqual(0.0f, t.level().value(), L"Default level_value", LINE_INFO());
                Assert::AreEqual(int(rtx_trigger_mode::automatic), int(t.mode()), L"Default mode", LINE_INFO());
                Assert::AreEqual(int(rtx_trigger_slope::rising), int(t.slope()), L"Default coupling", LINE_INFO());
                Assert::AreEqual("CH1", t.source(), L"Default source", LINE_INFO());

                t.coupling(rtx_trigger_coupling::low_frequency_reject);
                Assert::AreEqual(int(rtx_trigger_coupling::low_frequency_reject), int(t.coupling()), L"Set coupling", LINE_INFO());

                t.hold_off("10s");
                Assert::AreEqual("10s", t.hold_off(), L"Set hold_off", LINE_INFO());

                t.hysteresis(rtx_trigger_hysteresis::high);
                Assert::AreEqual(int(rtx_trigger_hysteresis::high), int(t.hysteresis()), L"Default hysteresis", LINE_INFO());

                t.level(3, rtx_quantity(42, "ms"));
                Assert::AreEqual(3, int(t.input()), L"Set level", LINE_INFO());
                Assert::AreEqual("ms", t.level().unit(), L"Set level", LINE_INFO());
                Assert::AreEqual(42.0f, t.level().value(), L"Set level", LINE_INFO());

                t.mode(rtx_trigger_mode::automatic);
                Assert::AreEqual(int(rtx_trigger_mode::automatic), int(t.mode()), L"Set mode", LINE_INFO());

                t.slope(rtx_trigger_slope::falling);
                Assert::AreEqual(int(rtx_trigger_slope::falling), int(t.slope()), L"Set coupling", LINE_INFO());

                t.source("CH3");
                Assert::AreEqual("CH3", t.source(), L"Set source", LINE_INFO());

            }
        }
    };

} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
