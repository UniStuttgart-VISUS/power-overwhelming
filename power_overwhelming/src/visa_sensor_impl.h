// <copyright file="visa_sensor_impl.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "power_overwhelming/visa_instrument.h"

#include "visa_exception.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// Stores the data of a generic VISA-based sensor.
    /// </summary>
    struct visa_sensor_impl {

        /// <summary>
        /// Represents the type of native VISA status codes.
        /// </summary>
        typedef visa_exception::value_type status_type;

        /// <summary>
        /// The VISA instrument.
        /// </summary>
        visa_instrument instrument;

        /// <summary>
        /// The user-facing name of the sensor.
        /// </summary>
        std::wstring sensor_name;

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        visa_sensor_impl(_In_z_ const char *path,
            _In_ const std::int32_t timeout);

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        visa_sensor_impl(_In_z_ const wchar_t *path,
            _In_ const std::int32_t timeout);

    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */

