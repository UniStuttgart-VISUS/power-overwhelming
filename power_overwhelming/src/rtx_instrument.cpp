// <copyright file="rtx_instrument.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/rtx_instrument.h"

#include <cassert>
#include <cstdlib>
#include <fstream>
#include <random>

#include "on_exit.h"
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

    /// <summary>
    /// Creates a random temporary file name for on-instrument use.
    /// </summary>
    static std::string make_random_file_name(const std::string& ext = ".TMP") {
        std::string name;
        name.reserve(8 + 1 + 3);

        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<> distribution('A', 'Z');

        for (std::size_t i = 0; i < 8; ++i) {
            name.push_back(distribution(rng));
        }

        name += ext;
        return name;
    }

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
visus::power_overwhelming::oscilloscope_acquisition_state
visus::power_overwhelming::rtx_instrument::acquisition(void) const {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    auto value = this->query("ACQ:STAT?\n");

    if (detail::starts_with(value.as<char>(), "RUN")) {
        return oscilloscope_acquisition_state::run;
    } else if (detail::starts_with(value.as<char>(), "STOP")) {
        return oscilloscope_acquisition_state::stop;
    } else if (detail::starts_with(value.as<char>(), "SING")) {
        return oscilloscope_acquisition_state::single;
    } else if (detail::starts_with(value.as<char>(), "BREAK")) {
        return oscilloscope_acquisition_state::interrupt;
    } else {
        throw std::range_error("The current acquisition state "
            "does not fall in the range of known values.");
    }

#else /*defined(POWER_OVERWHELMING_WITH_VISA) */
throw std::logic_error(detail::no_visa_error_msg);
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
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
 * visus::power_overwhelming::rtx_instrument::beep
 */
visus::power_overwhelming::rtx_instrument&
visus::power_overwhelming::rtx_instrument::beep(_In_ const std::size_t cnt) {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    for (std::size_t i = 0; i < cnt; ++i) {
        this->write("SYST:BEEP:IMM\n");
    }
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
    return *this;
}


/*
 * visus::power_overwhelming::rtx_instrument::beep_on_error
 */
bool visus::power_overwhelming::rtx_instrument::beep_on_error(void) {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    auto response = this->query("SYST:BEEP:ERR:STAT?\n");
    auto status = std::atoi(response.as<char>());
    return (status != 0);
#else /*defined(POWER_OVERWHELMING_WITH_VISA) */
    return false;
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
}


/*
 * visus::power_overwhelming::rtx_instrument::beep_on_error
 */
visus::power_overwhelming::rtx_instrument&
visus::power_overwhelming::rtx_instrument::beep_on_error(
        _In_ const bool enable) {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    auto& impl = this->check_not_disposed();
    impl.format("SYST:BEEP:ERR:STAT %s\n", enable ? "ON" : "OFF");
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */
    return *this;
}


/*
 * visus::power_overwhelming::rtx_instrument::beep_on_trigger
 */
bool visus::power_overwhelming::rtx_instrument::beep_on_trigger(void) {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    auto response = this->query("SYST:BEEP:TRIG:STAT?\n");
    auto status = std::atoi(response.as<char>());
    return (status != 0);
#else /*defined(POWER_OVERWHELMING_WITH_VISA) */
    return false;
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
}


/*
 * visus::power_overwhelming::rtx_instrument::beep_on_trigger
 */
visus::power_overwhelming::rtx_instrument&
visus::power_overwhelming::rtx_instrument::beep_on_trigger(
        _In_ const bool enable) {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    auto& impl = this->check_not_disposed();
    impl.format("SYST:BEEP:TRIG:STAT %s\n", enable ? "ON" : "OFF");
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */
    return *this;
}


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
        auto u = unit.as<char>();
        _Analysis_assume_(u != nullptr);
        *::strchr(u, '\n') = 0;

        impl.format("PROB%d:SET:ATT:MAN?\n", channel);
        auto value = impl.read_all();

        retval.attenuation(oscilloscope_quantity(
            detail::parse_float(value.as<char>()),
            u));
    }

    {
        typedef oscilloscope_channel_bandwidth enum_type;
        impl.format("CHAN%d:BAND?\n", channel);
        auto value = impl.read_all();

        if (detail::starts_with(value.as<char>(), "B20")) {
            retval.bandwidth(enum_type::limit_to_20_mhz);
        } else if (detail::starts_with(value.as<char>(), "FULL")) {
            retval.bandwidth(enum_type::full);
        }
    }

    {
        typedef oscilloscope_channel_coupling enum_type;
        impl.format("CHAN%d:COUP?\n", channel);
        auto value = impl.read_all();

        if (detail::starts_with(value.as<char>(), "ACL")) {
            retval.coupling(enum_type::alternating_current_limit);
        } else if (detail::starts_with(value.as<char>(), "GND")) {
            retval.coupling(enum_type::ground);
        } else if (detail::starts_with(value.as<char>(), "DCL")) {
            retval.coupling(enum_type::direct_current_limit);
        }
    }

    {
        typedef oscilloscope_decimation_mode enum_type;
        impl.format("CHAN%d:TYPE?\n", channel);
        auto value = impl.read_all();

        if (detail::starts_with(value.as<char>(), "HRES")) {
            retval.decimation_mode(enum_type::high_resolution);
        } else if (detail::starts_with(value.as<char>(), "PDET")) {
            retval.decimation_mode(enum_type::peak_detect);
        } else if (detail::starts_with(value.as<char>(), "SAMP")) {
            retval.decimation_mode(enum_type::sample);
        }
    }

    {
        impl.format("CHAN%d:LAB?\n", channel);
        auto text = impl.read_all();
        auto txt = text.as<char>();
        _Analysis_assume_(txt != nullptr);
        *::strchr(txt, '\n') = 0;
        txt = detail::trim_begin_if(txt, [](const char c) {
            return (c == '"');
        });
        *detail::trim_end_if(txt, [](const char c) {
            return (c == '"');
        }) = 0;

        impl.format("CHAN%d:LAB:STAT?\n", channel);
        auto visible = impl.read_all();
        auto vis = !detail::starts_with(visible.as<char>(), "0");

        retval.label(oscilloscope_label(txt, vis));
    }

    {
        impl.format("CHAN%d:OFFS?\n", channel);
        auto value = impl.read_all();
        retval.offset(detail::parse_float(value.as<char>()));
    }

    {
        impl.format("CHAN%d:RANG?\n", channel);
        auto value = impl.read_all();
        retval.range(detail::parse_float(value.as<char>()));
    }

    {
        impl.format("CHAN%d:SKEW?\n", channel);
        auto value = impl.read_all();
        retval.skew(detail::parse_float(value.as<char>()));
    }

    {
        impl.format("CHAN%d:STAT?\n", channel);
        auto value = impl.read_all();
        retval.state(!detail::starts_with(value.as<char>(), "0"));
    }

    {
        impl.format("CHAN%d:ZOFF?\n", channel);
        auto value = impl.read_all();
        retval.zero_offset(detail::parse_float(value.as<char>()));
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
 * visus::power_overwhelming::rtx_instrument::copy_file_from_instrument
 */
visus::power_overwhelming::blob
visus::power_overwhelming::rtx_instrument::copy_file_from_instrument(
        _In_z_ const wchar_t *name, _In_opt_z_ const wchar_t *path) const {
    auto n = convert_string<char>(name);
    auto p = convert_string<char>(path);
    return this->copy_file_from_instrument(n.c_str(), p.c_str());
}


/*
 * visus::power_overwhelming::rtx_instrument::copy_file_from_instrument
 */
visus::power_overwhelming::blob
visus::power_overwhelming::rtx_instrument::copy_file_from_instrument(
        _In_z_ const char *name, _In_opt_z_ const char *path) const {
    if ((name == nullptr) || (*name == 0)) {
        throw std::invalid_argument("The name of the file to read cannot be "
            "null or empty.");
    }

#if defined(POWER_OVERWHELMING_WITH_VISA)
    auto &impl = this->check_not_disposed();

    if ((path != nullptr) && (*path != 0)) {
        impl.format("MMEM:CDIR \"%s\"\n", path);
    }

    impl.format("MMEM:DATA? \"%s\"\n", name);
    return impl.read_binary();
#else /* defined(POWER_OVERWHELMING_WITH_VISA) */
    throw std::logic_error(detail::no_visa_error_msg);
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
}


/*
 * visus::power_overwhelming::rtx_instrument::copy_file_to_instrument
 */
visus::power_overwhelming::rtx_instrument&
visus::power_overwhelming::rtx_instrument::copy_file_to_instrument(
        _In_z_ const wchar_t *name,
        _In_ const blob& content,
        _In_opt_z_ const wchar_t *path) {
    auto n = convert_string<char>(name);
    auto p = convert_string<char>(path);
    return this->copy_file_to_instrument(n.c_str(), content, p.c_str());
}


/*
 * visus::power_overwhelming::rtx_instrument::copy_file_to_instrument
 */
visus::power_overwhelming::rtx_instrument&
visus::power_overwhelming::rtx_instrument::copy_file_to_instrument(
        _In_z_ const char *name,
        _In_ const blob& content,
        _In_opt_z_ const char *path) {
    if ((name == nullptr) || (*name == 0)) {
        throw std::invalid_argument("The name of the file to read cannot be "
            "null or empty.");
    }

#if defined(POWER_OVERWHELMING_WITH_VISA)
    auto &impl = this->check_not_disposed();

    if ((path != nullptr) && (*path != 0)) {
        impl.format("MMEM:CDIR \"%s\"\n", path);
    }

    auto length = std::to_string(content.size());
    if (length.size() > 9) {
        throw std::invalid_argument("The specified content is too long to be "
            "uploaded to the instrument.");
    }

    auto header = detail::format_string("MMEM:DATA \"%s\", #%u%s",
        name, length.size(), length.c_str());
    auto body = content.as<std::uint8_t>();

    impl.write(header.c_str());
    if (body != nullptr) {
        impl.write_all(body, content.size());
    }
    //impl.write("\n");
    impl.check_system_error();
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */

    return *this;
}


#if false
// TODO: that does not work atm. If we upload this again, the state is corrupted.
/*
 * visus::power_overwhelming::rtx_instrument::copy_state_from_instrument
 */
visus::power_overwhelming::blob
visus::power_overwhelming::rtx_instrument::copy_state_from_instrument(
        void) const {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    auto& impl = this->check_not_disposed();

    // Save to temporary file on internal device memory.
    auto file = detail::make_random_file_name(".SET");
    this->save_state_to_instrument(file.c_str());
    this->operation_complete();

    // Download the temporary file.
    auto retval = this->copy_file_from_instrument(file.c_str());
    this->operation_complete();

    // Delete the temporary file from device memory.
    impl.format("MMEM:DEL \"%s\"\n", file.c_str());

    return retval;
#else /* defined(POWER_OVERWHELMING_WITH_VISA) */
    throw std::logic_error(detail::no_visa_error_msg);
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
}
#endif


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
 * visus::power_overwhelming::rtx_instrument::edge_trigger
 */
visus::power_overwhelming::oscilloscope_edge_trigger
visus::power_overwhelming::rtx_instrument::edge_trigger(void) const {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    auto& impl = this->check_not_disposed();

    // First, check whether the trigger is actually an edge trigger.
    {
        auto type = this->query("TRIG:A:TYPE?\n");
        if (!detail::starts_with(type.as<char>(), "EDGE")) {
            throw std::logic_error("The currently configured trigger on "
                "the instrument is not an edge trigger.");
        }
    }

    // Next, we need to know the source for constructing the instance.
    auto source = this->query("TRIG:A:SOUR?\n");
    auto src = source.as<char>();
    _Analysis_assume_(src != nullptr);
    *::strchr(src, '\n') = 0;

    oscilloscope_edge_trigger retval(src);

    {
        typedef oscilloscope_trigger_mode enum_type;
        auto mode = this->query("TRIG:A:MODE?\n");

        if (detail::starts_with(mode.as<char>(), "AUTO")) {
            retval.mode(enum_type::automatic);

        } else if (detail::starts_with(mode.as<char>(), "NORM")) {
            retval.mode(enum_type::normal);

        } else {
            throw std::range_error("The current trigger mode of the instrument "
                "does not fall into the expected range of values.");
        }
    }

    {
        auto mode = this->query("TRIG:A:HOLD:MODE?\n");
        if (detail::starts_with(mode.as<char>(), "TIME")) {
            auto time = this->query("TRIG:A:HOLD:TIME?\n");
            auto t = time.as<char>();
            _Analysis_assume_(t != nullptr);
            *::strchr(t, '\n') = 0;
            retval.hold_off(t);

        } else {
            retval.hold_off(nullptr);
        }
    }

    {
        typedef oscilloscope_trigger_slope enum_type;
        auto edge = this->query("TRIG:A:EDGE:SLOP?\n");

        if (detail::starts_with(edge.as<char>(), "EITH")) {
            retval.slope(enum_type::both);

        } else if (detail::starts_with(edge.as<char>(), "POS")) {
            retval.slope(enum_type::rising);

        } else if (detail::starts_with(edge.as<char>(), "NEG")) {
            retval.slope(enum_type::falling);

        } else {
            throw std::range_error("The current trigger slope of the "
                "instrument does not fall into the expected range of values.");
        }
    }

    {
        auto level = this->query("TRIG:A:LEV:VAL?\n");
        // TODO: Parse channel here for specific level?
        retval.level(detail::parse_float(level.as<char>()));
    }

    {
        typedef oscilloscope_trigger_coupling enum_type;
        auto coupling = this->query("TRIG:A:EDGE:COUP?\n");

        if (detail::starts_with(coupling.as<char>(), "AC")) {
            retval.coupling(enum_type::alternating_current);

        } else if (detail::starts_with(coupling.as<char>(), "DC")) {
            retval.coupling(enum_type::direct_current);

        } else if (detail::starts_with(coupling.as<char>(), "LFR")) {
            retval.coupling(enum_type::low_frequency_reject);

        } else {
            throw std::range_error("The current trigger coupling of the "
                "instrument does not fall into the expected range of values.");
        }
    }

    return retval;
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
    return detail::parse_int(retval.as<char>());

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
    return detail::parse_int(retval.as<char>());

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
    auto position = detail::parse_float(response.as<char>()) * 100;
    return static_cast<oscilloscope_reference_point>(position);

#else /*defined(POWER_OVERWHELMING_WITH_VISA) */
    throw std::logic_error(detail::no_visa_error_msg);
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
}


/*
 * visus::power_overwhelming::rtx_instrument::load_state_from_instrument
 */
visus::power_overwhelming::rtx_instrument&
visus::power_overwhelming::rtx_instrument::load_state_from_instrument(
        _In_z_ const wchar_t *name, _In_z_ const wchar_t *path) {
    auto n = convert_string<char>(name);
    auto p = convert_string<char>(path);
    return this->load_state_from_instrument(n.c_str(), p.c_str());
}


/*
 * visus::power_overwhelming::rtx_instrument::load_state_from_instrument
 */
visus::power_overwhelming::rtx_instrument&
visus::power_overwhelming::rtx_instrument::load_state_from_instrument(
        _In_z_ const char *name, _In_z_ const char *path) {
    if ((name == nullptr) || (*name == 0)) {
        throw std::invalid_argument("The name of the settings file cannot be "
            "empty.");
    }
    if ((path == nullptr) || (*path == 0)) {
        throw std::invalid_argument("The path for reading the settings file "
            "from cannot be empty.");
    }

#if defined(POWER_OVERWHELMING_WITH_VISA)
    auto& impl = this->check_not_disposed();
    impl.format("MMEM:CDIR \"%s\"\n", path);
    impl.format("MMEM:LOAD:STAT 1, \"%s\"\n", name);
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
    return *this;
}


/*
 * visus::power_overwhelming::rtx_instrument::name
 */
std::size_t visus::power_overwhelming::rtx_instrument::name(
        _Out_writes_(cnt) wchar_t *dst,
        _In_ const std::size_t cnt) const {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    auto retval = this->name(nullptr, 0);

    if ((dst != nullptr) && (cnt > retval)) {
        std::vector<char> buffer(retval);
        retval = this->name(buffer.data(), buffer.size());
        auto name = convert_string<wchar_t>(buffer.data());

#if (defined(_MSC_VER) && (_MSC_VER >= 1400))
        ::wcscpy_s(dst, cnt, name.c_str());
#else /* (defined(_MSC_VER) && (_MSC_VER >= 1400)) */
        ::wcscpys(dst, name.c_str());
#endif /* (defined(_MSC_VER) && (_MSC_VER >= 1400)) */
    }

    return retval;

#else /*defined(POWER_OVERWHELMING_WITH_VISA) */
    return 0;
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
}


/*
 * visus::power_overwhelming::rtx_instrument::name
 */
std::size_t visus::power_overwhelming::rtx_instrument::name(
        _Out_writes_(cnt) char *dst,
        _In_ const std::size_t cnt) const {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    auto name = this->query("SYST:NAME?\n");
    auto n = name.as<char>();
    _Analysis_assume_(n != nullptr);

    *::strchr(n, '\n') = 0;
    // TODO: possibly requires removing quotes.
    auto retval = ::strlen(n) + 1;

    if ((dst != nullptr) && (cnt >= retval)) {
#if (defined(_MSC_VER) && (_MSC_VER >= 1400))
        ::strcpy_s(dst, cnt, n);
#else /* (defined(_MSC_VER) && (_MSC_VER >= 1400)) */
        ::strcpy(dst, n);
#endif /* (defined(_MSC_VER) && (_MSC_VER >= 1400)) */
    }

    return retval;

#else /*defined(POWER_OVERWHELMING_WITH_VISA) */
    return 0;
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
}


/*
 * visus::power_overwhelming::rtx_instrument::name
 */
std::size_t visus::power_overwhelming::rtx_instrument::name(
        _In_opt_ const std::nullptr_t dst,
        _In_ const std::size_t cnt) const {
    return this->name(static_cast<char *>(nullptr), 0);
}


/*
 * visus::power_overwhelming::rtx_instrument::name
 */
visus::power_overwhelming::rtx_instrument&
visus::power_overwhelming::rtx_instrument::name(_In_z_ const wchar_t *name) {
    if (name == nullptr) {
        throw std::invalid_argument("The name of the instrument must not be "
            "null.");
    }

    auto n = convert_string<char>(name);
    return this->name(n.c_str());
}


/*
 * visus::power_overwhelming::rtx_instrument::name
 */
visus::power_overwhelming::rtx_instrument&
visus::power_overwhelming::rtx_instrument::name(_In_z_ const char *name) {
    if (name == nullptr) {
        throw std::invalid_argument("The name of the instrument must not be "
            "null.");
    }

    auto& impl = this->check_not_disposed();
    impl.format("SYST:NAME \"%s\"\n", name);
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
    return *this;
}


/*
 * visus::power_overwhelming::rtx_instrument::save_state_to_instrument
 */
const visus::power_overwhelming::rtx_instrument&
visus::power_overwhelming::rtx_instrument::save_state_to_instrument(
        _In_z_ const wchar_t *name, _In_z_ const wchar_t *path) const {
    auto n = convert_string<char>(name);
    auto p = convert_string<char>(path);
    return this->save_state_to_instrument(n.c_str(), p.c_str());
}


/*
 * visus::power_overwhelming::rtx_instrument::save_state_to_instrument
 */
const visus::power_overwhelming::rtx_instrument&
visus::power_overwhelming::rtx_instrument::save_state_to_instrument(
        _In_z_ const char *name, _In_z_ const char *path) const {
    if ((name == nullptr) || (*name == 0)) {
        throw std::invalid_argument("The name of the settings file cannot be "
            "empty.");
    }
    if ((path == nullptr) || (*path == 0)) {
        throw std::invalid_argument("The path for storing the settings file "
            "cannot be empty.");
    }

#if defined(POWER_OVERWHELMING_WITH_VISA)
    auto& impl = this->check_not_disposed();

    impl.format("MMEM:CDIR \"%s\"\n", path);

    std::string file_name(name);
    std::string ext(".SET");

    // Check whether we have a user-defined extension.
    const auto ext_pos = file_name.find_last_of('.');
    if (ext_pos != std::string::npos) {
        ext = file_name.substr(ext_pos);
        file_name = file_name.substr(0, ext_pos);
    }

    // Truncate to 8.3 format on device.
    if (file_name.length() > 8) {
        file_name = file_name.substr(0, 8);
    }
    if (ext.length() > 4) {
        ext = ext.substr(0, 4);
    }
    file_name += ext;

    impl.format("MMEM:STOR:STAT 1, \"%s\"\n", file_name.c_str());
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
    return *this;
}


/*
 * visus::power_overwhelming::rtx_instrument::single_acquisition
 */
visus::power_overwhelming::oscilloscope_single_acquisition
visus::power_overwhelming::rtx_instrument::single_acquisition(void) const {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    auto& impl = this->check_not_disposed();
    oscilloscope_single_acquisition retval;

    auto aut = this->query("ACQ:POIN:AUT?\n");
    if (detail::starts_with(aut.as<char>(), "0")) {
        auto points = this->query("ACQ:POIN:VAL?\n");
        retval.points(detail::parse_uint(points.as<char>()));
    } else {
        retval.enable_automatic_points();
    }

    auto cnt = this->query("ACQ:NSIN:COUN?\n");
    retval.count(detail::parse_uint(cnt.as<char>()));

    auto seg = this->query("ACQ:SEGM:STAT?\n");
    retval.segmented(!detail::starts_with(aut.as<char>(), "0"));

    return retval;
#else /*defined(POWER_OVERWHELMING_WITH_VISA) */
    throw std::logic_error(detail::no_visa_error_msg);
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
}


/*
 * visus::power_overwhelming::rtx_instrument::time_range
 */
visus::power_overwhelming::oscilloscope_quantity
visus::power_overwhelming::rtx_instrument::time_range(void) const {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    auto response = this->query("TIM:RANG?\n");
    return detail::parse_float(response.as<char>());

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
    return detail::parse_float(response.as<char>());

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

        if (et->input() > 0) {
            impl.format("TRIG:A:LEV%d:VAL %f%s\n", et->input(),
                et->level().value(), et->level().unit());
        } else {
            impl.format("TRIG:A:LEV:VAL %f%s\n", et->level().value(),
                et->level().unit());
        }

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
visus::power_overwhelming::oscilloscope_trigger_output
visus::power_overwhelming::rtx_instrument::trigger_output(void) const {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    typedef oscilloscope_trigger_output enum_type;
    auto value = this->query("TRIG:OUT:MODEL?\n");

    if (detail::starts_with(value.as<char>(), "MASK")) {
        return enum_type::mask;
    } else if (detail::starts_with(value.as<char>(), "TRIG")) {
        return enum_type::pulse;
    } else if (detail::starts_with(value.as<char>(), "REF")) {
        return enum_type::reference;
    } else if (detail::starts_with(value.as<char>(), "OFF")) {
        return enum_type::off;
    } else {
        throw std::range_error("The trigger output currently configured "
            "does not fall in the range of known values.");
    }

#else /*defined(POWER_OVERWHELMING_WITH_VISA) */
    throw std::logic_error(detail::no_visa_error_msg);
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
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
std::size_t visus::power_overwhelming::rtx_instrument::unit(
        _Out_writes_(cnt) wchar_t *dst,
        _In_ const std::size_t cnt,
        _In_ const std::uint32_t channel) const {
    auto retval = this->unit(static_cast<char *>(nullptr), 0, channel);

    if ((dst != nullptr) && (cnt >= retval)) {
        blob u(retval * sizeof(char));
        auto src = u.as<char>();
        _Analysis_assume_(src != nullptr);
        this->unit(src, retval, channel);
        detail::convert_string(dst, cnt, src, retval);
    }

    return retval;
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
std::size_t visus::power_overwhelming::rtx_instrument::unit(
        _Out_writes_(cnt) char *dst,
        _In_ const std::size_t cnt,
        _In_ const std::uint32_t channel) const {
#if defined(POWER_OVERWHELMING_WITH_VISA)
    auto& impl = this->check_not_disposed();
    impl.format("PROB%u:SET:ATT:UNIT?\n", channel);

    // Read the answer and get a first guess of how long it is.
    auto unit = impl.read_all();
    auto src = unit.as<char>();
    _Analysis_assume_(src != nullptr);
    auto end = ::strchr(src, '\n');
    *end = 0;

    const auto retval = end - src + 1;
    if ((dst != nullptr) && (cnt >= retval)) {
        ::memcpy(dst, src, retval * sizeof(char));
    }

    return retval;
#else /*defined(POWER_OVERWHELMING_WITH_VISA) */
    throw std::logic_error(detail::no_visa_error_msg);
#endif /*defined(POWER_OVERWHELMING_WITH_VISA) */
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


/*
 * visus::power_overwhelming::rtx_instrument::unit
 */
std::size_t visus::power_overwhelming::rtx_instrument::unit(
        _In_opt_ std::nullptr_t dst,
        _In_ const std::size_t cnt,
        _In_ const std::uint32_t channel) const {
    return this->unit(static_cast<char *>(dst), 0, channel);
}
