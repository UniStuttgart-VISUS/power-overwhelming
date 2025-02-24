// <copyright file="usb_pd_sensor.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_USB_PD_SENSOR_H)
#define _PWROWG_USB_PD_SENSOR_H
#pragma once

#if defined(_WIN32)

#include <cassert>
#include <list>
#include <memory>
#include <string>
#include <vector>

#include "visus/pwrowg/sensor_array_callback.h"
#include "visus/pwrowg/sensor_description.h"
#include "visus/pwrowg/sensor_filters.h"
#include "visus/pwrowg/usb_pd_configuration.h"

#include "sensor_description_builder.h"
#include "sensor_utilities.h"
#include "usb_pd_library.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Implementation of a power sensor using the NVIDIA management library to
/// read the internal sensors of the GPU.
/// </summary>
class PWROWG_TEST_API usb_pd_sensor final {

public:

    /// <summary>
    /// The type of sensor class configuration used by this sensor.
    /// </summary>
    typedef usb_pd_configuration configuration_type;

    /// <summary>
    /// The type of a list of sensors of this type.
    /// </summary>
    typedef std::list<usb_pd_sensor> list_type;

    /// <summary>
    /// Create descriptions for all supported NVIDIA sensors in the system.
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
    /// Indicates that a sensor source is to be disabled.
    /// </summary>
    static constexpr std::size_t invalid_index
        = (std::numeric_limits<std::size_t>::max)();

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    usb_pd_sensor(_In_z_ const wchar_t *port,
        _In_ const std::size_t index_voltage,
        _In_ const std::size_t index_current);

    usb_pd_sensor(const usb_pd_sensor& rhs) = delete;

    /// <summary>
    /// Finalises the instance.
    /// </summary>
    ~usb_pd_sensor(void);

    /// <summary>
    /// Deliver a sample to the given <paramref name="callback" />.
    /// </summary>
    /// <param name="callback">The callback to be invoked.</param>
    /// <param name="sensors">The sensor descriptions passed to the
    /// <paramref name="callback" />.</param>
    /// <param name="context">An optional context pointer passed to the
    /// <paramref name="callback" />.</param>
    void sample(_In_ const sensor_array_callback callback,
        _In_ const sensor_description *sensors,
        _In_opt_ void *context = nullptr);

    usb_pd_sensor& operator =(const usb_pd_sensor& rhs) = delete;

private:

    std::size_t _index_voltage;
    std::size_t _index_current;
    usb_pd_tester _tester;
};

PWROWG_DETAIL_NAMESPACE_END

#include "usb_pd_sensor.inl"

#endif /* defined(_WIN32) */
#endif /* defined(_PWROWG_USB_PD_SENSOR_H) */
