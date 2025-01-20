// <copyright file="rtx_acquisition_test.cpp" company="Visualisierungsinstitut der Universit�t Stuttgart">
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

    TEST_CLASS(rtx_acquisition_test) {

    public:

        TEST_METHOD(test_default_ctor) {
            rtx_acquisition acq;

            Assert::IsTrue(acq.automatic_points(), L"Default automatic_points", LINE_INFO());
            Assert::AreEqual(int(1), int(acq.count()), L"Default count", LINE_INFO());
            Assert::AreEqual(int(0), int(acq.points()), L"Default points", LINE_INFO());
            Assert::IsFalse(acq.segmented(), L"Default segmented", LINE_INFO());
            Assert::AreEqual(int(rtx_acquisition_state::unknown), int(acq.state()), L"Default state", LINE_INFO());
        }

        TEST_METHOD(test_fluid_api) {
            rtx_acquisition acq;
            acq.count(42)
                .points(17)
                .segmented(true)
                .state(rtx_acquisition_state::single);

            Assert::IsFalse(acq.automatic_points(), L"Set automatic_points", LINE_INFO());
            Assert::AreEqual(int(42), int(acq.count()), L"Set count", LINE_INFO());
            Assert::AreEqual(int(17), int(acq.points()), L"Set points", LINE_INFO());
            Assert::IsTrue(acq.segmented(), L"Set segmented", LINE_INFO());
            Assert::AreEqual(int(rtx_acquisition_state::single), int(acq.state()), L"Set state", LINE_INFO());

            acq.enable_automatic_points();
            Assert::IsTrue(acq.automatic_points(), L"Default automatic_points", LINE_INFO());
            Assert::AreEqual(int(42), int(acq.count()), L"Set count", LINE_INFO());
            Assert::AreEqual(int(0), int(acq.points()), L"Default points", LINE_INFO());
            Assert::IsTrue(acq.segmented(), L"Set segmented", LINE_INFO());
        }
    };

} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
