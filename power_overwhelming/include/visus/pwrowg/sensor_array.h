// <copyright file="sensor_array.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_SENSOR_ARRAY_H)
#define _PWROWG_SENSOR_ARRAY_H
#pragma once

#include <algorithm>
#include <chrono>
#include <vector>

#include "visus/pwrowg/sensor_array_callback.h"
#include "visus/pwrowg/sensor_array_configuration.h"
#include "visus/pwrowg/sensor_description.h"


/* Forward declarations*/
PWROWG_DETAIL_NAMESPACE_BEGIN
struct sensor_array_impl;
PWROWG_DETAIL_NAMESPACE_END


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// The sensor array is the main structure of Power Overwhelming v2 as is
/// manages a set of sensors that are sampled simultaneously. Sensors can only
/// be created as membery of a sensor array.
/// </summary>
class POWER_OVERWHELMING_API sensor_array final {

public:

    /// <summary>
    /// Create sensor descriptors for all sensors we can find on the system.
    /// </summary>
    /// <remarks>
    /// <para>This method should not be called while a sensor array is active
    /// as a sensor implementation might require exclusive access.</para>
    /// <para>Callers should not make any assumptions about the order of the
    /// sensors returned. Most notably, the order might change when an actual
    /// array is being created from a set of descriptors.</para>
    /// </remarks>
    /// <param name="dst">An array receiving the sensors. If this is
    /// <c>nullptr</c>, nothing is returned, but the required buffer size is
    /// still computed.</param>
    /// <param name="cnt">The number of sensors that can be stored in
    /// <paramref name="cnt" />.</param>
    /// <param name="config">The array configuration detailing the behaviour of
    /// the sensors that are retrieved.</param>
    /// <returns>The number of sensors available, regardless of how
    /// many have been returned to <paramref name="dst" />.</returns>
    static std::size_t all_descriptions(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) sensor_description *dst,
        _In_ std::size_t cnt,
        _In_ const sensor_array_configuration& config);

    /// <summary>
    /// Create a sensor array for all <see cref="sensor_description" /> matching
    /// the given predicate.
    /// </summary>
    /// <typeparam name="TPredicate">An unary predicate for
    /// <see cref="sensor_description" />.</typeparam>
    /// <param name="config">The array configuration detailing the behaviour of
    /// the sensors that are retrieved.</param>
    /// <param name="predicate">The predicate selecting the sensors that are
    /// included in the array.</param>
    /// <returns>A new sensor array.</returns>
    template<class TPredicate> static sensor_array for_matches(
        _In_ const sensor_array_configuration& config,
        _In_ const TPredicate predicate);

    /// <summary>
    /// Initialises a new, but invalid instance.
    /// </summary>
    inline sensor_array(void) noexcept : _impl(nullptr) { }

    /// <summary>
    /// Initialises a new instance
    /// </summary>
    /// <param name="descs">The descriptors of the sensors that should be
    /// activated in the array. Callers must not assume that the order of
    /// the sensors within the array is the same as in this parameter. The
    /// array may choose to reorder sensors to improve performance.</param>
    /// <param name="cnt">The number of descriptors in <paramref name="cnt" />.
    /// </param>
    explicit sensor_array(
        _In_reads_(cnt) const sensor_description *descs,
        _In_ const std::size_t cnt);

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="rhs">The object to be moved.</param>
    inline sensor_array(_Inout_ sensor_array&& rhs) noexcept
            : _impl(rhs._impl) {
        rhs._impl = nullptr;
    }

    /// <summary>
    /// Finalises the instance.
    /// </summary>
    ~sensor_array(void) noexcept;

    /// <summary>
    /// Answer the descriptors for all sensors that are active in the array.
    /// </summary>
    /// <remarks>
    /// <para>It is safe to call this method on a disposed array, in which case
    /// the number of sensors will always be zero.</para>
    /// <para>The descriptors will always be returned in the order in which the
    /// sensor samples are created, i.e. this method can be used to obtain the
    /// description of a sample based on its index.</para>
    /// <para>The order of descriptors will never change after the array has
    /// been created. It is safe to keep a lookup table derived from the returned
    /// values externally.</para>
    /// </remarks>
    /// <param name="dst">An array receiving the sensors. If this is
    /// <c>nullptr</c>, nothing is returned, but the required buffer size is
    /// still computed.</param>
    /// <param name="cnt">The number of sensors that can be stored in
    /// <paramref name="cnt" />.</param>
    /// <returns>The number of sensors available, regardless of how
    /// many have been returned to <paramref name="dst" />.</returns>
    std::size_t descriptions(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) sensor_description *dst,
        _In_ std::size_t cnt);

    /// <summary>
    /// Starts sampling all sensors in the array.
    /// </summary>
    /// <param name="callback">The callback that is to receive the
    /// <see cref="sample" />s from all sensors.</param>
    /// <param name="context">An optional pointer that is passed to the
    /// <see cref="callback" /> every time.</param>
    /// <exception cref="std::runtime_error">If the object has been invalidated
    /// by a move operation.</exception>
    /// <exception cref="std::logic_error">If the sensor array was already
    /// running.</exception>
    void start(_In_ const sensor_array_callback callback,
        _In_opt_ void *context = nullptr);

    /// <summary>
    /// Stops all sensors and blocks until all asynchronous sampling has ended.
    /// </summary>
    void stop(void);

    /// <summary>
    /// Answer the number of sensors in the array.
    /// </summary>
    /// <remarks>
    /// <para>It is safe to call this method on a disposed array, in which case
    /// the number of sensors will always be zero.</para>
    /// </remarks>
    /// <returns>The number of sensors in the array.</returns>
    std::size_t size(void) const noexcept;

    /// <summary>
    /// Move assignment.
    /// </summary>
    /// <param name="rhs">The object to be moved.</param>
    /// <returns><c>*this</c>.</returns>
    sensor_array& operator =(_Inout_ sensor_array&& rhs) noexcept;

    /// <summary>
    /// Provides access to the descriptor of the <paramref name="idx" />th
    /// sensor.
    /// </summary>
    /// <param name="idx">The zero-based index of the sensor to retrieve the
    /// description for, which must be within [0, <see cref="size" />[.</param>
    /// <returns>The descriptor of the specified sensor.</returns>
    /// <exception cref="std::runtime_error">If the object has been invalidated
    /// by a move operation.</exception>
    /// <exception cref="std::range_error">If <paramref name="idx" /> is
    /// invalid.</exception>
    const sensor_description& operator [](_In_ int idx) const;

    /// <summary>
    /// Provides access to the descriptor of the <paramref name="idx" />th
    /// sensor.
    /// </summary>
    /// <remarks>
    /// This accessor can be used to change the label of a sensor. However, be
    /// aware that the API is not thread-safe, so multiple threads manipulating
    /// the descriptor will corrupt the data. The sensor array itself will,
    /// however, not change the descriptors after it has been created.
    /// </remarks>
    /// <param name="idx">The zero-based index of the sensor to retrieve the
    /// description for, which must be within [0, <see cref="size" />[.</param>
    /// <returns>The descriptor of the specified sensor.</returns>
    /// <exception cref="std::runtime_error">If the object has been invalidated
    /// by a move operation.</exception>
    /// <exception cref="std::range_error">If <paramref name="idx" /> is
    /// invalid.</exception>
    sensor_description& operator [](_In_ int idx);

    /// <summary>
    /// Answer whether the sensor array is valid or has been disposed, e.g. by
    /// a move operation.
    /// </summary>
    /// <returns><c>true</c> if the array is valid, <c>false</c> otherwise.
    inline operator bool(void) const noexcept {
        return (this->_impl != nullptr);
    }

private:

    PWROWG_DETAIL_NAMESPACE::sensor_array_impl *check_not_disposed(void) const;

    PWROWG_DETAIL_NAMESPACE::sensor_array_impl *_impl;
};

PWROWG_NAMESPACE_END

#include "visus/pwrowg/sensor_array.inl"

#endif /* !defined(_PWROWG_SENSOR_ARRAY_H) */
