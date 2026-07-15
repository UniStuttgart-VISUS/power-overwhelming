// <copyright file="daqmx_task.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_DAQMX_TASK_H)
#define _PWROWG_DAQMX_TASK_H
#pragma once
#if defined(POWER_OVERWHELMING_WITH_DAQMX)

#include "visus/pwrowg/daqmx_analog_edge_trigger.h"
#include "visus/pwrowg/daqmx_current_channel.h"
#include "visus/pwrowg/daqmx_done_handler.h"
#include "visus/pwrowg/daqmx_immediate_trigger.h"
#include "visus/pwrowg/daqmx_implicit_timing.h"
#include "visus/pwrowg/daqmx_power_channel.h"
#include "visus/pwrowg/daqmx_sample_clock_timing.h"
#include "visus/pwrowg/daqmx_sample_handler.h"
#include "visus/pwrowg/daqmx_time_trigger.h"
#include "visus/pwrowg/daqmx_voltage_channel.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// A RAII wrapper for NI-DAQmx task handles.
/// </summary>
class POWER_OVERWHELMING_API daqmx_task final {

public:

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="name">The name of the task.</param>
    explicit daqmx_task(_In_z_ const char *name);

    daqmx_task(const daqmx_task&) = delete;

    daqmx_task(daqmx_task&&) = delete;

    /// <summary>
    /// Finalises the instance.
    /// </summary>
    ~daqmx_task(void) noexcept;

    /// <summary>
    /// Destroys the task.
    /// </summary>
    void clear(void) noexcept;

    /// <summary>
    /// Indicates whether the task is done.
    /// </summary>
    /// <returns><see langword="true" /> if the task was completed,
    /// <see langword="false" /> otherwise.</returns>
    bool done(void) const;

    /// <summary>
    /// Configures the number of samples the internal buffer can hold per
    /// channel.
    /// </summary>
    /// <param name="size">The number of buffered samples. Use zero to disable
    /// buffering.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    daqmx_task& input_buffer(_In_ const std::size_t size);

    /// <summary>
    /// Sets a callback to be invoked when the task is completed.
    /// </summary>
    /// <typeparam name="TCallback"></typeparam>
    /// <param name="callback"></param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    template<class TCallback>
    inline daqmx_task& on_done(_In_ TCallback&& callback) {
        delete this->_on_done;
        this->_on_done = detail::daqmx_done_handler::install(
            *this, std::forward<TCallback>(callback));
        return *this;
    }

    /// <summary>
    /// Clears the callback for the task completion event.
    /// </summary>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    inline daqmx_task& on_done(const std::nullptr_t) noexcept {
        delete this->_on_done;
        this->_on_done = nullptr;
        return *this;
    }

    /// <summary>
    /// Installs a callback to be invoked whenever the task has acquired
    /// or emitted a given number of <paramref name="samples" />.
    /// </summary>
    /// <typeparam name="TCallback">The type of the callback.</typeparam>
    /// <param name="samples">The number of samples to wait for before
    /// invoking the callback.</param>
    /// <param name="type">The type of the sample event to wait for.</param>
    /// <param name="callback">The callback to be invoked.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    template<class TCallback> inline daqmx_task& on_sample(
            _In_ const uInt32 samples,
            _In_ const daqmx_sample_event_type type,
            _In_ TCallback&& callback) {
        delete this->_on_sample;
        this->_on_sample = detail::daqmx_sample_handler::install(
            *this, type, samples, std::forward<TCallback>(callback));
        return *this;
    }

    /// <summary>
    /// Installs a callback to be invoked whenever the task has acquired
    /// a given number of <paramref name="samples" />.
    /// </summary>
    /// <typeparam name="TCallback">The type of the callback.</typeparam>
    /// <param name="samples">The number of samples to wait for before
    /// invoking the callback.</param>
    /// <param name="callback">The callback to be invoked.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    template<class TCallback> inline daqmx_task& on_sample(
            _In_ const uInt32 samples,
            _In_ TCallback&& callback) {
        return this->on_sample(samples,
            daqmx_sample_event_type::acquired,
            std::forward<TCallback>(callback));
    }

    /// <summary>
    /// Clears the regular sample callback for the task.
    /// </summary>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    inline daqmx_task& on_sample(
            _In_ const uInt32,
            _In_ const std::nullptr_t) noexcept {
        delete this->_on_sample;
        this->_on_sample = nullptr;
        return *this;
    }

    /// <summary>
    /// Clears the regular sample callback for the task.
    /// </summary>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    inline daqmx_task& on_sample(_In_ const std::nullptr_t) noexcept {
        delete this->_on_sample;
        this->_on_sample = nullptr;
        return *this;
    }

    /// <summary>
    /// Reads at most <paramref name="samples" /> per configured channel into
    /// the given buffer.
    /// </summary>
    /// <param name="dst">A buffer of <pararmef name="cnt" /> numbers to store
    /// the samples to.</param>
    /// <param name="cnt">The number of elements in <paramref name="dst" />. If
    /// not specified, the default value reading as many samples as are
    /// available is used. If the default value is used for a task acquiring a
    /// finite number of samples, the call will block until all samples have
    /// been acquired or the timeout has been reached.</param>
    /// <param name="samples">The number of samples to read per channel.</param>
    /// <param name="interleaved">Indicates whether the values of a single
    /// sample should be consecutive (channels are interleaved) or all samples
    /// of a channel should be consecutive.</param>
    /// <param name="timeout">The maximum amount of time to wait, in seconds.
    /// Use <c>DAQmx_Val_WaitInfinitely</c> (the default) to wait indefinitely.
    /// </param>
    /// <returns>The number of samples read or zero if the operation timed out.
    /// </returns>
    std::size_t read(_Out_writes_(cnt * samples) double *dst,
        _In_ const std::size_t cnt,
        _In_ const int32 samples = DAQmx_Val_Auto,
        _In_ const bool interleaved = false,
        _In_ const double timeout = DAQmx_Val_WaitInfinitely);

    /// <summary>
    /// Configures the number of samples the internal buffer can hold per
    /// channel.
    /// </summary>
    /// <param name="size">The number of buffered samples. Use zero to disable
    /// buffering.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    daqmx_task& output_buffer(_In_ const std::size_t size);

    /// <summary>
    /// Starts the task.
    /// </summary>
    void start(void);

    /// <summary>
    /// Stops the task.
    /// </summary>
    void stop(void);

    /// <summary>
    /// Configures an implicit timing for the task.
    /// </summary>
    /// <param name="timing">The timing configuration.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    daqmx_task& timing(_In_ const daqmx_implicit_timing& timing);

    /// <summary>
    /// Configures the timing of the task.
    /// </summary>
    /// <param name="timing">The timing configuration.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    daqmx_task& timing(_In_ const daqmx_sample_clock_timing& timing);

    /// <summary>
    /// Configures how the task is being triggered.
    /// </summary>
    /// <param name="trigger">The trigger to be configured.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    daqmx_task& trigger(_In_ const daqmx_analog_edge_trigger& trigger);

    /// <summary>
    /// Configures how the task is being triggered.
    /// </summary>
    /// <param name="trigger">The trigger to be configured.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    daqmx_task& trigger(_In_ const daqmx_immediate_trigger& trigger);

    ///// <summary>
    ///// Configures how the task is being triggered.
    ///// </summary>
    ///// <param name="trigger">The trigger to be configured.</param>
    ///// <returns><c>*<see langword="this" /></c>.</returns>
    //daqmx_task& trigger(_In_ const daqmx_time_trigger& trigger);

    /// <summary>
    /// Waits for the task to complete.
    /// </summary>
    /// <param name="timeout">The maximum amount of time to wait, in seconds.
    /// Use <c>DAQmx_Val_WaitInfinitely</c> (the default) to wait indefinitely.
    /// </param>
    /// <returns><see langword="true "/> if the task finished in time,
    /// <see langword="false" /> if the operation timed out.</returns>
    bool wait(_In_ const double timeout = DAQmx_Val_WaitInfinitely) const;

    daqmx_task& operator =(const daqmx_task&) = delete;

    daqmx_task& operator =(daqmx_task&&) = delete;

    /// <summary>
    /// Configures the given analog current channel as part of the task.
    /// </summary>
    /// <param name="rhs"></param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    daqmx_task& operator +=(_In_ const daqmx_current_channel& rhs);

    /// <summary>
    /// Configures the given computed power channel as part of the task.
    /// </summary>
    /// <param name="rhs"></param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    daqmx_task& operator +=(_In_ const daqmx_power_channel& rhs);

    /// <summary>
    /// Configures the given analog voltage channel as part of the task.
    /// </summary>
    /// <param name="rhs"></param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    daqmx_task& operator +=(_In_ const daqmx_voltage_channel& rhs);

    /// <summary>
    /// Indicates whether the instance is valid.
    /// </summary>
    /// <returns><see langword="true" /> if the instance is valid,
    /// <see langword="false" /> otherwise.</returns>
    inline operator bool(void) const noexcept {
        return (this->_handle != nullptr);
    }

    /// <summary>
    /// Exposes the native task handle.
    /// </summary>
    /// <returns>The native task handle. The object remains owner of the
    /// handle.</returns>
    inline operator TaskHandle(void) const noexcept {
        return this->_handle;
    }

private:

    TaskHandle _handle;
    detail::daqmx_done_handler *_on_done;
    detail::daqmx_sample_handler *_on_sample;
};

PWROWG_NAMESPACE_END

#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
#endif /* !defined(_PWROWG_DAQMX_TASK_H) */
