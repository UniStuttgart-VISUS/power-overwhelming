// <copyright file="rtx_sensor_trigger.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_RTX_SENSOR_TRIGGER_H)
#define _PWROWG_RTX_SENSOR_TRIGGER_H
#pragma once

#include "visus/pwrowg/parallel_port_trigger.h"
#include "visus/pwrowg/rtx_acquisition.h"
#include "visus/pwrowg/rtx_trigger.h"


PWROWG_NAMESPACE_BEGIN

// Forward declarations.
namespace detail { struct rtx_sensor; }
namespace detail { struct rtx_sensor_trigger_impl; }
namespace detail { struct rtx_sen_trg_bld_final; }
namespace detail { struct rtx_sen_trg_bld_chan0; }
namespace detail { struct rtx_sen_trg_bld_chan1; }
namespace detail { struct rtx_sen_trg_bld_man0; }
namespace detail { struct rtx_sen_trg_bld_par0; }
namespace detail { struct rtx_sen_trg_bld_par1; }
namespace detail { struct rtx_sen_trg_bld_par2; }
namespace detail { struct rtx_sen_trg_bld_par3; }


/// <summary>
/// The <see cref="rtx_sensor_trigger" /> class represents a handle for
/// controlling the triggering behaviour of an RTA/RTB oscilloscope used as
/// a power sensor.
/// </summary>
/// <remarks>
/// <para>You cannot create useful instances of this class directly. Instead,
/// use the fluent API of <see cref="rtx_sensor_trigger_builder" />.</para>
/// <para>The <see cref="rtx_sensor_trigger" /> is a reference counted object
/// that is shared between the application and the
/// <see cref="detail::rtx_sensor" />. As such, it is immutable, i.e. it can
/// only be configured during construction as the Power Overwhelming framework
/// might asynchronously access its members after the
/// <see cref="sensor_array" /> has been started. It is safe for the application
/// to discard its own instance while the sensor is running if access to the
/// trigger is not needed anymore.</para>
/// <para>The trigger configuration is only relevant if the sensor is not
/// configured to manual triggering via the <see cref="rtx_acquisition_state" />
/// of the <see cref="rtx_instrument_configuration" />. If manual triggering is
/// configured, this object can be used to press the acquisition button of all
/// oscilloscopes used by an <see cref="detail::rtx_sensor" /> from software.
/// </para>
/// <para>All other oscilloscopes used by the sensor that is configured using
/// this object are set to external triggering.</para>
/// </remarks>
class POWER_OVERWHELMING_API rtx_sensor_trigger final {

public:

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    rtx_sensor_trigger(void);

    /// <summary>
    /// Clone <paramref name="other" />.
    /// </summary>
    /// <param name="other">The object to be cloned.</param>
    rtx_sensor_trigger(_In_ const rtx_sensor_trigger& other);

    /// <summary>
    /// Initialise from move.
    /// </summary>
    /// <param name="other">The object to be moved.</param>
    rtx_sensor_trigger(_Inout_ rtx_sensor_trigger&& other) noexcept;

    /// <summary>
    /// Finalises the instance.
    /// </summary>
    inline ~rtx_sensor_trigger(void) noexcept {
        this->reset(nullptr);
    }

    /// <summary>
    /// Triggers the oscilloscope manually and blocks the calling thread until
    /// the oscilloscope has acknowledged the trigger.
    /// </summary>
    /// <remarks>
    /// <para>This method must not be called on moved instances. The
    /// implementation will only assert this in debug builds.</para>
    /// <para>The operation happening here depends on the configuration of the
    /// trigger:</para>
    /// </remarks>
    void acquire(void);

    /// <summary>
    /// Answer the path the oscilloscope to be configured as the trigger source.
    /// </summary>
    /// <returns>The VISA path to the oscilloscope. If this is an empty string,
    /// all instruments should be set up similarly.
    /// </returns>
    _Ret_z_ const char *path(void) const noexcept;

    /// <summary>
    /// Answer the trigger configuration to be applied to the oscilloscope
    /// identified by the specified VISA <see cref="path" />.
    /// </summary>
    /// <returns>The trigger configuration. This might be
    /// <see langword="nullptr "/> if the instrument is to be triggered manually
    /// via a single acquisition button press.</returns>
    _Ret_maybenull_ const rtx_trigger *trigger(void) const noexcept;

    /// <summary>
    /// Assignment.
    /// </summary>
    /// <param name="rhs">The right-hand-side operand.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    rtx_sensor_trigger& operator =(_In_ const rtx_sensor_trigger& rhs);

    /// <summary>
    /// Move assignment.
    /// </summary>
    /// <param name="rhs">The right-hand-side operand.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    rtx_sensor_trigger& operator =(_Inout_ rtx_sensor_trigger&& rhs) noexcept;

    /// <summary>
    /// Answer whether this instance is valid.
    /// </summary>
    /// <returns><see langword="true" /> if this instance is valid, i.e. holds a
    /// valid implementation, <see langword="false" /> otherwise.</returns>
    inline operator bool(void) const noexcept {
        return (this->_impl != nullptr);
    }

private:

    bool reset(_In_opt_ detail::rtx_sensor_trigger_impl *impl) noexcept;

    detail::rtx_sensor_trigger_impl *_impl;

    friend class detail::rtx_sensor;
    friend class detail::rtx_sen_trg_bld_final;
    friend class detail::rtx_sen_trg_bld_chan0;
    friend class detail::rtx_sen_trg_bld_chan1;
    friend class detail::rtx_sen_trg_bld_man0;
    friend class detail::rtx_sen_trg_bld_par0;
    friend class detail::rtx_sen_trg_bld_par1;
    friend class detail::rtx_sen_trg_bld_par2;
    friend class detail::rtx_sen_trg_bld_par3;
    friend class rtx_sensor_trigger_builder;
};

PWROWG_NAMESPACE_END

#endif /*!defined(_PWROWG_RTX_SENSOR_TRIGGER_H) */
