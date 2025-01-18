// <copyright file="oscilloscope_channel_polarity.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/oscilloscope_channel_polarity.h"

#include <stdexcept>


/*
 * visus::power_overwhelming::parse_oscilloscope_channel_polarity
 */
visus::power_overwhelming::oscilloscope_channel_polarity
visus::power_overwhelming::parse_oscilloscope_channel_polarity(
        _In_z_ const wchar_t *str) {
#define _GCC_IS_SHIT(v) L##v
#define _FROM_STRING_CASE(v) if (::wcscmp(str, _GCC_IS_SHIT(#v)) == 0) \
return oscilloscope_channel_polarity::v

    if (str == nullptr) {
        throw std::invalid_argument("The string to be parsed not not be null.");
    }

    _FROM_STRING_CASE(normal);
    _FROM_STRING_CASE(inverted);

    throw std::invalid_argument("The specified string could not be parsed as a "
        "channel polarity. Make sure to add all new enumeration members in "
        "the parsing function.");

#undef _GCC_IS_SHIT
#undef _FROM_STRING_CASE
}


/*
 * visus::power_overwhelming::to_string
 */
_Ret_valid_
const wchar_t *visus::power_overwhelming::to_string(
        _In_ const oscilloscope_channel_polarity bandwidth) {
#define _GCC_IS_SHIT(v) L##v
#define _TO_STRING_CASE(v) case oscilloscope_channel_polarity::v:\
    return _GCC_IS_SHIT(#v)

    switch (bandwidth) {
        _TO_STRING_CASE(normal);
        _TO_STRING_CASE(inverted);

        default:
            throw std::invalid_argument("The specified channel polarity is "
                "unknown. Make sure to add all new enumeration members in "
                "to_string.");
    }

#undef _GCC_IS_SHIT
#undef _TO_STRING_CASE
}
