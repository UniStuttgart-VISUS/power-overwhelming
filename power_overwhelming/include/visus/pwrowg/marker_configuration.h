// <copyright file="marker_configuration.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 - 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_MARKER_CONFIGURATION_H)
#define _PWROWG_MARKER_CONFIGURATION_H
#pragma once

#include <string>

#include "visus/pwrowg/marker_controller.h"
#include "visus/pwrowg/sensor_configuration.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Allows for configuring a sensor that emits user-defined integral markers in
/// to the stream of samples.
/// </summary>
class POWER_OVERWHELMING_API marker_configuration final
        : public sensor_configuration {

public:

    /// <summary>
    /// The marker controller allows for injecting markers into the stream of
    /// samples while the sensor is running.
    /// </summary>
    typedef marker_controller controller_type;

    /// <summary>
    /// A unique identifier for the <see cref="marker_configuration" /> type.
    /// </summary>
    static const guid id;

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    inline marker_configuration(void) { }

    /// <summary>
    /// Finalises the instance.
    /// </summary>
    virtual ~marker_configuration(void) noexcept = default;
};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_MARKER_CONFIGURATION_H) */
