// <copyright file="cpu_vendor.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Specifies different vendors of CPUs.
    /// </summary>
    /// <remarks>
    /// <para>Some sensors, most notably the <see cref="msr_sensor" /> are
    /// dependent on vendor-specific implementations. This enumeration
    /// identifies the supported CPU vendors.</para>
    /// </remarks>
    enum class cpu_vendor {

        /// <summary>
        /// The CPU vendor is not known.
        /// </summary>
        unknown = 0,

        /// <summary>
        /// Identifies an AMD CPU.
        /// </summary>
        amd,

        /// <summary>
        /// Identifies an Intel CPU.
        /// </summary>
        intel,
    };

} /* namespace power_overwhelming */
} /* namespace visus */
