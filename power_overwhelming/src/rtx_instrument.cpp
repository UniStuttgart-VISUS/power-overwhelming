// <copyright file="rtx_instrument.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/rtx_instrument.h"

#include "visa_instrument_impl.h"


/*
 * visus::power_overwhelming::rtx_instrument::rtx_id
 */
constexpr const char *
visus::power_overwhelming::rtx_instrument::rtx_id;


/*
 * visus::power_overwhelming::rtx_instrument::rtx_instrument
 */
visus::power_overwhelming::rtx_instrument::rtx_instrument(void)
    : visa_instrument() { }


/*
 * visus::power_overwhelming::rtx_instrument::rtx_instrument
 */
visus::power_overwhelming::rtx_instrument::rtx_instrument(
    _In_z_ const wchar_t *path, _In_ const timeout_type timeout)
    : visa_instrument(path, timeout) { }


/*
 * visus::power_overwhelming::rtx_instrument::rtx_instrument
 */
visus::power_overwhelming::rtx_instrument::rtx_instrument(
    _In_z_ const char *path, _In_ const timeout_type timeout)
    : visa_instrument(path, timeout) { }


/*
 * visus::power_overwhelming::rtx_instrument::channel
 */
visus::power_overwhelming::rtx_instrument&
visus::power_overwhelming::rtx_instrument::channel(
        _In_ const oscilloscope_channel& channel) {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    auto& impl = this->check_not_disposed();

    // Note: Attenuation should be set first, because changing the attenuation
    // will also scale other values like the range.
    impl.format("PROB%d:SET:ATT:UNIT %s\n", channel.channel(),
        channel.attenuation().unit());
    this->throw_on_system_error();
    impl.format("PROB%d:SET:ATT:MAN %f\n", channel.channel(),
        channel.attenuation().value());
    this->throw_on_system_error();

    switch (channel.bandwidth()) {
        case oscilloscope_channel_bandwidth::limit_to_20_mhz:
            impl.format("CHAN%d:BAND B20\n", channel.channel());
            break;

        default:
            impl.format("CHAN%d:BAND FULL\n", channel.channel());
            break;
    }
    this->throw_on_system_error();

    switch (channel.coupling()) {
        case oscilloscope_channel_coupling::alternating_current_limit:
            impl.format("CHAN%d:COUP ACL\n", channel.channel());
            break;

        case oscilloscope_channel_coupling::ground:
            impl.format("CHAN%d:COUP GND\n", channel.channel());
            break;

        default:
            impl.format("CHAN%d:COUP DCL\n", channel.channel());
            break;
    }
    this->throw_on_system_error();

    switch (channel.decimation_mode()) {
        case oscilloscope_decimation_mode::high_resolution:
            impl.format("CHAN%d:TYPE HRES\n", channel.channel());
            break;

        case oscilloscope_decimation_mode::peak_detect:
            impl.format("CHAN%d:TYPE PDET\n", channel.channel());
            break;

        default:
            impl.format("CHAN%d:TYPE SAMP\n", channel.channel());
            break;
    }
    this->throw_on_system_error();

    impl.format("CHAN%d:LAB \"%s\"\n", channel.channel(),
        channel.label().text());
    this->throw_on_system_error();
    impl.format("CHAN%d:LAB:STAT %s\n", channel.channel(),
        channel.label().visible() ? "ON" : "OFF");
    this->throw_on_system_error();

    impl.format("CHAN%d:OFFS %f%s\n", channel.channel(),
        channel.offset().value(), channel.offset().unit());
    this->throw_on_system_error();

    switch (channel.polarity()) {
        case oscilloscope_channel_polarity::inverted:
            impl.format("CHAN%d:POL INV\n", channel.channel());
            break;

        default:
            impl.format("CHAN%d:POL NORM\n", channel.channel());
            break;
    }
    this->throw_on_system_error();

    impl.format("CHAN%d:RANG %f%s\n", channel.channel(),
        channel.range().value(), channel.range().unit());
    this->throw_on_system_error();

    impl.format("CHAN%d:SKEW %f%s\n", channel.channel(),
        channel.skew().value(), channel.skew().unit());
    this->throw_on_system_error();

    impl.format("CHAN%d:STAT %s\n", channel.channel(),
        channel.state() ? "ON" : "OFF");
    this->throw_on_system_error();

    impl.format("CHAN%d:ZOFF %f%s\n", channel.channel(),
        channel.zero_offset().value(), channel.zero_offset().unit());
    this->throw_on_system_error();
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */

    return *this;
}


/*
 * visus::power_overwhelming::rtx_instrument::expression
 */
visus::power_overwhelming::rtx_instrument&
visus::power_overwhelming::rtx_instrument::expression(
        _In_ const std::uint32_t channel,
        _In_opt_z_ const wchar_t *expression,
        _In_opt_z_ const wchar_t *unit) {
    auto e = convert_string<char>(expression);
    auto u = convert_string<char>(unit);
    return this->expression(channel,
        (expression != nullptr) ? e.c_str() : nullptr,
        (unit != nullptr) ? u.c_str() : nullptr);
}


/*
 * visus::power_overwhelming::rtx_instrument::expression
 */
visus::power_overwhelming::rtx_instrument&
visus::power_overwhelming::rtx_instrument::expression(
        _In_ const std::uint32_t channel,
        _In_opt_z_ const char *expression,
        _In_opt_z_ const char *unit) {
    auto& impl = this->check_not_disposed();

    if (expression != nullptr) {
        if (unit != nullptr) {
            impl.format("CALC:MATH%u:EXPR:DEF \"%s in %s\"\n",
                channel, expression, unit);
        } else {
            impl.format("CALC:MATH%u:EXPR:DEF \"%s\"\n", channel, expression);
        }

        impl.format("CALC:MATH%u:STAT ON\n", channel);

    } else {
        impl.format("CALC:MATH%u:STAT OFF\n", channel);
    }

    this->throw_on_system_error();
    return *this;
}


/*
 * visus::power_overwhelming::rtx_instrument::reference_position
 */
visus::power_overwhelming::rtx_instrument&
visus::power_overwhelming::rtx_instrument::reference_position(
        _In_ const oscilloscope_reference_point position) {
    auto& impl = this->check_not_disposed();
    impl.format("TIM:REF %f\n", static_cast<float>(position) / 100.0f);

    this->throw_on_system_error();
    return *this;
}


/*
 * visus::power_overwhelming::rtx_instrument::time_range
 */
visus::power_overwhelming::rtx_instrument&
visus::power_overwhelming::rtx_instrument::time_range(
        _In_ const oscilloscope_quantity& scale) {
    auto &impl = this->check_not_disposed();
    impl.format("TIM:RANG %f %s\n", scale.value(), scale.unit());

    this->throw_on_system_error();
    return *this;
}


/*
 * visus::power_overwhelming::rtx_instrument::time_scale
 */
visus::power_overwhelming::rtx_instrument&
visus::power_overwhelming::rtx_instrument::time_scale(
        _In_ const oscilloscope_quantity& scale) {
    auto& impl = this->check_not_disposed();
    impl.format("TIM:SCAL %f %s\n", scale.value(), scale.unit());

    this->throw_on_system_error();
    return *this;
}


/*
 * visus::power_overwhelming::rtx_instrument::trigger
 */
visus::power_overwhelming::rtx_instrument&
visus::power_overwhelming::rtx_instrument::trigger(
        _In_ const oscilloscope_trigger& trigger) {
    auto& impl = this->check_not_disposed();

    // Apply configuration that is valid for all triggers.
    switch (trigger.mode()) {
        case oscilloscope_trigger_mode::automatic:
            impl.format("TRIG:A:MODE AUTO\n");
            break;

        default:
            impl.format("TRIG:A:MODE NORM\n");
            break;
    }
    this->throw_on_system_error();

    impl.format("TRIG:A:SOUR %s\n", trigger.source());
    this->throw_on_system_error();

    impl.format("TRIG:A:TYPE %s\n", trigger.type());
    this->throw_on_system_error();

    if (trigger.hold_off() == nullptr) {
        impl.format("TRIG:A:HOLD:MODE OFF\n");
        this->throw_on_system_error();

    } else {
        impl.format("TRIG:A:HOLD:MODE TIME\n");
        this->throw_on_system_error();

        impl.format("TRIG:A:HOLD:TIME %s\n", trigger.hold_off());
        this->throw_on_system_error();
    }

    // Apply special configuration if the trigger is an edge trigger.
    auto et = dynamic_cast<const oscilloscope_edge_trigger *>(&trigger);
    if (et != nullptr) {
        switch (et->slope()) {
            case oscilloscope_trigger_slope::both:
                impl.format("TRIG:A:EDGE:SLOP EITH\n");
                break;

            case oscilloscope_trigger_slope::rising:
                impl.format("TRIG:A:EDGE:SLOP POS\n");
                break;

            case oscilloscope_trigger_slope::falling:
                impl.format("TRIG:A:EDGE:SLOP NEG\n");
                break;
        }
        this->throw_on_system_error();

        impl.format("TRIG:A:LEV%d:VAL %f %s\n", et->input(),
            et->level().value(), et->level().unit());
        this->throw_on_system_error();

        switch (et->coupling()) {
            case oscilloscope_trigger_coupling::alternating_current:
                impl.format("TRIG:A:EDGE:COUP AC\n");
                break;

            case oscilloscope_trigger_coupling::direct_current:
                impl.format("TRIG:A:EDGE:COUP DC\n");
                break;

            case oscilloscope_trigger_coupling::low_frequency_reject:
                impl.format("TRIG:A:EDGE:COUP LFR\n");
                break;
        }
        this->throw_on_system_error();

#if 0
        // TODO: Only RTA
        switch (et->hysteresis()) {
            case oscilloscope_trigger_hysteresis::automatic:
                impl.printf("TRIG:A:HYST AUTO\n");
                break;

            case oscilloscope_trigger_hysteresis::high:
                impl.printf("TRIG:A:HYST LARGE\n");
                break;

            case oscilloscope_trigger_hysteresis::low:
                impl.printf("TRIG:A:HYST SMAL\n");
                break;

            case oscilloscope_trigger_hysteresis::medium:
                impl.printf("TRIG:A:HYST MED\n");
                break;
        }
        this->throw_on_system_error();
#endif
    }

    return *this;
}


/*
 * visus::power_overwhelming::rtx_instrument::trigger_position
 */
visus::power_overwhelming::rtx_instrument&
visus::power_overwhelming::rtx_instrument::trigger_position(
        _In_ const oscilloscope_quantity& offset) {
    auto& impl = this->check_not_disposed();
    impl.format("TIM:POS %f%s\n", offset.value(), offset.unit());

    this->throw_on_system_error();
    return *this;
}


/*
 * visus::power_overwhelming::rtx_instrument::unit
 */
visus::power_overwhelming::rtx_instrument&
visus::power_overwhelming::rtx_instrument::unit(
        _In_ const std::uint32_t channel,
        _In_z_ const wchar_t *unit) {
    if (unit == nullptr) {
        throw std::invalid_argument("The unit for a probe cannot be null.");
    }

    auto& impl = this->check_not_disposed();
    auto u = convert_string<char>(unit);
    impl.format("PROB%u:SET:ATT:UNIT %s\n", channel, u.c_str());

    this->throw_on_system_error();
    return *this;
}


/*
 * visus::power_overwhelming::rtx_instrument::trigger_position
 */
visus::power_overwhelming::rtx_instrument&
visus::power_overwhelming::rtx_instrument::unit(
        _In_ const std::uint32_t channel,
        _In_z_ const char *unit) {
    if (unit == nullptr) {
        throw std::invalid_argument("The unit for a probe cannot be null.");
    }

    auto& impl = this->check_not_disposed();
    impl.format("PROB%u:SET:ATT:UNIT %s\n", channel, unit);

    this->throw_on_system_error();
    return *this;
}
