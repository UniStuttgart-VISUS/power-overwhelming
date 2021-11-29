// <copyright file="tinkerforge_scope.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "tinkerforge_scope.h"

#include <algorithm>
#include <iterator>

#include "tinkerforge_exception.h"


/*
 * visus::power_overwhelming::detail::tinkerforge_scope::tinkerforge_scope
 */
visus::power_overwhelming::detail::tinkerforge_scope::tinkerforge_scope(
        const std::string& host, const std::uint16_t port) {
    auto endpoint = to_endpoint(host, port);

    std::lock_guard<decltype(_lock_scopes)> l(_lock_scopes);
    auto it = _scopes.find(endpoint);
    if (it != _scopes.end()) {
        // Reuse existing scope for same connection.
        this->_scope = it->second;
    } else {
        // Create a new scope for an unknown connection.
        this->_scope = std::make_shared<data>(host, port);
        _scopes[endpoint] = this->_scope;
    }
}


/*
 * visus::power_overwhelming::detail::tinkerforge_scope::data::data
 */
visus::power_overwhelming::detail::tinkerforge_scope::data::data(
        const std::string& host, const std::uint16_t port) {
    ::ipcon_create(&this->connection);

    auto status = ::ipcon_connect(&this->connection, host.c_str(), port);
    if (status != E_OK) {
        // Must deallocate if throwing after ipcon_create!
        this->~data();
        throw tinkerforge_exception(status);
    }
}


/*
 * visus::power_overwhelming::detail::tinkerforge_scope::data::~data
 */
visus::power_overwhelming::detail::tinkerforge_scope::data::~data(void) {
    ::ipcon_destroy(&this->connection);
}


/*
 * visus::power_overwhelming::detail::tinkerforge_scope::to_endpoint
 */
std::string visus::power_overwhelming::detail::tinkerforge_scope::to_endpoint(
        const std::string& host, const std::uint16_t port) {
    std::string retval;
    retval.reserve(host.size() + 1 + 6);

    std::transform(host.begin(), host.end(), std::back_inserter(retval),
        std::tolower);
    retval += ":";
    retval += std::to_string(port);

    return retval;
}


/*
 * visus::power_overwhelming::detail::tinkerforge_scope::_scopes
 */
std::map<std::string, std::shared_ptr<
    visus::power_overwhelming::detail::tinkerforge_scope::data>>
visus::power_overwhelming::detail::tinkerforge_scope::_scopes;


/*
 * visus::power_overwhelming::detail::tinkerforge_scope::_lock_scopes
 */
std::mutex
visus::power_overwhelming::detail::tinkerforge_scope::_lock_scopes;
