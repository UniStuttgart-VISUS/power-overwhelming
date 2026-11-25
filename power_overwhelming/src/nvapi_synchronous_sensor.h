// <copyright file="nvapi_synchronous_sensor.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_NVAPI_SYNCHRONOUS_SENSOR_H)
#define _PWROWG_NVAPI_SYNCHRONOUS_SENSOR_H
#pragma once
#if defined(POWER_OVERWHELMING_WITH_NVAPI)

#include <cassert>
#include <list>
#include <memory>
#include <string>
#include <vector>

#include "visus/pwrowg/nvapi_synchronous_configuration.h"
#include "visus/pwrowg/sensor_description.h"
#include "visus/pwrowg/sensor_filters.h"

#include "nvapi_library.h"
#include "nvapi_scope.h"
#include "sensor_description_builder.h"
#include "sensor_utilities.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Implementation of a throttling sensor based on NVAPI. This cannot be
/// integrated into <see cref="nvapi_sensor" /> because the parts of NVAPI used
/// to determine the throttling state are not asynchronous.
/// </summary>
class PWROWG_TEST_API nvapi_synchronous_sensor final {

public:

    /// <summary>
    /// The type of sensor class configuration used by this sensor.
    /// </summary>
    typedef nvapi_synchronous_configuration configuration_type;

    /// <summary>
    /// The type of a list of sensors of this type.
    /// </summary>
    typedef std::list<nvapi_synchronous_sensor> list_type;

    /// <summary>
    /// Create descriptions for all supported syncrhonous NVIDIA sensors in
    /// the system.
    /// </summary>
    /// <remarks>
    /// <para>It is safe to call this method on systems without NVIDIA GPU.
    /// No descriptions are returned in this case.</para>
    /// </remarks>
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
    /// <param name="handle>The NVAPI physical GPU handle for the device to
    /// retrieve the data from.</param>
    /// <param name="index>The index of the descriptor of this sensor.</param>
    inline nvapi_synchronous_sensor(_In_ const NvPhysicalGpuHandle handle,
            _In_ const std::size_t index)
        : _handle(handle), _index(index) { }

    nvapi_synchronous_sensor(const nvapi_synchronous_sensor& rhs) = delete;

    /// <summary>
    /// Deliver a sample to the given <paramref name="callback" />.
    /// </summary>
    /// <param name="callback">The callback to be invoked.</param>
    /// <param name="sensors">The sensor descriptions passed to the
    /// <paramref name="callback" />.</param>
    /// <param name="cnt">The number of sensor descriptions in
    /// <paramref name="sensors" />, which is passed to the callback.</param>
    /// <param name="context">An optional context pointer passed to the
    /// <paramref name="callback" />.</param>
    void sample(_In_ const sensor_array_callback callback,
        _In_reads_(cnt) const sensor_description *sensors,
        _In_ const std::size_t cnt,
        _In_opt_ void *context = nullptr);

    nvapi_synchronous_sensor& operator =(const nvapi_synchronous_sensor& rhs) = delete;

private:

    const NvPhysicalGpuHandle _handle;
    const std::size_t _index;
    nvapi_scope _scope;
};

PWROWG_DETAIL_NAMESPACE_END

#include "nvapi_synchronous_sensor.inl"

#endif /* defined(POWER_OVERWHELMING_WITH_NVAPI) */
#endif /* defined(_PWROWG_NVAPI_SYNCHRONOUS_SENSOR_H) */
