// <copyright file="oscilloscope_acquisition_state.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart.
// Licenced under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cinttypes>

#include "power_overwhelming/power_overwhelming_api.h"


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Specifies possible acquisition states of a Rohde &amp; Schwarz
    /// oscilloscope.
    /// </summary>
    enum class oscilloscope_acquisition_state {

        /// <summary>
        /// The state could not be retrieved or should not be modified in case
        /// of a setter.
        /// </summary>
        unknown = 0x0000,

        /// <summary>
        /// Starts the acquisition.
        /// </summary>
        run,

        /// <summary>
        /// Stops the acquisition when it is finished.
        /// </summary>
        stop,

        /// <summary>
        /// Immediately interrupt the current acquisition.
        /// </summary>
        interrupt,

        /// <summary>
        /// Trigger a single acquisition.
        /// </summary>
        single
    };

    /// <summary>
    /// Parse the given string as <see cref="oscilloscope_acquisition_state" />.
    /// </summary>
    /// <param name="str">The string to be parsed.</param>
    /// <returns>The parsed enumeration value.</returns>
    /// <exception cref="std::invalid_argument">If <paramref name="str" /> is
    /// <c>nullptr</c>.</exception>
    /// <exception cref="std::invalid_argument">If <paramref name="str" /> does
    /// not represent a valid enumeration member.<exception>
    extern POWER_OVERWHELMING_API oscilloscope_acquisition_state
    parse_oscilloscope_acquisition_state(_In_z_ const wchar_t *str);

    /// <summary>
    /// Convert the given acquisition state to a human-readable string
    /// representation.
    /// </summary>
    /// <param name="state">The value to be converted.</param>
    /// <returns>The string representation of the value.</returns>
    /// <exception cref="std::invalid_argument">If the input is not
    /// valid and therefore could not be converted.</exception>
    extern POWER_OVERWHELMING_API _Ret_valid_ const wchar_t *to_string(
        _In_ const oscilloscope_acquisition_state state);

} /* namespace power_overwhelming */
} /* namespace visus */
