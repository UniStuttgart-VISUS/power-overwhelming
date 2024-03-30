// <copyright file="tinkerforge_sensor_definiton.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "power_overwhelming/tinkerforge_sensor_definition.h"


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Provides backwards compatibility for a typo in a previous version of
    /// the API.
    /// </summary>
    typedef tinkerforge_sensor_definition tinkerforge_sensor_definiton;

} /* namespace power_overwhelming */
} /* namespace visus */
