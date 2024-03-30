// <copyright file="oscilloscope_channel_bandwidth.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "power_overwhelming/power_overwhelming_api.h"


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Defines possible values for the channel bandwidth
    /// </summary>
    enum class oscilloscope_channel_bandwidth {

        /// <summary>
        /// Use the full bandwidth.
        /// </summary>
        full,

        /// <summary>
        /// Limit to 20 Mhz in order to reduce high-frequency noise.
        /// </summary>
        limit_to_20_mhz,
    };

    /// <summary>
    /// Parse the given string as <see cref="oscilloscope_channel_bandwidth" />.
    /// </summary>
    /// <param name="str">The string to be parsed.</param>
    /// <returns>The parsed enumeration value.</returns>
    /// <exception cref="std::invalid_argument">If <paramref name="str" /> is
    /// <c>nullptr</c>.</exception>
    /// <exception cref="std::invalid_argument">If <paramref name="str" /> does
    /// not represent a valid enumeration member.<exception>
    extern POWER_OVERWHELMING_API oscilloscope_channel_bandwidth
    parse_oscilloscope_channel_bandwidth(_In_z_ const wchar_t *str);

    /// <summary>
    /// Convert the given channel bandwidth to a human-readable string
    /// representation.
    /// </summary>
    /// <param name="bandwidth">The value to be converted.</param>
    /// <returns>The string representation of the value.</returns>
    /// <exception cref="std::invalid_argument">If the input is not
    /// valid and therefore could not be converted.</exception>
    extern POWER_OVERWHELMING_API _Ret_valid_ const wchar_t *to_string(
        _In_ const oscilloscope_channel_bandwidth bandwidth);

} /* namespace power_overwhelming */
} /* namespace visus */
