// <copyright file="convert_string.h" company="Visualisierungsinstitut der Universit�t Stuttgart">
// Copyright � 2021 Visualisierungsinstitut der Universit�t Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph M�ller</author>

#pragma once

#include <string>


namespace visus {
namespace power_overwhelming {
namespace detail {

    std::wstring convert_string(const char *str);

    inline std::wstring convert_string(const std::string& str) {
        return convert_string(str.c_str());
    }

} /* namespace detail */
} /* namespace power_overwhelming */
} /* namespace visus */
