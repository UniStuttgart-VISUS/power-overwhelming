// <copyright file="device_sampler_source.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <algorithm>
#include <mutex>
#include <map>
#include <vector>

#include "power_overwhelming/sampler_source.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// Implements a specialised <see cref="sampler_source" /> for sensors that
    /// are working on shared &quot;devices&quot;.
    /// </summary>
    /// <remarks>
    /// <para>This source groups the sensors by the device they are using and
    /// samples the device once and then has the sensors using the device
    /// evaluate the &quot;raw&quot; sample. The sensor must implement a
    /// <c>static sample</c> method and an instance <c>evaluate_async</c>
    /// method for this to work. The template is currently used by the
    /// <see cref="emi_sensor_impl" /> to implement asynchronous sampling.
    /// </para>
    /// </remarks>
    /// <typeparam name="TSensor">The type of the sensor, typically its
    /// implementation class.</typeparam>
    /// <typeparam name="TDevice">The type of the device being sampled.
    /// </typeparam>
    template<class TSensor, class TDevice>
    class device_sampler_source final : public sampler_source {

    public:

        typedef TDevice device_type;

        typedef TSensor *sensor_type;

        typedef device_sampler_source *source_type;

        static _Ret_valid_ source_type create(_In_ sensor_type sensor);

        static bool release(_In_opt_ sensor_type sensor);

        /// <inheritdoc />
        bool deliver(void) const override;

        /// <inheritdoc />
        interval_type interval(void) const noexcept;

    private:

        static std::mutex _lock;
        static std::map<device_type, source_type> _sources;

        device_sampler_source(_In_ sensor_type sensor);

        std::vector<sensor_type> _sensors;
    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */

#include "device_sampler_source.inl"
