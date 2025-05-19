// <copyright file="tinkerforge_display.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#if !defined(_PWROWG_TINKERFORGE_DISPLAY_H)
#define _PWROWG_TINKERFORGE_DISPLAY_H
#pragma once

#include "visus/pwrowg/tinkerforge_configuration.h"


/* Forward declarations. */
PWROWG_DETAIL_NAMESPACE_BEGIN
struct tinkerforge_display_impl;
PWROWG_DETAIL_NAMESPACE_END


PWROWG_NAMESPACE_BEGIN

/// <summary>
/// A resource wrapper around the Tinkerforge 126x64 LCD display.
/// </summary>
/// <remarks>
/// This class is just for building flashy applications. The LCD bricklet
/// is not required for doing power measurements.
/// </remarks>
class POWER_OVERWHELMING_API tinkerforge_display final {

public:

    /// <summary>
    /// Creates wrappers for all LCD bricklets attached to the specified
    /// master brick.
    /// </summary>
    /// <param name="out_displays"></param>
    /// <param name="cnt_displays"></param>
    /// <param name="host"></param>
    /// <param name="port"></param>
    /// <param name="timeout"></param>
    /// <returns></returns>
    static std::size_t for_all(
        _Out_writes_opt_(cnt_displays) tinkerforge_display *out_displays,
        _In_ const std::size_t cnt_displays,
        _In_opt_z_ const char *host = "localhost",
        _In_ const std::uint16_t port = 4223,
        _In_ const std::size_t timeout = 1000);

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    inline tinkerforge_display(void) : _impl(nullptr) { }

    /// <summary>
    /// Initialises a new instance.
    /// </summary>
    /// <param name="uid">The unique identifier of the LCD bricklet
    /// addressed by the object.</param>
    /// <param name="host">The host on which the Brick daemon is running.
    /// Usually, you would connect to &quot;localhost&quot;.</param>
    /// <param name="port">The port on which the Brick daemon is listening.
    /// Usually, you would connect to 4223.</param>
    /// <exception cref="std::invalid_argument">If <paramref name="uid" />
    /// is <c>nullptr</c>.</exceptions>
    /// <exception cref="std::bad_alloc">If the required resources could not
    /// be allocated.</exceptions>
    /// <exception cref="tinkerforge_exception">If the connection to the
    /// master brick could not be established.</exception>
    tinkerforge_display(_In_z_ const char *uid,
        _In_opt_z_ const char *host,
        _In_ const std::uint16_t port);

    /// <summary>
    /// Move <paramref name="rhs" /> into a new instance.
    /// </summary>
    /// <param name="rhs">The object to be moved.</param>
    inline tinkerforge_display(_In_ tinkerforge_display&& rhs) noexcept
            : _impl(rhs._impl) {
        rhs._impl = nullptr;
    }

    /// <summary>
    /// Clears the display.
    /// </summary>
    void clear(void);

    /// <summary>
    /// The text to be printed.
    /// </summary>
    /// <param name="text"></param>
    /// <param name="x">The x-coordinate of the cell to start at.</param>
    /// <param name="y">The y-coordinate of the cell to start at.</param>
    /// <param name="font">The font to use (mainly the size), which is
    /// one of the constants like <c>LCD_128X64_FONT_6X8</c>.</param>
    /// <param name="colour">If <c>true</c> (the default), print the text
    /// in black. Otherwise, print in white.</param>
    void print(_In_z_ const char *text,
        _In_ const std::uint8_t x = 0,
        _In_ const std::uint8_t y = 0,
        _In_ const std::uint8_t font = 0,
        _In_ const bool colour = true);

    /// <summary>
    /// Move assignment.
    /// </summary>
    /// <param name="rhs">The right-hand side operand</param>
    /// <returns><c>*this</c></returns>
    tinkerforge_display& operator =(
        _In_ tinkerforge_display&& rhs) noexcept;

    /// <summary>
    /// Determines whether the LCD display is valid.
    /// </summary>
    /// <remarks>
    /// A display is considered valid until it has been disposed by a move
    /// operation.
    /// </remarks>
    /// <returns><c>true</c> if the display is valid, <c>false</c>
    /// otherwise.</returns>
    operator bool(void) const noexcept;

private:

    detail::tinkerforge_display_impl *_impl;
};

PWROWG_NAMESPACE_END

#endif /* !defined(_PWROWG_TINKERFORGE_DISPLAY_H) */
