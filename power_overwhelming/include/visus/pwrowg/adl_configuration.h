// <copyright file="adl_configuration.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_ADL_CONFIGURATION_H)
#define _PWROWG_ADL_CONFIGURATION_H
#pragma once

#include "visus/pwrowg/sensor_configuration_base.h"


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// Provides additional configuration options for ADL-based sensors when
/// creating a <see cref="sensor_array" />.
/// </summary>
class POWER_OVERWHELMING_API adl_configuration final
        : public sensor_configuration_base {

public:

private:

};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_ADL_CONFIGURATION_H) */
