// <copyright file="rtx_sensor_trigger_builder.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_RTX_SENSOR_TRIGGER_BUILDER_H)
#define _PWROWG_RTX_SENSOR_TRIGGER_BUILDER_H
#pragma once

#include <chrono>

#include "visus/pwrowg/rtx_sensor_trigger.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// The last step in the builder stage which only allows for retrieving the
/// final object.
/// </summary>
class POWER_OVERWHELMING_API rtx_sensor_trg_build_final {

public:

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="trigger">The trigger to be returned by the builder.</param>
    rtx_sensor_trg_build_final(_In_ const rtx_sensor_trigger& trigger)
        : _trigger(trigger) { }

    /// <summary>
    /// Creates the trigger as configured by the previous steps.
    /// </summary>
    /// <returns>The trigger created using the builder.</returns>
    inline const rtx_sensor_trigger& build(void) noexcept {
        return this->_trigger;
    }

protected:

    rtx_sensor_trigger _trigger;
};


/// <summary>
/// This builder allows for customising optional parts of a channel trigger, or
/// for retrieving the trigger.
/// </summary>
class POWER_OVERWHELMING_API rtx_sensor_trg_build_chan_final final
        : public rtx_sensor_trg_build_final {

public:

    /// <summary>
    /// Initialise a new instance.
    /// </summary>
    /// <param name="trigger">The trigger to be configured or retrieved.</param>
    rtx_sensor_trg_build_chan_final(_In_ const rtx_sensor_trigger& trigger)
        : rtx_sensor_trg_build_final(trigger) { }


    /// <summary>
    /// Creates the trigger as configured by the previous steps.
    /// </summary>
    /// <returns>The trigger created using the builder.</returns>
    inline const rtx_sensor_trigger& build(void) noexcept {
        return this->_trigger;
    }

    /// <summary>
    /// Sets the trigger coupling to the specified value.
    /// </summary>
    /// <param name="coupling"></param>
    /// <returns></returns>
    rtx_sensor_trg_build_chan_final& with_coupling(
        _In_ const rtx_trigger_coupling coupling);

    /// <summary>
    /// Disables the trigger hold-off.
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    rtx_sensor_trg_build_chan_final& without_hold_off(void);

    /// <summary>
    /// Sets the trigger hold-off to the specified time span.
    /// </summary>
    /// <param name="time"></param>
    /// <returns></returns>
    rtx_sensor_trg_build_chan_final& with_hold_off(_In_z_ const wchar_t *time);

    /// <summary>
    /// Sets the trigger hold-off to the specified time span.
    /// </summary>
    /// <param name="time"></param>
    /// <returns></returns>
    rtx_sensor_trg_build_chan_final& with_hold_off(_In_z_ const char *time);
};


/// <summary>
/// This builder configures the mandatory parts of the trigger on an already
/// selected channel, which are the edge and the trigger level. Once this
/// information is provided, the trigger can be used or optional properties
/// can be set via <see cref="rtx_sensor_trg_build_chan_final" />.
/// </summary>
class POWER_OVERWHELMING_API rtx_sensor_trg_build_chan final {

public:

    /// <summary>
    /// Initialise a new instance.
    /// </summary>
    /// <param name="trigger">The trigger to be configured.</param>
    rtx_sensor_trg_build_chan(_In_ const rtx_sensor_trigger& trigger)
        : _trigger(trigger) { }

    /// <summary>
    /// Triggers on the falling edge at the specified <paramref name="level" />.
    /// </summary>
    /// <param name="level">The trigger level.</param>
    /// <returns>A builder that allows for configuring optional parts of the
    /// trigger or to retrieve the final result.</returns>
    rtx_sensor_trg_build_chan_final falls_below(
        _In_ const rtx_quantity& level);

    /// <summary>
    /// Triggers on the falling edge at the specified <paramref name="level" />.
    /// </summary>
    /// <param name="level">The trigger level.</param>
    /// <param name="unit">The unit of the channel.</param>
    /// <returns>A builder that allows for configuring optional parts of the
    /// trigger or to retrieve the final result.</returns>
    rtx_sensor_trg_build_chan_final falls_below(
            _In_ const float level, _In_z_ const wchar_t *unit) {
        return this->falls_below(rtx_quantity(level, unit));
    }

    /// <summary>
    /// Triggers on the falling edge at the specified <paramref name="level" />.
    /// </summary>
    /// <param name="level">The trigger level.</param>
    /// <param name="unit">The unit of the channel.</param>
    /// <returns>A builder that allows for configuring optional parts of the
    /// trigger or to retrieve the final result.</returns>
    rtx_sensor_trg_build_chan_final falls_below(
            _In_ const float level, _In_opt_z_ const char *unit = nullptr) {
        return this->falls_below(rtx_quantity(level, unit));
    }

    /// <summary>
    /// Triggers when the signal passes through the specified
    /// <paramref name="level" /> regardless of the slope.
    /// </summary>
    /// <param name="level">The trigger level.</param>
    /// <returns>A builder that allows for configuring optional parts of the
    /// trigger or to retrieve the final result.</returns>
    rtx_sensor_trg_build_chan_final passes_through(
        _In_ const rtx_quantity& level);

    /// <summary>
    /// Triggers when the signal passes through the specified
    /// <paramref name="level" /> regardless of the slope.
    /// </summary>
    /// <param name="level">The trigger level.</param>
    /// <param name="unit">The unit of the channel.</param>
    /// <returns>A builder that allows for configuring optional parts of the
    /// trigger or to retrieve the final result.</returns>
    rtx_sensor_trg_build_chan_final passes_through(
            _In_ const float level, _In_z_ const wchar_t *unit) {
        return this->passes_through(rtx_quantity(level, unit));
    }

    /// <summary>
    /// Triggers when the signal passes through the specified
    /// <paramref name="level" /> regardless of the slope.
    /// </summary>
    /// <param name="level">The trigger level.</param>
    /// <param name="unit">The unit of the channel.</param>
    /// <returns>A builder that allows for configuring optional parts of the
    /// trigger or to retrieve the final result.</returns>
    rtx_sensor_trg_build_chan_final passes_through(
            _In_ const float level, _In_opt_z_ const char *unit = nullptr) {
        return this->passes_through(rtx_quantity(level, unit));
    }

    /// <summary>
    /// Triggers on the rising edge at the specified <paramref name="level" />.
    /// </summary>
    /// <param name="level">The trigger level.</param>
    /// <returns>A builder that allows for configuring optional parts of the
    /// trigger or to retrieve the final result.</returns>
    rtx_sensor_trg_build_chan_final rises_above(
        _In_ const rtx_quantity& level);

    /// <summary>
    /// Triggers on the rising edge at the specified <paramref name="level" />.
    /// </summary>
    /// <param name="level">The trigger level.</param>
    /// <param name="unit">The unit of the channel.</param>
    /// <returns>A builder that allows for configuring optional parts of the
    /// trigger or to retrieve the final result.</returns>
    rtx_sensor_trg_build_chan_final rises_above(
            _In_ const float level, _In_z_ const wchar_t *unit) {
        return this->rises_above(rtx_quantity(level, unit));
    }

    /// <summary>
    /// Triggers on the rising edge at the specified <paramref name="level" />.
    /// </summary>
    /// <param name="level">The trigger level.</param>
    /// <param name="unit">The unit of the channel.</param>
    /// <returns>A builder that allows for configuring optional parts of the
    /// trigger or to retrieve the final result.</returns>
    rtx_sensor_trg_build_chan_final rises_above(
            _In_ const float level, _In_opt_z_ const char *unit = nullptr) {
        return this->rises_above(rtx_quantity(level, unit));
    }

private:

    rtx_sensor_trigger _trigger;
};


/// <summary>
/// Configures the details of the parallel port trigger.
/// </summary>
class POWER_OVERWHELMING_API rtx_sensor_trg_build_par final {

public:

    /// <summary>
    /// The type used to express time spans in milliseconds.
    /// </summary>
    typedef parallel_port_trigger::milliseconds_type milliseconds_type;

    /// <summary>
    /// Initialise a new instance.
    /// </summary>
    /// <param name="trigger">The trigger to be configured.</param>
    rtx_sensor_trg_build_par(_In_ const rtx_sensor_trigger& trigger)
        : _trigger(trigger) { }

    /// <summary>
    /// Creates a trigger on the specified channel.
    /// </summary>
    /// <param name="channel">The channel to trigger on, which must be the name
    /// of a valid channel of the oscilloscope.</param>
    /// <returns>A builder to configure the type of the trigger.</returns>
    detail::rtx_sensor_trg_build_chan_final measured_via_channel(
        _In_z_ const wchar_t *channel);

    /// <summary>
    /// Creates a trigger on the specified channel.
    /// </summary>
    /// <param name="channel">The channel to trigger on, which must be the name
    /// of a valid channel of the oscilloscope.</param>
    /// <returns>A builder to configure the type of the trigger.</returns>
    detail::rtx_sensor_trg_build_chan_final measured_via_channel(
        _In_z_ const char *channel);

    /// <summary>
    /// Creates a trigger on the specified channel.
    /// </summary>
    /// <param name="channel">The channel to trigger on, which must be the name
    /// of a valid channel of the oscilloscope.</param>
    /// <returns>A builder to configure the type of the trigger.</returns>
    detail::rtx_sensor_trg_build_chan_final measured_via_channel(
        _In_ const rtx_trigger::input_type channel);

    /// <summary>
    /// Sets the time, in milliseconds, the signal on the parallel port will be
    /// active before it is reset. Note that the thread triggering the parallel
    /// port will block for this time span.
    /// </summary>
    /// <param name="duration"></param>
    /// <returns></returns>
    rtx_sensor_trg_build_par& raised_for(_In_ const milliseconds_type duration);

    /// <summary>
    /// Sets the time, in the specified duration type, the signal on the parallel
    /// port will be active before it is reset. Note that the thread triggering
    /// the parallel port will block for this time span.
    /// </summary>
    /// <typeparam name="TRep"></typeparam>
    /// <typeparam name="TRatio"></typeparam>
    /// <param name="duration"></param>
    /// <returns></returns>
    template<class TRep, class TRatio> rtx_sensor_trg_build_par& raised_for(
            _In_ const std::chrono::duration<TRep, TRatio>& duration) {
        using std::chrono::duration_cast;
        typedef std::chrono::duration<milliseconds_type, std::milli> millis;
        return this->raised_for(duration_cast<millis>(duration).count());
    }

    /// <summary>
    /// Tells the framework to only use the specified pins of the parallel port
    /// trigger. If not specified, all data pins will be used.
    /// </summary>
    /// <param name="pins"></param>
    /// <returns></returns>
    rtx_sensor_trg_build_par& use_pins(_In_ const parallel_port_pin pins);

private:

    rtx_sensor_trigger _trigger;

};

PWROWG_DETAIL_NAMESPACE_END


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// A fluent builder for <see cref="rtx_sensor_trigger" />s.
/// </summary>
class POWER_OVERWHELMING_API rtx_sensor_trigger_builder final {

public:

    static rtx_sensor_trigger_builder for_path(_In_z_ const wchar_t *path);

    /// <summary>
    /// Creates a new builder for triggering the device identified by the given
    /// VISA path.
    /// </summary>
    /// <param name="path"></param>
    /// <returns></returns>
    /// <exception cref="std::invalid_argument">If <paramref name="path" /> is
    /// <see langword="nullptr" />.</exception>
    static rtx_sensor_trigger_builder for_path(_In_z_ const char *path);

    /// <summary>
    /// Creates a trigger on the specified channel.
    /// </summary>
    /// <param name="channel">The channel to trigger on, which must be the name
    /// of a valid channel of the oscilloscope.</param>
    /// <returns>A builder to configure the type of the trigger.</returns>
    detail::rtx_sensor_trg_build_chan when_channel(
        _In_z_ const wchar_t *channel);

    /// <summary>
    /// Creates a trigger on the specified channel.
    /// </summary>
    /// <param name="channel">The channel to trigger on, which must be the name
    /// of a valid channel of the oscilloscope.</param>
    /// <returns>A builder to configure the type of the trigger.</returns>
    detail::rtx_sensor_trg_build_chan when_channel(
        _In_z_ const char *channel);

    /// <summary>
    /// Creates a trigger on the specified channel.
    /// </summary>
    /// <param name="channel">The channel to trigger on, which must be the name
    /// of a valid channel of the oscilloscope.</param>
    /// <returns>A builder to configure the type of the trigger.</returns>
    detail::rtx_sensor_trg_build_chan when_channel(
        _In_ const rtx_trigger::input_type channel);

    /// <summary>
    /// Starts configuring a trigger that is controlled by a parallel port on
    /// the machine.
    /// </summary>
    /// <param name="path">The path of the parallel port.</param>
    /// <returns>A builder to configure the parallel port trigger.</returns>
    detail::rtx_sensor_trg_build_par when_parallel_port(
        _In_z_ const wchar_t *path);

    /// <summary>
    /// Starts configuring a trigger that is controlled by a parallel port on
    /// the machine.
    /// </summary>
    /// <param name="path">The path of the parallel port.</param>
    /// <returns>A builder to configure the parallel port trigger.</returns>
    detail::rtx_sensor_trg_build_par when_parallel_port(
        _In_z_ const char *path);

    /// <summary>
    /// Creates a trigger that must be triggered manually via the
    /// <see ref="rtx_sensor_trigger" /> interface returned by the builder.
    /// </summary>
    /// <returns>A builder for a manual trigger.</returns>
    detail::rtx_sensor_trg_build_final when_software_triggered(void) noexcept;

private:

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    inline rtx_sensor_trigger_builder(void) = default;

    rtx_sensor_trigger _trigger;
};

PWROWG_NAMESPACE_END

#endif /*!defined(_PWROWG_RTX_SENSOR_TRIGGER_BUILDER_H) */
