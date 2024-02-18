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
        /// Delivers to a
        /// </summary>
        on_measurement,
        on_measurement_data
    };

} /* namespace power_overwhelming */
} /* namespace visus */
