// <copyright file="string_functions.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "string_functions.h"

#include <cmath>
#include <cwchar>
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
#if defined(_WIN32)
        return (::stricmp(lhs, rhs) == 0);
#else /* defined(_WIN32) */
        return (::strcasecmp(lhs, rhs) == 0);
#endif /* defined(_WIN32) */
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
#if defined(_WIN32)
        return (::wcsicmp(lhs, rhs) == 0);
#else /* defined(_WIN32) */
        return (::wcscasecmp(lhs, rhs) == 0);
#endif /* defined(_WIN32) */
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
 * visus::power_overwhelming::detail::parse_uint
 */
unsigned int visus::power_overwhelming::detail::parse_uint(
        _In_opt_z_ const char *str) {
    return (str != nullptr) ? static_cast<unsigned int>(std::atoll(str)) : 0;
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


/*
 * visus::power_overwhelming::detail::starts_with
 */
bool visus::power_overwhelming::detail::starts_with(_In_opt_z_ const char *str,
        _In_opt_z_ const char *start, _In_ const bool ignore_case) {
    if ((start == nullptr) || (*start == 0)) {
        // Trivial accept of empty prefix.
        return true;
    }

    if (str == nullptr) {
        // Trivial reject of empty haystack.
        return false;
    }

    auto len_str = ::strlen(str);
    auto len_start = ::strlen(start);

    if (len_str < len_start) {
        return false;
    }

    if (ignore_case) {
#if defined(_WIN32)
        return (::strnicmp(str, start, len_start) == 0);
#else /* defined(_WIN32) */
        return (::strncasecmp(str, start, len_start) == 0);
#endif /* defined(_WIN32) */
    } else {
        return (::strncmp(str, start, len_start) == 0);
    }
}


/*
 * visus::power_overwhelming::detail::starts_with
 */
bool visus::power_overwhelming::detail::starts_with(_In_opt_z_ const wchar_t *str,
        _In_opt_z_ const wchar_t *start, _In_ const bool ignore_case) {
    if ((start == nullptr) || (*start == 0)) {
        // Trivial accept of empty prefix.
        return true;
    }

    if (str == nullptr) {
        // Trivial reject of empty haystack.
        return false;
    }

    auto len_str = ::wcslen(str);
    auto len_start = ::wcslen(start);

    if (len_str < len_start) {
        return false;
    }

    if (ignore_case) {
#if defined(_WIN32)
        return (::wcsnicmp(str, start, len_start) == 0);
#else /* defined(_WIN32) */
        return (::wcsncasecmp(str, start, len_start) == 0);
#endif /* defined(_WIN32) */
    } else {
        return (::wcsncmp(str, start, len_start) == 0);
    }
}
