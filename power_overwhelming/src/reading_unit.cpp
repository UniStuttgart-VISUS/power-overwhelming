// <copyright file="reading_unit.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/reading_unit.h"

#include <cassert>
#include <cstring>
#include <type_traits>


/*
 * PWROWG_NAMESPACE::to_string
 */
std::size_t PWROWG_NAMESPACE::to_string(_Out_writes_opt_z_(cnt) wchar_t *dst,
    _In_ std::size_t cnt,_In_ const reading_unit unit) noexcept {
#define _MK_STR(v) L##v
#define _MK_CASE(v, s) case reading_unit::v: value = _MK_STR(s); break;

    if (dst == nullptr) {
        cnt = 0;
    }

    const wchar_t *value = nullptr;
    switch (unit) {
        _MK_CASE(unknown, "unknown");
        _MK_CASE(ampere, "A");
        _MK_CASE(volt, "V");
        _MK_CASE(watt, "W");
        _MK_CASE(joule, "J");
        _MK_CASE(watt_hour, "Wh");
        _MK_CASE(coulomb, "C");
        _MK_CASE(ampere_hour, "Ah");
        _MK_CASE(celsius, "°C");
        _MK_CASE(kelvin, "K");
    }

    if (value != nullptr) {
        const auto retval = ::wcslen(value) + 1;
        if (retval <= cnt) {
            ::memcpy(dst, value, retval * sizeof(*value));
        }

        return retval;

    } else {
        typedef std::underlying_type_t<reading_unit> int_t;
        auto v = std::to_wstring(static_cast<int_t>(unit));
        const auto retval = v.size() + 1;
        if (retval <= cnt) {
            ::memcpy(dst, v.c_str(), retval * sizeof(*v.c_str()));
        }

        return retval;
    }
#undef _MK_STR
#undef _MK_CASE
}


/*
 * PWROWG_NAMESPACE::to_string
 */
std::size_t PWROWG_NAMESPACE::to_string(_Out_writes_opt_z_(cnt) char *dst,
    _In_ std::size_t cnt, _In_ const reading_unit unit) noexcept {
#define _MK_STR(v) v
#define _MK_CASE(v, s) case reading_unit::v: value = _MK_STR(s); break;

    if (dst == nullptr) {
        cnt = 0;
    }

    const char *value = nullptr;
    switch (unit) {
        _MK_CASE(unknown, "unknown");
        _MK_CASE(ampere, "A");
        _MK_CASE(volt, "V");
        _MK_CASE(watt, "W");
        _MK_CASE(joule, "J");
        _MK_CASE(watt_hour, "Wh");
        _MK_CASE(coulomb, "C");
        _MK_CASE(ampere_hour, "Ah");
        _MK_CASE(celsius, "°C");
        _MK_CASE(kelvin, "K");
    }

    if (value != nullptr) {
        const auto retval = ::strlen(value) + 1;
        if (retval <= cnt) {
            ::memcpy(dst, value, retval * sizeof(*value));
        }

        return retval;

    } else {
        typedef std::underlying_type_t<reading_unit> int_t;
        auto v = std::to_string(static_cast<int_t>(unit));
        const auto retval = v.size() + 1;
        if (retval <= cnt) {
            ::memcpy(dst, v.c_str(), retval * sizeof(*v.c_str()));
        }

        return retval;
    }
#undef _MK_STR
#undef _MK_CASE
}
