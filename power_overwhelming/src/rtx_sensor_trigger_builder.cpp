// <copyright file="rtx_sensor_trigger_builder.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/rtx_sensor_trigger_builder.h"

#include <cassert>
#include <stdexcept>

#include "visus/pwrowg/convert_string.h"

#include "rtx_sensor_trigger_impl.h"


/*
 * PWROWG_DETAIL_NAMESPACE::rtx_sensor_trg_build_chan_final::with_coupling
 */
PWROWG_DETAIL_NAMESPACE::rtx_sensor_trg_build_chan_final&
PWROWG_DETAIL_NAMESPACE::rtx_sensor_trg_build_chan_final::with_coupling(
        _In_ const rtx_trigger_coupling coupling) {
    assert(this->_trigger._impl != nullptr);
    assert(this->_trigger._impl->trigger != nullptr);
    this->_trigger._impl->trigger->coupling(coupling);
    return *this;
}


/*
 * PWROWG_DETAIL_NAMESPACE::rtx_sensor_trg_build_chan_final::without_hold_off
 */
PWROWG_DETAIL_NAMESPACE::rtx_sensor_trg_build_chan_final&
PWROWG_DETAIL_NAMESPACE::rtx_sensor_trg_build_chan_final::without_hold_off(
        void) {
    assert(this->_trigger._impl != nullptr);
    assert(this->_trigger._impl->trigger != nullptr);
    this->_trigger._impl->trigger->hold_off(nullptr);
    return *this;
}


/*
 * PWROWG_DETAIL_NAMESPACE::rtx_sensor_trg_build_chan_final::with_hold_off
 */
PWROWG_DETAIL_NAMESPACE::rtx_sensor_trg_build_chan_final&
PWROWG_DETAIL_NAMESPACE::rtx_sensor_trg_build_chan_final::with_hold_off(
        _In_z_ const wchar_t *time) {
    assert(this->_trigger._impl != nullptr);
    assert(this->_trigger._impl->trigger != nullptr);
    this->_trigger._impl->trigger->hold_off(time);
    return *this;
}


/*
 * PWROWG_DETAIL_NAMESPACE::rtx_sensor_trg_build_chan_final::with_hold_off
 */
PWROWG_DETAIL_NAMESPACE::rtx_sensor_trg_build_chan_final&
PWROWG_DETAIL_NAMESPACE::rtx_sensor_trg_build_chan_final::with_hold_off(
        _In_z_ const char *time) {
    assert(this->_trigger._impl != nullptr);
    assert(this->_trigger._impl->trigger != nullptr);
    this->_trigger._impl->trigger->hold_off(time);
    return *this;
}


/*
 * PWROWG_DETAIL_NAMESPACE::rtx_sensor_trg_build_chan::falls_below
 */
PWROWG_DETAIL_NAMESPACE::rtx_sensor_trg_build_chan_final
PWROWG_DETAIL_NAMESPACE::rtx_sensor_trg_build_chan::falls_below(
        _In_ const rtx_quantity& level) {
    assert(this->_trigger._impl != nullptr);
    assert(this->_trigger._impl->trigger != nullptr);
    this->_trigger._impl->trigger->type("EDGE")
        .slope(rtx_trigger_slope::falling)
        .level(level);
    return this->_trigger;
}


/*
 * PWROWG_DETAIL_NAMESPACE::rtx_sensor_trg_build_chan::passes_through
 */
PWROWG_DETAIL_NAMESPACE::rtx_sensor_trg_build_chan_final
PWROWG_DETAIL_NAMESPACE::rtx_sensor_trg_build_chan::passes_through(
        _In_ const rtx_quantity& level) {
    assert(this->_trigger._impl != nullptr);
    assert(this->_trigger._impl->trigger != nullptr);
    this->_trigger._impl->trigger->type("EDGE")
        .slope(rtx_trigger_slope::both)
        .level(level);
    return this->_trigger;
}


/*
 * PWROWG_DETAIL_NAMESPACE::rtx_sensor_trg_build_chan::rises_above
 */
PWROWG_DETAIL_NAMESPACE::rtx_sensor_trg_build_chan_final
PWROWG_DETAIL_NAMESPACE::rtx_sensor_trg_build_chan::rises_above(
        _In_ const rtx_quantity& level) {
    assert(this->_trigger._impl != nullptr);
    assert(this->_trigger._impl->trigger != nullptr);
    this->_trigger._impl->trigger->type("EDGE")
        .slope(rtx_trigger_slope::rising)
        .level(level);
    return this->_trigger;
}


/*
 * PWROWG_DETAIL_NAMESPACE::rtx_sensor_trg_build_par::measured_via_channel
 */
PWROWG_DETAIL_NAMESPACE::rtx_sensor_trg_build_chan_final
PWROWG_DETAIL_NAMESPACE::rtx_sensor_trg_build_par::measured_via_channel(
        _In_z_ const wchar_t *channel) {
    assert(this->_trigger._impl != nullptr);
    assert(this->_trigger._impl->trigger == nullptr);
    this->_trigger._impl->trigger = std::make_unique<rtx_trigger>(channel,
        L"EDGE");
    this->_trigger._impl->trigger->slope(rtx_trigger_slope::rising)
        .level(rtx_quantity(2.5f, "V"));
    return this->_trigger;
}


/*
 * PWROWG_DETAIL_NAMESPACE::rtx_sensor_trg_build_par::measured_via_channel
 */
PWROWG_DETAIL_NAMESPACE::rtx_sensor_trg_build_chan_final
PWROWG_DETAIL_NAMESPACE::rtx_sensor_trg_build_par::measured_via_channel(
        _In_z_ const char *channel) {
    assert(this->_trigger._impl != nullptr);
    assert(this->_trigger._impl->trigger == nullptr);
    this->_trigger._impl->trigger = std::make_unique<rtx_trigger>(channel,
        "EDGE");
    this->_trigger._impl->trigger->slope(rtx_trigger_slope::rising)
        .level(rtx_quantity(2.5f, "V"));
    return this->_trigger;
}

/*
 * PWROWG_DETAIL_NAMESPACE::rtx_sensor_trg_build_par::measured_via_channel
 */
PWROWG_DETAIL_NAMESPACE::rtx_sensor_trg_build_chan_final
PWROWG_DETAIL_NAMESPACE::rtx_sensor_trg_build_par::measured_via_channel(
        _In_ const rtx_trigger::input_type channel) {
    assert(this->_trigger._impl != nullptr);
    assert(this->_trigger._impl->trigger == nullptr);
    this->_trigger._impl->trigger = std::make_unique<rtx_trigger>(channel,
        L"EDGE");
    this->_trigger._impl->trigger->slope(rtx_trigger_slope::rising)
        .level(rtx_quantity(2.5f, "V"));
    return this->_trigger;
}


/*
 * PWROWG_DETAIL_NAMESPACE::rtx_sensor_trg_build_par::raised_for
 */
PWROWG_DETAIL_NAMESPACE::rtx_sensor_trg_build_par&
PWROWG_DETAIL_NAMESPACE::rtx_sensor_trg_build_par::raised_for(
        _In_ const milliseconds_type duration) {
    assert(this->_trigger._impl != nullptr);
    this->_trigger._impl->external_trigger_duration = duration;
    return *this;
}


/*
 * PWROWG_DETAIL_NAMESPACE::rtx_sensor_trg_build_par::use_pins
 */
PWROWG_DETAIL_NAMESPACE::rtx_sensor_trg_build_par&
PWROWG_DETAIL_NAMESPACE::rtx_sensor_trg_build_par::use_pins(
        _In_ const parallel_port_pin pins) {
    assert(this->_trigger._impl != nullptr);
    this->_trigger._impl->external_trigger_pins = pins;
    return *this;
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
PWROWG_DETAIL_NAMESPACE::rtx_sensor_trg_build_chan
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
PWROWG_DETAIL_NAMESPACE::rtx_sensor_trg_build_chan
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
PWROWG_DETAIL_NAMESPACE::rtx_sensor_trg_build_chan
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
PWROWG_DETAIL_NAMESPACE::rtx_sensor_trg_build_par
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
PWROWG_DETAIL_NAMESPACE::rtx_sensor_trg_build_par
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
PWROWG_DETAIL_NAMESPACE::rtx_sensor_trg_build_final
PWROWG_NAMESPACE::rtx_sensor_trigger_builder::when_software_triggered(
        void) noexcept {
    assert(this->_trigger._impl != nullptr);
    assert(this->_trigger._impl->trigger == nullptr);
    return this->_trigger;
}