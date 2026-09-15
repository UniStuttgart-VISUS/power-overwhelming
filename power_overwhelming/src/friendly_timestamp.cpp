// <copyright file="friendly_timestamp.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT License. See LICENCE.txt for further details.
// </copyright>
// <author>Christoph Müller</author>

#include "friendly_timestamp.h"

#include <ctime>
#include <cwchar>

#include "visus/pwrowg/convert_string.h"


/*
 * PWROWG_DETAIL_NAMESPACE::friendly_timestamp
 */
_Check_return_ bool PWROWG_DETAIL_NAMESPACE::friendly_timestamp(
        _Out_writes_(cnt) wchar_t *dst,
        _In_ const std::size_t cnt) {
    if (dst == nullptr) {
        return false;
    }

    time_t time;
    ::time(&time);
    auto tm = ::gmtime(&time);

    return (::wcsftime(dst, cnt, L"%Y%m%d%H%M%S", tm) > 0);
}


/*
 * PWROWG_DETAIL_NAMESPACE::friendly_timestamp
 */
_Check_return_ bool PWROWG_DETAIL_NAMESPACE::friendly_timestamp(
        _Out_writes_(cnt) char *dst,
        _In_ const std::size_t cnt) {
    if (dst == nullptr) {
        return false;
    }

    time_t time;
    ::time(&time);
    auto tm = ::gmtime(&time);

    return (::strftime(dst, cnt, "%Y%m%d%H%M%S", tm) > 0);
}
