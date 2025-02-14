// <copyright file="usb_pd_configuration.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_USB_PD_CONFIGURATION_H)
#define _PWROWG_USB_PD_CONFIGURATION_H
#pragma once

#include <chrono>

#include "visus/pwrowg/sensor_configuration.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Provides additional configuration options for sensors based on the Passmark
/// USB power delivery tested when creating a <see cref="sensor_array" />.
/// </summary>
class POWER_OVERWHELMING_API usb_pd_configuration final
        : public sensor_configuration {

public:

    /// <summary>
    /// A unique identifer for the <see cref="usb_pd_configuration" /> type.
    /// </summary>
    static const guid id;

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    usb_pd_configuration(void) noexcept;

    /// <summary>
    /// Answer the timeout for searching devices, in milliseconds.
    /// </summary>
    /// <returns>The timeout in milliseconds.</returns>
    inline std::int64_t timeout(void) const noexcept {
        return this->_timeout;
    }

    /// <summary>
    /// Sets the timeout for enumerating USB PD testers.
    /// </summary>
    /// <typeparam name="TType"></typeparam>
    /// <typeparam name="TPeriod"></typeparam>
    /// <param name="timeout"></param>
    /// <returns></returns>
    template<class TType, class TPeriod>
    inline usb_pd_configuration& timeout(
            _In_ const std::chrono::duration<TType, TPeriod> timeout) {
        auto m = std::chrono::duration_cast<std::chrono::milliseconds>(timeout);
        this->_timeout = std::abs(m.count());
        return *this;
    }

private:

    std::int64_t _timeout;
};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_USB_PD_CONFIGURATION_H) */
