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
class POWER_OVERWHELMING_API rtx_sen_trg_bld_final {

public:

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="trigger">The trigger to be returned by the builder.</param>
    inline rtx_sen_trg_bld_final(_In_ const rtx_sensor_trigger& trigger)
        : _trigger(trigger) { }

    /// <summary>
    /// Finalises the instance.
    /// </summary>
    virtual ~rtx_sen_trg_bld_final(void) noexcept = default;

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
/// for retrieving the trigger. It is the final stage of a builder chain that
/// configures triggers on a channel of the oscilloscope.
/// </summary>
class POWER_OVERWHELMING_API rtx_sen_trg_bld_chan1
        : public rtx_sen_trg_bld_final {

public:

    /// <summary>
    /// Initialise a new instance.
    /// </summary>
    /// <param name="trigger">The trigger to be configured or retrieved.</param>
    inline rtx_sen_trg_bld_chan1(_In_ const rtx_sensor_trigger& trigger)
        : rtx_sen_trg_bld_final(trigger) { }

    /// <summary>
    /// Finalises the instance.
    /// </summary>
    virtual ~rtx_sen_trg_bld_chan1(void) noexcept = default;

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
    rtx_sen_trg_bld_chan1& with_coupling(
        _In_ const rtx_trigger_coupling coupling);

    /// <summary>
    /// Disables the trigger hold-off.
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    rtx_sen_trg_bld_chan1& without_hold_off(void);

    /// <summary>
    /// Sets the trigger hold-off to the specified time span.
    /// </summary>
    /// <param name="time"></param>
    /// <returns></returns>
    rtx_sen_trg_bld_chan1& with_hold_off(_In_z_ const wchar_t *time);

    /// <summary>
    /// Sets the trigger hold-off to the specified time span.
    /// </summary>
    /// <param name="time"></param>
    /// <returns></returns>
    rtx_sen_trg_bld_chan1& with_hold_off(_In_z_ const char *time);
};


/// <summary>
/// This builder configures the mandatory parts of the trigger on an already
/// selected channel, which are the edge and the trigger level. Once this
/// information is provided, the trigger can be used or optional properties
/// can be set via <see cref="rtx_sen_trg_bld_chan1" />.
/// </summary>
class POWER_OVERWHELMING_API rtx_sen_trg_bld_chan0 final {

public:

    /// <summary>
    /// Initialise a new instance.
    /// </summary>
    /// <param name="trigger">The trigger to be configured.</param>
    rtx_sen_trg_bld_chan0(_In_ const rtx_sensor_trigger& trigger);

    /// <summary>
    /// Triggers on the falling edge at the specified <paramref name="level" />.
    /// </summary>
    /// <param name="level">The trigger level.</param>
    /// <returns>A builder that allows for configuring optional parts of the
    /// trigger or to retrieve the final result.</returns>
    rtx_sen_trg_bld_chan1 falls_below(
        _In_ const rtx_quantity& level);

    /// <summary>
    /// Triggers on the falling edge at the specified <paramref name="level" />.
    /// </summary>
    /// <param name="level">The trigger level.</param>
    /// <param name="unit">The unit of the channel.</param>
    /// <returns>A builder that allows for configuring optional parts of the
    /// trigger or to retrieve the final result.</returns>
    rtx_sen_trg_bld_chan1 falls_below(
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
    rtx_sen_trg_bld_chan1 falls_below(
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
    rtx_sen_trg_bld_chan1 passes_through(
        _In_ const rtx_quantity& level);

    /// <summary>
    /// Triggers when the signal passes through the specified
    /// <paramref name="level" /> regardless of the slope.
    /// </summary>
    /// <param name="level">The trigger level.</param>
    /// <param name="unit">The unit of the channel.</param>
    /// <returns>A builder that allows for configuring optional parts of the
    /// trigger or to retrieve the final result.</returns>
    rtx_sen_trg_bld_chan1 passes_through(
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
    rtx_sen_trg_bld_chan1 passes_through(
            _In_ const float level, _In_opt_z_ const char *unit = nullptr) {
        return this->passes_through(rtx_quantity(level, unit));
    }

    /// <summary>
    /// Triggers on the rising edge at the specified <paramref name="level" />.
    /// </summary>
    /// <param name="level">The trigger level.</param>
    /// <returns>A builder that allows for configuring optional parts of the
    /// trigger or to retrieve the final result.</returns>
    rtx_sen_trg_bld_chan1 rises_above(
        _In_ const rtx_quantity& level);

    /// <summary>
    /// Triggers on the rising edge at the specified <paramref name="level" />.
    /// </summary>
    /// <param name="level">The trigger level.</param>
    /// <param name="unit">The unit of the channel.</param>
    /// <returns>A builder that allows for configuring optional parts of the
    /// trigger or to retrieve the final result.</returns>
    rtx_sen_trg_bld_chan1 rises_above(
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
    rtx_sen_trg_bld_chan1 rises_above(
            _In_ const float level, _In_opt_z_ const char *unit = nullptr) {
        return this->rises_above(rtx_quantity(level, unit));
    }

private:

    rtx_sensor_trigger _trigger;
};


/// <summary>
/// The only configuration step for manual triggers.
/// </summary>
class POWER_OVERWHELMING_API rtx_sen_trg_bld_man0 final
        : public rtx_sen_trg_bld_final {

public:

    /// <summary>
    /// The default trigger level for the external trigger signal.
    /// </summary>
    static constexpr auto default_level = 2.5f;

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="trigger">The trigger to be returned by the builder.</param>
    inline rtx_sen_trg_bld_man0(_In_ const rtx_sensor_trigger& trigger)
        : rtx_sen_trg_bld_final(trigger) { }

    /// <summary>
    /// Configures the trigger to be daisy-chained with the other triggers of
    /// the other instruments of the sensor. If this is not set, a single
    /// acquisition will be triggered by &quot;pressing&quot; the button on
    /// each instrument, which will cause time differences between the
    /// measurements. Therefore, it is recommended to daisy chain the
    /// instruments via their external trigger input/output and set this flag.
    /// </summary>
    /// <param name="level">The trigger level for the daisy chain. If this
    /// value is zero or less, It will be forced to the
    /// <see cref="default_level" />.</param>
    /// <returns>The builder of the next stage.</returns>
    rtx_sen_trg_bld_final with_daisy_chain(
        _In_ const float level = default_level);
};


/// <summary>
/// The final stage of building a parallel port trigger, which allows for
/// configuring optional properties that have meaningful default values. It
/// is the final stage of builder chain that configures a parallel port trigger
/// that is measured by a channel of the oscilloscope.
/// </summary>
class POWER_OVERWHELMING_API rtx_sen_trg_bld_par3 final
        : public rtx_sen_trg_bld_chan1 {

public:

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="trigger">The trigger to be modified.</param>
    inline rtx_sen_trg_bld_par3(_In_ const rtx_sensor_trigger& trigger)
        : rtx_sen_trg_bld_chan1(trigger) { }

    /// <summary>
    /// Changes the level at which the parallel port trigger is activated. The
    /// default level of 2.5V should be OK for most applications.
    /// </summary>
    /// <param name="level">The trigger level.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    rtx_sen_trg_bld_par3& at_level(_In_ const rtx_quantity& level);

    /// <summary>
    /// Changes the level at which the parallel port trigger is activated. The
    /// default level of 2.5V should be OK for most applications.
    /// </summary>
    /// <param name="level">The trigger level.</param>
    /// <param name="unit">The unit of the trigger level.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    rtx_sen_trg_bld_par3& at_level(_In_ const float level,
            _In_z_ const wchar_t *unit) {
        return this->at_level(rtx_quantity(level, unit));
    }

    /// <summary>
    /// Changes the level at which the parallel port trigger is activated. The
    /// default level of 2.5V should be OK for most applications.
    /// </summary>
    /// <param name="level">The trigger level.</param>
    /// <param name="unit">The unit of the trigger level.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    rtx_sen_trg_bld_par3& at_level(_In_ const float level,
            _In_z_ const char *unit = nullptr) {
        return this->at_level(rtx_quantity(level, unit));
    }
};


/// <summary>
/// Configures how the parallel port trigger is measured by the oscilloscope.
/// </summary>
class POWER_OVERWHELMING_API rtx_sen_trg_bld_par2 final {

public:

    /// <summary>
    /// Initialise a new instance.
    /// </summary>
    /// <param name="trigger">The trigger to be configured.</param>
    inline rtx_sen_trg_bld_par2(_In_ const rtx_sensor_trigger& trigger)
        : _trigger(trigger) { }

    /// <summary>
    /// Creates a trigger on the specified channel.
    /// </summary>
    /// <param name="channel">The channel to trigger on, which must be the name
    /// of a valid channel of the oscilloscope.</param>
    /// <returns>A builder to configure the type of the trigger.</returns>
    rtx_sen_trg_bld_par3 measured_via_channel(_In_z_ const wchar_t *channel);

    /// <summary>
    /// Creates a trigger on the specified channel.
    /// </summary>
    /// <param name="channel">The channel to trigger on, which must be the name
    /// of a valid channel of the oscilloscope.</param>
    /// <returns>A builder to configure the type of the trigger.</returns>
    rtx_sen_trg_bld_par3 measured_via_channel(_In_z_ const char *channel);

    /// <summary>
    /// Creates a trigger on the specified channel.
    /// </summary>
    /// <param name="channel">The channel to trigger on, which must be the name
    /// of a valid channel of the oscilloscope.</param>
    /// <returns>A builder to configure the type of the trigger.</returns>
    rtx_sen_trg_bld_par3 measured_via_channel(
        _In_ const rtx_trigger::input_type channel);

private:

    rtx_sensor_trigger _trigger;
};


/// <summary>
/// Continues configuring the parallel port trigger.
/// </summary>
class POWER_OVERWHELMING_API rtx_sen_trg_bld_par1 final {

public:

    /// <summary>
    /// The type used to express time spans in milliseconds.
    /// </summary>
    typedef parallel_port_trigger::milliseconds_type milliseconds_type;

    /// <summary>
    /// Initialise a new instance.
    /// </summary>
    /// <param name="trigger">The trigger to be configured.</param>
    inline rtx_sen_trg_bld_par1(_In_ const rtx_sensor_trigger& trigger)
        : _trigger(trigger) { }

    /// <summary>
    /// Sets the time, in milliseconds, the signal on the parallel port will be
    /// active before it is reset. Note that the thread triggering the parallel
    /// port will block for this time span.
    /// </summary>
    /// <param name="duration"></param>
    /// <returns></returns>
    rtx_sen_trg_bld_par2 for_duration(_In_ const milliseconds_type duration);

    /// <summary>
    /// Sets the time, in the specified duration type, the signal on the parallel
    /// port will be active before it is reset. Note that the thread triggering
    /// the parallel port will block for this time span.
    /// </summary>
    /// <typeparam name="TRep"></typeparam>
    /// <typeparam name="TRatio"></typeparam>
    /// <param name="duration"></param>
    /// <returns></returns>
    template<class TRep, class TRatio> inline rtx_sen_trg_bld_par2 for_duration(
            _In_ const std::chrono::duration<TRep, TRatio>& duration) {
        using std::chrono::duration_cast;
        typedef std::chrono::duration<milliseconds_type, std::milli> millis;
        return this->for_duration(duration_cast<millis>(duration).count());
    }

private:

    rtx_sensor_trigger _trigger;
};


/// <summary>
/// Configures the details of the parallel port trigger.
/// </summary>
class POWER_OVERWHELMING_API rtx_sen_trg_bld_par0 final {

public:

    /// <summary>
    /// Initialise a new instance.
    /// </summary>
    /// <param name="trigger">The trigger to be configured.</param>
    rtx_sen_trg_bld_par0(_In_ const rtx_sensor_trigger& trigger);

    /// <summary>
    /// Creates a trigger on the specified channel.
    /// </summary>
    /// <param name="channel">The channel to trigger on, which must be the name
    /// of a valid channel of the oscilloscope.</param>
    /// <returns>A builder to configure the type of the trigger.</returns>
    rtx_sen_trg_bld_par3 measured_via_channel(_In_z_ const wchar_t *channel);

    /// <summary>
    /// Creates a trigger on the specified channel.
    /// </summary>
    /// <param name="channel">The channel to trigger on, which must be the name
    /// of a valid channel of the oscilloscope.</param>
    /// <returns>A builder to configure the type of the trigger.</returns>
    rtx_sen_trg_bld_par3 measured_via_channel(_In_z_ const char *channel);

    /// <summary>
    /// Creates a trigger on the specified channel.
    /// </summary>
    /// <param name="channel">The channel to trigger on, which must be the name
    /// of a valid channel of the oscilloscope.</param>
    /// <returns>A builder to configure the type of the trigger.</returns>
    rtx_sen_trg_bld_par3 measured_via_channel(
        _In_ const rtx_trigger::input_type channel);

    /// <summary>
    /// Creates a trigger on the external channel.
    /// </summary>
    /// <returns>A builder to configure the type of the trigger.</returns>
    rtx_sen_trg_bld_par3 measured_via_external(void);

    /// <summary>
    /// Tells the framework to only use the specified pins of the parallel port
    /// trigger. If not specified, all data pins will be used.
    /// </summary>
    /// <param name="pins">The pins to be raised. This parameter defaults to all
    /// data pins.</param>
    /// <returns>A builder for the next stage.</returns>
    rtx_sen_trg_bld_par1 raise_pins(_In_ const parallel_port_pin pins
        = parallel_port_pin::data);

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

    /// <summary>
    /// Creates a new builder for triggering all instruments similarly.
    /// </summary>
    /// <returns>A builder for configuring the trigger.</returns>
    static rtx_sensor_trigger_builder for_all(void);

    /// <summary>
    /// Creates a new builder for the first instrument matching the given query.
    /// </summary>
    /// <param name="query">The query to find the instrument, which should
    /// select R &amp; S RTA/RTB oscilloscopes.</param>
    /// <returns>A builder for configuring the trigger.</returns>
    /// <exception cref="std::invalid_argument">If no device matches the given
    /// <paramref name="query" />.</exception>
    /// <exception cref="std::system_error">If the connection to the device
    /// could not be established.</exception>
    static rtx_sensor_trigger_builder for_first(
        _In_opt_z_ const wchar_t *query);

    /// <summary>
    /// Creates a new builder for the first instrument matching the given query.
    /// </summary>
    /// <param name="query">The query to find the instrument, which should
    /// select R &amp; S RTA/RTB oscilloscopes.</param>
    /// <returns>A builder for configuring the trigger.</returns>
    /// <exception cref="std::invalid_argument">If no device matches the given
    /// <paramref name="query" />.</exception>
    /// <exception cref="std::system_error">If the connection to the device
    /// could not be established.</exception>
    static rtx_sensor_trigger_builder for_first(
        _In_opt_z_ const char *query = nullptr);

    /// <summary>
    /// Creates a new builder for triggering the device that has the given name
    /// configured. The operation will fail if the name does not uniquely match.
    /// </summary>
    /// <param name="name">The name of the device. There must be exactly one
    /// device with this name attached to the machine.</param>
    /// <param name="timeout">The time, in milliseconds, for device discovery.
    /// </param>
    /// <returns>A builder for configuring the trigger.</returns>
    /// <exception cref="std::invalid_argument">If <paramref name="name" /> is
    /// <see langword="nullptr" />, or if the name does not match a unique
    /// device.</exception>
    /// <exception cref="std::system_error">If the connection to the device
    /// could not be established.</exception>
    static rtx_sensor_trigger_builder for_name(_In_z_ const wchar_t *name,
        _In_ const std::int32_t timeout = 5000);

    /// <summary>
    /// Creates a new builder for triggering the device that has the given name
    /// configured. The operation will fail if the name does not uniquely match.
    /// </summary>
    /// <param name="name">The name of the device. There must be exactly one
    /// device with this name attached to the machine.</param>
    /// <param name="timeout">The time, in milliseconds, for device discovery.
    /// </param>
    /// <returns>A builder for configuring the trigger.</returns>
    /// <exception cref="std::invalid_argument">If <paramref name="name" /> is
    /// <see langword="nullptr" />, or if the name does not match a unique
    /// device.</exception>
    /// <exception cref="std::system_error">If the connection to the device
    /// could not be established.</exception>
    static rtx_sensor_trigger_builder for_name(_In_z_ const char *name,
        _In_ const std::int32_t timeout = 5000);

    /// <summary>
    /// Creates a new builder for triggering the device identified by the given
    /// VISA path.
    /// </summary>
    /// <param name="path">The VISA path to the instrument used to trigger the
    /// measurement.</param>
    /// <returns>A builder for configuring the trigger.</returns>
    /// <exception cref="std::invalid_argument">If <paramref name="path" /> is
    /// <see langword="nullptr" />.</exception>
    static rtx_sensor_trigger_builder for_path(_In_z_ const wchar_t *path);

    /// <summary>
    /// Creates a new builder for triggering the device identified by the given
    /// VISA path.
    /// </summary>
    /// <param name="path">The VISA path to the instrument used to trigger the
    /// measurement.</param>
    /// <returns>A builder for configuring the trigger.</returns>
    /// <exception cref="std::invalid_argument">If <paramref name="path" /> is
    /// <see langword="nullptr" />.</exception>
    static rtx_sensor_trigger_builder for_path(_In_z_ const char *path);

    /// <summary>
    /// Creates a new builder for triggering the device identified by the given
    /// VISA path.
    /// </summary>
    /// <param name="path">The VISA path to the instrument used to trigger the
    /// measurement.</param>
    /// <returns>A builder for configuring the trigger.</returns>
    template<class TChar, class TTraits, class TAlloc>
    static rtx_sensor_trigger_builder for_path(
            _In_ const std::basic_string<TChar, TTraits, TAlloc>& path) {
        return rtx_sensor_trigger_builder::for_path(path.c_str());
    }

    /// <summary>
    /// Creates a new builder for triggering the instrument with the given
    /// serial number. There must be exactly one device with matching the query
    /// for the serial number for the method to succeed.
    /// </summary>
    /// <param name="serial">The serial number to look for.</param>
    /// <returns>A builder for configuring the trigger.</returns>
    /// <exception cref="std::invalid_argument">If <paramref name="serial" />
    /// is <see langword="nullptr" />, or if no unique instrument was found.
    /// </exception>
    static rtx_sensor_trigger_builder for_serial(_In_z_ const wchar_t *serial);

    /// <summary>
    /// Creates a new builder for triggering the instrument with the given
    /// serial number. There must be exactly one device with matching the query
    /// for the serial number for the method to succeed.
    /// </summary>
    /// <param name="serial">The serial number to look for.</param>
    /// <returns>A builder for configuring the trigger.</returns>
    /// <exception cref="std::invalid_argument">If <paramref name="serial" />
    /// is <see langword="nullptr" />, or if no unique instrument was found.
    /// </exception>
    static rtx_sensor_trigger_builder for_serial(_In_z_ const char *serial);

    /// <summary>
    /// Creates a trigger on the specified channel.
    /// </summary>
    /// <param name="channel">The channel to trigger on, which must be the name
    /// of a valid channel of the oscilloscope.</param>
    /// <returns>A builder to configure the type of the trigger.</returns>
    detail::rtx_sen_trg_bld_chan0 when_channel(
        _In_z_ const wchar_t *channel);

    /// <summary>
    /// Creates a trigger on the specified channel.
    /// </summary>
    /// <param name="channel">The channel to trigger on, which must be the name
    /// of a valid channel of the oscilloscope.</param>
    /// <returns>A builder to configure the type of the trigger.</returns>
    detail::rtx_sen_trg_bld_chan0 when_channel(
        _In_z_ const char *channel);

    /// <summary>
    /// Creates a trigger on the specified channel.
    /// </summary>
    /// <param name="channel">The channel to trigger on, which must be the name
    /// of a valid channel of the oscilloscope.</param>
    /// <returns>A builder to configure the type of the trigger.</returns>
    detail::rtx_sen_trg_bld_chan0 when_channel(
        _In_ const rtx_trigger::input_type channel);

    /// <summary>
    /// Starts configuring a trigger that is controlled by a parallel port on
    /// the machine.
    /// </summary>
    /// <param name="path">The path of the parallel port.</param>
    /// <returns>A builder to configure the parallel port trigger.</returns>
    detail::rtx_sen_trg_bld_par0 when_parallel_port(
        _In_z_ const wchar_t *path);

    /// <summary>
    /// Starts configuring a trigger that is controlled by a parallel port on
    /// the machine.
    /// </summary>
    /// <param name="path">The path of the parallel port.</param>
    /// <returns>A builder to configure the parallel port trigger.</returns>
    detail::rtx_sen_trg_bld_par0 when_parallel_port(
        _In_z_ const char *path);

    /// <summary>
    /// Creates a trigger that must be triggered manually via the
    /// <see ref="rtx_sensor_trigger" /> interface returned by the builder.
    /// </summary>
    /// <returns>A builder for a manual trigger.</returns>
    detail::rtx_sen_trg_bld_man0 when_software_triggered(void) noexcept;

    /// <summary>
    /// Applies the given trigger.
    /// </summary>
    /// <param name="trigger">An object describing an oscilloscope trigger.
    /// </param>
    /// <returns>A builder for a manually configured trigger.</returns>
    detail::rtx_sen_trg_bld_final with_trigger(
        _In_ const rtx_trigger& trigger) noexcept;

private:

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    inline rtx_sensor_trigger_builder(void) = default;

    rtx_sensor_trigger _trigger;
};

PWROWG_NAMESPACE_END

#endif /*!defined(_PWROWG_RTX_SENSOR_TRIGGER_BUILDER_H) */
