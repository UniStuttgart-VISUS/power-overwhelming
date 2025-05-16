// <copyright file="marker_sensor.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "marker_sensor.h"

#include <array>
#include <stdexcept>

#include "sensor_description_builder.h"


/*
 * PWROWG_DETAIL_NAMESPACE_BEGIN::marker_sensor::descriptions
 */
std::size_t PWROWG_DETAIL_NAMESPACE::marker_sensor::descriptions(
        _When_(dst != nullptr, _Out_writes_opt_(cnt)) sensor_description *dst,
        _In_ std::size_t cnt,
        _In_ const configuration_type& config) {
    const auto retval = (config.size() > 0) ? 1 : 0;

    if ((retval > 0) && (cnt >= retval)) {
        auto builder = sensor_description_builder::create()
            .with_id(L"VISUS/Marker")
            .with_vendor(L"VISUS")
            .with_name(L"VISUS timestamp markers")
            .with_type(sensor_type::unknown)
            .produces(reading_type::signed_integer)
            .measured_in(reading_unit::unknown);
        *dst = builder.build();
    }

    return retval;
}
