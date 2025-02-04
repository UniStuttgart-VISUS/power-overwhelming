// <copyright file="rtx_serialisation_test.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

PWROWG_TEST_NAMESPACE_BEGIN

TEST_CLASS(rtx_serialisation_test) {

public:

    TEST_METHOD(test_rtx_channel) {
        const auto input = rtx_channel(42)
            .attenuation(rtx_quantity(12.3f, "V"))
            .bandwidth(rtx_channel_bandwidth::limit_to_20_mhz)
            .coupling(rtx_channel_coupling::alternating_current_limit)
            .decimation_mode(rtx_decimation_mode::peak_detect)
            .label(rtx_label("bla"))
            .offset(23.4f)
            .polarity(rtx_channel_polarity::inverted)
            .range(34.5f)
            .skew(45.6f)
            .zero_offset(56.7f);

        const auto json = detail::json_serialise(input);
        const auto output = detail::json_deserialise<rtx_channel>(json);
        Assert::AreEqual(input.attenuation().value(), output.attenuation().value(), L"attenuation.value", LINE_INFO());
        Assert::AreEqual(input.attenuation().unit(), output.attenuation().unit(), L"attenuation.unit", LINE_INFO());
        Assert::AreEqual(int(input.bandwidth()), int(output.bandwidth()), L"bandwidth", LINE_INFO());
        Assert::AreEqual(input.channel(), output.channel(), L"channel", LINE_INFO());
        Assert::AreEqual(int(input.coupling()), int(output.coupling()), L"coupling", LINE_INFO());
        Assert::AreEqual(int(input.decimation_mode()), int(output.decimation_mode()), L"decimation_mode", LINE_INFO());
        Assert::AreEqual(input.label().text(), output.label().text(), L"label.text", LINE_INFO());
        Assert::AreEqual(input.offset().value(), output.offset().value(), L"offset.value", LINE_INFO());
        Assert::AreEqual(input.offset().unit(), output.offset().unit(), L"offset.unit", LINE_INFO());
        Assert::AreEqual(int(input.polarity()), int(output.polarity()), L"polarity", LINE_INFO());
        Assert::AreEqual(input.range().value(), output.range().value(), L"range.value", LINE_INFO());
        Assert::AreEqual(input.range().unit(), output.range().unit(), L"range.unit", LINE_INFO());
        Assert::AreEqual(input.skew().value(), output.skew().value(), L"skew.value", LINE_INFO());
        Assert::AreEqual(input.skew().unit(), output.skew().unit(), L"skew.unit", LINE_INFO());
        Assert::AreEqual(input.zero_offset().value(), output.zero_offset().value(), L"zero_offset.value", LINE_INFO());
        Assert::AreEqual(input.zero_offset().unit(), output.zero_offset().unit(), L"zero_offset.unit", LINE_INFO());
    }

    TEST_METHOD(test_rtx_edge_trigger) {
        const auto input = rtx_trigger::edge("CH3")
            .coupling(rtx_trigger_coupling::low_frequency_reject)
            .hysteresis(rtx_trigger_hysteresis::high)
            .level(3, rtx_quantity(42.0f, "V"))
            .slope(rtx_trigger_slope::both)
            .hold_off("12s")
            .mode(rtx_trigger_mode::normal);

        const auto json = detail::json_serialise(input);
        const auto output = detail::json_deserialise<rtx_trigger>(json);
        Assert::AreEqual(int(input.coupling()), int(output.coupling()), L"coupling", LINE_INFO());
        Assert::AreEqual(input.hold_off(), output.hold_off(), L"hold_off", LINE_INFO());
        Assert::AreEqual(int(input.hysteresis()), int(output.hysteresis()), L"hysteresis", LINE_INFO());
        Assert::AreEqual(int(input.input()), int(output.input()), L"input", LINE_INFO());
        Assert::AreEqual(input.level().value(), output.level().value(), L"level.value", LINE_INFO());
        Assert::AreEqual(input.level().unit(), output.level().unit(), L"level.unit", LINE_INFO());
        Assert::AreEqual(int(input.mode()), int(output.mode()), L"mode", LINE_INFO());
        Assert::AreEqual(int(input.slope()), int(output.slope()), L"slope", LINE_INFO());
        Assert::AreEqual(input.source(), output.source(), L"source", LINE_INFO());
        Assert::AreEqual(input.type(), output.type(), L"type", LINE_INFO());
    }

    TEST_METHOD(test_rtx_label) {
        const rtx_label input("bla", false);
        const auto json = detail::json_serialise(input);
        const auto output = detail::json_deserialise<rtx_label>(json);
        Assert::AreEqual(input.text(), output.text(), L"text", LINE_INFO());
        Assert::AreEqual(input.visible(), output.visible(), L"visible", LINE_INFO());
    }

    TEST_METHOD(test_rtx_quantity) {
        const rtx_quantity input(42.0f, "GeV");
        const auto json = detail::json_serialise(input);
        const auto output = detail::json_deserialise<rtx_quantity>(json);
        Assert::AreEqual(input.value(), output.value(), L"value", LINE_INFO());
        Assert::AreEqual(input.unit(), output.unit(), L"unit", LINE_INFO());
    }

    TEST_METHOD(test_rtx_acquisition) {
        const auto input = rtx_acquisition()
            .count(8)
            .points(42)
            .segmented(true);
        const auto json = detail::json_serialise(input);
        const auto output = detail::json_deserialise<rtx_acquisition>(json);
        Assert::AreEqual(input.automatic_points(), output.automatic_points(), L"automatic_points", LINE_INFO());
        Assert::AreEqual(input.count(), output.count(), L"count", LINE_INFO());
        Assert::AreEqual(input.points(), output.points(), L"points", LINE_INFO());
        Assert::AreEqual(input.segmented(), output.segmented(), L"segmented", LINE_INFO());
    }

    TEST_METHOD(test_rtx_instrument_configuration) {
        const auto acquisition = rtx_acquisition()
            .count(8)
            .points(42)
            .segmented(true);
        const auto trigger = rtx_trigger::edge("CH3")
            .coupling(rtx_trigger_coupling::low_frequency_reject)
            .hysteresis(rtx_trigger_hysteresis::high)
            .level(3, rtx_quantity(42.0f, "V"))
            .slope(rtx_trigger_slope::both)
            .hold_off("12s")
            .mode(rtx_trigger_mode::normal);

        const auto input = rtx_instrument_configuration(rtx_quantity(12.0f, "s"), acquisition, trigger, 899)
            .beep_on_apply(42).beep_on_error(true).beep_on_trigger(true);
        const auto json = detail::json_serialise(input);
        const auto output = detail::json_deserialise<rtx_instrument_configuration>(json);

        Assert::AreEqual(input.acquisition().automatic_points(), output.acquisition().automatic_points(), L"acquisition.automatic_points", LINE_INFO());
        Assert::AreEqual(input.acquisition().count(), output.acquisition().count(), L"acquisition.count", LINE_INFO());
        Assert::AreEqual(input.acquisition().points(), output.acquisition().points(), L"acquisition.points", LINE_INFO());
        Assert::AreEqual(input.acquisition().segmented(), output.acquisition().segmented(), L"acquisition.segmented", LINE_INFO());

        Assert::AreEqual(input.beep_on_apply(), output.beep_on_apply(), L"beep_on_apply", LINE_INFO());
        Assert::AreEqual(input.beep_on_error(), output.beep_on_error(), L"beep_on_error", LINE_INFO());
        Assert::AreEqual(input.beep_on_trigger(), output.beep_on_trigger(), L"beep_on_trigger", LINE_INFO());
        Assert::AreEqual(input.channels(), output.channels(), L"channels", LINE_INFO());
        Assert::AreEqual(input.timeout(), output.timeout(), L"timeout", LINE_INFO());
        Assert::AreEqual(input.time_range().value(), output.time_range().value(), L"time_range.value", LINE_INFO());
        Assert::AreEqual(input.time_range().unit(), output.time_range().unit(), L"time_range.unit", LINE_INFO());

        Assert::AreEqual(int(input.trigger().coupling()), int(output.trigger().coupling()), L"trigger.coupling", LINE_INFO());
        Assert::AreEqual(input.trigger().hold_off(), output.trigger().hold_off(), L"trigger.hold_off", LINE_INFO());
        Assert::AreEqual(int(input.trigger().hysteresis()), int(output.trigger().hysteresis()), L"trigger.hysteresis", LINE_INFO());
        Assert::AreEqual(int(input.trigger().input()), int(output.trigger().input()), L"trigger.input", LINE_INFO());
        Assert::AreEqual(input.trigger().level().value(), output.trigger().level().value(), L"trigger.level.value", LINE_INFO());
        Assert::AreEqual(input.trigger().level().unit(), output.trigger().level().unit(), L"trigger.level.unit", LINE_INFO());
        Assert::AreEqual(int(input.trigger().mode()), int(output.trigger().mode()), L"trigger.mode", LINE_INFO());
        Assert::AreEqual(int(input.trigger().slope()), int(output.trigger().slope()), L"trigger.slope", LINE_INFO());
        Assert::AreEqual(input.trigger().source(), output.trigger().source(), L"trigger.source", LINE_INFO());
        Assert::AreEqual(input.trigger().type(), output.trigger().type(), L"trigger.type", LINE_INFO());
    }

    TEST_METHOD(test_rtx_instrument_config_with_channels) {
        const auto input = rtx_instrument_configuration(12.0f)
            .channel(rtx_channel(1))
            .channel(rtx_channel(2))
            .channel(rtx_channel(4));
        const auto json = detail::json_serialise(input);
        const auto output = detail::json_deserialise<rtx_instrument_configuration>(json);

        std::vector<rtx_channel> expected_channels(input.channels());
        input.channels(expected_channels.data(), expected_channels.size());

        std::vector<rtx_channel> actual_channels(input.channels());
        input.channels(actual_channels.data(), actual_channels.size());

        Assert::AreEqual(expected_channels.size(), actual_channels.size(), L"# of channels", LINE_INFO());
        Assert::AreEqual(expected_channels[0].channel(), actual_channels[0].channel(), L"CH1", LINE_INFO());
        Assert::AreEqual(expected_channels[1].channel(), actual_channels[1].channel(), L"CH2", LINE_INFO());
        Assert::AreEqual(expected_channels[2].channel(), actual_channels[2].channel(), L"CH4", LINE_INFO());
    }

};

PWROWG_TEST_NAMESPACE_END
