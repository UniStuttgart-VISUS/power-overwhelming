// <copyright file="emi_sensor_impl.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <string>

#include <Windows.h>
#include <emi.h>
#include <SetupAPI.h>

#include "sampler.h"
#include "timestamp.h"

#pragma comment(lib, "Setupapi.lib")


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// Private data container for the <see cref="emi_sensor" />.
    /// </summary>
    struct emi_sensor_impl final {

        /// <summary>
        /// A sampler for EMI sensors.
        /// </summary>
        static sampler<default_sampler_context<emi_sensor_impl>> sampler;

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

        /// <summary>
        /// Sample the sensor.
        /// </summary>
        /// <param name="resolution">The resolution of the timestamp to be
        /// generated, which defaults to milliseconds.</param>
        /// <returns>A measurement from the sensor.</returns>
        measurement sample(const timestamp_resolution resolution
            = timestamp_resolution::milliseconds) const;
    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
