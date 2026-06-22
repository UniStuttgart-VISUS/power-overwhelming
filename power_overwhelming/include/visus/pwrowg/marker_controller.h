// <copyright file="marker_controller.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_MARKER_CONTROLLER_H)
#define _PWROWG_MARKER_CONTROLLER_H
#pragma once

#include <cassert>

#include "visus/pwrowg/timestamp.h"


PWROWG_NAMESPACE_BEGIN

// Forward declarations.
namespace detail { class marker_sensor; }


/// <summary>
/// The marker controller allows for controlling the marker sensor at runtime,
/// which is required for injecting the markers in the sensor stream.
/// </summary>
/// <remarks>
/// <para>The controller is fully thread-safe, so any thread can inject markers
/// at any time. Markers emitted while the sensor is not running will be
/// discarded.</para>
/// </remarks>
class POWER_OVERWHELMING_API marker_controller final {

public:

    /// <summary>
    /// The type fo the sensor controlled by this controller.
    /// </summary>
    typedef detail::marker_sensor sensor_type;

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <typeparam name="TIterator">An iterator over a range of marker sensors.
    /// </typeparam>
    /// <param name="begin">The begin of the marker sensors, which must be a
    /// valid iterator.</param>
    /// <param name="end">The end of the marker sensors, which must directly
    /// follow <paramref name="begin" /> as we expect exactly one sensor of this
    /// type.</param>
    template<class TIterator>
    marker_controller(_In_ TIterator begin, _In_ TIterator end)
            : _sensor(*begin) {
        assert(begin != end);
    }

    /// <summary>
    /// If the sensor is enabled, emit the specified marker event.
    /// </summary>
    /// <param name="timestamp">The timestamp of the marker event.</param>
    /// <param name="id">The index of the marker.</param>
    /// <returns><c>true</c> if the sample was actually emitted, <c>false</c>
    /// otherwise.</returns>
    bool emit(_In_ const timestamp timestamp, _In_ const unsigned int id);

    /// <summary>
    /// If the sensor is enabled, emit the specified marker event.
    /// </summary>
    /// <param name="id">The index of the marker.</param>
    /// <returns><c>true</c> if the sample was acutally emitted, <c>false</c>
    /// otherwise.</returns>
    inline bool emit(_In_ const unsigned int id) {
        return this->emit(timestamp::now(), id);
    }

    /// <summary>
    /// If the sensor is enabled, emit a marker event wit the built-in
    /// auto-incrementing ID.
    /// </summary>
    /// <remarks>
    /// The auto-incrementing ID is a counter starting at zero, which is
    /// incremented every time a marker is emitted. It is not influenced by
    /// any explicitly specified marker ID. It is also not reset when the
    /// sensor is stopped.
    /// </remarks>
    /// <param name="timestamp">The timestamp of the marker event.</param>
    /// <returns><c>true</c> if the sample was actually emitted, <c>false</c>
    /// otherwise.</returns>
    bool emit(_In_ const timestamp timestamp);

    /// <summary>
    /// If the sensor is enabled, emit a marker event wit the built-in
    /// auto-incrementing ID.
    /// </summary>
    /// <remarks>
    /// The auto-incrementing ID is a counter starting at zero, which is
    /// incremented every time a marker is emitted. It is not influenced by
    /// any explicitly specified marker ID. It is also not reset when the
    /// sensor is stopped.
    /// </remarks>
    /// <param name="timestamp">The timestamp of the marker event.</param>
    /// <returns><c>true</c> if the sample was actually emitted, <c>false</c>
    /// otherwise.</returns>
    inline bool emit(void) {
        return this->emit(timestamp::now());
    }

private:

    sensor_type& _sensor;
};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_MARKER_CONTROLLER_H) */
