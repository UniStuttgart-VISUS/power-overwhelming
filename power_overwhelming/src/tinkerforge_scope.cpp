// <copyright file="tinkerforge_scope.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 -2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "tinkerforge_scope.h"

#include <algorithm>
#include <cctype>
#include <iterator>

#if defined(_WIN32)
#include <WinSock2.h>
#endif /* defined(_WIN32) */

#include "tinkerforge_exception.h"


/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_scope::tinkerforge_scope
 */
PWROWG_DETAIL_NAMESPACE::tinkerforge_scope::tinkerforge_scope(
    const std::string &host, const std::uint16_t port) {
    auto endpoint = to_endpoint(host, port);

    std::lock_guard<decltype(_lock_scopes)> l(_lock_scopes);
    auto it = _scopes.find(endpoint);
    if (it != _scopes.end()) {
        // Reuse existing scope for same connection.
        this->_scope = it->second.lock();
    }

    if (this->_scope == nullptr) {
        // If no existing scope was found or if the previous scope has been
        // deleted, create a new one.
        this->_scope = std::make_shared<data>(host, port);
        _scopes[endpoint] = this->_scope;
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_scope::data::data
 */
PWROWG_DETAIL_NAMESPACE::tinkerforge_scope::data::data(
    const std::string &host, const std::uint16_t port) {
    ::ipcon_create(&this->connection);
    //::ipcon_set_auto_reconnect(&this->connection, true);

    // Connect to master brick.
    {
        auto status = ::ipcon_connect(&this->connection, host.c_str(), port);
        if (status < 0) {
            // Must deallocate if throwing after ipcon_create!
            ::ipcon_destroy(&this->connection);
            throw tinkerforge_exception(status);
        }
    }

    // Register the callback.
    ::ipcon_register_callback(&this->connection, IPCON_CALLBACK_ENUMERATE,
        reinterpret_cast<void(*)(void)>(on_enumerate), this);

    // Perform first enumeration of devices.
    {
        auto status = ::ipcon_enumerate(&this->connection);
        if (status < 0) {
            // Same as above: manually cleanup resources.
            ::ipcon_destroy(&this->connection);
            throw tinkerforge_exception(status);
        }
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_scope::data::~data
 */
PWROWG_DETAIL_NAMESPACE::tinkerforge_scope::data::~data(void) {
    ::ipcon_destroy(&this->connection);
}


/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_scope::on_enumerate
 */
void CALLBACK PWROWG_DETAIL_NAMESPACE::tinkerforge_scope::on_enumerate(
    const char *uid, const char *connected_uid, char position,
    std::uint8_t hardware_version[3], std::uint8_t firmware_version[3],
    std::uint16_t device_identifier, std::uint8_t enumeration_type,
    void *user_data) {
    auto data = static_cast<tinkerforge_scope::data *>(user_data);
    const auto is_add = (enumeration_type == IPCON_ENUMERATION_TYPE_AVAILABLE)
        || (enumeration_type == IPCON_ENUMERATION_TYPE_CONNECTED);

    std::lock_guard<decltype(data->lock_bricklets)> l(data->lock_bricklets);
    auto it = data->bricklets.find(uid);

    if (is_add && (it == data->bricklets.end())) {
        // Insert if added and unknown.
        data->bricklets[uid] = tinkerforge_bricklet(uid, connected_uid,
            position, hardware_version, firmware_version, device_identifier);
    }

    if (!is_add && (it != data->bricklets.end())) {
        // Erase if removed and known.
        data->bricklets.erase(it);
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_scope::to_endpoint
 */
std::string PWROWG_DETAIL_NAMESPACE::tinkerforge_scope::to_endpoint(
        const std::string& host, const std::uint16_t port) {
    std::string retval;
    retval.reserve(host.size() + 1 + 6);

    std::transform(host.begin(), host.end(), std::back_inserter(retval),
        [](const char c) { return std::tolower(c); });
    retval += ":";
    retval += std::to_string(port);

    return retval;
}


/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_scope::_scopes
 */
std::map<std::string, std::weak_ptr<
    PWROWG_DETAIL_NAMESPACE::tinkerforge_scope::data>>
    PWROWG_DETAIL_NAMESPACE::tinkerforge_scope::_scopes;


/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_scope::_lock_scopes
 */
std::mutex
PWROWG_DETAIL_NAMESPACE::tinkerforge_scope::_lock_scopes;
