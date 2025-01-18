// <copyright file="adl_sensor_source.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 - 2024 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>

#include "visus/pwrowg/adl_sensor_source.h"

#include <stdexcept>
#include <type_traits>


/*
 * visus::power_overwhelming::operator |
 */
visus::power_overwhelming::adl_sensor_source
visus::power_overwhelming::operator |(_In_ const adl_sensor_source lhs,
        _In_ const adl_sensor_source rhs) {
    typedef std::underlying_type<adl_sensor_source>::type mask_type;
    auto retval = static_cast<mask_type>(lhs) | static_cast<mask_type>(rhs);
    return static_cast<adl_sensor_source>(retval);
}


/*
 * visus::power_overwhelming::operator &
 */
visus::power_overwhelming::adl_sensor_source
visus::power_overwhelming::operator &(_In_ const adl_sensor_source lhs,
        _In_ const adl_sensor_source rhs) {
    typedef std::underlying_type<adl_sensor_source>::type mask_type;
    auto retval = static_cast<mask_type>(lhs) & static_cast<mask_type>(rhs);
    return static_cast<adl_sensor_source>(retval);
}


/*
 * visus::power_overwhelming::parse_adl_sensor_source
 */
visus::power_overwhelming::adl_sensor_source
visus::power_overwhelming::parse_adl_sensor_source(_In_z_ const wchar_t *str) {
    if (str == nullptr) {
        throw std::invalid_argument("Only a valid string can be parsed into a "
            "adl_sensor_source.");
    }

    const std::wstring s(str);
#define _FROM_STRING_CASE(v) else if (to_string(adl_sensor_source::v) == s) \
    return adl_sensor_source::v

    if (false);
    _FROM_STRING_CASE(asic);
    _FROM_STRING_CASE(cpu);
    _FROM_STRING_CASE(graphics);
    _FROM_STRING_CASE(soc);
    _FROM_STRING_CASE(all);
    else throw std::invalid_argument("The given string represents no "
        "valid adl_sensor_source");

#undef _FROM_STRING_CASE
}


/*
 * visus::power_overwhelming::to_string
 */
_Ret_z_ const wchar_t *visus::power_overwhelming::to_string(
        _In_ const adl_sensor_source source) {
#define _GCC_IS_SHIT(v) L##v
#define _TO_STRING_CASE(v) case adl_sensor_source::v: return _GCC_IS_SHIT(#v)

    switch (source) {
        _TO_STRING_CASE(asic);
        _TO_STRING_CASE(cpu);
        _TO_STRING_CASE(graphics);
        _TO_STRING_CASE(soc);
        _TO_STRING_CASE(all);

        default:
            throw std::invalid_argument("The specified sensor source is "
                "unknown. Make sure to add all new sources in to_string.");
    }

#undef _GCC_IS_SHIT
#undef _TO_STRING_CASE
}
