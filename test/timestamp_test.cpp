// <copyright file="timestamp_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace visus {
namespace power_overwhelming {
namespace test {

    TEST_CLASS(timestamp_test) {

    public:

        TEST_METHOD(test_construction) {
            {
                auto n = std::chrono::system_clock::now();
                auto t = timestamp<std::chrono::system_clock::time_point>::create();
                Assert::IsTrue(std::chrono::duration_cast<std::chrono::milliseconds>(t - n).count() < 10, L"timestamp from system clock", LINE_INFO());
            }

            {
                auto n = std::chrono::high_resolution_clock::now();
                auto t = timestamp<std::chrono::high_resolution_clock::time_point>::create();
                Assert::IsTrue(std::chrono::duration_cast<std::chrono::milliseconds>(t - n).count() < 10, L"timestamp from hires clock", LINE_INFO());
            }
        }
    };
} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
