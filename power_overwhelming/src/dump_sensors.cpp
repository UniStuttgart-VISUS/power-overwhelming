// <copyright file="dump_sensors.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2026 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "visus/pwrowg/dump_sensors.h"

#include <stdexcept>

#include "visus/pwrowg/convert_string.h"

#include "json_serialiser.h"
#include "sensor_description_builder.h"
#include "sensor_utilities.h"


PWROWG_DETAIL_NAMESPACE_BEGIN

/// <summary>
/// Restores the given array of <see cref="sensor_description" />s from the
/// given JSON array.
/// </summary>
static std::size_t restore_sensor_descriptions(
        _Out_writes_opt_(cnt) sensor_description *sensors,
        _In_ std::size_t cnt,
        _In_ const nlohmann::json& json) {
    if (sensors == nullptr) {
        cnt = 0;
    }

    if (json.is_array()) {
        const auto retval = json.size();

        for (std::size_t i = 0; (i < cnt) && (i < retval); ++i) {
            sensors[i] = json_deserialise<sensor_description>(json[i]);
            assert(sensors[i].id() != nullptr);
            assert(*sensors[i].id() != 0);
        }

        return retval;

    } else if (json.is_object()) {
        constexpr std::size_t retval = 1;
        sensor_description_builder builder;

        if (cnt >= retval) {
            *sensors = json_deserialise<sensor_description>(json);
        }

        return retval;

    } else {
        // This cannot be a sensor description or array thereof.
        return 0;
    }
}

PWROWG_DETAIL_NAMESPACE_END


/*
 * PWROWG_NAMESPACE::dump_sensors
 */
std::size_t PWROWG_NAMESPACE::dump_sensors(
        _In_ const sensor_array& sensors,
        _In_z_ const char *path) {
    auto descs = detail::get_all_sensor_descs(sensors);
    detail::save_json(descs, path);
    return descs.size();
}


/*
 * PWROWG_NAMESPACE::dump_sensors
 */
std::size_t PWROWG_NAMESPACE::dump_sensors(
        _In_ const sensor_array& sensors,
        _In_z_ const wchar_t *path) {
    auto descs = detail::get_all_sensor_descs(sensors);
    detail::save_json(descs, path);
    return descs.size();
}


/*
 * PWROWG_NAMESPACE::restore_sensor_descriptions
 */
std::size_t PWROWG_NAMESPACE::restore_sensor_descriptions(
        _Out_writes_opt_(cnt) sensor_description *sensors,
        _In_ const std::size_t cnt,
        _In_z_ const wchar_t *path) {
    return detail::restore_sensor_descriptions(sensors, cnt,
        detail::load_json(path));
}


/*
 * PWROWG_NAMESPACE::restore_sensor_descriptions
 */
std::size_t PWROWG_NAMESPACE::restore_sensor_descriptions(
        _Out_writes_opt_(cnt) sensor_description *sensors,
        _In_ const std::size_t cnt,
        _In_z_ const char *path) {
    return detail::restore_sensor_descriptions(sensors, cnt,
        detail::load_json(path));
}
