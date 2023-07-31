// <copyright file="json_serialiser.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "json_serialiser.h"

#include <fstream>
#include <stdexcept>



/*
 * nlohmann::json visus::power_overwhelming::detail::load_json
 */
nlohmann::json visus::power_overwhelming::detail::load_json(
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
    auto p = power_overwhelming::convert_string<char>(path);
    s.open(p);
#endif /* defined(_WIN32) */

    nlohmann::json retval;
    s >> retval;
    s.close();

    return retval;
}


/*
 * visus::power_overwhelming::detail::save_json
 */
void visus::power_overwhelming::detail::save_json(
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
    auto p = power_overwhelming::convert_string<char>(path);
    s.open(p, std::ofstream::trunc);
#endif /* defined(_WIN32) */

    json >> s;
    s.close();
}
