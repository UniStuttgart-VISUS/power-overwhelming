// <copyright file="daqmx_sensor_trigger.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_DAQMX_SENSOR_TRIGGER_H)
#define _PWROWG_DAQMX_SENSOR_TRIGGER_H
#pragma once

#include <exception>

#include "visus/pwrowg/parallel_port_trigger.h"
#include "visus/pwrowg/rtx_acquisition.h"
#include "visus/pwrowg/rtx_trigger.h"
#include "visus/pwrowg/type_erased_storage.h"


PWROWG_NAMESPACE_BEGIN

// Forward declarations.
namespace detail { class daqmx_sensor; }
namespace detail { struct daqmx_sensor_trigger_impl; }
namespace detail { class daqmx_sen_trg_bld_chan0; }
namespace detail { class daqmx_sen_trg_bld_final; }
namespace detail { class daqmx_sen_trg_bld_par0; }
namespace detail { class daqmx_sen_trg_bld_par1; }
namespace detail { class daqmx_sen_trg_bld_par2; }
namespace detail { class daqmx_sen_trg_bld_par3; }


/// <summary>
/// Configures how the DAQmx-based sensor will be triggered.
/// </summary>
class POWER_OVERWHELMING_API daqmx_sensor_trigger final {

public:

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    daqmx_sensor_trigger(void);

    /// <summary>
    /// Clone <paramref name="other" />.
    /// </summary>
    /// <param name="other">The object to be cloned.</param>
    daqmx_sensor_trigger(_In_ const daqmx_sensor_trigger& other);

    /// <summary>
    /// Initialise from move.
    /// </summary>
    /// <param name="other">The object to be moved.</param>
    daqmx_sensor_trigger(_Inout_ daqmx_sensor_trigger&& other) noexcept;

    /// <summary>
    /// Finalises the instance.
    /// </summary>
    inline ~daqmx_sensor_trigger(void) noexcept {
        this->reset(nullptr);
    }

    /// <summary>
    /// Triggers the oscilloscope as soon as any ongoing acquisition has
    /// finished.
    /// </summary>
    /// <typeparam name="TDone">The type of the callback to be invoked when
    /// the acquisition was fully processed by the RTX sensor controller
    /// thread. This must be a callable type accepting no arguments and
    /// returning <see langword="void" />.</typeparam>
    /// <typeparam name="TFailed">The type of the callback to be invoked when
    /// when RTX sensor controller asynchronously encounters an error while
    /// processing the waveforms. This must be a callable type accepting an
    /// <see cref="std::exception_ptr" /> and returning
    /// <see langword="bool" />. If the callback returns <see cref="true" />,
    /// the thread will continue processing the next acquisitions. Otherwise,
    /// the error will be propagated and cause the application to exit.
    /// </typeparam>
    /// <param name="when_done">The callback to be invoked when the acquisition
    /// was processed.</param>
    /// <param name="when_failed">The callback to be invoked when an error was
    /// encountered.</param>
    /// <returns><see langword="true" /> if the trigger was acknowledged,
    /// <see langword="false" /> if the trigger was not issued as the sensor is
    /// shutting down.</returns>
    template<class TDone, class TFailed>
    bool acquire(_In_ TDone&& when_done, _In_ TFailed&& when_failed) {
        type_erased_storage done, failed;
        done.emplace<TDone>(std::forward<TDone>(when_done));
        failed.emplace<TFailed>(std::forward<TFailed>(when_failed));

        return this->acquire(
            [](const type_erased_storage& c) {
                (*c.template get<TDone>())();
            },
            std::move(done),
            [](const std::exception_ptr ex, const type_erased_storage& c) {
                return (*c.template get<TFailed>())(ex);
            },
            std::move(failed));
    }

    /// <summary>
    /// Triggers the oscilloscope as soon as any ongoing acquisition has
    /// finished.
    /// </summary>
    /// <typeparam name="TDone">The type of the callback to be invoked when
    /// the acquisition was fully processed by the RTX sensor controller
    /// thread. This must be a functor type accepting no arguments and returning
    /// <see langword="void" />.</typeparam>
    /// <param name="done">The callback to be invoked when the acquisition was
    /// processed.</param>
    /// <returns><see langword="true" /> if the trigger was acknowledged,
    /// <see langword="false" /> if the trigger was not issued as the sensor is
    /// shutting down.</returns>
    template<class TDone> bool acquire(_In_ TDone&& done) {
        type_erased_storage when_done;
        when_done.emplace<TDone>(std::forward<TDone>(done));

        return this->acquire(
            [](const type_erased_storage& c) { (*c.template get<TDone>())(); },
            std::move(when_done),
            daqmx_sensor_trigger::fatal_failure,
            type_erased_storage());
    }

    /// <summary>
    /// Triggers the oscilloscope as soon as any ongoing acquisition has
    /// finished.
    /// </summary>
    /// <returns><see langword="true" /> if the trigger was acknowledged,
    /// <see langword="false" /> if the trigger was not issued as the sensor is
    /// shutting down.</returns>
    inline bool acquire(void) {
        return this->acquire(
            [](const type_erased_storage&) { },
            type_erased_storage(),
            daqmx_sensor_trigger::fatal_failure,
            type_erased_storage());
    }

    /// <summary>
    /// Assignment.
    /// </summary>
    /// <param name="rhs">The right-hand-side operand.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    daqmx_sensor_trigger& operator =(_In_ const daqmx_sensor_trigger& rhs);

    /// <summary>
    /// Move assignment.
    /// </summary>
    /// <param name="rhs">The right-hand-side operand.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    daqmx_sensor_trigger& operator =(
        _Inout_ daqmx_sensor_trigger&& rhs) noexcept;

    /// <summary>
    /// Answer whether this instance is valid.
    /// </summary>
    /// <returns><see langword="true" /> if this instance is valid, i.e. holds a
    /// valid implementation, <see langword="false" /> otherwise.</returns>
    inline operator bool(void) const noexcept {
        return (this->_impl != nullptr);
    }

private:

    static bool fatal_failure(const std::exception_ptr,
        const type_erased_storage&) noexcept;

    bool acquire(
        _In_ void (*done)(const type_erased_storage&),
        _Inout_ type_erased_storage&& done_context,
        _In_ bool (*failed)(const std::exception_ptr,
            const type_erased_storage&),
        _Inout_ type_erased_storage&& failed_context);

    bool reset(_In_opt_ detail::daqmx_sensor_trigger_impl *impl) noexcept;

    detail::daqmx_sensor_trigger_impl *_impl;

    friend class detail::daqmx_sensor;
    friend class detail::daqmx_sen_trg_bld_chan0;
    friend class detail::daqmx_sen_trg_bld_final;
    friend class detail::daqmx_sen_trg_bld_par0;
    friend class detail::daqmx_sen_trg_bld_par1;
    friend class detail::daqmx_sen_trg_bld_par2;
    friend class detail::daqmx_sen_trg_bld_par3;
    friend class daqmx_sensor_trigger_builder;
};

PWROWG_NAMESPACE_END

#endif /*!defined(_PWROWG_DAQMX_SENSOR_TRIGGER_H) */
