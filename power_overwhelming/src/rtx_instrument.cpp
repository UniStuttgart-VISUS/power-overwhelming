// <copyright file="rtx_instrument.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/rtx_instrument.h"

#include "no_visa_error_msg.h"
#include "visa_instrument_impl.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

#if defined(POWER_OVERWHELMING_WITH_VISA)
    /// <summary>
    /// RAAI override of the instrument timeout.
    /// </summary>
    class rtx_timeout_override final {

    public:

        inline rtx_timeout_override(_In_ ViSession session,
                _In_ const visa_instrument::timeout_type timeout) 
                : _session(session), _timeout(0) {
            visa_exception::throw_on_error(visa_library::instance()
                .viGetAttribute(this->_session, VI_ATTR_TMO_VALUE,
                    &this->_timeout));
            visa_exception::throw_on_error(visa_library::instance()
                .viSetAttribute(this->_session, VI_ATTR_TMO_VALUE,
                    timeout));
        }

        rtx_timeout_override(const rtx_timeout_override&) = delete;

        inline ~rtx_timeout_override(void) {
            visa_library::instance().viSetAttribute(this->_session,
                VI_ATTR_TMO_VALUE, this->_timeout);
        }

        rtx_timeout_override& operator =(const rtx_timeout_override&) = delete;

    private:

        ViSession _session;
        visa_instrument::timeout_type _timeout;
    };
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */


/*
 * visus::power_overwhelming::rtx_instrument::create
 */
visus::power_overwhelming::rtx_instrument
visus::power_overwhelming::rtx_instrument::create(_In_z_ const wchar_t *path,
        _In_ void (*on_new)(rtx_instrument &, void *),
        _In_opt_ void *context,
        _In_ const timeout_type timeout) {
    if (on_new == nullptr) {
        throw std::invalid_argument("The callback for new instruments must not "
            "be null.");
    }

    auto is_new = false;
    rtx_instrument retval(is_new, path, timeout);

    if (is_new) {
        on_new(retval, context);
    }

    return retval;
}



/*
 * visus::power_overwhelming::rtx_instrument::create
 */
visus::power_overwhelming::rtx_instrument
visus::power_overwhelming::rtx_instrument::create(_In_z_ const char *path,
        _In_ void (*on_new)(rtx_instrument &, void *),
        _In_opt_ void *context,
        _In_ const timeout_type timeout) {
    if (on_new == nullptr) {
        throw std::invalid_argument("The callback for new instruments must not "
            "be null.");
    }

    auto is_new = false;
    rtx_instrument retval(is_new, path, timeout);

    if (is_new) {
        on_new(retval, context);
    }

    return retval;
}



/*
 * visus::power_overwhelming::rtx_instrument::create_and_reset_new
 */
visus::power_overwhelming::rtx_instrument
visus::power_overwhelming::rtx_instrument::create_and_reset_new(
        _In_z_ const wchar_t *path, _In_ const timeout_type timeout) {
    return rtx_instrument::create(path,
        [](rtx_instrument& i, void *) { i.reset(true, true); },
        nullptr,
        timeout);
}


/*
 * visus::power_overwhelming::rtx_instrument::create_and_reset_new
 */
visus::power_overwhelming::rtx_instrument
visus::power_overwhelming::rtx_instrument::create_and_reset_new(
        _In_z_ const char *path, _In_ const timeout_type timeout) {
    return rtx_instrument::create(path,
        [](rtx_instrument &i, void *) { i.reset(true, true); },
        nullptr,
        timeout);
}


/*
 * visus::power_overwhelming::rtx_instrument::product_id
 */
constexpr const char *
visus::power_overwhelming::rtx_instrument::product_id;


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
 * visus::power_overwhelming::rtx_instrument::rtx_instrument
 */
visus::power_overwhelming::rtx_instrument::rtx_instrument(
    _Out_ bool& is_new_connection, _In_z_ const wchar_t *path,
    _In_ const timeout_type timeout)
    : visa_instrument(is_new_connection, path, timeout) { }


/*
 * visus::power_overwhelming::rtx_instrument::rtx_instrument
 */
visus::power_overwhelming::rtx_instrument::rtx_instrument(
    _Out_ bool& is_new_connection, _In_z_ const char *path,
    _In_ const timeout_type timeout)
    : visa_instrument(is_new_connection, path, timeout) { }


/*
 * visus::power_overwhelming::rtx_sensor::acquisition
 */
visus::power_overwhelming::rtx_instrument&
visus::power_overwhelming::rtx_instrument::acquisition(
        _In_ const oscilloscope_single_acquisition& acquisition,
        _In_ const bool run,
        _In_ const bool wait) {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    auto& impl = this->check_not_disposed();

    if (acquisition.automatic_points()) {
        impl.format("ACQ:POIN:AUT ON\n", acquisition.points());
    } else {
        impl.format("ACQ:POIN:VAL %u\n", acquisition.points());
    }

    impl.format("ACQ:NSIN:COUN %u\n", acquisition.count());

    impl.format("ACQ:SEGM:STAT %s\n", acquisition.segmented() ? "ON" : "OFF");

    if (run) {
        this->acquisition(oscilloscope_acquisition_state::single, wait);
    }
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */

    return *this;
}


/*
 * visus::power_overwhelming::rtx_instrument::acquisition
 */
const visus::power_overwhelming::rtx_instrument&
visus::power_overwhelming::rtx_instrument::acquisition(
        _In_ const oscilloscope_acquisition_state state,
        _In_ const bool wait) const {
    switch (state) {
        case oscilloscope_acquisition_state::run:
            this->write("ACQ:STAT RUN\n");
            break;

        case oscilloscope_acquisition_state::stop:
            if (wait) {
                this->query("ACQ:STAT STOP; *OPC?\n");
            } else {
                this->write("ACQ:STAT STOP\n");
            }
            break;

        case oscilloscope_acquisition_state::single:
            if (wait) {
                this->query("*SING; *OPC?\n");
            } else {
                this->write("SING\n");
            }
            break;

        case oscilloscope_acquisition_state::interrupt:
        default:
            this->write("ACQ:STAT BREAK\n");
            break;
    }

    return *this;
}


#if false
// TODO: disabled, because long queries reproducibly cause an I/O error.
/*
 * visus::power_overwhelming::rtx_instrument::ascii_data
 */
visus::power_overwhelming::blob
visus::power_overwhelming::rtx_instrument::ascii_data(
        _In_ const std::uint32_t channel) {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    auto& impl = this->check_not_disposed();

    impl.write("FORM ASC\n");
    this->check_system_error();

    auto query = detail::format_string("CHAN%u:DATA?\n", channel);
    return this->query(query.c_str());

#else /*defined(POWER_OVERWHELMING_WITH_VISA) */
    throw std::logic_error(detail::no_visa_error_msg);
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
}
#endif


/*
 * visus::power_overwhelming::rtx_instrument::binary_data
 */
visus::power_overwhelming::blob
visus::power_overwhelming::rtx_instrument::binary_data(
        _In_ const std::uint32_t channel) const {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    auto& impl = this->check_not_disposed();

    impl.write("FORM REAL,32\n");
    impl.write("FORM:BORD LSBF\n");
    impl.check_system_error();

    impl.format("CHAN%u:DATA?\n", channel);
    return impl.read_binary();

#else /*defined(POWER_OVERWHELMING_WITH_VISA) */
    throw std::logic_error(detail::no_visa_error_msg);
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
}


/*
 * visus::power_overwhelming::rtx_instrument::channel
 */
visus::power_overwhelming::oscilloscope_channel
visus::power_overwhelming::rtx_instrument::channel(
        _In_ const std::uint32_t channel) const {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    auto& impl = this->check_not_disposed();
    oscilloscope_channel retval(channel);

    {
        impl.format("PROB%d:SET:ATT:UNIT?\n", channel);
        auto unit = impl.read_all();

        impl.format("PROB%d:SET:ATT:MAN?\n", channel);
        auto value = impl.read_all();

        retval.attenuation(oscilloscope_quantity(
            std::atof(value.as<char>()),
            unit.as<char>()));
    }

    {
        impl.format("CHAN%d:BAND?\n", channel);
        auto value = impl.read_all();
    }

    {
        impl.format("CHAN%d:COUP?\n", channel);
        auto value = impl.read_all();
    }

    {
        impl.format("CHAN%d:TYPE?\n", channel);
        auto value = impl.read_all();
    }

    {
        impl.format("CHAN%d:LAB?\n", channel);
        auto text = impl.read_all();

        impl.format("CHAN%d:LAB:STAT?\n", channel);
        auto visible = impl.read_all();
    }

    {
        impl.format("CHAN%d:OFFS?\n", channel);
        auto value = impl.read_all();
    }

    {
        impl.format("CHAN%d:RANG?\n", channel);
        auto value = impl.read_all();
    }

    {
        impl.format("CHAN%d:SKEW?\n", channel);
        auto value = impl.read_all();
    }

    {
        impl.format("CHAN%d:STAT?\n", channel);
        auto value = impl.read_all();
    }

    {
        impl.format("CHAN%d:ZOFF?\n", channel);
        auto value = impl.read_all();
        retval.state(*value.as<char>(0) != '0');
    }

    return retval;

#else /*defined(POWER_OVERWHELMING_WITH_VISA) */
    throw std::logic_error(detail::no_visa_error_msg);
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
}


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
    if (channel.attenuation().value() > 0.0f) {
        impl.format("PROB%d:SET:ATT:UNIT %s\n", channel.channel(),
            channel.attenuation().unit());
        impl.format("PROB%d:SET:ATT:MAN %f\n", channel.channel(),
            channel.attenuation().value());
    }

    switch (channel.bandwidth()) {
        case oscilloscope_channel_bandwidth::limit_to_20_mhz:
            impl.format("CHAN%d:BAND B20\n", channel.channel());
            break;

        case oscilloscope_channel_bandwidth::full:
        default:
            impl.format("CHAN%d:BAND FULL\n", channel.channel());
            break;
    }

    switch (channel.coupling()) {
        case oscilloscope_channel_coupling::alternating_current_limit:
            impl.format("CHAN%d:COUP ACL\n", channel.channel());
            break;

        case oscilloscope_channel_coupling::ground:
            impl.format("CHAN%d:COUP GND\n", channel.channel());
            break;

        case oscilloscope_channel_coupling::direct_current_limit:
        default:
            impl.format("CHAN%d:COUP DCL\n", channel.channel());
            break;
    }

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

    impl.format("CHAN%d:LAB \"%s\"\n", channel.channel(),
        channel.label().text());
    impl.format("CHAN%d:LAB:STAT %s\n", channel.channel(),
        channel.label().visible() ? "ON" : "OFF");

    impl.format("CHAN%d:OFFS %f%s\n", channel.channel(),
        channel.offset().value(), channel.offset().unit());

    switch (channel.polarity()) {
        case oscilloscope_channel_polarity::inverted:
            impl.format("CHAN%d:POL INV\n", channel.channel());
            break;

        default:
            impl.format("CHAN%d:POL NORM\n", channel.channel());
            break;
    }

    impl.format("CHAN%d:RANG %f%s\n", channel.channel(),
        channel.range().value(), channel.range().unit());

    impl.format("CHAN%d:SKEW %f%s\n", channel.channel(),
        channel.skew().value(), channel.skew().unit());

    impl.format("CHAN%d:STAT %s\n", channel.channel(),
        channel.state() ? "ON" : "OFF");

    impl.format("CHAN%d:ZOFF %f%s\n", channel.channel(),
        channel.zero_offset().value(), channel.zero_offset().unit());
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */

    return *this;
}


/*
 * visus::power_overwhelming::rtx_instrument::channels
 */
std::size_t visus::power_overwhelming::rtx_instrument::channels(
        _In_ const timeout_type timeout) const {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    try {
        auto& impl = this->check_not_disposed();
        std::size_t retval = 1;
        const detail::rtx_timeout_override timeout(impl.session, timeout);

        // Clear the status as we rely on the device to enter an error state for
        // the detection below.
        impl.write("*CLS; *OPC?\n");
        impl.read_all();

        while (true) {
            try {
                // We count by trying to retrieve the state of the channels one
                // after another. There seems to be no way to query this except
                // for trying when the operation fails ...
                impl.format("CHAN%u:STAT?\n", retval);
                impl.read_all();
                this->throw_on_system_error();
                ++retval;
            } catch (...) {
                impl.write("*CLS; *OPC?\n");
                impl.read_all();
                return (retval - 1);
            }
        }

    } catch (...) {
        // If disposed, we have no channel.
        return 0;
    }

#else /* defined(POWER_OVERWHELMING_WITH_VISA) */
    return 0;
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */
}


/*
 * visus::power_overwhelming::rtx_instrument::data
 */
visus::power_overwhelming::oscilloscope_waveform
visus::power_overwhelming::rtx_instrument::data(
        _In_ const std::uint32_t channel,
        _In_ const oscilloscope_waveform_points points) const {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    auto& impl = this->check_not_disposed();

    switch (points) {
        case oscilloscope_waveform_points::maximum:
            impl.format("CHAN%u:DATA:POIN MAX\n", channel);
            break;

        case oscilloscope_waveform_points::maximum_visible:
            impl.format("CHAN%u:DATA:POIN DMAX\n", channel);
            break;

        case oscilloscope_waveform_points::visible:
        default:
            impl.format("CHAN%u:DATA:POIN DEF\n", channel);
            break;
    }

    const auto query = detail::format_string("CHAN%u:DATA:HEAD?\n", channel);
    const auto header = this->query(query.c_str());
    return oscilloscope_waveform(header.as<char>(), this->binary_data(channel));

#else /*defined(POWER_OVERWHELMING_WITH_VISA) */
    throw std::logic_error(detail::no_visa_error_msg);
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
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

    return *this;
}


/*
 * visus::power_overwhelming::rtx_instrument::history_segment
 */
int visus::power_overwhelming::rtx_instrument::history_segment(void) const {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    auto retval = this->query("CHAN:HIST:CURR?\n");
    return std::atoi(retval.as<char>());

#else /*defined(POWER_OVERWHELMING_WITH_VISA) */
    throw std::logic_error(detail::no_visa_error_msg);
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
}


/*
 * visus::power_overwhelming::rtx_instrument::history_segment
 */
visus::power_overwhelming::rtx_instrument&
visus::power_overwhelming::rtx_instrument::history_segment(
        _In_ const int segment) {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    this->check_not_disposed().format("CHAN:HIST:CURR %i\n", segment);
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
    return *this;
}


/*
 * visus::power_overwhelming::rtx_instrument::history_segments
 */
std::size_t visus::power_overwhelming::rtx_instrument::history_segments(
        void) const {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    auto retval = this->query("ACQ:AVA?\n");
    return std::atoi(retval.as<char>());

#else /*defined(POWER_OVERWHELMING_WITH_VISA) */
    throw std::logic_error(detail::no_visa_error_msg);
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
}


/*
 * visus::power_overwhelming::rtx_instrument::reference_position
 */
visus::power_overwhelming::oscilloscope_reference_point
visus::power_overwhelming::rtx_instrument::reference_position(void) const {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    auto response = this->query("TIM:REF?\n");
    auto position = std::atof(response.as<char>()) * 100;
    return static_cast<oscilloscope_reference_point>(position);

#else /*defined(POWER_OVERWHELMING_WITH_VISA) */
    throw std::logic_error(detail::no_visa_error_msg);
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
}


/*
 * visus::power_overwhelming::rtx_instrument::reference_position
 */
visus::power_overwhelming::rtx_instrument&
visus::power_overwhelming::rtx_instrument::reference_position(
        _In_ const oscilloscope_reference_point position) {
    auto& impl = this->check_not_disposed();
    impl.format("TIM:REF %f\n", static_cast<float>(position) / 100.0f);
    return *this;
}


/*
 * visus::power_overwhelming::rtx_instrument::time_range
 */
visus::power_overwhelming::oscilloscope_quantity
visus::power_overwhelming::rtx_instrument::time_range(void) const {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    auto response = this->query("TIM:RANG?\n");
    return std::atof(response.as<char>());

#else /*defined(POWER_OVERWHELMING_WITH_VISA) */
    throw std::logic_error(detail::no_visa_error_msg);
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
}


/*
 * visus::power_overwhelming::rtx_instrument::time_range
 */
visus::power_overwhelming::rtx_instrument&
visus::power_overwhelming::rtx_instrument::time_range(
        _In_ const oscilloscope_quantity& scale) {
    auto &impl = this->check_not_disposed();
    impl.format("TIM:RANG %f %s\n", scale.value(), scale.unit());
    return *this;
}


/*
 * visus::power_overwhelming::rtx_instrument::time_scale
 */
visus::power_overwhelming::oscilloscope_quantity
visus::power_overwhelming::rtx_instrument::time_scale(void) const {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    auto response = this->query("TIM:SCAL?\n");
    return std::atof(response.as<char>());

#else /*defined(POWER_OVERWHELMING_WITH_VISA) */
    throw std::logic_error(detail::no_visa_error_msg);
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
}


/*
 * visus::power_overwhelming::rtx_instrument::time_scale
 */
visus::power_overwhelming::rtx_instrument&
visus::power_overwhelming::rtx_instrument::time_scale(
        _In_ const oscilloscope_quantity& scale) {
    auto& impl = this->check_not_disposed();
    impl.format("TIM:SCAL %f %s\n", scale.value(), scale.unit());
    return *this;
}


/*
 * visus::power_overwhelming::rtx_instrument::trigger
 */
visus::power_overwhelming::rtx_instrument&
visus::power_overwhelming::rtx_instrument::trigger(_In_ const bool wait) {
    if (wait) {
        this->query("*TRG; *OPC?\n");
    } else {
        this->check_not_disposed().write("*TRG\n");
    }

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

    impl.format("TRIG:A:SOUR %s\n", trigger.source());
    impl.format("TRIG:A:TYPE %s\n", trigger.type());

    if (trigger.hold_off() == nullptr) {
        impl.format("TRIG:A:HOLD:MODE OFF\n");

    } else {
        impl.format("TRIG:A:HOLD:MODE TIME\n");
        impl.format("TRIG:A:HOLD:TIME %s\n", trigger.hold_off());
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

        impl.format("TRIG:A:LEV%d:VAL %f %s\n", et->input(),
            et->level().value(), et->level().unit());

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
        this->check_system_error();
#endif
    }

    return *this;
}


/*
 * visus::power_overwhelming::rtx_instrument::trigger_output
 */
visus::power_overwhelming::rtx_instrument&
visus::power_overwhelming::rtx_instrument::trigger_output(
        _In_ const oscilloscope_trigger_output output) {
    switch (output) {
        case oscilloscope_trigger_output::mask:
            this->check_not_disposed().write("TRIG:OUT:MODE MASK\n");
            break;

        case oscilloscope_trigger_output::pulse:
            this->check_not_disposed().write("TRIG:OUT:MODE TRIG\n");
            break;

        case oscilloscope_trigger_output::reference:
            this->check_not_disposed().write("TRIG:OUT:MODE REF\n");
            break;

        case oscilloscope_trigger_output::off:
        default:
            this->check_not_disposed().write("TRIG:OUT:MODE OFF\n");
            break;
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

    return *this;
}


/*
 * visus::power_overwhelming::rtx_instrument::unit
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

    return *this;
}
