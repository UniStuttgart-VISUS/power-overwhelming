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
            Assert::AreEqual(async_sampling::default_interval, as.interval(), L"1000 us default interval", LINE_INFO());
            Assert::IsFalse(as.triggered(), L"Not triggered", LINE_INFO());
            Assert::IsFalse(bool(as), L"Not enabled", LINE_INFO());
            Assert::AreEqual(int(timestamp_resolution::milliseconds), int(as.resolution()), L"Timestamps are in ms", LINE_INFO());
        }

        TEST_METHOD(test_measurement) {
            const auto cb = [](const measurement&, void *) { };

            async_sampling as;
            as.samples_every(1000)
                .delivers_measurements_to(cb)
                .from_source(tinkerforge_sensor_source::power)
                .passes_context((void *) 42)
                .using_resolution(timestamp_resolution::nanoseconds)
                .samples_on_trigger();

            Assert::AreEqual(intptr_t(42), intptr_t(as.context()), L"Context is 42", LINE_INFO());
            Assert::AreEqual(int(tinkerforge_sensor_source::power), int(as.tinkerforge_sensor_source()), L"Power only", LINE_INFO());
            Assert::AreEqual(std::uint64_t(1000), as.interval(), L"1 ms interval", LINE_INFO());
            Assert::IsTrue(as.on_measurement(), L"on_measurement enabled", LINE_INFO());
            Assert::IsTrue(as.triggered(), L"Triggered", LINE_INFO());
            Assert::IsTrue(bool(as), L"Is enabled", LINE_INFO());
            Assert::AreEqual(int(timestamp_resolution::nanoseconds), int(as.resolution()), L"Timestamps are in ns", LINE_INFO());
        }

        TEST_METHOD(test_measurement_data) {
            const auto cb = [](const wchar_t *, const measurement_data *, const std::size_t, void *) { };

             const auto as = std::move(async_sampling()
                 .samples_every(1000)
                 .delivers_measurement_data_to(cb)
                 .from_source(tinkerforge_sensor_source::power)
                 .passes_context((void *)42)
                 .using_resolution(timestamp_resolution::hundred_nanoseconds)
                 .samples_on_trigger());

            Assert::AreEqual(intptr_t(42), intptr_t(as.context()), L"Context is 42", LINE_INFO());
            Assert::AreEqual(int(tinkerforge_sensor_source::power), int(as.tinkerforge_sensor_source()), L"Power only", LINE_INFO());
            Assert::AreEqual(std::uint64_t(1000), as.interval(), L"1 ms interval", LINE_INFO());
            Assert::IsTrue(as.on_measurement_data(), L"on_measurement_data enabled", LINE_INFO());
            Assert::IsTrue(as.triggered(), L"Triggered", LINE_INFO());
            Assert::IsTrue(bool(as), L"Is enabled", LINE_INFO());
            Assert::AreEqual(int(timestamp_resolution::hundred_nanoseconds), int(as.resolution()), L"Timestamps are in 100 ns", LINE_INFO());
        }

        TEST_METHOD(test_owned_context) {
            const auto cb = [](const wchar_t *, const measurement_data *, const std::size_t, void *) {};

            auto as = std::move(async_sampling()
                .delivers_measurement_data_to(cb)
                .stores_and_passes_context(42));

            Assert::IsNotNull(as.context(), L"Context created", LINE_INFO());
            Assert::AreEqual(42, *((int *) as.context()), L"Context is 42", LINE_INFO());

            std::vector<int> context { 41, 42, 43 };
            as.stores_and_passes_context(std::move(context));
            Assert::IsTrue(context.empty(), L"Original context moved away", LINE_INFO());
            Assert::AreEqual(std::size_t(3), ((std::vector<int> *) as.context())->size(), L"Context has size 3", LINE_INFO());
        }

        TEST_METHOD(test_lambda) {
            measurement_data data(0, 0.0f);
            std::wstring source;

            const auto as = std::move(async_sampling()
                .delivers_measurement_data_to_functor(
                        [&](const wchar_t *s, const measurement_data *m, const std::size_t) {
                    data = *m;
                    source = s;
                }));

            Assert::IsNotNull(as.context(), L"Context created", LINE_INFO());
            as.deliver(L"dummy", measurement_data(1, 2.0f));
            Assert::AreEqual(measurement_data::timestamp_type(1), data.timestamp(), L"timestamp assigned", LINE_INFO());
            Assert::AreEqual(2.0f, data.power(), L"power assigned", LINE_INFO());
            Assert::AreEqual(L"dummy", source.c_str(), L"source assigned", LINE_INFO());
        }
    };

} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
