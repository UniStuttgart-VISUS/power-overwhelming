// <copyright file="sensor_configuration_base.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_SENSOR_CONFIGURATION_BASE_H)
#define _PWROWG_SENSOR_CONFIGURATION_BASE_H
#pragma once

#include "visus/pwrowg/api.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// The base class for all sensor-specific configuration containers. Note that
/// this class is not useful in itself, but we need it to have a standardised
/// interface for enumerating configurations.
/// </summary>
class POWER_OVERWHELMING_API sensor_configuration_base {

protected:

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    sensor_configuration_base(void) = default;
};


PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_SENSOR_CONFIGURATION_BASE_H) */
