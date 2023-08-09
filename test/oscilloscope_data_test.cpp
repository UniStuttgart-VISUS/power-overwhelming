// <copyright file="oscilloscope_data_test.cpp" company="Visualisierungsinstitut der Universit�t Stuttgart">
// Copyright � 2023 Visualisierungsinstitut der Universit�t Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph M�ller</author>

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
                oscilloscope_waveform waveform(nullptr, nullptr, nullptr, nullptr, blob());
            }, L"Header nullptr", LINE_INFO());

            Assert::ExpectException<std::invalid_argument>([](void) {
                oscilloscope_waveform waveform("bla", "1,1,1", "2,2,2", "3", blob());
            }, L"Invalid header", LINE_INFO());

            Assert::ExpectException<std::invalid_argument>([](void) {
                oscilloscope_waveform waveform("0.0, 1.0, 42, 1", "1,1,1", "2,2,2", "3", blob());
            }, L"Sample size mismatch", LINE_INFO());

            {
                const oscilloscope_waveform waveform("0.0, 1.0, 42, 1", "1,2,3", "3, 4, 6", "99", blob(42 * sizeof(float)));
                Assert::AreEqual(0.0f, waveform.time_begin(), L"time_begin", LINE_INFO());
                Assert::AreEqual(1.0f, waveform.time_end(), L"time_end", LINE_INFO());
                Assert::AreEqual(99.0f, waveform.segment_offset(), L"segment_offset", LINE_INFO());
                Assert::AreEqual(std::size_t(42), waveform.record_length(), L"record_length", LINE_INFO());
            }

            {
                oscilloscope_waveform waveform("0.0, 1.0, 42, 1", "1,2,3", "3, 4, 6", "99", blob(42 * sizeof(float)));
                const oscilloscope_waveform expected("0.0, 1.0, 42, 1", "1,2,3", "3, 4, 6", "99", blob(42 * sizeof(float)));
                const oscilloscope_waveform actual(std::move(waveform));

                Assert::AreEqual(expected.time_begin(), actual.time_begin(), L"time_begin", LINE_INFO());
                Assert::AreEqual(expected.time_end(), actual.time_end(), L"time_end", LINE_INFO());
                Assert::AreEqual(expected.segment_offset(), actual.segment_offset(), L"segment_offset", LINE_INFO());
                Assert::AreEqual(expected.record_length(), actual.record_length(), L"record_length", LINE_INFO());

                Assert::AreEqual(0.0f, waveform.time_begin(), L"source time_begin", LINE_INFO());
                Assert::AreEqual(0.0f, waveform.time_end(), L"source time_end", LINE_INFO());
                Assert::AreEqual(0.0f, waveform.segment_offset(), L"source segment_offset", LINE_INFO());
                Assert::AreEqual(std::size_t(0), waveform.record_length(), L"source record_length", LINE_INFO());
            }
        }

        TEST_METHOD(test_oscilloscope_waveform) {
            blob samples(8 * sizeof(float));
            for (std::size_t i = 0; i < samples.size() / sizeof(float); ++i) {
                samples.as<float>()[i] = 2.0f * i;
            }

            oscilloscope_waveform waveform("0.0, 1.0, 8, 1", "1,2,3", "3, 4, 6", "99", std::move(samples));
            Assert::AreEqual(0.0f, waveform.time_begin(), L"time_begin", LINE_INFO());
            Assert::AreEqual(1.0f, waveform.time_end(), L"time_end", LINE_INFO());
            Assert::AreEqual(99.0f, waveform.segment_offset(), L"segment_offset", LINE_INFO());
            Assert::AreEqual(std::size_t(8), waveform.record_length(), L"record_length", LINE_INFO());
            Assert::AreEqual(waveform.record_length(), waveform.size(), L"size", LINE_INFO());

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
            oscilloscope_waveform waveform("0.0, 1.0, 8, 1", "1,2,3", "3, 4, 6", "99", std::move(data));
            Assert::IsFalse(waveform.empty(), L"waveform not empty", LINE_INFO());

            oscilloscope_sample sample(&channel, &waveform, 1);
            Assert::IsFalse(sample.empty(), L"empty", LINE_INFO());
            Assert::AreEqual(std::size_t(1), sample.size(), L"size", LINE_INFO());
            Assert::IsNotNull(sample.begin(), L"begin", LINE_INFO());
            Assert::IsNotNull(sample.end(), L"begin", LINE_INFO());

            Assert::IsNull(waveform.samples(), L"waveform moved", LINE_INFO());
            Assert::IsTrue(waveform.empty(), L"waveform empty", LINE_INFO());

            Assert::AreEqual(channel, sample[0].channel(), L"channel", LINE_INFO());
            Assert::AreEqual(std::size_t(8), sample[0].waveform().record_length(), L"record_length", LINE_INFO());
        }

        TEST_METHOD(test_multi_channel_oscilloscope_sample) {
            const oscilloscope_channel::channel_type channels[] = { 42, 44 };

            blob data0(4 * sizeof(float));
            for (std::size_t i = 0; i < data0.size() / sizeof(float); ++i) {
                data0.as<float>()[i] = i;
            }

            blob data1(4 * sizeof(float));
            for (std::size_t i = 0; i < data1.size() / sizeof(float); ++i) {
                data1.as<float>()[i] = 2.0f * i;
            }

            oscilloscope_waveform waveforms[] = {
                oscilloscope_waveform("0.0, 1.0, 4, 1", "1,2,3", "3, 4, 6", "99", std::move(data0)),
                oscilloscope_waveform("0.0, 1.0, 4, 1", "2023,8,9", "17, 39, 00.5", "99", std::move(data1))
            };

            oscilloscope_sample sample(channels, waveforms, 2);
            Assert::IsFalse(sample.empty(), L"empty", LINE_INFO());
            Assert::AreEqual(std::size_t(2), sample.size(), L"size", LINE_INFO());
            Assert::IsNotNull(sample.begin(), L"begin", LINE_INFO());
            Assert::IsNotNull(sample.end(), L"begin", LINE_INFO());

            Assert::AreEqual(channels[0], sample[0].channel(), L"channel #0", LINE_INFO());
            Assert::AreEqual(channels[1], sample[1].channel(), L"channel #1", LINE_INFO());

            Assert::AreEqual(std::size_t(4), sample[0].waveform().record_length(), L"record_length #0", LINE_INFO());
            Assert::AreEqual(std::size_t(4), sample[1].waveform().record_length(), L"record_length #1", LINE_INFO());
        }

        TEST_METHOD(test_multi_segment_oscilloscope_sample) {
            const oscilloscope_channel::channel_type channels[] = { 42 };

            blob data0(4 * sizeof(float));
            for (std::size_t i = 0; i < data0.size() / sizeof(float); ++i) {
                data0.as<float>()[i] = i;
            }

            blob data1(4 * sizeof(float));
            for (std::size_t i = 0; i < data1.size() / sizeof(float); ++i) {
                data1.as<float>()[i] = 2.0f * i;
            }

            oscilloscope_waveform waveforms[] = {
                oscilloscope_waveform("0.0, 1.0, 4, 1", "1,2,3", "3, 4, 6", "99", std::move(data0)),
                oscilloscope_waveform("0.0, 1.0, 4, 1", "2023,8,9", "17, 39, 00.5", "99", std::move(data1))
            };

            oscilloscope_sample sample(channels, waveforms, 1, 2);
            Assert::IsFalse(sample.empty(), L"empty", LINE_INFO());
            Assert::AreEqual(std::size_t(2), sample.size(), L"size", LINE_INFO());
            Assert::IsNotNull(sample.begin(), L"begin", LINE_INFO());
            Assert::IsNotNull(sample.end(), L"begin", LINE_INFO());

            Assert::AreEqual(channels[0], sample[0].channel(), L"channel #0", LINE_INFO());

            Assert::AreEqual(std::size_t(4), sample[0].waveform().record_length(), L"record_length #0", LINE_INFO());
            Assert::AreEqual(std::size_t(4), sample[1].waveform().record_length(), L"record_length #1", LINE_INFO());
        }

        TEST_METHOD(test_multi_channel_multi_segment_oscilloscope_sample) {
            const std::size_t segments = 2;
            const std::vector<oscilloscope_channel::channel_type> channels = { 17, 42, 44 };
            std::vector<oscilloscope_waveform> waveforms;

            for (std::size_t i = 0; i < segments * channels.size(); ++i) {
                blob data(4 * sizeof(float));
                for (std::size_t j = 0; j < data.size() / sizeof(float); ++j) {
                    data.as<float>()[j] = i * j;
                }

                auto date = std::to_string(i) + "," + std::to_string(i) + ",42";
                waveforms.emplace_back("0.0, 1.0, 4, 1", date.c_str(), "3, 4, 6", "99", std::move(data));
            }

            oscilloscope_sample sample(channels.data(), waveforms.data(), channels.size(), segments);
            Assert::IsFalse(sample.empty(), L"empty", LINE_INFO());
            Assert::AreEqual(std::size_t(segments * channels.size()), sample.size(), L"size", LINE_INFO());
            Assert::IsNotNull(sample.begin(), L"begin", LINE_INFO());
            Assert::IsNotNull(sample.end(), L"begin", LINE_INFO());

            Assert::AreEqual(channels[0], sample[0].channel(), L"channel #0", LINE_INFO());
            Assert::AreEqual(channels[1], sample[1].channel(), L"channel #1", LINE_INFO());
            Assert::AreEqual(channels[2], sample[2].channel(), L"channel #2", LINE_INFO());
            Assert::AreEqual(channels[0], sample[3].channel(), L"channel #3", LINE_INFO());
            Assert::AreEqual(channels[1], sample[4].channel(), L"channel #4", LINE_INFO());
            Assert::AreEqual(channels[2], sample[5].channel(), L"channel #5", LINE_INFO());

            Assert::AreEqual(std::size_t(4), sample[0].waveform().record_length(), L"record_length #0", LINE_INFO());
            Assert::AreEqual(std::size_t(4), sample[1].waveform().record_length(), L"record_length #1", LINE_INFO());
            Assert::AreEqual(std::size_t(4), sample[2].waveform().record_length(), L"record_length #2", LINE_INFO());
            Assert::AreEqual(std::size_t(4), sample[3].waveform().record_length(), L"record_length #3", LINE_INFO());
            Assert::AreEqual(std::size_t(4), sample[4].waveform().record_length(), L"record_length #4", LINE_INFO());
            Assert::AreEqual(std::size_t(4), sample[5].waveform().record_length(), L"record_length #5", LINE_INFO());

        }
    };

} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
