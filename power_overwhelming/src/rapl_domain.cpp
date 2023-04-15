// <copyright file="rapl_domain.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/rapl_domain.h"

#include <stdexcept>


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
