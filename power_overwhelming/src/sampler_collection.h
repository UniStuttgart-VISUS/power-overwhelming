// <copyright file="sampler_collection.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <vector>

#include "sampler.h"


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
        /// The type used to specify the sampling interval.
        /// </summary>
        typedef std::chrono::duration<async_sampling::microseconds_type,
            std::micro> interval_type;

        /// <summary>
        /// The type of samplers that are managed by this collection.
        /// </summary>
        typedef TSampler sampler_type;

        /// <summary>
        /// The type of data sources that are sampled by the samplers in this
        /// collection.
        /// </summary>
        typedef typename TSampler::source_type source_type;

        /// <summary>
        /// The default sampler collection, which should be used by most of the
        /// sensors unless they have specific needs for different behaviour.
        /// </summary>
        static basic_sampler_collection default;

        basic_sampler_collection(void) = default;

        basic_sampler_collection(const basic_sampler_collection&) = delete;

        bool add(_In_ source_type source, _Inout_ async_sampling&& sampling);

        /// <summary>
        /// Removes the given source from all of the samplers in the collection.
        /// </summary>
        /// <param name="source">The source to be removed. It is safe to pass
        /// <c>nullptr</c>, in which case nothing will be done.</param>
        /// <returns><c>true</c> if the source was removed, <c>false</c>
        /// otherwise.</returns>
        bool remove(_In_ const source_type source);

        basic_sampler_collection& operator =(
            const basic_sampler_collection&) = delete;

        /// <summary>
        /// Answer whether there is any sampler in the collection.
        /// </summary>
        /// <returns><c>true</c> if there is at least one sampler running in
        /// this collection, <c>false</c> otherwise.</returns>
        operator bool(void) const;

    private:

        mutable std::mutex _lock;
        std::vector<std::unique_ptr<sampler_type>> _samplers;
    };


    /// <summary>
    /// The generic sampler collection that uses a thread per intervall to
    /// periodically poll all registered sensors.
    /// </summary>
    typedef basic_sampler_collection<sampler> sampler_collection;

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
