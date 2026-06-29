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
#include "visus/pwrowg/daqmx_power_channel.h"
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

    /// <summary>
    /// Initialise from move.
    /// </summary>
    /// <param name="other">The object to be moved.</param>
    daqmx_task(_Inout_ daqmx_task&& other) noexcept;

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
    /// Starts the task.
    /// </summary>
    void start(void);

    /// <summary>
    /// Stops the task.
    /// </summary>
    void stop(void);

    /// <summary>
    /// Waits for the task to complete.
    /// </summary>
    /// <param name="timeout">The maximum amount of time to wait, in seconds.
    /// Use <c>DAQmx_Val_WaitInfinitely</c> (the default) to wait indefinitely.
    /// </param>
    /// <returns><see langword="true "/> if the task finished in time,
    /// <see langword="false" /> if the operation timed out.</returns>
    bool wait(_In_ const double timeout = DAQmx_Val_WaitInfinitely) const;

    /// <summary>
    /// Move assignment.
    /// </summary>
    /// <param name="rhs">The right-hand-side operand.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    daqmx_task& operator =(_Inout_ daqmx_task&& rhs) noexcept;

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

    TaskHandle _handle;
};

PWROWG_NAMESPACE_END

#endif /* defined(POWER_OVERWHELMING_WITH_DAQMX) */
#endif /* !defined(_PWROWG_DAQMX_TASK_H) */
