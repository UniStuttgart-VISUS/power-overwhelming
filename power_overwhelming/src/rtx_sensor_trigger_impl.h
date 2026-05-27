// <copyright file="rtx_sensor_trigger_impl.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_RTX_SENSOR_TRIGGER_IMPL_H)
#define _PWROWG_RTX_SENSOR_TRIGGER_IMPL_H
#pragma once

#include <atomic>
#include <memory>
#include <string>
#include <thread>

#include "visus/pwrowg/atomic_utilities.h"
#include "visus/pwrowg/parallel_port_trigger.h"
#include "visus/pwrowg/rtx_acquisition.h"
#include "visus/pwrowg/rtx_trigger.h"
#include "visus/pwrowg/thread_name.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Implements the shared, reference-counted state of an
/// <see cref="rtx_sensor_trigger" />.
/// </summary>
struct rtx_sensor_trigger_impl final {

    /// <summary>
    /// Configures how the instrument will acquire data.
    /// </summary>
    rtx_acquisition acquisition;

    /// <summary>
    /// If the instance is valid, the oscilloscope will be triggered via the
    /// configured parallel port.
    /// </summary>
    parallel_port_trigger external_trigger;

    /// <summary>
    /// The duration for which the pins specified in
    /// <see cref="external_trigger_pins" /> are raised. This value defaults to
    /// 100 milliseconds.
    /// </summary>
    parallel_port_trigger::milliseconds_type external_trigger_duration;

    /// <summary>
    /// The pins to be raised on the parallel port if
    /// <see cref="external_trigger" /> is valid. This value defaults to all the
    /// data pins.
    /// </summary>
    parallel_port_pin external_trigger_pins;

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
    /// specified VISA <see cref="path" />. If this member is
    /// <see langword="nullptr" />, the oscilloscope will be triggered
    /// programmatically by starting the acquisition manually.
    /// </summary>
    std::unique_ptr<rtx_trigger> trigger;

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    inline rtx_sensor_trigger_impl(void)
        : external_trigger_duration(100),
        external_trigger_pins(parallel_port_pin::data),
        references(1) { }
};

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_RTX_SENSOR_TRIGGER_IMPL_H) */
