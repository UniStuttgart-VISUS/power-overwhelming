// <copyright file="daqmx_sensor_trigger_builder.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_DAQMX_SENSOR_TRIGGER_BUILDER_H)
#define _PWROWG_DAQMX_SENSOR_TRIGGER_BUILDER_H
#pragma once

#include <chrono>

#include "visus/pwrowg/daqmx_sensor_trigger.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// The last step in the builder stage which only allows for retrieving the
/// final object.
/// </summary>
class POWER_OVERWHELMING_API daqmx_sen_trg_bld_final {

public:

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="trigger">The trigger to be returned by the builder.</param>
    inline daqmx_sen_trg_bld_final(_In_ const daqmx_sensor_trigger& trigger)
        : _trigger(trigger) { }

    /// <summary>
    /// Finalises the instance.
    /// </summary>
    virtual ~daqmx_sen_trg_bld_final(void) noexcept = default;

    /// <summary>
    /// Creates the trigger as configured by the previous steps.
    /// </summary>
    /// <returns>The trigger created using the builder.</returns>
    inline const daqmx_sensor_trigger& build(void) noexcept {
        return this->_trigger;
    }

protected:

    daqmx_sensor_trigger _trigger;
};


/// <summary>
/// This builder configures the analog trigger level.
/// </summary>
class POWER_OVERWHELMING_API daqmx_sen_trg_bld_chan0 final {

public:

    /// <summary>
    /// Initialise a new instance.
    /// </summary>
    /// <param name="trigger">The trigger to be configured.</param>
    /// <param name="channel">The channel to trigger on.</param>
    daqmx_sen_trg_bld_chan0(_In_ const daqmx_sensor_trigger& trigger,
        _In_ const char *channel);

    /// <summary>
    /// Finalises the instance.
    /// </summary>
    virtual ~daqmx_sen_trg_bld_chan0(void) noexcept = default;

    /// <summary>
    /// Configures an analog edge trigger falling below the specified
    /// <paramref name="level" /> in Volts.
    /// </summary>
    /// <param name="level">The trigger level in Volts.</param>
    /// <returns>A builder instance for configuring the next step.</returns>
    daqmx_sen_trg_bld_final is_falling_below(_In_ const double level);

    /// <summary>
    /// Configures an analog edge trigger rising above the specified
    /// <paramref name="level" /> in Volts.
    /// </summary>
    /// <param name="level">The trigger level in Volts.</param>
    /// <returns>A builder instance for configuring the next step.</returns>
    daqmx_sen_trg_bld_final is_rising_above(_In_ const double level);

private:

    blob _channel;
    daqmx_sensor_trigger _trigger;
};


/// <summary>
/// Allows for adjusting the trigger level or keeping the default level at a
/// rising edge.
/// </summary>
class POWER_OVERWHELMING_API daqmx_sen_trg_bld_par3 final
        : public daqmx_sen_trg_bld_final {

public:

    /// <summary>
    /// Initialise a new instance.
    /// </summary>
    /// <param name="trigger">The trigger to be configured.</param>
    /// <par,am name="channel">The channel to trigger on.</param>
    daqmx_sen_trg_bld_par3(_In_ const daqmx_sensor_trigger& trigger,
        _In_ const char *channel);

    /// <summary>
    /// Configures an analog edge trigger rising above the specified
    /// <paramref name="level" /> in Volts.
    /// </summary>
    /// <param name="level">The trigger level in Volts.</param>
    /// <returns>A builder instance for configuring the next step.</returns>
    daqmx_sen_trg_bld_final rising_above(_In_ const double level);
};


/// <summary>
/// Configures how the parallel port trigger is measured by the DAQ.
/// </summary>
class POWER_OVERWHELMING_API daqmx_sen_trg_bld_par2 final {

public:

    /// <summary>
    /// Initialise a new instance.
    /// </summary>
    /// <param name="trigger">The trigger to be configured.</param>
    inline daqmx_sen_trg_bld_par2(_In_ const daqmx_sensor_trigger& trigger)
        : _trigger(trigger) { }

    /// <summary>
    /// Creates a trigger on the specified channel.
    /// </summary>
    /// <param name="channel">The channel to trigger on, which must be the name
    /// of a valid channel of any of the connected DAQs.</param>
    /// <returns>A builder to configure the type of the trigger.</returns>
    daqmx_sen_trg_bld_par3 measured_via_channel(_In_z_ const wchar_t *channel);

    /// <summary>
    /// Creates a trigger on the specified channel.
    /// </summary>
    /// <param name="channel">The channel to trigger on, which must be the name
    /// of a valid channel of any of the connected DAQs.</param>
    /// <returns>A builder to configure the type of the trigger.</returns>
    daqmx_sen_trg_bld_par3 measured_via_channel(_In_z_ const char *channel);

private:

    daqmx_sensor_trigger _trigger;
};


/// <summary>
/// Continues configuring the parallel port trigger.
/// </summary>
class POWER_OVERWHELMING_API daqmx_sen_trg_bld_par1 final {

public:

    /// <summary>
    /// The type used to express time spans in milliseconds.
    /// </summary>
    typedef parallel_port_trigger::milliseconds_type milliseconds_type;

    /// <summary>
    /// Initialise a new instance.
    /// </summary>
    /// <param name="trigger">The trigger to be configured.</param>
    inline daqmx_sen_trg_bld_par1(_In_ const daqmx_sensor_trigger& trigger)
        : _trigger(trigger) { }

    /// <summary>
    /// Sets the time, in milliseconds, the signal on the parallel port will be
    /// active before it is reset. Note that the thread triggering the parallel
    /// port will block for this time span.
    /// </summary>
    /// <param name="duration"></param>
    /// <returns></returns>
    daqmx_sen_trg_bld_par2 for_duration(_In_ const milliseconds_type duration);

    /// <summary>
    /// Sets the time, in the specified duration type, the signal on the parallel
    /// port will be active before it is reset. Note that the thread triggering
    /// the parallel port will block for this time span.
    /// </summary>
    /// <typeparam name="TRep"></typeparam>
    /// <typeparam name="TRatio"></typeparam>
    /// <param name="duration"></param>
    /// <returns></returns>
    template<class TRep, class TRatio>
    inline daqmx_sen_trg_bld_par2 for_duration(
            _In_ const std::chrono::duration<TRep, TRatio>& duration) {
        using std::chrono::duration_cast;
        typedef std::chrono::duration<milliseconds_type, std::milli> millis;
        return this->for_duration(duration_cast<millis>(duration).count());
    }

private:

    daqmx_sensor_trigger _trigger;
};


/// <summary>
/// Configures the details of the parallel port trigger.
/// </summary>
class POWER_OVERWHELMING_API daqmx_sen_trg_bld_par0 final {

public:

    /// <summary>
    /// Initialise a new instance.
    /// </summary>
    /// <param name="trigger">The trigger to be configured.</param>
    inline daqmx_sen_trg_bld_par0(_In_ const daqmx_sensor_trigger& trigger)
        : _trigger(trigger) { }

    /// <summary>
    /// Creates a trigger on the specified channel.
    /// </summary>
    /// <param name="channel">The channel to trigger on, which must be the name
    /// of a valid channel of any of the connected DAQs.</param>
    /// <returns>A builder to configure the type of the trigger.</returns>
    daqmx_sen_trg_bld_par3 measured_via_channel(_In_z_ const wchar_t *channel);

    /// <summary>3
    /// Creates a trigger on the specified channel.
    /// </summary>
    /// <param name="channel">The channel to trigger on, which must be the name
    /// of a valid channel of any of the connected DAQs.</param>
    /// <returns>A builder to configure the type of the trigger.</returns>
    daqmx_sen_trg_bld_par3 measured_via_channel(_In_z_ const char *channel);

    /// <summary>
    /// Tells the framework to only use the specified pins of the parallel port
    /// trigger. If not specified, all data pins will be used.
    /// </summary>
    /// <param name="pins">The pins to be raised. This parameter defaults to all
    /// data pins.</param>
    /// <returns>A builder for the next stage.</returns>
    daqmx_sen_trg_bld_par1 raise_pins(_In_ const parallel_port_pin pins
        = parallel_port_pin::data);

private:

    daqmx_sensor_trigger _trigger;
};

PWROWG_DETAIL_NAMESPACE_END


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// A fluent builder for <see cref="daqmx_sensor_trigger" />s.
/// </summary>
class POWER_OVERWHELMING_API daqmx_sensor_trigger_builder final {

public:

    /// <summary>
    /// Creates a trigger on the specified channel.
    /// </summary>
    /// <param name="channel">The channel to trigger on, which must be the name
    /// of a valid channel of a NI-DAQmx device connected to the machine.</param>
    /// <returns>A builder to configure the type of the trigger.</returns>
    detail::daqmx_sen_trg_bld_chan0 when_channel(_In_z_ const wchar_t *channel);

    /// <summary>
    /// Creates a trigger on the specified channel.
    /// </summary>
    /// <param name="channel">The channel to trigger on, which must be the name
    /// of a valid channel of a NI-DAQmx device connected to the machine.</param>
    /// <returns>A builder to configure the type of the trigger.</returns>
    detail::daqmx_sen_trg_bld_chan0 when_channel(_In_z_ const char *channel);

    /// <summary>
    /// Starts configuring a trigger that is controlled by a parallel port on
    /// the machine.
    /// </summary>
    /// <param name="path">The path of the parallel port.</param>
    /// <returns>A builder to configure the parallel port trigger.</returns>
    detail::daqmx_sen_trg_bld_par0 when_parallel_port(
        _In_z_ const wchar_t *path);

    /// <summary>
    /// Starts configuring a trigger that is controlled by a parallel port on
    /// the machine.
    /// </summary>
    /// <param name="path">The path of the parallel port.</param>
    /// <returns>A builder to configure the parallel port trigger.</returns>
    detail::daqmx_sen_trg_bld_par0 when_parallel_port(
        _In_z_ const char *path);

    /// <summary>
    /// Configures the sensor to trigger as soon as the sensor array is started.
    /// </summary>
    /// <returns>A builder for an auto-start trigger.</returns>
    detail::daqmx_sen_trg_bld_final when_starting(void);
};

PWROWG_NAMESPACE_END

#endif /*!defined(_PWROWG_DAQMX_SENSOR_TRIGGER_BUILDER_H) */
