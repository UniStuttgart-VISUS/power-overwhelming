// <copyright file="tinkerforge_display_impl.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <string>

#include <bricklet_lcd_128x64.h>

#include "tinkerforge_scope.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// RAII scope for the <see cref="LCD128x64" />.
    /// </summary>
    struct tinkerforge_display_impl final {

        /// <summary>
        /// The device object.
        /// </summary>
        LCD128x64 bricklet;

        /// <summary>
        /// The scope keeping the connection alive while the sensor is still in
        /// use.
        /// </summary>
        tinkerforge_scope scope;

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="host"></param>
        /// <param name="port"></param>
        /// <param name="uid"></param>
        tinkerforge_display_impl(const std::string& host,
            const std::uint16_t port, const char *uid);

        /// <summary>
        /// Finalises the instance.
        /// </summary>
        ~tinkerforge_display_impl(void);
    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
