// <copyright file="string_functions.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "string_functions.h"

#include <cmath>
#include <stdexcept>



/*
 * visus::power_overwhelming::detail::equals
 */
bool visus::power_overwhelming::detail::equals(_In_opt_z_ const char *lhs,
        _In_opt_z_ const char *rhs, _In_ const bool ignore_case) {
    if (lhs == rhs) {
        // Trivial equality.
        return true;
    }

    if ((lhs == nullptr) || (rhs == nullptr)) {
        // Trivial inequality after test of pointer equality.
        return false;
    }

    if (ignore_case) {
        return (::stricmp(lhs, rhs) == 0);
    } else {
        return (::strcmp(lhs, rhs) == 0);
    }
}


/*
 * visus::power_overwhelming::detail::equals
 */
bool visus::power_overwhelming::detail::equals(_In_opt_z_ const wchar_t *lhs,
        _In_opt_z_ const wchar_t *rhs, _In_ const bool ignore_case) {
    if (lhs == rhs) {
        // Trivial equality.
        return true;
    }

    if ((lhs == nullptr) || (rhs == nullptr)) {
        // Trivial inequality after test of pointer equality.
        return false;
    }

    if (ignore_case) {
        return (::wcsicmp(lhs, rhs) == 0);
    } else {
        return (::wcscmp(lhs, rhs) == 0);
    }
}


/*
 * visus::power_overwhelming::detail::parse_float
 */
float visus::power_overwhelming::detail::parse_float(
        _In_opt_z_ const char *str) {
    return (str != nullptr) ? std::atof(str) : 0.0f;
}


/*
 * visus::power_overwhelming::detail::parse_int
 */
int visus::power_overwhelming::detail::parse_int(_In_opt_z_ const char *str) {
    return (str != nullptr) ? std::atoi(str) : 0;
}


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
