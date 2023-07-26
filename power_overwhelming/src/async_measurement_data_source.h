// <copyright file="async_measurement_data_source.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "power_overwhelming/async_sampling.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// The interface that sensor implementations must implement to be able to
    /// be used with the generic asynchronous sampler implementation.
    /// </summary>
    /// <remarks>
    /// 
    /// </remarks>
    class async_measurement_data_source {

    public:

        /// <summary>
        /// The type of the callback that receives asynchronous samples.
        /// </summary>
        typedef async_sampling::on_measurement_data_callback async_callback;

        /// <summary>
        /// Delivers one or more samples to the specified callback for
        /// asynchronous <see cref="measurement_data" />.
        /// </summary>
        /// <remarks>
        /// <para>Sensor implementations using the default sampler
        /// implementation must provide their samples via this method.</para>
        /// </remarks>
        /// <param name="sampling">The sampling configuration that determines
        /// where to deliver the samples.</param>
        virtual void sample(_In_ const async_sampling& sampling) const = 0;

    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
