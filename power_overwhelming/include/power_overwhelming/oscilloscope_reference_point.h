// <copyright file="oscilloscope_reference_point.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cinttypes>


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Specifies possible locations of the reference point in an oscilloscope
    /// diagram on Rohde &amp; Schwarz devices.
    /// </summary>
    /// <remarks>
    /// <para>The reference point determines the centre of time scaling
    /// operations.</para>
    /// <para>The values of the enumeration fields are the magic numbers for
    /// Rohde &amp; Schwarz oscilloscopes multiplied by 100.</para>
    /// </remarks>
    enum class oscilloscope_reference_point : std::uint32_t {

        /// <summary>
        /// The scaling origin is located on the left side of the diagram.
        /// </summary>
        left = 833,

        /// <summary>
        /// The scaling origin is located in the centre of the diagram, which is
        /// the default.
        /// </summary>
        middle = 5000,

        /// <summary>
        /// The scaling origin is located on the right side of the diagram.
        /// </summary>
        right = 9167
    };

} /* namespace power_overwhelming */
} /* namespace visus */
