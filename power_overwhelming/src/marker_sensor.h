// <copyright file="marker_sensor.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_MARKER_SENSOR_H)
#define _PWROWG_MARKER_SENSOR_H
#pragma once

#include <cassert>
#include <list>
#include <memory>
#include <string>
#include <vector>

#include <nvml.h>

#include "visus/pwrowg/marker_configuration.h"
#include "visus/pwrowg/multi_sz.h"
#include "visus/pwrowg/sensor_array_callback.h"
#include "visus/pwrowg/sensor_description.h"
#include "visus/pwrowg/sensor_filters.h"

#include "sensor_description_builder.h"
#include "sensor_utilities.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// A sensor that allows for injecting user-defined markers into the output
/// stream.
/// </summary>
/// <remarks>
/// A marker is a user-defined string from a <see cref="marker_configuration" />,
/// which is referenced by its index.
/// </remarks>
class PWROWG_TEST_API marker_sensor final {

public:

    /// <summary>
    /// The type of sensor class configuration used by this sensor.
    /// </summary>
    typedef marker_configuration configuration_type;

    /// <summary>
    /// The type of a list of sensors of this type.
    /// </summary>
    typedef std::list<marker_sensor> list_type;

    /// <summary>
    /// Create descriptions for the single <see cref="marker_sensor" /> that
    /// is supported on a system.
    /// </summary>
    /// <remarks>
    /// <para>There can be only one such sensor in any programme. It will only
    /// be available if the configuration holds at least one marker name.</para>
    /// </remarks>
    /// <paramref name="dst"></param>
    /// <paramref name="cnt"></param>
    /// <param name="config">The global sensor configuration which might affect
    /// which sensors can be enumerated.</param>
    /// <returns>The number of available sensors, independently from the fact
    /// whether all of them have been returned.</returns>
    static std::size_t descriptions(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) sensor_description *dst,
        _In_ std::size_t cnt,
        _In_ const configuration_type& config);

    /// <summary>
    /// Generate sensors for all matching configurations within
    /// <paramref name="begin" /> and <paramref name="end" />.
    /// </summary>
    /// <remarks>
    /// <para>The method will go through all sensor descriptions provided and
    /// created sensors for each description that is recognised as one of its
    /// own. All of these matching descriptions are sorted to the begin of the
    /// range. All other descriptions, which could not be used to create a
    /// sensor of this type, are move to the end of the range and the returned
    /// iterator points to the first of those descriptions.</para>
    /// </remarks>
    /// <typeparam name="TInput">The type of the input iterator over the
    /// <see cref="sensor_description" />s.</typeparam>
    /// <param name="dst">The output list, which will receive the sensors and the
    /// sampler callbacks.</param>
    /// <param name="index">The index to be used for the first sensor created.
    /// </param>
    /// <param name="begin">The begin of the range of sensor descriptions.
    /// </param>
    /// <param name="end">The end of the range of sensor descriptions.</param>
    /// <param name="owner">The sensor array owning the sensors to be created.
    /// This pointer is required to gain access to the callback pointers and
    /// the context data. It can also be used to access the per-sensor class
    /// configuration contained  in <paramref name="config" /> later on.</param>
    /// <param name="config">The configuration for the sensor class.</param>
    /// <returns>The iterator to the first sensor description within
    /// <paramref name="begin" /> and <paramref name="end" /> that has not been
    /// used for creating a sensor.</returns>
    template<class TInput>
    static TInput from_descriptions(_In_ list_type& dst,
        _In_ std::size_t index,
        _In_ const TInput begin,
        _In_ const TInput end,
        _In_ const sensor_array_impl *owner,
        _In_ const configuration_type& config);

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="config>The configuration object holding the names of the
    /// markers.</param>
    inline marker_sensor(_In_ const configuration_type& config)
        : _markers(config.size()) { }

    marker_sensor(const marker_sensor& rhs) = delete;

    marker_sensor& operator =(const marker_sensor& rhs) = delete;

private:

    std::size_t _markers;
};

PWROWG_DETAIL_NAMESPACE_END

#include "marker_sensor.inl"

#endif /* defined(_PWROWG_MARKER_SENSOR_H) */
