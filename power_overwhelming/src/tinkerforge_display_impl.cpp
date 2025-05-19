// <copyright file="tinkerforge_display_impl.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "tinkerforge_display_impl.h"

#include <stdexcept>


/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_display_impl::tinkerforge_display_impl
 */
PWROWG_DETAIL_NAMESPACE::tinkerforge_display_impl::tinkerforge_display_impl(
        const std::string& host, const std::uint16_t port, const char *uid)
        : scope(host, port) {
    if (uid == nullptr) {
        // Scope will be destructed automatically as it was initialised in the
        // initialiser list.
        throw std::invalid_argument("The UID of the voltage/current bricklet "
            "must not be null.");
    }

    ::lcd_128x64_create(&this->bricklet, uid, this->scope);
}


/*
 * PWROWG_DETAIL_NAMESPACE::tinkerforge_display_impl::~tinkerforge_display_impl
 */
PWROWG_DETAIL_NAMESPACE::tinkerforge_display_impl::~tinkerforge_display_impl(
        void) {
    ::lcd_128x64_destroy(&this->bricklet);
}
