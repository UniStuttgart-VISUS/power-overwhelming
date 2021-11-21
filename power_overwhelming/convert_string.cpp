// <copyright file="convert_string.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "convert_string.h"

#include <system_error>
#include <vector>

#include <Windows.h>


/*
 * visus::power_overwhelming::detail::convert_string
 */
std::wstring visus::power_overwhelming::detail::convert_string(
        const char *str) {
    if (str == nullptr) {
        return std::wstring();
    }

    const auto strLen = static_cast<int>(::strlen(str));

    auto wcsLen = ::MultiByteToWideChar(CP_UTF8, 0, str, strLen, nullptr, 0);
    if (wcsLen <= 0) {
        throw std::system_error(::GetLastError(), std::system_category());
    }

    std::vector<wchar_t> retval;
    retval.resize(++wcsLen);

    wcsLen = ::MultiByteToWideChar(CP_UTF8, 0, str, strLen, retval.data(),
        wcsLen);
    if (wcsLen <= 0) {
        throw std::system_error(::GetLastError(), std::system_category());
    }

    return retval.data();
}
