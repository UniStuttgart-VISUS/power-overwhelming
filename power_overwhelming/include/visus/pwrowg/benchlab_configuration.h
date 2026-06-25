// <copyright file="benchlab_configuration.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 - 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_BENCHLAB_CONFIGURATION_H)
#define _PWROWG_BENCHLAB_CONFIGURATION_H
#pragma once

#include "visus/pwrowg/sensor_configuration.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Provides additional configuration options for sensors using the BenchLab
/// power measurement device (PMD).
/// </summary>
class POWER_OVERWHELMING_API benchlab_configuration final
        : public sensor_configuration {

public:

    /// <summary>
    /// A unique identifier for the <see cref="benchlab_configuration" /> type.
    /// </summary>
    static const guid id;

private:

};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_BENCHLAB_CONFIGURATION_H) */
