// <copyright file="sampler_context.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <stdexcept>

#include "async_measurement_data_source.h"
#include "with_context.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// Generic implementation for a container grouping a sampler source and its
    /// configuration.
    /// </summary>
    /// <typeparam name="TSource">The type of the sensor source, which must
    /// derive from <see cref="async_measurement_data_source" /> or provide a
    /// similar interface in order to be used with the generic implementation of
    /// a sampler for inherently synchronous sensors.</typeparam>
    /// <typeparam name="TContext">An additional user-defined context type that
    /// is optionally (if not <c>void</c>, which is the default) stored along
    /// the sensor source and configuration.</typeparam>
    template<class TSource, class TContext = void>
    struct basic_sampler_context : public with_context<TContext> {

        /// <summary>
        /// The type of the source that provides the samples.
        /// </summary>
        typedef TSource source_type;

        /// <summary>
        /// The asynchronous sampling configuration for the source, which most
        /// notably includes the callback to be invoked along with the context
        /// pointer that has to be passed to the callback.
        /// </summary>
        async_sampling configuration;

        /// <summary>
        /// A pointer to the source of the data.
        /// </summary>
        source_type *source;

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="source">The source that is being sampled.</param>
        /// <param name="configuration">The sampling configuration, most notably
        /// the callback to be invoked.</param>
        /// <exception cref="std::invalid_argument">If
        /// <paramref name="source " /> is <c>nullptr</c>, or if no valid
        /// callback is set in <paramref name="configuration" />.</exception>
        basic_sampler_context(_In_ source_type *source,
            _Inout_ async_sampling&& configuration);

        basic_sampler_context(_Inout_ basic_sampler_context&&) = default;

        basic_sampler_context& operator =(
            _Inout_ basic_sampler_context&&) = default;
    };


    /// <summary>
    /// The standard sampler context that is used for sensors that are
    /// inherently synchronous and need to be sampled by a dedicated thread to
    /// obtain and deliver data periodically.
    /// </summary>
    /// <remarks>
    /// <para>This implementation assumes that the implementation <c>struct</c>
    /// used by the sensor is derived from
    /// <see cref="async_measurement_data_source" /> and therefore can be used
    /// polymorphically. Implementors are, however, free to provide their own
    /// implementation, which, however, will not be able to sample from the same
    /// threads as the default implementation. In order to minimise the number
    /// of sampler threads being used for the same sampling interval, it is
    /// strongly recommended to use the default implementation and provide the
    /// required interface for it.</para>
    /// </remarks>
    typedef basic_sampler_context<async_measurement_data_source>
        sampler_context;

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */

#include "sampler_context.inl"
