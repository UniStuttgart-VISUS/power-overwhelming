// <copyright file="device_sampler_source.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "sampler_source.h"

#include <mutex>
#include <map>


namespace visus {
namespace power_overwhelming {
namespace detail {

    template<class TSensor, class TDevice>
    class device_sampler_source final : public sampler_source {

    public:

        typedef TDevice device_type;

        typedef TSensor *sensor_type;

        typedef device_sampler_source *source_type;

        static _Ret_valid_ source_type create(_In_ sensor_type sensor);

        /// <inheritdoc />
        bool deliver(void) const override;

        /// <inheritdoc />
        interval_type interval(void) const noexcept;

    private:

        static std::mutex _lock;
        static std::map<device_type, source_type> _sources;

        device_sampler_source(void);

        sensor_type _sensor;
    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */

#include "device_sampler_source.inl"
