// <copyright file="string_functions.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "string_functions.h"

#include <cmath>
#include <cwchar>
#include <limits>
#include <stdexcept>


/*
 * PWROWG_DETAIL_NAMESPACE::compare
 */
int PWROWG_DETAIL_NAMESPACE::compare(_In_opt_z_ const char *lhs,
        _In_opt_z_ const char *rhs,
        _In_ const bool ignore_case) {
    if (lhs == rhs) {
        // Trivial equality.
        return 0;
    }

    if (lhs == nullptr) {
        return std::numeric_limits<int>::lowest();
    }

    if (rhs == nullptr) {
        return (std::numeric_limits<int>::max)();
    }

    if (ignore_case) {
#if defined(_WIN32)
        return ::stricmp(lhs, rhs);
#else /* defined(_WIN32) */
        return ::strcasecmp(lhs, rhs);
#endif /* defined(_WIN32) */
    } else {
        return ::strcmp(lhs, rhs);
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::compare
 */
int PWROWG_DETAIL_NAMESPACE::compare(_In_opt_z_ const wchar_t *lhs,
        _In_opt_z_ const wchar_t *rhs,
        _In_ const bool ignore_case) {
    if (lhs == rhs) {
        // Trivial equality.
        return 0;
    }

    if (lhs == nullptr) {
        return std::numeric_limits<int>::lowest();
    }

    if (rhs == nullptr) {
        return (std::numeric_limits<int>::max)();
    }

    if (ignore_case) {
#if defined(_WIN32)
        return ::wcsicmp(lhs, rhs);
#else /* defined(_WIN32) */
        return ::wcscasecmp(lhs, rhs);
#endif /* defined(_WIN32) */
    } else {
        return ::wcscmp(lhs, rhs);
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::parse_float
 */
float PWROWG_DETAIL_NAMESPACE::parse_float(_In_opt_z_ const char *str) {
    return (str != nullptr) ? std::atof(str) : 0.0f;
}


/*
 * PWROWG_DETAIL_NAMESPACE::parse_int
 */
int PWROWG_DETAIL_NAMESPACE::parse_int(_In_opt_z_ const char *str) {
    return (str != nullptr) ? std::atoi(str) : 0;
}


/*
 * PWROWG_DETAIL_NAMESPACE::parse_uint
 */
unsigned int PWROWG_DETAIL_NAMESPACE::parse_uint(
        _In_opt_z_ const char *str) {
    return (str != nullptr) ? static_cast<unsigned int>(std::atoll(str)) : 0;
}


/*
 * PWROWG_DETAIL_NAMESPACE::safe_duplicate
 */
_Ret_maybenull_z_ wchar_t *PWROWG_DETAIL_NAMESPACE::safe_duplicate(
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
 * PWROWG_DETAIL_NAMESPACE::safe_duplicate
 */
_Ret_maybenull_z_ char *PWROWG_DETAIL_NAMESPACE::safe_duplicate(
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
 * PWROWG_DETAIL_NAMESPACE::starts_with
 */
bool PWROWG_DETAIL_NAMESPACE::starts_with(_In_opt_z_ const char *str,
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
 * PWROWG_DETAIL_NAMESPACE::starts_with
 */
bool PWROWG_DETAIL_NAMESPACE::starts_with(_In_opt_z_ const wchar_t *str,
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
