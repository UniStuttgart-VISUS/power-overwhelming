// <copyright file="basic_sampler_source.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <memory>
#include <stdexcept>

#include "visus/pwrowg/sampler_source.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// A generic implementation that can be used to attach asynchronous
    /// sampling behaviour to sensor implementation structures by inheriting
    /// from this structure.
    /// </summary>
    /// <typeparam name="TDerived">The derived type inheriting from the
    /// template (CRTP).</typeparam>
    template<class TDerived>
    struct basic_sampler_source : public sampler_source {

        /// <summary>
        /// Stores the asynchronous sampling configuration for the source
        /// derived from this class.
        /// </summary>
        power_overwhelming::async_sampling async_sampling;

        /// <inheritdoc />
        bool deliver(void) const override;

        /// <inheritdoc />
        interval_type interval(void) const noexcept override;
    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */

#include "basic_sampler_source.inl"
