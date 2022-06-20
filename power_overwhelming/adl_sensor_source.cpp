// <copyright file="adl_sensor_source.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2022 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "power_overwhelming/adl_sensor_source.h"

#include <stdexcept>


/*
 * visus::power_overwhelming::to_string
 */
const wchar_t *visus::power_overwhelming::to_string(
        const adl_sensor_source source) {
#define _TO_STRING_CASE(v) case adl_sensor_source::##v: return L#v

    switch (source) {
        _TO_STRING_CASE(asic);
        _TO_STRING_CASE(cpu);
        _TO_STRING_CASE(graphics);
        _TO_STRING_CASE(soc);

        default:
            throw std::invalid_argument("The specified sensor source is "
                "unknown. Make sure to add all new sources in to_string.");
    }
}
