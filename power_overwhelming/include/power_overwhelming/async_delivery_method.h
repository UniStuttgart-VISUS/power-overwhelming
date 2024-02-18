// <copyright file="async_delivery_method.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Possible delivery methods for asynchronous samples.
    /// </summary>
    enum class async_delivery_method {

        /// <summary>
        /// Delivers to a <see cref="measurement_callback" />.
        /// </summary>
        on_measurement,

        /// <summary>
        /// Delivers to an
        /// <see cref="async_sampling::on_measurement_data_callback" />.
        /// </summary>
        on_measurement_data,

        /// <summary>
        /// Delivers GPU throttling information to an
        /// <see cref="async_sampling::on_throttling_sample_callback" />.
        /// </summary>
        on_throttling_sample,
    };

} /* namespace power_overwhelming */
} /* namespace visus */
