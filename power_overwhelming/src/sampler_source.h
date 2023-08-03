﻿// <copyright file="sampler_source.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <chrono>

#include "power_overwhelming/async_sampling.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// This class defines the interface for sources that can be sampled by the
    /// generic <see cref="sampler_thread" />.
    /// </summary>
    /// <remarks>
    /// <para>Sensors that are inherently synchronous can use the template
    /// <see cref="basic_sampler_source" /> to make their implementation object
    /// a source of asynchronous samples without any additional implementation
    /// effort.</para>
    /// </remarks>
    class sampler_source {

    public:

        /// <summary>
        /// The type used to specify the sampling interval.
        /// </summary>
        typedef std::chrono::duration<async_sampling::microseconds_type,
            std::micro> interval_type;

        /// <summary>
        /// Synchronously delivers a sample to the registered callback or
        /// callbacks.
        /// </summary>
        /// <remarks>
        /// <para>If this method returns <c>false</c>, the sampler must
        /// unregister the source immediately and not use it again for any
        /// purpose. Callers shall treat the pointer to a source returning
        /// <c>false</c> as dangling references.</para>
        /// </remarks>
        /// <returns><c>true</c> if a sample was delivered and the source can and
        /// should be sampled again in the future, <c>false</c> otherwise.
        /// </returns>
        virtual bool deliver(void) const = 0;

        /// <summary>
        /// Answers the requested sampling interval of the source.
        /// </summary>
        /// <returns>The requested sampling interval.</returns>
        virtual interval_type interval(void) const noexcept = 0;
    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */