// <copyright file="rtx_sensor_trigger.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_RTX_SENSOR_TRIGGER_H)
#define _PWROWG_RTX_SENSOR_TRIGGER_H
#pragma once

#include "visus/pwrowg/rtx_trigger.h"


PWROWG_NAMESPACE_BEGIN

// Forward declarations.
namespace detail { struct rtx_sensor_trigger_impl; }


/// <summary>
/// The <see cref="rtx_sensor_trigger" /> class represents a handle for
/// controlling the triggering behaviour of an RTA/RTB oscilloscope used as
/// a power sensor.
/// </summary>
/// <remarks>
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
    /// <param name="path">The VISA path to the oscilloscope to be configured
    /// as the trigger source.</param>
    /// <param name="trigger">The trigger configuration to apply to the
    /// oscilloscope identified by the specified VISA <paramref name="path" />.
    /// </param>
    rtx_sensor_trigger(_In_z_ const char *path, _In_ const rtx_trigger trigger);

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="path">The VISA path to the oscilloscope to be configured
    /// as the trigger source.</param>
    /// <param name="trigger">The trigger configuration to apply to the
    /// oscilloscope identified by the specified VISA <paramref name="path" />.
    /// </param>
    rtx_sensor_trigger(_In_z_ const wchar_t *path,
        _In_ const rtx_trigger trigger);

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
    /// Answer the path the oscilloscope to be configured as the trigger source.
    /// </summary>
    /// <returns>The VISA path to the oscilloscope.</returns>
    _Ret_z_ const char *path(void) const noexcept;

    /// <summary>
    /// Answer the trigger configuration to be applied to the oscilloscope
    /// identified by the specified VISA <see cref="path" />.
    /// </summary>
    /// <returns>The trigger configuration.</returns>
    const rtx_trigger& trigger(void) noexcept;

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

private:

    bool reset(_In_opt_ detail::rtx_sensor_trigger_impl *impl) noexcept;

    detail::rtx_sensor_trigger_impl *_impl;
};

PWROWG_NAMESPACE_END

#endif /*!defined(_PWROWG_RTX_SENSOR_TRIGGER_H) */
