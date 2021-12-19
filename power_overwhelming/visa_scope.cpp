// <copyright file="visa_scope.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "visa_scope.h"

#include <cassert>
#include <stdexcept>

#include "visa_library.h"


/*
 * visus::power_overwhelming::detail::visa_scope::visa_scope
 */
visus::power_overwhelming::detail::visa_scope::visa_scope(
        const char *path, const std::uint32_t timeout) {
    if (path == nullptr) {
        throw std::invalid_argument("The path to a VISA device must not be "
            "null.");
    }

    std::lock_guard<decltype(_lock_scopes)> l(_lock_scopes);
    auto it = _scopes.find(path);
    if (it != _scopes.end()) {
        // Reuse existing scope for same connection.
        this->_impl = it->second.lock();
    }

    if (this->_impl == nullptr) {
        // If no existing scope was found or if the previous scope has been
        // deleted, create a new one.
        this->_impl = std::make_shared<visa_scope_impl>(path, timeout);
        _scopes[path] = this->_impl;
    }
}


/*
 * visus::power_overwhelming::detail::visa_scope::_scopes
 */
std::map<std::string, std::weak_ptr<visus::power_overwhelming::detail::visa_scope_impl>>
visus::power_overwhelming::detail::visa_scope::_scopes;


/*
 * visus::power_overwhelming::detail::visa_scope::_lock_scopes
 */
std::mutex visus::power_overwhelming::detail::visa_scope::_lock_scopes;
