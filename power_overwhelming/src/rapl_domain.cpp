// <copyright file="rapl_domain.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/rapl_domain.h"

#include <stdexcept>

#include "power_overwhelming/for_each_rapl_domain.h"


/*
 * visus::power_overwhelming::for_each_rapl_domain
 */
std::size_t visus::power_overwhelming::for_each_rapl_domain(
        _In_ bool (*func)(const rapl_domain, void *),
        _In_opt_ void *context) {
    if (func == nullptr) {
        throw std::invalid_argument("A valid function pointer must be provided "
            "to enumerate the rapl_domains.");
    }

    return for_each_rapl_domain([func, context](const rapl_domain d) {
        return func(d, context);
    });
}


/*
 * visus::power_overwhelming::parse_rapl_domain
 */
visus::power_overwhelming::rapl_domain
visus::power_overwhelming::parse_rapl_domain(_In_z_ const wchar_t *str) {
    if (str == nullptr) {
        throw std::invalid_argument("Only a valid string can be parsed into a "
            "rapl_domain.");
    }

    const std::wstring s(str);
#define _FROM_STRING_CASE(v) else if (to_string(rapl_domain::v) == s) \
    return rapl_domain::v

    if (false);
    _FROM_STRING_CASE(package);
    _FROM_STRING_CASE(pp0);
    _FROM_STRING_CASE(pp1);
    _FROM_STRING_CASE(dram);
    else throw std::invalid_argument("The given string represents no "
        "valid rapl_domain");

#undef _FROM_STRING_CASE
}


/*
 * visus::power_overwhelming::to_string
 */
_Ret_z_ const wchar_t *visus::power_overwhelming::to_string(
        _In_ const rapl_domain domain) {
#define _GCC_IS_SHIT(v) L##v
#define _TO_STRING_CASE(v) case rapl_domain::v: return _GCC_IS_SHIT(#v)

    switch (domain) {
        _TO_STRING_CASE(package);
        _TO_STRING_CASE(pp0);
        _TO_STRING_CASE(pp1);
        _TO_STRING_CASE(dram);

        default:
            throw std::invalid_argument("The specified RAPL domain is "
                "unknown. Make sure to add all new sources in to_string.");
    }

#undef _GCC_IS_SHIT
#undef _TO_STRING_CASE
}
