// <copyright file="tinkerforge_scope.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

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
    /// As the connection to a brick uses a network connection, scopes share
    /// this connection. In order to enable this, this scope is copyable and
    /// retains a reference count of how many users of the resource there
    /// are. The connection is only destroyed once the last scope was destroyed.
    /// <see cref="tinkerforge_scope" /> are thread-safe.
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
        /// Clone <paramref name="rhs" />
        /// </summary>
        /// <param name="rhs">The object to be cloned</param>
        tinkerforge_scope(const tinkerforge_scope& rhs);

        /// <summary>
        /// Finalises the instance.
        /// </summary>
        ~tinkerforge_scope(void);

        /// <summary>
        /// Assignment operator.
        /// </summary>
        /// <param name="rhs">The right-hand side operand.</param>
        /// <returns><c>*this</c></returns>
        tinkerforge_scope& operator =(const tinkerforge_scope& rhs);

        /// <summary>
        /// Converts the scope into the embedded <see cref="IPConnection" />.
        /// </summary>
        /// <remarks>
        /// Callers must not destroy the connection returned under any
        /// circumstance. Callers must also not keep local copies of the
        /// value returned.
        /// </remarks>
        /// <returns>The IP connection, which is guaranteed to be valid and
        /// connected for any valid instance of the scope.</returns>
        inline operator IPConnection *(void) {
            std::lock_guard<decltype(_lock)> l(_lock);
            return std::addressof(_data[this->_endpoint]->connection);
        }

    private:

        /// <summary>
        /// Groups the per-connection data.
        /// </summary>
        struct data {

            /// <summary>
            /// The connection handle for the master brick.
            /// </summary>
            IPConnection connection;

            /// <summary>
            /// The reference count for this connection.
            /// </summary>
            std::size_t count;

            /// <summary>
            /// Initialises a new instance.
            /// </summary>
            data(const std::string& host, const std::uint16_t port);

            /// <summary>
            /// Finalises the instance.
            /// </summary>
            ~data(void);
        };

        static std::string to_endpoint(const std::string& host,
            const std::uint16_t port);

        static std::map<std::string, std::unique_ptr<data>> _data;
        static std::mutex _lock;

        std::string _endpoint;
    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
