// <copyright file="sensor_configuration.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_SENSOR_CONFIGURATION_H)
#define _PWROWG_SENSOR_CONFIGURATION_H
#pragma once

#include "visus/pwrowg/guid.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// The base class for all sensor-specific configuration containers.
/// </summary>
/// <remarks>
/// Note that this class is not useful in itself, but we need it to have a
/// standardised interface for enumerating configurations.
/// </remarks>>
class POWER_OVERWHELMING_API sensor_configuration {

protected:

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    sensor_configuration(void) = default;
};


PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_SENSOR_CONFIGURATION_H) */
