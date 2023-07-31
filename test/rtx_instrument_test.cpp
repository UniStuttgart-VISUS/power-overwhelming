// <copyright file="rtx_instrument_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace visus {
namespace power_overwhelming {
namespace test {

    TEST_CLASS(rtx_instrument_test) {

    public:

        TEST_METHOD(test_config_dft_ctor) {
            const oscilloscope_single_acquisition expected_acquisition;
            const oscilloscope_edge_trigger expected_trigger("EXT");

            rtx_instrument_configuration config;
            Assert::AreEqual(expected_acquisition.automatic_points(), config.acquisition().automatic_points(), L"acquisition.automatic_points", LINE_INFO());
            Assert::AreEqual(expected_acquisition.count(), config.acquisition().count(), L"acquisition.count", LINE_INFO());
            Assert::AreEqual(expected_acquisition.points(), config.acquisition().points(), L"acquisition.points", LINE_INFO());
            Assert::AreEqual(expected_acquisition.segmented(), config.acquisition().segmented(), L"acquisition.segmented", LINE_INFO());
            Assert::AreEqual(std::size_t(0), config.beep_on_apply(), L"beep_on_apply", LINE_INFO());
            Assert::IsFalse(config.beep_on_error(), L"beep_on_error", LINE_INFO());
            Assert::IsFalse(config.beep_on_trigger(), L"beep_on_trigger", LINE_INFO());
            Assert::AreEqual(0.0f, config.time_range().value(), L"time_range.value", LINE_INFO());
            Assert::AreEqual("", config.time_range().unit(), L"time_range.unit", LINE_INFO());
            Assert::AreEqual(int(expected_trigger.coupling()), int(config.trigger().coupling()), L"trigger.coupling", LINE_INFO());
            Assert::AreEqual(expected_trigger.hold_off(), config.trigger().hold_off(), L"trigger.hold_off", LINE_INFO());
            Assert::AreEqual(int(expected_trigger.hysteresis()), int(config.trigger().hysteresis()), L"trigger.hysteresis", LINE_INFO());
            Assert::AreEqual(int(expected_trigger.input()), int(config.trigger().input()), L"trigger.input", LINE_INFO());
            Assert::AreEqual(expected_trigger.level().value(), config.trigger().level().value(), L"trigger.level.value", LINE_INFO());
            Assert::AreEqual(expected_trigger.level().unit(), config.trigger().level().unit(), L"trigger.level.unit", LINE_INFO());
            Assert::AreEqual(int(expected_trigger.mode()), int(config.trigger().mode()), L"trigger.mode", LINE_INFO());
            Assert::AreEqual(expected_trigger.source(), config.trigger().source(), L"trigger.source", LINE_INFO());
            Assert::AreEqual(int(expected_trigger.slope()), int(config.trigger().slope()), L"trigger.slope", LINE_INFO());
            Assert::AreEqual(expected_trigger.type(), config.trigger().type(), L"trigger.type", LINE_INFO());
        }

        TEST_METHOD(test_config_channel) {
            rtx_instrument_configuration config;

            config.channel(oscilloscope_channel(1).range(17.0f));
            Assert::AreEqual(std::size_t(1), config.channels(), L"Channel added", LINE_INFO());

            config.channel(oscilloscope_channel(1).range(42.0f));
            Assert::AreEqual(std::size_t(1), config.channels(), L"Channel overwritten", LINE_INFO());

            config.channel(oscilloscope_channel(2).range(43.0f));
            Assert::AreEqual(std::size_t(2), config.channels(), L"Channel added", LINE_INFO());

            std::vector<oscilloscope_channel> channels(config.channels());
            config.channels(channels.data(), channels.size());

            Assert::AreEqual(std::uint32_t(1), channels[0].channel(), L"Channel 1", LINE_INFO());
            Assert::AreEqual(42.0f, channels[0].range().value(), L"range.value #1", LINE_INFO());
            Assert::AreEqual(std::uint32_t(2), channels[1].channel(), L"Channel 2", LINE_INFO());
            Assert::AreEqual(43.0f, channels[1].range().value(), L"range.value #2", LINE_INFO());
        }


    };
} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
