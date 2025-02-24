// <copyright file="msr_configuration.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_MSR_CONFIGURATION_H)
#define _PWROWG_MSR_CONFIGURATION_H
#pragma once

#include "visus/pwrowg/sensor_configuration.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Provides additional configuration options for sensors based on model-specific
/// (RAPL) registers when creating a <see cref="sensor_array" />.
/// </summary>
class POWER_OVERWHELMING_API msr_configuration final
        : public sensor_configuration {

public:

    /// <summary>
    /// A unique identifer for the <see cref="msr_configuration" /> type.
    /// </summary>
    static const guid id;

private:

};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_MSR_CONFIGURATION_H) */
