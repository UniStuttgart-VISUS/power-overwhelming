﻿// <copyright file="stable_power_state_scope.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_STABLE_POWER_STATE_SCOPE_H)
#define _PWROWG_STABLE_POWER_STATE_SCOPE_H
#pragma once

#include "visus/pwrowg/graphics_device.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// A RAII object that puts one or more GPUs into a stable power state, ie
/// disables GPU boost for these devices to produce a more predictable
/// behaviour.
/// </summary>
class POWER_OVERWHELMING_API stable_power_state_scope final {

public:

    /// <summary>
    /// Initialises a new instance putting all supported devices into a
    /// stable power state.
    /// </summary>
    stable_power_state_scope(void);

    /// <summary>
    /// Initialises a new instance putting the specified device into a
    /// stable power state.
    /// </summary>
    /// <param name="device">The device to be put into a stable power
    /// state.</param>
    stable_power_state_scope(_In_ graphics_device& device);

    stable_power_state_scope(const stable_power_state_scope&) = delete;

    /// <summary>
    /// Finalise the instance.
    /// </summary>
    ~stable_power_state_scope(void);

    /// <summary>
    /// Answer the number of devices covered by this scope.
    /// </summary>
    /// <returns>The number of devices that have been put into stable
    /// power state by this scope.</returns>
    inline std::size_t size(void) const noexcept {
        return this->_cnt_devices;
    }

    stable_power_state_scope& operator =(
        const stable_power_state_scope&) = delete;

private:

    void enable(_In_ graphics_device::device_type *device);

    std::size_t _cnt_devices;
    graphics_device *_devices;

};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_STABLE_POWER_STATE_SCOPE_H) */
