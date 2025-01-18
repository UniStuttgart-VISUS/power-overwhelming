// <copyright file="tinkerforge_sensor_source.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 - 2023 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/tinkerforge_sensor_source.h"

#include <stdexcept>
#include <type_traits>


/*
 * visus::power_overwhelming::operator |
 */
visus::power_overwhelming::tinkerforge_sensor_source
visus::power_overwhelming::operator |(_In_ const tinkerforge_sensor_source lhs,
        _In_ const tinkerforge_sensor_source rhs) {
    typedef std::underlying_type<tinkerforge_sensor_source>::type mask_type;
    auto retval = static_cast<mask_type>(lhs) | static_cast<mask_type>(rhs);
    return static_cast<tinkerforge_sensor_source>(retval);
}


/*
 * visus::power_overwhelming::operator &
 */
visus::power_overwhelming::tinkerforge_sensor_source
visus::power_overwhelming::operator &(_In_ const tinkerforge_sensor_source lhs,
        _In_ const tinkerforge_sensor_source rhs) {
    typedef std::underlying_type<tinkerforge_sensor_source>::type mask_type;
    auto retval = static_cast<mask_type>(lhs) & static_cast<mask_type>(rhs);
    return static_cast<tinkerforge_sensor_source>(retval);
}


/*
 * visus::power_overwhelming::to_string
 */
_Ret_valid_ const wchar_t *visus::power_overwhelming::to_string(
        _In_ const tinkerforge_sensor_source source) {
#define _GCC_IS_SHIT(v) L##v
#define _TO_STRING_CASE(v) case tinkerforge_sensor_source::v:\
    return _GCC_IS_SHIT(#v)

    switch (source) {
        _TO_STRING_CASE(current);
        _TO_STRING_CASE(voltage);
        _TO_STRING_CASE(power);
        _TO_STRING_CASE(all);

        default:
            throw std::invalid_argument("The specified sensor source is "
                "unknown. Make sure to add all new sources in to_string.");
    }

#undef _GCC_IS_SHIT
#undef _TO_STRING_CASE
}
