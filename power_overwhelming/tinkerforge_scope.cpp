// <copyright file="tinkerforge_scope.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "tinkerforge_scope.h"

#include "tinkerforge_exception.h"


/*
 * visus::power_overwhelming::detail::tinkerforge_scope::tinkerforge_scope
 */
visus::power_overwhelming::detail::tinkerforge_scope::tinkerforge_scope(
        const std::string& host, const std::uint16_t port) {
    ::ipcon_create(&this->_connection);

    auto status = ::ipcon_connect(&this->_connection, host.c_str(), port);
    if (status != E_OK) {
        // Must deallocate if throwing after ipcon_create!
        this->~tinkerforge_scope();
        throw tinkerforge_exception(status);
    }
}


/*
 * visus::power_overwhelming::detail::tinkerforge_scope::~tinkerforge_scope
 */
visus::power_overwhelming::detail::tinkerforge_scope::~tinkerforge_scope(void) {
    ::ipcon_destroy(&this->_connection);
}
