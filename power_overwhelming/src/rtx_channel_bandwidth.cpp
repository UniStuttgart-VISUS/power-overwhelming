// <copyright file="rtx_channel_bandwidth.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/rtx_channel_bandwidth.h"

#include <stdexcept>


/*
 * PWROWG_NAMESPACE::parse_rtx_channel_bandwidth
 */
PWROWG_NAMESPACE::rtx_channel_bandwidth
PWROWG_NAMESPACE::parse_rtx_channel_bandwidth(
        _In_z_ const wchar_t *str) {
#define _GCC_IS_SHIT(v) L##v
#define _FROM_STRING_CASE(v) if (::wcscmp(str, _GCC_IS_SHIT(#v)) == 0) \
return rtx_channel_bandwidth::v

    if (str == nullptr) {
        throw std::invalid_argument("The string to be parsed not not be null.");
    }

    _FROM_STRING_CASE(full);
    _FROM_STRING_CASE(limit_to_20_mhz);

    throw std::invalid_argument("The specified string could not be parsed as a "
        "channel bandwidth. Make sure to add all new enumeration members in "
        "the parsing function.");

#undef _GCC_IS_SHIT
#undef _FROM_STRING_CASE
}


/*
 * PWROWG_NAMESPACE::to_string
 */
_Ret_valid_
const wchar_t *PWROWG_NAMESPACE::to_string(
        _In_ const rtx_channel_bandwidth bandwidth) {
#define _GCC_IS_SHIT(v) L##v
#define _TO_STRING_CASE(v) case rtx_channel_bandwidth::v:\
    return _GCC_IS_SHIT(#v)

    switch (bandwidth) {
        _TO_STRING_CASE(full);
        _TO_STRING_CASE(limit_to_20_mhz);

        default:
            throw std::invalid_argument("The specified channel bandwidth is "
                "unknown. Make sure to add all new enumeration members in "
                "to_string.");
    }

#undef _GCC_IS_SHIT
#undef _TO_STRING_CASE
}
