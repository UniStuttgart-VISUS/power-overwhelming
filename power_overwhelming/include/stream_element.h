// <copyright file="stream_element.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <chrono>


namespace visus {
namespace power_overwhelming {

    template<class TTimestamp = std::chrono::high_resolution_clock::time_point>
    class stream_element {

    public:

        /// <summary>
        /// The type of a timestamp associated with a measurement.
        /// </summary>
        typedef TTimestamp timestamp_type;

        /// <summary>
        /// Gets the timestamp of the measurement.
        /// </summary>
        /// <returns>The timestamp of the element.</returns>
        inline timestamp_type timestamp(void) const noexcept {
            return this->_timestamp;
        }

    private:

        timestamp_type _timestamp;
    };

} /* namespace power_overwhelming */
} /* namespace visus */
