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
    /// <para>The interface is used by the generic sampler implementation and
    /// manages the callback registered and the sample delivery. It is held
    /// generic in that implementors manage more than once callback in this
    /// class. Some implementations might be so special that they have their
    /// own threads and therefore completely bypass this interface.</para>
    /// </remarks>
    class async_measurement_data_source {

    public:

        /// <summary>
        /// Synchronously delivers a sample to the registered callback or
        /// callbacks.
        /// </summary>
        virtual void deliver_async(void) const = 0;

        /// <summary>
        /// Changes the asynchronous sampling configuration.
        /// </summary>
        /// <param name="sampling">The new configuration object.</param>
        virtual void update_async(_Inout_ async_sampling&& sampling) = 0;

    protected:

        async_measurement_data_source(void) = default;
    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
