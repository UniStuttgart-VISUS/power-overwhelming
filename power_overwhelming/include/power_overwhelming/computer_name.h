// <copyright file="computer_name.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cstddef>

#include "power_overwhelming/power_overwhelming_api.h"


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Answer the name of the computer the calling code is running on.
    /// </summary>
    /// <remarks>
    /// Call with <c>nullptr</c> and a buffer size of zero to determine the
    /// required buffer size and call again with the actual buffer.
    /// </remarks>
    /// <param name="dst">Receives the name of the computer if not
    /// <c>nullptr</c>. On exit, this value is only to be considered
    /// valid if the return value is less or equal to
    /// <paramref name="cnt" />.</param>
    /// <param name="cnt">The size of <paramref name="dst" /> in number of
    /// characters.</param>
    /// <returns>The required size of the <paramref name="dst" /> buffer to
    /// store the computer name.</returns>
    /// <exception cref="std::system_error">In case the operation failed.
    /// </exception>
    std::size_t POWER_OVERWHELMING_API computer_name(char *dst,
        const std::size_t cnt);

    /// <summary>
    /// Answer the name of the computer the calling code is running on.
    /// </summary>
    /// <remarks>
    /// Call with <c>nullptr</c> and a buffer size of zero to determine the
    /// required buffer size and call again with the actual buffer.
    /// </remarks>
    /// <param name="dst">Receives the name of the computer if not
    /// <c>nullptr</c>. On exit, this value is only to be considered
    /// valid if the return value is less or equal to
    /// <paramref name="cnt" />.</param>
    /// <param name="cnt">The size of <paramref name="dst" /> in number of
    /// characters.</param>
    /// <returns>The required size of the <paramref name="dst" /> buffer to
    /// store the computer name.</returns>
    /// <exception cref="std::system_error">In case the operation failed.
    /// </exception>
    std::size_t POWER_OVERWHELMING_API computer_name(wchar_t *dst,
        const std::size_t cnt);

} /* namespace power_overwhelming */
} /* namespace visus */
