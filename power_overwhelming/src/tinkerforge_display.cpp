// <copyright file="tinkerforge_display.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/tinkerforge_display.h"

#include <stdexcept>
#include <vector>

#include "tinkerforge_bricklet.h"
#include "tinkerforge_display_impl.h"
#include "tinkerforge_exception.h"


/*
 * visus::power_overwhelming::tinkerforge_display::for_all
 */
std::size_t visus::power_overwhelming::tinkerforge_display::for_all(
        _Out_writes_opt_(cnt_displays) tinkerforge_display *out_displays,
        _In_ const std::size_t cnt_displays,
        _In_opt_z_ const char *host,
        _In_ const std::uint16_t port,
        _In_ const std::size_t timeout) {
    std::vector<detail::tinkerforge_bricklet> bricklets;
    const std::string safe_host = (host != nullptr) ? host : default_host;
    detail::tinkerforge_scope scope(safe_host, port);

    auto retval = scope.copy_bricklets(std::back_inserter(bricklets),
        [](const detail::tinkerforge_bricklet& b) {
            return (b.device_type() == LCD_128X64_DEVICE_IDENTIFIER);
        }, std::chrono::milliseconds(timeout), cnt_displays);

    if (out_displays != nullptr) {
        for (std::size_t i = 0; (i < cnt_displays) && (i < retval); ++i) {
            out_displays[i] = tinkerforge_display(bricklets[i].uid().c_str(),
                safe_host.c_str(), port);
        }
    }

    return retval;
}


/*
 * visus::power_overwhelming::tinkerforge_display::tinkerforge_display
 */
visus::power_overwhelming::tinkerforge_display::tinkerforge_display(
        _In_z_ const char *uid,
        _In_opt_z_ const char *host,
        _In_ const std::uint16_t port)
        : _impl(nullptr) {
    this->_impl = new detail::tinkerforge_display_impl(
        (host != nullptr) ? host : default_host,
        port,
        uid);
}


/*
 * visus::power_overwhelming::tinkerforge_display::clear
 */
void visus::power_overwhelming::tinkerforge_display::clear(void) {
    if (!*this) {
        throw std::runtime_error("A disposed instance of tinkerforge_display "
            "cannot be cleared.");
    }

    auto status = ::lcd_128x64_clear_display(&this->_impl->bricklet);
    if (status < 0) {
        throw tinkerforge_exception(status);
    }
}


/*
 * visus::power_overwhelming::tinkerforge_display::print
 */
void visus::power_overwhelming::tinkerforge_display::print(
        _In_z_ const char *text,
        _In_ const std::uint8_t x,
        _In_ const std::uint8_t y,
        _In_ const std::uint8_t font,
        _In_ const bool colour) {
    if (!*this) {
        throw std::runtime_error("A disposed instance of tinkerforge_display "
            "cannot be used to print text.");
    }
    if (text == nullptr) {
        throw std::invalid_argument("The text cannot be null.");
    }

    auto status = ::lcd_128x64_draw_text(&this->_impl->bricklet, x, y, font,
        colour, text);
    if (status < 0) {
        throw tinkerforge_exception(status);
    }
}


/*
 * visus::power_overwhelming::tinkerforge_display::operator =
 */
visus::power_overwhelming::tinkerforge_display& 
visus::power_overwhelming::tinkerforge_display::operator =(
        _In_ tinkerforge_display&& rhs) noexcept {
    if (this != std::addressof(rhs)) {
        this->_impl = rhs._impl;
        rhs._impl = nullptr;
    }

    return *this;
}


/*
 * visus::power_overwhelming::tinkerforge_display::operator bool
 */
visus::power_overwhelming::tinkerforge_display::operator bool(
        void) const noexcept {
    return (this->_impl != nullptr);
}
