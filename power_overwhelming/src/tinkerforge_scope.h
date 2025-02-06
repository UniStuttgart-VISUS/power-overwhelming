// <copyright file="tinkerforge_scope.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_TINKERFORGE_SCOPE_H)
#define _PWROWG_TINKERFORGE_SCOPE_H
#pragma once

#include <algorithm>
#include <cinttypes>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <thread>

#include <ip_connection.h>

#include "tinkerforge_bricklet.h"


#if !defined(CALLBACK)
#define CALLBACK
#endif /* !defined(CALLBACK) */


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// RAII container for a Tinkerforge brick connection.
/// </summary>
/// <remarks>
/// <para>Tinkerforge scopes can be shared on a per-connection basis. The
/// scope keeps a reference count for each connection and terminates it once
/// the last instance was destructed.</para>
/// <para>Callers must make sure to adhere the thread-safety requirements
/// of the Tingerforge <see cref="IPConnection" /> they can obtain from a
/// scope. The creation of new scopes and their destruction is, however,
/// thread-safe.</para>
/// </remarks>
class PWROWG_TEST_API tinkerforge_scope final {

public:

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="host">The host on which the Brick daemon is running.
    /// </param>
    /// <param name="port">The port on which the Brick daemon is listening.
    /// </param>
    /// <exception cref="tinkerforge_exception">In case the connection could
    /// not be established.</exception>
    tinkerforge_scope(const std::string& host, const std::uint16_t port);

    /// <summary>
    /// Copy the the currently known <see cref="tinkerforge_bricklet" />s
    /// matching the given predicate in a thread-safe manner to the output
    /// iterator <paramref name="oit" />.
    /// </summary>
    /// <typeparam name="TIterator">An output iterator that can accept an
    /// arbitrary number of <see cref="tinkerfore_bricklet" />s being
    /// written.</typeparam>
    /// <typeparam name="TPredicate">An unary predicate accepting a
    /// <see cref="tinkerforge_bricklet" /> returning a <c>bool</c> that
    /// indicates whether the bricklet should be returned or not.
    /// </typeparam>
    /// <param name="oit"></param>
    /// <returns></returns>
    template<class TIterator, class TPredicate>
    std::size_t copy_bricklets(TIterator oit,
        const TPredicate& predicate) const;

    /// <summary>
    /// Copy the the currently known <see cref="tinkerforge_bricklet" />s
    /// in a thread-safe manner to the output iterator.
    /// </summary>
    /// <typeparam name="TIterator">An output iterator that can accept an
    /// arbitrary number of <see cref="tinkerfore_bricklet" />s being
    /// written.</typeparam>
    /// <param name="oit"></param>
    /// <returns></returns>
    template<class TIterator>
    inline std::size_t copy_bricklets(TIterator oit) const {
        return this->copy_bricklets(oit, [](const tinkerforge_bricklet&) {
            return true;
        });
    }

    /// <summary>
    /// Copy the the currently known <see cref="tinkerforge_bricklet" />s
    /// matching the given predicate in a thread-safe manner to the output
    /// iterator <paramref name="oit" />. If no bricklets are known, retry
    /// until the specified timeout was reached.
    /// </summary>
    /// <typeparam name="TIterator">An output iterator that can accept an
    /// arbitrary number of <see cref="tinkerfore_bricklet" />s being
    /// written.</typeparam>
    /// <typeparam name="TPredicate">An unary predicate accepting a
    /// <see cref="tinkerforge_bricklet" /> returning a <c>bool</c> that
    /// indicates whether the bricklet should be returned or not.
    /// </typeparam>
    /// <param name="oit">The output iterator receiving the bricklets.
    /// </param>
    /// <param name="predicate">The predicate the returned bricklets
    /// must match.</param>
    /// <param name="timeout">The maximum time in milliseconds to try to
    /// retrieve bricklets from the master brick in case no bricklets are
    /// cached.</param>
    /// <param name="expected">If greater than zero, the method will wait
    /// for this number of (matching) bricklets to be available before
    /// returning. Otherwise (if zero), the method will return if at least
    /// one bricklet was found. Note that the timeout will be honoured in
    /// both cases.</param>
    /// <returns>The number of bricklets written to <paramref name="oit" />.
    /// </returns>
    template<class TIterator, class TPredicate>
    std::size_t copy_bricklets(TIterator oit, const TPredicate& predicate,
        const std::chrono::milliseconds timeout,
        const std::size_t expected = 0) const;

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
    inline operator IPConnection *(void) noexcept {
        return std::addressof(this->_scope->connection);
    }

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
    inline operator const IPConnection *(void) const noexcept {
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
        std::map<std::string, tinkerforge_bricklet> bricklets;
        std::mutex lock_bricklets;
        IPConnection connection;
        data(const std::string& host, const std::uint16_t port);
        ~data(void);
    };

    /// <summary>
    /// Device enumeration callback for a connection.
    /// </summary>
    /// <param name="uid"></param>
    /// <param name="connected_uid"></param>
    /// <param name="position"></param>
    /// <param name="hardware_version"></param>
    /// <param name="firmware_version"></param>
    /// <param name="device_identifier"></param>
    /// <param name="enumeration_type"></param>
    /// <param name="user_data"></param>
    /// <returns></returns>
    static void CALLBACK on_enumerate(const char *uid,
        const char *connected_uid,
        char position,
        std::uint8_t hardware_version[3],
        std::uint8_t firmware_version[3],
        std::uint16_t device_identifier,
        std::uint8_t enumeration_type,
        void *user_data);

    /// <summary>
    /// Creates a unique endpoint representation that is used to index the
    /// <see cref="_scopes" /> map.
    /// </summary>
    /// <param name="host"></param>
    /// <param name="port"></param>
    /// <returns></returns>
    static std::string to_endpoint(const std::string& host,
        const std::uint16_t port);

    static std::map<std::string, std::weak_ptr<data>> _scopes;
    static std::mutex _lock_scopes;

    std::shared_ptr<data> _scope;
};

PWROWG_DETAIL_NAMESPACE_END

#include "tinkerforge_scope.inl"

#endif /* !defined(_PWROWG_TINKERFORGE_SCOPE_H) */
