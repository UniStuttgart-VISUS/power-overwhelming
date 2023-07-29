// <copyright file="parallel_port_pin.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cinttypes>
#include <type_traits>

#include "power_overwhelming/power_overwhelming_api.h"


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Identifies a pin of a 25-pin parallel port connector.
    /// </summary>
    enum class parallel_port_pin {

        /// <summary>
        /// Represents no pin.
        /// </summary>
        none = 0,

        /// <summary>
        /// Represents the strobe pin.
        /// </summary>
        /// <remarks>
        /// <para>This pin is true on low logic.</para>
        /// <para>This pin cannot be set in user mode.</para>
        /// </remarks>
        strobe = (static_cast<std::uint32_t>(1) << 1),

        /// <summary>
        /// The first data pin.
        /// </summary>
        data0 = (static_cast<std::uint32_t>(1) << 2),

        /// <summary>
        /// The second data pin.
        /// </summary>
        data1 = (static_cast<std::uint32_t>(1) << 3),

        /// <summary>
        /// The third data pin.
        /// </summary>
        data2 = (static_cast<std::uint32_t>(1) << 4),

        /// <summary>
        /// The fourth data pin.
        /// </summary>
        data3 = (static_cast<std::uint32_t>(1) << 5),

        /// <summary>
        /// The fifth data pin.
        /// </summary>
        data4 = (static_cast<std::uint32_t>(1) << 6),

        /// <summary>
        /// The sixth data pin.
        /// </summary>
        data5 = (static_cast<std::uint32_t>(1) << 7),

        /// <summary>
        /// The seventh data pin.
        /// </summary>
        data6 = (static_cast<std::uint32_t>(1) << 8),

        /// <summary>
        /// The eighth data pin.
        /// </summary>
        data7 = (static_cast<std::uint32_t>(1) << 9),

        /// <summary>
        /// Represents all data pins.
        /// </summary>
        data = (static_cast<std::uint32_t>(0xFF) << 2),

        /// <summary>
        /// Represents the acknowledge pin.
        /// </summary>
        /// <remarks>
        /// <para>This pin cannot be set in user mode.</para>
        /// </remarks>
        acknowledge = (static_cast<std::uint32_t>(1) << 10),

        /// <summary>
        /// Represents the busy pin.
        /// </summary>
        /// <remarks>
        /// <para>This pin is true on low logic.</para>
        /// <para>This pin cannot be set in user mode.</para>
        /// </remarks>
        busy = (static_cast<std::uint32_t>(1) << 11),

        /// <summary>
        /// The pin indicating the end of the paper.
        /// </summary>
        /// <remarks>
        /// <para>This pin cannot be set in user mode.</para>
        /// </remarks>
        paper_out = (static_cast<std::uint32_t>(1) << 12),

        /// <summary>
        /// The select pin.
        /// </summary>
        /// <remarks>
        /// <para>This pin cannot be set in user mode.</para>
        /// </remarks>
        select = (static_cast<std::uint32_t>(1) << 13),

        /// <summary>
        /// The pin indicating a line feed.
        /// </summary>
        line_feed = (static_cast<std::uint32_t>(1) << 14),

        /// <summary>
        /// The error pin.
        /// </summary>
        /// <remarks>
        /// <para>This pin cannot be set in user mode.</para>
        /// </remarks>
        error = (static_cast<std::uint32_t>(1) << 15),

        /// <summary>
        /// The reset pin.
        /// </summary>
        /// <remarks>
        /// <para>This pin cannot be set in user mode.</para>
        /// </remarks>
        reset = (static_cast<std::uint32_t>(1) << 16),

        /// <summary>
        /// The printer selection pin.
        /// </summary>
        /// <remarks>
        /// <para>This pin cannot be set in user mode.</para>
        /// </remarks>
        select_printer = (static_cast<std::uint32_t>(1) << 17),

        /// <summary>
        /// The first ground pin.
        /// </summary>
        /// <remarks>
        /// <para>This pin cannot be set.</para>
        /// </remarks>
        ground0 = (static_cast<std::uint32_t>(1) << 18),

        /// <summary>
        /// The second ground pin.
        /// </summary>
        /// <remarks>
        /// <para>This pin cannot be set.</para>
        /// </remarks>
        ground1 = (static_cast<std::uint32_t>(1) << 19),

        /// <summary>
        /// The third ground pin.
        /// </summary>
        /// <remarks>
        /// <para>This pin cannot be set.</para>
        /// </remarks>
        ground2 = (static_cast<std::uint32_t>(1) << 20),

        /// <summary>
        /// The fourth ground pin.
        /// </summary>
        /// <remarks>
        /// <para>This pin cannot be set.</para>
        /// </remarks>
        ground3 = (static_cast<std::uint32_t>(1) << 21),

        /// <summary>
        /// The fifth ground pin.
        /// </summary>
        /// <remarks>
        /// <para>This pin cannot be set.</para>
        /// </remarks>
        ground4 = (static_cast<std::uint32_t>(1) << 22),

        /// <summary>
        /// The sixth ground pin.
        /// </summary>
        /// <remarks>
        /// <para>This pin cannot be set.</para>
        /// </remarks>
        ground5 = (static_cast<std::uint32_t>(1) << 23),

        /// <summary>
        /// The seventh ground pin.
        /// </summary>
        /// <remarks>
        /// <para>This pin cannot be set.</para>
        /// </remarks>
        ground6 = (static_cast<std::uint32_t>(1) << 24),

        /// <summary>
        /// The eighth ground pin.
        /// </summary>
        /// <remarks>
        /// <para>This pin cannot be set.</para>
        /// </remarks>
        ground7 = (static_cast<std::uint32_t>(1) << 25),

        /// <summary>
        /// Selects all valid pins.
        /// </summary>
        all = (static_cast<std::uint32_t>(1) << 26) - 1
    };

    /// <summary>
    /// Performs a bitwise combination of the given
    /// <see cref="parallel_port_pin" />s.
    /// </summary>
    /// <param name="lhs">The left-hand side operand.</param>
    /// <param name="rhs">The right-hand side operand.</param>
    /// <returns>The combined pins.</returns>
    inline parallel_port_pin operator |(
            _In_ const parallel_port_pin lhs,
            _In_ const parallel_port_pin rhs) {
        typedef std::decay<decltype(lhs)>::type enum_type;
        auto l = static_cast<std::underlying_type<enum_type>::type>(lhs);
        auto r = static_cast<std::underlying_type<enum_type>::type>(rhs);
        return static_cast<enum_type>(l | r);
    }

    /// <summary>
    /// Performs a bitwise intersection of the given
    /// <see cref="parallel_port_pin" />s.
    /// </summary>
    /// <param name="lhs">The left-hand side operand.</param>
    /// <param name="rhs">The right-hand side operand.</param>
    /// <returns>The intersected pins.</returns>
    inline parallel_port_pin operator &(
            _In_ const parallel_port_pin lhs,
            _In_ const parallel_port_pin rhs) {
        typedef std::decay<decltype(lhs)>::type enum_type;
        auto l = static_cast<std::underlying_type<enum_type>::type>(lhs);
        auto r = static_cast<std::underlying_type<enum_type>::type>(rhs);
        return static_cast<enum_type>(l & r);
    }

    /// <summary>
    /// Inverts the given <see cref="parallel_port_pin" />s.
    /// </summary>
    /// <param name="status">The pins to invert.</param>
    /// <returns>The inverted pins.</returns>
    inline parallel_port_pin operator ~(_In_ const parallel_port_pin status) {
        typedef std::decay<decltype(status)>::type enum_type;
        auto s = static_cast<std::underlying_type<enum_type>::type>(status);
        return static_cast<enum_type>(~s);
    }

} /* namespace power_overwhelming */
} /* namespace visus */
