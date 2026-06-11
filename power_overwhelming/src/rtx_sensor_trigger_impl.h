// <copyright file="rtx_sensor_trigger_impl.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_RTX_SENSOR_TRIGGER_IMPL_H)
#define _PWROWG_RTX_SENSOR_TRIGGER_IMPL_H
#pragma once

#include <atomic>
#include <cinttypes>
#include <limits>
#include <memory>
#include <string>
#include <vector>

#include "visus/pwrowg/atomic_utilities.h"
#include "visus/pwrowg/parallel_port_trigger.h"
#include "visus/pwrowg/rtx_acquisition.h"
#include "visus/pwrowg/rtx_instrument.h"
#include "visus/pwrowg/rtx_trigger.h"
#include "visus/pwrowg/timestamp.h"

#include "rtx_sensor_state.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Implements the shared, reference-counted state of an
/// <see cref="rtx_sensor_trigger" />.
/// </summary>
struct rtx_sensor_trigger_impl final {

    /// <summary>
    /// If positive, the oscilloscopes will be assumed to be daisy-chained even
    /// if they are configured to be triggered manually. In this case, this
    /// value is the trigger level for the external trigger.
    /// </summary>
    float daisy_chain;

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

#if defined(POWER_OVERWHELMING_WITH_VISA)
    /// <summary>
    /// The instruments used by the sensor. This list is stored in the trigger,
    /// because it must have access to the instruments as well.
    /// </summary>
    std::vector<rtx_instrument> instruments;
#endif /* defined(POWER_OVERWHELMING_WITH_VISA) */

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
    /// Keeps track of the state of the sensor.
    /// </summary>
    /// <remarks>
    /// This information is stored in the trigger implementation rather than in
    /// the sensor, because the state is used to relay manual trigger requests
    /// from the user of the library to the worker thread of the sensor.
    /// Therefore, the <see cref="rtx_sensor_trigger" /> must have access to the
    /// state.
    /// </remarks>
    alignas(false_sharing_range) std::atomic<rtx_sensor_state> state;

    /// <summary>
    /// The trigger configuration to apply to the oscilloscope identified by the
    /// specified VISA <see cref="path" />. If this member is
    /// <see langword="nullptr" />, the oscilloscope will be triggered
    /// programmatically by starting the acquisition manually.
    /// </summary>
    alignas(false_sharing_range) std::unique_ptr<rtx_trigger> trigger;

    /// <summary>
    /// The index of the instrument to be triggered manually if there is a
    /// daisy chain in place.
    /// </summary>
    std::size_t trigger_instrument;

    /// <summary>
    /// The host timestamps when the tigger was activated.
    /// </summary>
    std::vector<timestamp> trigger_timestamps;

    /// <summary>
    /// Allocates aligned memory for a new object.
    /// </summary>
    /// <param name="size">The size of the block to align.</param>
    /// <returns>A pointer to the newly allocated block.</returns>
    /// <exception cref="std::bad_alloc">If the allocation fails.
    /// </exception>
    static inline void *operator new(_In_ const std::size_t size) {
        assert(size >= sizeof(rtx_sensor_trigger_impl));
        auto retval = allocate_for_atomic(size);
        assert(reinterpret_cast<std::uintptr_t>(retval)
            % false_sharing_range == 0);
        return retval;
    }

    /// <summary>
    /// Frees the allocation of an aligned object.
    /// </summary>
    static inline void operator delete(_In_ void *ptr) noexcept {
        assert(ptr != nullptr);
        free_for_atomic(ptr);
    }

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    inline rtx_sensor_trigger_impl(void)
        : daisy_chain(0.0f),
        external_trigger_duration(100),
        external_trigger_pins(parallel_port_pin::data),
        references(1),
        state(rtx_sensor_state::none),
        trigger_instrument((std::numeric_limits<std::size_t>::max)()),
        trigger_timestamps(1, timestamp()) { }

};

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_RTX_SENSOR_TRIGGER_IMPL_H) */
