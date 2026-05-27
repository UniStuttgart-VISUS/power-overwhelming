// <copyright file="rtx_sensor_trigger_builder.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/rtx_sensor_trigger_builder.h"

#include <cassert>
#include <stdexcept>

#include "visus/pwrowg/convert_string.h"
#include "visus/pwrowg/trace.h"
#include "visus/pwrowg/rtx_instrument.h"

#include "rtx_sensor_trigger_impl.h"
#include "visa_library.h"


/// <summary>
/// Applies the defaults for the parallel port trigger.
/// </summary>
static void configure_par_default(
        _In_ PWROWG_DETAIL_NAMESPACE::rtx_sensor_trigger_impl& impl,
        _In_ const wchar_t *channel) {
    using namespace PWROWG_NAMESPACE;
    assert(impl.trigger == nullptr);
    impl.trigger = std::make_unique<rtx_trigger>(channel, L"EDGE");
    impl.trigger->level(rtx_quantity(2.5f, "V"));
    impl.trigger->slope(rtx_trigger_slope::rising);
}


/// <summary>
/// Applies the defaults for the parallel port trigger.
/// </summary>
static void configure_par_default(
        _In_ PWROWG_DETAIL_NAMESPACE::rtx_sensor_trigger_impl& impl,
        _In_ const char *channel) {
    using namespace PWROWG_NAMESPACE;
    assert(impl.trigger == nullptr);
    impl.trigger = std::make_unique<rtx_trigger>(channel, "EDGE");
    impl.trigger->level(rtx_quantity(2.5f, "V"));
    impl.trigger->slope(rtx_trigger_slope::rising);
}


/// <summary>
/// Applies the defaults for the parallel port trigger.
/// </summary>
static void configure_par_default(
        _In_ PWROWG_DETAIL_NAMESPACE::rtx_sensor_trigger_impl& impl,
        _In_ const PWROWG_NAMESPACE::rtx_trigger::input_type channel) {
    using namespace PWROWG_NAMESPACE;
    assert(impl.trigger == nullptr);
    impl.trigger = std::make_unique<rtx_trigger>(channel, L"EDGE");
    impl.trigger->level(rtx_quantity(2.5f, "V"));
    impl.trigger->slope(rtx_trigger_slope::rising);
}


/*
 * PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_chan1::with_coupling
 */
PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_chan1&
PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_chan1::with_coupling(
        _In_ const rtx_trigger_coupling coupling) {
    assert(this->_trigger._impl != nullptr);
    assert(this->_trigger._impl->trigger != nullptr);
    this->_trigger._impl->trigger->coupling(coupling);
    return *this;
}


/*
 * PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_chan1::without_hold_off
 */
PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_chan1&
PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_chan1::without_hold_off(void) {
    assert(this->_trigger._impl != nullptr);
    assert(this->_trigger._impl->trigger != nullptr);
    this->_trigger._impl->trigger->hold_off(nullptr);
    return *this;
}


/*
 * PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_chan1::with_hold_off
 */
PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_chan1&
PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_chan1::with_hold_off(
        _In_z_ const wchar_t *time) {
    assert(this->_trigger._impl != nullptr);
    assert(this->_trigger._impl->trigger != nullptr);
    this->_trigger._impl->trigger->hold_off(time);
    return *this;
}


/*
 * PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_chan1::with_hold_off
 */
PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_chan1&
PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_chan1::with_hold_off(
        _In_z_ const char *time) {
    assert(this->_trigger._impl != nullptr);
    assert(this->_trigger._impl->trigger != nullptr);
    this->_trigger._impl->trigger->hold_off(time);
    return *this;
}



/*
 * PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_chan0::falls_below
 */
PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_chan1
PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_chan0::falls_below(
        _In_ const rtx_quantity& level) {
    assert(this->_trigger._impl != nullptr);
    assert(this->_trigger._impl->trigger != nullptr);
    this->_trigger._impl->trigger->type("EDGE")
        .slope(rtx_trigger_slope::falling)
        .level(level);
    return this->_trigger;
}


/*
 * PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_chan0::passes_through
 */
PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_chan1
PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_chan0::passes_through(
        _In_ const rtx_quantity& level) {
    assert(this->_trigger._impl != nullptr);
    assert(this->_trigger._impl->trigger != nullptr);
    this->_trigger._impl->trigger->type("EDGE")
        .slope(rtx_trigger_slope::both)
        .level(level);
    return this->_trigger;
}


/*
 * PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_chan0::rises_above
 */
PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_chan1
PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_chan0::rises_above(
        _In_ const rtx_quantity& level) {
    assert(this->_trigger._impl != nullptr);
    assert(this->_trigger._impl->trigger != nullptr);
    this->_trigger._impl->trigger->type("EDGE")
        .slope(rtx_trigger_slope::rising)
        .level(level);
    return this->_trigger;
}


/*
 * PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_par3::at_level
 */
PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_par3&
PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_par3::at_level(
        _In_ const rtx_quantity& level) {
    assert(this->_trigger._impl != nullptr);
    assert(this->_trigger._impl->trigger != nullptr);
    this->_trigger._impl->trigger->level(level);
    return *this;
}


/*
 * PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_par2::measured_via_channel
 */
PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_par3
PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_par2::measured_via_channel(
        _In_z_ const wchar_t *channel) {
    assert(this->_trigger._impl != nullptr);
    ::configure_par_default(*this->_trigger._impl, channel);
    return this->_trigger;
}


/*
 * PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_par2::measured_via_channel
 */
PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_par3
PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_par2::measured_via_channel(
        _In_z_ const char *channel) {
    assert(this->_trigger._impl != nullptr);
    ::configure_par_default(*this->_trigger._impl, channel);
    return this->_trigger;
}


/*
 * PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_par2::measured_via_channel
 */
PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_par3
PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_par2::measured_via_channel(
        _In_ const rtx_trigger::input_type channel) {
    assert(this->_trigger._impl != nullptr);
    ::configure_par_default(*this->_trigger._impl, channel);
    return this->_trigger;
}


/*
 * PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_par1::raised_for
 */
PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_par2
PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_par1::for_duration(
        _In_ const milliseconds_type duration) {
    assert(this->_trigger._impl != nullptr);
    this->_trigger._impl->external_trigger_duration = duration;
    return this->_trigger;
}


/*
 * PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_par0::measured_via_channel
 */
PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_par3
PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_par0::measured_via_channel(
        _In_z_ const wchar_t *channel) {
    assert(this->_trigger._impl != nullptr);
    ::configure_par_default(*this->_trigger._impl, channel);
    return this->_trigger;
}


/*
 * PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_par0::measured_via_channel
 */
PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_par3
PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_par0::measured_via_channel(
        _In_z_ const char *channel) {
    assert(this->_trigger._impl != nullptr);
    ::configure_par_default(*this->_trigger._impl, channel);
    return this->_trigger;
}


/*
 * PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_par0::measured_via_channel
 */
PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_par3
PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_par0::measured_via_channel(
        _In_ const rtx_trigger::input_type channel) {
    assert(this->_trigger._impl != nullptr);
    ::configure_par_default(*this->_trigger._impl, channel);
    return this->_trigger;
}


/*
 * PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_par0::raise_pins
 */
PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_par1
PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_par0::raise_pins(
    _In_ const parallel_port_pin pins) {
    assert(this->_trigger._impl != nullptr);
    this->_trigger._impl->external_trigger_pins = pins;
    return this->_trigger;
}


/*
 * PWROWG_NAMESPACE::rtx_sensor_trigger_builder::for_name
 */
PWROWG_NAMESPACE::rtx_sensor_trigger_builder
PWROWG_NAMESPACE::rtx_sensor_trigger_builder::for_name(
        _In_z_ const wchar_t *name,
        _In_ const std::int32_t timeout) {
    if (name == nullptr) {
        throw std::invalid_argument("A valid device name must be provided.");
    }

    const auto n = convert_string<char>(name);
    return for_name(n.c_str(), timeout);
}


/*
 * PWROWG_NAMESPACE::rtx_sensor_trigger_builder::for_name
 */
PWROWG_NAMESPACE::rtx_sensor_trigger_builder
PWROWG_NAMESPACE::rtx_sensor_trigger_builder::for_name(
        _In_z_ const char *name,
        _In_ const std::int32_t timeout) {
    if (name == nullptr) {
        throw std::invalid_argument("A valid device name must be provided.");
    }

    const auto devices = detail::visa_library::instance().find_resource();
    std::string dev_name(name);
    const auto cnt_name = dev_name.size() + 1;
    std::string path;

    for (auto d : devices) {
        try {
            rtx_instrument i(d.c_str(), timeout);
            if (i.name(nullptr, 0) == cnt_name) {
                // Only if the device name has the name length, there is a
                // chance for a match.
                dev_name[0] = 0;
                i.name(&dev_name[0], cnt_name);

                if (dev_name == name) {
                    if (!path.empty()) {
                        // If we already have match, the name is not unique,
                        // which is an error. We do not want to have naming
                        // collisions here as the trigger configuration might
                        // be wrong in this case.
                        throw std::invalid_argument("The given name does not "
                            "uniquely identify a instrument.");
                    }

                    path = d;
                }
            } /* if (i.name(nullptr, 0) == dev_name.size()) */
        } catch (...) {
            PWROWG_TRACE("Failed to open instrument \"%s\", so we skip it.",
                d.c_str());
        }
    } /* for (auto d : devices) */

    if (path.empty()) {
        throw std::invalid_argument("No instrument with the given name could "
            "be found.");
    }

    return for_path(path.c_str());
}


/*
 * PWROWG_NAMESPACE::rtx_sensor_trigger_builder::for_path
 */
PWROWG_NAMESPACE::rtx_sensor_trigger_builder
PWROWG_NAMESPACE::rtx_sensor_trigger_builder::for_path(
        _In_z_ const wchar_t *path) {
    if (path == nullptr) {
        throw std::invalid_argument("A valid VISA path must be provided.");
    }

    rtx_sensor_trigger_builder retval;
    retval._trigger._impl->path = convert_string<char>(path);
    return retval;
}


/*
 * PWROWG_NAMESPACE::rtx_sensor_trigger_builder::for_path
 */
PWROWG_NAMESPACE::rtx_sensor_trigger_builder
PWROWG_NAMESPACE::rtx_sensor_trigger_builder::for_path(
        _In_z_ const char *path) {
    if (path == nullptr) {
        throw std::invalid_argument("A valid VISA path must be provided.");
    }

    rtx_sensor_trigger_builder retval;
    retval._trigger._impl->path = path;
    return retval;
}


/*
 * PWROWG_NAMESPACE::rtx_sensor_trigger_builder::when_channel
 */
PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_chan0
PWROWG_NAMESPACE::rtx_sensor_trigger_builder::when_channel(
        _In_z_ const wchar_t *channel) {
    assert(this->_trigger._impl != nullptr);
    assert(this->_trigger._impl->trigger == nullptr);
    this->_trigger._impl->trigger = std::make_unique<rtx_trigger>(channel,
        L"EDGE");
    return this->_trigger;
}


/*
 * PWROWG_NAMESPACE::rtx_sensor_trigger_builder::when_channel
 */
PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_chan0
PWROWG_NAMESPACE::rtx_sensor_trigger_builder::when_channel(
        _In_z_ const char *channel) {
    assert(this->_trigger._impl != nullptr);
    assert(this->_trigger._impl->trigger == nullptr);
    this->_trigger._impl->trigger = std::make_unique<rtx_trigger>(channel,
        "EDGE");
    return this->_trigger;
}


/*
 * PWROWG_NAMESPACE::rtx_sensor_trigger_builder::when_channel
 */
PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_chan0
PWROWG_NAMESPACE::rtx_sensor_trigger_builder::when_channel(
        _In_ const rtx_trigger::input_type channel) {
    assert(this->_trigger._impl != nullptr);
    assert(this->_trigger._impl->trigger == nullptr);
    this->_trigger._impl->trigger = std::make_unique<rtx_trigger>(channel,
        L"EDGE");
    return this->_trigger;
}


/*
 * PWROWG_NAMESPACE::rtx_sensor_trigger_builder::when_parallel_port
 */
PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_par0
PWROWG_NAMESPACE::rtx_sensor_trigger_builder::when_parallel_port(
        _In_z_ const wchar_t *path) {
    assert(this->_trigger._impl != nullptr);
    assert(this->_trigger._impl->trigger == nullptr);
    this->_trigger._impl->external_trigger.open(path);
    return this->_trigger;
}


/*
 * PWROWG_NAMESPACE::rtx_sensor_trigger_builder::when_parallel_port
 */
PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_par0
PWROWG_NAMESPACE::rtx_sensor_trigger_builder::when_parallel_port(
        _In_z_ const char *path) {
    assert(this->_trigger._impl != nullptr);
    assert(this->_trigger._impl->trigger == nullptr);
    this->_trigger._impl->external_trigger.open(path);
    return this->_trigger;
}


/*
 * PWROWG_NAMESPACE::rtx_sensor_trigger_builder::when_software_triggered
 */
PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_final
PWROWG_NAMESPACE::rtx_sensor_trigger_builder::when_software_triggered(
        void) noexcept {
    assert(this->_trigger._impl != nullptr);
    assert(this->_trigger._impl->trigger == nullptr);
    return this->_trigger;
}