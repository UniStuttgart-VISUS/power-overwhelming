// <copyright file="emi_sensor_impl.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <memory>

#include "emi_device.h"
#include "sampler.h"
#include "timestamp.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// Private data container for the <see cref="emi_sensor" />.
    /// </summary>
    struct emi_sensor_impl final {

#if defined(_WIN32)
        /// <summary>
        /// A sampler for EMI sensors.
        /// </summary>
        static sampler<default_sampler_context<emi_sensor_impl>> sampler;

        /// <summary>
        /// The RAII wrapper for the EMI device handle.
        /// </summary>
        std::shared_ptr<emi_device> device;

        /// <summary>
        /// The sensor name.
        /// </summary>
        std::wstring sensor_name;

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        inline emi_sensor_impl(void) { }

        /// <summary>
        /// Finalises the instance.
        /// </summary>
        ~emi_sensor_impl(void);

        std::size_t sample(void *dst, const ULONG cnt);

        void set(const std::shared_ptr<emi_device>& device,
            const std::basic_string<TCHAR>& path,
            const std::uint16_t channel);
#endif /* defined(_WIN32) */
    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
