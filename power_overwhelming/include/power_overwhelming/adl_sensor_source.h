// <copyright file="adl_sensor_source.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cinttypes>
#include <limits>

#include "power_overwhelming/power_overwhelming_api.h"


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Specifies possible sources for ADL sensors.
    /// </summary>
    enum class adl_sensor_source : std::uint32_t {

        /// <summary>
        /// <c>ADL_PMLOG_SOC_POWER</c>.
        /// </summary>
        soc = 0x0001,

        /// <summary>
        /// <c>ADL_PMLOG_GFX_POWER</c>.
        /// </summary>
        graphics = 0x0002,

        /// <summary>
        /// <c>ADL_PMLOG_ASIC_POWER</c> or <c>ADL_PMLOG_SSPAIRED_ASICPOWER</c>.
        /// </summary>
        asic = 0x0004,

        /// <summary>
        /// <c>ADL_PMLOG_CPU_POWER</c>.
        /// </summary>
        cpu = 0x0008,

        /// <summary>
        /// Total board power (<c>ADL_PMLOG_BOARD_POWER</c>).
        /// </summary>
        board = 0x0010,

        /// <summary>
        /// Represents all possible sensor sources.
        /// </summary>
        /// <remarks>
        /// This should only be used for filtering when creating the sensor
        /// instances. In end-user code, it is usually an indication that
        /// something is going wrong if this value is used.
        /// </remarks>
        all = (std::numeric_limits<std::uint32_t>::max)()
    };

    /// <summary>
    /// Combine two <see cref="adl_sensor_source" />s.
    /// </summary>
    /// <param name="lhs">The left-hand side operand.</param>
    /// <param name="rhs">The right-hand side operand.</param>
    /// <returns>The bitwise &quot;or&quot; of the two operands.</returns>
    extern POWER_OVERWHELMING_API adl_sensor_source operator |(
        _In_ const adl_sensor_source lhs, _In_ const adl_sensor_source rhs);

    /// <summary>
    /// Test two <see cref="adl_sensor_source" />s.
    /// </summary>
    /// <param name="lhs">The left-hand side operand.</param>
    /// <param name="rhs">The right-hand side operand.</param>
    /// <returns>The bitwise &quot;and&quot; of the two operands.</returns>
    extern POWER_OVERWHELMING_API adl_sensor_source operator &(
        _In_ const adl_sensor_source lhs, _In_ const adl_sensor_source rhs);

    /// <summary>
    /// Parse a sensor source from a string.
    /// </summary>
    /// <param name="str">The string to be parsed.</param>
    /// <returns>The sensor source represented by the string.</returns>
    extern POWER_OVERWHELMING_API adl_sensor_source parse_adl_sensor_source(
        _In_z_ const wchar_t *str);

    /// <summary>
    /// Convert the given sensor source to a human-readable string
    /// representation.
    /// </summary>
    /// <param name="source">The source to be converted.</param>
    /// <returns>The name of the source.</returns>
    extern POWER_OVERWHELMING_API _Ret_z_ const wchar_t *to_string(
        _In_ const adl_sensor_source source);

} /* namespace power_overwhelming */
} /* namespace visus */
