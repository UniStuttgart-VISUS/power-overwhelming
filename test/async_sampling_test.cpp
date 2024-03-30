// <copyright file="async_sampling_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
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
            Assert::IsFalse(bool(as), L"Not enabled", LINE_INFO());
        }

        TEST_METHOD(test_measurement) {
            const auto cb = [](const measurement&, void *) { };

            async_sampling as;
            as.samples_every(1000)
                .delivers_measurements_to(cb)
                .from_source(tinkerforge_sensor_source::power)
                .passes_context((void *) 42);

            Assert::AreEqual(intptr_t(42), intptr_t(as.context()), L"Context is 42", LINE_INFO());
            Assert::AreEqual(int(tinkerforge_sensor_source::power), int(as.tinkerforge_sensor_source()), L"Power only", LINE_INFO());
            Assert::AreEqual(std::uint64_t(1000), as.interval(), L"1 ms interval", LINE_INFO());
            Assert::AreEqual(int(async_delivery_method::on_measurement), int(as.delivery_method()), L"on_measurement enabled", LINE_INFO());
            Assert::IsTrue(bool(as), L"Is enabled", LINE_INFO());
        }

        TEST_METHOD(test_measurement_data) {
            const auto cb = [](const wchar_t *, const measurement_data *, const std::size_t, void *) { };

            const auto as = std::move(async_sampling()
                .samples_every(1000)
                .delivers_measurement_data_to(cb)
                .from_source(tinkerforge_sensor_source::power)
                .passes_context((void *) 42));

            Assert::AreEqual(intptr_t(42), intptr_t(as.context()), L"Context is 42", LINE_INFO());
            Assert::AreEqual(int(tinkerforge_sensor_source::power), int(as.tinkerforge_sensor_source()), L"Power only", LINE_INFO());
            Assert::AreEqual(std::uint64_t(1000), as.interval(), L"1 ms interval", LINE_INFO());
            Assert::AreEqual(int(async_delivery_method::on_measurement_data), int(as.delivery_method()), L"on_measurement_data enabled", LINE_INFO());
            Assert::IsTrue(bool(as), L"Is enabled", LINE_INFO());
        }

        TEST_METHOD(test_throttling_sample) {
            const auto cb = [](const wchar_t *, const throttling_sample *, const std::size_t, void *) { };

            const auto as = std::move(async_sampling()
                .samples_every(1000)
                .delivers_throttling_samples_to(cb)
                .passes_context((void *)42));

            Assert::AreEqual(intptr_t(42), intptr_t(as.context()), L"Context is 42", LINE_INFO());
            Assert::AreEqual(std::uint64_t(1000), as.interval(), L"1 ms interval", LINE_INFO());
            Assert::AreEqual(int(async_delivery_method::on_throttling_sample), int(as.delivery_method()), L"on_throttling_sample enabled", LINE_INFO());
            Assert::IsTrue(bool(as), L"Is enabled", LINE_INFO());
        }

        TEST_METHOD(test_thermal_sample) {
            const auto cb = [](const wchar_t *, const thermal_sample *, const std::size_t, void *) { };

            const auto as = std::move(async_sampling()
                .samples_every(1000)
                .delivers_thermal_samples_to(cb)
                .passes_context((void *)42));

            Assert::AreEqual(intptr_t(42), intptr_t(as.context()), L"Context is 42", LINE_INFO());
            Assert::AreEqual(std::uint64_t(1000), as.interval(), L"1 ms interval", LINE_INFO());
            Assert::AreEqual(int(async_delivery_method::on_thermal_sample), int(as.delivery_method()), L"on_thermal_sample enabled", LINE_INFO());
            Assert::IsTrue(bool(as), L"Is enabled", LINE_INFO());
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
            measurement_data data(timestamp::zero, 0.0f);
            std::wstring source;

            const auto as = std::move(async_sampling()
                .delivers_measurement_data_to_functor(
                        [&](const wchar_t *s, const measurement_data *m, const std::size_t) {
                    data = *m;
                    source = s;
                }));

            Assert::IsNotNull(as.context(), L"Context created", LINE_INFO());
            as.deliver(L"dummy", measurement_data(timestamp(1), 2.0f));
            Assert::AreEqual(timestamp::value_type(1), data.timestamp().value(), L"timestamp assigned", LINE_INFO());
            Assert::AreEqual(2.0f, data.power(), L"power assigned", LINE_INFO());
            Assert::AreEqual(L"dummy", source.c_str(), L"source assigned", LINE_INFO());
        }

        TEST_METHOD(test_throttling_lambda) {
            throttling_sample data;
            std::wstring source;

            const auto as = std::move(async_sampling()
                .delivers_throttling_samples_to_functor(
                    [&](const wchar_t *s, const throttling_sample *m, const std::size_t) {
                data = *m;
                source = s;
            }));

            Assert::IsNotNull(as.context(), L"Context created", LINE_INFO());
            as.deliver(L"dummy", throttling_sample(timestamp(1), throttling_state::thermal));
            Assert::AreEqual(timestamp::value_type(1), data.timestamp().value(), L"timestamp assigned", LINE_INFO());
            Assert::AreEqual(int(throttling_state::thermal), int(data.state()), L"limit assigned", LINE_INFO());
            Assert::AreEqual(L"dummy", source.c_str(), L"source assigned", LINE_INFO());
        }

        TEST_METHOD(test_thermal_lambda) {
            thermal_sample data;
            std::wstring source;

            const auto as = std::move(async_sampling()
                .delivers_thermal_samples_to_functor(
                    [&](const wchar_t *s, const thermal_sample *m, const std::size_t) {
                data = *m;
                source = s;
            }));

            Assert::IsNotNull(as.context(), L"Context created", LINE_INFO());
            as.deliver(L"dummy", thermal_sample(timestamp(1), 42.0f));
            Assert::AreEqual(timestamp::value_type(1), data.timestamp().value(), L"timestamp assigned", LINE_INFO());
            Assert::AreEqual(42.0f, data.temperature(), L"temperature assigned", LINE_INFO());
            Assert::AreEqual(L"dummy", source.c_str(), L"source assigned", LINE_INFO());
        }
    };

} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
