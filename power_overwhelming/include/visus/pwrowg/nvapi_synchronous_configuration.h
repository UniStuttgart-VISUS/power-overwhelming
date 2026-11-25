// <copyright file="nvapi_synchronous_configuration.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_NVAPI_SYNCHRONOUS_CONFIGURATION_H)
#define _PWROWG_NVAPI_SYNCHRONOUS_CONFIGURATION_H
#pragma once

#include "visus/pwrowg/nvapi_throttling_reason.h"
#include "visus/pwrowg/sensor_configuration.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Provides additional configuration options for synchronous NVAPI-based
/// sensors when creating a <see cref="sensor_array" />. These sensors are
/// not power sensors, but provide throttling information for NVIDIA GPUs.
/// </summary>
class POWER_OVERWHELMING_API nvapi_synchronous_configuration final
        : public sensor_configuration {

public:

    /// <summary>
    /// A unique identifier for the
    /// <see cref="nvapi_synchronous_configuration" /> type.
    /// </summary>
    static const guid id;

};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_NVAPI_SYNCHRONOUS_CONFIGURATION_H) */
