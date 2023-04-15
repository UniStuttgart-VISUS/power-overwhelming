// <copyright file="msr_sensor_impl.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "power_overwhelming/msr_sensor.h"
#include "power_overwhelming/measurement.h"

#include "msr_device.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// Private data container for the <see cref="msr_sensor" />.
    /// </summary>
    struct msr_sensor_impl final {

        /// <summary>
        /// A sampler for MSR sensors.
        /// </summary>
        //static detail::sampler<emi_sampler_context> sampler;

        /// <summary>
        /// The sensor name.
        /// </summary>
        std::wstring sensor_name;

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        inline msr_sensor_impl(void) { }

        /// <summary>
        /// Finalises the instance.
        /// </summary>
        ~msr_sensor_impl(void);

    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
