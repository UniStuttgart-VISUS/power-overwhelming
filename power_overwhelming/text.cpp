// <copyright file="text.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "text.h"

#include <codecvt>
#include <locale>
#include <system_error>

#include <wchar.h>


/*
 * visus::power_overwhelming::detail::convert_string
 */
std::size_t visus::power_overwhelming::detail::convert_string(
        char *output, const std::size_t cnt_output,
        const wchar_t *input, const std::size_t cnt_input) {
    std::size_t retval = 0;
    auto state = std::mbstate_t();

    auto error = ::wcsrtombs_s(&retval,
        output, (output == nullptr) ? 0 : cnt_output,
        &input, cnt_input,
        &state);

    if (error != 0) {
        throw std::system_error(error, std::system_category());
    }

    return retval;

    //return std::wcsrtombs_s(output, &input, cnt_output, &state);
}


/*
 * visus::power_overwhelming::detail::convert_string
 */
std::size_t visus::power_overwhelming::detail::convert_string(
        wchar_t *output, const std::size_t cnt_output,
        const char *input, const std::size_t cnt_input) {
    std::size_t retval = 0;
    auto state = std::mbstate_t();

    auto error = ::mbsrtowcs_s(&retval,
        output, (output == nullptr) ? 0 : cnt_output,
        &input, cnt_input,
        &state);

    if (error != 0) {
        throw std::system_error(error, std::system_category());
    }

    return retval;

    //return std::mbsrtowcs(output, &input, cnt_output, &state);
}
