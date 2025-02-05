// <copyright file="nvml_sensor.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_NVML_SENSOR_H)
#define _PWROWG_NVML_SENSOR_H
#pragma once

#include <memory>
#include <string>
#include <vector>

#include <nvml.h>

#include "visus/pwrowg/nvml_configuration.h"
#include "visus/pwrowg/sensor_array_callback.h"
#include "visus/pwrowg/sensor_description.h"

#include "nvidia_management_library.h"
#include "nvml_exception.h"
#include "nvml_scope.h"
#include "sensor.h"
#include "sensor_description_builder.h"
#include "string_functions.h"
#include "sensor_utilities.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Implementation of a power sensor using the NVIDIA management library to
/// read the internal sensors of the GPU.
/// </summary>
class PWROWG_TEST_API nvml_sensor final : public sensor {

public:

    /// <summary>
    /// The type of sensor class configuration used by this sensor.
    /// </summary>
    typedef nvml_configuration configuration_type;

    /// <summary>
    /// Create descriptions for all supported NVIDIA sensors in the system.
    /// </summary>
    /// <remarks>
    /// <para>It is safe to call this method on systems without NVIDIA GPU.
    /// No descriptions are returned in this case.</para>
    /// </remarks>
    /// <param name="config">The global sensor configuration which might affect
    /// which sensors can be enumerated.</param>
    /// <returns>A list of sensor descriptors that can be used to instantiate a
    /// specific sensor.</returns>
    template<class TOutput> static void descriptions(_In_ TOutput oit,
        _In_ const configuration_type& config);

    /// <summary>
    /// Create a new instance for the device with the specified PCI bus ID.
    /// </summary>
    /// <param name="bus_id"></param>
    /// <returns></returns>
    /// <exception cref="nvml_exception">If the specified device was not
    /// found, is not unique or another error occurred in NVML.</exception>
    static std::shared_ptr<nvml_sensor> from_bus_id(_In_z_ const char *bus_id,
        _In_ const std::size_t index);

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
    /// <typeparam name="TOutput">An output iterator for shared pointers of
    /// sensors that is able to receive at least a sensor for every element
    /// <paramref name="begin" /> and <paramref name="end" />.</typeparam>
    /// <typeparam name="TInput">The type of the input iterator over the
    /// <see cref="sensor_description" />s.</typeparam>
    /// <param name="oit">The output iterator receiving the sensors.</param>
    /// <param name="index">The index to be used for the first sensor created.
    /// </param>
    /// <param name="begin">The begin of the range of sensor descriptions.
    /// </param>
    /// <param name="end">The end of the range of sensor descriptions.</param>
    /// <returns>The iterator to the first sensor description within
    /// <paramref name="begin" /> and <paramref name="end" /> that has not been
    /// used for creating a sensor.</returns>
    template<class TOutput, class TInput>
    static TInput from_descriptions(_In_ TOutput oit, _In_ std::size_t index,
        _In_ const TInput begin, _In_ const TInput end);

    /// <summary>
    /// Create a new instance for the device with the specified unique ID.
    /// </summary>
    /// <param name="guid"></param>
    /// <returns></returns>
    /// <exception cref="nvml_exception">If the specified device was not
    /// found, is not unique or another error occurred in NVML.</exception>
    static std::shared_ptr<nvml_sensor> from_guid(_In_z_ const char *guid,
        _In_ const std::size_t index);

    /// <summary>
    /// Create a new instance from a device index.
    /// </summary>
    /// <remarks>
    /// <para>Device indices start at zero and go up to the number of
    /// supported NVIDIA cards minus one.</para>
    /// <para>Please note that the indices may not match the indices of
    /// CUDA devices and/or DXGI adapters.</para>
    /// </remarks>
    /// <param name="idx"></param>
    /// <returns></returns>
    /// <exception cref="nvml_exception">If the specified device was not
    /// found, is not unique or another error occurred in NVML.</exception>
    static std::shared_ptr<nvml_sensor> from_index(_In_ const unsigned int idx,
        _In_ const std::size_t index);

    /// <summary>
    /// Create a new instance for a specific device serial number printed on
    /// the board.
    /// </summary>
    /// <param name="serial"></param>
    /// <returns></returns>
    /// <exception cref="nvml_exception">If the specified device was not
    /// found, is not unique or another error occurred in NVML.</exception>
    static std::shared_ptr<nvml_sensor> from_serial(_In_z_ const char *serial,
        _In_ const std::size_t index);

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    inline nvml_sensor(_In_ const nvmlDevice_t device,
            _In_ const std::size_t index)
        : _device(device), _index(index) { }

    nvml_sensor(const nvml_sensor& rhs) = delete;

    /// <summary>
    /// Deliver a sample to the given <paramref name="callback" />.
    /// </summary>
    /// <param name="callback">The callback to be invoked.</param>
    /// <param name="context">An optional context pointer passed to the
    /// <paramref name="callback" />.</param>
    void sample(_In_ const sensor_array_callback callback,
        _In_opt_ void *context = nullptr);

    nvml_sensor& operator =(const nvml_sensor& rhs) = delete;

private:

    /// <summary>
    /// The NVML device the sensor is reading from.
    /// </summary>
    nvmlDevice_t _device;

    /// <summary>
    /// The index of the sensor in the array.
    /// </summary>
    std::size_t _index;

    /// <summary>
    /// The NVML scope making sure the library is ready while the sensor
    /// exists.
    /// </summary>
    nvml_scope _scope;
};

PWROWG_DETAIL_NAMESPACE_END

#include "nvml_sensor.inl"

#endif /* defined(_PWROWG_NVML_SENSOR_H) */
