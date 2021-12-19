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
        const std::string& host, const std::uint16_t port)
        : _endpoint(to_endpoint(host, port)) {
    //::ipcon_create(&this->_connection);

    //auto status = ::ipcon_connect(&this->_connection, host.c_str(), port);
    //if (status != E_OK) {
    //    // Must deallocate if throwing after ipcon_create!
    //    this->~tinkerforge_scope();
    //    throw tinkerforge_exception(status);
    //}
}


/*
 * visus::power_overwhelming::detail::tinkerforge_scope::tinkerforge_scope
 */
visus::power_overwhelming::detail::tinkerforge_scope::tinkerforge_scope(
        const tinkerforge_scope& rhs) {
    throw "TODO";
}


/*
 * visus::power_overwhelming::detail::tinkerforge_scope::~tinkerforge_scope
 */
visus::power_overwhelming::detail::tinkerforge_scope::~tinkerforge_scope(void) {
    std::lock_guard<decltype(_lock)> l(_lock);
    if (--_data[this->_endpoint]->count == 0) {
        _data.erase(this->_endpoint);
    }
}


/*
 * visus::power_overwhelming::detail::tinkerforge_scope::operator =
 */
visus::power_overwhelming::detail::tinkerforge_scope&
visus::power_overwhelming::detail::tinkerforge_scope::operator =(
        const tinkerforge_scope& rhs) {
    if (this != std::addressof(rhs)) {
        std::lock_guard<decltype(_lock)> l(_lock);
        _data[this->_endpoint]->count--;
        this->_endpoint = rhs._endpoint;
        _data[this->_endpoint]->count++;
    }

    return *this;
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
 * visus::power_overwhelming::detail::tinkerforge_scope::data::data
 */
visus::power_overwhelming::detail::tinkerforge_scope::data::data(
        const std::string& host, const std::uint16_t port) : count(1) {
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
 * visus::power_overwhelming::detail::tinkerforge_scope::_data
 */
std::map<std::string, std::unique_ptr<
    visus::power_overwhelming::detail::tinkerforge_scope::data>>
visus::power_overwhelming::detail::tinkerforge_scope::_data;


/*
 * visus::power_overwhelming::detail::tinkerforge_scope::_lock
 */
std::mutex visus::power_overwhelming::detail::tinkerforge_scope::_lock;

