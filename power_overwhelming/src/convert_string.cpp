// <copyright file="convert_string.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2022 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/convert_string.h"

#include <codecvt>
#include <cwchar>
#include <locale>
#include <system_error>

#include <errno.h>


/*
 * visus::power_overwhelming::detail::convert_string
 */
std::size_t visus::power_overwhelming::detail::convert_string(
        _Out_writes_opt_z_(cnt_output) char *output,
        _In_ const std::size_t cnt_output,
        _In_reads_or_z_(cnt_input) const wchar_t *input,
        _In_ const std::size_t cnt_input) {
    auto state = std::mbstate_t();

#if defined(_WIN32)
    std::size_t retval = 0;

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

    if (retval == static_cast<std::size_t>(-1)) {
        throw std::system_error(errno, std::system_category());
    }

    ++retval;   // Add terminating zero.
#endif /* defined(_WIN32) */

    return retval;
}


/*
 * visus::power_overwhelming::detail::convert_string
 */
std::size_t visus::power_overwhelming::detail::convert_string(
        _Out_writes_opt_z_(cnt_output) wchar_t *output,
        _In_ const std::size_t cnt_output,
        _In_reads_or_z_(cnt_input) const char *input,
        _In_ const std::size_t cnt_input) {
    auto state = std::mbstate_t();

#if defined(_WIN32)
    std::size_t retval = 0;

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

    if (retval == static_cast<std::size_t>(-1)) {
        throw std::system_error(errno, std::system_category());
    }

    ++retval;   // Add terminating zero.
#endif /* defined(_WIN32) */

    return retval;
}
