// <copyright file="measurement_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
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
                auto m = measurement(L"test", timestamp(42), 2.0f, 3.0f, 6.1f);
                Assert::AreEqual(2.0f, m.voltage(), L"voltage", LINE_INFO());
                Assert::AreEqual(3.0f, m.current(), L"current", LINE_INFO());
                Assert::AreEqual(6.1f, m.power(), L"power", LINE_INFO());
                Assert::AreEqual(L"test", m.sensor(), L"sensor", LINE_INFO());
                Assert::AreEqual(std::int64_t(42), m.timestamp().value(), L"timestamp", LINE_INFO());
                Assert::IsTrue(m, L"operator bool", LINE_INFO());
            }

            {
                auto m = measurement(L"test", timestamp(42), 2.0f, 3.0f);
                Assert::AreEqual(2.0f, m.voltage(), L"voltage", LINE_INFO());
                Assert::AreEqual(3.0f, m.current(), L"current", LINE_INFO());
                Assert::AreEqual(6.0f, m.power(), L"power", LINE_INFO());
                Assert::AreEqual(L"test", m.sensor(), L"sensor", LINE_INFO());
                Assert::AreEqual(std::int64_t(42), m.timestamp().value(), L"timestamp", LINE_INFO());
                Assert::IsTrue(m, L"operator bool", LINE_INFO());
            }

            {
                auto m = measurement(L"test", timestamp(42), 2.0f);
                Assert::AreEqual(measurement::invalid_value, m.voltage(), L"voltage", LINE_INFO());
                Assert::AreEqual(measurement::invalid_value, m.current(), L"current", LINE_INFO());
                Assert::AreEqual(2.0f, m.power(), L"power", LINE_INFO());
                Assert::AreEqual(L"test", m.sensor(), L"sensor", LINE_INFO());
                Assert::AreEqual(std::int64_t(42), m.timestamp().value(), L"timestamp", LINE_INFO());
                Assert::IsTrue(m, L"operator bool", LINE_INFO());
            }

            Assert::ExpectException<std::invalid_argument>([](void) {
                auto m = measurement(nullptr, timestamp(42), 2.0f, 3.0f, 6.1f);
            });

            Assert::ExpectException<std::invalid_argument>([](void) {
                auto m = measurement(nullptr, timestamp(42), 2.0f, 3.0f);
            });

            Assert::ExpectException<std::invalid_argument>([](void) {
                auto m = measurement(nullptr, timestamp(42), 2.0f);
            });

            Assert::ExpectException<std::invalid_argument>([](void) {
                auto m = measurement(L"test", timestamp(42), measurement::invalid_value, 3.0f);
            });

            Assert::ExpectException<std::invalid_argument>([](void) {
                auto m = measurement(L"test", timestamp(42), 2.0f, measurement::invalid_value);
            });

            Assert::ExpectException<std::invalid_argument>([](void) {
                auto m = measurement(L"test", timestamp(42), measurement::invalid_value);
            });
        }

        TEST_METHOD(test_copy) {
            {
                auto m = measurement(L"test", timestamp(42), 2.0f, 3.0f, 6.1f);
                auto n = m;

                Assert::AreEqual(m.voltage(), n.voltage(), L"voltage", LINE_INFO());
                Assert::AreEqual(m.current(), n.current(), L"current", LINE_INFO());
                Assert::AreEqual(m.power(), n.power(), L"power", LINE_INFO());
                Assert::AreEqual(m.sensor(), n.sensor(), L"sensor", LINE_INFO());
                Assert::AreEqual(m.timestamp().value(), n.timestamp().value(), L"timestamp", LINE_INFO());
                Assert::IsTrue(m, L"source operator bool", LINE_INFO());
                Assert::IsTrue(n, L"destination operator bool", LINE_INFO());
            }

            {
                auto m = measurement(L"test", timestamp(42), 2.0f, 3.0f, 6.1f);
                auto n = std::move(m);

                Assert::AreEqual(measurement::invalid_value, m.voltage(), L"voltage", LINE_INFO());
                Assert::AreEqual(measurement::invalid_value, m.current(), L"current", LINE_INFO());
                Assert::IsNull(m.sensor(), L"sensor", LINE_INFO());
                Assert::AreEqual(std::int64_t(0), m.timestamp().value(), L"timestamp", LINE_INFO());
                Assert::IsFalse(m, L"source operator bool", LINE_INFO());

                Assert::AreEqual(2.0f, n.voltage(), L"voltage", LINE_INFO());
                Assert::AreEqual(3.0f, n.current(), L"current", LINE_INFO());
                Assert::AreEqual(6.1f, n.power(), L"power", LINE_INFO());
                Assert::AreEqual(L"test", n.sensor(), L"sensor", LINE_INFO());
                Assert::AreEqual(std::int64_t(42), n.timestamp().value(), L"timestamp", LINE_INFO());
                Assert::IsTrue(n, L"destination operator bool", LINE_INFO());
            }
        }
    };
} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
