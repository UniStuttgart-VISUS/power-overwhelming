// <copyright file="oscilloscope_channel_polarity.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "power_overwhelming/power_overwhelming_api.h"


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Defines possible values for the channel polarity.
    /// </summary>
    enum class oscilloscope_channel_polarity {

        /// <summary>
        /// The data are unmodified
        /// </summary>
        normal,

        /// <summary>
        /// Reflect the voltage values of all signal components against the
        /// ground level.
        /// </summary>
        /// <remarks>
        /// Inversion affects only the display of the signal, but not the
        /// trigger.
        /// </remarks>
        inverted,
    };

    /// <summary>
    /// Parse the given string as <see cref="oscilloscope_channel_polarity" />.
    /// </summary>
    /// <param name="str">The string to be parsed.</param>
    /// <returns>The parsed enumeration value.</returns>
    /// <exception cref="std::invalid_argument">If <paramref name="str" /> is
    /// <c>nullptr</c>.</exception>
    /// <exception cref="std::invalid_argument">If <paramref name="str" /> does
    /// not represent a valid enumeration member.<exception>
    extern POWER_OVERWHELMING_API oscilloscope_channel_polarity
    parse_oscilloscope_channel_polarity(_In_z_ const wchar_t *str);

    /// <summary>
    /// Convert the given channel polarity to a human-readable string
    /// representation.
    /// </summary>
    /// <param name="polarity">The polarity to be converted.</param>
    /// <returns>The string representation of teh value.</returns>
    /// <exception cref="std::invalid_argument">If the input is not
    /// valid and therefore could not be converted.</exception>
    extern POWER_OVERWHELMING_API _Ret_valid_ const wchar_t *to_string(
        _In_ const oscilloscope_channel_polarity polarity);

} /* namespace power_overwhelming */
} /* namespace visus */
