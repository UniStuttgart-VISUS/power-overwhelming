// <copyright file="rtx_sensor_trigger_impl.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_RTX_SENSOR_TRIGGER_IMPL_H)
#define _PWROWG_RTX_SENSOR_TRIGGER_IMPL_H
#pragma once

#include <atomic>
#include <string>

#include "visus/pwrowg/rtx_trigger.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Implements the shared, reference-counted state of an
/// <see cref="rtx_sensor_trigger" />.
/// </summary>
struct rtx_sensor_trigger_impl final {

    /// <summary>
    /// The path to the oscilloscope used for triggering.
    /// </summary>
    std::string path;

    /// <summary>
    /// The number of <see cref="rtx_sensor_trigger" /> instances sharing this
    /// implementation.
    /// </summary>
    std::atomic<std::size_t> references;

    /// <summary>
    /// The trigger configuration to apply to the oscilloscope identified by the
    /// specified VISA <see cref="path" />.
    /// </summary>
    rtx_trigger trigger;

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    inline rtx_sensor_trigger_impl(
            _In_ const std::string& path,
            _In_ const rtx_trigger trigger)
        : path(path),
            references(1),
            trigger(trigger) { }
};

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_RTX_SENSOR_TRIGGER_IMPL_H) */
