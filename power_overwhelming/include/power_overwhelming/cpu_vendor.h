// <copyright file="cpu_vendor.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "power_overwhelming/power_overwhelming_api.h"


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
        /// Identifies a Centaur CPU.
        /// </summary>
        centaur,

        /// <summary>
        /// Identifies a Cyrix CPU.
        /// </summary>
        cyrix,

        /// <summary>
        /// Identifies a Hygon CPU.
        /// </summary>
        hygon,

        /// <summary>
        /// Identifies an Intel CPU.
        /// </summary>
        intel,

        /// <summary>
        /// Identifies a National Semiconductor CPU.
        /// </summary>
        national_semiconductor,

        /// <summary>
        /// Identifies a NexGen CPU.
        /// </summary>
        nexgen,

        /// <summary>
        /// Identifies a Rise Technology CPU.
        /// </summary>
        rise,

        /// <summary>
        /// Identifies an SiS CPU.
        /// </summary>
        sis,

        /// <summary>
        /// Identifies a Transmeta CPU.
        /// </summary>
        transmeta,

        /// <summary>
        /// Identifies a UMC CPU.
        /// </summary>
        umc
    };

    /// <summary>
    /// Determines the vendor of the CPUs on the system.
    /// </summary>
    /// <remarks>
    /// This function works using the CPUID intrinsics. For the unlikely case
    /// that the code is running on a machine with different kinds of CPUs, the
    /// caller should set the thread affinity to the desired CPU in order to
    /// make sure that the CPUID registers of the expected processors are read.
    /// The <see cref="set_thread_affinity" /> function can be used for this
    /// purpose.
    /// </remarks>
    /// <returns>An enumeration value identifying the CPU vendor or
    /// <see cref="cpu_vendor::unknown" /> if the CPU vendor could not be
    /// determined.</returns>
    extern POWER_OVERWHELMING_API cpu_vendor get_cpu_vendor(void) noexcept;

} /* namespace power_overwhelming */
} /* namespace visus */
