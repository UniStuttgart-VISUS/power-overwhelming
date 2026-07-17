// <copyright file="daqmx_sensor_trigger_impl.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_DAQMX_SENSOR_TRIGGER_IMPL_H)
#define _PWROWG_DAQMX_SENSOR_TRIGGER_IMPL_H
#pragma once

#include <atomic>
#include <cinttypes>
#include <exception>
#include <limits>
#include <memory>
#include <string>
#include <vector>

#include "visus/pwrowg/atomic_utilities.h"
#include "visus/pwrowg/daqmx_analog_edge_trigger.h"
#include "visus/pwrowg/daqmx_task.h"
#include "visus/pwrowg/daqmx_timing.h"
#include "visus/pwrowg/parallel_port_trigger.h"
#include "visus/pwrowg/timestamp.h"
#include "visus/pwrowg/trace.h"
#include "visus/pwrowg/type_erased_storage.h"

#include "sensor_trigger_state.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Implements the shared, reference-counted state of an
/// <see cref="daqmx_sensor_trigger" />.
/// </summary>
struct daqmx_sensor_trigger_impl final {

    /// <summary>
    /// If the instance is valid, the DAQ will be triggered via the configured
    /// parallel port.
    /// </summary>
    /// <remarks>
    /// A valid edge <see cref="trigger" /> must be configured when using an
    /// external trigger such that the device knows there the trigger is
    /// connected to.
    /// </remarks>
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
    /// Therefore, the <see cref="daqmx_sensor_trigger" /> must have access to
    /// the state.
    /// </remarks>
    alignas(false_sharing_range) std::atomic<sensor_trigger_state> state;

#if defined(POWER_OVERWHELMING_WITH_DAQMX)
    /// <summary>
    /// The task holding the acquisition channels and the optional external
    /// trigger.
    /// </summary>
    alignas(false_sharing_range) daqmx_task task;
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */

    /// <summary>
    /// An (optional) analog edge trigger starting the acquisition. If this is
    /// <see langword="nullptr" />, the acquisition is started with the task.
    /// </summary>
    /// <remarks>
    /// If this member is <see langword="nullptr" />, any external trigger will
    /// be ignored.
    /// </remarks>
    std::unique_ptr<daqmx_analog_edge_trigger> trigger;

#if defined(POWER_OVERWHELMING_WITH_DAQMX)
    /// <summary>
    /// Holds the timing information for the acquisition.
    /// </summary>
    std::unique_ptr<daqmx_timing> timing;
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */

    /// <summary>
    /// The host timestamp when the trigger was activated.
    /// </summary>
    timestamp trigger_timestamp;

    /// <summary>
    /// A callback to be invoked when the DAQMX completed an acquisition.
    /// </summary>
    void (*when_done)(const type_erased_storage&);

    /// <summary>
    /// The context passed to <see cref="when_done" />. This is usually used to
    /// store a user-defined lambda to be called.
    /// </summary>
    type_erased_storage when_done_context;

    /// <summary>
    /// A callback to be invoked when an acquisition fails. The callback can
    /// decide on whether the thread should continue or whether the failure is
    /// fatal.
    /// </summary>
    bool (*when_failed)(std::exception_ptr, const type_erased_storage&);

    /// <summary>
    /// The context passed to <see cref="when_failed" />. This is usually used to
    /// store a user-defined lambda to be called.
    /// </summary>
    type_erased_storage when_failed_context;

    /// <summary>
    /// Allocates aligned memory for a new object.
    /// </summary>
    /// <param name="size">The size of the block to align.</param>
    /// <returns>A pointer to the newly allocated block.</returns>
    /// <exception cref="std::bad_alloc">If the allocation fails.
    /// </exception>
    static inline void *operator new(_In_ const std::size_t size) {
        assert(size >= sizeof(daqmx_sensor_trigger_impl));
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
    inline daqmx_sensor_trigger_impl(_In_z_ const char *task = nullptr)
            : external_trigger_duration(100),
            external_trigger_pins(parallel_port_pin::data),
            references(1),
            state(sensor_trigger_state::none),
#if defined(POWER_OVERWHELMING_WITH_DAQMX)
            task((task == nullptr)
                ? std::to_string(reinterpret_cast<std::uintptr_t>(this))
                : task),
#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
            when_done(nullptr),
            when_failed(nullptr) { }
};

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_DAQMX_SENSOR_TRIGGER_IMPL_H) */
