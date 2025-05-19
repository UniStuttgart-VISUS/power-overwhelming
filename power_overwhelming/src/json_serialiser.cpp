// <copyright file="json_serialiser.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "json_serialiser.h"

#include <fstream>
#include <stdexcept>


/*
 * nlohmann::json PWROWG_DETAIL_NAMESPACE::load_json
 */
nlohmann::json PWROWG_DETAIL_NAMESPACE::load_json(
        _In_z_ const wchar_t *path) {
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
