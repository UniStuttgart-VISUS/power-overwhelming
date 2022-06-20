// <copyright file="collector_impl.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/sensor.h"

#include <memory>
#include <string>
#include <vector>


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// Private data container for <see cref="collector" />.
    /// </summary>
    struct collector_impl final {

        /// <summary>
        /// The desired sampling interval.
        /// </summary>
        sensor::microseconds_type sampling_interval;

        /// <summary>
        /// The list of sensors.
        /// </summary>
        std::vector<std::unique_ptr<sensor>> sensors;

        /// <summary>
        /// The output stream for the results.
        /// </summary>
        std::ofstream stream;
    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
