// <copyright file="sampler_collection.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <map>
#include <stdexcept>
#include <thread>

#include "basic_sampler.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// 
    /// </summary>
    /// <typeparam name="TSampler">The type of samplers that are managed by
    /// this collection.</typeparam>
    template<class TSampler> class basic_sampler_collection final {

    public:

        /// <summary>
        /// The type of samplers that are managed by this collection.
        /// </summary>
        typedef TSampler sampler_type;

    private:

        /// <summary>
        /// The list of sampling threads.
        /// </summary>
        std::vector<std::unique_ptr<context_type>> _contexts;

        /// <summary>
        /// A lock for protecting <see cref="_contexts" />.
        /// </summary>
        mutable std::mutex _lock;
    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
