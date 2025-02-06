// <copyright file="sensor_type.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_SENSOR_TYPE_H)
#define _PWROWG_SENSOR_TYPE_H
#pragma once

#include <cinttypes>
#include <type_traits>

#include "visus/pwrowg/api.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Identifies different kinds of sensors supported by the library.
/// </summary>
/// <remarks>
/// The sensor type is a bitmask, which typically has serveral of the given
/// constants set to describe the nature of the sensor.
/// </remarks>
enum class sensor_type : std::uint32_t {

    /// <summary>
    /// Nothing is known about the sensor.
    /// </summary>
    /// <remarks>
    /// This value should only be used in invalid sensor descriptions.
    /// </remarks>
    unknown = 0x00000000,

    /// <summary>
    /// The sensor is external, i.e. gets data from other devices.
    /// </summary>
    external = 0x00000001,

    /// <summary>
    /// The sensor measures the whole system power draw.
    /// </summary>
    system = 0x00000002,

    /// <summary>
    /// The sensor measures the CPU power draw.
    /// </summary>
    cpu = 0x00000004,

    /// <summary>
    /// The sensor measures the GPU power draw.
    /// </summary>
    gpu = 0x00000008,

    /// <summary>
    /// The sensor provides power readings.
    /// </summary>
    power = 0x00010000,

    /// <summary>
    /// The sensor provides voltage readings.
    /// </summary>
    voltage = 0x00020000,

    /// <summary>
    /// The sensor provides current readings.
    /// </summary>
    current = 0x00040000,

    /// <summary>
    /// The sensor provides temperature readings.
    /// </summary>
    temperature = 0x00080000,

    /// <summary>
    /// The sensor indicates the throttling state of the device.
    /// </summary>
    throttling = 0x00100000,

    /// <summary>
    /// The sensor is a software sensor which obtains its data from the driver
    /// or operating system.
    /// </summary>
    software = 0x10000000,

    /// <summary>
    /// The sensor uses dedicated hardware.
    /// </summary>
    hardware = 0x2000000
};


/// <summary>
/// Combines <paramref name="lhs" /> and <paramref name="rhs" />.
/// </summary>
/// <param name="lhs"></param>
/// <param name="rhs"></param>
/// <returns></returns>
inline sensor_type operator |(_In_ const sensor_type lhs,
        _In_ const sensor_type rhs) {
    typedef typename std::decay<decltype(lhs)>::type enum_type;
    typedef typename std::underlying_type<enum_type>::type mask_type;
    const auto l = static_cast<mask_type>(lhs);
    const auto r = static_cast<mask_type>(rhs);
    return static_cast<decltype(lhs)>(l | r);
}


/// <summary>
/// Tests <paramref name="lhs" /> and <paramref name="rhs" /> for shared bits.
/// </summary>
/// <param name="lhs"></param>
/// <param name="rhs"></param>
/// <returns></returns>
inline sensor_type operator &(_In_ const sensor_type lhs,
        _In_ const sensor_type rhs) {
    typedef typename std::decay<decltype(lhs)>::type enum_type;
    typedef typename std::underlying_type<enum_type>::type mask_type;
    const auto l = static_cast<mask_type>(lhs);
    const auto r = static_cast<mask_type>(rhs);
    return static_cast<decltype(lhs)>(l & r);
}

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_SENSOR_TYPE_H) */
