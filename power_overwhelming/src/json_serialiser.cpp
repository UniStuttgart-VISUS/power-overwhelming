// <copyright file="json_serialiser.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "json_serialiser.h"

#include <fstream>
#include <stdexcept>

#include "sensor_description_builder.h"


/*
 * json_serialiser<sensor_description,false, false>::deserialise
 */
typename PWROWG_DETAIL_NAMESPACE::json_serialiser<
    PWROWG_NAMESPACE::sensor_description, false, false>::value_type
PWROWG_DETAIL_NAMESPACE::json_serialiser<
        PWROWG_NAMESPACE::sensor_description,false, false>
::deserialise(_In_ const nlohmann::json& json) {
    sensor_description_builder builder;

    {
        auto it = json.find("id");
        builder.with_id(json_deserialise<std::string>(*it));
    }

    {
        auto it = json.find("label");
        auto value = json_deserialise<std::wstring>(*it);
        builder.with_id(value.c_str());
    }

    {
        auto it = json.find("name");
        auto value = json_deserialise<std::string>(*it);
        builder.with_name(value.c_str());
    }

    {
        auto it = json.find("path");
        builder.with_path(json_deserialise<std::string>(*it));
    }

    {
        auto it = json.find("readingType");
        builder.produces(json_deserialise<reading_type>(*it));
    }

    {
        auto it = json.find("readingUnit");
        builder.measured_in(json_deserialise<reading_unit>(*it));
    }

    {
        auto it = json.find("type");
        builder.with_type(json_deserialise<sensor_type>(*it));
    }

    {
        auto it = json.find("path");
        auto value = json_deserialise<std::wstring>(*it);
        builder.with_vendor(value.c_str());
    }

    // HAZARD: The deserialiser cannot restore any private data, so the
    // description might be unusable in a new array.
    return builder.build();
}


/*
 * json_serialiser<sensor_description,false, false>::serialise
 */
nlohmann::json PWROWG_DETAIL_NAMESPACE::json_serialiser<
    PWROWG_NAMESPACE::sensor_description, false, false>
::serialise(_In_ const value_type& value) {
    auto retval = nlohmann::json::object();

    retval["id"] = json_serialise(value.id());
    retval["label"] = json_serialise(value.label());
    retval["name"] = json_serialise(value.name());
    retval["path"] = json_serialise(value.path());
    retval["readingType"] = json_serialise(value.reading_type());
    retval["readingUnit"] = json_serialise(value.reading_unit());
    retval["type"] = json_serialise(value.sensor_type());
    retval["vendor"] = json_serialise(value.vendor());

    return retval;
}


/*
 * nlohmann::json PWROWG_DETAIL_NAMESPACE::load_json
 */
nlohmann::json PWROWG_DETAIL_NAMESPACE::load_json(_In_z_ const wchar_t *path) {
    if (path == nullptr) {
        throw std::invalid_argument("The path to the JSON file to read must "
            "not be null.");
    }

    std::ifstream s;
    s.exceptions(s.exceptions() | std::ios::failbit | std::ios::badbit);

#if defined(_WIN32)
    s.open(path);
#else /* defined(_WIN32) */
    auto p = PWROWG_NAMESPACE::convert_string<char>(path);
    s.open(p);
#endif /* defined(_WIN32) */

    nlohmann::json retval;
    s >> retval;
    s.close();

    return retval;
}


/*
 * nlohmann::json PWROWG_DETAIL_NAMESPACE::load_json
 */
nlohmann::json PWROWG_DETAIL_NAMESPACE::load_json(_In_z_ const char *path) {
    if (path == nullptr) {
        throw std::invalid_argument("The path to the JSON file to read must "
            "not be null.");
    }

    std::ifstream s;
    s.exceptions(s.exceptions() | std::ios::failbit | std::ios::badbit);
    s.open(path);

    nlohmann::json retval;
    s >> retval;
    s.close();

    return retval;
}


/*
 * PWROWG_DETAIL_NAMESPACE::save_json
 */
void PWROWG_DETAIL_NAMESPACE::save_json(
        _In_ const nlohmann::json& json,
        _In_z_ const wchar_t *path) {
    if (path == nullptr) {
        throw std::invalid_argument("The path to the JSON file to write must "
            "not be null.");
    }

    std::ofstream s;
    s.exceptions(s.exceptions() | std::ios::failbit | std::ios::badbit);

#if defined(_WIN32)
    s.open(path, std::ofstream::trunc);
#else /* defined(_WIN32) */
    auto p = PWROWG_NAMESPACE::convert_string<char>(path);
    s.open(p, std::ofstream::trunc);
#endif /* defined(_WIN32) */

    s << json;
    s.close();
}

/*
 * PWROWG_DETAIL_NAMESPACE::save_json
 */
void PWROWG_DETAIL_NAMESPACE::save_json(
        _In_ const nlohmann::json& json,
        _In_z_ const char *path) {
    if (path == nullptr) {
        throw std::invalid_argument("The path to the JSON file to write must "
            "not be null.");
    }

    std::ofstream s;
    s.exceptions(s.exceptions() | std::ios::failbit | std::ios::badbit);
    s.open(path, std::ofstream::trunc);

    s << json;
    s.close();
}

