// <copyright file="throttling_sample.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "visus/pwrowg/throttling_state.h"


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Container for samples from a <see cref="throttling_sensor" />.
    /// </summary>
    class POWER_OVERWHELMING_API throttling_sample final {

    public:

        /// <summary>
        /// The type of a timestamp associated with the sample.
        /// </summary>
        typedef power_overwhelming::timestamp timestamp_type;

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="timestamp">The timestamp when the sample was obtained.
        /// </param>
        /// <param name="state">The throttling state.</param>
        inline throttling_sample(
                _In_ const timestamp_type timestamp = timestamp_type::zero,
                _In_ const throttling_state state = throttling_state::none)
            : _state(state), _timestamp(timestamp) { }

        /// <summary>
        /// Gets the throttling state.
        /// </summary>
        /// <returns>The throttling state of the GPU.</returns>
        inline throttling_state state(void) const noexcept {
            return this->_state;
        }

        /// <summary>
        /// Answer whether <paramref name="state" /> indicates that the GPU is
        ///  throttled.
        /// </summary>
        /// <returns><c>true</c> if the GPU indicated that it is throttled,
        /// <c>false</c> otherwise.</returns>
        inline bool throttled(void) const noexcept {
            return (this->_state != throttling_state::none);
        }

        /// <summary>
        /// Gets the timestamp of the sample.
        /// </summary>
        /// <returns>The timestamp in the unit requested from the sensor.
        /// </returns>
        inline timestamp_type timestamp(void) const noexcept {
            return this->_timestamp;
        }

    private:

        throttling_state _state;
        timestamp_type _timestamp;
    };

} /* namespace power_overwhelming */
} /* namespace visus */
