﻿// <copyright file="emi_device_factory.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_EMI_DEVICE_FACTORY_H)
#define _PWROWG_EMI_DEVICE_FACTORY_H
#pragma once

#include <cassert>
#include <memory>
#include <mutex>
#include <unordered_map>

#include "emi_device.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// A factory class that allows for reusing <see cref="emi_device" /> instances
/// for multiple sensors.
/// </summary>
/// <remarks>
/// <para>The factory is thread-safe.</para>
/// </remarks>
class emi_device_factory final {

public:

    /// <summary>
    /// The type of devices created by the factory.
    /// </summary>
    typedef std::shared_ptr<emi_device> device_type;

    /// <summary>
    /// The type used to specify device names.
    /// </summary>
    typedef emi_device::string_type string_type;

    /// <summary>
    /// Creates a new instance or reuses and existing one for the same
    /// device.
    /// </summary>
    /// <param name="path">The path to the EMI device.</param>
    static device_type create(const string_type& path);

    /// <summary>
    /// Clear all cached instances.
    /// </summary>
    /// <remarks>
    /// <para>Clearing the cache does not affect instances that are still in
    /// use. However, if a device that is still in use is subsequently
    /// requested from the factory, a new handle will be created instead of
    /// using the existing one.</para>
    /// </remarks>
    static void clear(void);

private:

    static std::unordered_map<string_type, device_type> _instances;
    static std::mutex _lock;
};

PWROWG_DETAIL_NAMESPACE_END

#endif /* !defined(_PWROWG_EMI_DEVICE_FACTORY_H) */
