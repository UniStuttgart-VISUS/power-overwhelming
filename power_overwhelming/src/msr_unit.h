// <copyright file="msrunit.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include <ios>


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// Specifies the vendor-specific offset of the RAPL units in the MSR device
    /// file.
    /// </summary>
    enum class msr_unit : std::streamoff {
        amd_power = 0xc0010299,
        intel_power = 0x606
    };

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
