// <copyright file="measurement_data_series_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace visus {
namespace power_overwhelming {
namespace test {

    TEST_CLASS(measurement_data_series_test) {

    public:

        TEST_METHOD(test_construction) {
            Assert::ExpectException<std::invalid_argument>([](void) {
                measurement_data_series s(nullptr);
            }, L"Sensor name must be provided", LINE_INFO());

            {
                measurement_data_series s(L"sensor");
                Assert::AreEqual(L"sensor", s.sensor(), L"Sensor name", LINE_INFO());
                Assert::AreEqual(std::size_t(0), s.size(), L"Size", LINE_INFO());
                Assert::IsTrue(bool(s), L"Series is valid", LINE_INFO());
                Assert::IsNull(s.data(), L"No data", LINE_INFO());
                Assert::IsTrue(s.empty(), L"Series is empty", LINE_INFO());
            }
        }

        TEST_METHOD(test_resize) {
            measurement_data_series s(L"sensor");

            {
                auto d = measurement_data_series::resize(s, 1);
                Assert::IsNotNull(d, L"Data allocated", LINE_INFO());
                Assert::AreEqual((void *) d, (void *) s.data(), L"Data returned", LINE_INFO());
                Assert::AreEqual(std::size_t(1), s.size(), L"New size", LINE_INFO());
                Assert::IsFalse(s.empty(), L"Series is not empty any more", LINE_INFO());

                *d = measurement_data(42, 43.0f, 44.0f, 45.0f);
                Assert::AreEqual(measurement_data::timestamp_type(42), s.begin()->timestamp(), L"Data assigned", LINE_INFO());
            }

            {
                auto d = measurement_data_series::resize(s, 2);
                Assert::IsNotNull(d, L"Data allocated", LINE_INFO());
                Assert::AreEqual((void *) d, (void *)s.data(), L"Data returned", LINE_INFO());
                Assert::AreEqual(std::size_t(2), s.size(), L"New size", LINE_INFO());
                Assert::AreEqual(measurement_data::timestamp_type(42), s.begin()->timestamp(), L"Data copied", LINE_INFO());
            }

            {
                auto d = measurement_data_series::resize(s, 1);
                Assert::IsNotNull(d, L"Data allocated", LINE_INFO());
                Assert::AreEqual((void *) d, (void *)s.data(), L"Data returned", LINE_INFO());
                Assert::AreEqual(std::size_t(1), s.size(), L"New size", LINE_INFO());
                Assert::AreEqual(measurement_data::timestamp_type(42), s.begin()->timestamp(), L"Data copied", LINE_INFO());
            }

            {
                auto d = measurement_data_series::resize(s, 0);
                Assert::IsNull(d, L"Data freed", LINE_INFO());
                Assert::AreEqual(std::size_t(0), s.size(), L"New size", LINE_INFO());
                Assert::IsTrue(s.empty(), L"Series is empty", LINE_INFO());
            }
        }
    };
} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
