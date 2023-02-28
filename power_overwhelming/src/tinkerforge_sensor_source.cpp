// <copyright file="tinkerforge_sensor_source.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/tinkerforge_sensor_source.h"

#include <stdexcept>
#include <type_traits>


/*
 * visus::power_overwhelming::operator |
 */
visus::power_overwhelming::tinkerforge_sensor_source
visus::power_overwhelming::operator |(const tinkerforge_sensor_source lhs,
        const tinkerforge_sensor_source rhs) {
    typedef std::underlying_type<tinkerforge_sensor_source>::type mask_type;
    auto retval = static_cast<mask_type>(lhs) | static_cast<mask_type>(rhs);
    return static_cast<tinkerforge_sensor_source>(retval);
}


/*
 * visus::power_overwhelming::operator &
 */
visus::power_overwhelming::tinkerforge_sensor_source
visus::power_overwhelming::operator &(const tinkerforge_sensor_source lhs,
        const tinkerforge_sensor_source rhs) {
    typedef std::underlying_type<tinkerforge_sensor_source>::type mask_type;
    auto retval = static_cast<mask_type>(lhs) & static_cast<mask_type>(rhs);
    return static_cast<tinkerforge_sensor_source>(retval);
}


/*
 * visus::power_overwhelming::to_string
 */
const wchar_t *visus::power_overwhelming::to_string(
        const tinkerforge_sensor_source source) {
#define _TO_STRING_CASE(v) case tinkerforge_sensor_source::##v: return L#v

    switch (source) {
        _TO_STRING_CASE(current);
        _TO_STRING_CASE(voltage);
        _TO_STRING_CASE(power);
        _TO_STRING_CASE(all);

        default:
            throw std::invalid_argument("The specified sensor source is "
                "unknown. Make sure to add all new sources in to_string.");
    }

#undef _TO_STRING_CASE
}
