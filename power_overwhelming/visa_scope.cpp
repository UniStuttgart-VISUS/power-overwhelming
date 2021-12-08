// <copyright file="visa_scope.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "visa_scope.h"

#include "visa_scope_impl.h"


/*
 * visus::power_overwhelming::detail::visa_scope::visa_scope
 */
visus::power_overwhelming::detail::visa_scope::visa_scope(
        const std::string& path) {
    std::lock_guard<decltype(_lock_scopes)> l(_lock_scopes);
    auto it = _scopes.find(path);
    if (it != _scopes.end()) {
        // Reuse existing scope for same connection.
        this->_impl = it->second.lock();
    }

    if (this->_impl == nullptr) {
        // If no existing scope was found or if the previous scope has been
        // deleted, create a new one.
        this->_impl = std::make_shared<visa_scope_impl>(path);
        _scopes[path] = this->_impl;
    }
}
