// <copyright file="rtx_sensor_state.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_RTX_SENSOR_STATE_H)
#define _PWROWG_RTX_SENSOR_STATE_H
#pragma once

#include <atomic>
#include <cinttypes>

#include "visus/pwrowg/api.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Tracks the state of the <see cref="rtx_sensor" />'s worker thread and the
/// <see cref="rtx_sensor_trigger" /> connected to the sensor.
/// </summary>
enum class rtx_sensor_state : std::uint32_t {

    /// <summary>
    /// The sensor is running and the worker thread should do nothing but wait
    /// for the next event.
    /// </summary>
    running = 0x00000000,

    /// <summary>
    /// The sensor has requested the worker thread to exit. No other state
    /// changes can be requested after this flag has been set.
    /// </summary>
    stop = 0x00000001,

    /// <summary>
    /// Indicates that the worker thread should manually trigger a single
    /// acquisition on the instrument(s).
    /// </summary>
    trigger = 0x00000002,

    /// <summary>
    /// Indicates that the instrument is busy retrieving the measurement data.
    /// The instrument must not be manipulated by any other thread while this
    /// flag is set.
    /// </summary>
    busy = 0x00000004
};


/// <summary>
/// Checks whether all bits of <paramref name="check" /> are set in
/// <paramref name="state" />.
/// </summary>
/// <param name="state"></param>
/// <param name="check"></param>
/// <returns></returns>
inline constexpr bool check_state(
        _In_ const rtx_sensor_state state,
        _In_ const rtx_sensor_state check) noexcept {
    typedef std::underlying_type_t<rtx_sensor_state> underlying_type;
    const auto actual = static_cast<underlying_type>(state);
    const auto reference = static_cast<underlying_type>(check);
    return ((actual & reference) == reference);
}


/// <summary>
/// Checks whether all bits of <paramref name="check" /> are set in
/// <paramref name="state" />.
/// </summary>
/// <param name="state"></param>
/// <param name="check"></param>
/// <returns></returns>
inline bool check_state(_In_ const std::atomic<rtx_sensor_state>& state,
        _In_ const rtx_sensor_state check) noexcept {
    return check_state(state.load(std::memory_order_acquire), check);
}


/// <summary>
/// Removes all of the the given <paramref name="old_state" /> flags from
/// <paramref name="state" /> and answers whether the state change was
/// successful.
/// </summary>
/// <param name="state"></param>
/// <param name="old_state"></param>
/// <returns></returns>
PWROWG_TEST_API bool clear_state(_Inout_ rtx_sensor_state& state,
    _In_ const rtx_sensor_state old_state) noexcept;


/// <summary>
/// Removes all of the the given <paramref name="old_state" /> flags from
/// <paramref name="state" /> and answers whether the state change was
/// successful.
/// </summary>
/// <param name="state"></param>
/// <param name="old_state"></param>
/// <returns></returns>
PWROWG_TEST_API bool clear_state(_Inout_ std::atomic<rtx_sensor_state>& state,
    _In_ const rtx_sensor_state old_state) noexcept;


/// <summary>
/// Sets the given <paramref name="new_state" /> flags in
/// <paramref name="state" /> and answers whether the state change was
/// successful.
/// </summary>
/// <param name="state"></param>
/// <param name="new_state"></param>
/// <returns></returns>
PWROWG_TEST_API bool set_state(_Inout_ rtx_sensor_state& state,
    _In_ const rtx_sensor_state new_state) noexcept;


/// <summary>
/// Sets the given <paramref name="new_state" /> flags in
/// <paramref name="state" /> and answers whether the state change was
/// successful.
/// </summary>
/// <param name="state"></param>
/// <param name="new_state"></param>
/// <returns></returns>
PWROWG_TEST_API bool set_state(_Inout_ std::atomic<rtx_sensor_state>& state,
    _In_ const rtx_sensor_state new_state) noexcept;

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_RTX_SENSOR_STATE_H) */
