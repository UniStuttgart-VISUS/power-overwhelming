// <copyright file="custom_sampler_base.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <chrono>
#include <map>
#include <memory>
#include <mutex>
#include <sstream>
#include <thread>
#include <vector>

#include "visus/pwrowg/async_sampling.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// The base class for a fully customised sampler that manages the
    /// association of threads to sensors by itself.
    /// </summary>
    /// <typeparam name="TDerived">The specific implementation of the custom
    /// sampler, which must provide the <c>sample</c> method. This is for
    /// implementing the CRTP.</typeparam>
    /// <typeparam name="TKey">The type that is used to group the sensors.
    /// </typeparam>
    /// <typeparam name="TSensor">The type to reference a sensor, which is
    /// typically the implementation object that can outlive sensor instances
    /// that are moved.</typeparam>
    template<class TDerived, class TKey, class TSensor>
    class custom_sampler_base {

    public:

        /// <summary>
        /// The type used to specify the sampling interval.
        /// </summary>
        typedef std::chrono::duration<async_sampling::microseconds_type,
            std::micro> interval_type;

        /// <summary>
        /// The type that is used to group the sensors.
        /// </summary>
        typedef TKey key_type;

        /// <summary>
        /// The type to reference a sensor, which is typically the
        /// implementation object that can outlive sensor instances that are
        /// moved.
        /// </summary>
        typedef TSensor *sensor_type;

        /// <summary>
        /// The default sampler instance.
        /// </summary>
        static custom_sampler_base default_sampler;

        /// <summary>
        /// Finalises the instance.
        /// </summary>
        virtual ~custom_sampler_base(void) noexcept;

        void add(_In_ const key_type& key, _In_ sensor_type sensor);

        /// <summary>
        /// Remove <paramref name="sensor" /> from being sampled.
        /// </summary>
        /// <param name="sensor">The sensor to be removed.</param>
        /// <returns><c>true</c> if the sampler has no sensors to sample any
        /// more, <c>false</c> if there are other sensors being sampled.
        /// </returns>
        bool remove(_In_ const sensor_type sensor);

    protected:

        /// <summary>
        /// The sensor group that is defined by a single
        /// <see cref="key_type" />.
        /// </summary>
        struct sensor_group {
            interval_type interval;
            std::mutex lock;
            std::vector<sensor_type> sensors;
            std::thread thread;
        };

        custom_sampler_base(void) = default;

    private:

        mutable std::mutex _lock;
        std::map<key_type, std::unique_ptr<sensor_group>> _sensor_groups;

    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */

#include "custom_sampler_base.inl"
