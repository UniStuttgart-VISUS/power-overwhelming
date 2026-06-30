// <copyright file="daqmx_task.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_DAQMX_TASK_H)
#define _PWROWG_DAQMX_TASK_H
#pragma once
#if defined(POWER_OVERWHELMING_WITH_DAQMX)

#include "visus/pwrowg/daqmx_current_channel.h"
#include "visus/pwrowg/daqmx_implicit_timing.h"
#include "visus/pwrowg/daqmx_power_channel.h"
#include "visus/pwrowg/daqmx_sample_clock_timing.h"
#include "visus/pwrowg/daqmx_voltage_channel.h"
#include "visus/pwrowg/type_erased_storage.h"


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
    /// Sets a callback to be invoked when the task is completed.
    /// </summary>
    /// <typeparam name="TCallback"></typeparam>
    /// <param name="callback"></param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    template<class TCallback> daqmx_task& on_done(_In_ TCallback&& callback);

    /// <summary>
    /// Clears the callback for the task completion event.
    /// </summary>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    inline daqmx_task& on_done(const std::nullptr_t) {
        this->_on_done.reset();
        this->set_on_done(nullptr);
        return *this;
    }

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
    /// Waits for the task to complete.
    /// </summary>
    /// <param name="timeout">The maximum amount of time to wait, in seconds.
    /// Use <c>DAQmx_Val_WaitInfinitely</c> (the default) to wait indefinitely.
    /// </param>
    /// <returns><see langword="true "/> if the task finished in time,
    /// <see langword="false" /> if the operation timed out.</returns>
    bool wait(_In_ const double timeout = DAQmx_Val_WaitInfinitely) const;

    daqmx_task& operator =(const daqmx_task&) = delete;

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
    operator bool(void) const noexcept {
        return (this->_handle != nullptr);
    }

private:

    static int32 CVICALLBACK done_callback(_In_ const TaskHandle task,
        _In_ const int32 status, _In_ void *context);

    static int32 CVICALLBACK sample_callback(_In_ const TaskHandle task,
        _In_ const int32 type, _In_ const uInt32 cnt, _In_ void *context);

    void set_on_done(_In_opt_ DAQmxDoneEventCallbackPtr cb = done_callback);

    void set_on_sample(_In_opt_ DAQmxEveryNSamplesEventCallbackPtr cb);

    TaskHandle _handle;
    type_erased_storage _on_done;
    type_erased_storage _on_sample;
};

PWROWG_NAMESPACE_END

#include "visus/pwrowg/daqmx_task.inl"

#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
#endif /* !defined(_PWROWG_DAQMX_TASK_H) */
