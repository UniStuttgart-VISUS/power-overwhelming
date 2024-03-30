// <copyright file="convert_string.h" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2022 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#pragma once

#include <string>
#include <vector>

#include "power_overwhelming/power_overwhelming_api.h"


namespace visus {
namespace power_overwhelming {

namespace detail {

    extern std::size_t POWER_OVERWHELMING_API convert_string(
        _Out_writes_opt_z_(cnt_output) char *output,
        _In_ const std::size_t cnt_output,
        _In_reads_or_z_(cnt_input) const wchar_t *input,
        _In_ const std::size_t cnt_input);

    extern std::size_t POWER_OVERWHELMING_API convert_string(
        _Out_writes_opt_z_(cnt_output) wchar_t *output,
        _In_ const std::size_t cnt_output,
        _In_reads_or_z_(cnt_input) const char *input,
        _In_ const std::size_t cnt_input);
}

    /// <summary>
    /// Converts a string to the given character set.
    /// </summary>
    /// <typeparam name="TOutput">The character set of the target string.
    /// </typeparam>
    /// <typeparam name="TInput">The character set of the original string.
    /// </typeparam>
    /// </typeparam>
    /// <param name="str">The string to be converted. If is safe to pass
    /// <c>nullptr</c>, in which case an empty string will be assumed.</param>
    /// <returns>The converted string.</returns>
    template<class TOutput, class TInput>
    typename std::enable_if<std::is_same<TOutput, TInput>::value,
        std::basic_string<TOutput>>::type
    convert_string(_In_opt_z_ const TInput *str);

    /// <summary>
    /// Converts a string to the given character set.
    /// </summary>
    /// <typeparam name="TOutput">The character set of the target string.
    /// </typeparam>
    /// <typeparam name="TInput">The character set of the original string.
    /// </typeparam>
    /// </typeparam>
    /// <param name="str">The string to be converted. If is safe to pass
    /// <c>nullptr</c>, in which case an empty string will be assumed.</param>
    /// <returns>The converted string.</returns>
    template<class TOutput, class TInput>
    typename std::enable_if<!std::is_same<TOutput, TInput>::value,
        std::basic_string<TOutput>>::type
    convert_string(_In_opt_z_ const TInput *str);

    /// <summary>
    /// Converts a string to the given character set.
    /// </summary>
    /// <typeparam name="TOutput"></typeparam>
    /// <typeparam name="TInput"></typeparam>
    /// <typeparam name="TTraits"></typeparam>
    /// <typeparam name="TAlloc"></typeparam>
    /// <param name="str"></param>
    /// <returns></returns>
    template<class TOutput, class TInput, class TTraits, class TAlloc>
    inline std::basic_string<TOutput> convert_string(
            _In_ const std::basic_string<TInput, TTraits, TAlloc>& str) {
        return convert_string<TOutput>(str.c_str());
    }

} /* namespace power_overwhelming */
} /* namespace visus */

#include "power_overwhelming/convert_string.inl"
