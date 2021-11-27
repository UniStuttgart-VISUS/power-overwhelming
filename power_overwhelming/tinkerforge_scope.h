// <copyright file="tinkerforge_scope.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cinttypes>
#include <string>

#include <ip_connection.h>


namespace visus {
namespace power_overwhelming {
namespace detail{

    /// <summary>
    /// RAII container for a Tinkerforge brick connection.
    /// </summary>
    class tinkerforge_scope final {

    public:

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="host">The host on which the Brick daemon is running.
        /// This parameter defaults to &quot;localhost&quot;.</param>
        /// <param name="port">The port on which the Brick daemon is listening.
        /// This parameter defaots to 4223.</param>
        tinkerforge_scope(const std::string& host = "localhost",
            const std::uint16_t port = 4223);

        tinkerforge_scope(const tinkerforge_scope&) = delete;

        /// <summary>
        /// Finalises the instance.
        /// </summary>
        ~tinkerforge_scope(void);

        tinkerforge_scope& operator =(const tinkerforge_scope&) = delete;

        /// <summary>
        /// Converts the scope into the embedded <see cref="IPConnection" />.
        /// </summary>
        /// <remarks>
        /// Callers must not destroy the connection returned under any
        /// circumstance.
        /// </remarks>
        /// <returns>The IP connection, which is guaranteed to be valid and
        /// connected for any valid instance of the scope.</returns>
        inline operator IPConnection *(void) {
            return std::addressof(this->_connection);
        }

    private:

        IPConnection _connection;
    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
