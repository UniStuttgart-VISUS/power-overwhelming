// <copyright file="nvml_sensor.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_NVML_SENSOR_H)
#define _PWROWG_NVML_SENSOR_H
#pragma once

#include <string>
#include <vector>

#include <nvml.h>

#include "visus/pwrowg/nvml_configuration.h"
#include "visus/pwrowg/sensor_description.h"

#include "nvml_scope.h"
#include "sensor.h"


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
    static std::vector<sensor_description> descriptions(
        _In_ configuration_type& config);

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    nvml_sensor(void);

    nvml_sensor(const nvml_sensor& rhs) = delete;

    /// <summary>
    /// Finalise the instance.
    /// </summary>
    ~nvml_sensor(void);

    nvml_sensor& operator =(const nvml_sensor& rhs) = delete;

private:

    /// <summary>
    /// The NVML device the sensor is reading from.
    /// </summary>
    nvmlDevice_t _device;

    /// <summary>
    /// The NVML scope making sure the library is ready while the sensor
    /// exists.
    /// </summary>
    nvml_scope _scope;

};

PWROWG_DETAIL_NAMESPACE_END

#endif /* defined(_PWROWG_NVML_SENSOR_H) */

