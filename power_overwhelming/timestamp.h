// <copyright file="timestamp.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <chrono>


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Implements a generator for timestamps from STL clocks.
    /// </summary>
    /// <remarks>
    /// While the default implementation assumes that
    /// <typeparamref name="TTimestamp" /> is the time point of an STL clock,
    /// and derives the clock from that. It is, however, possible to use custom
    /// types of timestamps by providing a template specialisation for that
    /// type.
    /// </remarks>
    /// <typeparam name="TTimestamp">The type of the timestamp. For the default
    /// implementation it is assume that this is an STL time point.</typeparam>
    template<class TTimestamp> class timestamp {

    public:

        /// <summary>
        /// The value type of the time stamp.
        /// </summary>
        typedef TTimestamp value_type;

        /// <summary>
        /// Samples the underlying clock of <see cref="value_type" /> to
        /// create new timestamp.
        /// </summary>
        /// <returns>A new timestamp for the current point in time.</returns>
        static inline value_type create(void) {
            return typename value_type::clock::now();
        }
    };

} /* namespace power_overwhelming */
} /* namespace visus */
