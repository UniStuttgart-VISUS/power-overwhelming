// <copyright file="for_each_rapl_domain.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <cstdlib>
#include <functional>
#include <stdexcept>

#include "power_overwhelming/rapl_domain.h"


namespace visus {
namespace power_overwhelming {
namespace detail {

    /// <summary>
    /// Recursion stop for <see cref="for_each_rapl_domain" />.
    /// </summary>
    template<class TFunc> std::size_t for_each_rapl_domain(_In_ TFunc&& func,
            _In_ rapl_domain_list_type<>) {
        return 0;
    }

    /// <summary>
    /// Executes <paramref name="func" /> for <typeparamref name="Domain" />
    /// and recuses for <typeparamref name="Domains" />.
    /// </summary>
    template<class TFunc, rapl_domain Domain, rapl_domain... Domains>
    inline std::size_t for_each_rapl_domain(_In_ TFunc&& func,
            _In_ rapl_domain_list_type<Domain, Domains...>) {
        if (func(Domain)) {
            return 1 + for_each_rapl_domain(func,
                rapl_domain_list_type<Domains...> { });
        } else {
            return 1;
        }
    }

} /* namespace detail */

    /// <summary>
    /// Executes <paramref name="func" /> for each RAPL domain in
    /// <see cref="rapl_domain_list" />.
    /// </summary>
    /// <typeparam name="TFunc">The function or functor to be executed for each
    /// member of <see cref="rapl_domain_list" />. This fuctor must accept a
    /// <see cref="rapl_domain" /> as its single parameter and return a
    /// <c>bool</c> indicating whether the enumeration should continue.
    /// </typeparam>
    /// <param name="func">The function to execute for each RAPL domain.</param>
    /// <returns>The number of invocation of <paramref name="func" />.</returns>
    template<class TFunc>
    inline std::size_t for_each_rapl_domain(_In_ TFunc&& func) {
        return detail::for_each_rapl_domain(func, rapl_domain_list { });
    }

} /* namespace power_overwhelming */
} /* namespace visus */
