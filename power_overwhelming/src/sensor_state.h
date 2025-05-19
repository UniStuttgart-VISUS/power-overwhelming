// <copyright file="sensor_state.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_SENSOR_STATE_H)
#define _PWROWG_SENSOR_STATE_H
#pragma once

#include "visus/pwrowg/atomic_utilities.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Atomically tracks the state of a sensor or the sensor array as a whole.
/// </summary>
class PWROWG_TEST_API alignas(false_sharing_range) sensor_state final {

public:

    /// <summary>
    /// Possible states of the sensor or sensor array.
    /// </summary>
    enum class value_type {

        /// <summary>
        /// The sensors or the array are stopped and can be started.
        /// </summary>
        stopped,

        /// <summary>
        /// The sensor is starting and in a state where it cannot be modified,
        /// or the array is in the process of starting the sensors.
        /// </summary>
        /// <remarks>
        /// The following states can be <see cref="running" /> if the startup has
        /// succeeded, or <see cref="stopped" /> in case of an error.
        /// </remarks>
        starting,

        /// <summary>
        /// The sensor or the array are running and delivering data to the
        /// callbacks.
        /// </summary>
        running,

        /// <summary>
        /// The sensors are being stopped, but some are still running, or a single
        /// sensor is in a transitional state where it cannot be modified.
        /// </summary>
        /// <remarks>
        /// The next state after this must be <see cref="stopped" />.
        /// </remarks>
        stopping
    };

    /// <summary>
    /// Performs an aligned allocation for a new sensor.
    /// </summary>
    /// <param name="size">The size of the allocation in bytes.</param>
    /// <returns>A pointer to the memory, which must be freed using
    /// <see cref="free_for_atomic" />.</returns>
    /// <exception cref="std::bad_alloc">If the allocation failed.</exception>
    static inline void *operator new(_In_ const std::size_t size) {
        return allocate_for_atomic(size);
    }

    /// <summary>
    /// Frees the aligned allocation of a sensor.
    /// </summary>
    /// <param name="ptr">The pointer to be freed. It is safe to pass
    /// <c>nullptr</c>.</param>
    static inline void operator delete(_In_opt_ void *ptr) noexcept {
        free_for_atomic(ptr);
    }

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    inline sensor_state(void) : _value(value_type::stopped) { }

    /// <summary>
    /// Change the state to <see cref="value_type::starting" />.
    /// </summary>
    /// <exception cref="std::logic_error">If the sensor is already running or
    /// in a transitional state.</exception>
    void begin_start(void);

    /// <summary>
    /// Change the state to <see cref="value_type::stopping" />.
    /// </summary>
    /// <exception cref="std::logic_error">If the sensor is not running or
    /// in a transitional state.</exception>
    void begin_stop(void);

    /// <summary>
    /// Change the state to <see cref="value_type::running" />.
    /// </summary>
    /// <exception cref="std::logic_error">If the sensor is not in state
    /// <see cref="value_type::starting" />.</exception>
    void end_start(void);

    /// <summary>
    /// Change the state to <see cref="value_type::stopped" />.
    /// </summary>
    /// <exception cref="std::logic_error">If the sensor is not in state
    /// <see cref="value_type::stopping" />.</exception>
    void end_stop(void);

    /// <summary>
    /// Forcefully change the state to <see cref="value_type::stopped" />.
    /// </summary>
    void stop(void) noexcept;

    /// <summary>
    /// Try chaning the state to <see cref="value_type::starting" />.
    /// </summary>
    /// <returns><c>true</c> if the state change was possible and has been
    /// applied, <c>false</c> otherwise</returns>
    bool try_begin_start(void) noexcept;

    /// <summary>
    /// Try chaning the state to <see cref="value_type::stopping" />.
    /// </summary>
    /// <returns><c>true</c> if the state change was possible and has been
    /// applied, <c>false</c> otherwise</returns>
    bool try_begin_stop(void) noexcept;

    /// <summary>
    /// Gets a momentary snapshot of the <see cref="value_type" /> the sensor
    /// is in.
    /// </summary>
    /// <returns>The current state of the sensor.</returns>
    inline operator value_type(void) const noexcept {
        return this->_value.load(std::memory_order_acquire);
    }

    /// <summary>
    /// Indicates whether the state is starting or running.
    /// </summary>
    /// <returns><c>true</c> if the sensor should continue, <c>false</c> if it
    /// should stop.</returns>
    inline operator bool(void) const {
        const auto v = this->_value.load(std::memory_order_acquire);
        return ((v == value_type::starting) || (v == value_type::running));
    }

private:

    alignas(false_sharing_range) std::atomic<value_type> _value;
};

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_SENSOR_STATE_H) */
