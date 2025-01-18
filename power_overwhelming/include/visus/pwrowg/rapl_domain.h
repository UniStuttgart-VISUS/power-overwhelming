// <copyright file="rapl_domain.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cstddef>

#include "visus/pwrowg/api.h"


namespace visus {
namespace power_overwhelming {

    /// <summary>
    /// Possible RAPL domains that can be queried using an
    /// <see cref="emi_sensor" /> or an <see cref="msr_sensor" />.
    /// </summary>
    /// <remarks>
    /// <para>Implementation note: If new elements are added to this enumeration,
    /// they must be added to the <see cref="rapl_domain_list" /> towards the
    /// end of this file, too. This list enables automated enumeration of all
    /// RAPL domains.</para>
    /// <para>Implementation note: If new elements are added to this enumeration,
    /// they must also be added in the implementation of <see cref="to_string" />
    /// and <see cref="parse_rapl_domain" /> towards the end of this file.</para>
    /// </remarks>
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
    /// Type of a list to enumerate all RAPL domains at compile time, which is
    /// declared at the end of this file.
    /// </summary>
    template<rapl_domain...> struct rapl_domain_list_type final { };


    /// <summary>
    /// A list of all supported RAPL domains, which can be used to generate code
    /// per-domain at compile time.
    /// </summary>
    using rapl_domain_list = rapl_domain_list_type<
        rapl_domain::package,
        rapl_domain::pp0,
        rapl_domain::pp1,
        rapl_domain::dram>;


    /// <summary>
    /// Execute <paramref name="func" /> for each member of the
    /// <see cref="rapl_domain_list" />.
    /// </summary>
    /// <param name="func">A function that receives the
    /// <see cref="rapl_domain" /> and the user-provided <see cref="context" />
    /// and returns whether the enumeration should be continued.</param>
    /// <param name="context">A user-defined context passed to every call of
    /// <paramref name="func" />.</param>
    /// <returns>The number of invocations of <paramref name="func" />.
    /// </returns>
    /// <exception cref="std::invalid_argument">If <paramref name="func" /> is
    /// <c>nullptr</c>.</exception>
    extern POWER_OVERWHELMING_API std::size_t for_each_rapl_domain(
        _In_ bool (*func)(const rapl_domain, void *),
        _In_opt_ void *context = nullptr);

    /// <summary>
    /// Parses a string into a value of the <see cref="rapl_domain" />
    /// enumeration.
    /// </summary>
    /// <param name="str">The string to be parsed.</param>
    /// <returns>The value represented by the string.</returns>
    /// <exception cref="std::invalid_argument">If <paramref name="str" /> is
    /// either <c>nullptr</c> or if it does not represent a valid RAPL domain.
    /// </exception>
    extern POWER_OVERWHELMING_API rapl_domain parse_rapl_domain(
        _In_z_ const wchar_t *str);

    /// <summary>
    /// Convert the given RAPL domain to a human-readable string representation.
    /// </summary>
    /// <param name="domain">The RAPL domain to be converter.</param>
    /// <returns>The name of the domain.</returns>
    extern POWER_OVERWHELMING_API _Ret_z_ const wchar_t *to_string(
        _In_ const rapl_domain domain);

} /* namespace power_overwhelming */
} /* namespace visus */
