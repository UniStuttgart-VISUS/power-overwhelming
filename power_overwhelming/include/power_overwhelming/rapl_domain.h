// <copyright file="rapl_domain.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include "power_overwhelming/power_overwhelming_api.h"


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Possible RAPL domains that can be queried using an
    /// <see cref="emi_sensor" /> or an <see cref="msr_sensor" />.
    /// </summary>
    enum class rapl_domain {

        /// <summary>
        /// The whole CPU package.
        /// </summary>
        package,

        /// <summary>
        /// PP0 typically comprises the CPU cores.
        /// </summary>
        pp0,

        /// <summary>
        /// PP1 typically comrpises the on-board GPU.
        /// </summary>
        pp1,

        /// <summary>
        /// The DRAM package.
        /// </summary>
        dram
    };

    /// <summary>
    /// Convert the given RAPL domain to a human-readable string representation.
    /// </summary>
    /// <param name="domain">The RAPL domain to be converter.</param>
    /// <returns>The name of the domain.</returns>
    extern POWER_OVERWHELMING_API _Ret_z_ const wchar_t *to_string(
        _In_ const rapl_domain domain);

} /* namespace power_overwhelming */
} /* namespace visus */
