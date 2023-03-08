// <copyright file="nvml_exception.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2023 Visualisierungsinstitut der Universität Stuttgart. Alle Rechte vorbehalten.
// </copyright>
// <author>Christoph Müller</author>

#include "nvml_exception.h"

#include "nvidia_management_library.h"

using visus::power_overwhelming::detail::nvidia_management_library;


/*
 * visus::power_overwhelming::nvml_exception::nvml_exception
 */
visus::power_overwhelming::nvml_exception::nvml_exception(const value_type code)
    : std::runtime_error(nvidia_management_library::instance().nvmlErrorString(
    code)), _code(code) { }
