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
            const oscilloscope_acquisition expected_acquisition;
            const oscilloscope_edge_trigger expected_trigger("EXT");

            rtx_instrument_configuration config;
            Assert::AreEqual(expected_acquisition.automatic_points(), config.acquisition().automatic_points(), L"acquisition.automatic_points", LINE_INFO());
            Assert::AreEqual(expected_acquisition.count(), config.acquisition().count(), L"acquisition.count", LINE_INFO());
            Assert::AreEqual(expected_acquisition.points(), config.acquisition().points(), L"acquisition.points", LINE_INFO());
            Assert::AreEqual(expected_acquisition.segmented(), config.acquisition().segmented(), L"acquisition.segmented", LINE_INFO());
            Assert::AreEqual(std::size_t(0), config.beep_on_apply(), L"beep_on_apply", LINE_INFO());
            Assert::IsFalse(config.beep_on_error(), L"beep_on_error", LINE_INFO());
            Assert::IsFalse(config.beep_on_trigger(), L"beep_on_trigger", LINE_INFO());
            Assert::AreEqual(visa_instrument::timeout_type(0), config.timeout(), L"timeout", LINE_INFO());
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

        TEST_METHOD(test_config_copy_ctor) {
            const auto expected_acquisition = oscilloscope_acquisition()
                .count(42)
                .points(1024)
                .segmented(true);
            const auto expected_trigger = oscilloscope_edge_trigger("EXT")
                .coupling(oscilloscope_trigger_coupling::low_frequency_reject)
                .level(42.0f);
            const oscilloscope_quantity expected_time_range(42.42f, "ms");
            const visa_instrument::timeout_type expected_timeout = 17;
            const std::size_t expected_beeps = 8;

            rtx_instrument_configuration config(expected_time_range, expected_acquisition, expected_trigger, 17);
            config.beep_on_apply(expected_beeps).beep_on_error(true).beep_on_trigger(true);
            config.channel(oscilloscope_channel(1).label("bla"));
            config.channel(oscilloscope_channel(3).label("blubb"));
            Assert::AreEqual(expected_acquisition.automatic_points(), config.acquisition().automatic_points(), L"Initialise acquisition.automatic_points", LINE_INFO());
            Assert::AreEqual(expected_acquisition.count(), config.acquisition().count(), L"Initialise acquisition.count", LINE_INFO());
            Assert::AreEqual(expected_acquisition.points(), config.acquisition().points(), L"Initialise acquisition.points", LINE_INFO());
            Assert::AreEqual(expected_acquisition.segmented(), config.acquisition().segmented(), L"Initialise acquisition.segmented", LINE_INFO());
            Assert::AreEqual(expected_beeps, config.beep_on_apply(), L"Initialise beep_on_apply", LINE_INFO());
            Assert::IsTrue(config.beep_on_error(), L"Initialise beep_on_error", LINE_INFO());
            Assert::IsTrue(config.beep_on_trigger(), L"Initialise beep_on_trigger", LINE_INFO());
            Assert::AreEqual(std::size_t(2), config.channels(), L"Initialise channels", LINE_INFO());
            Assert::AreEqual(expected_timeout, config.timeout(), L"Initialise timeout", LINE_INFO());
            Assert::AreEqual(expected_time_range.value(), config.time_range().value(), L"Initialise time_range.value", LINE_INFO());
            Assert::AreEqual(expected_time_range.unit(), config.time_range().unit(), L"Initialise time_range.unit", LINE_INFO());
            Assert::AreEqual(int(expected_trigger.coupling()), int(config.trigger().coupling()), L"Initialise trigger.coupling", LINE_INFO());
            Assert::AreEqual(expected_trigger.hold_off(), config.trigger().hold_off(), L"Initialise trigger.hold_off", LINE_INFO());
            Assert::AreEqual(int(expected_trigger.hysteresis()), int(config.trigger().hysteresis()), L"Initialise trigger.hysteresis", LINE_INFO());
            Assert::AreEqual(int(expected_trigger.input()), int(config.trigger().input()), L"Initialise trigger.input", LINE_INFO());
            Assert::AreEqual(expected_trigger.level().value(), config.trigger().level().value(), L"Initialise trigger.level.value", LINE_INFO());
            Assert::AreEqual(expected_trigger.level().unit(), config.trigger().level().unit(), L"Initialise trigger.level.unit", LINE_INFO());
            Assert::AreEqual(int(expected_trigger.mode()), int(config.trigger().mode()), L"Initialise trigger.mode", LINE_INFO());
            Assert::AreEqual(expected_trigger.source(), config.trigger().source(), L"Initialise trigger.source", LINE_INFO());
            Assert::AreEqual(int(expected_trigger.slope()), int(config.trigger().slope()), L"Initialise trigger.slope", LINE_INFO());
            Assert::AreEqual(expected_trigger.type(), config.trigger().type(), L"Initialise trigger.type", LINE_INFO());

            rtx_instrument_configuration copy(config);
            Assert::AreEqual(config.acquisition().automatic_points(), copy.acquisition().automatic_points(), L"acquisition.automatic_points", LINE_INFO());
            Assert::AreEqual(config.acquisition().count(), copy.acquisition().count(), L"acquisition.count", LINE_INFO());
            Assert::AreEqual(config.acquisition().points(), copy.acquisition().points(), L"acquisition.points", LINE_INFO());
            Assert::AreEqual(config.acquisition().segmented(), copy.acquisition().segmented(), L"acquisition.segmented", LINE_INFO());
            Assert::AreEqual(config.beep_on_apply(), copy.beep_on_apply(), L"beep_on_apply", LINE_INFO());
            Assert::AreEqual(config.beep_on_error(), copy.beep_on_error(), L"beep_on_error", LINE_INFO());
            Assert::AreEqual(config.beep_on_trigger(),copy.beep_on_trigger(), L"beep_on_trigger", LINE_INFO());
            Assert::AreEqual(config.channels(), copy.channels(), L"channels", LINE_INFO());
            Assert::AreEqual(config.timeout(), copy.timeout(), L"timeout", LINE_INFO());
            Assert::AreEqual(config.time_range().value(), copy.time_range().value(), L"time_range.value", LINE_INFO());
            Assert::AreEqual(config.time_range().unit(), copy.time_range().unit(), L"time_range.unit", LINE_INFO());
            Assert::AreEqual(int(config.trigger().coupling()), int(copy.trigger().coupling()), L"trigger.coupling", LINE_INFO());
            Assert::AreEqual(config.trigger().hold_off(), copy.trigger().hold_off(), L"trigger.hold_off", LINE_INFO());
            Assert::AreEqual(int(config.trigger().hysteresis()), int(copy.trigger().hysteresis()), L"trigger.hysteresis", LINE_INFO());
            Assert::AreEqual(int(config.trigger().input()), int(copy.trigger().input()), L"trigger.input", LINE_INFO());
            Assert::AreEqual(config.trigger().level().value(), copy.trigger().level().value(), L"trigger.level.value", LINE_INFO());
            Assert::AreEqual(config.trigger().level().unit(), copy.trigger().level().unit(), "trigger.level.unit", LINE_INFO());
            Assert::AreEqual(int(config.trigger().mode()), int(copy.trigger().mode()), L"trigger.mode", LINE_INFO());
            Assert::AreEqual(config.trigger().source(), copy.trigger().source(), L"trigger.source", LINE_INFO());
            Assert::AreEqual(int(config.trigger().slope()), int(copy.trigger().slope()), L"trigger.slope", LINE_INFO());
            Assert::AreEqual(config.trigger().type(), copy.trigger().type(), L"trigger.type", LINE_INFO());

            std::vector<oscilloscope_channel> expected_channels(config.channels());
            config.channels(expected_channels.data(), expected_channels.size());
            std::vector<oscilloscope_channel> actual_channels(copy.channels());
            config.channels(actual_channels.data(), actual_channels.size());

            Assert::AreEqual(expected_channels.size(), actual_channels.size(), L"# of channels matches", LINE_INFO());
            for (std::size_t i = 0; i < expected_channels.size(); ++i) {
                Assert::AreEqual(expected_channels[i].attenuation().value(), actual_channels[i].attenuation().value(), L"attenuation.value", LINE_INFO());
                Assert::AreEqual(expected_channels[i].attenuation().unit(), actual_channels[i].attenuation().unit(), L"attenuation.unit", LINE_INFO());
                Assert::AreEqual(int(expected_channels[i].bandwidth()), int(actual_channels[i].bandwidth()), L"bandwidth", LINE_INFO());
                Assert::AreEqual(expected_channels[i].channel(), actual_channels[i].channel(), L"channel", LINE_INFO());
                Assert::AreEqual(int(expected_channels[i].coupling()), int(actual_channels[i].coupling()), L"coupling", LINE_INFO());
                Assert::AreEqual(int(expected_channels[i].decimation_mode()), int(actual_channels[i].decimation_mode()), L"decimation_mode", LINE_INFO());
                Assert::AreEqual(expected_channels[i].label().text(), actual_channels[i].label().text(), L"attenuation.text", LINE_INFO());
                Assert::AreEqual(expected_channels[i].label().visible(), actual_channels[i].label().visible(), L"attenuation.visible", LINE_INFO());
                Assert::AreEqual(expected_channels[i].offset().value(), actual_channels[i].offset().value(), L"offset.value", LINE_INFO());
                Assert::AreEqual(expected_channels[i].offset().unit(), actual_channels[i].offset().unit(), L"offset.unit", LINE_INFO());
                Assert::AreEqual(int(expected_channels[i].polarity()), int(actual_channels[i].polarity()), L"polarity", LINE_INFO());
                Assert::AreEqual(expected_channels[i].range().value(), actual_channels[i].range().value(), L"range.value", LINE_INFO());
                Assert::AreEqual(expected_channels[i].range().unit(), actual_channels[i].range().unit(), L"range.unit", LINE_INFO());
                Assert::AreEqual(expected_channels[i].skew().value(), actual_channels[i].skew().value(), L"skew.value", LINE_INFO());
                Assert::AreEqual(expected_channels[i].skew().unit(), actual_channels[i].skew().unit(), L"skew.unit", LINE_INFO());
                Assert::AreEqual(expected_channels[i].state(), actual_channels[i].state(), L"state", LINE_INFO());
                Assert::AreEqual(expected_channels[i].zero_offset().value(), actual_channels[i].zero_offset().value(), L"zero_offset.value", LINE_INFO());
                Assert::AreEqual(expected_channels[i].zero_offset().unit(), actual_channels[i].zero_offset().unit(), L"zero_offset.unit", LINE_INFO());
            }
        }

        TEST_METHOD(test_config_assign) {
            const auto expected_acquisition = oscilloscope_acquisition()
                .count(42)
                .points(1024)
                .segmented(true);
            const auto expected_trigger = oscilloscope_edge_trigger("EXT")
                .coupling(oscilloscope_trigger_coupling::low_frequency_reject)
                .level(42.0f);
            const oscilloscope_quantity expected_time_range(42.42f, "ms");
            const visa_instrument::timeout_type expected_timeout = 17;
            const std::size_t expected_beeps = 8;

            rtx_instrument_configuration config(expected_time_range, expected_acquisition, expected_trigger, 17);
            config.beep_on_apply(expected_beeps).beep_on_error(true).beep_on_trigger(true);
            config.channel(oscilloscope_channel(1).label("bla"));
            config.channel(oscilloscope_channel(3).label("blubb"));

            rtx_instrument_configuration copy;
            copy = copy.as_slave();

            copy = config;
            Assert::AreEqual(config.acquisition().automatic_points(), copy.acquisition().automatic_points(), L"acquisition.automatic_points", LINE_INFO());
            Assert::AreEqual(config.acquisition().count(), copy.acquisition().count(), L"acquisition.count", LINE_INFO());
            Assert::AreEqual(config.acquisition().points(), copy.acquisition().points(), L"acquisition.points", LINE_INFO());
            Assert::AreEqual(config.acquisition().segmented(), copy.acquisition().segmented(), L"acquisition.segmented", LINE_INFO());
            Assert::AreEqual(config.beep_on_apply(), copy.beep_on_apply(), L"beep_on_apply", LINE_INFO());
            Assert::AreEqual(config.beep_on_error(), copy.beep_on_error(), L"beep_on_error", LINE_INFO());
            Assert::AreEqual(config.beep_on_trigger(), copy.beep_on_trigger(), L"beep_on_trigger", LINE_INFO());
            Assert::AreEqual(config.channels(), copy.channels(), L"channels", LINE_INFO());
            Assert::AreEqual(config.timeout(), copy.timeout(), L"timeout", LINE_INFO());
            Assert::AreEqual(config.time_range().value(), copy.time_range().value(), L"time_range.value", LINE_INFO());
            Assert::AreEqual(config.time_range().unit(), copy.time_range().unit(), L"time_range.unit", LINE_INFO());
            Assert::AreEqual(int(config.trigger().coupling()), int(copy.trigger().coupling()), L"trigger.coupling", LINE_INFO());
            Assert::AreEqual(config.trigger().hold_off(), copy.trigger().hold_off(), L"trigger.hold_off", LINE_INFO());
            Assert::AreEqual(int(config.trigger().hysteresis()), int(copy.trigger().hysteresis()), L"trigger.hysteresis", LINE_INFO());
            Assert::AreEqual(int(config.trigger().input()), int(copy.trigger().input()), L"trigger.input", LINE_INFO());
            Assert::AreEqual(config.trigger().level().value(), copy.trigger().level().value(), L"trigger.level.value", LINE_INFO());
            Assert::AreEqual(config.trigger().level().unit(), copy.trigger().level().unit(), "trigger.level.unit", LINE_INFO());
            Assert::AreEqual(int(config.trigger().mode()), int(copy.trigger().mode()), L"trigger.mode", LINE_INFO());
            Assert::AreEqual(config.trigger().source(), copy.trigger().source(), L"trigger.source", LINE_INFO());
            Assert::AreEqual(int(config.trigger().slope()), int(copy.trigger().slope()), L"trigger.slope", LINE_INFO());
            Assert::AreEqual(config.trigger().type(), copy.trigger().type(), L"trigger.type", LINE_INFO());

            std::vector<oscilloscope_channel> expected_channels(config.channels());
            config.channels(expected_channels.data(), expected_channels.size());
            std::vector<oscilloscope_channel> actual_channels(copy.channels());
            config.channels(actual_channels.data(), actual_channels.size());

            Assert::AreEqual(expected_channels.size(), actual_channels.size(), L"# of channels matches", LINE_INFO());
            for (std::size_t i = 0; i < expected_channels.size(); ++i) {
                Assert::AreEqual(expected_channels[i].attenuation().value(), actual_channels[i].attenuation().value(), L"attenuation.value", LINE_INFO());
                Assert::AreEqual(expected_channels[i].attenuation().unit(), actual_channels[i].attenuation().unit(), L"attenuation.unit", LINE_INFO());
                Assert::AreEqual(int(expected_channels[i].bandwidth()), int(actual_channels[i].bandwidth()), L"bandwidth", LINE_INFO());
                Assert::AreEqual(expected_channels[i].channel(), actual_channels[i].channel(), L"channel", LINE_INFO());
                Assert::AreEqual(int(expected_channels[i].coupling()), int(actual_channels[i].coupling()), L"coupling", LINE_INFO());
                Assert::AreEqual(int(expected_channels[i].decimation_mode()), int(actual_channels[i].decimation_mode()), L"decimation_mode", LINE_INFO());
                Assert::AreEqual(expected_channels[i].label().text(), actual_channels[i].label().text(), L"attenuation.text", LINE_INFO());
                Assert::AreEqual(expected_channels[i].label().visible(), actual_channels[i].label().visible(), L"attenuation.visible", LINE_INFO());
                Assert::AreEqual(expected_channels[i].offset().value(), actual_channels[i].offset().value(), L"offset.value", LINE_INFO());
                Assert::AreEqual(expected_channels[i].offset().unit(), actual_channels[i].offset().unit(), L"offset.unit", LINE_INFO());
                Assert::AreEqual(int(expected_channels[i].polarity()), int(actual_channels[i].polarity()), L"polarity", LINE_INFO());
                Assert::AreEqual(expected_channels[i].range().value(), actual_channels[i].range().value(), L"range.value", LINE_INFO());
                Assert::AreEqual(expected_channels[i].range().unit(), actual_channels[i].range().unit(), L"range.unit", LINE_INFO());
                Assert::AreEqual(expected_channels[i].skew().value(), actual_channels[i].skew().value(), L"skew.value", LINE_INFO());
                Assert::AreEqual(expected_channels[i].skew().unit(), actual_channels[i].skew().unit(), L"skew.unit", LINE_INFO());
                Assert::AreEqual(expected_channels[i].state(), actual_channels[i].state(), L"state", LINE_INFO());
                Assert::AreEqual(expected_channels[i].zero_offset().value(), actual_channels[i].zero_offset().value(), L"zero_offset.value", LINE_INFO());
                Assert::AreEqual(expected_channels[i].zero_offset().unit(), actual_channels[i].zero_offset().unit(), L"zero_offset.unit", LINE_INFO());
            }
        }


        TEST_METHOD(test_config_move_ctor) {
            const auto expected_acquisition = oscilloscope_acquisition()
                .count(42)
                .points(1024)
                .segmented(true);
            const auto expected_trigger = oscilloscope_edge_trigger("EXT")
                .coupling(oscilloscope_trigger_coupling::low_frequency_reject)
                .level(42.0f);
            const oscilloscope_quantity expected_time_range(42.42f, "ms");
            const visa_instrument::timeout_type expected_timeout = 17;
            const std::size_t expected_beeps = 8;

            rtx_instrument_configuration config(expected_time_range, expected_acquisition, expected_trigger, 17);
            config.beep_on_apply(expected_beeps).beep_on_error(true).beep_on_trigger(true);
            config.channel(oscilloscope_channel(1).label("bla"));
            config.channel(oscilloscope_channel(3).label("blubb"));
            Assert::AreEqual(expected_acquisition.automatic_points(), config.acquisition().automatic_points(), L"Initialise acquisition.automatic_points", LINE_INFO());
            Assert::AreEqual(expected_acquisition.count(), config.acquisition().count(), L"Initialise acquisition.count", LINE_INFO());
            Assert::AreEqual(expected_acquisition.points(), config.acquisition().points(), L"Initialise acquisition.points", LINE_INFO());
            Assert::AreEqual(expected_acquisition.segmented(), config.acquisition().segmented(), L"Initialise acquisition.segmented", LINE_INFO());
            Assert::AreEqual(expected_beeps, config.beep_on_apply(), L"Initialise beep_on_apply", LINE_INFO());
            Assert::IsTrue(config.beep_on_error(), L"Initialise beep_on_error", LINE_INFO());
            Assert::IsTrue(config.beep_on_trigger(), L"Initialise beep_on_trigger", LINE_INFO());
            Assert::AreEqual(std::size_t(2), config.channels(), L"Initialise channels", LINE_INFO());
            Assert::AreEqual(expected_timeout, config.timeout(), L"Initialise timeout", LINE_INFO());
            Assert::AreEqual(expected_time_range.value(), config.time_range().value(), L"Initialise time_range.value", LINE_INFO());
            Assert::AreEqual(expected_time_range.unit(), config.time_range().unit(), L"Initialise time_range.unit", LINE_INFO());
            Assert::AreEqual(int(expected_trigger.coupling()), int(config.trigger().coupling()), L"Initialise trigger.coupling", LINE_INFO());
            Assert::AreEqual(expected_trigger.hold_off(), config.trigger().hold_off(), L"Initialise trigger.hold_off", LINE_INFO());
            Assert::AreEqual(int(expected_trigger.hysteresis()), int(config.trigger().hysteresis()), L"Initialise trigger.hysteresis", LINE_INFO());
            Assert::AreEqual(int(expected_trigger.input()), int(config.trigger().input()), L"Initialise trigger.input", LINE_INFO());
            Assert::AreEqual(expected_trigger.level().value(), config.trigger().level().value(), L"Initialise trigger.level.value", LINE_INFO());
            Assert::AreEqual(expected_trigger.level().unit(), config.trigger().level().unit(), L"Initialise trigger.level.unit", LINE_INFO());
            Assert::AreEqual(int(expected_trigger.mode()), int(config.trigger().mode()), L"Initialise trigger.mode", LINE_INFO());
            Assert::AreEqual(expected_trigger.source(), config.trigger().source(), L"Initialise trigger.source", LINE_INFO());
            Assert::AreEqual(int(expected_trigger.slope()), int(config.trigger().slope()), L"Initialise trigger.slope", LINE_INFO());
            Assert::AreEqual(expected_trigger.type(), config.trigger().type(), L"Initialise trigger.type", LINE_INFO());

            rtx_instrument_configuration copy(std::move(config));
            Assert::AreEqual(expected_acquisition.automatic_points(), copy.acquisition().automatic_points(), L"acquisition.automatic_points", LINE_INFO());
            Assert::AreEqual(expected_acquisition.count(), copy.acquisition().count(), L"acquisition.count", LINE_INFO());
            Assert::AreEqual(expected_acquisition.points(), copy.acquisition().points(), L"acquisition.points", LINE_INFO());
            Assert::AreEqual(expected_acquisition.segmented(), copy.acquisition().segmented(), L"acquisition.segmented", LINE_INFO());
            Assert::AreEqual(expected_beeps, copy.beep_on_apply(), L"beep_on_apply", LINE_INFO());
            Assert::IsTrue(copy.beep_on_error(), L"beep_on_error", LINE_INFO());
            Assert::AreEqual(config.beep_on_trigger(), copy.beep_on_trigger(), L"beep_on_trigger", LINE_INFO());
            Assert::AreEqual(std::size_t(2), copy.channels(), L"channels", LINE_INFO());
            Assert::AreEqual(std::size_t(0), config.channels(), L"No channels in source", LINE_INFO());
            Assert::AreEqual(expected_timeout, copy.timeout(), L"timeout", LINE_INFO());
            Assert::AreEqual(expected_time_range.value(), copy.time_range().value(), L"time_range.value", LINE_INFO());
            Assert::AreEqual(expected_time_range.unit(), copy.time_range().unit(), L"time_range.unit", LINE_INFO());
            Assert::AreEqual(int(expected_trigger.coupling()), int(copy.trigger().coupling()), L"Initialise trigger.coupling", LINE_INFO());
            Assert::AreEqual(expected_trigger.hold_off(), copy.trigger().hold_off(), L"Initialise trigger.hold_off", LINE_INFO());
            Assert::AreEqual(int(expected_trigger.hysteresis()), int(copy.trigger().hysteresis()), L"Initialise trigger.hysteresis", LINE_INFO());
            Assert::AreEqual(int(expected_trigger.input()), int(copy.trigger().input()), L"Initialise trigger.input", LINE_INFO());
            Assert::AreEqual(expected_trigger.level().value(), copy.trigger().level().value(), L"Initialise trigger.level.value", LINE_INFO());
            Assert::AreEqual(expected_trigger.level().unit(), copy.trigger().level().unit(), L"Initialise trigger.level.unit", LINE_INFO());
            Assert::AreEqual(int(expected_trigger.mode()), int(copy.trigger().mode()), L"Initialise trigger.mode", LINE_INFO());
            Assert::AreEqual(expected_trigger.source(), copy.trigger().source(), L"Initialise trigger.source", LINE_INFO());
            Assert::AreEqual(int(expected_trigger.slope()), int(copy.trigger().slope()), L"Initialise trigger.slope", LINE_INFO());
            Assert::AreEqual(expected_trigger.type(), copy.trigger().type(), L"Initialise trigger.type", LINE_INFO());
        }

        TEST_METHOD(test_config_move_assign) {
            const auto expected_acquisition = oscilloscope_acquisition()
                .count(42)
                .points(1024)
                .segmented(true);
            const auto expected_trigger = oscilloscope_edge_trigger("EXT")
                .coupling(oscilloscope_trigger_coupling::low_frequency_reject)
                .level(42.0f);
            const oscilloscope_quantity expected_time_range(42.42f, "ms");
            const visa_instrument::timeout_type expected_timeout = 17;
            const std::size_t expected_beeps = 8;

            rtx_instrument_configuration config(expected_time_range, expected_acquisition, expected_trigger, 17);
            config.beep_on_apply(expected_beeps).beep_on_error(true).beep_on_trigger(true);
            config.channel(oscilloscope_channel(1).label("bla"));
            config.channel(oscilloscope_channel(3).label("blubb"));

            rtx_instrument_configuration copy;
            copy = copy.as_slave();

            copy = std::move(config);
            Assert::AreEqual(expected_acquisition.automatic_points(), copy.acquisition().automatic_points(), L"acquisition.automatic_points", LINE_INFO());
            Assert::AreEqual(expected_acquisition.count(), copy.acquisition().count(), L"acquisition.count", LINE_INFO());
            Assert::AreEqual(expected_acquisition.points(), copy.acquisition().points(), L"acquisition.points", LINE_INFO());
            Assert::AreEqual(expected_acquisition.segmented(), copy.acquisition().segmented(), L"acquisition.segmented", LINE_INFO());
            Assert::AreEqual(expected_beeps, copy.beep_on_apply(), L"beep_on_apply", LINE_INFO());
            Assert::IsTrue(copy.beep_on_error(), L"beep_on_error", LINE_INFO());
            Assert::AreEqual(config.beep_on_trigger(), copy.beep_on_trigger(), L"beep_on_trigger", LINE_INFO());
            Assert::AreEqual(std::size_t(2), copy.channels(), L"channels", LINE_INFO());
            Assert::AreEqual(std::size_t(0), config.channels(), L"No channels in source", LINE_INFO());
            Assert::AreEqual(expected_timeout, copy.timeout(), L"timeout", LINE_INFO());
            Assert::AreEqual(expected_time_range.value(), copy.time_range().value(), L"time_range.value", LINE_INFO());
            Assert::AreEqual(expected_time_range.unit(), copy.time_range().unit(), L"time_range.unit", LINE_INFO());
            Assert::AreEqual(int(expected_trigger.coupling()), int(copy.trigger().coupling()), L"Initialise trigger.coupling", LINE_INFO());
            Assert::AreEqual(expected_trigger.hold_off(), copy.trigger().hold_off(), L"Initialise trigger.hold_off", LINE_INFO());
            Assert::AreEqual(int(expected_trigger.hysteresis()), int(copy.trigger().hysteresis()), L"Initialise trigger.hysteresis", LINE_INFO());
            Assert::AreEqual(int(expected_trigger.input()), int(copy.trigger().input()), L"Initialise trigger.input", LINE_INFO());
            Assert::AreEqual(expected_trigger.level().value(), copy.trigger().level().value(), L"Initialise trigger.level.value", LINE_INFO());
            Assert::AreEqual(expected_trigger.level().unit(), copy.trigger().level().unit(), L"Initialise trigger.level.unit", LINE_INFO());
            Assert::AreEqual(int(expected_trigger.mode()), int(copy.trigger().mode()), L"Initialise trigger.mode", LINE_INFO());
            Assert::AreEqual(expected_trigger.source(), copy.trigger().source(), L"Initialise trigger.source", LINE_INFO());
            Assert::AreEqual(int(expected_trigger.slope()), int(copy.trigger().slope()), L"Initialise trigger.slope", LINE_INFO());
            Assert::AreEqual(expected_trigger.type(), copy.trigger().type(), L"Initialise trigger.type", LINE_INFO());
        }

        TEST_METHOD(test_config_channel) {
            rtx_instrument_configuration config;

            config.channel(oscilloscope_channel(1).range(17.0f));
            Assert::AreEqual(std::size_t(1), config.channels(), L"Channel added", LINE_INFO());

            config.channel(oscilloscope_channel(1).range(42.0f));
            Assert::AreEqual(std::size_t(1), config.channels(), L"Channel overwritten", LINE_INFO());

            config.channel(oscilloscope_channel(2).range(43.0f));
            Assert::AreEqual(std::size_t(2), config.channels(), L"Channel added", LINE_INFO());

            {
                std::vector<oscilloscope_channel> channels(config.channels());
                config.channels(channels.data(), channels.size());

                Assert::AreEqual(std::uint32_t(1), channels[0].channel(), L"Channel #1", LINE_INFO());
                Assert::AreEqual(42.0f, channels[0].range().value(), L"range.value #1", LINE_INFO());
                Assert::AreEqual(std::uint32_t(2), channels[1].channel(), L"Channel #2", LINE_INFO());
                Assert::AreEqual(43.0f, channels[1].range().value(), L"range.value #2", LINE_INFO());
            }

            config.ignore_channel(10);
            Assert::AreEqual(std::size_t(2), config.channels(), L"Erase unknown channel", LINE_INFO());

            config.ignore_channel(1);
            Assert::AreEqual(std::size_t(1), config.channels(), L"Channel removed", LINE_INFO());

            {
                std::vector<oscilloscope_channel> channels(config.channels());
                config.channels(channels.data(), channels.size());

                Assert::AreEqual(std::uint32_t(2), channels[0].channel(), L"Channel #", LINE_INFO());
                Assert::AreEqual(43.0f, channels[0].range().value(), L"range.value", LINE_INFO());
            }

            config.ignore_channel(2);
            Assert::AreEqual(std::size_t(0), config.channels(), L"Channel removed", LINE_INFO());

            config.channel(oscilloscope_channel(1));
            config.channel(oscilloscope_channel(2));
            config.channel(oscilloscope_channel(3));
            config.channel(oscilloscope_channel(4));
            Assert::AreEqual(std::size_t(4), config.channels(), L"Channels added", LINE_INFO());

            config.ignore_channel(4);
            Assert::AreEqual(std::size_t(3), config.channels(), L"Channel removed", LINE_INFO());

            {
                std::vector<oscilloscope_channel> channels(config.channels());
                config.channels(channels.data(), channels.size());

                Assert::AreEqual(std::uint32_t(1), channels[0].channel(), L"Channel #1", LINE_INFO());
                Assert::AreEqual(std::uint32_t(2), channels[1].channel(), L"Channel #2", LINE_INFO());
                Assert::AreEqual(std::uint32_t(3), channels[2].channel(), L"Channel #3", LINE_INFO());
            }

            config.ignore_channel(2);
            Assert::AreEqual(std::size_t(2), config.channels(), L"Channel removed", LINE_INFO());

            {
                std::vector<oscilloscope_channel> channels(config.channels());
                config.channels(channels.data(), channels.size());

                Assert::AreEqual(std::uint32_t(1), channels[0].channel(), L"Channel #1", LINE_INFO());
                Assert::AreEqual(std::uint32_t(3), channels[1].channel(), L"Channel #3", LINE_INFO());
            }
        }

        TEST_METHOD(test_config_save_load) {
            const auto expected_config = rtx_instrument_configuration(
                oscilloscope_quantity(42.42f, "ms"),
                oscilloscope_acquisition().count(42).points(1024).segmented(true),
                oscilloscope_edge_trigger("CH2").coupling(oscilloscope_trigger_coupling::low_frequency_reject).level(42.0f),
                17)
                .beep_on_apply(8)
                .beep_on_error(true)
                .beep_on_trigger(true)
                .channel(oscilloscope_channel(1).label("bla"))
                .channel(oscilloscope_channel(3).label("blubb"));
            rtx_instrument_configuration::save(expected_config, L"test.json");

            auto actual_config = rtx_instrument_configuration::load(L"test.json");
            Assert::AreEqual(expected_config.acquisition().automatic_points(), actual_config.acquisition().automatic_points(), L"acquisition.automatic_points", LINE_INFO());
            Assert::AreEqual(expected_config.acquisition().count(), actual_config.acquisition().count(), L"acquisition.count", LINE_INFO());
            Assert::AreEqual(expected_config.acquisition().points(), actual_config.acquisition().points(), L"acquisition.points", LINE_INFO());
            Assert::AreEqual(expected_config.acquisition().segmented(), actual_config.acquisition().segmented(), L"acquisition.segmented", LINE_INFO());
            Assert::AreEqual(expected_config.beep_on_apply(), actual_config.beep_on_apply(), L"beep_on_apply", LINE_INFO());
            Assert::AreEqual(expected_config.beep_on_error(), actual_config.beep_on_error(), L"beep_on_error", LINE_INFO());
            Assert::AreEqual(expected_config.beep_on_trigger(), actual_config.beep_on_trigger(), L"beep_on_trigger", LINE_INFO());
            Assert::AreEqual(expected_config.channels(), actual_config.channels(), L"channels", LINE_INFO());
            Assert::AreEqual(expected_config.timeout(), actual_config.timeout(), L"timeout", LINE_INFO());
            Assert::AreEqual(expected_config.time_range().value(), actual_config.time_range().value(), L"time_range.value", LINE_INFO());
            Assert::AreEqual(expected_config.time_range().unit(), actual_config.time_range().unit(), L"time_range.unit", LINE_INFO());
            Assert::AreEqual(int(expected_config.trigger().coupling()), int(actual_config.trigger().coupling()), L"trigger.coupling", LINE_INFO());
            Assert::AreEqual("", actual_config.trigger().hold_off(), L"trigger.hold_off", LINE_INFO());
            Assert::AreEqual(int(expected_config.trigger().hysteresis()), int(actual_config.trigger().hysteresis()), L"trigger.hysteresis", LINE_INFO());
            Assert::AreEqual(int(expected_config.trigger().input()), int(actual_config.trigger().input()), L"trigger.input", LINE_INFO());
            Assert::AreEqual(expected_config.trigger().level().value(), actual_config.trigger().level().value(), L"trigger.level.value", LINE_INFO());
            Assert::AreEqual(expected_config.trigger().level().unit(), actual_config.trigger().level().unit(), "trigger.level.unit", LINE_INFO());
            Assert::AreEqual(int(expected_config.trigger().mode()), int(actual_config.trigger().mode()), L"trigger.mode", LINE_INFO());
            Assert::AreEqual(expected_config.trigger().source(), actual_config.trigger().source(), L"trigger.source", LINE_INFO());
            Assert::AreEqual(int(expected_config.trigger().slope()), int(actual_config.trigger().slope()), L"trigger.slope", LINE_INFO());
            Assert::AreEqual(expected_config.trigger().type(), actual_config.trigger().type(), L"trigger.type", LINE_INFO());
        }

        TEST_METHOD(test_config_save_load_array) {
            const std::vector<rtx_instrument_configuration> expected_configs = {
                rtx_instrument_configuration(
                    oscilloscope_quantity(42.42f, "ms"),
                    oscilloscope_acquisition().count(42).points(1024).segmented(true),
                    oscilloscope_edge_trigger("CH2").coupling(oscilloscope_trigger_coupling::low_frequency_reject).level(42.0f),
                    17)
                .beep_on_apply(8)
                .beep_on_error(true)
                .beep_on_trigger(true)
                .channel(oscilloscope_channel(1).label("bla"))
                .channel(oscilloscope_channel(3).label("blubb")),
                rtx_instrument_configuration(oscilloscope_quantity(42.42f, "s"), 99, 4242)
            };

            rtx_instrument_configuration::save(expected_configs.data(), expected_configs.size(), L"test.json");

            {
                auto actual_config = rtx_instrument_configuration::load(L"test.json");
                Assert::AreEqual(expected_configs[0].acquisition().automatic_points(), actual_config.acquisition().automatic_points(), L"acquisition.automatic_points", LINE_INFO());
                Assert::AreEqual(expected_configs[0].acquisition().count(), actual_config.acquisition().count(), L"acquisition.count", LINE_INFO());
                Assert::AreEqual(expected_configs[0].acquisition().points(), actual_config.acquisition().points(), L"acquisition.points", LINE_INFO());
                Assert::AreEqual(expected_configs[0].acquisition().segmented(), actual_config.acquisition().segmented(), L"acquisition.segmented", LINE_INFO());
                Assert::AreEqual(expected_configs[0].beep_on_apply(), actual_config.beep_on_apply(), L"beep_on_apply", LINE_INFO());
                Assert::AreEqual(expected_configs[0].beep_on_error(), actual_config.beep_on_error(), L"beep_on_error", LINE_INFO());
                Assert::AreEqual(expected_configs[0].beep_on_trigger(), actual_config.beep_on_trigger(), L"beep_on_trigger", LINE_INFO());
                Assert::AreEqual(expected_configs[0].channels(), actual_config.channels(), L"channels", LINE_INFO());
                Assert::AreEqual(expected_configs[0].timeout(), actual_config.timeout(), L"timeout", LINE_INFO());
                Assert::AreEqual(expected_configs[0].time_range().value(), actual_config.time_range().value(), L"time_range.value", LINE_INFO());
                Assert::AreEqual(expected_configs[0].time_range().unit(), actual_config.time_range().unit(), L"time_range.unit", LINE_INFO());
                Assert::AreEqual(int(expected_configs[0].trigger().coupling()), int(actual_config.trigger().coupling()), L"trigger.coupling", LINE_INFO());
                Assert::AreEqual("", actual_config.trigger().hold_off(), L"trigger.hold_off", LINE_INFO());
                Assert::AreEqual(int(expected_configs[0].trigger().hysteresis()), int(actual_config.trigger().hysteresis()), L"trigger.hysteresis", LINE_INFO());
                Assert::AreEqual(int(expected_configs[0].trigger().input()), int(actual_config.trigger().input()), L"trigger.input", LINE_INFO());
                Assert::AreEqual(expected_configs[0].trigger().level().value(), actual_config.trigger().level().value(), L"trigger.level.value", LINE_INFO());
                Assert::AreEqual(expected_configs[0].trigger().level().unit(), actual_config.trigger().level().unit(), "trigger.level.unit", LINE_INFO());
                Assert::AreEqual(int(expected_configs[0].trigger().mode()), int(actual_config.trigger().mode()), L"trigger.mode", LINE_INFO());
                Assert::AreEqual(expected_configs[0].trigger().source(), actual_config.trigger().source(), L"trigger.source", LINE_INFO());
                Assert::AreEqual(int(expected_configs[0].trigger().slope()), int(actual_config.trigger().slope()), L"trigger.slope", LINE_INFO());
                Assert::AreEqual(expected_configs[0].trigger().type(), actual_config.trigger().type(), L"trigger.type", LINE_INFO());
            }

            {
                std::vector<rtx_instrument_configuration> actual_configs(rtx_instrument_configuration::load(nullptr, 0, L"test.json"));
                Assert::AreEqual(expected_configs.size(), actual_configs.size(), L"All configurations found", LINE_INFO());
                rtx_instrument_configuration::load(actual_configs.data(), actual_configs.size(), L"test.json");

                for (std::size_t i = 0; i < actual_configs.size(); ++i) {
                    Assert::AreEqual(expected_configs[i].acquisition().automatic_points(), actual_configs[i].acquisition().automatic_points(), L"acquisition.automatic_points", LINE_INFO());
                    Assert::AreEqual(expected_configs[i].acquisition().count(), actual_configs[i].acquisition().count(), L"acquisition.count", LINE_INFO());
                    Assert::AreEqual(expected_configs[i].acquisition().points(), actual_configs[i].acquisition().points(), L"acquisition.points", LINE_INFO());
                    Assert::AreEqual(expected_configs[i].acquisition().segmented(), actual_configs[i].acquisition().segmented(), L"acquisition.segmented", LINE_INFO());
                    Assert::AreEqual(expected_configs[i].beep_on_apply(), actual_configs[i].beep_on_apply(), L"beep_on_apply", LINE_INFO());
                    Assert::AreEqual(expected_configs[i].beep_on_error(), actual_configs[i].beep_on_error(), L"beep_on_error", LINE_INFO());
                    Assert::AreEqual(expected_configs[i].beep_on_trigger(), actual_configs[i].beep_on_trigger(), L"beep_on_trigger", LINE_INFO());
                    Assert::AreEqual(expected_configs[i].channels(), actual_configs[i].channels(), L"channels", LINE_INFO());
                    Assert::AreEqual(expected_configs[i].timeout(), actual_configs[i].timeout(), L"timeout", LINE_INFO());
                    Assert::AreEqual(expected_configs[i].time_range().value(), actual_configs[i].time_range().value(), L"time_range.value", LINE_INFO());
                    Assert::AreEqual(expected_configs[i].time_range().unit(), actual_configs[i].time_range().unit(), L"time_range.unit", LINE_INFO());
                    Assert::AreEqual(int(expected_configs[i].trigger().coupling()), int(actual_configs[i].trigger().coupling()), L"trigger.coupling", LINE_INFO());
                    Assert::AreEqual("", actual_configs[i].trigger().hold_off(), L"trigger.hold_off", LINE_INFO());
                    Assert::AreEqual(int(expected_configs[i].trigger().hysteresis()), int(actual_configs[i].trigger().hysteresis()), L"trigger.hysteresis", LINE_INFO());
                    Assert::AreEqual(int(expected_configs[i].trigger().input()), int(actual_configs[i].trigger().input()), L"trigger.input", LINE_INFO());
                    Assert::AreEqual(expected_configs[i].trigger().level().value(), actual_configs[i].trigger().level().value(), L"trigger.level.value", LINE_INFO());
                    Assert::AreEqual(expected_configs[i].trigger().level().unit(), actual_configs[i].trigger().level().unit(), "trigger.level.unit", LINE_INFO());
                    Assert::AreEqual(int(expected_configs[i].trigger().mode()), int(actual_configs[i].trigger().mode()), L"trigger.mode", LINE_INFO());
                    Assert::AreEqual(expected_configs[i].trigger().source(), actual_configs[i].trigger().source(), L"trigger.source", LINE_INFO());
                    Assert::AreEqual(int(expected_configs[i].trigger().slope()), int(actual_configs[i].trigger().slope()), L"trigger.slope", LINE_INFO());
                    Assert::AreEqual(expected_configs[i].trigger().type(), actual_configs[i].trigger().type(), L"trigger.type", LINE_INFO());
                }
            }

        }

    };
} /* namespace test */
} /* namespace power_overwhelming */
} /* namespace visus */
