// <copyright file="string_functions.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "string_functions.h"

#include <stdexcept>


/*
 * visus::power_overwhelming::detail::safe_duplicate
 */
_Ret_maybenull_z_ wchar_t *visus::power_overwhelming::detail::safe_duplicate(
        _In_opt_z_ const wchar_t *src) {
    if (src != nullptr) {
        auto retval = ::wcsdup(src);
        if (retval == nullptr) {
            throw std::bad_alloc();
        }

        return retval;

    } else {
        return nullptr;
    }
}


/*
 * visus::power_overwhelming::detail::safe_duplicate
 */
_Ret_maybenull_z_ char *visus::power_overwhelming::detail::safe_duplicate(
        _In_opt_z_ const char *src) {
    if (src != nullptr) {
        auto retval = ::strdup(src);
        if (retval == nullptr) {
            throw std::bad_alloc();
        }

        return retval;

    } else {
        return nullptr;
    }
}
