// <copyright file="msr_device_factory.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cassert>
#include <memory>
#include <mutex>
#include <unordered_map>

#include "msr_device.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// A factory class that allows for reusing <see cref="msr_device" />
    /// instances for multiple sensors.
    /// </summary>
    /// <remarks>
    /// <para>The factory is thread-safe.</para>
    /// </remarks>
    class msr_device_factory final {

    public:

        /// <summary>
        /// The type used to identify a CPU core.
        /// </summary>
        typedef msr_device::core_type core_type;

        /// <summary>
        /// The type of devices created by the factory.
        /// </summary>
        typedef std::shared_ptr<msr_device> device_type;

        /// <summary>
        /// The type used to specify device names.
        /// </summary>
        typedef msr_device::string_type string_type;

        /// <summary>
        /// Creates a new instance or reuses and existing one for the same
        /// device.
        /// </summary>
        /// <param name="path">The path to the MSR device.</param>
        static device_type create(_In_ const string_type& path);

        /// <summary>
        /// Creates a new instance or reuses and existing one for the MSR device
        /// of the specified CPU core.
        /// </summary>
        /// <param name="core">The zero-based index of the CPU core to open the
        /// MSR device file for.</param>
        static device_type create(_In_ const core_type core);

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

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
