// <copyright file="async_sampling.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "power_overwhelming/power_overwhelming_api.h"
#include "power_overwhelming/timestamp_resolution.h"


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Configures the behaviour of ansychronous sampling of a sensor.
    /// </summary>
    class POWER_OVERWHELMING_API async_sampling final {

    public:


        /// <summary>
        /// A callback for <see cref="measurement" />s that are received
        /// asynchronously.
        /// </summary>
       // typedef void (*measurement_callback)(const measurement &, _In_opt_ void *);


    private:


    };

} /* namespace power_overwhelming */
} /* namespace visus */
