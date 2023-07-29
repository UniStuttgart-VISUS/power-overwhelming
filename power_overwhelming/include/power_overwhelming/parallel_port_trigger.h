// <copyright file="parallel_port_trigger.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cinttypes>
#include <cstdlib>
#include <limits>

#if defined(_WIN32)
#include <Windows.h>
#endif /* defined(_WIN32) */

#include "power_overwhelming/parallel_port_pin.h"


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Enables application to send trigger signals at low latency via a
    /// parallel port attached to the computer.
    /// </summary>
    class POWER_OVERWHELMING_API parallel_port_trigger final {

    public:

        /// <summary>
        /// The type to express a time span in milliseconds.
        /// </summary>
        typedef std::uint32_t milliseconds_type;

        /// <summary>
        /// The type of a data value that can be written to the port.
        /// </summary>
        typedef std::uint8_t value_type;

        /// <summary>
        /// Translate <paramref name="message" /> to Morse code for use with the
        /// <see cref="morse" /> method.
        /// </summary>
        /// <remarks>
        /// <para>The method performs a transformation based on the ITU
        /// alphabet. Any character that is not translatable will be omitted in
        /// the output.</para>
        /// </remarks>
        /// <param name="dst">Receives the Morse code. This parameter can be
        /// <c>nullptr</c>, in which case the required buffer size will be
        /// measured. The output is guaranteed to be null-terminated if the
        /// buffer is able to hold at least one element.</param>
        /// <param name="cnt">The size of <paramref name="dst" />.</param>
        /// <param name="message">The message to be encoded. If this is larger
        /// than <paramref name="cnt" />, the output is incomplete.</param>
        /// <returns>The size of the buffer required, regardless of whether the
        /// full message could be written or not.</returns>
        /// <exception cref="std::invalid_argument">If
        /// <paramref name="message" /> is <c>nullptr</c>.</exception>
        static std::size_t to_morse(_Out_writes_opt_z_(cnt) wchar_t *dst,
            _In_ const std::size_t cnt, _In_z_ const wchar_t *message);

        /// <summary>
        /// Extracts the data pins from <paramref name="pins" />.
        /// </summary>
        /// <param name="pins">The parallel port pins from which the value
        /// pins should be extracted.</param>
        /// <returns>The data value represented by <paramref name="pins" />.
        /// </returns>
        static inline constexpr value_type to_value(
                _In_ const parallel_port_pin pins) noexcept {
            typedef std::underlying_type<parallel_port_pin>::type pin_type;
            auto retval = static_cast<pin_type>(pins);
            retval >>= 2;
            retval &= (std::numeric_limits<value_type>::max)();
            return static_cast<value_type>(retval);
        }

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <remarks>
        /// The instance initialised by this constructor is unusable unless a
        /// parallel port is opened afterwards.
        /// </remarks>
        parallel_port_trigger(void);

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="path">The path to the parallel port to open.</param>
        /// <exception cref="std::invalid_argument">If the
        /// <paramref name="path" /> is <c>nullptr</c>.</exception>
        /// <exception cref="std::system_error">If the specified port could not
        /// be opened.</exception>
        explicit parallel_port_trigger(_In_z_ const wchar_t *path);

        /// <summary>
        /// Initialises a new instance.
        /// </summary>
        /// <param name="path">The path to the parallel port to open.</param>
        /// <exception cref="std::invalid_argument">If the
        /// <paramref name="path" /> is <c>nullptr</c>.</exception>
        /// <exception cref="std::system_error">If the specified port could not
        /// be opened.</exception>
        explicit parallel_port_trigger(_In_z_ const char *path);

        /// <summary>
        /// Initialise by move.
        /// </summary>
        /// <param name="rhs">The object to be moved.</param>
        parallel_port_trigger(_Inout_ parallel_port_trigger&& rhs) noexcept;

        /// <summary>
        /// Finalises the instance.
        /// </summary>
        ~parallel_port_trigger(void);

        /// <summary>
        /// Closes the underlying parallel port if it is open.
        /// </summary>
        void close(void) noexcept;

        /// <summary>
        /// Write the given Morse code to the parallel port.
        /// </summary>
        /// <remarks>
        /// <para>The morse code is made of dots for short pulses and hyphens
        /// for long ones. Characters are separated by spaces (that represents a
        /// pause of three dits) and words are separated by a slash (that
        /// represents a puase of seven dits). For instance, to write
        /// &quot;Power Overwhelming&quot;, you would need to morse
        /// <c>.--. --- .-- . .-. / --- ...- . .-. .-- .... . .-.. -- .. -. --.
        /// </c>.</para>
        /// </remarks>
        /// <param name="code">The Morse code to write.</param>
        /// <param name="base_time">The base time of the code (a dit) in
        /// milliseconds. This parameter defaults to 200 ms.</param>
        /// <param name="on">The pins to turn on, which defaults to all.</param>
        /// <param name="off">The pins to turn off, which defaults to all data
        /// pins.</param>
        /// <exception cref="std::system_error">If the data could not be written
        /// to the port.</exception>
        void morse(_In_opt_z_ const wchar_t *code,
            _In_ const milliseconds_type base_time = 200,
            _In_ const parallel_port_pin on = parallel_port_pin::data,
            _In_ const parallel_port_pin off = parallel_port_pin::data) const;

        /// <summary>
        /// Opens the parallel port with the given path.
        /// </summary>
        /// <remarks>
        /// If the port was already open, it will be closed before opening a new
        /// one.
        /// </remarks>
        /// <param name="path">The path of the parallel port.</param>
        /// <exception cref="std::invalid_argument">If the
        /// <paramref name="path" /> is <c>nullptr</c>.</exception>
        /// <exception cref="std::system_error">If the specified port could not
        /// be opened.</exception>
        void open(_In_z_ const wchar_t *path);

        /// <summary>
        /// Opens the parallel port with the given path.
        /// </summary>
        /// <remarks>
        /// If the port was already open, it will be closed before opening a new
        /// one.
        /// </remarks>
        /// <param name="path">The path of the parallel port.</param>
        /// <exception cref="std::invalid_argument">If the
        /// <paramref name="path" /> is <c>nullptr</c>.</exception>
        /// <exception cref="std::system_error">If the specified port could not
        /// be opened.</exception>
        void open(_In_z_ const char *path);

        /// <summary>
        /// Activates the given data bits for <paramref name="period" />
        /// milliseconds and disables all data pins afterwards.
        /// </summary>
        /// <remarks>
        /// <para>The method will <i>not</i> disable the pins before pulsing
        /// them. The caller must ensure that all relevant pins are low before
        /// calling the method.</para>
        /// </remarks>
        /// <param name="data">The data bits to be enabled.</param>
        /// <param name="period">The period for which the data pins should be
        /// enabled, in milliseconds. This parameter defaults to 500
        /// milliseconds.</param>
        /// <exception cref="std::system_error">If the data could not be written
        /// to the port.</exception>
        void pulse(_In_ const value_type data,
            _In_ const milliseconds_type period = 500) const;

        /// <summary>
        /// Activates the given pins for <paramref name="period" />
        /// milliseconds and disables all pins afterwards.
        /// </summary>
        /// <remarks>
        /// <para>The method will <i>not</i> disable the pins before pulsing
        /// them. The caller must ensure that all relevant pins are low before
        /// calling the method.</para>
        /// <para>Note that this method currently only considers data pins.
        /// This behaviour might change in the future.</para>
        /// </remarks>
        /// <param name="pins">The pins to be pulsed. This defaults to all data
        /// pins.</param>
        /// <param name="period">The period for which the data pins should be
        /// enabled, in milliseconds. This parameter defaults to 500
        /// milliseconds.</param>
        /// <exception cref="std::system_error">If the data could not be written
        /// to the port.</exception>
        void pulse(_In_ const parallel_port_pin pins = parallel_port_pin::data,
            _In_ const milliseconds_type period = 500) const;

        /// <summary>
        /// Sets exactly the data bits active in <paramref name="data" />.
        /// </summary>
        /// <param name="data">The data bits to be enabled.</param>
        /// <exception cref="std::system_error">If the data could not be written
        /// to the port.</exception>
        void write(_In_ const value_type data) const;

        /// <summary>
        /// Sets exactly the data bits active in <paramref name="pins" />.
        /// </summary>
        /// <remarks>
        /// <para>Note that this method currently only considers data pins.
        /// This behaviour might change in the future.</para>
        /// </remarks>
        /// <param name="pins">The pins to be enabled.</param>
        /// <exception cref="std::system_error">If the data could not be written
        /// to the port.</exception>
        void write(_In_ const parallel_port_pin pins) const;

        /// <summary>
        /// Move assignment.
        /// </summary>
        /// <param name="rhs">The right-hand side operand.</param>
        /// <returns><c>*this</c>.</returns>
        parallel_port_trigger& operator =(
            _Inout_ parallel_port_trigger&& rhs) noexcept;

        /// <summary>
        /// Indicates whether the parallel port is open and can be triggered.
        /// </summary>
        /// <returns><c>true</c> if the parallel port is open,
        /// <c>false</c> otherwise.</returns>
        operator bool(void) const noexcept;

    private:

#if defined(_WIN32)
        typedef HANDLE handle_type;
#else /* defined(_WIN32) */
        typedef int handle_type;
#endif /* defined(_WIN32) */

#if defined(_WIN32)
        static constexpr const handle_type invalid_handle
            = INVALID_HANDLE_VALUE;
#else /* defined(_WIN32) */
        static constexpr const handle_type invalid_handle = -1;
#endif /* defined(_WIN32) */

        handle_type _handle;
    };

} /* namespace power_overwhelming */
} /* namespace visus */
