// <copyright file="nvml_exception.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "nvml_exception.h"

#include "nvidia_management_library.h"

using PWROWG_DETAIL_NAMESPACE::nvidia_management_library;


/*
 * visus::power_overwhelming::nvml_exception::nvml_exception
 */
PWROWG_NAMESPACE::nvml_exception::nvml_exception(const value_type code)
    : std::runtime_error(nvidia_management_library::instance().nvmlErrorString(
    code)), _code(code) { }
