// <copyright file="tinkerforge_display.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "tinkerforge_sensor.h"


namespace visus {
namespace power_overwhelming {

    /* Forward declarations. */
    namespace detail { struct tinkerforge_display_impl; }

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
        /// The default host on which brickd is assumed to run.
        /// </summary>
        static constexpr const char *default_host
            = tinkerforge_sensor::default_host;

        /// <summary>
        /// The default port on which brickd is assumed to listen on.
        /// </summary>
        static constexpr const std::uint16_t default_port
            = tinkerforge_sensor::default_port;

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
        static std::size_t for_all(tinkerforge_display *out_displays,
            const std::size_t cnt_displays, const char *host = default_host,
            const std::uint16_t port = default_port,
            const std::size_t timeout = 1000);

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
        /// This parameter defaults to &quot;localhost&quot;.</param>
        /// <param name="port">The port on which the Brick daemon is listening.
        /// This parameter defaults to 4223.</param>
        /// <exception cref="std::invalid_argument">If <paramref name="uid" />
        /// is <c>nullptr</c>.</exceptions>
        /// <exception cref="std::bad_alloc">If the required resources could not
        /// be allocated.</exceptions>
        /// <exception cref="tinkerforge_exception">If the connection to the
        /// master brick could not be established.</exception>
        tinkerforge_display(const char *uid, const char *host = default_host,
            const std::uint16_t port = default_port);

        /// <summary>
        /// Move <paramref name="rhs" /> into a new instance.
        /// </summary>
        /// <param name="rhs">The object to be moved.</param>
        inline tinkerforge_display(tinkerforge_display&& rhs) noexcept
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
        void print(const char *text, const std::uint8_t x = 0,
            const std::uint8_t y = 0, const std::uint8_t font = 0,
            const bool colour = true);

        /// <summary>
        /// Move assignment.
        /// </summary>
        /// <param name="rhs">The right-hand side operand</param>
        /// <returns><c>*this</c></returns>
        tinkerforge_display& operator =(tinkerforge_display&& rhs) noexcept;

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

} /* namespace power_overwhelming */
} /* namespace visus */
