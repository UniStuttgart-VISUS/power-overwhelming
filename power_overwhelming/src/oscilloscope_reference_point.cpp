// <copyright file="oscilloscope_reference_point.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/oscilloscope_reference_point.h"

#include <stdexcept>


/*
 * visus::power_overwhelming::parse_oscilloscope_reference_point
 */
visus::power_overwhelming::oscilloscope_reference_point
visus::power_overwhelming::parse_oscilloscope_reference_point(
        _In_z_ const wchar_t *str) {
#define _GCC_IS_SHIT(v) L##v
#define _FROM_STRING_CASE(v) if (::wcscmp(str, _GCC_IS_SHIT(#v)) == 0) \
return oscilloscope_reference_point::v

    if (str == nullptr) {
        throw std::invalid_argument("The string to be parsed not not be null.");
    }

    _FROM_STRING_CASE(left);
    _FROM_STRING_CASE(middle);
    _FROM_STRING_CASE(right);

    throw std::invalid_argument("The specified string could not be parsed as a "
        "reference point. Make sure to add all new enumeration members in "
        "the parsing function.");

#undef _GCC_IS_SHIT
#undef _FROM_STRING_CASE
}


/*
 * visus::power_overwhelming::to_string
 */
_Ret_valid_
const wchar_t *visus::power_overwhelming::to_string(
        _In_ const oscilloscope_reference_point value) {
#define _GCC_IS_SHIT(v) L##v
#define _TO_STRING_CASE(v) case oscilloscope_reference_point::v:\
    return _GCC_IS_SHIT(#v)

    switch (value) {
        _TO_STRING_CASE(left);
        _TO_STRING_CASE(middle);
        _TO_STRING_CASE(right);

        default:
            throw std::invalid_argument("The specified reference point is "
                "unknown. Make sure to add all new enumeration members in "
                "to_string.");
    }

#undef _GCC_IS_SHIT
#undef _TO_STRING_CASE
}
