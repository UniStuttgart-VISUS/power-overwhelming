// <copyright file="async_sampling_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace visus {
namespace power_overwhelming {
namespace test {

    TEST_CLASS(async_sampling_test) {

    public:

        TEST_METHOD(test_default) {
            async_sampling as;
            Assert::IsNull(as.context(), L"Context is null", LINE_INFO());
            Assert::AreEqual(int(tinkerforge_sensor_source::all), int(as.tinkerforge_sensor_source()), L"All Tinkerforge enabled", LINE_INFO());
            Assert::AreEqual(std::uint64_t(1000), as.interval(), L"1000 us default interval", LINE_INFO());
            Assert::IsFalse(bool(as), L"Not enabled", LINE_INFO());
            Assert::AreEqual(int(timestamp_resolution::milliseconds), int(as.resolution()), L"Timestamps are in ms", LINE_INFO());
        }

        TEST_METHOD(test_measurement) {
            const auto cb = [](const measurement&, void *) { };

            async_sampling as;
            as.samples_every(5000)
                .from_source(tinkerforge_sensor_source::power)
                .passing_context((void *) 42)
                .produces_measurement(cb)
                .using_resolution(timestamp_resolution::nanoseconds);

            Assert::AreEqual(intptr_t(42), intptr_t(as.context()), L"Context is 42", LINE_INFO());
            Assert::AreEqual(int(tinkerforge_sensor_source::power), int(as.tinkerforge_sensor_source()), L"Power only", LINE_INFO());
            Assert::AreEqual(std::uint64_t(5000), as.interval(), L"5 ms interval", LINE_INFO());
            Assert::IsTrue(bool(as), L"Is enabled", LINE_INFO());
            Assert::AreEqual(int(timestamp_resolution::nanoseconds), int(as.resolution()), L"Timestamps are in ns", LINE_INFO());
        }

        TEST_METHOD(test_measurement_data) {
            const auto cb = [](const sensor&, const measurement_data&, void *) { };

             const auto as = std::move(async_sampling()
                 .samples_every(5000)
                 .from_source(tinkerforge_sensor_source::power)
                 .passing_context((void *)42)
                 .produces_measurement_data(cb)
                 .using_resolution(timestamp_resolution::hundred_nanoseconds));

            Assert::AreEqual(intptr_t(42), intptr_t(as.context()), L"Context is 42", LINE_INFO());
            Assert::AreEqual(int(tinkerforge_sensor_source::power), int(as.tinkerforge_sensor_source()), L"Power only", LINE_INFO());
            Assert::AreEqual(std::uint64_t(5000), as.interval(), L"5 ms interval", LINE_INFO());
            Assert::IsTrue(bool(as), L"Is enabled", LINE_INFO());
            Assert::AreEqual(int(timestamp_resolution::hundred_nanoseconds), int(as.resolution()), L"Timestamps are in 100 ns", LINE_INFO());
        }

    };
} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
