// <copyright file="reading_type.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/reading_type.h"

#include <cassert>
#include <cstring>


/*
 * PWROWG_NAMESPACE::to_string
 */
std::size_t PWROWG_NAMESPACE::to_string(_Out_writes_opt_z_(cnt) wchar_t *dst,
        _In_ std::size_t cnt, _In_ const reading_type type) noexcept {
#define _MK_STR(v) L##v
#define _MK_CASE(v, s) case reading_type::v: value = _MK_STR(s); break;

    if (dst == nullptr) {
        cnt = 0;
    }

    const auto *value = _MK_STR("void");
    switch (type) {
        _MK_CASE(floating_point, "float32");
        _MK_CASE(signed_integer, "int32");
        _MK_CASE(unsigned_integer, "uint32");
    }

    const auto retval = ::wcslen(value) + 1;
    if (retval <= cnt) {
        ::memcpy(dst, value, retval * sizeof(*value));
    }

    return retval;
#undef _MK_STR
#undef _MK_CASE
}


/*
 * PWROWG_NAMESPACE::to_string
 */
std::size_t PWROWG_NAMESPACE::to_string(_Out_writes_opt_z_(cnt) char *dst,
        _In_ std::size_t cnt, _In_ const reading_type type) noexcept {
#define _MK_STR(v) v
#define _MK_CASE(v, s) case reading_type::v: value = _MK_STR(s); break;

    if (dst == nullptr) {
        cnt = 0;
    }

    const auto *value = _MK_STR("void");
    switch (type) {
        _MK_CASE(floating_point, "float32");
        _MK_CASE(signed_integer, "int32");
        _MK_CASE(unsigned_integer, "uint32");
    }

    const auto retval = ::strlen(value) + 1;
    if (retval <= cnt) {
        ::memcpy(dst, value, retval * sizeof(*value));
    }

    return retval;
#undef _MK_STR
#undef _MK_CASE
}
