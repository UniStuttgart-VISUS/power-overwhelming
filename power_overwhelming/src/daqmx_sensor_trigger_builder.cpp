// <copyright file="daqmx_sensor_trigger_builder.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/daqmx_sensor_trigger_builder.h"

#include <cassert>
#include <stdexcept>

#include "visus/pwrowg/convert_string.h"
#include "visus/pwrowg/daqmx_sample_clock_timing.h"
#include "visus/pwrowg/string_functions.h"
#include "visus/pwrowg/trace.h"

#include "daqmx_sensor_trigger_impl.h"


/*
 * PWROWG_DETAIL_NAMESPACE::daqmx_sen_trg_bld_final1::a_finite_number
 */
PWROWG_DETAIL_NAMESPACE::daqmx_sen_trg_bld_final2&
PWROWG_DETAIL_NAMESPACE::daqmx_sen_trg_bld_final1::a_finite_number(
        _In_ const std::uint64_t samples) {
    assert(this->_trigger._impl != nullptr);
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
    assert(this->_trigger._impl->timing != nullptr);
    auto timing = dynamic_cast<daqmx_sample_clock_timing *>(
        this->_trigger._impl->timing.get());
    assert(timing != nullptr);
    timing->mode(daqmx_sample_mode::finite).samples(samples);
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
    return *this;
}


/*
 * PWROWG_DETAIL_NAMESPACE::daqmx_sen_trg_bld_final1::in_batches_of
 */
PWROWG_DETAIL_NAMESPACE::daqmx_sen_trg_bld_final2&
PWROWG_DETAIL_NAMESPACE::daqmx_sen_trg_bld_final1::in_batches_of(
        _In_ const std::uint64_t samples) {
    assert(this->_trigger._impl != nullptr);
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
    assert(this->_trigger._impl->timing != nullptr);
    auto timing = dynamic_cast<daqmx_sample_clock_timing *>(
        this->_trigger._impl->timing.get());
    assert(timing != nullptr);
    timing->samples(samples);
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
    return *this;
}


/*
 * PWROWG_DETAIL_NAMESPACE::daqmx_sen_trg_bld_final0::sample_at
 */
PWROWG_DETAIL_NAMESPACE::daqmx_sen_trg_bld_final1
PWROWG_DETAIL_NAMESPACE::daqmx_sen_trg_bld_final0::sample_at(
        _In_ const double rate) {
    assert(this->_trigger._impl != nullptr);
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
    assert(this->_trigger._impl->timing == nullptr);
    this->_trigger._impl->timing = std::make_unique<daqmx_sample_clock_timing>(
        rate, daqmx_edge::rising, daqmx_sample_mode::continuous);
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
    return daqmx_sen_trg_bld_final1(this->_trigger);
}


/*
 * PWROWG_DETAIL_NAMESPACE::daqmx_sen_trg_bld_chan0::daqmx_sen_trg_bld_chan0
 */
PWROWG_DETAIL_NAMESPACE::daqmx_sen_trg_bld_chan0::daqmx_sen_trg_bld_chan0(
        _In_ const daqmx_sensor_trigger& trigger,
        _In_ const char *channel)
        : _trigger(trigger) {
    assert(this->_trigger._impl != nullptr);
    assert(channel != nullptr);
    detail::safe_assign(this->_channel, channel);
}


/*
 * PWROWG_DETAIL_NAMESPACE::daqmx_sen_trg_bld_chan0::is_falling_below
 */
PWROWG_DETAIL_NAMESPACE::daqmx_sen_trg_bld_final0
PWROWG_DETAIL_NAMESPACE::daqmx_sen_trg_bld_chan0::is_falling_below(
        _In_ const double level) {
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
    assert(this->_trigger._impl != nullptr);
    assert(this->_trigger._impl->trigger == nullptr);
    this->_trigger._impl->trigger.reset(new daqmx_analog_edge_trigger(
        this->_channel.as<char>(), daqmx_edge::falling, level));
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
    return daqmx_sen_trg_bld_final0(this->_trigger);
}


/*
 * PWROWG_DETAIL_NAMESPACE::daqmx_sen_trg_bld_chan0::is_rising_above
 */
PWROWG_DETAIL_NAMESPACE::daqmx_sen_trg_bld_final0
PWROWG_DETAIL_NAMESPACE::daqmx_sen_trg_bld_chan0::is_rising_above(
        _In_ const double level) {
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
    assert(this->_trigger._impl != nullptr);
    assert(this->_trigger._impl->trigger == nullptr);
    this->_trigger._impl->trigger.reset(new daqmx_analog_edge_trigger(
        this->_channel.as<char>(), daqmx_edge::rising, level));
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
    return daqmx_sen_trg_bld_final0(this->_trigger);
}


/*
 * PWROWG_DETAIL_NAMESPACE::daqmx_sen_trg_bld_par3::sample_at
 */
PWROWG_DETAIL_NAMESPACE::daqmx_sen_trg_bld_final1
PWROWG_DETAIL_NAMESPACE::daqmx_sen_trg_bld_par3::sample_at(
        _In_ const double rate) {
    return this->is_rising_above(2.5).sample_at(rate);
}


/*
 * PWROWG_DETAIL_NAMESPACE::daqmx_sen_trg_bld_par2::measured_via_channel
 */
PWROWG_DETAIL_NAMESPACE::daqmx_sen_trg_bld_par3
PWROWG_DETAIL_NAMESPACE::daqmx_sen_trg_bld_par2::measured_via_channel(
        _In_z_ const wchar_t *channel) {
    assert(this->_trigger._impl != nullptr);
    assert(channel != nullptr);
    const auto c = PWROWG_NAMESPACE::convert_string<char>(channel);
    return daqmx_sen_trg_bld_par3(this->_trigger, c.c_str());
}


/*
 * PWROWG_DETAIL_NAMESPACE::daqmx_sen_trg_bld_par2::measured_via_channel
 */
PWROWG_DETAIL_NAMESPACE::daqmx_sen_trg_bld_par3
PWROWG_DETAIL_NAMESPACE::daqmx_sen_trg_bld_par2::measured_via_channel(
        _In_z_ const char *channel) {
    assert(this->_trigger._impl != nullptr);
    assert(channel != nullptr);
    return daqmx_sen_trg_bld_par3(this->_trigger, channel);
}



/*
 * PWROWG_DETAIL_NAMESPACE::rtx_sen_trg_bld_par1::raised_for
 */
PWROWG_DETAIL_NAMESPACE::daqmx_sen_trg_bld_par2
PWROWG_DETAIL_NAMESPACE::daqmx_sen_trg_bld_par1::for_duration(
        _In_ const milliseconds_type duration) {
    assert(this->_trigger._impl != nullptr);
    this->_trigger._impl->external_trigger_duration = duration;
    return this->_trigger;
}

/*
 * PWROWG_DETAIL_NAMESPACE::daqmx_sen_trg_bld_par0::measured_via_channel
 */
PWROWG_DETAIL_NAMESPACE::daqmx_sen_trg_bld_par3
PWROWG_DETAIL_NAMESPACE::daqmx_sen_trg_bld_par0::measured_via_channel(
        _In_z_ const wchar_t *channel) {
    assert(channel != nullptr);
    assert(this->_trigger._impl != nullptr);
    daqmx_sen_trg_bld_par2 builder(this->_trigger);
    return builder.measured_via_channel(channel);
}


/*
 * PWROWG_DETAIL_NAMESPACE::daqmx_sen_trg_bld_par2::measured_via_channel
 */
PWROWG_DETAIL_NAMESPACE::daqmx_sen_trg_bld_par3
PWROWG_DETAIL_NAMESPACE::daqmx_sen_trg_bld_par0::measured_via_channel(
        _In_z_ const char *channel) {
    assert(channel != nullptr);
    assert(this->_trigger._impl != nullptr);
    daqmx_sen_trg_bld_par2 builder(this->_trigger);
    return builder.measured_via_channel(channel);
}


/*
 * PWROWG_DETAIL_NAMESPACE::daqmx_sen_trg_bld_par0::raise_pins
 */
PWROWG_DETAIL_NAMESPACE::daqmx_sen_trg_bld_par1
PWROWG_DETAIL_NAMESPACE::daqmx_sen_trg_bld_par0::raise_pins(
        _In_ const parallel_port_pin pins) {
    assert(this->_trigger._impl != nullptr);
    this->_trigger._impl->external_trigger_pins = pins;
    return this->_trigger;
}


/*
 * PWROWG_NAMESPACE::daqmx_sensor_trigger_builder::when_channel
 */
PWROWG_DETAIL_NAMESPACE::daqmx_sen_trg_bld_chan0
PWROWG_NAMESPACE::daqmx_sensor_trigger_builder::when_channel(
        _In_z_ const wchar_t *channel) {
    auto c = convert_string<char>(channel);
    return detail::daqmx_sen_trg_bld_chan0(daqmx_sensor_trigger(), c.c_str());
}


/*
 * PWROWG_NAMESPACE::daqmx_sensor_trigger_builder::when_channel
 */
PWROWG_DETAIL_NAMESPACE::daqmx_sen_trg_bld_chan0
PWROWG_NAMESPACE::daqmx_sensor_trigger_builder::when_channel(
        _In_z_ const char *channel) {
    return detail::daqmx_sen_trg_bld_chan0(daqmx_sensor_trigger(), channel);
}


/*
 * PWROWG_NAMESPACE::daqmx_sensor_trigger_builder::when_parallel_port
 */
PWROWG_DETAIL_NAMESPACE::daqmx_sen_trg_bld_par0
PWROWG_NAMESPACE::daqmx_sensor_trigger_builder::when_parallel_port(
        _In_z_ const wchar_t *path) {
    daqmx_sensor_trigger trigger;
    trigger._impl->external_trigger = parallel_port_trigger(path);
    return detail::daqmx_sen_trg_bld_par0(trigger);
}


/*
 * PWROWG_NAMESPACE::daqmx_sensor_trigger_builder::when_parallel_port
 */
PWROWG_DETAIL_NAMESPACE::daqmx_sen_trg_bld_par0
PWROWG_NAMESPACE::daqmx_sensor_trigger_builder::when_parallel_port(
        _In_z_ const char *path) {
    daqmx_sensor_trigger trigger;
    trigger._impl->external_trigger = parallel_port_trigger(path);
    return detail::daqmx_sen_trg_bld_par0(trigger);
}


/*
 * PWROWG_NAMESPACE::daqmx_sensor_trigger_builder::when_starting
 */
PWROWG_DETAIL_NAMESPACE::daqmx_sen_trg_bld_final0
PWROWG_NAMESPACE::daqmx_sensor_trigger_builder::when_starting(void) {
    return detail::daqmx_sen_trg_bld_final0(daqmx_sensor_trigger());
}
