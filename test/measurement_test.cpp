// <copyright file="measurement_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace visus {
namespace power_overwhelming {
namespace test {

    TEST_CLASS(measurement_test) {

    public:

        TEST_METHOD(test_construction) {
            {
                auto m = measurement<>(std::chrono::high_resolution_clock::now(), 2.0f, 3.0f);
                Assert::AreEqual(2.0f, m.voltage(), L"voltage", LINE_INFO());
                Assert::AreEqual(3.0f, m.current(), L"current", LINE_INFO());
                Assert::AreEqual(6.0f, m.power(), L"power", LINE_INFO());
            }

            {
                auto m = measurement<>(std::chrono::high_resolution_clock::now(), 2.0f, 3.0f, 6.1f);
                Assert::AreEqual(2.0f, m.voltage(), L"voltage", LINE_INFO());
                Assert::AreEqual(3.0f, m.current(), L"current", LINE_INFO());
                Assert::AreEqual(6.1f, m.power(), L"power", LINE_INFO());
            }

            {
                auto m = measurement<>(std::chrono::high_resolution_clock::now(), 2.0f);
                Assert::AreEqual(std::numeric_limits<float>::lowest(), m.voltage(), L"voltage", LINE_INFO());
                Assert::AreEqual(std::numeric_limits<float>::lowest(), m.current(), L"current", LINE_INFO());
                Assert::AreEqual(2.0f, m.power(), L"power", LINE_INFO());
            }
        }
    };
} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
