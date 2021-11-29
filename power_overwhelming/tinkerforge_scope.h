// <copyright file="tinkerforge_scope.h" company="Visualisierungsinstitut der Universit�t Stuttgart">
// Copyright � 2021 Visualisierungsinstitut der Universit�t Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph M�ller</author>

#pragma once

#include <cinttypes>
#include <map>
#include <memory>
#include <mutex>
#include <string>

#include <ip_connection.h>


namespace visus {
namespace power_overwhelming {
namespace detail{

    /// <summary>
    /// RAII container for a Tinkerforge brick connection.
    /// </summary>
    /// <remarks>
    /// Tinkerforge scopes can be shared on a per-connection basis. The scope
    /// keeps a reference count for each connection and terminates it once the
    /// last instance was destructed.
    /// </remarks>
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
            return std::addressof(this->_scope->connection);
        }

    private:

        /// <summary>
        /// RAII wrapper for the actual connections.
        /// </summary>
        /// <remarks>
        /// The scopes referring to a specific connection hold a shared pointer
        /// to one of these.
        /// </remarks>
        struct data {
            IPConnection connection;
            explicit data(const std::string& host, const std::uint16_t port);
            ~data(void);
        };

        static std::string to_endpoint(const std::string& host,
            const std::uint16_t port);

        static std::map<std::string, std::shared_ptr<data>> _scopes;
        static std::mutex _lock_scopes;

        std::shared_ptr<data> _scope;
    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
