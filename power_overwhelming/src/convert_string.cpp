// <copyright file="convert_string.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2022 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/convert_string.h"

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

#if defined(_WIN32)
    auto error = ::wcsrtombs_s(&retval,
        output, (output == nullptr) ? 0 : cnt_output,
        &input, cnt_input,
        &state);

    if (error != 0) {
        throw std::system_error(error, std::system_category());
    }

#else /* defined(_WIN32) */
    auto retval = std::wcsrtombs(output, &input,
        (output == nullptr) ? 0 : cnt_output,
        &state);

    if (retval != static_cast<std::size_t>(-1)) {
        throw std::system_error(error, std::system_category());
    }

    ++retval;   // Add terminating zero.
#endif /* defined(_WIN32) */

    return retval;
}


/*
 * visus::power_overwhelming::detail::convert_string
 */
std::size_t visus::power_overwhelming::detail::convert_string(
        wchar_t *output, const std::size_t cnt_output,
        const char *input, const std::size_t cnt_input) {
    std::size_t retval = 0;
    auto state = std::mbstate_t();

#if defined(_WIN32)
    auto error = ::mbsrtowcs_s(&retval,
        output, (output == nullptr) ? 0 : cnt_output,
        &input, cnt_input,
        &state);

    if (error != 0) {
        throw std::system_error(error, std::system_category());
    }

#else /* defined(_WIN32) */
    auto retval = std::mbsrtowcs(output, &input,
        (output == nullptr) ? 0 : cnt_output,
        &state);

    if (retval != static_cast<std::size_t>(-1)) {
        throw std::system_error(error, std::system_category());
    }

    ++retval;   // Add terminating zero.
#endif /* defined(_WIN32) */

    return retval;
}
