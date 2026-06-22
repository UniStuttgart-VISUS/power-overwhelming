// <copyright file="tinkerforge_controller.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_TINKERFORGE_CONTROLLER_H)
#define _PWROWG_TINKERFORGE_CONTROLLER_H
#pragma once

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iterator>
#include <memory>

#include "visus/pwrowg/sensor_controller.h"


PWROWG_NAMESPACE_BEGIN

// Forward declarations.
namespace detail { class tinkerforge_sensor; }


/// <summary>
/// 
/// </summary>
class POWER_OVERWHELMING_API tinkerforge_controller final {

public:

    /// <summary>
    /// The type fo the sensor controlled by this controller.
    /// </summary>
    typedef detail::tinkerforge_sensor sensor_type;

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <typeparam name="TIterator">An iterator over a range of Tinkerforge sensors.
    /// </typeparam>
    /// <param name="begin">The begin of the Tinkerforge sensors, which must be a
    /// valid iterator.</param>
    /// <param name="end">The end of the Tinkerforge sensors.</param>
    template<class TIterator>
    tinkerforge_controller(_In_ TIterator begin, _In_ TIterator end)
            : _cnt(std::distance(begin, end)), _sensors(nullptr) {
        this->_sensors = new sensor_type *[this->_cnt];
        std::transform(begin, end, this->_sensors,
            [](sensor_type& s) { return std::addressof(s); });
    }

    /// <summary>
    /// Clone <paramref name="other" />.
    /// </summary>
    /// <param name="other">The object to be cloned.</param>
    inline tinkerforge_controller(_In_ const tinkerforge_controller& other)
            : _cnt(0), _sensors(nullptr) {
        *this = other;
    }

    /// <summary>
    /// Move <paramref name="other" />.
    /// </summary>
    /// <param name="other">The object to be cloned.</param>
    inline tinkerforge_controller(
            _Inout_ tinkerforge_controller&& other) noexcept
            : _cnt(other._cnt), _sensors(other._sensors) {
        other._cnt = 0;
        other._sensors = nullptr;
    }

    /// <summary>
    /// Finalises the instance.
    /// </summary>
    ~tinkerforge_controller(void) noexcept;

    /// <summary>
    /// Provided the Tinkerforge sensors have the custom firmware that allows
    /// for reading their internal clock, update the time drift estimation for
    /// these sensors.
    /// </summary>
    /// <remarks>
    /// <para>This method does nothing if there are no Tinkerforge sensors or if
    /// the Voltage/Current Bricklets do not have the custom firmware requested
    /// at build time.</para>
    /// <para>This method should not be called when measuring important data as
    /// it requires significant bandwidth on the Tinkerforge connection and
    /// might cause samples to be delayed or dropped. Callers should call this
    /// method between benchmarks to improve the estimate of the clock drift,
    /// ideally while the sensor array is not running.</para>
    /// <para>The calling thread will be blocked until the operation is
    /// complete.</para>
    /// </remarks>
    void resync_clock(void) const;

    /// <summary>
    /// Assignment operator.
    /// </summary>
    /// <param name="rhs">The right-hand-side operand.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    tinkerforge_controller& operator =(_In_ const tinkerforge_controller& rhs);

    /// <summary>
    /// Assignment operator.
    /// </summary>
    /// <param name="rhs">The right-hand-side operand.</param>
    /// <returns><c>*<see langword="this" /></c>.</returns>
    tinkerforge_controller& operator =(
        _Inout_ tinkerforge_controller&& rhs) noexcept;

private:

    std::size_t _cnt;
    sensor_type **_sensors;
};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_TINKERFORGE_CONTROLLER_H) */
