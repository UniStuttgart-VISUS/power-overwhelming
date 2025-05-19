// <copyright file="nvml_scope.cpp" company="Visualisierungsinstitut der Universität Stuttgart">
// Copyright © 2021 - 2025 Visualisierungsinstitut der Universität Stuttgart.
// Licensed under the MIT licence. See LICENCE file for details.
// </copyright>
// <author>Christoph Müller</author>

#include "nvml_scope.h"

#include "nvidia_management_library.h"
#include "nvml_exception.h"


/*
 * PWROWG_DETAIL_NAMESPACE::nvml_scope::nvml_scope
 */
PWROWG_DETAIL_NAMESPACE::nvml_scope::nvml_scope(void) {
    auto status = nvidia_management_library::instance().nvmlInit();
    if (status != NVML_SUCCESS) {
        throw nvml_exception(status);
    }
}


/*
 * PWROWG_DETAIL_NAMESPACE::nvml_scope::~nvml_scope
 */
PWROWG_DETAIL_NAMESPACE::nvml_scope::~nvml_scope(void) {
    nvidia_management_library::instance().nvmlShutdown();
}
