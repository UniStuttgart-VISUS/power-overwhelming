// <copyright file="powenetics_configuration.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 - 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_POWENETICS_CONFIGURATION_H)
#define _PWROWG_POWENETICS_CONFIGURATION_H
#pragma once

#include <chrono>
#include <cstdlib>

#include "visus/pwrowg/sensor_configuration.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Provides additional configuration options for sensors using the Powenetics
/// power measurement device (PMD).
/// </summary>
class POWER_OVERWHELMING_API powenetics_configuration final
        : public sensor_configuration {

public:

    /// <summary>
    /// A unique identifier for the <see cref="powenetics_configuration" /> type.
    /// </summary>
    static const guid id;

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    powenetics_configuration(void) noexcept;

    /// <summary>
    /// Gets the timeout, in milliseconds, for probing a serial port for a
    /// Powenetics v2 device.
    /// </summary>
    /// <returns>The timeout in milliseconds.</returns>
    inline std::size_t timeout(void) const noexcept {
        return this->_timeout;
    }

    /// <summary>
    /// Sets the timeout for probing a serial port whether it has a Powenetics
    /// device connected.
    /// </summary>
    /// <typeparam name="TType"></typeparam>
    /// <typeparam name="TPeriod"></typeparam>
    /// <param name="timeout">The timeout for probing.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    template<class TType, class TPeriod>
    inline powenetics_configuration& timeout(
            _In_ const std::chrono::duration<TType, TPeriod> timeout) {
        auto m = std::chrono::duration_cast<std::chrono::milliseconds>(timeout);
        this->_timeout = static_cast<std::size_t>(std::abs(m.count()));
        return *this;
    }

private:

    std::size_t _timeout;

};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_POWENETICS_CONFIGURATION_H) */
