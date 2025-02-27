// <copyright file="powenetics_sensor.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_POWENETICS_SENSOR_H)
#define _PWROWG_POWENETICS_SENSOR_H
#pragma once
#if defined(POWER_OVERWHELMING_WITH_POWENETICS)

#include <cassert>
#include <functional>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <libpowenetics/powenetics.h>

#include "visus/pwrowg/powenetics_configuration.h"
#include "visus/pwrowg/sensor_array_callback.h"
#include "visus/pwrowg/sensor_description.h"
#include "visus/pwrowg/sensor_filters.h"

#include "sensor_description_builder.h"
#include "sensor_utilities.h"
#include "sensor_state.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Implementation of a power sensor using the NVIDIA management library to
/// read the internal sensors of the GPU.
/// </summary>
class PWROWG_TEST_API powenetics_sensor final {

public:

    /// <summary>
    /// The type of sensor class configuration used by this sensor.
    /// </summary>
    typedef powenetics_configuration configuration_type;

    /// <summary>
    /// The type used for a sensor index.
    /// </summary>
    typedef PWROWG_NAMESPACE::sample::source_type index_type;

    /// <summary>
    /// The type of a list of sensors of this type.
    /// </summary>
    typedef std::list<powenetics_sensor> list_type;

    /// <summary>
    /// The type of a function selecting a sample value.
    /// </summary>
    typedef std::function<float(const powenetics_sample&)> selector_type;

    /// <summary>
    /// Create descriptions for all supported Powenetics sensors in the system.
    /// </summary>
    /// <remarks>
    /// <para>It is safe to call this method on systems without Powenetics PMD.
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
    /// <param name="path"></param>
    /// <param name="indices"></param>
    powenetics_sensor(_In_z_ const wchar_t *path,
        _Inout_ std::map<index_type, selector_type>&& indices,
        _In_ const sensor_array_impl *owner);

    powenetics_sensor(const powenetics_sensor& rhs) = delete;

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    ~powenetics_sensor(void) noexcept;

    /// <summary>
    /// Starts or stops sampling the sensor.
    /// </summary>
    /// <param name="enable"><c>true</c> for enabling the sensor,
    /// <c>false</c> for disabling it.</param>
    void sample(_In_ const bool enable);

    powenetics_sensor& operator =(const powenetics_sensor& rhs) = delete;

private:

    /// <summary>
    /// Processes a single sample.
    /// </summary>
    static void on_sample(_In_ powenetics_handle source,
        _In_ const struct powenetics_sample_t *sample,
        _In_opt_ void *context);

    /// <summary>
    /// Specialises the <paramref name="builder" /> for the given sub-sensor.
    /// </summary>
    static sensor_description_builder& specialise(
        _In_ sensor_description_builder& builder,
        _In_ const std::wstring& port,
        _In_z_ const wchar_t *rail,
        _In_ const sensor_type type,
        _In_z_ const wchar_t *quantity,
        _In_ const reading_unit unit,
        _In_ const selector_type& selector);

    /// <summary>
    /// Specialises the <paramref name="builder" /> for all quantities of the
    /// given rail and adds it to <paramref name="dst" />.
    /// </summary>
    static std::size_t specialise(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) sensor_description *dst,
        _In_ const std::size_t cnt,
        _In_ std::size_t index,
        _In_ sensor_description_builder& builder,
        _In_ const std::wstring& port,
        _In_z_ const wchar_t *rail,
        _In_ const sensor_type type,
        _In_ const selector_type& voltage_selector,
        _In_ const selector_type& current_selector,
        _In_ const selector_type& power_selector);

    powenetics_handle _handle;
    std::map<index_type, selector_type> _indices;
    const sensor_array_impl *_owner;
    sensor_state _state;
};

PWROWG_DETAIL_NAMESPACE_END

#include "powenetics_sensor.inl"

#endif /* defined(POWER_OVERWHELMING_WITH_POWENETICS) */
#endif /* defined(_PWROWG_POWENETICS_SENSOR_H) */
