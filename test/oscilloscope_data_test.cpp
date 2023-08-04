// <copyright file="oscilloscope_data_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace visus {
namespace power_overwhelming {
namespace test {

    TEST_CLASS(oscilloscope_data_test) {

    public:

        TEST_METHOD(test_oscilloscope_waveform_ctor) {
            Assert::ExpectException<std::invalid_argument>([](void) {
                oscilloscope_waveform waveform(nullptr, 0.0f, blob());
            }, L"Header nullptr", LINE_INFO());

            Assert::ExpectException<std::invalid_argument>([](void) {
                oscilloscope_waveform waveform("bla", 0.0f, blob());
            }, L"Invalid header", LINE_INFO());

            Assert::ExpectException<std::invalid_argument>([](void) {
                oscilloscope_waveform waveform("0.0, 1.0, 42, 1", 0.0f, blob());
            }, L"Sample size mismatch", LINE_INFO());

            {
                oscilloscope_waveform waveform("0.0, 1.0, 42, 1", 99.0f, blob(42 * sizeof(float)));
                Assert::AreEqual(0.0f, waveform.time_begin(), L"time_begin", LINE_INFO());
                Assert::AreEqual(1.0f, waveform.time_end(), L"time_end", LINE_INFO());
                Assert::AreEqual(99.0f, waveform.segment_offset(), L"segment_offset", LINE_INFO());
                Assert::AreEqual(std::size_t(42), waveform.record_length(), L"record_length", LINE_INFO());
            }
        }

        TEST_METHOD(test_oscilloscope_waveform) {
            blob samples(8 * sizeof(float));
            for (std::size_t i = 0; i < samples.size() / sizeof(float); ++i) {
                samples.as<float>()[i] = 2.0f * i;
            }

            oscilloscope_waveform waveform("0.0, 1.0, 8, 1", 99.0f, std::move(samples));
            Assert::AreEqual(0.0f, waveform.time_begin(), L"time_begin", LINE_INFO());
            Assert::AreEqual(1.0f, waveform.time_end(), L"time_end", LINE_INFO());
            Assert::AreEqual(99.0f, waveform.segment_offset(), L"segment_offset", LINE_INFO());
            Assert::AreEqual(std::size_t(8), waveform.record_length(), L"record_length", LINE_INFO());

            Assert::AreEqual(0.0f, waveform.sample(0), L"sample 0", LINE_INFO());
            Assert::AreEqual(2.0f, waveform.sample(1), L"sample 1", LINE_INFO());
            Assert::AreEqual(4.0f, waveform.sample(2), L"sample 2", LINE_INFO());
            Assert::AreEqual(6.0f, waveform.sample(3), L"sample 3", LINE_INFO());
            Assert::AreEqual(8.0f, waveform.sample(4), L"sample 4", LINE_INFO());
            Assert::AreEqual(10.0f, waveform.sample(5), L"sample 5", LINE_INFO());
            Assert::AreEqual(12.0f, waveform.sample(6), L"sample 6", LINE_INFO());
            Assert::AreEqual(14.0f, waveform.sample(7), L"sample 7", LINE_INFO());

            Assert::IsNotNull(waveform.begin(), L"begin", LINE_INFO());
            Assert::IsNotNull(waveform.end(), L"end", LINE_INFO());
            Assert::AreEqual(0.0f, *waveform.begin(), L"*begin", LINE_INFO());
        }

        TEST_METHOD(test_oscilloscope_sample_default_ctor) {
            oscilloscope_sample sample;
            Assert::IsTrue(sample.empty(), L"empty", LINE_INFO());
            Assert::AreEqual(std::size_t(0), sample.size(), L"size", LINE_INFO());
            Assert::IsNull(sample.begin(), L"begin", LINE_INFO());
            Assert::IsNull(sample.end(), L"begin", LINE_INFO());
        }

        TEST_METHOD(test_oscilloscope_sample_ctor) {
            blob data(8 * sizeof(float));
            for (std::size_t i = 0; i < data.size() / sizeof(float); ++i) {
                data.as<float>()[i] = 2.0f * i;
            }

            oscilloscope_channel::channel_type channel = 42;
            oscilloscope_waveform waveform("0.0, 1.0, 8, 1", 99.0f, std::move(data));

            oscilloscope_sample sample(&channel, &waveform, 1);
            Assert::IsFalse(sample.empty(), L"empty", LINE_INFO());
            Assert::AreEqual(std::size_t(1), sample.size(), L"size", LINE_INFO());
            Assert::IsNotNull(sample.begin(), L"begin", LINE_INFO());
            Assert::IsNotNull(sample.end(), L"begin", LINE_INFO());

            Assert::IsNull(waveform.samples(), L"waveform moved", LINE_INFO());

            Assert::AreEqual(channel, sample[0].channel(), L"channel", LINE_INFO());
            Assert::AreEqual(std::size_t(8), sample[0].waveform().record_length(), L"record_length", LINE_INFO());
        }
    };

} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
