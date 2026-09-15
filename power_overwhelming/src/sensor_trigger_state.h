// <copyright file="sensor_trigger_state.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_SENSOR_TRIGGER_STATE_H)
#define _PWROWG_SENSOR_TRIGGER_STATE_H
#pragma once

#include <atomic>
#include <chrono>
#include <cinttypes>

#include "visus/pwrowg/api.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Tracks the state of the <see cref="daqmx_sensor" />'s and the
/// <see cref="rtx_sensor" />'s worker threads and the trigger handlers
/// connected to the sensor.
/// </summary>
enum class sensor_trigger_state : std::uint32_t {

    /// <summary>
    /// The sensor is in an undefined state and should exit.
    /// </summary>
    none = 0x00000000,

    /// <summary>
    /// The worker thread should continue checking the instrument. If this flag
    /// is unset, the worker thread should exit.
    /// </summary>
    running = 0x00000001,

    /// <summary>
    /// Indicates that an acquisition has been requested by the application.
    /// </summary>
    /// <remarks>
    /// <para>This flag tells the RTX sensor worker thread that the application
    /// wants to retrieve a sample. The worker thread will only try downloading
    /// waveforms if it finds this flag set when it receives an OPC.</para>
    /// </remarks>
    armed = 0x00000002,

    /// <summary>
    /// Indicates that the instrument is busy retrieving the measurement data.
    /// <summary>
    /// <remarks>
    /// <para>The RTX sensor worker thread sets this flag once it received an
    /// OPC while being armed. The instrument must not be manipulated by any
    /// other thread while this flag is set. The worker thread will clear the
    /// flag once it is done, even if the processing failed.</para>
    /// </remarks>
    busy = 0x00000004
};


/// <summary>
/// Computes the bitwise AND of <paramref name="lhs" /> and
/// <paramref name="rhs" />.
/// </summary>
/// <param name="lhs"></param>
/// <param name="rhs"></param>
/// <returns></returns>
inline constexpr PWROWG_DETAIL_NAMESPACE::sensor_trigger_state operator &(
        _In_ const PWROWG_DETAIL_NAMESPACE::sensor_trigger_state lhs,
        _In_ const PWROWG_DETAIL_NAMESPACE::sensor_trigger_state rhs) noexcept {
    typedef std::decay_t<decltype(lhs)> enum_type;
    typedef std::underlying_type_t<enum_type> underlying_type;
    auto l = static_cast<underlying_type>(lhs);
    auto r = static_cast<underlying_type>(rhs);
    return static_cast<enum_type>(l & r);
}


/// <summary>
/// Computes the bitwise OR of <paramref name="lhs" /> and
/// <paramref name="rhs" />.
/// </summary>
/// <param name="lhs"></param>
/// <param name="rhs"></param>
/// <returns></returns>
inline constexpr PWROWG_DETAIL_NAMESPACE::sensor_trigger_state operator |(
        _In_ const PWROWG_DETAIL_NAMESPACE::sensor_trigger_state lhs,
        _In_ const PWROWG_DETAIL_NAMESPACE::sensor_trigger_state rhs) noexcept {
    typedef std::decay_t<decltype(lhs)> enum_type;
    typedef std::underlying_type_t<enum_type> underlying_type;
    auto l = static_cast<underlying_type>(lhs);
    auto r = static_cast<underlying_type>(rhs);
    return static_cast<enum_type>(l | r);
}


/// <summary>
/// Computes the bitwise NOT of <paramref name="value" />.
/// </summary>
/// <param name="value"></param>
/// <returns></returns>
inline constexpr PWROWG_DETAIL_NAMESPACE::sensor_trigger_state operator ~(
        _In_ const PWROWG_DETAIL_NAMESPACE::sensor_trigger_state value) noexcept {
    typedef std::decay_t<decltype(value)> enum_type;
    typedef std::underlying_type_t<enum_type> underlying_type;
    return static_cast<enum_type>(~static_cast<underlying_type>(value));
}

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_SENSOR_TRIGGER_STATE_H) */
