// <copyright file="rtx_sampler.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "visus/pwrowg/rtx_instrument.h"

#include <string>

#include "custom_sampler_base.h"
#include "rtx_sensor_impl.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// A customised sampler for RTA/RTB instruments, which is required, because
    /// sampling these is very slow, so we need to spawn a thread for each
    /// instrument and dispatch a single sample to all sensors created on it.
    /// </summary>
    class rtx_sampler final : public custom_sampler_base<rtx_sampler,
            std::string, rtx_sensor_impl> {

    public:

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        rtx_sampler(void) = default;

    private:

        void sample(_In_ std::string path, _In_ sensor_group *group);

        friend class custom_sampler_base<rtx_sampler, std::string,
            rtx_sensor_impl>;

    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
