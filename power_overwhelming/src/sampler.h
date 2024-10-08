﻿// <copyright file="sampler.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <map>

#include "power_overwhelming/sampler_source.h"

#include "sampler_thread.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// Manages the <see cref="sampler_thread" />s used for asynchronously
    /// sampling inherently synchronous sources.
    /// </summary>
    class sampler final {

    public:

        /// <summary>
        /// The type used to specify the sampling interval.
        /// </summary>
        typedef sampler_source::interval_type interval_type;

        /// <summary>
        /// The type of the source that provides the samples.
        /// </summary>
        typedef sampler_source *source_type;

        /// <summary>
        /// The default sampler that runs a thread for every configured sampling
        /// interval.
        /// </summary>
        static sampler default_sampler;

        /// <summary>
        /// Finalises the instance.
        /// </summary>
        /// <remarks>
        /// The destructor blocks until the sampler thread has exited.
        /// </remarks>
        ~sampler(void) noexcept;

        sampler& operator +=(_In_ source_type source);

        sampler& operator -=(_In_ source_type source);

        operator bool(void) const;

    private:

        mutable std::mutex _lock;
        std::map<interval_type, sampler_thread> _threads;
    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
