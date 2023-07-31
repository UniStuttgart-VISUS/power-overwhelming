// <copyright file="oscilloscope_decimation_mode.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/oscilloscope_decimation_mode.h"

#include <stdexcept>


/*
 * visus::power_overwhelming::parse_oscilloscope_decimation_mode
 */
visus::power_overwhelming::oscilloscope_decimation_mode
visus::power_overwhelming::parse_oscilloscope_decimation_mode(
        _In_z_ const wchar_t *str) {
#define _GCC_IS_SHIT(v) L##v
#define _FROM_STRING_CASE(v) if (::wcscmp(str, _GCC_IS_SHIT(#v)) == 0) \
return oscilloscope_decimation_mode::v

    if (str == nullptr) {
        throw std::invalid_argument("The string to be parsed not not be null.");
    }

    _FROM_STRING_CASE(sample);
    _FROM_STRING_CASE(peak_detect);
    _FROM_STRING_CASE(high_resolution);

    throw std::invalid_argument("The specified string could not be parsed as a "
        "decimation mode. Make sure to add all new enumeration members in the"
        "parsing function.");

#undef _GCC_IS_SHIT
#undef _FROM_STRING_CASE
}


/*
 * visus::power_overwhelming::to_string
 */
_Ret_valid_
const wchar_t *visus::power_overwhelming::to_string(
        _In_ const oscilloscope_decimation_mode value) {
#define _GCC_IS_SHIT(v) L##v
#define _TO_STRING_CASE(v) case oscilloscope_decimation_mode::v:\
    return _GCC_IS_SHIT(#v)

    switch (value) {
        _TO_STRING_CASE(sample);
        _TO_STRING_CASE(peak_detect);
        _TO_STRING_CASE(high_resolution);

        default:
            throw std::invalid_argument("The specified decimation mode is "
                "unknown. Make sure to add all new enumeration members in "
                "to_string.");
    }

#undef _GCC_IS_SHIT
#undef _TO_STRING_CASE
}
