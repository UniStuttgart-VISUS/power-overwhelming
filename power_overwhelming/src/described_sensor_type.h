// <copyright file="described_sensor_type.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// Allows for deriving the type of a sensor from a descriptor instance.
    /// </summary>
    /// <typeparam name="TDesc">The descriptor to derive the sensor of.
    /// </typeparam>
    template<class TDesc> struct described_sensor_type final { };

    /// <summary>
    /// Specialisation for valid descriptors.
    /// </summary>
    template<class TSensor, template<class> class TDesc>
    struct described_sensor_type <TDesc<TSensor>> final {

        /// <summary>
        /// The type of the sensor described by <typeparamref name="TDesc" />.
        /// </summary>
        typedef TSensor type;
    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
