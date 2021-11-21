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
                auto n = std::chrono::high_resolution_clock::now();
                auto t = detail::timestamp<timestamp_resolution::seconds>::create();
                auto s = std::chrono::duration_cast<std::chrono::seconds>(n.time_since_epoch());
                Assert::AreEqual(s.count(), t, L"timestamp second", LINE_INFO());
            }

            {
                auto n = std::chrono::high_resolution_clock::now();
                auto t = detail::timestamp<timestamp_resolution::milliseconds>::create();
                auto s = std::chrono::duration_cast<std::chrono::milliseconds>(n.time_since_epoch());
                Assert::IsTrue(t - s.count() < 10, L"timestamp millisecond", LINE_INFO());
            }

            {
                auto n = std::chrono::high_resolution_clock::now();
                auto t = detail::timestamp<timestamp_resolution::nanoseconds>::create();
                auto s = std::chrono::duration_cast<std::chrono::nanoseconds>(n.time_since_epoch());
                Assert::IsTrue(t - s.count() < 1000, L"timestamp nanosecond", LINE_INFO());
            }
        }
    };
} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
